#define GJetsAnalyzer_cxx
#include "sandro/VPlusJetsAnaysis/include/GJetsAnalyzer.h"
#include "sandro/VPlusJetsAnaysis/include/GJetsDefs.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <Riostream.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStyle.h>
#include <TCanvas.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<float>+;
#endif

//		In a ROOT session, you can do:
//			Root > .L GJetsAnalyzer.C
//			Root > GJetsAnalyzer t
//			Root > t.GetEntry(12); // Fill t data members with entry number 12
//			Root > t.Show();       // Show values of entry 12
//			Root > t.Show(16);     // Read and show values of entry 16
//			Root > t.Loop();       // Loop on all entries
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
//				fChain->SetBranchStatus("*",0);          // disable all branches
//				fChain->SetBranchStatus("branchname",1); // activate branchname
//			METHOD2:
//				replace line fChain->GetEntry(jentry); // read all branches
//				by b_branchname->GetEntry(ientry);     // read only this branch


void GJetsAnalyzer::Loop(Int_t isample){

  Float_t weight;
  Int_t itype = 0;   // dummy for the moment 

  // choose the sample:
  // isample == 0 -> data
  // isample == 1 -> GJets 200<HT<400
  // isample == 2 -> Gjets 400<HT<Inf
  // isample == 3 -> QCD   100<HT<250
  // isample == 4 -> QCD   250<HT<500
  // isample == 5 -> QCD   500<HT<1000
  // isample == 6 -> QCD   1000<HT<inf
  // isample == 7 -> test

//  double Lumi_t = 185.798;  
  double Lumi_t = 510.274;  
  double xsec = 1.;  
  double kFac = 1.;  
  double nEvents = 1.;  

/*
  if (isample == 0) {
    sprintf(outputname, "data_Run2012B-13Jul2012_gammahistos_%d.root", itype);
    weight = 1.;
    cout << "Running on data. " << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " \pb" << endl;
  }
*/
  if (isample == 0) {
    sprintf(outputname, "data_all_photons_gammahistos_%d.root", itype);
    weight = 1.;
    cout << "Running on data. " << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " \pb" << endl;
  }

  else if (isample == 1){ 
    sprintf(outputname, "mc_GJets_HT-200To400_gammahistos_%d.root", itype);   //xsec=25690 pb * k-factor 1.23?
		nEvents = 4990000;
		xsec = 960.5;  
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on GJets_HT-200To400. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 2){
    sprintf(outputname, "mc_GJets_HT-400ToInf_gammahistos_%d.root", itype);   //xsec=5213 pb *1.23?
		nEvents = 3995000;
		xsec = 107.5;  
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on GJets_HT-400ToInf. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 3){
    sprintf(outputname, "mc_QCD_HT-100To250_gammahistos_%d.root", itype);   //xsec=798.3 pb *1.23?
		nEvents = 5000000;
		xsec = 1.036E7;  
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on GQCD_HT-100To250 " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 4){
    sprintf(outputname, "mc_QCD_HT-250To500_gammahistos_%d.root", itype);   //xsec=198500
		nEvents = 1.;
		xsec = 	276000.0;  
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on QCD_HT-250To500. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 5){
    sprintf(outputname, "mc_QCD_HT-500To1000_gammahistos_%d.root", itype);   //xsec=5856
		nEvents = 4985000;
		xsec = 8426.0;  
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on QCD_HT-500To1000. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 6){
    sprintf(outputname, "mc_QCD_HT-1000ToInf_gammahistos_%d.root", itype);   //xsec=198500
		nEvents = 3987307;
		xsec = 204.0;  
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on QCD_HT-1000ToInf. " << endl;
    cout << "weight is " << weight << endl;
  }

  else if (isample == 7){
    sprintf(outputname, "test_%d.root", itype);   //xsec=198500
    weight = 1.;
    cout << "Running on test " << endl;
    cout << "weight is " << weight << endl;
  }


  if (fChain == 0) return;

  // ================ initialize and book histograms
  TFile *fhistos= new TFile(outputname, "RECREATE");
  Book_Histos();
  iSelected = 0;
/*    iSelected1 = 0;
      iSelected2 = 0;
        iSelected3 = 0;
          iSelected4 = 0;
            iSelected5 = 0;
              iSelected6 = 0;
*/
//  iSelectedWithWeights = 0;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    if(jentry%100000 == 0) cout << jentry << endl;
    Zero_Variables();

    // ============ selection for photon at GEN level
    // take request of jet, as done by Jessica
    // if (selGEN && nPhotonsGEN > 0 && photonPtGEN > 150. && TMath::Abs(photonEtaGEN) < 3. && nJetsGEN > 0) {

    if (selGEN && nPhotonsGEN > 0 && photonPtGEN > 150. && TMath::Abs(photonEtaGEN) < 3.) { //da aggiungere isEBEEGap()
          
      ptGENjet1 = jetPtGEN->at(0);
      etaGENjet1 = jetEtaGEN->at(0);

      // if(ptGENjet1>50. && TMath::Abs(etaGENjet1)<2.5){
      Bool_t DummyTrue = kTRUE;
      if(DummyTrue){
        ptPhotonGEN_->Fill(photonPtGEN, 1.);

				// ======= now look here for reconstructed photon, do not require trigger and reconstructed jets at this point
        if (selRECO && nPhotons > 0 && (*photonPt)[0] > 150. && TMath::Abs((*photonEta)[0]) < 3. && (((*photonBit)[0]&1) || ((*photonBit)[0]&4)) ) {

          Float_t deta = photonEtaGEN - ((*photonEta)[0]);
          Float_t dphi = deltaPhi((*photonPhi)[0], photonPhiGEN);
          Float_t drsquared = deta*deta + dphi*dphi;
          Float_t DeltaR_GENREC = TMath::Sqrt(drsquared);
          // if(jentry<10) cout << "deta " << deta << endl;
          // if(jentry<10) cout << "dphi " << deta << endl;
          // if(jentry<10) cout << "DeltaR_GENREC " << DeltaR_GENREC << endl;
          DeltaRGENREC_->Fill(DeltaR_GENREC, 1.); // why such a small number?
          if (DeltaR_GENREC < 0.1) {
	    			ptPhotonREC_->Fill(photonPtGEN, 1.);
	  			} // end if DeltaR matching GEN-REC cut
				} // end RECO cuts on photons
      } // end DummyTrue  
    } // end GEN cuts

    // ============ selection for photons at RECO level for control plots
		if(selRECO && nPhotons > 0 && nJets > 0 && isTriggerMatchedFamily4) { 

			// =========== add stricter selection here
			// at least one jet with pt > 50 GeV and eta < 2.5
			// and that the photon is in the barrel (photonBit |= (it->isEB()          << 0) => (*photonBit)[0]&1) con 2^0 = 1
			// and has a pt greater than 150.;

			// jet1
			ptjet1 = jetPt->at(0);
			etajet1 = jetEta->at(0);
			phijet1 = jetPhi->at(0);           
			if (ptjet1 > 50. && TMath::Abs(etajet1) < 2.5 && (*photonPt)[0] > 150. && ((*photonBit)[0]&1) ) {

				if(photonPassConversionVeto == 1 && 
				   photonid_hadronicOverEm2012 < 0.05 && 
				   photonid_sieie < 0.012 && 
				   photonPfIsoChargedHad < 2.6 && 
				   photonPfIsoNeutralHad < (3.5 + 0.04*(*photonPt)[0]) &&
				   photonPfIsoPhoton < (1.3 + 0.005*(*photonPt)[0])){

/*
			if((*photonPassConversionVeto)[0] == 1){ 
				   iSelected1++;				 
				   if((*photonid_hadronicOverEm2012)[0] < 0.05){
				    iSelected2++;
					 	if((*photonid_sieie)[0] < 0.012){ 
					    iSelected3++;
				    	if((*photonPfIsoChargedHad)[0] < 2.6){ 
						    iSelected4++;
				   			if((*photonPfIsoNeutralHad)[0] < (3.5 + 0.04*(*photonPt)[0])){
							    iSelected5++;
				   				if((*photonPfIsoPhoton)[0] < (1.3 + 0.005*(*photonPt)[0])){
								    iSelected6++;
*/

				iSelected++;

				Nvtx_->Fill(nVtx, weight);
				nPhotons_->Fill(nPhotons, weight);
				nJets_->Fill(nJets, weight);
				
				ptPhoton_->Fill((*photonPt)[0], weight);
				etaPhoton_->Fill((*photonEta)[0], weight);
				phiPhoton_->Fill((*photonPhi)[0], weight);

				ptjet1_->Fill(ptjet1, weight);
				etajet1_->Fill(etajet1, weight);
				phijet1_->Fill(phijet1, weight);
				} // end quality selection
//			}}}}}}

			} // end selection with 1 jet

      // if (Cut(ientry) < 0) continue;
		} // end if preselection
	} // end loop on entries

	// ====================================terminate and plot
