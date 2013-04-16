#define GJetsAnalyzer_cxx
#include "GJetsAnalyzer.h"
#include "GJetsDefs.h"
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
#include <Riostream.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>
#include <DataFormats/Math/interface/deltaPhi.h>
#include <DataFormats/Math/interface/deltaR.h>
#include <TLorentzVector.h>
#include <../../../QCDAnalysis/Tools/interface/EventShapeLorentz.h>

//#ifdef __MAKECINT__
//#pragma link C++ class vector<float>+;
//#endif

//		In a ROOT session, you can do:
//			Root > .L GJetsAnalyzer.C+
//			Root > GJetsAnalyzer t;
//			Root > t.GetEntry(12);	// Fill t data members with entry number 12
//			Root > t.Show();				// Show values of entry 12
//			Root > t.Show(16);			// Read and show values of entry 16
//			Root > t.Loop();				// Loop on all entries
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


void GJetsAnalyzer::Loop(){

	bool RedAn = false; // analysis with a reuced entries number
	string geo = "barrel"; // barrel or endcaps
	Int_t plothistos = 0; // please select which plots to show
	Int_t textfile = 1; // if you want a text report for each sample
	Int_t itype = 8; // it identifies histos with different analysis 

	// choose the sample:
	// -----------------------------------------------------
	// mysample == 0   -> Test
	// -----------------------------------------------------
	// mysample == 1   -> DATA Run2012A-13Jul2012
	// mysample == 2   -> DATA Run2012A-recover-06Aug2012
	// mysample == 3   -> DATA Run2012B-13Jul2012
	// mysample == 4   -> DATA Run2012C-24Aug2012
	// mysample == 5   -> DATA Run2012C-EcalRecover_11Dec2012
	// mysample == 6   -> DATA Run2012C-PromptReco
	// mysample == 7   -> DATA Run2012D-PromptReco
	// -----------------------------------------------------
	// mysample == 11  -> GJets 200<HT<400
	// mysample == 12  -> Gjets 400<HT<Inf
	// -----------------------------------------------------
	// mysample == 21  -> QCD EMEnriched 20<Pt<30
	// mysample == 22  -> QCD EMEnriched 30<Pt<80
	// mysample == 23  -> QCD EMEnriched 80<Pt<170
	// mysample == 24  -> QCD EMEnriched 170<Pt<250
	// mysample == 25  -> QCD EMEnriched 250<Pt<350
	// mysample == 26  -> QCD EMEnriched 350<Pt<Inf
	// -----------------------------------------------------
	// mysample == 31  -> QCD BCtoE 20<Pt<30
	// mysample == 32  -> QCD BCtoE 30<Pt<80
	// mysample == 33  -> QCD BCtoE 80<Pt<170
	// mysample == 34  -> QCD BCtoE 170<Pt<250
	// mysample == 35  -> QCD BCtoE 250<Pt<350
	// mysample == 36  -> QCD BCtoE 350<Pt<Inf
	// -----------------------------------------------------
	// mysample == 41  -> QCD 100<HT<250
	// mysample == 42  -> QCD 250<HT<500
	// mysample == 43  -> QCD 500<HT<1000
	// mysample == 44  -> QCD 1000<HT<inf
	// -----------------------------------------------------

	double Lumi_t = 19027.853; // /pb
	double xsec = 1.;
	double FiltEff = 1.;
	double kFac = 1.;
	double nEvents = 1.;

	Float_t weight = 1; 
	Float_t weight_withPU = 1;

	//since the Z can be also forward if the momenta of the leptons are
	//added up - choose a very big value
	double fCut_eta_central = 150894;

	string geo_s = geo + "/";
	string sample = "";
	string out_files = "output_files/";
	string histos = "_histos_%d_";
	string report = "_report_%d_";
	string root = ".root";
	string txt = ".txt";

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

// data -----------------------------------------------------------------
	else if (mysample == 1) {
		sample = "DATA_Run2012A-13Jul2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 2) {
		sample = "DATA_Run2012A-recover-06Aug2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 3) {
		sample = "DATA_Run2012B-13Jul2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 4) {
		sample = "DATA_Run2012C-24Aug2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 5) {
		sample = "DATA_Run2012C-EcalRecover_11Dec2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 6) {
		sample = "DATA_Run2012C-PromptReco";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 7) {
		sample = "DATA_Run2012D-PromptReco";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

// MC signal GJets_HT-xToy ----------------------------------------------
	else if (mysample == 11){ 
		sample = "MC_GJets_HT-200To400";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 57311030;
//		xsec = 960.5;
		xsec = 1008.03; //da cambiare
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 12){
		sample = "MC_GJets_HT-400ToInf";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 41872600;
//		xsec = 107.5;
		xsec = 105.418; //da cambiare
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

// MC background QCD_Pt_x_y EMEnriched ----------------------------------
	else if (mysample == 21){
		sample = "MC_QCD_Pt_20_30_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 35040695;
//		xsec = 2.886E8;
		xsec = 2.88651E8; //da cambiare
		FiltEff = 0.0101;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 22){
		sample = "MC_QCD_Pt_30_80_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 33088888;
//		xsec = 7.433E7;
		xsec = 7.43031E7; //da cambiare
		FiltEff = 0.0621;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 23){
		sample = "MC_QCD_Pt_80_170_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34542763;
//		xsec = 1191000.0;
		xsec = 1.19391E6; //da cambiare
		FiltEff = 0.1539;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 24){
		sample = "MC_QCD_Pt_170_250_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 31697066;
//		xsec = 30990.0;
		xsec = 30980.0; //da cambiare
		FiltEff = 0.148;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 25){
		sample = "MC_QCD_Pt_250_350_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34611322;
//		xsec = 4250.0;
		xsec = 4245.29; //da cambiare
		FiltEff = 0.131;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 26){
		sample = "MC_QCD_Pt_350_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34080562;
//		xsec = 810.0;
		xsec = 810.454; //da cambiare
		FiltEff = 0.11;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

// MC background QCD_Pt_x_y BCtoE ---------------------------------------
	else if (mysample == 31){
		sample = "MC_QCD_Pt_20_30_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1740229;
		xsec = 2.886E8;
		FiltEff = 5.8E-4;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 32){
		sample = "MC_QCD_Pt_30_80_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1998152 ;
		xsec = 7.424E7;
		FiltEff = 0.00225;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 33){
		sample = "MC_QCD_Pt_80_170_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1945525;
		xsec = 1191000.0;
		FiltEff = 0.0109;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 34){
		sample = "MC_QCD_Pt_170_250_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1948112;
		xsec = 30980.0; 
		FiltEff = 0.0204;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 35){
		sample = "MC_QCD_Pt_250_350_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 2026521 ;
		xsec = 4250.0;
		FiltEff = 0.0243;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 36){
		sample = "MC_QCD_Pt_350_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1948532 ;
		xsec = 811.0;
		FiltEff = 0.0295;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}


// MC background QCD HT-xToy --------------------------------------------
	else if (mysample == 41){
		sample = "MC_QCD_HT-100To250";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 50129518;
//		xsec = 1.036E7;
		xsec = 1.0515E7; //da cambiare
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 42){
		sample = "MC_QCD_HT-250To500";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 27062078;
//		xsec = 276000.0;
		xsec = 276000.0; //da cambiare
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 43){
		sample = "MC_QCD_HT-500To1000";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 30536845;
//		xsec = 8426.0;
		xsec = 8631.07; //da cambiare
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 44){
		sample = "MC_QCD_HT-1000ToInf";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 13843863;
//		xsec = 204.0;
		xsec = 210.585; //da cambiare
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}
	weight_r = weight;
	sample_r = sample;

	if (fChain == 0) return;

	// ================ initialize and book histograms
	TFile *fhistos= new TFile(outputname, "RECREATE");
	Book_Histos();
 
	iSelected0 = 0;
	iSelected1 = 0;
	iSelected2 = 0;
	iSelected3 = 0;
	iSelected4 = 0;

	iSelectedWithWeights0 = 0;
	iSelectedWithWeights1 = 0;
	iSelectedWithWeights2 = 0;
	iSelectedWithWeights3 = 0;
	iSelectedWithWeights4 = 0;
 
	//loop on entries
	Long64_t nentries;
	if(RedAn){
		nentries = 500000; // analysis with a reuced entries number
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

		// ======= weight
		if (isMC && !isTEST) {
			weight_withPU = PUWeight*Lumi_t/1000.; // MC
		}
		else {
			weight_withPU = 1.; // data & Test
		}
		weight_withPU_r = weight_withPU;

		// =========== GEN selection
		// isMC selection
		if (isMC){

			// jetVeto: jetsGEN vs. PhotonGEN 
			if(nPhotonsGEN > 0 && (nJetsGEN > 0 && (nJetsGEN == (int)jetPtGEN->size())) ){

				CleanedJetsGEN_N = 0;
				SelectedJetsGEN_N = 0;

				for (unsigned int iJetGENPos = 0; iJetGENPos < jetPtGEN->size(); iJetGENPos++) {

					// selection of cleaned jets vs. PhotonGEN
					bool closeGEN = false;
					if ( deltaR(photonEtaGEN, photonPhiGEN, jetEtaGEN->at(iJetGENPos), jetPhiGEN->at(iJetGENPos)) < 0.4 ) {
						closeGEN = true;
					}
					if (!closeGEN){
						CleanedJetsGEN_Pt.push_back(jetPtGEN->at(iJetGENPos));
						CleanedJetsGEN_N += 1;

						CleanedJetsGEN_HT = 0;
						for(unsigned int jJetGENPos = 0; jJetGENPos < CleanedJetsGEN_Pt.size(); jJetGENPos++) {
							CleanedJetsGEN_HT += CleanedJetsGEN_Pt.at(jJetGENPos);
						}

						// jets kinematic selection
						if(jetPtGEN->at(iJetGENPos) > 50. && TMath::Abs(jetEtaGEN->at(iJetGENPos)) < 2.5 ){
							SelectedJetsGEN_Pt.push_back(jetPtGEN->at(iJetGENPos));
							SelectedJetsGEN_E.push_back(jetEGEN->at(iJetGENPos));
							SelectedJetsGEN_Eta.push_back(jetEtaGEN->at(iJetGENPos));
							SelectedJetsGEN_Phi.push_back(jetPhiGEN->at(iJetGENPos));
							SelectedJetsGEN_N += 1;
						} // end jets kinematic selection
					} // end selection of cleaned jets vs. PhotonGEN
				}
			} // end jetVeto: jetsGEN vs. PhotonGEN

			// collectives jetsGEN properties - aggiunta inizio
			SelectedJetsGEN_HT = 0;
			for(unsigned int zJetGENPos = 0; zJetGENPos < SelectedJetsGEN_Pt.size(); zJetGENPos++) {
				SelectedJetsGEN_HT += SelectedJetsGEN_Pt.at(zJetGENPos);
			} // end collectives jetsGEN properties - aggiunta fine

			// photonGEN selection
			if (nPhotonsGEN > 0){

				// photonGEN kinematic selection
				bool geo_selGEN = false;
				if (geo == "barrel") {
					geo_selGEN = TMath::Abs(photonEtaGEN) < 1.479;
				}
				else if (geo == "endcaps"){
					geo_selGEN = TMath::Abs(photonEtaGEN) > 1.479 && TMath::Abs(photonEtaGEN) < 3.;
				}
				else {
				cout << "Error: Wrong geometry string writed" << endl;
				}

				if (photonPtGEN > 180. && geo_selGEN) {

					// kin JetsGEN (cleaned vs. photonGEN) selection
					if (SelectedJetsGEN_N > 0){

						// HTGEN selection
						if (SelectedJetsGEN_HT > 250){

							nPhotonsGEN_->Fill(nPhotonsGEN, 1);
							photonPtGEN_->Fill(photonPtGEN, 1);
							photonEtaGEN_->Fill(photonEtaGEN, 1);
							photonPhiGEN_->Fill(photonPhiGEN, 1);
							photonEGEN_->Fill(photonEGEN, 1);

							CleanedJetsGEN_N_->Fill(CleanedJetsGEN_N, 1);
							SelectedJetsGEN_N_->Fill(SelectedJetsGEN_N, 1);

							SelectedJets_PtGEN_1_->Fill(SelectedJetsGEN_Pt.at(0), 1);
							SelectedJets_EGEN_1_->Fill(SelectedJetsGEN_E.at(0), 1);
							SelectedJets_EtaGEN_1_->Fill(SelectedJetsGEN_Eta.at(0), 1);
							SelectedJets_PhiGEN_1_->Fill(SelectedJetsGEN_Phi.at(0), 1);

							CleanedJetsGEN_HT_->Fill(CleanedJetsGEN_HT, 1);
							SelectedJetsGEN_HT_->Fill(SelectedJetsGEN_HT, 1);

							HTParSum_->Fill(HTParSum, 1);

						} // end HTGEN selection
					} // end kin JetsGEN (cleaned vs. photonGEN) selection
				} // end photonGEN kinematic selection
			} // end photonGEN selection

			// clean jets GEN
			CleanedJetsGEN_N = 0;
			SelectedJetsGEN_N = 0;
			CleanedJetsGEN_HT = 0;
			SelectedJetsGEN_HT = 0;

			CleanedJetsGEN_Pt.clear();
			SelectedJetsGEN_Pt.clear();
			SelectedJetsGEN_E.clear();
			SelectedJetsGEN_Eta.clear();
			SelectedJetsGEN_Phi.clear();

		} // end isMC selection

		// =========== REC selection
		// photon selection
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) { 

			IDIsoPhotons_N = 0;
			SelectedPhotons_N = 0;

			// SelectedPhotons collection selection 
			for(unsigned int iPhoPos = 0; iPhoPos < photonPt->size(); iPhoPos++) {

			photonPfIso = 0;
			photonPfIso_ov_Pt = 0;
			photonPfIso = photonPfIsoChargedHad->at(iPhoPos) + photonPfIsoNeutralHad->at(iPhoPos) + photonPfIsoPhoton->at(iPhoPos);
			photonPfIso_ov_Pt = photonPfIso/photonPt->at(iPhoPos);

			photonIsoFPRCharged_ov_Pt = 0;
			photonIsoFPRNeutral_ov_Pt = 0;
			photonIsoFPRPhoton_ov_Pt = 0;
			photonIsoFPRCharged_ov_Pt = photonIsoFPRCharged->at(iPhoPos)/photonPt->at(iPhoPos);
			photonIsoFPRNeutral_ov_Pt = photonIsoFPRNeutral->at(iPhoPos)/photonPt->at(iPhoPos);
			photonIsoFPRPhoton_ov_Pt = photonIsoFPRPhoton->at(iPhoPos)/photonPt->at(iPhoPos);

			bool geo_quality_sel = false;
			if (geo == "barrel") {
				// photon quality selection: Barrel - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
				if(photonPassConversionVeto->at(iPhoPos) == 1){ 
					if(photonid_hadronicOverEm2012->at(iPhoPos) < 0.05){
						if(photonid_sieie->at(iPhoPos) < 0.011){ 
							if(photonPfIsoChargedHad->at(iPhoPos) < 1.5){ 
								if(photonPfIsoNeutralHad->at(iPhoPos) < (1.0 + 0.04*photonPt->at(iPhoPos))){
									if(photonPfIsoPhoton->at(iPhoPos) < (0.7 + 0.005*photonPt->at(iPhoPos))){
										geo_quality_sel = true;
									}
								}
							}
						}
					}
				}
			}
			else if (geo == "endcaps"){
				// photon quality selection: Endcaps - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
				if(photonPassConversionVeto->at(iPhoPos) == 1){ 
					if(photonid_hadronicOverEm2012->at(iPhoPos) < 0.05){
						if(photonid_sieie->at(iPhoPos) < 0.033){ 
							if(photonPfIsoChargedHad->at(iPhoPos) < 1.2){ 
								if(photonPfIsoNeutralHad->at(iPhoPos) < (1.5 + 0.04*photonPt->at(iPhoPos))){
									if(photonPfIsoPhoton->at(iPhoPos) < (1.0 + 0.005*photonPt->at(iPhoPos))){
										geo_quality_sel = true;
									}
								}
							}
						}
					}
				}
			}
			else {
				cout << "Error: Wrong geometry string writed" << endl;
			}

			// photon quality selection
			if(geo_quality_sel){ 

				IDIsoPhotons_N += 1;

				// photon kinematic selection
				bool geo_sel = false;
				if (geo == "barrel") {
					geo_sel = photonBit->at(iPhoPos)&1;
				}
				else if (geo == "endcaps"){
					geo_sel = photonBit->at(iPhoPos)&2;
				}
				else {
				cout << "Error: Wrong geometry string writed" << endl;
				}

				if (photonPt->at(iPhoPos) > 180. && geo_sel) {

					SelectedPhotons_Pt.push_back(photonPt->at(iPhoPos));
					SelectedPhotons_E.push_back(photonE->at(iPhoPos));
					SelectedPhotons_Eta.push_back(photonEta->at(iPhoPos)); 
					SelectedPhotons_Phi.push_back(photonPhi->at(iPhoPos));

					SelectedPhotons_PassConversionVeto.push_back(photonPassConversionVeto->at(iPhoPos));
					SelectedPhotons_PfIsoChargedHad.push_back(photonPfIsoChargedHad->at(iPhoPos)); 
					SelectedPhotons_PfIsoNeutralHad.push_back(photonPfIsoNeutralHad->at(iPhoPos)); 
					SelectedPhotons_PfIsoPhoton.push_back(photonPfIsoPhoton->at(iPhoPos));

					SelectedPhotons_PfIso.push_back(photonPfIso);
					SelectedPhotons_PfIso_ov_Pt.push_back(photonPfIso_ov_Pt);

					SelectedPhotons_PfIsoPhotons03ForCic.push_back(photonPfIsoPhotons03ForCic->at(iPhoPos)); 
					SelectedPhotons_PfIsoNeutrals03ForCic.push_back(photonPfIsoNeutrals03ForCic->at(iPhoPos)); 
					SelectedPhotons_PfIsoCharged03ForCicVtx0.push_back(photonPfIsoCharged03ForCicVtx0->at(iPhoPos)); 
					SelectedPhotons_PfIsoCharged03BadForCic.push_back(photonPfIsoCharged03BadForCic->at(iPhoPos));

					SelectedPhotons_PfIsoPhotons04ForCic.push_back(photonPfIsoPhotons04ForCic->at(iPhoPos)); 
					SelectedPhotons_PfIsoNeutrals04ForCic.push_back(photonPfIsoNeutrals04ForCic->at(iPhoPos));
					SelectedPhotons_PfIsoCharged04ForCicVtx0.push_back(photonPfIsoCharged04ForCicVtx0->at(iPhoPos)); 
					SelectedPhotons_PfIsoCharged04BadForCic.push_back(photonPfIsoCharged04BadForCic->at(iPhoPos));

					SelectedPhotons_id_sieie.push_back(photonid_sieie->at(iPhoPos));
					SelectedPhotons_id_sieip.push_back(photonid_sieip->at(iPhoPos)); 
					SelectedPhotons_id_etawidth.push_back(photonid_etawidth->at(iPhoPos)); 
					SelectedPhotons_id_phiwidth.push_back(photonid_phiwidth->at(iPhoPos)); 
					SelectedPhotons_id_r9.push_back(photonid_r9->at(iPhoPos));

					SelectedPhotons_id_lambdaRatio.push_back(photonid_lambdaRatio->at(iPhoPos)); 
					SelectedPhotons_id_s4Ratio.push_back(photonid_s4Ratio->at(iPhoPos));
					SelectedPhotons_id_e25.push_back(photonid_e25->at(iPhoPos));
					SelectedPhotons_id_sceta.push_back(photonid_sceta->at(iPhoPos));

					SelectedPhotons_id_ESEffSigmaRR.push_back(photonid_ESEffSigmaRR->at(iPhoPos));
					SelectedPhotons_id_hadronicOverEm.push_back(photonid_hadronicOverEm->at(iPhoPos));
					SelectedPhotons_id_hadronicOverEm2012.push_back(photonid_hadronicOverEm2012->at(iPhoPos));

					SelectedPhotons_hcalTowerSumEtConeDR04.push_back(photonhcalTowerSumEtConeDR04->at(iPhoPos));
					SelectedPhotons_ecalRecHitSumEtConeDR04.push_back(photonecalRecHitSumEtConeDR04->at(iPhoPos));
					SelectedPhotons_nTrkSolidConeDR04.push_back(photonnTrkSolidConeDR04->at(iPhoPos));
					SelectedPhotons_trkSumPtSolidConeDR04.push_back(photontrkSumPtSolidConeDR04->at(iPhoPos)); 
					SelectedPhotons_nTrkHollowConeDR04.push_back(photonnTrkHollowConeDR04->at(iPhoPos));
					SelectedPhotons_trkSumPtHollowConeDR04.push_back(photontrkSumPtHollowConeDR04->at(iPhoPos));

					SelectedPhotons_IsoFPRCharged.push_back(photonIsoFPRCharged->at(iPhoPos));
					SelectedPhotons_IsoFPRNeutral.push_back(photonIsoFPRNeutral->at(iPhoPos));
					SelectedPhotons_IsoFPRPhoton.push_back(photonIsoFPRPhoton->at(iPhoPos));
					SelectedPhotons_IsoFPRCharged_ov_Pt.push_back(photonIsoFPRCharged_ov_Pt);
					SelectedPhotons_IsoFPRNeutral_ov_Pt.push_back(photonIsoFPRNeutral_ov_Pt);
					SelectedPhotons_IsoFPRPhoton_ov_Pt.push_back(photonIsoFPRPhoton_ov_Pt);
					SelectedPhotons_Bit.push_back(photonBit->at(iPhoPos));

					SelectedPhotons_N+=1;

					} // end photon kinematic selection
				} // end photon quality selection
			} // end SelectedPhotons collection selection
		} // end photon selection

		// jetVeto: jets vs. SelectedPhotons 
		if(SelectedPhotons_N > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			CleanedJetsLEA_N = 0;
			SelectedJetsLEA_N = 0;
			CleanedJets_N = 0;
			SelectedJets_N = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// only counting of cleaned jets vs. LEADING SelectedPhotons
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.4 ) {
					closeLEA = true;
				}
				if (!closeLEA){
					CleanedJetsLEA_N += 1;
					// only counting of selected jets vs. LEADING SelectedPhotons
					if(jetPt->at(iJetPos) > 50. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){
						SelectedJetsLEA_N += 1;
					}
				} // end only counting of cleaned jets vs. LEADING SelectedPhotons

				// selection of cleaned jets vs. ALL SelectedPhotons
				bool close = false;
				for (unsigned int jPhoPos = 0; jPhoPos < SelectedPhotons_N; ++jPhoPos){
					if ( deltaR(SelectedPhotons_Eta.at(jPhoPos), SelectedPhotons_Phi.at(jPhoPos), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.4) {
						close = true;
						break;
					}
				}
				if (!close){
					CleanedJets_Pt.push_back(jetPt->at(iJetPos));
					CleanedJets_N += 1;

					// jets kinematic selection
					if(jetPt->at(iJetPos) > 50. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){
						SelectedJets_Pt.push_back(jetPt->at(iJetPos));
						SelectedJets_E.push_back(jetE->at(iJetPos));
						SelectedJets_Eta.push_back(jetEta->at(iJetPos));
						SelectedJets_Phi.push_back(jetPhi->at(iJetPos));
						SelectedJets_N += 1;
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. ALL SelectedPhotons
			}
		} // jetVeto: jets vs. SelectedPhotons

		// collectives jets properties - aggiunta inizio
		CleanedJets_HT = 0;
		for(unsigned int jJetPos = 0; jJetPos < CleanedJets_Pt.size(); jJetPos++) {
			CleanedJets_HT += CleanedJets_Pt.at(jJetPos);
		}

		SelectedJets_HT = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt.size(); zJetPos++) {
			SelectedJets_HT += SelectedJets_Pt.at(zJetPos);
			TLorentzVector PtEtaPhiE_tmp = TLorentzVector(0,0,0,0);
			PtEtaPhiE_tmp.SetPtEtaPhiE(SelectedJets_Pt.at(zJetPos), SelectedJets_Eta.at(zJetPos), SelectedJets_Phi.at(zJetPos), SelectedJets_E.at(zJetPos));
			vPtEtaPhiE.push_back(PtEtaPhiE_tmp);
		}
		EventShapeLorentz* myEvshp = new EventShapeLorentz(vPtEtaPhiE, fCut_eta_central ,1);
		myEvshpV = myEvshp->getEventShapes();
		TA = myEvshp->getThrustAxis();
		Grouping = myEvshp->getGrouping();
		Grouping_test = myEvshp->getGrouping_C();
		delete myEvshp;
		// end collectives jets properties - aggiunta fine

		// =========== Analysis selection
		// (photonBit |= (it->isEB() << 0) => (*photonBit)[0]&1) con 2^0 = 1
		iSelected0++;
		iSelectedWithWeights0 = iSelectedWithWeights0 + weight_withPU;

		// ID+Iso+kin Photons selection (then, on the LEADING one)
		if (SelectedPhotons_N > 0){
			iSelected1++;
			iSelectedWithWeights1 = iSelectedWithWeights1 + weight_withPU;

			// trigger Matching selection
			if (isTriggerMatchedFamily4) {
				iSelected2++;
				iSelectedWithWeights2 = iSelectedWithWeights2 + weight_withPU;

				// kin Jets (cleaned vs. Photons) selection
				if (SelectedJets_N > 0) {
					iSelected3++;
					iSelectedWithWeights3 = iSelectedWithWeights3 + weight_withPU;

					CleanedJetsLEA_preHT_N_->Fill(CleanedJetsLEA_N, weight_withPU);
					SelectedJetsLEA_preHT_N_->Fill(SelectedJetsLEA_N, weight_withPU);

					CleanedJets_preHT_N_->Fill(CleanedJets_N, weight_withPU);
					SelectedJets_preHT_N_->Fill(SelectedJets_N, weight_withPU);

					SelectedJets_preHT_Pt_1_->Fill(SelectedJets_Pt.at(0), weight_withPU);
					if (SelectedJets_N > 1){
						SelectedJets_preHT_Pt_2_->Fill(SelectedJets_Pt.at(1), weight_withPU);
					}
					if (SelectedJets_N > 2){
						SelectedJets_preHT_Pt_3_->Fill(SelectedJets_Pt.at(2), weight_withPU);
					}

					CleanedJets_preHT_HT_->Fill(CleanedJets_HT, weight_withPU);
					SelectedJets_preHT_HT_->Fill(SelectedJets_HT, weight_withPU);

					// HT selection
					if (SelectedJets_HT > 250){
						iSelected4++;
						iSelectedWithWeights4 = iSelectedWithWeights4 + weight_withPU;

						Nvtx_->Fill(nVtx, weight_withPU);

						IDIsoPhotons_N_->Fill(IDIsoPhotons_N, weight_withPU);
						SelectedPhotons_N_->Fill(SelectedPhotons_N, weight_withPU);

						SelectedPhotons_Pt_1_->Fill(SelectedPhotons_Pt.at(0), weight_withPU);
						SelectedPhotons_E_1_->Fill(SelectedPhotons_E.at(0), weight_withPU);
						SelectedPhotons_Eta_1_->Fill(SelectedPhotons_Eta.at(0), weight_withPU);
						SelectedPhotons_Phi_1_->Fill(SelectedPhotons_Phi.at(0), weight_withPU);

						SelectedPhotons_PassConversionVeto_1_->Fill(SelectedPhotons_PassConversionVeto.at(0), weight_withPU);
						SelectedPhotons_PfIsoChargedHad_1_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_withPU);
						SelectedPhotons_PfIsoNeutralHad_1_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_withPU);
						SelectedPhotons_PfIsoPhoton_1_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_withPU);

						SelectedPhotons_PfIso_1_->Fill(SelectedPhotons_PfIso.at(0), weight_withPU);
						SelectedPhotons_PfIso_ov_Pt_1_->Fill(SelectedPhotons_PfIso_ov_Pt.at(0), weight_withPU);

						SelectedPhotons_PfIsoPhotons03ForCic_1_->Fill(SelectedPhotons_PfIsoPhotons03ForCic.at(0), weight_withPU);
						SelectedPhotons_PfIsoNeutrals03ForCic_1_->Fill(SelectedPhotons_PfIsoNeutrals03ForCic.at(0), weight_withPU);
						SelectedPhotons_PfIsoCharged03ForCicVtx0_1_->Fill(SelectedPhotons_PfIsoCharged03ForCicVtx0.at(0), weight_withPU);
						SelectedPhotons_PfIsoCharged03BadForCic_1_->Fill(SelectedPhotons_PfIsoCharged03BadForCic.at(0), weight_withPU);

						SelectedPhotons_PfIsoPhotons04ForCic_1_->Fill(SelectedPhotons_PfIsoPhotons04ForCic.at(0), weight_withPU);
						SelectedPhotons_PfIsoNeutrals04ForCic_1_->Fill(SelectedPhotons_PfIsoNeutrals04ForCic.at(0), weight_withPU);
						SelectedPhotons_PfIsoCharged04ForCicVtx0_1_->Fill(SelectedPhotons_PfIsoCharged04ForCicVtx0.at(0), weight_withPU);
						SelectedPhotons_PfIsoCharged04BadForCic_1_->Fill(SelectedPhotons_PfIsoCharged04BadForCic.at(0), weight_withPU);

						SelectedPhotons_id_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), weight_withPU);
						SelectedPhotons_id_sieip_1_->Fill(SelectedPhotons_id_sieip.at(0), weight_withPU);
						SelectedPhotons_id_etawidth_1_->Fill(SelectedPhotons_id_etawidth.at(0), weight_withPU);
						SelectedPhotons_id_phiwidth_1_->Fill(SelectedPhotons_id_phiwidth.at(0), weight_withPU);
						SelectedPhotons_id_r9_1_->Fill(SelectedPhotons_id_r9.at(0), weight_withPU);

						SelectedPhotons_id_lambdaRatio_1_->Fill(SelectedPhotons_id_lambdaRatio.at(0), weight_withPU);
						SelectedPhotons_id_s4Ratio_1_->Fill(SelectedPhotons_id_s4Ratio.at(0), weight_withPU);
						SelectedPhotons_id_e25_1_->Fill(SelectedPhotons_id_e25.at(0), weight_withPU);
						SelectedPhotons_id_sceta_1_->Fill(SelectedPhotons_id_sceta.at(0), weight_withPU);

						SelectedPhotons_id_ESEffSigmaRR_1_->Fill(SelectedPhotons_id_ESEffSigmaRR.at(0), weight_withPU);
						SelectedPhotons_id_hadronicOverEm_1_->Fill(SelectedPhotons_id_hadronicOverEm.at(0), weight_withPU);
						SelectedPhotons_id_hadronicOverEm2012_1_->Fill(SelectedPhotons_id_hadronicOverEm2012.at(0), weight_withPU);

						SelectedPhotons_hcalTowerSumEtConeDR04_1_->Fill(SelectedPhotons_hcalTowerSumEtConeDR04.at(0), weight_withPU);
						SelectedPhotons_ecalRecHitSumEtConeDR04_1_->Fill(SelectedPhotons_ecalRecHitSumEtConeDR04.at(0), weight_withPU);
						SelectedPhotons_nTrkSolidConeDR04_1_->Fill(SelectedPhotons_nTrkSolidConeDR04.at(0), weight_withPU);
						SelectedPhotons_trkSumPtSolidConeDR04_1_->Fill(SelectedPhotons_trkSumPtSolidConeDR04.at(0), weight_withPU);
						SelectedPhotons_nTrkHollowConeDR04_1_->Fill(SelectedPhotons_nTrkHollowConeDR04.at(0), weight_withPU);
						SelectedPhotons_trkSumPtHollowConeDR04_1_->Fill(SelectedPhotons_trkSumPtHollowConeDR04.at(0), weight_withPU);

						SelectedPhotons_IsoFPRCharged_1_->Fill(SelectedPhotons_IsoFPRCharged.at(0), weight_withPU);
						SelectedPhotons_IsoFPRNeutral_1_->Fill(SelectedPhotons_IsoFPRNeutral.at(0), weight_withPU);
						SelectedPhotons_IsoFPRPhoton_1_->Fill(SelectedPhotons_IsoFPRPhoton.at(0), weight_withPU);
						SelectedPhotons_IsoFPRCharged_ov_Pt_1_->Fill(SelectedPhotons_IsoFPRCharged_ov_Pt.at(0), weight_withPU);
						SelectedPhotons_IsoFPRNeutral_ov_Pt_1_->Fill(SelectedPhotons_IsoFPRNeutral_ov_Pt.at(0), weight_withPU);
						SelectedPhotons_IsoFPRPhoton_ov_Pt_1_->Fill(SelectedPhotons_IsoFPRPhoton_ov_Pt.at(0), weight_withPU);
						SelectedPhotons_Bit_1_->Fill(SelectedPhotons_Bit.at(0), weight_withPU);

						CleanedJetsLEA_N_->Fill(CleanedJetsLEA_N, weight_withPU);
						SelectedJetsLEA_N_->Fill(SelectedJetsLEA_N, weight_withPU);

						CleanedJets_N_->Fill(CleanedJets_N, weight_withPU);
						SelectedJets_N_->Fill(SelectedJets_N, weight_withPU);

						SelectedJets_Pt_1_->Fill(SelectedJets_Pt.at(0), weight_withPU);
						SelectedJets_E_1_->Fill(SelectedJets_E.at(0), weight_withPU);
						SelectedJets_Eta_1_->Fill(SelectedJets_Eta.at(0), weight_withPU);
						SelectedJets_Phi_1_->Fill(SelectedJets_Phi.at(0), weight_withPU);

						DeltaR_photon1_jet1 = deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedJets_Eta.at(0), SelectedJets_Phi.at(0));
						DeltaEta_photon1_jet1 = deltaEta(SelectedPhotons_Eta.at(0), SelectedJets_Eta.at(0));
						DeltaPhi_photon1_jet1 = deltaPhi(SelectedPhotons_Phi.at(0), SelectedJets_Phi.at(0));
						
						DeltaR_photon1_jet1_->Fill(DeltaR_photon1_jet1, weight_withPU);
						DeltaEta_photon1_jet1_->Fill(DeltaEta_photon1_jet1, weight_withPU);
						DeltaPhi_photon1_jet1_->Fill(DeltaPhi_photon1_jet1, weight_withPU);

						if (SelectedJets_N > 1){
							SelectedJets_Pt_2_->Fill(SelectedJets_Pt.at(1), weight_withPU);
							SelectedJets_E_2_->Fill(SelectedJets_E.at(1), weight_withPU);
							SelectedJets_Eta_2_->Fill(SelectedJets_Eta.at(1), weight_withPU);
							SelectedJets_Phi_2_->Fill(SelectedJets_Phi.at(1), weight_withPU);

							DeltaR_photon1_jet2 = deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedJets_Eta.at(1), SelectedJets_Phi.at(1));
							DeltaR_jet1_jet2 = deltaR(SelectedJets_Eta.at(0), SelectedJets_Phi.at(0), SelectedJets_Eta.at(1), SelectedJets_Phi.at(1));
							DeltaEta_jet1_jet2 = deltaEta(SelectedJets_Eta.at(0), SelectedJets_Eta.at(1));
							DeltaPhi_jet1_jet2 = deltaPhi(SelectedJets_Phi.at(0), SelectedJets_Phi.at(1));

							DeltaR_photon1_jet2_->Fill(DeltaR_photon1_jet2, weight_withPU);
							DeltaR_jet1_jet2_->Fill(DeltaR_jet1_jet2, weight_withPU);
							DeltaEta_jet1_jet2_->Fill(DeltaEta_jet1_jet2, weight_withPU);
							DeltaPhi_jet1_jet2_->Fill(DeltaPhi_jet1_jet2, weight_withPU);
						}

						if (SelectedJets_N > 2){
							SelectedJets_Pt_3_->Fill(SelectedJets_Pt.at(2), weight_withPU);
							SelectedJets_E_3_->Fill(SelectedJets_E.at(2), weight_withPU);
							SelectedJets_Eta_3_->Fill(SelectedJets_Eta.at(2), weight_withPU);
							SelectedJets_Phi_3_->Fill(SelectedJets_Phi.at(2), weight_withPU);

							DeltaR_photon1_jet3 = deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedJets_Eta.at(2), SelectedJets_Phi.at(2));

							DeltaR_photon1_jet3_->Fill(DeltaR_photon1_jet3, weight_withPU);
						}

						CleanedJets_HT_->Fill(CleanedJets_HT, weight_withPU);
						SelectedJets_HT_->Fill(SelectedJets_HT, weight_withPU);

						phiTA = atan2(TA[1],TA[0]);
						dphi_TA_BAxis = deltaPhi(phiTA, SelectedPhotons_Phi.at(0));
