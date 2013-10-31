#define ZJetsAnalyzer_cxx
#include "ZJetsAnalyzer.h"
#include "ZJetsDefs.h"
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
#include <Riostream.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TH2F.h>
#include <fstream>

#include <DataFormats/Math/interface/deltaPhi.h>
#include <DataFormats/Math/interface/deltaR.h>
#include <TLorentzVector.h>
#include <../../../QCDAnalysis/Tools/interface/EventShapeLorentz.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "FWCore/Utilities/interface/Exception.h"
#endif

using namespace std;

//#ifdef __MAKECINT__
//#pragma link C++ class vector<float>+;
//#endif

//		In a ROOT session, you can do:
//			Root > .L ZJetsAnalyzer.C++
//			Root > ZJetsAnalyzer t(0,4); // Load the analysis on the sample number 4 
//			Root > t.GetEntry(12);	     // Fill t data members with entry number 12
//			Root > t.Show();				     // Show values of entry 12
//			Root > t.Show(16);			     // Read and show values of entry 16
//			Root > t.Loop();				     // Loop on all entries
//

//		This is the loop skeleton where:
//			jentry is the global entry number in the chain;
//			ientry is the entry number in the current Tree.
//		Note that the argument to GetEntry must be:
//			jentry for TChain::GetEntry;
//			ientry for TTree::GetEntry and TBranch::GetEntry.
//
//		To read only selected branches, Insert statements like:
//			METHOD1:
//				fChain->SetBranchStatus("*",0);						// disable all branches
//				fChain->SetBranchStatus("branchname",1);	// activate branchname
//			METHOD2:
//				replace line fChain->GetEntry(jentry);	// read all branches
//				by b_branchname->GetEntry(ientry);			// read only this branch


