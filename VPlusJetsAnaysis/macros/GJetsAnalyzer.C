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
//			Root > .L GJetsAnalyzer.C++
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

  Float_t weight = 1;
  Int_t itype = 0;   // 0: Medium ID (80%) 
//  Int_t itype = 1;   // 0: Loose ID (90%) 

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
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

  else if (isample == 1){ 
    sprintf(outputname, "mc_GJets_HT-200To400_gammahistos_%d.root", itype);   //xsec=25690 pb * k-factor 1.23?
		nEvents = 365000;
//		nEvents = 4990000;
		xsec = 960.5;  //Matching efficiency: 0.148
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on GJets_HT-200To400. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 2){
    sprintf(outputname, "mc_GJets_HT-400ToInf_gammahistos_%d.root", itype);   //xsec=5213 pb *1.23?
		nEvents = 398804;
//		nEvents = 3995000;
		xsec = 107.5;  //Matching efficiency: 0.123
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on GJets_HT-400ToInf. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 3){
    sprintf(outputname, "mc_QCD_HT-100To250_gammahistos_%d.root", itype);   //xsec=798.3 pb *1.23?
		nEvents = 380000;
//		nEvents = 5000000;
		xsec = 1.036E7;  //Matching efficiency: 0.29
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on QCD_HT-100To250 " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 4){
    sprintf(outputname, "mc_QCD_HT-250To500_gammahistos_%d.root", itype);   //xsec=198500
		nEvents = 1.;
		xsec = 	276000.0;  //Matching efficiency: 0.23
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on QCD_HT-250To500. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 5){
    sprintf(outputname, "mc_QCD_HT-500To1000_gammahistos_%d.root", itype);   //xsec=5856
		nEvents = 368426;
//		nEvents = 4985000;
		xsec = 8426.0;  //Matching efficiency: 0.32
	  kFac = 1.;  
    // weight = 1.;                                                       // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*kFac));
    cout << "Running on QCD_HT-500To1000. " << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (isample == 6){
    sprintf(outputname, "mc_QCD_HT-1000ToInf_gammahistos_%d.root", itype);   //xsec=198500
		nEvents = 3987307;
		xsec = 204.0;  //Matching efficiency: 0.28
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
  iSelected0 = 0;
  iSelected1 = 0;
  iSelected2 = 0;
  iSelected3 = 0;
  iSelected4 = 0;
  iSelected5 = 0;
  iSelected6 = 0;
  iSelected = 0;
//  iSelectedWithWeights = 0;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

		if(jentry<2) cout << "Entering first event" << endl;
    if(jentry%100000 == 0) cout << jentry << endl;
    Zero_Variables();
/*
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
*/

    // ============ selection for photons at RECO level for control plots
		if(selRECO && nPhotons > 0 && nJets > 0 && isTriggerMatchedFamily4) { 

			// =========== add stricter selection here
			// at least one jet with pt > 50 GeV and eta < 2.5
			// and that the photon is in the barrel (photonBit |= (it->isEB()          << 0) => (*photonBit)[0]&1) con 2^0 = 1
			// and has a pt greater than 150.;

			photonPt_1 = photonPt->at(0);
			photonE_1 = photonE->at(0);
			photonEta_1 = photonEta->at(0);
			photonPhi_1 = photonPhi->at(0);			
			photonPassConversionVeto_1 = photonPassConversionVeto->at(0);
			photonPfIsoChargedHad_1 = photonPfIsoChargedHad->at(0); 
			photonPfIsoNeutralHad_1 = photonPfIsoNeutralHad->at(0); 
			photonPfIsoPhoton_1 = photonPfIsoPhoton->at(0);  
			photonPfIsoPhotons03ForCic_1 = photonPfIsoPhotons03ForCic->at(0); 
			photonPfIsoNeutrals03ForCic_1 = photonPfIsoNeutrals03ForCic->at(0); 
			photonPfIsoCharged03ForCicVtx0_1 = photonPfIsoCharged03ForCicVtx0->at(0); 
			photonPfIsoCharged03BadForCic_1 = photonPfIsoCharged03BadForCic->at(0); 
			photonPfIsoPhotons04ForCic_1 = photonPfIsoPhotons04ForCic->at(0); 
			photonPfIsoNeutrals04ForCic_1 = photonPfIsoNeutrals04ForCic->at(0);
			photonPfIsoCharged04ForCicVtx0_1 = photonPfIsoCharged04ForCicVtx0->at(0); 
			photonPfIsoCharged04BadForCic_1 = photonPfIsoCharged04BadForCic->at(0);
			photonid_sieie_1 = photonid_sieie->at(0);  
			photonid_sieip_1 = photonid_sieip->at(0); 
			photonid_etawidth_1 = photonid_etawidth->at(0); 
			photonid_phiwidth_1 = photonid_phiwidth->at(0); 
			photonid_r9_1 = photonid_r9->at(0); 
			photonid_lambdaRatio_1 = photonid_lambdaRatio->at(0); 
			photonid_s4Ratio_1 = photonid_s4Ratio->at(0);
			photonid_e25_1 = photonid_e25->at(0);
			photonid_sceta_1 = photonid_sceta->at(0); 
			photonid_ESEffSigmaRR_1 = photonid_ESEffSigmaRR->at(0);
			photonid_hadronicOverEm_1 = photonid_hadronicOverEm->at(0);
			photonid_hadronicOverEm2012_1 = photonid_hadronicOverEm2012->at(0);
			photonhcalTowerSumEtConeDR04_1 = photonhcalTowerSumEtConeDR04->at(0);
			photonecalRecHitSumEtConeDR04_1 = photonecalRecHitSumEtConeDR04->at(0);
			photonnTrkSolidConeDR04_1 = photonnTrkSolidConeDR04->at(0);
			photontrkSumPtSolidConeDR04_1 = photontrkSumPtSolidConeDR04->at(0); 
			photonnTrkHollowConeDR04_1 = photonnTrkHollowConeDR04->at(0);
			photontrkSumPtHollowConeDR04_1 = photontrkSumPtHollowConeDR04->at(0);
			//PhotonIso_1 = PhotonIso->at(0);
			photonIsoFPRCharged_1 = photonIsoFPRCharged->at(0);
			photonIsoFPRNeutral_1 = photonIsoFPRNeutral->at(0);
			photonIsoFPRPhoton_1 = photonIsoFPRPhoton->at(0);
			photonBit_1 = photonBit->at(0);

			jetPt_1 = jetPt->at(0);
			jetEta_1 = jetEta->at(0);
			jetY_1 = jetY->at(0);
			jetPhi_1 = jetPhi->at(0);           
			jetE_1 = jetE->at(0);
			
			if(nJets > 1){  
				jetPt_2 = jetPt->at(1);
				jetEta_2 = jetEta->at(1);
				jetY_2 = jetY->at(1);
				jetPhi_2 = jetPhi->at(1);           
				jetE_2 = jetE->at(1);
			}
			if(nJets > 2){  
				jetPt_3 = jetPt->at(2);
				jetEta_3 = jetEta->at(2);
				jetY_3 = jetY->at(2);
				jetPhi_3 = jetPhi->at(2);           
				jetE_3 = jetE->at(2);		
			}

			DeltaR_photon1_jet1 = deltaR(photonEta_1, photonPhi_1, jetEta_1, jetPhi_1);
			if(nJets > 1){  
			DeltaR_photon1_jet2 = deltaR(photonEta_1, photonPhi_1, jetEta_2, jetPhi_2);
			}
			if(nJets > 2){  
			DeltaR_photon1_jet3 = deltaR(photonEta_1, photonPhi_1, jetEta_3, jetPhi_3);
			}
			
			if (jetPt_1 > 50. && TMath::Abs(jetEta_1) < 2.5 && photonPt_1 > 150. && ((*photonBit)[0]&1) ) {

/*
				if(photonPassConversionVeto == 1 && 
				   photonid_hadronicOverEm2012 < 0.05 && 
				   photonid_sieie < 0.012 && 
				   photonPfIsoChargedHad < 2.6 && 
				   photonPfIsoNeutralHad < (3.5 + 0.04*(*photonPt)[0]) &&
				   photonPfIsoPhoton < (1.3 + 0.005*(*photonPt)[0])){
*/
			iSelected0++;


			//quality selection: Barrel - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
			if((*photonPassConversionVeto)[0] == 1){ 
				   iSelected1++;				 
				   if((*photonid_hadronicOverEm2012)[0] < 0.05){
				    iSelected2++;
					 	if((*photonid_sieie)[0] < 0.011){ 
					    iSelected3++;
				    	if((*photonPfIsoChargedHad)[0] < 1.5){ 
						    iSelected4++;
				   			if((*photonPfIsoNeutralHad)[0] < (1.0 + 0.04*photonPt_1)){
							    iSelected5++;
				   				if((*photonPfIsoPhoton)[0] < (0.7 + 0.005*photonPt_1)){
								    iSelected6++;
/*
			//quality selection: Barrel - Loose (90%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
			if((*photonPassConversionVeto)[0] == 1){ 
				   iSelected1++;				 
				   if((*photonid_hadronicOverEm2012)[0] < 0.05){
				    iSelected2++;
					 	if((*photonid_sieie)[0] < 0.012){ 
					    iSelected3++;
				    	if((*photonPfIsoChargedHad)[0] < 2.6){ 
						    iSelected4++;
				   			if((*photonPfIsoNeutralHad)[0] < (3.5 + 0.04*photonPt_1)){
							    iSelected5++;
				   				if((*photonPfIsoPhoton)[0] < (1.3 + 0.005*photonPt_1)){
								    iSelected6++;
*/
				iSelected++;

				Nvtx_->Fill(nVtx, weight);
				nPhotons_->Fill(nPhotons, weight);
				isPhotonlead_->Fill(isPhotonlead, weight);
//				photonPt_1_->Fill((*photonPt)[0], weight);
				photonPt_1_->Fill(photonPt_1, weight);
				photonE_1_->Fill(photonE_1, weight);
				photonEta_1_->Fill(photonEta_1, weight);
				photonPhi_1_->Fill(photonPhi_1, weight);
				photonBit_1_->Fill(photonBit_1, weight);
				photonPassConversionVeto_1_->Fill(photonPassConversionVeto_1, weight);
				photonPfIsoChargedHad_1_->Fill(photonPfIsoChargedHad_1, weight);
				photonPfIsoNeutralHad_1_->Fill(photonPfIsoNeutralHad_1, weight);
				photonPfIsoPhoton_1_->Fill(photonPfIsoPhoton_1, weight);
				photonPfIsoPhotons03ForCic_1_->Fill(photonPfIsoPhotons03ForCic_1, weight);
				photonPfIsoNeutrals03ForCic_1_->Fill(photonPfIsoNeutrals03ForCic_1, weight);
				photonPfIsoCharged03ForCicVtx0_1_->Fill(photonPfIsoCharged03ForCicVtx0_1, weight);
				photonPfIsoCharged03BadForCic_1_->Fill(photonPfIsoCharged03BadForCic_1, weight);
				photonPfIsoPhotons04ForCic_1_->Fill(photonPfIsoPhotons04ForCic_1, weight);
				photonPfIsoNeutrals04ForCic_1_->Fill(photonPfIsoNeutrals04ForCic_1, weight);
				photonPfIsoCharged04ForCicVtx0_1_->Fill(photonPfIsoCharged04ForCicVtx0_1, weight);
				photonPfIsoCharged04BadForCic_1_->Fill(photonPfIsoCharged04BadForCic_1, weight);
				photonid_sieie_1_->Fill(photonid_sieie_1, weight);
				photonid_sieip_1_->Fill(photonid_sieip_1, weight);
				photonid_etawidth_1_->Fill(photonid_etawidth_1, weight);
				photonid_phiwidth_1_->Fill(photonid_phiwidth_1, weight);
				photonid_r9_1_->Fill(photonid_r9_1, weight);
				photonid_lambdaRatio_1_->Fill(photonid_lambdaRatio_1, weight);
				photonid_s4Ratio_1_->Fill(photonid_s4Ratio_1, weight);
				photonid_e25_1_->Fill(photonid_e25_1, weight);
				photonid_sceta_1_->Fill(photonid_sceta_1, weight);
				photonid_ESEffSigmaRR_1_->Fill(photonid_ESEffSigmaRR_1, weight);
				photonid_hadronicOverEm_1_->Fill(photonid_hadronicOverEm_1, weight);
				photonid_hadronicOverEm2012_1_->Fill(photonid_hadronicOverEm2012_1, weight);
				photonhcalTowerSumEtConeDR04_1_->Fill(photonhcalTowerSumEtConeDR04_1, weight);
				photonecalRecHitSumEtConeDR04_1_->Fill(photonecalRecHitSumEtConeDR04_1, weight);
				photonnTrkSolidConeDR04_1_->Fill(photonnTrkSolidConeDR04_1, weight);
				photontrkSumPtSolidConeDR04_1_->Fill(photontrkSumPtSolidConeDR04_1, weight);
				photonnTrkHollowConeDR04_1_->Fill(photonnTrkHollowConeDR04_1, weight);
				photontrkSumPtHollowConeDR04_1_->Fill(photontrkSumPtHollowConeDR04_1, weight);
				//PhotonIso_1->Fill(PhotonIso_1, weight);
				photonIsoFPRCharged_1_->Fill(photonIsoFPRCharged_1, weight);
				photonIsoFPRNeutral_1_->Fill(photonIsoFPRNeutral_1, weight);
				photonIsoFPRPhoton_1_->Fill(photonIsoFPRPhoton_1, weight);

				nJets_->Fill(nJets, weight);
				
				jetPt_1_->Fill(jetPt_1, weight);
				jetEta_1_->Fill(jetEta_1, weight);
				jetY_1_->Fill(jetY_1, weight);
				jetPhi_1_->Fill(jetPhi_1, weight);
				jetE_1_->Fill(jetE_1, weight);
				
				jetPt_2_->Fill(jetPt_2, weight);
				jetEta_2_->Fill(jetEta_2, weight);
				jetY_2_->Fill(jetY_2, weight);
				jetPhi_2_->Fill(jetPhi_2, weight);
				jetE_2_->Fill(jetE_2, weight);

				jetPt_3_->Fill(jetPt_3, weight);
				jetEta_3_->Fill(jetEta_3, weight);
				jetY_3_->Fill(jetY_3, weight);
				jetPhi_3_->Fill(jetPhi_3, weight);
				jetE_3_->Fill(jetE_3, weight);

				DeltaR_photon1_jet1_->Fill(DeltaR_photon1_jet1, weight);
				DeltaR_photon1_jet2_->Fill(DeltaR_photon1_jet2, weight);
				DeltaR_photon1_jet3_->Fill(DeltaR_photon1_jet3, weight);
				
//				} // end quality selection
									}
								}
							}
						}
					}
				} // end quality selection
			} // end selection with 1 jet

      // if (Cut(ientry) < 0) continue;
		} // end if preselection
	} // end loop on entries

	// ====================================terminate and plot
	cout << "Number of selected events 0, unweighted = " << iSelected0 << endl;
	cout << "Number of selected events 1, unweighted = " << iSelected1 << endl;
	cout << "Number of selected events 2, unweighted = " << iSelected2 << endl;
	cout << "Number of selected events 3, unweighted = " << iSelected3 << endl;
	cout << "Number of selected events 4, unweighted = " << iSelected4 << endl;
	cout << "Number of selected events 5, unweighted = " << iSelected5 << endl;
	cout << "Number of selected events 6, unweighted = " << iSelected6 << endl;

	cout << "Number of selected events, unweighted = " << iSelected << endl;
	cout << "Number of selected events Only one type and ptjet1 > 50, weighted = " << iSelected*weight << endl;
 
	fhistos->Write();
	Plot_Histos();  
}