//						if(dphi_TA_BAxis > M_PI/2.0){
//							dphi_TA_BAxis = M_PI-dphi_TA_BAxis;
//						}
						dphi_TA_J1Axis = deltaPhi(phiTA, SelectedJets_Phi.at(0));
//						if(dphi_TA_J1Axis > M_PI/2.0){
//							dphi_TA_J1Axis=M_PI-dphi_TA_J1Axis;
//						}
						if(myEvshpV[2] <= 0){
							myEvshpV[2] = 10e-15;
						}
						thrust = myEvshpV[2];
						broad = myEvshpV[6];
						S3 = myEvshpV[8];
						S4 = myEvshpV[9];

						thrust_->Fill(thrust, weight_withPU);
						broad_->Fill(broad, weight_withPU);
						S3_->Fill(S3, weight_withPU);
						S4_->Fill(S4, weight_withPU);
					} // end HT selection
				} // end trigger Matching selection
			} // end kin Jets (cleaned vs. Photons) selection 
		} // end ID+Iso+kin Photons selection (then, on the LEADING one)

		// clean jets
		CleanedJetsLEA_N = 0;
		SelectedJetsLEA_N = 0;
		CleanedJets_N = 0;
		SelectedJets_N = 0;
		CleanedJets_HT = 0;
		SelectedJets_HT = 0;

		CleanedJets_Pt.clear();

		SelectedJets_Pt.clear();
		SelectedJets_E.clear();
		SelectedJets_Eta.clear();
		SelectedJets_Phi.clear();

		vPtEtaPhiE.clear();

		// clean photons
		IDIsoPhotons_N = 0;
		SelectedPhotons_N = 0;

		SelectedPhotons_Pt.clear();
		SelectedPhotons_E.clear();
		SelectedPhotons_Eta.clear(); 
		SelectedPhotons_Phi.clear();

		SelectedPhotons_PassConversionVeto.clear();
		SelectedPhotons_PfIsoChargedHad.clear(); 
		SelectedPhotons_PfIsoNeutralHad.clear(); 
		SelectedPhotons_PfIsoPhoton.clear();

		SelectedPhotons_PfIso.clear();
		SelectedPhotons_PfIso_ov_Pt.clear();

		SelectedPhotons_PfIsoPhotons03ForCic.clear(); 
		SelectedPhotons_PfIsoNeutrals03ForCic.clear(); 
		SelectedPhotons_PfIsoCharged03ForCicVtx0.clear(); 
		SelectedPhotons_PfIsoCharged03BadForCic.clear();

		SelectedPhotons_PfIsoPhotons04ForCic.clear();
		SelectedPhotons_PfIsoNeutrals04ForCic.clear();
		SelectedPhotons_PfIsoCharged04ForCicVtx0.clear(); 
		SelectedPhotons_PfIsoCharged04BadForCic.clear();

		SelectedPhotons_id_sieie.clear();
		SelectedPhotons_id_sieip.clear(); 
		SelectedPhotons_id_etawidth.clear(); 
		SelectedPhotons_id_phiwidth.clear(); 
		SelectedPhotons_id_r9.clear();

		SelectedPhotons_id_lambdaRatio.clear(); 
		SelectedPhotons_id_s4Ratio.clear();
		SelectedPhotons_id_e25.clear();
		SelectedPhotons_id_sceta.clear();

		SelectedPhotons_id_ESEffSigmaRR.clear();
		SelectedPhotons_id_hadronicOverEm.clear();
		SelectedPhotons_id_hadronicOverEm2012.clear();

		SelectedPhotons_hcalTowerSumEtConeDR04.clear();
		SelectedPhotons_ecalRecHitSumEtConeDR04.clear();
		SelectedPhotons_nTrkSolidConeDR04.clear();
		SelectedPhotons_trkSumPtSolidConeDR04.clear();
		SelectedPhotons_nTrkHollowConeDR04.clear();
		SelectedPhotons_trkSumPtHollowConeDR04.clear();

		SelectedPhotons_IsoFPRCharged.clear();
		SelectedPhotons_IsoFPRNeutral.clear();
		SelectedPhotons_IsoFPRPhoton.clear();
		SelectedPhotons_IsoFPRCharged_ov_Pt.clear();
		SelectedPhotons_IsoFPRNeutral_ov_Pt.clear();
		SelectedPhotons_IsoFPRPhoton_ov_Pt.clear();

		SelectedPhotons_Bit.clear();

		// if (Cut(ientry) < 0) continue;
	} // end loop on entries

	// ====================================terminate and plot

	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	cout << "Number of selected events 0, unweighted = " << iSelected0 << endl;
	cout << "Number of selected events 1, unweighted = " << iSelected1 << endl;
	cout << "Number of selected events 2, unweighted = " << iSelected2 << endl;
	cout << "Number of selected events 3, unweighted = " << iSelected3 << endl;
	cout << "Number of selected events 4, unweighted = " << iSelected4 << endl;
	cout << "Number of selected events, unweighted = " << iSelected4 << endl;
	cout << "Number of selected events, weighted = " << iSelected4*weight_r << endl;
	fhistos->Write();
	if (plothistos == 1){
		Plot_Histos();
	}
	if (textfile == 1){
		Text_File();
	}
}