void ZJetsAnalyzer::Loop(){


	// ==================================== choose the tools
	
	bool RedAn = false;								// analysis with a reduced entries number for tests
	bool data_ReReco = true;					// analysis with data ReReco or data PromptReco
	string geo = "barrel";						// barrel or endcaps
		
	bool plothistos = false;					// please select which plots to show
	bool textfile = true;							// if you want a text report for each sample
	Int_t itype = 16;									// it identifies histos with different analysis 

	// choose the sample:
	// -----------------------------------------------------
	// mysample == 0   -> Test
	// -----------------------------------------------------
	// mysample == 91  -> DYJetsToLL_M-50
	// -----------------------------------------------------

	// ==================================== exception controls

	if (!(geo == "barrel" || geo == "endcaps")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps)\". You wrote: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}


	// ==================================== numeric and definition side of the code
	
	double Lumi_t;
	if (data_ReReco) Lumi_t = 19712.; // /pb
	else Lumi_t = 19027.853; // /pb
	double xsec = 1.;
	double FiltEff = 1.;
	double kFac = 1.;
	double nEvents = 1.;

	Float_t weight = 1; 

	string geo_s = geo + "/";
	string sample = "";
	string out_files = "output_files/";
	string histos = "_histos_%d_";
	string report = "_report_%d_";
	string root = ".root";
	string txt = ".txt";
				

	cout << "Analysis on " << geo << endl;
	cout << "mysample is " << mysample << endl;

	// test -----------------------------------------------------------------
	if (mysample == 0){
		sample = "TEST";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	// MC signal DYJetsToLL_M-50 --------------------------------------------
	else if (mysample == 91) {
		sample = "DYJetsToLL_M_50";
	sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 30458871;
		xsec = 3503.71; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}
	
	weight_r = weight;
	sample_r = sample;
	// end numeric and definition side of the code

	if (fChain == 0) return;

	// ==================================== initialize and book histograms
	
	TFile *fhistos= new TFile(outputname, "RECREATE");
	Book_Histos();
 
	// ==================================== loop on entries
	
	Long64_t nentries;
	if(RedAn){
		nentries = 1000000; // analysis with a reduced entries number
	}
	else{
		nentries = fChain->GetEntriesFast();
	}

	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries << endl;
	nentries_r = nentries; 

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if(jentry<1) cout << "Entering first event" << endl;
		if(jentry%100000 == 0) cout << jentry << endl;
		Zero_Variables();


		// ==================================== GEN selection
		if (isMC){

			// jetVeto: jetsGEN vs. leptonsGEN 
			if( (nLeptonsGEN >= 2 && (nLeptonsGEN == (int)lepPtGEN->size())) && (nJetsGEN > 0 && (nJetsGEN == (int)jetPtGEN->size())) ){

				SelectedJetsGEN_N = 0;

				for (unsigned int iJetGENPos = 0; iJetGENPos < jetPtGEN->size(); iJetGENPos++) {

					// selection of cleaned GEN jets vs. 2 first GEN leptons 
					bool closeGEN = false;
					for (unsigned int jLepGENPos = 0; jLepGENPos < 2; jLepGENPos++){
						if ( deltaR(lepEtaGEN->at(jLepGENPos), lepPhiGEN->at(jLepGENPos), jetEtaGEN->at(iJetGENPos), jetPhiGEN->at(iJetGENPos)) < 0.5 ) {
							closeGEN = true;
							break;	
						}					
					}
					if (!closeGEN){

						// jets kinematic selection
						if(jetPtGEN->at(iJetGENPos) > 30. && TMath::Abs(jetEtaGEN->at(iJetGENPos)) < 2.5 ){
							SelectedJetsGEN_Pt.push_back(jetPtGEN->at(iJetGENPos));
							SelectedJetsGEN_E.push_back(jetEGEN->at(iJetGENPos));
							SelectedJetsGEN_Eta.push_back(jetEtaGEN->at(iJetGENPos));
							SelectedJetsGEN_Phi.push_back(jetPhiGEN->at(iJetGENPos));
							SelectedJetsGEN_N += 1;
						} // end jets kinematic selection
					} // end selection of cleaned GEN jets vs. 2 first GEN leptons
				}
			} // end jetVeto: jetsGEN vs. leptonsGEN

			// collectives jetsGEN properties
			SelectedJetsGEN_HT = 0;
			for(unsigned int zJetGENPos = 0; zJetGENPos < SelectedJetsGEN_Pt.size(); zJetGENPos++) {
				SelectedJetsGEN_HT += SelectedJetsGEN_Pt.at(zJetGENPos);
			} // end collectives jetsGEN properties

			// LeptonsGEN selection
			if (nLeptonsGEN >= 2 && (nLeptonsGEN == (int)lepPtGEN->size()) ){

/*				
				// eta - definition
				bool geo_selGEN_1 = false;
				if (geo == "barrel") {
					geo_selGEN_1 = TMath::Abs(lepEtaGEN->at(0)) < 1.479;
				}
				else if (geo == "endcaps"){
					geo_selGEN_1 = TMath::Abs(lepEtaGEN->at(0)) > 1.479 && TMath::Abs(lepEtaGEN->at(0)) < 3.;
				}
				else {
					cout << "ERROR: Wrong geometry string written (only barrel or endcaps)" << endl;
				} 

				bool geo_selGEN_2 = false;
				if (geo == "barrel") {
					geo_selGEN_2 = TMath::Abs(lepEtaGEN->at(1)) < 1.479;
				}
				else if (geo == "endcaps"){
					geo_selGEN_2 = TMath::Abs(lepEtaGEN->at(1)) > 1.479 && TMath::Abs(lepEtaGEN->at(1)) < 3.;
				}
				else {
					cout << "ERROR: Wrong geometry string written (only barrel or endcaps)" << endl;
				} // end eta - definition
*/

				// double muon or double electron selection
				if ((lepChIdGEN->at(0)*lepChIdGEN->at(1) == -169) || (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -121)){	

					// leptonGEN kinematic selection
					if ((lepPtGEN->at(0) > 20. && TMath::Abs(lepEtaGEN->at(0)) < 2.4) && (lepPtGEN->at(1) > 20. && TMath::Abs(lepEtaGEN->at(1)) < 2.4)) {

						// llM kinematic selection
						if (TMath::Abs(llMGEN-91) < 20 && TMath::Abs(llEtaGEN) < 1.479) {

							// kin JetsGEN (cleaned vs. 2 leptonGEN) selection
							if (SelectedJetsGEN_N > 0){
							
								// HTGEN selection
								if (SelectedJetsGEN_HT > 0){

									if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -169){
									
										nLeptonsGEN_mumu_N0_->Fill(nLeptonsGEN, weight);
										
										lepPtGEN_mumu_N0_1_->Fill(lepPtGEN->at(0), weight);
										lepEGEN_mumu_N0_1_->Fill(lepEGEN->at(0), weight);
										lepEtaGEN_mumu_N0_1_->Fill(lepEtaGEN->at(0), weight);
										lepPhiGEN_mumu_N0_1_->Fill(lepPhiGEN->at(0), weight);

										lepPtGEN_mumu_N0_2_->Fill(lepPtGEN->at(1), weight);
										lepEGEN_mumu_N0_2_->Fill(lepEGEN->at(1), weight);
										lepEtaGEN_mumu_N0_2_->Fill(lepEtaGEN->at(1), weight);
										lepPhiGEN_mumu_N0_2_->Fill(lepPhiGEN->at(1), weight);

										llMGEN_mumu_N0_->Fill(llMGEN, weight);
										llPtGEN_mumu_N0_->Fill(llPtGEN, weight);
										llEtaGEN_mumu_N0_->Fill(llEtaGEN, weight);
										llPhiGEN_mumu_N0_->Fill(llPhiGEN, weight);

										SelectedJetsGEN_N_mumu_N0_->Fill(SelectedJetsGEN_N, weight);

										SelectedJets_PtGEN_mumu_N0_1_->Fill(SelectedJetsGEN_Pt.at(0), weight);
										SelectedJets_EGEN_mumu_N0_1_->Fill(SelectedJetsGEN_E.at(0), weight);
										SelectedJets_EtaGEN_mumu_N0_1_->Fill(SelectedJetsGEN_Eta.at(0), weight);
										SelectedJets_PhiGEN_mumu_N0_1_->Fill(SelectedJetsGEN_Phi.at(0), weight);
								
										SelectedJetsGEN_HT_mumu_N0_->Fill(SelectedJetsGEN_HT, weight);
									}

									if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -121){

										nLeptonsGEN_ee_N0_->Fill(nLeptonsGEN, weight);
										
										lepPtGEN_ee_N0_1_->Fill(lepPtGEN->at(0), weight);
										lepEGEN_ee_N0_1_->Fill(lepEGEN->at(0), weight);
										lepEtaGEN_ee_N0_1_->Fill(lepEtaGEN->at(0), weight);
										lepPhiGEN_ee_N0_1_->Fill(lepPhiGEN->at(0), weight);

										lepPtGEN_ee_N0_2_->Fill(lepPtGEN->at(1), weight);
										lepEGEN_ee_N0_2_->Fill(lepEGEN->at(1), weight);
										lepEtaGEN_ee_N0_2_->Fill(lepEtaGEN->at(1), weight);
										lepPhiGEN_ee_N0_2_->Fill(lepPhiGEN->at(1), weight);

										llMGEN_ee_N0_->Fill(llMGEN, weight);
										llPtGEN_ee_N0_->Fill(llPtGEN, weight);
										llEtaGEN_ee_N0_->Fill(llEtaGEN, weight);
										llPhiGEN_ee_N0_->Fill(llPhiGEN, weight);

										SelectedJetsGEN_N_ee_N0_->Fill(SelectedJetsGEN_N, weight);
	
										SelectedJets_PtGEN_ee_N0_1_->Fill(SelectedJetsGEN_Pt.at(0), weight);
										SelectedJets_EGEN_ee_N0_1_->Fill(SelectedJetsGEN_E.at(0), weight);
										SelectedJets_EtaGEN_ee_N0_1_->Fill(SelectedJetsGEN_Eta.at(0), weight);
										SelectedJets_PhiGEN_ee_N0_1_->Fill(SelectedJetsGEN_Phi.at(0), weight);
								
										SelectedJetsGEN_HT_ee_N0_->Fill(SelectedJetsGEN_HT, weight);
									}

									nLeptonsGEN_ll_N0_->Fill(nLeptonsGEN, weight);

									lepPtGEN_ll_N0_1_->Fill(lepPtGEN->at(0), weight);
									lepEGEN_ll_N0_1_->Fill(lepEGEN->at(0), weight);
									lepEtaGEN_ll_N0_1_->Fill(lepEtaGEN->at(0), weight);
									lepPhiGEN_ll_N0_1_->Fill(lepPhiGEN->at(0), weight);

									lepPtGEN_ll_N0_2_->Fill(lepPtGEN->at(1), weight);
									lepEGEN_ll_N0_2_->Fill(lepEGEN->at(1), weight);
									lepEtaGEN_ll_N0_2_->Fill(lepEtaGEN->at(1), weight);
									lepPhiGEN_ll_N0_2_->Fill(lepPhiGEN->at(1), weight);

									llMGEN_ll_N0_->Fill(llMGEN, weight);									
									llPtGEN_ll_N0_->Fill(llPtGEN, weight);
									llEtaGEN_ll_N0_->Fill(llEtaGEN, weight);
									llPhiGEN_ll_N0_->Fill(llPhiGEN, weight);

									SelectedJetsGEN_N_ll_N0_->Fill(SelectedJetsGEN_N, weight);

									SelectedJets_PtGEN_ll_N0_1_->Fill(SelectedJetsGEN_Pt.at(0), weight);
									SelectedJets_EGEN_ll_N0_1_->Fill(SelectedJetsGEN_E.at(0), weight);
									SelectedJets_EtaGEN_ll_N0_1_->Fill(SelectedJetsGEN_Eta.at(0), weight);
									SelectedJets_PhiGEN_ll_N0_1_->Fill(SelectedJetsGEN_Phi.at(0), weight);
								
									SelectedJetsGEN_HT_ll_N0_->Fill(SelectedJetsGEN_HT, weight);

									if (SelectedJetsGEN_N == 1){
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -169){
											llPtGEN_mumu_excl1_->Fill(llPtGEN, weight);
										}		
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -121){
											llPtGEN_ee_excl1_->Fill(llPtGEN, weight);
										}		
										llPtGEN_ll_excl1_->Fill(llPtGEN, weight);
									}

									if (SelectedJetsGEN_N == 2){
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -169){
											llPtGEN_mumu_excl2_->Fill(llPtGEN, weight);
										}		
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -121){
											llPtGEN_ee_excl2_->Fill(llPtGEN, weight);
										}		
										llPtGEN_ll_excl2_->Fill(llPtGEN, weight);
									}

									if (SelectedJetsGEN_N > 1){
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -169){
											llPtGEN_mumu_N1_->Fill(llPtGEN, weight);
										}		
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -121){
											llPtGEN_ee_N1_->Fill(llPtGEN, weight);
										}		
										llPtGEN_ll_N1_->Fill(llPtGEN, weight);
									}

									if (SelectedJetsGEN_N > 2){
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -169){
											llPtGEN_mumu_N2_->Fill(llPtGEN, weight);
										}		
										if (lepChIdGEN->at(0)*lepChIdGEN->at(1) == -121){
											llPtGEN_ee_N2_->Fill(llPtGEN, weight);
										}		
										llPtGEN_ll_N2_->Fill(llPtGEN, weight);
									}
								} // end HTGEN selection
							} // end kin JetsGEN (cleaned vs. 2 leptonGEN) selection
						} // end llM kinematic selection
					} // end leptonGEN kinematic selection
				} // end double muon or double electron selection
			} // end leptonGEN selection

			HTParSum_->Fill(HTParSum, weight);

			// clean jets GEN
			SelectedJetsGEN_N = 0;
			SelectedJetsGEN_HT = 0;
			
			SelectedJetsGEN_Pt.clear();
			SelectedJetsGEN_E.clear();
			SelectedJetsGEN_Eta.clear();
			SelectedJetsGEN_Phi.clear();
			// end clean jets GEN
		} // end GEN selection			 

	} // end loop on entries

	// ====================================terminate and plot

	fhistos->Write();

	if (plothistos){
		Plot_Histos();
	}
	if (textfile){
		Text_File();
	}
}