// ----- methods ----------------

void Book_Histos(){

	cout << "Booking histograms... " << endl;
	// book the histograms
/*
  ptPhotonGEN_= new TH1F("ptPhotonGEN","p_{T} of the GEN photon", 2, 150., 200.);
  ptPhotonREC_= new TH1F("ptPhotonREC_","p_{T} of the REC photon (GEN selection)",2,150.,200.);
  DeltaRGENREC_=new TH1F("DeltaRGENREC_","DeltaR Gen-REC photon", 50, 0., 0.01);
*/
  Nvtx_ = new TH1F("Nvtx_","Number of vertices ", 50, 0, 50);

	nPhotons_ = new TH1F("nPhotons_","N Photons ", 10, 0, 10);
	isPhotonlead_ = new TH1F("isPhotonlead_", "isPhotonlead", 10, -2, 2);
	photonPt_1_ = new TH1F("photonPt_1","Photon p_{T} ", 100, 0., 1000.);
	photonE_1_ = new TH1F("photonE_1","Photon E ", 100, 0., 1000.);
	photonEta_1_ = new TH1F("photonEta_1","Photon #eta ", 100, -3, 3.);
	photonPhi_1_ = new TH1F("photonPhi_1","Photon #varphi ", 100, -3.1416, 3.1416);
	photonBit_1_ = new TH1F("photonBit_1","Photon bit ", 100, 0., 1000.);
	photonPassConversionVeto_1_ = new TH1F("photonPassConversionVeto_1","photonPassConversionVeto ", 10, -2, 2);
	photonPfIsoChargedHad_1_ = new TH1F("photonPfIsoChargedHad_1", "photon PfIsoChargedHad", 100, 0, 5);
	photonPfIsoNeutralHad_1_ = new TH1F("photonPfIsoNeutralHad_1", "photon PfIsoNeutralHad", 50, 0, 50);
	photonPfIsoPhoton_1_ = new TH1F("photonPfIsoPhoton_1", "photon PfIsoPhoton",30, 0, 15);
  photonPfIsoPhotons03ForCic_1_ = new TH1F("photonPfIsoPhotons03ForCic_1", "photon PfIsoPhotons03ForCic", 100, 0, 100);
	photonPfIsoNeutrals03ForCic_1_ = new TH1F("photonPfIsoNeutrals03ForCic_1","photon PfIsoNeutrals03ForCic", 50, 0, 50);
	photonPfIsoCharged03ForCicVtx0_1_ = new TH1F("photonPfIsoCharged03ForCicVtx0_1", "photon PfIsoCharged03ForCicVtx0", 100, 0, 100);
	photonPfIsoCharged03BadForCic_1_ = new TH1F("photonPfIsoCharged03BadForCic_1", "photon PfIsoCharged03BadForCic", 100, 0, 100);
	photonPfIsoPhotons04ForCic_1_ = new TH1F("photonPfIsoPhotons04ForCic_1", "photon PfIsoPhotons04ForCic", 100, 0, 100);
	photonPfIsoNeutrals04ForCic_1_ = new TH1F("photonPfIsoNeutrals04ForCic_1", "photon PfIsoNeutrals04ForCic", 50, 0, 50);
	photonPfIsoCharged04ForCicVtx0_1_ = new TH1F("photonPfIsoCharged04ForCicVtx0_1", "photon PfIsoCharged04ForCicVtx0", 100, 0, 100);
	photonPfIsoCharged04BadForCic_1_ = new TH1F("photonPfIsoCharged04BadForCic_1", "photonPfIsoCharged04BadForCic", 100, 0, 100);
	photonid_sieie_1_ = new TH1F("photonid_sieie_1", "photon ID: #sigma_{i#etai#eta}", 20, 0., 0.02);
	photonid_sieip_1_ = new TH1F("photonid_sieip_1", "photon ID: #sigma_{i#etai#varphi}", 20, 0, 0.02);
	photonid_etawidth_1_ = new TH1F("photonid_etawidth_1", "photon ID: #eta width", 30, 0, 0.03);
	photonid_phiwidth_1_ = new TH1F("photonid_phiwidth_1", "photon ID: #varphi width", 50, 0, 0.2);
	photonid_r9_1_ = new TH1F("photonid_r9_1", "photon ID: r9", 50, 0, 1);
	photonid_lambdaRatio_1_ = new TH1F("photonid_lambdaRatio_1", "photon ID: #lambda Ratio", 50, 0, 1);
	photonid_s4Ratio_1_ = new TH1F("photonid_s4Ratio_1","photon ID: s4 Ratio", 50, 0, 1);
	photonid_e25_1_ = new TH1F("photonid_e25_1", "photon ID: #rho25", 50, 0, 1000);
	photonid_sceta_1_ = new TH1F("photonid_sceta_1", "photon ID: SC #eta", 100, -3, 3);
	photonid_ESEffSigmaRR_1_ = new TH1F("photonid_ESEffSigmaRR_1", "photon ID: ESEffSigmaRR", 10, 0, 1);
	photonid_hadronicOverEm_1_ = new TH1F("photonid_hadronicOverEm_1", "photon ID: hadronicOverEm", 100, 0, 1);
	photonid_hadronicOverEm2012_1_ = new TH1F("photonid_hadronicOverEm2012_1", "photon ID: hadronicOverEm2012", 100, 0, 1);
	photonhcalTowerSumEtConeDR04_1_ = new TH1F("photonhcalTowerSumEtConeDR04_1","photon hcalTowerSumEtConeDR04", 100, 0, 100);
	photonecalRecHitSumEtConeDR04_1_ = new TH1F("photonecalRecHitSumEtConeDR04_1", "photon ecalRecHitSumEtConeDR04", 100, 0, 100);
	photonnTrkSolidConeDR04_1_ = new TH1F("photonnTrkSolidConeDR04_1", "photon nTrkSolidConeDR04", 30, 0, 30);
	photontrkSumPtSolidConeDR04_1_ = new TH1F("photontrkSumPtSolidConeDR04_1","photon trkSumPtSolidConeDR04", 100, 0, 500);
	photonnTrkHollowConeDR04_1_ = new TH1F("photonnTrkHollowConeDR04_1", "photon nTrkHollowConeDR04", 30, 0, 30) ;
	photontrkSumPtHollowConeDR04_1_ = new TH1F("photontrkSumPtHollowConeDR04", "photon trkSumPtHollowConeDR04", 100, 0, 100);
	
	//PhotonIso
	photonIsoFPRCharged_1_ = new TH1F("photonIsoFPRCharged_1", "photon IsoFPRCharged", 40, 0, 40); //with FOOT PRINT REMOVAL FROM MP
	photonIsoFPRNeutral_1_ = new TH1F("photonIsoFPRNeutral_1", "photon IsoFPRNeutral", 40, 0, 20);
	photonIsoFPRPhoton_1_ = new TH1F("photonIsoFPRPhoton_1", "photon IsoFPRPhoton", 40, 0, 40);
//jetPhotonDPhi_1_;

	nJets_ = new TH1F("nJets_","N Jets ", 10, 0, 10);

	jetPt_1_ = new TH1F("jetPt_1","Jet 1 p_{T} ", 100, 0., 1000.);
	jetEta_1_ = new TH1F("jetEta_1","Jet 1 #eta ", 100, -3., 3.);
	jetY_1_ = new TH1F("jetY_1", "jet 1 Y",100, -3., 3.); 
	jetPhi_1_ = new TH1F("jetPhi_1","Jet 1 #varphi ", 100, -3.1416, 3.1416);
	jetE_1_ = new TH1F("jetE_1", "jet 1 E", 100, 0., 1000.);

	jetPt_2_ = new TH1F("jetPt_2","Jet 2 p_{T} ", 100, 0., 1000.);
	jetEta_2_ = new TH1F("jetEta_2","Jet 2 #eta ", 100, -3., 3.);
	jetY_2_ = new TH1F("jetY_2", "jet 2 Y",100, -3., 3.); 
	jetPhi_2_ = new TH1F("jetPhi_2","Jet 2 #varphi ", 100, -3.1416, 3.1416);
	jetE_2_ = new TH1F("jetE_2", "jet 2 E", 100, 0., 1000.);

	jetPt_3_ = new TH1F("jetPt_3","Jet 3 p_{T} ", 100, 0., 1000.);
	jetEta_3_ = new TH1F("jetEta_3","Jet 3 #eta ", 100, -3., 3.);
	jetY_3_ = new TH1F("jetY_3", "jet 3 Y",100, -3., 3.); 
	jetPhi_3_ = new TH1F("jetPhi_3","Jet 3 #varphi ", 100, -3.1416, 3.1416);
	jetE_3_ = new TH1F("jetE_3", "jet 3 E", 100, 0., 1000.);

	DeltaR_photon1_jet1_ = new TH1F("DeltaR_photon1_jet1_","#DeltaR photon1-jet1", 100, 0, 2);
	DeltaR_photon1_jet2_ = new TH1F("DeltaR_photon1_jet2_","#DeltaR photon1-jet2", 100, 0, 2);
	DeltaR_photon1_jet3_ = new TH1F("DeltaR_photon1_jet3_","#DeltaR photon1-jet3", 100, 0, 2);

//  ptPhoton_->Sumw2();
//  etaPhoton_->Sumw2();
//  phiPhoton_->Sumw2();

	cout << "...booking histograms finished." << endl;
}