// ----- methods ----------------

void GJetsAnalyzer::Book_Histos(){

	cout << "Booking histograms... " << endl;
	// book the histograms
	if(isMC){
		nPhotonsGEN_ = new TH1F("nPhotonsGEN_","Photons GEN N", 50, 0, 50);
		photonPtGEN_ = new TH1F("photonPtGEN_","Photon GEN p_{T}", 400, 0., 4000.);
		photonEGEN_ = new TH1F("photonEGEN_","Photon GEN E", 400, 0., 4000.);
		photonEtaGEN_ = new TH1F("photonEtaGEN_","Photon GEN #eta", 3000, -3, 3);
		photonPhiGEN_ = new TH1F("photonPhiGEN_","Photon GEN #varphi", 1000, -3.1416, 3.1416);

		CleanedJetsGEN_N_ = new TH1F("CleanedJetsGEN_N_","Cleaned Jets GEN N", 10, 0, 10);
		SelectedJetsGEN_N_ = new TH1F("SelectedJetsGEN_N_","Selected Jets GEN N", 10, 0, 10);

		SelectedJets_PtGEN_1_ = new TH1F("SelectedJets_PtGEN_1_","Jet 1 GEN p_{T} ", 400, 0., 4000.);
		SelectedJets_EGEN_1_ = new TH1F("SelectedJets_EGEN_1_", "jet 1 GEN E", 400, 0., 4000.);
		SelectedJets_EtaGEN_1_ = new TH1F("SelectedJets_EtaGEN_1_","Jet 1 GEN #eta ", 3000, -3, 3);
		SelectedJets_PhiGEN_1_ = new TH1F("SelectedJets_PhiGEN_1_","Jet 1 GEN #varphi ", 1000, -3.1416, 3.1416);

		CleanedJetsGEN_HT_ = new TH1F("CleanedJetsGEN_HT_","Cleaned Jets H_{T} GEN", 400, 0, 4000);
		SelectedJetsGEN_HT_ = new TH1F("SelectedJetsGEN_HT_","Selected Jets H_{T} GEN", 400, 0, 4000);

		HTParSum_ = new TH1F("HTParSum_","H_{T} Partons Sum", 400, 0, 4000);
	}

	IDIsoPhotons_N_ = new TH1F("IDIsoPhotons_N_","ID-Iso Photons N", 10, 0, 10);
	SelectedPhotons_N_ = new TH1F("SelectedPhotons_N_","Selected Photons N", 10, 0, 10);

	Nvtx_ = new TH1F("Nvtx_","Number of vertices ", 50, 0, 50);

	SelectedPhotons_Pt_1_ = new TH1F("SelectedPhotons_Pt_1_","Photon p_{T} ", 400, 0., 4000.);
	SelectedPhotons_E_1_ = new TH1F("SelectedPhotons_E_1_","Photon E ", 400, 0., 4000.);
	SelectedPhotons_Eta_1_ = new TH1F("SelectedPhotons_Eta_1_","Photon #eta ", 3000, -3, 3);
	SelectedPhotons_Phi_1_ = new TH1F("SelectedPhotons_Phi_1_","Photon #varphi ", 1000, -3.1416, 3.1416);
	SelectedPhotons_Bit_1_ = new TH1F("SelectedPhotons_Bit_1_","Photon bit ", 100, 0., 1000.);

	SelectedPhotons_PassConversionVeto_1_ = new TH1F("SelectedPhotons_PassConversionVeto_1_","photonPassConversionVeto ", 10, -2, 2);
	SelectedPhotons_PfIsoChargedHad_1_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_", "photon PfIsoChargedHad", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_", "photon PfIsoNeutralHad", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_", "photon PfIsoPhoton", 2000, 0, 200);
	SelectedPhotons_PfIso_1_ = new TH1F("SelectedPhotons_PfIso_1_", "photon PfIso", 2000, 0, 200);
	SelectedPhotons_PfIso_ov_Pt_1_ = new TH1F("SelectedPhotons_PfIso_ov_Pt_1_", "photon PfIso/p_{T} ", 100, 0, 0.2);
	SelectedPhotons_PfIsoPhotons03ForCic_1_ = new TH1F("SelectedPhotons_PfIsoPhotons03ForCic_1_", "photon PfIsoPhotons03ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoNeutrals03ForCic_1_ = new TH1F("SelectedPhotons_PfIsoNeutrals03ForCic_1_","photon PfIsoNeutrals03ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged03ForCicVtx0_1_ = new TH1F("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "photon PfIsoCharged03ForCicVtx0", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged03BadForCic_1_ = new TH1F("SelectedPhotons_PfIsoCharged03BadForCic_1_", "photon PfIsoCharged03BadForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoPhotons04ForCic_1_ = new TH1F("SelectedPhotons_PfIsoPhotons04ForCic_1_", "photon PfIsoPhotons04ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoNeutrals04ForCic_1_ = new TH1F("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "photon PfIsoNeutrals04ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged04ForCicVtx0_1_ = new TH1F("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "photon PfIsoCharged04ForCicVtx0", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged04BadForCic_1_ = new TH1F("SelectedPhotons_PfIsoCharged04BadForCic_1_", "photonPfIsoCharged04BadForCic", 2000, 0, 200);
	SelectedPhotons_id_sieie_1_ = new TH1F("SelectedPhotons_id_sieie_1_", "photon ID: #sigma_{i#etai#eta}", 500, 0., 0.050);
	SelectedPhotons_id_sieip_1_ = new TH1F("SelectedPhotons_id_sieip_1_", "photon ID: #sigma_{i#etai#varphi}", 400, 0, 0.04);
	SelectedPhotons_id_etawidth_1_ = new TH1F("SelectedPhotons_id_etawidth_1_", "photon ID: #eta width", 400, 0, 0.04);
	SelectedPhotons_id_phiwidth_1_ = new TH1F("SelectedPhotons_id_phiwidth_1_", "photon ID: #varphi width", 200, 0, 0.2);
	SelectedPhotons_id_r9_1_ = new TH1F("SelectedPhotons_id_r9_1_", "photon ID: r9", 200, 0, 2);
	SelectedPhotons_id_lambdaRatio_1_ = new TH1F("SelectedPhotons_id_lambdaRatio_1_", "photon ID: #lambda Ratio", 200, 0, 2);
	SelectedPhotons_id_s4Ratio_1_ = new TH1F("SelectedPhotons_id_s4Ratio_1_","photon ID: s4 Ratio", 200, 0, 2);
	SelectedPhotons_id_e25_1_ = new TH1F("SelectedPhotons_id_e25_1_", "photon ID: #rho25", 400, 0, 4000);
	SelectedPhotons_id_sceta_1_ = new TH1F("SelectedPhotons_id_sceta_1_", "photon ID: SC #eta", 3000, -3, 3);
	SelectedPhotons_id_ESEffSigmaRR_1_ = new TH1F("SelectedPhotons_id_ESEffSigmaRR_1_", "photon ID: ESEffSigmaRR", 200, 0, 2);
	SelectedPhotons_id_hadronicOverEm_1_ = new TH1F("SelectedPhotons_id_hadronicOverEm_1_", "photon ID: hadronicOverEm", 4000, 0, 0.4);
	SelectedPhotons_id_hadronicOverEm2012_1_ = new TH1F("SelectedPhotons_id_hadronicOverEm2012_1_", "photon ID: hadronicOverEm2012", 4000, 0, 0.4);
	SelectedPhotons_hcalTowerSumEtConeDR04_1_ = new TH1F("SelectedPhotons_hcalTowerSumEtConeDR04_1_","photon hcalTowerSumEtConeDR04", 1000, 0, 1000);
	SelectedPhotons_ecalRecHitSumEtConeDR04_1_ = new TH1F("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "photon ecalRecHitSumEtConeDR04", 1000, 0, 1000);
	SelectedPhotons_nTrkSolidConeDR04_1_ = new TH1F("SelectedPhotons_nTrkSolidConeDR04_1_", "photon nTrkSolidConeDR04", 2000, 0, 1000);
	SelectedPhotons_trkSumPtSolidConeDR04_1_ = new TH1F("SelectedPhotons_trkSumPtSolidConeDR04_1_","photon trkSumPtSolidConeDR04", 1000, 0, 1000);
	SelectedPhotons_nTrkHollowConeDR04_1_ = new TH1F("SelectedPhotons_nTrkHollowConeDR04_1_", "photon nTrkHollowConeDR04", 200, 0, 100) ;
	SelectedPhotons_trkSumPtHollowConeDR04_1_ = new TH1F("SelectedPhotons_trkSumPtHollowConeDR04_1_", "photon trkSumPtHollowConeDR04", 1000, 0, 1000);
	SelectedPhotons_IsoFPRCharged_1_ = new TH1F("SelectedPhotons_IsoFPRCharged_1_", "photon IsoFPRCharged", 2000, 0, 200); 
	SelectedPhotons_IsoFPRNeutral_1_ = new TH1F("SelectedPhotons_IsoFPRNeutral_1_", "photon IsoFPRNeutral", 2000, 0, 200);
	SelectedPhotons_IsoFPRPhoton_1_ = new TH1F("SelectedPhotons_IsoFPRPhoton_1_", "photon IsoFPRPhoton", 2000, 0, 200);
	SelectedPhotons_IsoFPRCharged_ov_Pt_1_ = new TH1F("SelectedPhotons_IsoFPRCharged_ov_Pt_1_", "photon IsoFPRCharged/p_{T}", 100, 0, 0.2); 
	SelectedPhotons_IsoFPRNeutral_ov_Pt_1_ = new TH1F("SelectedPhotons_IsoFPRNeutral_ov_Pt_1_", "photon IsoFPRNeutral/p_{T}", 100, 0, 0.2);
	SelectedPhotons_IsoFPRPhoton_ov_Pt_1_ = new TH1F("SelectedPhotons_IsoFPRPhoton_ov_Pt_1_", "photon IsoFPRPhoton/p_{T}", 100, 0, 0.2);

	CleanedJetsLEA_N_ = new TH1F("CleanedJetsLEA_N_","Cleaned Jets LEA N ", 10, 0, 10);
	SelectedJetsLEA_N_ = new TH1F("SelectedJetsLEA_N_","Selected Jets LEA N", 10, 0, 10);
	CleanedJets_N_ = new TH1F("CleanedJets_N_","Cleaned Jets N ", 10, 0, 10);
	SelectedJets_N_ = new TH1F("SelectedJets_N_","Selected Jets N", 10, 0, 10);

	SelectedJets_Pt_1_ = new TH1F("SelectedJets_Pt_1_","Jet 1 p_{T} ", 400, 0., 4000.);
	SelectedJets_E_1_ = new TH1F("SelectedJets_E_1_", "jet 1 E", 400, 0., 4000.);
	SelectedJets_Eta_1_ = new TH1F("SelectedJets_Eta_1_","Jet 1 #eta ", 3000, -3, 3);
	SelectedJets_Phi_1_ = new TH1F("SelectedJets_Phi_1_","Jet 1 #varphi ", 1000, -3.1416, 3.1416);

	DeltaR_photon1_jet1_ = new TH1F("DeltaR_photon1_jet1_","#DeltaR #gamma1-jet1", 30, 0, 6);
	DeltaEta_photon1_jet1_ = new TH1F("DeltaEta_photon1_jet1_","#Delta#eta #gamma1-jet1", 50, 0, 5);
	DeltaPhi_photon1_jet1_ = new TH1F("DeltaPhi_photon1_jet1_","#Delta#varphi #gamma1-jet1", 50, 0, 3.1416);

	SelectedJets_Pt_2_ = new TH1F("SelectedJets_Pt_2_","Jet 2 p_{T} ", 400, 0., 4000.);
	SelectedJets_E_2_ = new TH1F("SelectedJets_E_2_", "jet 2 E", 400, 0., 4000.);
	SelectedJets_Eta_2_ = new TH1F("SelectedJets_Eta_2_","Jet 2 #eta ", 3000, -3, 3);
	SelectedJets_Phi_2_ = new TH1F("SelectedJets_Phi_2_","Jet 2 #varphi ", 1000, -3.1416, 3.1416);

	DeltaR_photon1_jet2_ = new TH1F("DeltaR_photon1_jet2_","#DeltaR #gamma1-jet2", 30, 0, 6);
	DeltaR_jet1_jet2_ = new TH1F("DeltaR_jet1_jet2_","#DeltaR jet1-jet2", 30, 0, 6);
	DeltaEta_jet1_jet2_ = new TH1F("DeltaEta_jet1_jet2_","#Delta#eta jet1-jet2", 50, 0, 5);
	DeltaPhi_jet1_jet2_ = new TH1F("DeltaPhi_jet1_jet2_","#Delta#varphi jet1-jet2", 50, 0, 3.1416);

	SelectedJets_Pt_3_ = new TH1F("SelectedJets_Pt_3_","Jet 3 p_{T} ", 400, 0., 4000.);
	SelectedJets_E_3_ = new TH1F("SelectedJets_E_3_", "jet 3 E", 400, 0., 4000.);
	SelectedJets_Eta_3_ = new TH1F("SelectedJets_Eta_3_","Jet 3 #eta ", 3000, -3, 3);
	SelectedJets_Phi_3_ = new TH1F("SelectedJets_Phi_3_","Jet 3 #varphi ", 1000, -3.1416, 3.1416);

	DeltaR_photon1_jet3_ = new TH1F("DeltaR_photon1_jet3_","#DeltaR #gamma1-jet3", 30, 0, 6);

	CleanedJets_HT_ = new TH1F("CleanedJets_HT_","Cleaned Jets H_{T}", 400, 0, 4000);
	SelectedJets_HT_ = new TH1F("SelectedJets_HT_","Selected Jets H_{T}", 400, 0, 4000);

	CleanedJetsLEA_preHT_N_ = new TH1F("CleanedJetsLEA_preHT_N_","Cleaned Jets LEA N pre-H_{T}", 10, 0, 10);
	SelectedJetsLEA_preHT_N_ = new TH1F("SelectedJetsLEA_preHT_N_","Selected Jets LEA N pre-H_{T}", 10, 0, 10);
	CleanedJets_preHT_N_= new TH1F("CleanedJets_preHT_N_","Cleaned Jets N pre-H_{T}", 10, 0, 10);
	SelectedJets_preHT_N_= new TH1F("SelectedJets_preHT_N_","Selected Jets N pre-H_{T}", 10, 0, 10);
	SelectedJets_preHT_Pt_1_= new TH1F("SelectedJets_preHT_Pt_1_","Jet 1 p_{T} pre-H_{T}", 400, 0., 4000.);
	SelectedJets_preHT_Pt_2_ = new TH1F("SelectedJets_preHT_Pt_2_","Jet 2 p_{T} pre-H_{T}", 400, 0., 4000.);
	SelectedJets_preHT_Pt_3_ = new TH1F("SelectedJets_preHT_Pt_3_","Jet 3 p_{T} pre-H_{T}", 400, 0., 4000.);
	CleanedJets_preHT_HT_= new TH1F("CleanedJets_preHT_HT_","Cleaned Jets H_{T} pre-H_{T}", 400, 0, 4000);
	SelectedJets_preHT_HT_= new TH1F("SelectedJets_preHT_HT_","Selected Jets H_{T} pre-H_{T}", 400, 0, 4000);

	thrust_ = new TH1F("thrust_","thrust", 50, -3.1416, 3.1416);
	broad_ = new TH1F("broad_","broad", 50, -3.1416, 3.1416);
	S3_ = new TH1F("S3_","S3", 50, -3.1416, 3.1416);
	S4_ = new TH1F("S4_","S4", 50, -3.1416, 3.1416);

//	ptPhoton_->Sumw2();
//	etaPhoton_->Sumw2();
//	phiPhoton_->Sumw2();

	cout << "...booking histograms finished." << endl;
}


void GJetsAnalyzer::Plot_Histos(){

	// plot few histograms at the end, for check
	cout << "Plots: quick check... " << endl;

	bool plot_gen_01 = true;
	bool plot_gen_02 = true;
	bool plot_gen_03 = true;

	bool plot_01 = true;
	bool plot_02 = true;
	bool plot_03 = true;
	bool plot_04 = true;
	bool plot_05 = true;
	bool plot_06 = true;
	bool plot_07 = true;
	bool plot_08 = true;
	bool plot_09 = true;
	bool plot_10 = true;
	bool plot_11 = true;
	bool plot_12 = true;
	bool plot_13 = true;
	bool plot_14 = true;
	bool plot_15 = false;
	bool plot_16 = false;

	gStyle->SetOptStat(1111111);

	if(plot_gen_01){
		TCanvas *c_gen01 = new TCanvas("c_gen01", "GEN photon kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen01->Divide(2,3);
		c_gen01->cd(1);
		nPhotonsGEN_->Draw();
		c_gen01->cd(2);
		photonPtGEN_->Draw();
		c_gen01->cd(3);
		photonEGEN_->Draw();
		c_gen01->cd(4);
		photonEtaGEN_->Draw();
		c_gen01->cd(5);
		photonPhiGEN_->Draw();
		c_gen01->cd(6);
	}

	if(plot_gen_02){
		TCanvas *c_gen02 = new TCanvas("c_gen02", "GEN jets variables", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen02->Divide(2,3);
		c_gen02->cd(1);
		CleanedJetsGEN_N_->Draw();
		c_gen02->cd(2);
		SelectedJetsGEN_N_->Draw();
		c_gen02->cd(3);
		SelectedJets_PtGEN_1_->Draw();
		c_gen02->cd(4);
		SelectedJets_EGEN_1_->Draw();
		c_gen02->cd(5);
		SelectedJets_EtaGEN_1_->Draw();
		c_gen02->cd(6);
		SelectedJets_PhiGEN_1_->Draw();
	}

	if(plot_gen_03){
		TCanvas *c_gen03 = new TCanvas("c_gen03", "GEN H_T", 10, 10, 700, 700);
		gPad->SetLogy();
		c_gen03->Divide(1,3);
		c_gen03->cd(1);
		CleanedJetsGEN_HT_->Draw();
		c_gen03->cd(2);
		SelectedJetsGEN_HT_->Draw();
		c_gen03->cd(3);
		HTParSum_->Draw();
	}

	if(plot_01){
		TCanvas *c01 = new TCanvas("c01", "photon kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c01->Divide(2,4);
		c01->cd(1);
		IDIsoPhotons_N_->Draw();
		c01->cd(2);
		SelectedPhotons_N_->Draw();
		c01->cd(3);
		Nvtx_->Draw();
		c01->cd(4);
		SelectedPhotons_Pt_1_->Draw();
		c01->cd(5);
		SelectedPhotons_E_1_->Draw();
		c01->cd(6);
		SelectedPhotons_Eta_1_->Draw();
		c01->cd(7);
		SelectedPhotons_Phi_1_->Draw();
		c01->cd(8);
	}

	if(plot_02){ 
		TCanvas *c02 = new TCanvas("c02", "photon Isolation", 10, 10, 700, 700);
		gPad->SetLogy();
		c02->Divide(3,2);
		c02->cd(1);
		SelectedPhotons_PassConversionVeto_1_->Draw();
		c02->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_->Draw();
		c02->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_->Draw();
		c02->cd(4);
		SelectedPhotons_PfIsoPhoton_1_->Draw();
		c02->cd(5);
		SelectedPhotons_PfIso_1_->Draw();
		c02->cd(6);
		SelectedPhotons_PfIso_ov_Pt_1_->Draw();
	}

	if(plot_03){
		TCanvas *c03 = new TCanvas("c03", "photon Isolation cone 03 for Cic", 10, 10, 700, 700);
		gPad->SetLogy();
		c03->Divide(2,2);
		c03->cd(1);
		SelectedPhotons_PfIsoPhotons03ForCic_1_->Draw();
		c03->cd(2);
		SelectedPhotons_PfIsoNeutrals03ForCic_1_->Draw();
		c03->cd(3);
		SelectedPhotons_PfIsoCharged03ForCicVtx0_1_->Draw();
		c03->cd(4);
		SelectedPhotons_PfIsoCharged03BadForCic_1_->Draw();
	}

	if(plot_04){
		TCanvas *c04 = new TCanvas("c04", "photon Isolation cone 04 for Cic", 10, 10, 700, 700);
		gPad->SetLogy();
		c04->Divide(2,2);
		c04->cd(1);
		SelectedPhotons_PfIsoPhotons04ForCic_1_->Draw();
		c04->cd(2);
		SelectedPhotons_PfIsoNeutrals04ForCic_1_->Draw();
		c04->cd(3);
		SelectedPhotons_PfIsoCharged04ForCicVtx0_1_->Draw();
		c04->cd(4);
		SelectedPhotons_PfIsoCharged04BadForCic_1_->Draw();
	}

	if(plot_05){
		TCanvas *c05 = new TCanvas("c05", "photon ID", 10, 10, 700, 700);
		gPad->SetLogy();
		c05->Divide(3,4);
		c05->cd(1);
		SelectedPhotons_id_sieie_1_->Draw();
		c05->cd(2);
		SelectedPhotons_id_sieip_1_->Draw();
		c05->cd(3);
		SelectedPhotons_id_etawidth_1_->Draw();
		c05->cd(4);
		SelectedPhotons_id_phiwidth_1_->Draw();
		c05->cd(5);
		SelectedPhotons_id_r9_1_->Draw();
		c05->cd(6);
		SelectedPhotons_id_lambdaRatio_1_->Draw();
		c05->cd(7);
		SelectedPhotons_id_s4Ratio_1_->Draw();
		c05->cd(8);
		SelectedPhotons_id_e25_1_->Draw();
		c05->cd(9);
		SelectedPhotons_id_sceta_1_->Draw();
		c05->cd(10);
		SelectedPhotons_id_ESEffSigmaRR_1_->Draw();
		c05->cd(11);
		SelectedPhotons_id_hadronicOverEm_1_->Draw();
		c05->cd(12);
		SelectedPhotons_id_hadronicOverEm2012_1_->Draw();
	}

	if(plot_06){
		TCanvas *c06 = new TCanvas("c06", "photon E_{T}-p_{T} cone 04", 10, 10, 700, 700);
		gPad->SetLogy();
		c06->Divide(3,2);
		c06->cd(1);
		SelectedPhotons_hcalTowerSumEtConeDR04_1_->Draw();
		c06->cd(2);
		SelectedPhotons_ecalRecHitSumEtConeDR04_1_->Draw();
		c06->cd(3);
		SelectedPhotons_nTrkSolidConeDR04_1_->Draw();
		c06->cd(4);
		SelectedPhotons_trkSumPtSolidConeDR04_1_->Draw();
		c06->cd(5);
		SelectedPhotons_nTrkHollowConeDR04_1_->Draw();
		c06->cd(6);
		SelectedPhotons_trkSumPtHollowConeDR04_1_->Draw();
	}

	if(plot_07){
		TCanvas *c07 = new TCanvas("c07", "photon Isolation FPR", 10, 10, 700, 700);
		gPad->SetLogy();
		c07->Divide(3,2);
		c07->cd(1);
		SelectedPhotons_IsoFPRCharged_1_->Draw(); 
		c07->cd(2);
		SelectedPhotons_IsoFPRNeutral_1_->Draw(); 
		c07->cd(3);
		SelectedPhotons_IsoFPRPhoton_1_->Draw();
		c07->cd(4);
		SelectedPhotons_IsoFPRCharged_ov_Pt_1_->Draw(); 
		c07->cd(5);
		SelectedPhotons_IsoFPRNeutral_ov_Pt_1_->Draw(); 
		c07->cd(6);
		SelectedPhotons_IsoFPRPhoton_ov_Pt_1_->Draw();
	}

	if(plot_08){
		TCanvas *c08 = new TCanvas("c08", "jets counting", 10, 10, 700, 700);
		gPad->SetLogy();
		c08->Divide(2,2);
		c08->cd(1);
		CleanedJetsLEA_N_->Draw(); 
		c08->cd(2);
		SelectedJetsLEA_N_->Draw(); 
		c08->cd(3);
		CleanedJets_N_->Draw();
		c08->cd(4);
		SelectedJets_N_->Draw();
	}

	if(plot_09){
		TCanvas *c09 = new TCanvas("c09", "Jet 1 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c09->Divide(2,2);
		c09->cd(1);
		SelectedJets_Pt_1_->Draw(); 
		c09->cd(2);
		SelectedJets_E_1_->Draw();
		c09->cd(3);
		SelectedJets_Eta_1_->Draw();
		c09->cd(4);
		SelectedJets_Phi_1_->Draw();
	}

	if(plot_10){
		TCanvas *c10 = new TCanvas("c10", "angular variables with 1 jet", 10, 10, 700, 700);
		gPad->SetLogy();
		c10->Divide(1,3);
		c10->cd(1);
		DeltaR_photon1_jet1_->Draw();
		c10->cd(2);
		DeltaEta_photon1_jet1_->Draw();
		c10->cd(3);
		DeltaPhi_photon1_jet1_->Draw();
	}

	if(plot_11){
		TCanvas *c11 = new TCanvas("c11", "Jet 2 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c11->Divide(2,2);
		c11->cd(1);
		SelectedJets_Pt_2_->Draw(); 
		c11->cd(2);
		SelectedJets_E_2_->Draw();
		c11->cd(3);
		SelectedJets_Eta_2_->Draw();
		c11->cd(4);
		SelectedJets_Phi_2_->Draw();
	}

	if(plot_12){
		TCanvas *c12 = new TCanvas("c12", "Angular variables with 2-3 jets", 10, 10, 700, 700);
		gPad->SetLogy();
		c12->Divide(2,3);
		c12->cd(1);
		DeltaR_photon1_jet2_->Draw();
		c12->cd(2);
		DeltaR_jet1_jet2_->Draw();
		c12->cd(3);
		DeltaEta_jet1_jet2_->Draw();
		c12->cd(4);
		DeltaPhi_jet1_jet2_->Draw();
		c12->cd(5);
		DeltaR_photon1_jet3_ = new TH1F("DeltaR_photon1_jet3_","#DeltaR #gamma1-jet3", 30, 0, 6);
		c12->cd(6);
	}

	if(plot_13){
		TCanvas *c13 = new TCanvas("c13", "Jet 3 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c13->Divide(2,2);
		c13->cd(1);
		SelectedJets_Pt_3_->Draw(); 
		c13->cd(2);
		SelectedJets_E_3_->Draw();
		c13->cd(3);
		SelectedJets_Eta_3_->Draw();
		c13->cd(4);
		SelectedJets_Phi_3_->Draw();
	}

	if(plot_14){
		TCanvas *c14 = new TCanvas("c14", "H_T", 10, 10, 700, 700);
		gPad->SetLogy();
		c14->Divide(1,2);
		c14->cd(1);
		CleanedJets_HT_->Draw(); 
		c14->cd(2);
		SelectedJets_HT_->Draw();
	}

	if(plot_15){
		TCanvas *c15 = new TCanvas("c15", "Variables pre-H_T cut", 10, 10, 700, 700);
		gPad->SetLogy();
		c15->Divide(2,5);
		c15->cd(1);
		CleanedJetsLEA_preHT_N_->Draw(); 
		c15->cd(2);
		SelectedJetsLEA_preHT_N_->Draw();
		c15->cd(3);
		CleanedJets_preHT_N_->Draw();
		c15->cd(4);
		SelectedJets_preHT_N_->Draw();
		c15->cd(5);
		SelectedJets_preHT_Pt_1_->Draw();
		c15->cd(6);
		SelectedJets_preHT_Pt_2_->Draw();
		c15->cd(7);
		SelectedJets_preHT_Pt_3_->Draw();
		c15->cd(8);
		CleanedJets_preHT_HT_->Draw();
		c15->cd(9);
		SelectedJets_preHT_HT_->Draw();
		c15->cd(10);
	}

	if(plot_16){
		TCanvas *c16 = new TCanvas("c16", "Event shape variables", 10, 10, 700, 700);
		gPad->SetLogy();
		c16->Divide(2,2);
		c16->cd(1);
		thrust_->Draw();
		c16->cd(2);
		broad_->Draw();
		c16->cd(3);
		S3_->Draw();
		c16->cd(4);
		S4_->Draw();
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


void GJetsAnalyzer::Text_File(){

	cout << "Writing text file... " << endl;
	ofstream text;
	text.open(textname);
	text << "Running on " << sample_r << endl;
	text << "Weight is " << weight_r << endl;
	text << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	text << "Number of selected events 0, unweighted = " << iSelected0 << endl;
	text << "Number of selected events 1, unweighted = " << iSelected1 << endl;
	text << "Number of selected events 2, unweighted = " << iSelected2 << endl;
	text << "Number of selected events 3, unweighted = " << iSelected3 << endl;
	text << "Number of selected events 4, unweighted = " << iSelected4 << endl;
	text << "Number of selected events, unweighted = " << iSelected4 << endl;
	text << "Number of selected events, weighted = " << iSelected4*weight_r << endl;
	text.close();
	cout << "...writing text file finished. " << endl;
	}