/*	cout << "Number of selected events, unweighted = " << iSelected1 << endl;
		cout << "Number of selected events, unweighted = " << iSelected2 << endl;
			cout << "Number of selected events, unweighted = " << iSelected3 << endl;
				cout << "Number of selected events, unweighted = " << iSelected4 << endl;
					cout << "Number of selected events, unweighted = " << iSelected5 << endl;
						cout << "Number of selected events, unweighted = " << iSelected6 << endl;
*/
	cout << "Number of selected events, unweighted = " << iSelected << endl;
	cout << "Number of selected events Only one type and ptjet1 > 50, weighted = " << iSelected*weight << endl;
 
	fhistos->Write();
	Plot_Histos();  
}


// ----- methods ----------------

void Book_Histos(){

	cout << "Booking histograms... " << endl;
	// book the histograms

  ptPhotonGEN_= new TH1F("ptPhotonGEN","p_{T} of the GEN photon", 2, 150., 200.);
  ptPhotonREC_= new TH1F("ptPhotonREC_","p_{T} of the REC photon (GEN selection)",2,150.,200.);
  DeltaRGENREC_=new TH1F("DeltaRGENREC_","DeltaR Gen-REC photon", 50, 0., 0.01);

  Nvtx_ = new TH1F("Nvtx_","Number of vertices ", 50, 0, 50);
	nPhotons_ = new TH1F("nPhotons_","Number of Photons ", 10, 0, 10);
	nJets_ = new TH1F("nJets_","Number of Jets ", 10, 0, 10);
	ptPhoton_ = new TH1F("ptPhoton_","p_{T} of the REC photon ", 100, 0., 1000.);
	etaPhoton_ = new TH1F("etaPhoton_","#eta of the REC photon ", 100, -5., 5.);
	phiPhoton_ = new TH1F("phiPhoton_","#varphi of the REC photon ", 100, -3.1416, 3.1416);

	ptjet1_ = new TH1F("ptjet1","p_{T} of jet 1 ", 100, 0., 1000.);
	etajet1_ = new TH1F("etajet1","#eta of jet 1", 100, -5., 5.);
	phijet1_ = new TH1F("phijet1","#varphi of of jet 1", 100, -3.1416, 3.1416);


//  ptPhoton_->Sumw2();
//  etaPhoton_->Sumw2();
//  phiPhoton_->Sumw2();
}