// ----- methods ----------------

void ZJetsAnalyzer::Book_Histos(){

	cout << "Booking histograms... " << endl;
	// book the histograms
	if(isMC){

		//plotsCompare_gen_01
		nLeptonsGEN_mumu_N0_ = new TH1F("nLeptonsGEN_mumu_N0_","Leptons GEN N (Z->#mu#mu)", 50, 0, 50);

		lepPtGEN_mumu_N0_1_ = new TH1F("lepPtGEN_mumu_N0_1_", "lepton 1 GEN p_{T} (Z->#mu#mu)", 800, 0., 4000.);
		lepEGEN_mumu_N0_1_ = new TH1F("lepEGEN_mumu_N0_1_", "lepton 1 GEN E (Z->#mu#mu)", 800, 0., 4000.);
		lepEtaGEN_mumu_N0_1_ = new TH1F("lepEtaGEN_mumu_N0_1_", "lepton 1 GEN #eta (Z->#mu#mu)", 3000, -3, 3);
		lepPhiGEN_mumu_N0_1_ = new TH1F("lepPhiGEN_mumu_N0_1_", "lepton 1 GEN #phi (Z->#mu#mu)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_02
		lepPtGEN_mumu_N0_2_ = new TH1F("lepPtGEN_mumu_N0_2_", "lepton 2 GEN p_{T} (Z->#mu#mu)", 800, 0., 4000.);
		lepEGEN_mumu_N0_2_ = new TH1F("lepEGEN_mumu_N0_2_", "lepton 2 GEN E (Z->#mu#mu)", 800, 0., 4000.);
		lepEtaGEN_mumu_N0_2_ = new TH1F("lepEtaGEN_mumu_N0_2_", "lepton 2 GEN #eta (Z->#mu#mu)", 3000, -3, 3);
		lepPhiGEN_mumu_N0_2_ = new TH1F("lepPhiGEN_mumu_N0_2_", "lepton 2 GEN #phi (Z->#mu#mu)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_03
		llMGEN_mumu_N0_ = new TH1F("llMGEN_mumu_N0_", "M^{ll} GEN (Z->#mu#mu)", 600, 60., 120.);
		llPtGEN_mumu_N0_ = new TH1F("llPtGEN_mumu_N0_", "p_{T}^{ll} GEN (Z->#mu#mu)", 800, 0., 4000.);
		llEtaGEN_mumu_N0_ = new TH1F("llEtaGEN_mumu_N0_", "#eta^{ll} GEN (Z->#mu#mu)", 3000, -3, 3);
		llPhiGEN_mumu_N0_ = new TH1F("llPhiGEN_mumu_N0_", "#phi^{ll} GEN (Z->#mu#mu)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_04
		SelectedJetsGEN_N_mumu_N0_ = new TH1F("SelectedJetsGEN_N_mumu_N0_","Selected Jets GEN N (Z->#mu#mu)", 10, 0, 10);
		SelectedJets_PtGEN_mumu_N0_1_ = new TH1F("SelectedJets_PtGEN_mumu_N0_1_","Jet 1 GEN p_{T} (Z->#mu#mu)", 800, 0., 4000.);
		SelectedJets_EGEN_mumu_N0_1_ = new TH1F("SelectedJets_EGEN_mumu_N0_1_", "Jet 1 GEN E (Z->#mu#mu)", 800, 0., 4000.);
		SelectedJets_EtaGEN_mumu_N0_1_ = new TH1F("SelectedJets_EtaGEN_mumu_N0_1_","Jet 1 GEN #eta (Z->#mu#mu)", 3000, -3, 3);
		SelectedJets_PhiGEN_mumu_N0_1_ = new TH1F("SelectedJets_PhiGEN_mumu_N0_1_","Jet 1 GEN #varphi (Z->#mu#mu)", 1000, -3.1416, 3.1416);

		SelectedJetsGEN_HT_mumu_N0_ = new TH1F("SelectedJetsGEN_HT_mumu_N0_","Selected Jets H_{T} GEN (Z->#mu#mu)", 400, 0, 4000);
		
		//plotsCompare_gen_05
		nLeptonsGEN_ee_N0_ = new TH1F("nLeptonsGEN_ee_N0_","Leptons GEN N (Z->ee)", 50, 0, 50);

		lepPtGEN_ee_N0_1_ = new TH1F("lepPtGEN_ee_N0_1_", "lepton 1 GEN p_{T} (Z->ee)", 800, 0., 4000.);
		lepEGEN_ee_N0_1_ = new TH1F("lepEGEN_ee_N0_1_", "lepton 1 GEN E (Z->ee)", 800, 0., 4000.);
		lepEtaGEN_ee_N0_1_ = new TH1F("lepEtaGEN_ee_N0_1_", "lepton 1 GEN #eta (Z->ee)", 3000, -3, 3);
		lepPhiGEN_ee_N0_1_ = new TH1F("lepPhiGEN_ee_N0_1_", "lepton 1 GEN #phi (Z->ee)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_06
		lepPtGEN_ee_N0_2_ = new TH1F("lepPtGEN_ee_N0_2_", "lepton 2 GEN p_{T} (Z->ee)", 800, 0., 4000.);
		lepEGEN_ee_N0_2_ = new TH1F("lepEGEN_ee_N0_2_", "lepton 2 GEN E (Z->ee)", 800, 0., 4000.);
		lepEtaGEN_ee_N0_2_ = new TH1F("lepEtaGEN_ee_N0_2_", "lepton 2 GEN #eta (Z->ee)", 3000, -3, 3);
		lepPhiGEN_ee_N0_2_ = new TH1F("lepPhiGEN_ee_N0_2_", "lepton 2 GEN #phi (Z->ee)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_07
		llMGEN_ee_N0_ = new TH1F("llMGEN_ee_N0_", "M^{ll} GEN (Z->ee)", 600, 60., 120.);
		llPtGEN_ee_N0_ = new TH1F("llPtGEN_ee_N0_", "p_{T}^{ll} GEN (Z->ee)", 800, 0., 4000.);
		llEtaGEN_ee_N0_ = new TH1F("llEtaGEN_ee_N0_", "#eta^{ll} GEN (Z->ee)", 3000, -3, 3);
		llPhiGEN_ee_N0_ = new TH1F("llPhiGEN_ee_N0_", "#phi^{ll} GEN (Z->ee)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_08
		SelectedJetsGEN_N_ee_N0_ = new TH1F("SelectedJetsGEN_N_ee_N0_","Selected Jets GEN N (Z->ee)", 10, 0, 10);
		SelectedJets_PtGEN_ee_N0_1_ = new TH1F("SelectedJets_PtGEN_ee_N0_1_","Jet 1 GEN p_{T} (Z->ee)", 800, 0., 4000.);
		SelectedJets_EGEN_ee_N0_1_ = new TH1F("SelectedJets_EGEN_ee_N0_1_", "Jet 1 GEN E (Z->ee)", 800, 0., 4000.);
		SelectedJets_EtaGEN_ee_N0_1_ = new TH1F("SelectedJets_EtaGEN_ee_N0_1_","Jet 1 GEN #eta (Z->ee)", 3000, -3, 3);
		SelectedJets_PhiGEN_ee_N0_1_ = new TH1F("SelectedJets_PhiGEN_ee_N0_1_","Jet 1 GEN #varphi (Z->ee)", 1000, -3.1416, 3.1416);

		SelectedJetsGEN_HT_ee_N0_ = new TH1F("SelectedJetsGEN_HT_ee_N0_","Selected Jets H_{T} GEN (Z->ee)", 400, 0, 4000);

		//plotsCompare_gen_09
		nLeptonsGEN_ll_N0_ = new TH1F("nLeptonsGEN_ll_N0_","Leptons GEN N (Z->ll)", 50, 0, 50);

		lepPtGEN_ll_N0_1_ = new TH1F("lepPtGEN_ll_N0_1_", "lepton 1 GEN p_{T} (Z->ll)", 800, 0., 4000.);
		lepEGEN_ll_N0_1_ = new TH1F("lepEGEN_ll_N0_1_", "lepton 1 GEN E (Z->ll)", 800, 0., 4000.);
		lepEtaGEN_ll_N0_1_ = new TH1F("lepEtaGEN_ll_N0_1_", "lepton 1 GEN #eta (Z->ll)", 3000, -3, 3);
		lepPhiGEN_ll_N0_1_ = new TH1F("lepPhiGEN_ll_N0_1_", "lepton 1 GEN #phi (Z->ll)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_10
		lepPtGEN_ll_N0_2_ = new TH1F("lepPtGEN_ll_N0_2_", "lepton 2 GEN p_{T} (Z->ll)", 800, 0., 4000.);
		lepEGEN_ll_N0_2_ = new TH1F("lepEGEN_ll_N0_2_", "lepton 2 GEN E (Z->ll)", 800, 0., 4000.);
		lepEtaGEN_ll_N0_2_ = new TH1F("lepEtaGEN_ll_N0_2_", "lepton 2 GEN #eta (Z->ll)", 3000, -3, 3);
		lepPhiGEN_ll_N0_2_ = new TH1F("lepPhiGEN_ll_N0_2_", "lepton 2 GEN #phi (Z->ll)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_11
		llMGEN_ll_N0_ = new TH1F("llMGEN_ll_N0_", "M^{ll} GEN (Z->ll)", 600, 60., 120.);
		llPtGEN_ll_N0_ = new TH1F("llPtGEN_ll_N0_", "p_{T}^{ll} GEN (Z->ll)", 800, 0., 4000.);
		llEtaGEN_ll_N0_ = new TH1F("llEtaGEN_ll_N0_", "#eta^{ll} GEN (Z->ll)", 3000, -3, 3);
		llPhiGEN_ll_N0_ = new TH1F("llPhiGEN_ll_N0_", "#phi^{ll} GEN (Z->ll)", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_12
		SelectedJetsGEN_N_ll_N0_ = new TH1F("SelectedJetsGEN_N_ll_N0_","Selected Jets GEN N (Z->ll)", 10, 0, 10);
		SelectedJets_PtGEN_ll_N0_1_ = new TH1F("SelectedJets_PtGEN_ll_N0_1_","Jet 1 GEN p_{T} (Z->ll)", 800, 0., 4000.);
		SelectedJets_EGEN_ll_N0_1_ = new TH1F("SelectedJets_EGEN_ll_N0_1_", "Jet 1 GEN E (Z->ll)", 800, 0., 4000.);
		SelectedJets_EtaGEN_ll_N0_1_ = new TH1F("SelectedJets_EtaGEN_ll_N0_1_","Jet 1 GEN #eta (Z->ll)", 3000, -3, 3);
		SelectedJets_PhiGEN_ll_N0_1_ = new TH1F("SelectedJets_PhiGEN_ll_N0_1_","Jet 1 GEN #varphi (Z->ll)", 1000, -3.1416, 3.1416);

		SelectedJetsGEN_HT_ll_N0_ = new TH1F("SelectedJetsGEN_HT_ll_N0_","Selected Jets H_{T} GEN (Z->ll)", 400, 0, 4000);

		//plotsCompare_gen_13
		HTParSum_ = new TH1F("HTParSum_","H_{T} Partons Sum", 400, 0, 4000);

		//plotsCompare_gen_14
		llPtGEN_mumu_excl1_ = new TH1F("llPtGEN_mumu_excl1_", "p_{T}^{ll} GEN (Z->#mu#mu), N^{jets}_{GEN} = 1", 800, 0., 4000.);
		llPtGEN_ee_excl1_ = new TH1F("llPtGEN_ee_excl1_", "p_{T}^{ll} GEN (Z->ee), N^{jets}_{GEN} = 1", 800, 0., 4000.);
		llPtGEN_ll_excl1_ = new TH1F("llPtGEN_ll_excl1_", "p_{T}^{ll} GEN (Z->ll), N^{jets}_{GEN} = 1", 800, 0., 4000.);

		//plotsCompare_gen_15
		llPtGEN_mumu_excl2_ = new TH1F("llPtGEN_mumu_excl2_", "p_{T}^{ll} GEN (Z->#mu#mu), N^{jets}_{GEN} = 2", 800, 0., 4000.);
		llPtGEN_ee_excl2_ = new TH1F("llPtGEN_ee_excl2_", "p_{T}^{ll} GEN (Z->ee), N^{jets}_{GEN} = 2", 800, 0., 4000.);
		llPtGEN_ll_excl2_ = new TH1F("llPtGEN_ll_excl2_", "p_{T}^{ll} GEN (Z->ll), N^{jets}_{GEN} = 2", 800, 0., 4000.);

		//plotsCompare_gen_16
		llPtGEN_mumu_N1_ = new TH1F("llPtGEN_mumu_N1_", "p_{T}^{ll} GEN (Z->#mu#mu), N^{jets}_{GEN} > 1", 800, 0., 4000.);
		llPtGEN_ee_N1_ = new TH1F("llPtGEN_ee_N1_", "p_{T}^{ll} GEN (Z->ee), N^{jets}_{GEN} > 1", 800, 0., 4000.);
		llPtGEN_ll_N1_ = new TH1F("llPtGEN_ll_N1_", "p_{T}^{ll} GEN (Z->ll), N^{jets}_{GEN} > 1", 800, 0., 4000.);

		//plotsCompare_gen_17
		llPtGEN_mumu_N2_ = new TH1F("llPtGEN_mumu_N2_", "p_{T}^{ll} GEN (Z->#mu#mu), N^{jets}_{GEN} > 2", 800, 0., 4000.);
		llPtGEN_ee_N2_ = new TH1F("llPtGEN_ee_N2_", "p_{T}^{ll} GEN (Z->ee), N^{jets}_{GEN} > 2", 800, 0., 4000.);
		llPtGEN_ll_N2_ = new TH1F("llPtGEN_ll_N2_", "p_{T}^{ll} GEN (Z->ll), N^{jets}_{GEN} > 2", 800, 0., 4000.);
	}


	cout << "...booking histograms finished." << endl;
}


void ZJetsAnalyzer::Plot_Histos(){

	// plot few histograms at the end, for check
	cout << "Plots: quick check... " << endl;

	bool plot_gen_01 = true; // GEN lepton 1 kinematics (Z->#mu#mu)
	bool plot_gen_02 = true; // GEN lepton 2 kinematics (Z->#mu#mu)
	bool plot_gen_03 = true; // GEN ll kinematics (Z->#mu#mu)
	bool plot_gen_04 = true; // GEN jets variables (Z->#mu#mu)
	bool plot_gen_05 = true; // GEN lepton 1 kinematics (Z->ee)
	bool plot_gen_06 = true; // GEN lepton 2 kinematics (Z->ee)
	bool plot_gen_07 = true; // GEN ll kinematics (Z->ee)
	bool plot_gen_08 = true; // GEN jets variables (Z->ee)
	bool plot_gen_09 = true; // GEN lepton 1 kinematics (Z->ll)
	bool plot_gen_10 = true; // GEN lepton 2 kinematics (Z->ll)
	bool plot_gen_11 = true; // GEN ll kinematics (Z->ll)
	bool plot_gen_12 = true; // GEN jets variables (Z->ll)
	bool plot_gen_13 = true; // GEN HTParSum
	bool plot_gen_14 = true; // GEN ll kinematics (N GEN jets = 1)
	bool plot_gen_15 = true; // GEN ll kinematics (N GEN jets = 2)
	bool plot_gen_16 = true; // GEN ll kinematics (N GEN jets > 1)
	bool plot_gen_17 = true; // GEN ll kinematics (N GEN jets > 2)
	 		
	gStyle->SetOptStat(1111111);

	if(plot_gen_01){
		TCanvas *c_gen01 = new TCanvas("c_gen01", "GEN lepton 1 kinematics (Z->mumu)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen01->Divide(3,2);
		c_gen01->cd(1);
		nLeptonsGEN_mumu_N0_->Draw();
		c_gen01->cd(2);
		lepPtGEN_mumu_N0_1_->Draw();
		c_gen01->cd(3);
		lepEGEN_mumu_N0_1_->Draw();
		c_gen01->cd(4);
		lepEtaGEN_mumu_N0_1_->Draw();
		c_gen01->cd(5);
		lepPhiGEN_mumu_N0_1_->Draw();
		c_gen01->cd(6);
	}

	if(plot_gen_02){
		TCanvas *c_gen02 = new TCanvas("c_gen02", "GEN lepton 2 kinematics (Z->mumu)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen02->Divide(3,2);
		c_gen02->cd(1);
		c_gen02->cd(2);
		lepPtGEN_mumu_N0_2_->Draw();
		c_gen02->cd(3);
		lepEGEN_mumu_N0_2_->Draw();
		c_gen02->cd(4);
		lepEtaGEN_mumu_N0_2_->Draw();
		c_gen02->cd(5);
		lepPhiGEN_mumu_N0_2_->Draw();
		c_gen02->cd(6);
	}

	if(plot_gen_03){
		TCanvas *c_gen03 = new TCanvas("c_gen03", "GEN ll kinematics (Z->mumu)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen03->Divide(2,2);
		c_gen03->cd(1);
		llMGEN_mumu_N0_->Draw();
		c_gen03->cd(2);
		llPtGEN_mumu_N0_->Draw();
		c_gen03->cd(3);
		llEtaGEN_mumu_N0_->Draw();
		c_gen03->cd(4);
		llPhiGEN_mumu_N0_->Draw();
	}

	if(plot_gen_04){
		TCanvas *c_gen04 = new TCanvas("c_gen02", "GEN jets variables (Z->mumu)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen04->Divide(3,2);
		c_gen04->cd(1);
		SelectedJetsGEN_N_mumu_N0_->Draw();
		c_gen04->cd(2);
		SelectedJets_PtGEN_mumu_N0_1_->Draw();
		c_gen04->cd(3);
		SelectedJets_EGEN_mumu_N0_1_->Draw();
		c_gen04->cd(4);
		SelectedJets_EtaGEN_mumu_N0_1_->Draw();
		c_gen04->cd(5);
		SelectedJets_PhiGEN_mumu_N0_1_->Draw();
		c_gen04->cd(6);
		SelectedJetsGEN_HT_mumu_N0_->Draw();
	}

	if(plot_gen_05){
		TCanvas *c_gen05 = new TCanvas("c_gen05", "GEN lepton 1 kinematics (Z->ee)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen05->Divide(3,2);
		c_gen05->cd(1);
		nLeptonsGEN_ee_N0_->Draw();
		c_gen05->cd(2);
		lepPtGEN_ee_N0_1_->Draw();
		c_gen05->cd(3);
		lepEGEN_ee_N0_1_->Draw();
		c_gen05->cd(4);
		lepEtaGEN_ee_N0_1_->Draw();
		c_gen05->cd(5);
		lepPhiGEN_ee_N0_1_->Draw();
		c_gen05->cd(6);
	}

	if(plot_gen_06){
		TCanvas *c_gen06 = new TCanvas("c_gen06", "GEN lepton 2 kinematics (Z->ee)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen06->Divide(3,2);
		c_gen06->cd(1);
		c_gen06->cd(2);
		lepPtGEN_ee_N0_2_->Draw();
		c_gen06->cd(3);
		lepEGEN_ee_N0_2_->Draw();
		c_gen06->cd(4);
		lepEtaGEN_ee_N0_2_->Draw();
		c_gen06->cd(5);
		lepPhiGEN_ee_N0_2_->Draw();
		c_gen06->cd(6);
	}

	if(plot_gen_07){
		TCanvas *c_gen07 = new TCanvas("c_gen07", "GEN ll kinematics (Z->ee)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen07->Divide(2,2);
		c_gen07->cd(1);
		llMGEN_ee_N0_->Draw();
		c_gen07->cd(2);
		llPtGEN_ee_N0_->Draw();
		c_gen07->cd(3);
		llEtaGEN_ee_N0_->Draw();
		c_gen07->cd(4);
		llPhiGEN_ee_N0_->Draw();
	}

	if(plot_gen_08){
		TCanvas *c_gen08 = new TCanvas("c_gen08", "GEN jets variables (Z->ee)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen08->Divide(3,2);
		c_gen08->cd(1);
		SelectedJetsGEN_N_ee_N0_->Draw();
		c_gen08->cd(2);
		SelectedJets_PtGEN_ee_N0_1_->Draw();
		c_gen08->cd(3);
		SelectedJets_EGEN_ee_N0_1_->Draw();
		c_gen08->cd(4);
		SelectedJets_EtaGEN_ee_N0_1_->Draw();
		c_gen08->cd(5);
		SelectedJets_PhiGEN_ee_N0_1_->Draw();
		c_gen08->cd(6);
		SelectedJetsGEN_HT_ee_N0_->Draw();
	}

	if(plot_gen_09){
		TCanvas *c_gen09 = new TCanvas("c_gen09", "GEN lepton 1 kinematics (Z->ll)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen09->Divide(3,2);
		c_gen09->cd(1);
		nLeptonsGEN_ll_N0_->Draw();
		c_gen09->cd(2);
		lepPtGEN_ll_N0_1_->Draw();
		c_gen09->cd(3);
		lepEGEN_ll_N0_1_->Draw();
		c_gen09->cd(4);
		lepEtaGEN_ll_N0_1_->Draw();
		c_gen09->cd(5);
		lepPhiGEN_ll_N0_1_->Draw();
		c_gen09->cd(6);
	}

	if(plot_gen_10){
		TCanvas *c_gen10 = new TCanvas("c_gen10", "GEN lepton 2 kinematics (Z->ll)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen10->Divide(3,2);
		c_gen10->cd(1);
		c_gen10->cd(2);
		lepPtGEN_ll_N0_2_->Draw();
		c_gen10->cd(3);
		lepEGEN_ll_N0_2_->Draw();
		c_gen10->cd(4);
		lepEtaGEN_ll_N0_2_->Draw();
		c_gen10->cd(5);
		lepPhiGEN_ll_N0_2_->Draw();
		c_gen10->cd(6);
	}

	if(plot_gen_11){
		TCanvas *c_gen11 = new TCanvas("c_gen11", "GEN ll kinematics (Z->ll)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen11->Divide(2,2);
		c_gen11->cd(1);
		llMGEN_ll_N0_->Draw();
		c_gen11->cd(2);
		llPtGEN_ll_N0_->Draw();
		c_gen11->cd(3);
		llEtaGEN_ll_N0_->Draw();
		c_gen11->cd(4);
		llPhiGEN_ll_N0_->Draw();
	}

	if(plot_gen_12){
		TCanvas *c_gen12 = new TCanvas("c_gen12", "GEN jets variables (Z->ll)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen12->Divide(3,2);
		c_gen12->cd(1);
		SelectedJetsGEN_N_ll_N0_->Draw();
		c_gen12->cd(2);
		SelectedJets_PtGEN_ll_N0_1_->Draw();
		c_gen12->cd(3);
		SelectedJets_EGEN_ll_N0_1_->Draw();
		c_gen12->cd(4);
		SelectedJets_EtaGEN_ll_N0_1_->Draw();
		c_gen12->cd(5);
		SelectedJets_PhiGEN_ll_N0_1_->Draw();
		c_gen12->cd(6);
		SelectedJetsGEN_HT_ll_N0_->Draw();
	}

	if(plot_gen_13){
		TCanvas *c_gen13 = new TCanvas("c_gen13", "GEN HTParSum", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen13->Divide(1,1);
		c_gen13->cd(1);
		HTParSum_->Draw();
	}

	if(plot_gen_14){
		TCanvas *c_gen14 = new TCanvas("c_gen14", "GEN ll kinematics (N GEN jets = 1)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen14->Divide(3,1);
		c_gen14->cd(1);
		llPtGEN_mumu_excl1_->Draw();
		c_gen14->cd(2);
		llPtGEN_ee_excl1_->Draw();
		c_gen14->cd(3);
		llPtGEN_ll_excl1_->Draw();
	}

	if(plot_gen_15){
		TCanvas *c_gen15 = new TCanvas("c_gen15", "GEN ll kinematics (N GEN jets = 2)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen15->Divide(3,1);
		c_gen15->cd(1);
		llPtGEN_mumu_excl2_->Draw();
		c_gen15->cd(2);
		llPtGEN_ee_excl2_->Draw();
		c_gen15->cd(3);
		llPtGEN_ll_excl2_->Draw();
	}

	if(plot_gen_16){
		TCanvas *c_gen16 = new TCanvas("c_gen16", "GEN ll kinematics (N GEN jets > 1)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen16->Divide(3,1);
		c_gen16->cd(1);
		llPtGEN_mumu_N1_->Draw();
		c_gen16->cd(2);
		llPtGEN_ee_N1_->Draw();
		c_gen16->cd(3);
		llPtGEN_ll_N1_->Draw();
	}

	if(plot_gen_17){
		TCanvas *c_gen17 = new TCanvas("c_gen17", "GEN ll kinematics (N GEN jets > 2)", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen17->Divide(3,1);
		c_gen17->cd(1);
		llPtGEN_mumu_N2_->Draw();
		c_gen17->cd(2);
		llPtGEN_ee_N2_->Draw();
		c_gen17->cd(3);
		llPtGEN_ll_N2_->Draw();
	}


	cout << "...plots: quick check finished. " << endl;

	}


float deltaEta(float eta1, float eta2) { 

	float result = eta1 - eta2;
	float absresult = TMath::Abs(result);
	return absresult;
}

void Zero_Variables(){
}


void ZJetsAnalyzer::Text_File(){

	cout << "Writing text file... " << endl;
	ofstream text;
	text.open(textname);
	text.close();
	cout << "...writing text file finished. " << endl;
	}
	
	
void TotalAnalysis_DYJetsToLL_M_50(){

	// MC signal DYJetsToLL_M_50 ---------------------------------------------

	ZJetsAnalyzer MC_DYJetsToLL_M_50(0,91);
	MC_DYJetsToLL_M_50.Loop();
}	
