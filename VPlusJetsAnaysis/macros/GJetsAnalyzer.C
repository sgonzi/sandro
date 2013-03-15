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
//#ifdef __MAKECINT__
//#pragma link C++ class vector<float>+;
//#endif

//		In a ROOT session, you can do:
//			Root > .L GJetsAnalyzer.C+
//			Root > GJetsAnalyzer t;
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


void GJetsAnalyzer::Loop(){

  Int_t plothistos = 0;
  Int_t textfile = 1;

  Float_t weight = 1; 
	Float_t weight_withPU = 1;
  Int_t itype = 2;   // identifica histo con analisi diverse 

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
	
	string sample = "";
	string histos = "_histos_%d";
	string report = "_report_%d";
	string root = ".root";
	string txt = ".txt";
	
	cout << "mysample is " << mysample << endl;

// test -----------------------------------------------------------------
  if (mysample == 0){
  	sample = "TEST";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout << "Weight is " << weight << endl;
  }

// data -----------------------------------------------------------------
  else if (mysample == 1) {
  	sample = "DATA_Run2012A-13Jul2012";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }
  
  else if (mysample == 2) {
  	sample = "DATA_Run2012A-recover-06Aug2012";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

  else if (mysample == 3) {
  	sample = "DATA_Run2012B-13Jul2012";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

  else if (mysample == 4) {
  	sample = "DATA_Run2012C-24Aug2012";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

  else if (mysample == 5) {
  	sample = "DATA_Run2012C-EcalRecover_11Dec2012";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

  else if (mysample == 6) {
  	sample = "DATA_Run2012C-PromptReco";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

  else if (mysample == 7) {
  	sample = "DATA_Run2012D-PromptReco";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
    weight = 1.;
    cout << "Running on " << sample << endl;
    cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
  }

// MC signal GJets_HT-xToy ----------------------------------------------
  else if (mysample == 11){ 
  	sample = "MC_GJets_HT-200To400";
    sprintf(outputname, (sample+histos+root).c_str(), itype);   
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 41872600;
//		xsec = 107.5;
		xsec = 105.418;	//da cambiare
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 34611322;
//		xsec = 	4250.0;
		xsec = 	4245.29; //da cambiare
		FiltEff = 0.131;		
	  kFac = 1.;  
    // weight = 1.; // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
    cout << "Running on " << sample << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (mysample == 26){
  	sample = "MC_QCD_Pt_350_EMEnriched";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 34080562;
//		xsec = 	810.0;
		xsec = 	810.454; //da cambiare
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 1998152 ;
		xsec = 	7.424E7;
		FiltEff = 0.00225;		
	  kFac = 1.;  
    // weight = 1.; // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
    cout << "Running on " << sample << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (mysample == 33){
  	sample = "MC_QCD_Pt_80_170_BCtoE";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 1948112;
		xsec = 	30980.0; 
		FiltEff = 0.0204;		
	  kFac = 1.;  
    // weight = 1.; // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
    cout << "Running on " << sample << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (mysample == 35){
  	sample = "MC_QCD_Pt_250_350_BCtoE";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 2026521 ;
		xsec = 	4250.0;
		FiltEff = 0.0243;		
	  kFac = 1.;  
    // weight = 1.; // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
    cout << "Running on " << sample << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (mysample == 36){
  	sample = "MC_QCD_Pt_350_BCtoE";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 1948532 ;
		xsec = 	811.0;
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
    sprintf(outputname, (sample+histos+root).c_str(), itype); 
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
		nEvents = 27062078;
//		xsec = 	276000.0;
		xsec = 	276000.0; //da cambiare
		FiltEff = 1.;		
	  kFac = 1.;  
    // weight = 1.; // temporary weight=1 for eff. calculation    
    weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
    cout << "Running on " << sample << endl;
    cout << "Weight is " << weight << endl;
  }

  else if (mysample == 43){
  	sample = "MC_QCD_HT-500To1000";
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
    sprintf(outputname, (sample+histos+root).c_str(), itype);
    sprintf(textname, (sample+report+txt).c_str(), itype);
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
  iSelected5 = 0;
  iSelected6 = 0;
  iSelected7 = 0;
  
  iSelectedWithWeights0 = 0;
  iSelectedWithWeights1 = 0;
  iSelectedWithWeights2 = 0;
  iSelectedWithWeights3 = 0;
  iSelectedWithWeights4 = 0;
  iSelectedWithWeights5 = 0;
  iSelectedWithWeights6 = 0;
  iSelectedWithWeights7 = 0;
  
  iSelected0_cl = 0;
  iSelected1_cl = 0;
  iSelected2_cl = 0;
  iSelected3_cl = 0;
  iSelected4_cl = 0;
  iSelected5_cl = 0;
  iSelected6_cl = 0;
  iSelected7_cl = 0;

  iSelectedWithWeights0_cl = 0;
  iSelectedWithWeights1_cl = 0;
  iSelectedWithWeights2_cl = 0;
  iSelectedWithWeights3_cl = 0;
  iSelectedWithWeights4_cl = 0;
  iSelectedWithWeights5_cl = 0;
  iSelectedWithWeights6_cl = 0;
  iSelectedWithWeights7_cl = 0;

//  iSelectedWithWeights = 0;

	Long64_t nentries = fChain->GetEntriesFast();
//  Long64_t nentries = 1000;
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
//cout << "-----inizio-------" << endl;
//cout << "qui 4" << endl;

		// ---- objects position ----------------------------------------------
		if(nPhotons > 0 && nJets > 0 && isTriggerMatchedFamily4 /*da cancellare*/) {
	
			// ---- photons
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

			photonIsoFPRCharged_1 = photonIsoFPRCharged->at(0);
			photonIsoFPRNeutral_1 = photonIsoFPRNeutral->at(0);
			photonIsoFPRPhoton_1 = photonIsoFPRPhoton->at(0);
			photonBit_1 = photonBit->at(0);

			// ---- jets

			jetPt_1 = jetPt->at(0);
			jetEta_1 = jetEta->at(0);
			jetPhi_1 = jetPhi->at(0);           
			jetE_1 = jetE->at(0);
		
			if(nJets > 1){  
				jetPt_2 = jetPt->at(1);
				jetEta_2 = jetEta->at(1);
				jetPhi_2 = jetPhi->at(1);           
				jetE_2 = jetE->at(1);
			}
				
			if(nJets > 2){  
				jetPt_3 = jetPt->at(2);
				jetEta_3 = jetEta->at(2);
				jetPhi_3 = jetPhi->at(2);           
				jetE_3 = jetE->at(2);		
			}

     	// ---- angular  
			DeltaR_photon1_jet1 = deltaR(photonEta_1, photonPhi_1, jetEta_1, jetPhi_1);
			DeltaPhi_photon1_jet1 = deltaPhi(photonPhi_1, jetPhi_1);

			if(nJets > 1){  
				DeltaR_photon1_jet2 = deltaR(photonEta_1, photonPhi_1, jetEta_2, jetPhi_2);
				DeltaEta_jet1_jet2 = deltaEta(jetEta_1, jetEta_2);
				DeltaPhi_jet1_jet2 = deltaPhi(jetPhi_1, jetPhi_2);
			}
			if(nJets > 2){  
				DeltaR_photon1_jet3 = deltaR(photonEta_1, photonPhi_1, jetEta_3, jetPhi_3);
			}

     	// ---- other  				
			HT = 0;
			for(unsigned int j = 0; j < jetPt->size(); j++) {
     	  HT += jetPt->at(j);
			}
			
			// ---- clean
			nJets_cl = 0;

			for (unsigned int iJetar = 0; iJetar < jetVeto->size(); iJetar++) {
				bool close = (jetVeto->at(iJetar))&4;
//				cout << "close(" << iJetar << ") = " << close << endl;
				if (close!=1){
//cout << "jetPt->at(" << iJetar << ") = " << jetPt->at(iJetar) << endl;
					jetPt_cl.push_back(jetPt->at(iJetar));
					jetEta_cl.push_back(jetEta->at(iJetar));
					jetPhi_cl.push_back(jetPhi->at(iJetar));
					jetE_cl.push_back(jetE->at(iJetar));
					nJets_cl += 1;
				}
			}	
			
			// ---- jets clean
			if(nJets_cl > 0){ 
				jetPt_1_cl = jetPt_cl.at(0);
				jetEta_1_cl = jetEta_cl.at(0);
				jetPhi_1_cl = jetPhi_cl.at(0);  
				jetE_1_cl = jetE_cl.at(0);

				if(nJets_cl > 1){  
					jetPt_2_cl = jetPt_cl.at(1);
					jetEta_2_cl = jetEta_cl.at(1);
					jetPhi_2_cl = jetPhi_cl.at(1);           
					jetE_2_cl = jetE_cl.at(1);
				}
				
				if(nJets_cl > 2){  
					jetPt_3_cl = jetPt_cl.at(2);
					jetEta_3_cl = jetEta_cl.at(2);
					jetPhi_3_cl = jetPhi_cl.at(2);           
					jetE_3_cl = jetE_cl.at(2);		
				}

     		// ---- angular clean
				DeltaR_photon1_jet1_cl = deltaR(photonEta_1, photonPhi_1, jetEta_1_cl, jetPhi_1_cl);
				DeltaPhi_photon1_jet1_cl = deltaPhi(photonPhi_1, jetPhi_1_cl);

				if(nJets_cl > 1){  
					DeltaR_photon1_jet2_cl = deltaR(photonEta_1, photonPhi_1, jetEta_2_cl, jetPhi_2_cl);
					DeltaEta_jet1_jet2_cl = deltaEta(jetEta_1_cl, jetEta_2_cl);
					DeltaPhi_jet1_jet2_cl = deltaPhi(jetPhi_1_cl, jetPhi_2_cl);
				}
				if(nJets_cl > 2){  
					DeltaR_photon1_jet3_cl = deltaR(photonEta_1, photonPhi_1, jetEta_3_cl, jetPhi_3_cl);
				}

     		// ---- other clean			
				HT_cl = 0;
				for(unsigned int j = 0; j < jetPt_cl.size(); j++) {
     	  	HT_cl += jetPt_cl.at(j);
				}

     	  jetPt_cl.clear();
     	  jetEta_cl.clear(); 
				jetPhi_cl.clear();
				jetE_cl.clear();	
			}

		 	// ======= weight
			if(mysample < 8){  //data
				weight_withPU = 1.;
			}
			else{   // MC         
				weight_withPU = PUWeight*Lumi_t/1000.;
			}
		  weight_withPU_r = weight_withPU;

		}	// end of objects position 
					
		// =========== Analysis selection
		// at least one jet with pt > 50 GeV and eta < 2.5
		// and that the photon is in the barrel (photonBit |= (it->isEB() << 0) => (*photonBit)[0]&1) con 2^0 = 1
		// and has a pt greater than 150.;
		if(nPhotons > 0 && nJets > 0) { 
			
			iSelected0++;
			iSelectedWithWeights0 = iSelectedWithWeights0 + weight_withPU;

			if (jetPt_1 > 50. && TMath::Abs(jetEta_1) < 2.5 && photonPt_1 > 160. && (photonBit_1&1) && isTriggerMatchedFamily4) {

				iSelected1++;
				iSelectedWithWeights1 = iSelectedWithWeights1 + weight_withPU;

				// quality selection: Barrel - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
				if((*photonPassConversionVeto)[0] == 1){ 
				 	iSelected2++;				 
					iSelectedWithWeights2 = iSelectedWithWeights2 + weight_withPU;
				 	 if((*photonid_hadronicOverEm2012)[0] < 0.05){
				 	  iSelected3++;
  					iSelectedWithWeights3 = iSelectedWithWeights3 + weight_withPU;
					 	if((*photonid_sieie)[0] < 0.011){ 
					    iSelected4++;
    					iSelectedWithWeights4 = iSelectedWithWeights4 + weight_withPU;
				 	  	if((*photonPfIsoChargedHad)[0] < 1.5){ 
						    iSelected5++;
	    					iSelectedWithWeights5 = iSelectedWithWeights5 + weight_withPU;
				 	 			if((*photonPfIsoNeutralHad)[0] < (1.0 + 0.04*photonPt_1)){
							    iSelected6++;
		    					iSelectedWithWeights6 = iSelectedWithWeights6 + weight_withPU;
				 	 				if((*photonPfIsoPhoton)[0] < (0.7 + 0.005*photonPt_1)){
								    iSelected7++;
										iSelectedWithWeights7 = iSelectedWithWeights7 + weight_withPU;
										Nvtx_->Fill(nVtx, weight_withPU);
										
										nPhotons_->Fill(nPhotons, weight_withPU);
//									photonPt_1_->Fill((*photonPt)[0], weight_withPU);
										photonPt_1_->Fill(photonPt_1, weight_withPU);
										photonE_1_->Fill(photonE_1, weight_withPU);
										photonEta_1_->Fill(photonEta_1, weight_withPU);
										photonPhi_1_->Fill(photonPhi_1, weight_withPU);
										photonBit_1_->Fill(photonBit_1, weight_withPU);
										photonPassConversionVeto_1_->Fill(photonPassConversionVeto_1, weight_withPU);
										photonPfIsoChargedHad_1_->Fill(photonPfIsoChargedHad_1, weight_withPU);
										photonPfIsoNeutralHad_1_->Fill(photonPfIsoNeutralHad_1, weight_withPU);
										photonPfIsoPhoton_1_->Fill(photonPfIsoPhoton_1, weight_withPU);
										photonPfIsoPhotons03ForCic_1_->Fill(photonPfIsoPhotons03ForCic_1, weight_withPU);
										photonPfIsoNeutrals03ForCic_1_->Fill(photonPfIsoNeutrals03ForCic_1, weight_withPU);
										photonPfIsoCharged03ForCicVtx0_1_->Fill(photonPfIsoCharged03ForCicVtx0_1, weight_withPU);
										photonPfIsoCharged03BadForCic_1_->Fill(photonPfIsoCharged03BadForCic_1, weight_withPU);
										photonPfIsoPhotons04ForCic_1_->Fill(photonPfIsoPhotons04ForCic_1, weight_withPU);
										photonPfIsoNeutrals04ForCic_1_->Fill(photonPfIsoNeutrals04ForCic_1, weight_withPU);
										photonPfIsoCharged04ForCicVtx0_1_->Fill(photonPfIsoCharged04ForCicVtx0_1, weight_withPU);
										photonPfIsoCharged04BadForCic_1_->Fill(photonPfIsoCharged04BadForCic_1, weight_withPU);
										photonid_sieie_1_->Fill(photonid_sieie_1, weight_withPU);
										photonid_sieip_1_->Fill(photonid_sieip_1, weight_withPU);
										photonid_etawidth_1_->Fill(photonid_etawidth_1, weight_withPU);
										photonid_phiwidth_1_->Fill(photonid_phiwidth_1, weight_withPU);
										photonid_r9_1_->Fill(photonid_r9_1, weight_withPU);
										photonid_lambdaRatio_1_->Fill(photonid_lambdaRatio_1, weight_withPU);
										photonid_s4Ratio_1_->Fill(photonid_s4Ratio_1, weight_withPU);
										photonid_e25_1_->Fill(photonid_e25_1, weight_withPU);
										photonid_sceta_1_->Fill(photonid_sceta_1, weight_withPU);
										photonid_ESEffSigmaRR_1_->Fill(photonid_ESEffSigmaRR_1, weight_withPU);
										photonid_hadronicOverEm_1_->Fill(photonid_hadronicOverEm_1, weight_withPU);
										photonid_hadronicOverEm2012_1_->Fill(photonid_hadronicOverEm2012_1, weight_withPU);
										photonhcalTowerSumEtConeDR04_1_->Fill(photonhcalTowerSumEtConeDR04_1, weight_withPU);
										photonecalRecHitSumEtConeDR04_1_->Fill(photonecalRecHitSumEtConeDR04_1, weight_withPU);
										photonnTrkSolidConeDR04_1_->Fill(photonnTrkSolidConeDR04_1, weight_withPU);
										photontrkSumPtSolidConeDR04_1_->Fill(photontrkSumPtSolidConeDR04_1, weight_withPU);
										photonnTrkHollowConeDR04_1_->Fill(photonnTrkHollowConeDR04_1, weight_withPU);
										photontrkSumPtHollowConeDR04_1_->Fill(photontrkSumPtHollowConeDR04_1, weight_withPU);
										photonIsoFPRCharged_1_->Fill(photonIsoFPRCharged_1, weight_withPU);
										photonIsoFPRNeutral_1_->Fill(photonIsoFPRNeutral_1, weight_withPU);
										photonIsoFPRPhoton_1_->Fill(photonIsoFPRPhoton_1, weight_withPU);

										nJets_->Fill(nJets, weight_withPU);
			
										jetPt_1_->Fill(jetPt_1, weight_withPU);
										jetEta_1_->Fill(jetEta_1, weight_withPU);
										jetPhi_1_->Fill(jetPhi_1, weight_withPU);
										jetE_1_->Fill(jetE_1, weight_withPU);

										if(nJets > 1){
											jetPt_2_->Fill(jetPt_2, weight_withPU);
											jetEta_2_->Fill(jetEta_2, weight_withPU);
											jetPhi_2_->Fill(jetPhi_2, weight_withPU);
											jetE_2_->Fill(jetE_2, weight_withPU);
										}

										if(nJets > 2){										
											jetPt_3_->Fill(jetPt_3, weight_withPU);
											jetEta_3_->Fill(jetEta_3, weight_withPU);
											jetPhi_3_->Fill(jetPhi_3, weight_withPU);
											jetE_3_->Fill(jetE_3, weight_withPU);
										}
										
										DeltaR_photon1_jet1_->Fill(DeltaR_photon1_jet1, weight_withPU);
										DeltaPhi_photon1_jet1_->Fill(DeltaPhi_photon1_jet1, weight_withPU);

										if(nJets > 1){	
											DeltaR_photon1_jet2_->Fill(DeltaR_photon1_jet2, weight_withPU);
											DeltaEta_jet1_jet2_->Fill(DeltaEta_jet1_jet2, weight_withPU);
											DeltaPhi_jet1_jet2_->Fill(DeltaPhi_jet1_jet2, weight_withPU);
										}

										if(nJets > 2){												
											DeltaR_photon1_jet3_->Fill(DeltaR_photon1_jet3, weight_withPU);
										}

										HT_->Fill(HT, weight_withPU);
				
									}
								}
							}
						}
					}
				} // end quality selection
			} // end selection with 1 jet
      // if (Cut(ientry) < 0) continue;
		} // end if preselection
		
		//------cleaning

		if(nPhotons > 0 && nJets_cl > 0) { 
			
			iSelected0_cl++;
			iSelectedWithWeights0_cl = iSelectedWithWeights0_cl + weight_withPU;

			if (jetPt_1_cl > 50. && TMath::Abs(jetEta_1_cl) < 2.5 && photonPt_1 > 160. && (photonBit_1&1) && isTriggerMatchedFamily4) {

				iSelected1_cl++;
				iSelectedWithWeights1_cl = iSelectedWithWeights1_cl + weight_withPU;
				
				// quality selection: Barrel - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
				if((*photonPassConversionVeto)[0] == 1){ 
					iSelected2_cl++;				 
					iSelectedWithWeights2_cl = iSelectedWithWeights2_cl + weight_withPU;				 	 
				 	 if((*photonid_hadronicOverEm2012)[0] < 0.05){
				 	  iSelected3_cl++;
						iSelectedWithWeights3_cl = iSelectedWithWeights3_cl + weight_withPU;				 	  
					 	if((*photonid_sieie)[0] < 0.011){ 
					    iSelected4_cl++;
							iSelectedWithWeights4_cl = iSelectedWithWeights4_cl + weight_withPU;					    
				 	  	if((*photonPfIsoChargedHad)[0] < 1.5){ 
						    iSelected5_cl++;
								iSelectedWithWeights5_cl = iSelectedWithWeights5_cl + weight_withPU;
				 	 			if((*photonPfIsoNeutralHad)[0] < (1.0 + 0.04*photonPt_1)){
							    iSelected6_cl++;
									iSelectedWithWeights6_cl = iSelectedWithWeights6_cl + weight_withPU;
				 	 				if((*photonPfIsoPhoton)[0] < (0.7 + 0.005*photonPt_1)){
								    iSelected7_cl++;
										iSelectedWithWeights7_cl = iSelectedWithWeights7_cl + weight_withPU;
										Nvtx_cl_->Fill(nVtx, weight_withPU);
										
										nPhotons_cl_->Fill(nPhotons, weight_withPU);
//									photonPt_1_cl_->Fill((*photonPt)[0], weight_withPU);
										photonPt_1_cl_->Fill(photonPt_1, weight_withPU);
										photonE_1_cl_->Fill(photonE_1, weight_withPU);
										photonEta_1_cl_->Fill(photonEta_1, weight_withPU);
										photonPhi_1_cl_->Fill(photonPhi_1, weight_withPU);
										photonBit_1_cl_->Fill(photonBit_1, weight_withPU);
										photonPassConversionVeto_1_cl_->Fill(photonPassConversionVeto_1, weight_withPU);
										photonPfIsoChargedHad_1_cl_->Fill(photonPfIsoChargedHad_1, weight_withPU);
										photonPfIsoNeutralHad_1_cl_->Fill(photonPfIsoNeutralHad_1, weight_withPU);
										photonPfIsoPhoton_1_cl_->Fill(photonPfIsoPhoton_1, weight_withPU);
										photonPfIsoPhotons03ForCic_1_cl_->Fill(photonPfIsoPhotons03ForCic_1, weight_withPU);
										photonPfIsoNeutrals03ForCic_1_cl_->Fill(photonPfIsoNeutrals03ForCic_1, weight_withPU);
										photonPfIsoCharged03ForCicVtx0_1_cl_->Fill(photonPfIsoCharged03ForCicVtx0_1, weight_withPU);
										photonPfIsoCharged03BadForCic_1_cl_->Fill(photonPfIsoCharged03BadForCic_1, weight_withPU);
										photonPfIsoPhotons04ForCic_1_cl_->Fill(photonPfIsoPhotons04ForCic_1, weight_withPU);
										photonPfIsoNeutrals04ForCic_1_cl_->Fill(photonPfIsoNeutrals04ForCic_1, weight_withPU);
										photonPfIsoCharged04ForCicVtx0_1_cl_->Fill(photonPfIsoCharged04ForCicVtx0_1, weight_withPU);
										photonPfIsoCharged04BadForCic_1_cl_->Fill(photonPfIsoCharged04BadForCic_1, weight_withPU);
										photonid_sieie_1_cl_->Fill(photonid_sieie_1, weight_withPU);
										photonid_sieip_1_cl_->Fill(photonid_sieip_1, weight_withPU);
										photonid_etawidth_1_cl_->Fill(photonid_etawidth_1, weight_withPU);
										photonid_phiwidth_1_cl_->Fill(photonid_phiwidth_1, weight_withPU);
										photonid_r9_1_cl_->Fill(photonid_r9_1, weight_withPU);
										photonid_lambdaRatio_1_cl_->Fill(photonid_lambdaRatio_1, weight_withPU);
										photonid_s4Ratio_1_cl_->Fill(photonid_s4Ratio_1, weight_withPU);
										photonid_e25_1_cl_->Fill(photonid_e25_1, weight_withPU);
										photonid_sceta_1_cl_->Fill(photonid_sceta_1, weight_withPU);
										photonid_ESEffSigmaRR_1_cl_->Fill(photonid_ESEffSigmaRR_1, weight_withPU);
										photonid_hadronicOverEm_1_cl_->Fill(photonid_hadronicOverEm_1, weight_withPU);
										photonid_hadronicOverEm2012_1_cl_->Fill(photonid_hadronicOverEm2012_1, weight_withPU);
										photonhcalTowerSumEtConeDR04_1_cl_->Fill(photonhcalTowerSumEtConeDR04_1, weight_withPU);
										photonecalRecHitSumEtConeDR04_1_cl_->Fill(photonecalRecHitSumEtConeDR04_1, weight_withPU);
										photonnTrkSolidConeDR04_1_cl_->Fill(photonnTrkSolidConeDR04_1, weight_withPU);
										photontrkSumPtSolidConeDR04_1_cl_->Fill(photontrkSumPtSolidConeDR04_1, weight_withPU);
										photonnTrkHollowConeDR04_1_cl_->Fill(photonnTrkHollowConeDR04_1, weight_withPU);
										photontrkSumPtHollowConeDR04_1_cl_->Fill(photontrkSumPtHollowConeDR04_1, weight_withPU);
										photonIsoFPRCharged_1_cl_->Fill(photonIsoFPRCharged_1, weight_withPU);
										photonIsoFPRNeutral_1_cl_->Fill(photonIsoFPRNeutral_1, weight_withPU);
										photonIsoFPRPhoton_1_cl_->Fill(photonIsoFPRPhoton_1, weight_withPU);

										nJets_cl_->Fill(nJets_cl, weight_withPU);
			
										jetPt_1_cl_->Fill(jetPt_1_cl, weight_withPU);
										jetEta_1_cl_->Fill(jetEta_1_cl, weight_withPU);
										jetPhi_1_cl_->Fill(jetPhi_1_cl, weight_withPU);
										jetE_1_cl_->Fill(jetE_1_cl, weight_withPU);

										if(nJets > 1){
											jetPt_2_cl_->Fill(jetPt_2_cl, weight_withPU);
											jetEta_2_cl_->Fill(jetEta_2_cl, weight_withPU);
											jetPhi_2_cl_->Fill(jetPhi_2_cl, weight_withPU);
											jetE_2_cl_->Fill(jetE_2_cl, weight_withPU);
										}

										if(nJets > 2){										
											jetPt_3_cl_->Fill(jetPt_3_cl, weight_withPU);
											jetEta_3_cl_->Fill(jetEta_3_cl, weight_withPU);
											jetPhi_3_cl_->Fill(jetPhi_3_cl, weight_withPU);
											jetE_3_cl_->Fill(jetE_3_cl, weight_withPU);
										}
										
										DeltaR_photon1_jet1_cl_->Fill(DeltaR_photon1_jet1_cl, weight_withPU);
										DeltaPhi_photon1_jet1_cl_->Fill(DeltaPhi_photon1_jet1_cl, weight_withPU);

										if(nJets > 1){	
											DeltaR_photon1_jet2_cl_->Fill(DeltaR_photon1_jet2_cl, weight_withPU);
											DeltaEta_jet1_jet2_cl_->Fill(DeltaEta_jet1_jet2_cl, weight_withPU);
											DeltaPhi_jet1_jet2_cl_->Fill(DeltaPhi_jet1_jet2_cl, weight_withPU);
										}

										if(nJets > 2){												
											DeltaR_photon1_jet3_cl_->Fill(DeltaR_photon1_jet3_cl, weight_withPU);
										}

										HT_cl_->Fill(HT_cl, weight_withPU);
				
									}
								}
							}
						}
					}
				} // end quality selection
			} // end selection with 1 jet
//cout << "qui 3" << endl;
      // if (Cut(ientry) < 0) continue;
		} // end if preselection
//cout << "-----fine---------" << endl;		
	} // end loop on entries

	// ====================================terminate and plot
	
	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	cout << "Number of selected events 0, unweighted = " << iSelected0 << endl;
	cout << "Number of selected events 1, unweighted = " << iSelected1 << endl;
	cout << "Number of selected events 2, unweighted = " << iSelected2 << endl;
	cout << "Number of selected events 3, unweighted = " << iSelected3 << endl;
	cout << "Number of selected events 4, unweighted = " << iSelected4 << endl;
	cout << "Number of selected events 5, unweighted = " << iSelected5 << endl;
	cout << "Number of selected events 6, unweighted = " << iSelected6 << endl;
	cout << "Number of selected events 7, unweighted = " << iSelected7 << endl;
	cout << "Number of selected events, unweighted = " << iSelected7 << endl;
	cout << "Number of selected events, weighted = " << iSelected7*weight << endl;
	cout << "Cleaning: " << endl;
	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	cout << "Number of selected events 0, unweighted = " << iSelected0_cl << endl;
	cout << "Number of selected events 1, unweighted = " << iSelected1_cl << endl;
	cout << "Number of selected events 2, unweighted = " << iSelected2_cl << endl;
	cout << "Number of selected events 3, unweighted = " << iSelected3_cl << endl;
	cout << "Number of selected events 4, unweighted = " << iSelected4_cl << endl;
	cout << "Number of selected events 5, unweighted = " << iSelected5_cl << endl;
	cout << "Number of selected events 6, unweighted = " << iSelected6_cl << endl;
	cout << "Number of selected events 6, unweighted = " << iSelected6_cl << endl;
	cout << "Number of selected events 7, unweighted = " << iSelected7_cl << endl;
	cout << "Number of selected events, unweighted = " << iSelected7_cl << endl;
	cout << "Number of selected events, weighted = " << iSelected7_cl*weight_r << endl;
	fhistos->Write();
	if (plothistos == 1){
		Plot_Histos();  
	}
	if (textfile == 1){
		Text_File();
	}
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
	photonPt_1_ = new TH1F("photonPt_1_","Photon p_{T} ", 200, 0., 1200.);
	photonE_1_ = new TH1F("photonE_1_","Photon E ", 200, 0., 1200.);
	photonEta_1_ = new TH1F("photonEta_1_","Photon #eta ", 50, -2.7, 2.7);
	photonPhi_1_ = new TH1F("photonPhi_1_","Photon #varphi ", 50, -3.1416, 3.1416);
	photonBit_1_ = new TH1F("photonBit_1_","Photon bit ", 100, 0., 1000.);

	photonPassConversionVeto_1_ = new TH1F("photonPassConversionVeto_1_","photonPassConversionVeto ", 10, -2, 2);
	photonPfIsoChargedHad_1_ = new TH1F("photonPfIsoChargedHad_1_", "photon PfIsoChargedHad", 50, 0, 2);
	photonPfIsoNeutralHad_1_ = new TH1F("photonPfIsoNeutralHad_1_", "photon PfIsoNeutralHad", 30, 0, 30);
	photonPfIsoPhoton_1_ = new TH1F("photonPfIsoPhoton_1_", "photon PfIsoPhoton", 20, 0, 4);
  photonPfIsoPhotons03ForCic_1_ = new TH1F("photonPfIsoPhotons03ForCic_1_", "photon PfIsoPhotons03ForCic", 50, 0, 100);
	photonPfIsoNeutrals03ForCic_1_ = new TH1F("photonPfIsoNeutrals03ForCic_1_","photon PfIsoNeutrals03ForCic", 40, 0, 20);
	photonPfIsoCharged03ForCicVtx0_1_ = new TH1F("photonPfIsoCharged03ForCicVtx0_1_", "photon PfIsoCharged03ForCicVtx0", 50, 0, 100);
	photonPfIsoCharged03BadForCic_1_ = new TH1F("photonPfIsoCharged03BadForCic_1_", "photon PfIsoCharged03BadForCic", 50, 0, 100);
	photonPfIsoPhotons04ForCic_1_ = new TH1F("photonPfIsoPhotons04ForCic_1_", "photon PfIsoPhotons04ForCic", 50, 0, 100);
	photonPfIsoNeutrals04ForCic_1_ = new TH1F("photonPfIsoNeutrals04ForCic_1_", "photon PfIsoNeutrals04ForCic", 40, 0, 20);
	photonPfIsoCharged04ForCicVtx0_1_ = new TH1F("photonPfIsoCharged04ForCicVtx0_1_", "photon PfIsoCharged04ForCicVtx0", 50, 0, 100);
	photonPfIsoCharged04BadForCic_1_ = new TH1F("photonPfIsoCharged04BadForCic_1_", "photonPfIsoCharged04BadForCic", 50, 0, 100);
	photonid_sieie_1_ = new TH1F("photonid_sieie_1_", "photon ID: #sigma_{i#etai#eta}", 40, 0., 0.015);
	photonid_sieip_1_ = new TH1F("photonid_sieip_1_", "photon ID: #sigma_{i#etai#varphi}", 20, 0, 0.01);
	photonid_etawidth_1_ = new TH1F("photonid_etawidth_1_", "photon ID: #eta width", 30, 0, 0.02);
	photonid_phiwidth_1_ = new TH1F("photonid_phiwidth_1_", "photon ID: #varphi width", 30, 0, 0.1);
	photonid_r9_1_ = new TH1F("photonid_r9_1_", "photon ID: r9", 50, 0, 1);
	photonid_lambdaRatio_1_ = new TH1F("photonid_lambdaRatio_1_", "photon ID: #lambda Ratio", 50, 0, 1);
	photonid_s4Ratio_1_ = new TH1F("photonid_s4Ratio_1_","photon ID: s4 Ratio", 50, 0, 1);
	photonid_e25_1_ = new TH1F("photonid_e25_1_", "photon ID: #rho25", 50, 0, 1200);
	photonid_sceta_1_ = new TH1F("photonid_sceta_1_", "photon ID: SC #eta", 50, -2.7, 2.7);
	photonid_ESEffSigmaRR_1_ = new TH1F("photonid_ESEffSigmaRR_1_", "photon ID: ESEffSigmaRR", 10, 0, 1);
	photonid_hadronicOverEm_1_ = new TH1F("photonid_hadronicOverEm_1_", "photon ID: hadronicOverEm", 50, 0, 1);
	photonid_hadronicOverEm2012_1_ = new TH1F("photonid_hadronicOverEm2012_1_", "photon ID: hadronicOverEm2012", 50, 0, 0.5);
	photonhcalTowerSumEtConeDR04_1_ = new TH1F("photonhcalTowerSumEtConeDR04_1_","photon hcalTowerSumEtConeDR04", 100, 0, 100);
	photonecalRecHitSumEtConeDR04_1_ = new TH1F("photonecalRecHitSumEtConeDR04_1_", "photon ecalRecHitSumEtConeDR04", 100, 0, 100);
	photonnTrkSolidConeDR04_1_ = new TH1F("photonnTrkSolidConeDR04_1_", "photon nTrkSolidConeDR04", 30, 0, 30);
	photontrkSumPtSolidConeDR04_1_ = new TH1F("photontrkSumPtSolidConeDR04_1_","photon trkSumPtSolidConeDR04", 100, 0, 500);
	photonnTrkHollowConeDR04_1_ = new TH1F("photonnTrkHollowConeDR04_1_", "photon nTrkHollowConeDR04", 30, 0, 30) ;
	photontrkSumPtHollowConeDR04_1_ = new TH1F("photontrkSumPtHollowConeDR04_", "photon trkSumPtHollowConeDR04", 100, 0, 100);
	
	//PhotonIso
	photonIsoFPRCharged_1_ = new TH1F("photonIsoFPRCharged_1_", "photon IsoFPRCharged", 40, 0, 40); //with FOOT PRINT REMOVAL FROM MP
	photonIsoFPRNeutral_1_ = new TH1F("photonIsoFPRNeutral_1_", "photon IsoFPRNeutral", 40, 0, 20);
	photonIsoFPRPhoton_1_ = new TH1F("photonIsoFPRPhoton_1_", "photon IsoFPRPhoton", 40, 0, 40);
//jetPhotonDPhi_1_;

	nJets_ = new TH1F("nJets_","N Jets ", 10, 0, 10);

	jetPt_1_ = new TH1F("jetPt_1_","Jet 1 p_{T} ", 300, 0., 1050.);
	jetEta_1_ = new TH1F("jetEta_1_","Jet 1 #eta ", 50, -2.6, 2.6);
	jetPhi_1_ = new TH1F("jetPhi_1_","Jet 1 #varphi ", 50, -3.1416, 3.1416);
	jetE_1_ = new TH1F("jetE_1_", "jet 1 E", 300, 0., 1050.);

	jetPt_2_ = new TH1F("jetPt_2_","Jet 2 p_{T} ", 300, 0., 1050.);
	jetEta_2_ = new TH1F("jetEta_2_","Jet 2 #eta ", 50, -2.6, 2.6);
	jetPhi_2_ = new TH1F("jetPhi_2_","Jet 2 #varphi ", 50, -3.1416, 3.1416);
	jetE_2_ = new TH1F("jetE_2_", "jet 2 E", 300, 0., 1050.);

	jetPt_3_ = new TH1F("jetPt_3_","Jet 3 p_{T} ", 300, 0., 1050.);
	jetEta_3_ = new TH1F("jetEta_3_","Jet 3 #eta ", 50, -2.6, 2.6);
	jetPhi_3_ = new TH1F("jetPhi_3_","Jet 3 #varphi ", 50, -3.1416, 3.1416);
	jetE_3_ = new TH1F("jetE_3_", "jet 3 E", 300, 0., 1050.);

	DeltaR_photon1_jet1_ = new TH1F("DeltaR_photon1_jet1_","#DeltaR photon1-jet1", 30, 0, 6);
	DeltaPhi_photon1_jet1_ = new TH1F("DeltaPhi_photon1_jet1_","#Delta#varphi photon1-jet1", 50, 0, 3.1416);

	DeltaR_photon1_jet2_ = new TH1F("DeltaR_photon1_jet2_","#DeltaR photon1-jet2", 30, 0, 6);
	DeltaEta_jet1_jet2_ = new TH1F("DeltaEta_jet1_jet2_","#Delta#eta jet1-jet2", 50, 0, 5);
	DeltaPhi_jet1_jet2_ = new TH1F("DeltaPhi_jet1_jet2_","#Delta#varphi jet1-jet2", 50, 0, 3.1416);

	DeltaR_photon1_jet3_ = new TH1F("DeltaR_photon1_jet3_","#DeltaR photon1-jet3", 30, 0, 6);

	HT_ = new TH1F("HT_","H_{T}", 100, 0, 1300);

// -- cleaning
  Nvtx_cl_ = new TH1F("Nvtx_cl_","Number of vertices ", 50, 0, 50);

	nPhotons_cl_ = new TH1F("nPhotons_cl_","N Photons ", 10, 0, 10);
	photonPt_1_cl_ = new TH1F("photonPt_1_cl_","Photon p_{T} ", 200, 0., 1200.);
	photonE_1_cl_ = new TH1F("photonE_1_cl_","Photon E ", 200, 0., 1200.);
	photonEta_1_cl_ = new TH1F("photonEta_1_cl_","Photon #eta ", 50, -2.7, 2.7);
	photonPhi_1_cl_ = new TH1F("photonPhi_1_cl_","Photon #varphi ", 50, -3.1416, 3.1416);
	photonBit_1_cl_ = new TH1F("photonBit_1_cl_","Photon bit ", 100, 0., 1000.);
	
	photonPassConversionVeto_1_cl_ = new TH1F("photonPassConversionVeto_1_cl_","photonPassConversionVeto ", 10, -2, 2);
	photonPfIsoChargedHad_1_cl_ = new TH1F("photonPfIsoChargedHad_1_cl_", "photon PfIsoChargedHad", 50, 0, 2);
	photonPfIsoNeutralHad_1_cl_ = new TH1F("photonPfIsoNeutralHad_1_cl_", "photon PfIsoNeutralHad", 30, 0, 30);
	photonPfIsoPhoton_1_cl_ = new TH1F("photonPfIsoPhoton_1_cl_", "photon PfIsoPhoton", 20, 0, 4);
  photonPfIsoPhotons03ForCic_1_cl_ = new TH1F("photonPfIsoPhotons03ForCic_1_cl_", "photon PfIsoPhotons03ForCic", 50, 0, 100);
	photonPfIsoNeutrals03ForCic_1_cl_ = new TH1F("photonPfIsoNeutrals03ForCic_1_cl_","photon PfIsoNeutrals03ForCic", 40, 0, 20);
	photonPfIsoCharged03ForCicVtx0_1_cl_ = new TH1F("photonPfIsoCharged03ForCicVtx0_1_cl_", "photon PfIsoCharged03ForCicVtx0", 50, 0, 100);
	photonPfIsoCharged03BadForCic_1_cl_ = new TH1F("photonPfIsoCharged03BadForCic_1_cl_", "photon PfIsoCharged03BadForCic", 50, 0, 100);
	photonPfIsoPhotons04ForCic_1_cl_ = new TH1F("photonPfIsoPhotons04ForCic_1_cl_", "photon PfIsoPhotons04ForCic", 50, 0, 100);
	photonPfIsoNeutrals04ForCic_1_cl_ = new TH1F("photonPfIsoNeutrals04ForCic_1_cl_", "photon PfIsoNeutrals04ForCic", 40, 0, 20);
	photonPfIsoCharged04ForCicVtx0_1_cl_ = new TH1F("photonPfIsoCharged04ForCicVtx0_1_cl_", "photon PfIsoCharged04ForCicVtx0", 50, 0, 100);
	photonPfIsoCharged04BadForCic_1_cl_ = new TH1F("photonPfIsoCharged04BadForCic_1_cl_", "photonPfIsoCharged04BadForCic", 50, 0, 100);
	photonid_sieie_1_cl_ = new TH1F("photonid_sieie_1_cl_", "photon ID: #sigma_{i#etai#eta}", 40, 0., 0.015);
	photonid_sieip_1_cl_ = new TH1F("photonid_sieip_1_cl_", "photon ID: #sigma_{i#etai#varphi}", 20, 0, 0.01);
	photonid_etawidth_1_cl_ = new TH1F("photonid_etawidth_1_cl_", "photon ID: #eta width", 30, 0, 0.02);
	photonid_phiwidth_1_cl_ = new TH1F("photonid_phiwidth_1_cl_", "photon ID: #varphi width", 30, 0, 0.1);
	photonid_r9_1_cl_ = new TH1F("photonid_r9_1_cl_", "photon ID: r9", 50, 0, 1);
	photonid_lambdaRatio_1_cl_ = new TH1F("photonid_lambdaRatio_1_cl_", "photon ID: #lambda Ratio", 50, 0, 1);
	photonid_s4Ratio_1_cl_ = new TH1F("photonid_s4Ratio_1_cl_","photon ID: s4 Ratio", 50, 0, 1);
	photonid_e25_1_cl_ = new TH1F("photonid_e25_1_cl_", "photon ID: #rho25", 50, 0, 1200);
	photonid_sceta_1_cl_ = new TH1F("photonid_sceta_1_cl_", "photon ID: SC #eta", 50, -2.7, 2.7);
	photonid_ESEffSigmaRR_1_cl_ = new TH1F("photonid_ESEffSigmaRR_1_cl_", "photon ID: ESEffSigmaRR", 10, 0, 1);
	photonid_hadronicOverEm_1_cl_ = new TH1F("photonid_hadronicOverEm_1_cl_", "photon ID: hadronicOverEm", 50, 0, 1);
	photonid_hadronicOverEm2012_1_cl_ = new TH1F("photonid_hadronicOverEm2012_1_cl_", "photon ID: hadronicOverEm2012", 50, 0, 0.5);
	photonhcalTowerSumEtConeDR04_1_cl_ = new TH1F("photonhcalTowerSumEtConeDR04_1_cl_","photon hcalTowerSumEtConeDR04", 100, 0, 100);
	photonecalRecHitSumEtConeDR04_1_cl_ = new TH1F("photonecalRecHitSumEtConeDR04_1_cl_", "photon ecalRecHitSumEtConeDR04", 100, 0, 100);
	photonnTrkSolidConeDR04_1_cl_ = new TH1F("photonnTrkSolidConeDR04_1_cl_", "photon nTrkSolidConeDR04", 30, 0, 30);
	photontrkSumPtSolidConeDR04_1_cl_ = new TH1F("photontrkSumPtSolidConeDR04_1_cl_","photon trkSumPtSolidConeDR04", 100, 0, 500);
	photonnTrkHollowConeDR04_1_cl_ = new TH1F("photonnTrkHollowConeDR04_1_cl_", "photon nTrkHollowConeDR04", 30, 0, 30) ;
	photontrkSumPtHollowConeDR04_1_cl_ = new TH1F("photontrkSumPtHollowConeDR04_cl_", "photon trkSumPtHollowConeDR04", 100, 0, 100);
	
	//PhotonIso
	photonIsoFPRCharged_1_cl_ = new TH1F("photonIsoFPRCharged_1_cl_", "photon IsoFPRCharged", 40, 0, 40); //with FOOT PRINT REMOVAL FROM MP
	photonIsoFPRNeutral_1_cl_ = new TH1F("photonIsoFPRNeutral_1_cl_", "photon IsoFPRNeutral", 40, 0, 20);
	photonIsoFPRPhoton_1_cl_ = new TH1F("photonIsoFPRPhoton_1_cl_", "photon IsoFPRPhoton", 40, 0, 40);


	nJets_cl_ = new TH1F("nJets_cl_","N Jets ", 10, 0, 10);

	jetPt_1_cl_ = new TH1F("jetPt_1_cl_","Jet 1 p_{T} ", 300, 0., 1050.);
	jetEta_1_cl_ = new TH1F("jetEta_1_cl_","Jet 1 #eta ", 50, -2.6, 2.6);
	jetPhi_1_cl_ = new TH1F("jetPhi_1_cl_","Jet 1 #varphi ", 50, -3.1416, 3.1416);
	jetE_1_cl_ = new TH1F("jetE_1_cl_", "jet 1 E", 300, 0., 1050.);

	jetPt_2_cl_ = new TH1F("jetPt_2_cl_","Jet 2 p_{T} ", 300, 0., 1050.);
	jetEta_2_cl_ = new TH1F("jetEta_2_cl_","Jet 2 #eta ", 50, -2.6, 2.6);
	jetPhi_2_cl_ = new TH1F("jetPhi_2_cl_","Jet 2 #varphi ", 50, -3.1416, 3.1416);
	jetE_2_cl_ = new TH1F("jetE_2_cl_", "jet 2 E", 300, 0., 1050.);

	jetPt_3_cl_ = new TH1F("jetPt_3_cl_","Jet 3 p_{T} ", 300, 0., 1050.);
	jetEta_3_cl_ = new TH1F("jetEta_3_cl_","Jet 3 #eta ", 50, -2.6, 2.6);
	jetPhi_3_cl_ = new TH1F("jetPhi_3_cl_","Jet 3 #varphi ", 50, -3.1416, 3.1416);
	jetE_3_cl_ = new TH1F("jetE_3_cl_", "jet 3 E", 300, 0., 1050.);

	DeltaR_photon1_jet1_cl_ = new TH1F("DeltaR_photon1_jet1_cl_","#DeltaR photon1-jet1", 30, 0, 6);
	DeltaPhi_photon1_jet1_cl_ = new TH1F("DeltaPhi_photon1_jet1_cl_","#Delta#varphi photon1-jet1", 50, 0, 3.1416);

	DeltaR_photon1_jet2_cl_ = new TH1F("DeltaR_photon1_jet2_cl_","#DeltaR photon1-jet2", 30, 0, 6);
	DeltaEta_jet1_jet2_cl_ = new TH1F("DeltaEta_jet1_jet2_cl_","#Delta#eta jet1-jet2", 50, 0, 5);
	DeltaPhi_jet1_jet2_cl_ = new TH1F("DeltaPhi_jet1_jet2_cl_","#Delta#varphi jet1-jet2", 50, 0, 3.1416);

	DeltaR_photon1_jet3_cl_ = new TH1F("DeltaR_photon1_jet3_cl_","#DeltaR photon1-jet3", 30, 0, 6);

	HT_cl_ = new TH1F("HT_cl_","H_{T}", 100, 0, 1300);
 

//  ptPhoton_->Sumw2();
//  etaPhoton_->Sumw2();
//  phiPhoton_->Sumw2();

	cout << "...booking histograms finished." << endl;
}


void Plot_Histos(){

  // plot few histograms at the end, for check
  cout << "Plots: quick check... " << endl;

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

  TCanvas *c12 = new TCanvas("c12", "Angular variables", 10, 10, 700, 700);
  gPad->SetLogy();
  c12->Divide(2,2);
  c12->cd(1);
	DeltaPhi_photon1_jet1_->Draw();
  c12->cd(2);
	DeltaEta_jet1_jet2_->Draw();
  c12->cd(3);
	DeltaPhi_jet1_jet2_->Draw();
  c12->cd(4);
	HT_->Draw();

		
  cout << "...plots: quick check finished. " << endl;

  }


float deltaEta(float eta1, float eta2) { 

  float result = eta1 - eta2;
  float absresult = TMath::Abs(result);
  return absresult;
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


void Text_File(){

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
	text << "Number of selected events 5, unweighted = " << iSelected5 << endl;
	text << "Number of selected events 6, unweighted = " << iSelected6 << endl;
	text << "Number of selected events 6, unweighted = " << iSelected6 << endl;
	text << "Number of selected events 7, unweighted = " << iSelected7 << endl;
	text << "Number of selected events, unweighted = " << iSelected7 << endl;
	text << "Number of selected events, weighted = " << iSelected7*weight_r << endl;
	text << "Cleaning: " << endl;
  text << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	text << "Number of selected events 0, unweighted = " << iSelected0_cl << endl;
	text << "Number of selected events 1, unweighted = " << iSelected1_cl << endl;
	text << "Number of selected events 2, unweighted = " << iSelected2_cl << endl;
	text << "Number of selected events 3, unweighted = " << iSelected3_cl << endl;
	text << "Number of selected events 4, unweighted = " << iSelected4_cl << endl;
	text << "Number of selected events 5, unweighted = " << iSelected5_cl << endl;
	text << "Number of selected events 6, unweighted = " << iSelected6_cl << endl;
	text << "Number of selected events 6, unweighted = " << iSelected6_cl << endl;
	text << "Number of selected events 7, unweighted = " << iSelected7_cl << endl;
	text << "Number of selected events, unweighted = " << iSelected7_cl << endl;
	text << "Number of selected events, weighted = " << iSelected7_cl*weight_r << endl;
	text.close();
	cout << "...writing text file finished. " << endl;
	}