void Plot_Histos(){

  // plot few histograms at the end, for check
  cout << "Plot, quick check " << endl;

  gStyle->SetOptStat(1111111);

  TCanvas *c111 = new TCanvas("c111", "General", 10, 10, 700, 700);
  gPad->SetLogy();
  c111->Divide(2,3);
  c111->cd(1);
  Nvtx_->Draw();
  c111->cd(2);
  ptPhoton_->Draw();
  c111->cd(3);
	nPhotons_->Draw();
  c111->cd(4);
  etaPhoton_->Draw();
  c111->cd(5);
  nJets_->Draw();
  c111->cd(6);
  phiPhoton_->Draw();


  TCanvas *c222 = new TCanvas("c222", "Efficiencies", 10, 10, 700, 700);
  c222->Divide(2,2);
  c222->cd(1);
  ptPhotonGEN_->Draw();
  gPad->SetLogy();
  c222->cd(2);
  ptPhotonREC_->Draw();
  gPad->SetLogy();
  c222->cd(3);
  TH1F *efficiency = (TH1F*) ptPhotonREC_->Clone();
  efficiency->Divide(ptPhotonGEN_);
  efficiency->Draw();
  c222->cd(4);
  DeltaRGENREC_->Draw();
  

  TCanvas *c333 = new TCanvas("c333", "Jet 1", 10, 10, 700, 700);
  gPad->SetLogy();
  c333->Divide(1,3);
  c333->cd(1);
	ptjet1_->Draw();
  c333->cd(2);
	etajet1_->Draw();
  c333->cd(3);
	phijet1_->Draw();
  
}


float deltaPhi(float phi1, float phi2) { 

  float result = phi1 - phi2;
  while (result > TMath::Pi()) result -= float(2.*TMath::Pi());
  while (result <= -TMath::Pi()) result += float(2.*TMath::Pi());
  float absresult = TMath::Abs(result);
  return absresult;
}


void Zero_Variables(){
}