void Plot_Histos(){

  // plot few histograms at the end, for check
  cout << "Plot, quick check " << endl;

  gStyle->SetOptStat(1111111);

  TCanvas *c01 = new TCanvas("c01", "photon kinematics", 10, 10, 700, 700);
  gPad->SetLogy();
  c01->Divide(2,3);
  c01->cd(1);
  Nvtx_->Draw();
  c01->cd(2);
	nPhotons_->Draw();
  c01->cd(3);
	photonPt_1_->Draw();
  c01->cd(4);
  photonE_1_->Draw();
  c01->cd(5);
  photonEta_1_->Draw();
  c01->cd(6);
  photonPhi_1_->Draw();

/*
  TCanvas *c02 = new TCanvas("c02", "Efficiencies", 10, 10, 700, 700);
  c02->Divide(2,2);
  c02->cd(1);
  ptPhotonGEN_->Draw();
  gPad->SetLogy();
  c02->cd(2);
  ptPhotonREC_->Draw();
  gPad->SetLogy();
  c02->cd(3);
  TH1F *efficiency = (TH1F*) ptPhotonREC_->Clone();
  efficiency->Divide(ptPhotonGEN_);
  efficiency->Draw();
  c02->cd(4);
  DeltaRGENREC_->Draw();
*/
  TCanvas *c02 = new TCanvas("c02", "photon Isolation", 10, 10, 700, 700);
  gPad->SetLogy();
  c02->Divide(2,2);
  c02->cd(1);
  photonPassConversionVeto_1_->Draw();
  c02->cd(2);
	photonPfIsoChargedHad_1_->Draw();
  c02->cd(3);
	photonPfIsoNeutralHad_1_->Draw();
  c02->cd(4);
  photonPfIsoPhoton_1_->Draw();


  TCanvas *c03 = new TCanvas("c03", "photon Isolation cone 03 for Cic", 10, 10, 700, 700);
  gPad->SetLogy();
  c03->Divide(2,2);
  c03->cd(1);
  photonPfIsoPhotons03ForCic_1_->Draw();
  c03->cd(2);
	photonPfIsoNeutrals03ForCic_1_->Draw();
  c03->cd(3);
	photonPfIsoCharged03ForCicVtx0_1_->Draw();
  c03->cd(4);
	photonPfIsoCharged03BadForCic_1_->Draw();


  TCanvas *c04 = new TCanvas("c04", "photon Isolation cone 04 for Cic", 10, 10, 700, 700);
  gPad->SetLogy();
  c04->Divide(2,2);
  c04->cd(1);
  photonPfIsoPhotons04ForCic_1_->Draw();
  c04->cd(2);
	photonPfIsoNeutrals04ForCic_1_->Draw();
  c04->cd(3);
	photonPfIsoCharged04ForCicVtx0_1_->Draw();
  c04->cd(4);
	photonPfIsoCharged04BadForCic_1_->Draw();


  TCanvas *c05 = new TCanvas("c05", "photon ID", 10, 10, 700, 700);
  gPad->SetLogy();
  c05->Divide(3,4);
  c05->cd(1);
	photonid_sieie_1_->Draw();
  c05->cd(2);
	photonid_sieip_1_->Draw();
  c05->cd(3);
	photonid_etawidth_1_->Draw();
  c05->cd(4);
	photonid_phiwidth_1_->Draw();
  c05->cd(5);
 	photonid_r9_1_->Draw();
  c05->cd(6);
  photonid_lambdaRatio_1_->Draw();
  c05->cd(7);
	photonid_s4Ratio_1_->Draw();
  c05->cd(8);
  photonid_e25_1_->Draw();
  c05->cd(9);
  photonid_sceta_1_->Draw();
  c05->cd(10);
  photonid_ESEffSigmaRR_1_->Draw();
  c05->cd(11);
  photonid_hadronicOverEm_1_->Draw();
  c05->cd(12);
  photonid_hadronicOverEm2012_1_->Draw();


  TCanvas *c06 = new TCanvas("c06", "photon E_{T}-p_{T}", 10, 10, 700, 700);
  gPad->SetLogy();
  c06->Divide(3,2);
  c06->cd(1);
	photonhcalTowerSumEtConeDR04_1_->Draw();
  c06->cd(2);
	photonecalRecHitSumEtConeDR04_1_->Draw();
  c06->cd(3);
	photonnTrkSolidConeDR04_1_->Draw();
  c06->cd(4);
	photontrkSumPtSolidConeDR04_1_->Draw();
  c06->cd(5);
 	photonnTrkHollowConeDR04_1_->Draw();
  c06->cd(6);
  photontrkSumPtHollowConeDR04_1_->Draw();


  TCanvas *c07 = new TCanvas("c07", "photon Isolation FPR", 10, 10, 700, 700);
  gPad->SetLogy();
  c07->Divide(3,1);
  c07->cd(1);
	photonIsoFPRCharged_1_->Draw(); 
  c07->cd(2);
	photonIsoFPRNeutral_1_->Draw(); 
  c07->cd(3);
	photonIsoFPRPhoton_1_->Draw();


  TCanvas *c08 = new TCanvas("c08", "Jet 1 kinematics", 10, 10, 700, 700);
  gPad->SetLogy();
  c08->Divide(3,2);
  c08->cd(1);
	nJets_->Draw(); 
  c08->cd(2);
	jetPt_1_->Draw(); 
  c08->cd(3);
	jetEta_1_->Draw();
  c08->cd(4);
  jetY_1_->Draw();
  c08->cd(5);
	jetPhi_1_->Draw();
  c08->cd(6);
	jetE_1_->Draw();

  TCanvas *c09 = new TCanvas("c09", "Jet 2 kinematics", 10, 10, 700, 700);
  gPad->SetLogy();
  c09->Divide(3,2);
  c09->cd(1);
	nJets_->Draw(); 
  c09->cd(2);
	jetPt_2_->Draw(); 
  c09->cd(3);
	jetEta_2_->Draw();
  c09->cd(4);
  jetY_2_->Draw();
  c09->cd(5);
	jetPhi_2_->Draw();
  c09->cd(6);
	jetE_2_->Draw();

  TCanvas *c10 = new TCanvas("c10", "Jet 3 kinematics", 10, 10, 700, 700);
  gPad->SetLogy();
  c10->Divide(3,2);
  c10->cd(1);
	nJets_->Draw(); 
  c10->cd(2);
	jetPt_3_->Draw(); 
  c10->cd(3);
	jetEta_3_->Draw();
  c10->cd(4);
  jetY_3_->Draw();
  c10->cd(5);
	jetPhi_3_->Draw();
  c10->cd(6);
	jetE_3_->Draw();

  TCanvas *c11 = new TCanvas("c11", "Delta R photon1-jets", 10, 10, 700, 700);
  gPad->SetLogy();
  c11->Divide(3,1);
  c11->cd(1);
	DeltaR_photon1_jet1_->Draw();
  c11->cd(2);
	DeltaR_photon1_jet2_->Draw();
  c11->cd(3);
	DeltaR_photon1_jet3_->Draw();	
  }


float deltaPhi(float phi1, float phi2) { 

  float result = phi1 - phi2;
  while (result > TMath::Pi()) result -= float(2.*TMath::Pi());
  while (result <= -TMath::Pi()) result += float(2.*TMath::Pi());
  float absresult = TMath::Abs(result);
  return absresult;
}


float deltaR(float eta1, float eta2, float phi1, float phi2) { 

	float result = sqrt(pow(eta1 - eta2, 2) + pow(phi1 - phi2, 2));
  return result;
}


void Zero_Variables(){
}
