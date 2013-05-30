#ifndef GJetsAnalyzer_h
#define GJetsAnalyzer_h

#include <Riostream.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <sstream>
#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "FWCore/Utilities/interface/Exception.h"
#endif

class GJetsAnalyzer {
  public :

		string       folder_samples;
		string       file_sample;
		string       file_address_s;
		bool         isTEST;
		bool         isMC;
  	Int_t        mysample;
		TTree       *fChain;   //!pointer to the analyzed TTree or TChain
		Int_t        fCurrent;  //!current Tree number in a TChain

		// Declaration of leaf types
		// ---- global event variables ----------------------------------------
		Int_t        isRealData;
		ULong64_t    eventNum;
		Int_t        runNum;
		Int_t        lumi;
		Int_t        nVtx;
		Int_t        nLeptons;
		Int_t        nPhotons;
		Int_t        nJets;
		Int_t        fwnJets;
		Float_t      rho;
		Float_t      rho25;
		Float_t      rhoQG;
		// ---- met variables -------------------------------------------------
		Float_t      pfmet;
		Float_t      pfmetPhi;
		Float_t      pfhadPt;
		Float_t      pfSumEt;
		// ---- dilepton variables --------------------------------------------
		Float_t      llM;
		Float_t      llPt;
		Float_t      llPhi;
		Float_t      llDPhi;
		Float_t      llY;
		Float_t      llEta;
		// ---- photon variables ----------------------------------------------
		vector<float>  *photonPt;
		vector<float>  *photonE;
		vector<float>  *photonEta;
		vector<float>  *photonPhi;
		vector<float>  *photonPassConversionVeto;
		vector<float>  *photonPfIsoChargedHad;
		vector<float>  *photonPfIsoNeutralHad; 
		vector<float>  *photonPfIsoPhoton;
		vector<float>  *photonPfIsoPhotons03ForCic;
		vector<float>  *photonPfIsoNeutrals03ForCic;
		vector<float>  *photonPfIsoCharged03ForCicVtx0;
		vector<float>  *photonPfIsoCharged03BadForCic;
		vector<float>  *photonPfIsoPhotons04ForCic;
		vector<float>  *photonPfIsoNeutrals04ForCic;
		vector<float>  *photonPfIsoCharged04ForCicVtx0;
		vector<float>  *photonPfIsoCharged04BadForCic;
		vector<float>  *photonid_sieie;
		vector<float>  *photonid_sieip;
		vector<float>  *photonid_etawidth;
		vector<float>  *photonid_phiwidth;  
		vector<float>  *photonid_r9;
		vector<float>  *photonid_lambdaRatio;
		vector<float>  *photonid_s4Ratio;
		vector<float>  *photonid_e25;
		vector<float>  *photonid_sceta;
		vector<float>  *photonid_ESEffSigmaRR;
		vector<float>  *photonid_hadronicOverEm;
		vector<float>  *photonid_hadronicOverEm2012;
		vector<float>  *photonhcalTowerSumEtConeDR04;
		vector<float>  *photonecalRecHitSumEtConeDR04;
		vector<float>  *photonnTrkSolidConeDR04;
		vector<float>  *photontrkSumPtSolidConeDR04;
		vector<float>  *photonnTrkHollowConeDR04;
		vector<float>  *photontrkSumPtHollowConeDR04;
		vector<float>  *photonIsoFPRCharged;
		vector<float>  *photonIsoFPRNeutral;
		vector<float>  *photonIsoFPRPhoton;
		vector<int>  *photonBit;
		// ---- trigger variables ---------------------------------------------
		vector<int>    *fired;
		vector<int>    *prescaleL1;
		vector<int>    *prescaleHLT;
		Int_t        isTriggered;
		// ---- trigger matching variables ---------------------------------------------
		Int_t        isTriggerMatchedFamily1;
		Int_t        isTriggerMatchedFamily2;
		Int_t        isTriggerMatchedFamily3;
		Int_t        isTriggerMatchedFamily4;
		Int_t        isTriggerMatchedFamily5;
		Int_t        isTriggerMatchedFamily6;
		// ---- lepton variables ----------------------------------------------
		vector<float>  *lepPt;
		vector<float>  *lepEta;
		vector<float>  *lepPhi;
		vector<float>  *lepE;
		vector<float>  *lepPFIsoUnc;
		vector<float>  *lepPFIsoDBCor;
		vector<float>  *lepPFIsoRhoCor;
		vector<int>    *lepChId;
		vector<float>  *lepR9orChi2ndof;
		vector<int>    *lepId;
		// ---- jet variables -------------------------------------------------
		vector<int>    *jetVeto;
		vector<float>  *jetPt;
		vector<float>  *jetEta;
		vector<float>  *jetPhi;
		vector<float>  *jetE;
		vector<float>  *jetArea;
		vector<float>  *jetBeta;
		vector<float>  *jetQGL;
		vector<int>    *jetPdgId;
//		vector<int>    *jetChgQC;
//		vector<int>    *jetNeutralPtCut;
//		vector<float>  *jetPtDQC;
//		vector<float>  *jetAxis1QC;
//		vector<float>  *jetAxis2QC;
		vector<float>  *jetQGMLP;
		vector<float>  *jetQG_axis2_L;
		vector<float>  *jetQG_ptD_L;
		vector<int>    *jetQG_mult_L;
		vector<float>  *jetQG_axis1_MLP;
		vector<float>  *jetQG_axis2_MLP;
		vector<float>  *jetQG_ptD_MLP;
		vector<int>    *jetQG_mult_MLP;
		vector<float>  *jetRMS;
		vector<float>  *jetBtag;
		vector<float>  *jetTagInfoNVtx;
		vector<float>  *jetTagInfoNTracks;
		vector<float>  *jetTagInfoVtxMass;
		vector<int>    *jetMCFlavour;
		vector<float>  *jetJEC;
		vector<float>  *jetUNC;
		vector<float>  *jetllDPhi;
	  // ---- forward jets - two leading forward jets -----------------------
		vector<float>  *fwjetPt;
		vector<float>  *fwjetEta;
		vector<float>  *fwjetPhi;
		vector<float>  *fwjetE;
	  // ---- vertex variables ----------------------------------------------
		vector<float>  *vtxZ;
		vector<float>  *vtxNdof;
		// ---- gen variables -------------------------------------------------
		Int_t        puINT;
		Int_t        puOOT;
		Int_t        puTrueINT;		
		Int_t        puTrueOOT;
		Int_t        nLeptonsGEN;
		Int_t        nJetsGEN;
		Float_t      llMGEN;
		Float_t      llPtGEN;
		Float_t      llPhiGEN;
		Float_t      llDPhiGEN;
		Float_t      llYGEN;
		Float_t      llEtaGEN;
		vector<float>  *lepPtGEN;
		vector<float>  *lepEtaGEN;
		vector<float>  *lepPhiGEN;
		vector<float>  *lepEGEN;
		vector<int>    *lepChIdGEN;
		vector<float>  *lepMatchedDRGEN;
		vector<int>    *lepMatchedGEN;
		vector<float>  *jetPtGEN;
		vector<float>  *jetEtaGEN;
		vector<float>  *jetPhiGEN;
		vector<float>  *jetEGEN;
		vector<int>    *jetVetoGEN;
		vector<float>  *jetllDPhiGEN;
		vector<int>    *jetIdGEN;
		vector<int>    *jetNpartonsGEN;		
		Float_t      HTParSum;
		Int_t        nParton; 		
		Float_t      mcWeight;
    Float_t      qScale;
    Float_t      alphaQED;
    Float_t      alphaQCD;
    Float_t      x1;
    Float_t      x2;
    Int_t        pdf1Id;
    Int_t        pdf2Id;
    Float_t      scalePDF;
		Int_t        nPhotonsGEN;
		Float_t      photonPtGEN;
		Float_t      photonEGEN;
		Float_t      photonEtaGEN;
		Float_t      photonPhiGEN;
		Float_t      photonIsoPtDR03GEN;
		Float_t      photonIsoSumPtDR03GEN;
		Float_t      photonIsoEDR03GEN;
		Float_t      photonIsoPtDR04GEN;
		Float_t      photonIsoSumPtDR04GEN;		
		Float_t      photonIsoEDR04GEN;
		Float_t      photonIsoPtDR05GEN;
		Float_t      photonIsoSumPtDR05GEN;
		Float_t      photonIsoEDR05GEN;		
		Int_t        photonMotherIdGEN;
		Float_t      photonRECODRGEN;
		Int_t        VBPartonDM;
		Float_t      VBPartonM;
		Float_t      VBPartonE;
		Float_t      VBPartonPt;
		Float_t      VBPartonEta;
		Float_t      VBPartonPhi;
//		vector<float>  *QGVars;
		vector<float>  *lepSigmaIEtaIEta;
		vector<float>  *lepHadronicOverEm;
		Double_t      eventWeight;
		Double_t      PUWeight;

  	// List of branches
	  // ---- global event variables ----------------------------------------
  	TBranch      *b_isRealData;
  	TBranch      *b_eventNum;
 		TBranch      *b_runNum;
  	TBranch      *b_lumi;
  	TBranch      *b_nVtx;
  	TBranch      *b_nLeptons;
  	TBranch      *b_nPhotons;
  	TBranch      *b_nJets;
  	TBranch      *b_fwnJets;
  	TBranch      *b_rho;
  	TBranch      *b_rho25;
  	TBranch      *b_rhoQG;
	  // ---- met variables -------------------------------------------------
  	TBranch      *b_pfmet;
  	TBranch      *b_pfmetPhi;
  	TBranch      *b_pfhadPt;
  	TBranch      *b_pfSumEt;
	  // ---- dilepton variables -------------------------------------------- 
  	TBranch      *b_llM;
  	TBranch      *b_llPt;
  	TBranch      *b_llPhi;
  	TBranch      *b_llDPhi;
  	TBranch      *b_llY;
  	TBranch      *b_llEta;
	  // ---- photon variables ----------------------------------------------  
  	TBranch      *b_photonPt;
  	TBranch      *b_photonE;
  	TBranch      *b_photonEta;
  	TBranch      *b_photonPhi;
  	TBranch      *b_photonPassConversionVeto;
  	TBranch      *b_photonPfIsoChargedHad;
  	TBranch      *b_photonPfIsoNeutralHad; 
  	TBranch      *b_photonPfIsoPhoton;
  	TBranch      *b_photonPfIsoPhotons03ForCic;
  	TBranch      *b_photonPfIsoNeutrals03ForCic;
  	TBranch      *b_photonPfIsoCharged03ForCicVtx0;
  	TBranch      *b_photonPfIsoCharged03BadForCic;
  	TBranch      *b_photonPfIsoPhotons04ForCic;
  	TBranch      *b_photonPfIsoNeutrals04ForCic;
  	TBranch      *b_photonPfIsoCharged04ForCicVtx0;
  	TBranch      *b_photonPfIsoCharged04BadForCic;
  	TBranch      *b_photonid_sieie;
  	TBranch      *b_photonid_sieip;
  	TBranch      *b_photonid_etawidth;
  	TBranch      *b_photonid_phiwidth;  
  	TBranch      *b_photonid_r9;
  	TBranch      *b_photonid_lambdaRatio;
  	TBranch      *b_photonid_s4Ratio;
  	TBranch      *b_photonid_e25;
  	TBranch      *b_photonid_sceta;
  	TBranch      *b_photonid_ESEffSigmaRR;
  	TBranch      *b_photonid_hadronicOverEm;
  	TBranch      *b_photonid_hadronicOverEm2012;
  	TBranch      *b_photonhcalTowerSumEtConeDR04;
  	TBranch      *b_photonecalRecHitSumEtConeDR04;
  	TBranch      *b_photonnTrkSolidConeDR04;
  	TBranch      *b_photontrkSumPtSolidConeDR04;
  	TBranch      *b_photonnTrkHollowConeDR04;
  	TBranch      *b_photontrkSumPtHollowConeDR04;
  	TBranch      *b_photonIsoFPRCharged;
  	TBranch      *b_photonIsoFPRNeutral;
  	TBranch      *b_photonIsoFPRPhoton;
  	TBranch      *b_photonBit;
		// ---- trigger variables ---------------------------------------------  
  	TBranch      *b_fired;
  	TBranch      *b_prescaleL1;
  	TBranch      *b_prescaleHLT;
  	TBranch      *b_isTriggered;
	  // ---- trigger matching variables ---------------------------------------------
  	TBranch      *b_isTriggerMatchedFamily1;
  	TBranch      *b_isTriggerMatchedFamily2;
  	TBranch      *b_isTriggerMatchedFamily3;
  	TBranch      *b_isTriggerMatchedFamily4;
  	TBranch      *b_isTriggerMatchedFamily5;
  	TBranch      *b_isTriggerMatchedFamily6;
	  // ---- lepton variables ----------------------------------------------
  	TBranch      *b_lepPt;
  	TBranch      *b_lepEta;
  	TBranch      *b_lepPhi;  
  	TBranch      *b_lepE;
  	TBranch      *b_lepPFIsoUnc;
  	TBranch      *b_lepPFIsoDBCor;
  	TBranch      *b_lepPFIsoRhoCor;
  	TBranch      *b_lepChId;
  	TBranch      *b_lepR9orChi2ndof;
  	TBranch      *b_lepId;
	  // ---- jet variables -------------------------------------------------  
  	TBranch      *b_jetVeto;
  	TBranch      *b_jetPt;
  	TBranch      *b_jetEta;
  	TBranch      *b_jetPhi;
  	TBranch      *b_jetE;
  	TBranch      *b_jetArea;
  	TBranch      *b_jetBeta;
  	TBranch      *b_jetQGL;
  	TBranch      *b_jetPdgId;
//  	TBranch      *b_jetChgQC;
//  	TBranch      *b_jetNeutralPtCut;
//  	TBranch      *b_jetPtDQC;
//  	TBranch      *b_jetAxis1QC;
//  	TBranch      *b_jetAxis2QC;
  	TBranch      *b_jetQGMLP;
  	TBranch      *b_jetQG_axis2_L;
  	TBranch      *b_jetQG_ptD_L;
  	TBranch      *b_jetQG_mult_L;
  	TBranch      *b_jetQG_axis1_MLP;
  	TBranch      *b_jetQG_axis2_MLP;
  	TBranch      *b_jetQG_ptD_MLP;
  	TBranch      *b_jetQG_mult_MLP;
  	TBranch      *b_jetRMS;
  	TBranch      *b_jetBtag;
  	TBranch      *b_jetTagInfoNVtx;
  	TBranch      *b_jetTagInfoNTracks;
  	TBranch      *b_jetTagInfoVtxMass;
  	TBranch      *b_jetMCFlavour;
  	TBranch      *b_jetJEC;
  	TBranch      *b_jetUNC;
  	TBranch      *b_jetllDPhi;
	  // ---- forward jets - two leading forward jets -----------------------
	  TBranch      *b_fwjetPt;
	  TBranch      *b_fwjetEta;
	  TBranch      *b_fwjetPhi;
	  TBranch      *b_fwjetE;
	  // ---- vertex variables ----------------------------------------------  
  	TBranch      *b_vtxZ;
  	TBranch      *b_vtxNdof;
	  // ---- gen variables -------------------------------------------------
  	TBranch      *b_puINT;
  	TBranch      *b_puOOT;
  	TBranch      *b_puTrueINT;
  	TBranch      *b_puTrueOOT;
  	TBranch      *b_nLeptonsGEN;
  	TBranch      *b_nJetsGEN;
  	TBranch      *b_qScale;
  	TBranch      *b_alphaQED;
  	TBranch      *b_alphaQCD;
  	TBranch      *b_x1;
  	TBranch      *b_x2;
  	TBranch      *b_pdf1Id;
  	TBranch      *b_pdf2Id;
  	TBranch      *b_scalePDF;
  	TBranch      *b_llMGEN;
  	TBranch      *b_llPtGEN;
  	TBranch      *b_llPhiGEN;
  	TBranch      *b_llDPhiGEN;
  	TBranch      *b_llYGEN;
  	TBranch      *b_llEtaGEN;
  	TBranch      *b_lepPtGEN;
  	TBranch      *b_lepEtaGEN;
  	TBranch      *b_lepPhiGEN;
  	TBranch      *b_lepEGEN;
  	TBranch      *b_lepChIdGEN;
  	TBranch      *b_lepMatchedDRGEN;
  	TBranch      *b_lepMatchedGEN;
  	TBranch      *b_jetPtGEN;
  	TBranch      *b_jetEtaGEN;
  	TBranch      *b_jetPhiGEN;
  	TBranch      *b_jetEGEN;
  	TBranch      *b_jetVetoGEN;
  	TBranch      *b_jetllDPhiGEN;
  	TBranch      *b_jetIdGEN;
  	TBranch      *b_jetNpartonsGEN;
  	TBranch      *b_HTParSum;
  	TBranch      *b_nParton;  	
  	TBranch      *b_mcWeight;
  	TBranch      *b_nPhotonsGEN;
  	TBranch      *b_photonPtGEN;
  	TBranch      *b_photonEGEN;
  	TBranch      *b_photonEtaGEN;
  	TBranch      *b_photonPhiGEN;
  	TBranch      *b_photonIsoPtDR03GEN;
  	TBranch      *b_photonIsoSumPtDR03GEN;  	
  	TBranch      *b_photonIsoEDR03GEN;
  	TBranch      *b_photonIsoPtDR04GEN;
  	TBranch      *b_photonIsoSumPtDR04GEN;
  	TBranch      *b_photonIsoEDR04GEN;
  	TBranch      *b_photonIsoPtDR05GEN;
  	TBranch      *b_photonIsoSumPtDR05GEN;
  	TBranch      *b_photonIsoEDR05GEN;
  	TBranch      *b_photonMotherIdGEN;
  	TBranch      *b_photonRECODRGEN;
  	TBranch      *b_VBPartonDM;
  	TBranch      *b_VBPartonM;
  	TBranch      *b_VBPartonE;
  	TBranch      *b_VBPartonPt;
  	TBranch      *b_VBPartonEta;
  	TBranch      *b_VBPartonPhi;
//  	TBranch      *b_QGVars;
  	TBranch      *b_lepSigmaIEtaIEta;
  	TBranch      *b_lepHadronicOverEm;
  	TBranch      *b_eventWeight;
  	TBranch      *b_PUWeight;
	
		GJetsAnalyzer(TTree *tree = 0, Int_t isample = -1);
		virtual ~GJetsAnalyzer();
		virtual Int_t    GetEntry(Long64_t entry);
		virtual Long64_t LoadTree(Long64_t entry);
  	virtual void     Init(TTree *tree);
  	virtual Bool_t   Notify();
  	virtual void     Show(Long64_t entry = -1);
		virtual Int_t    Cut(Long64_t entry);
//		virtual TString  floatToString(float number);	
  	virtual void     Loop();

  	virtual void     Book_Histos();
  	virtual void     Plot_Histos();
  	virtual void     Text_File();
  	
};
#endif

#ifdef GJetsAnalyzer_cxx
GJetsAnalyzer::GJetsAnalyzer(TTree *tree, Int_t isample) {
	// if parameter tree is not specified (or zero), connect the file
	// used to generate this class and read the Tree.

  folder_samples = "samples/";
  file_sample = "";
  file_address_s = "";
	mysample = isample;

	isTEST = false;
	if (mysample == 0) isTEST = true;

	isMC = false;
	if (mysample == 0 || mysample > 7) isMC = true;
	
  if (tree == 0) {

		bool outrange;
		outrange = mysample < 0 || (mysample > 7 && mysample < 11) || (mysample > 14 && mysample < 21) || (mysample > 31 && mysample < 41) || (mysample > 41 && mysample < 51) || (mysample > 56 && mysample < 61) || (mysample > 66 && mysample < 71) || mysample > 74;
		
		if (outrange){
		cout << "Error: mysample is out of range. " << endl;
		cout << "Choose the sample:" << endl;
		cout << "----------------------------------------------------- " << endl;
		cout << "mysample == 0   -> Test" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "mysample == 1   -> DATA Run2012A-13Jul2012" << endl;
		cout << "mysample == 2   -> DATA Run2012A-recover-06Aug2012" << endl;
		cout << "mysample == 3   -> DATA Run2012B-13Jul2012" << endl;
		cout << "mysample == 4   -> DATA Run2012C-24Aug2012" << endl;
		cout << "mysample == 5   -> DATA Run2012C-EcalRecover_11Dec2012" << endl;
		cout << "mysample == 6   -> DATA Run2012C-PromptReco" << endl;
		cout << "mysample == 7   -> DATA Run2012D-PromptReco" << endl;
		cout << "-----------------------------------------------------  " << endl;
		cout << "mysample == 11  -> GJets 40<HT<100" << endl;
		cout << "mysample == 12  -> Gjets 100<HT<200" << endl;
		cout << "mysample == 13  -> GJets 200<HT<400" << endl;
		cout << "mysample == 14  -> Gjets 400<HT<Inf" << endl;
		cout << "-----------------------------------------------------  " << endl;
		cout << "mysample == 21  -> G 15<Pt<30" << endl;
		cout << "mysample == 22  -> G 30<Pt<50" << endl;
		cout << "mysample == 23  -> G 50<Pt<80" << endl;
		cout << "mysample == 24  -> G 80<Pt<120" << endl;
		cout << "mysample == 25  -> G 120<Pt<170" << endl;
		cout << "mysample == 26  -> G 170<Pt<300" << endl;
		cout << "mysample == 27  -> G 300<Pt<470" << endl;
		cout << "mysample == 28  -> G 470<Pt<800" << endl;
		cout << "mysample == 29  -> G 800<Pt<1400" << endl;
		cout << "mysample == 30  -> G 1400<Pt<1800" << endl;
		cout << "mysample == 31  -> G 1800<Pt<Inf" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "mysample == 41  -> DiPhotonJets" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "mysample == 51  -> QCD EMEnriched 20<Pt<30" << endl;
		cout << "mysample == 52  -> QCD EMEnriched 30<Pt<80" << endl;
		cout << "mysample == 53  -> QCD EMEnriched 80<Pt<170" << endl;
		cout << "mysample == 54  -> QCD EMEnriched 170<Pt<250" << endl;
		cout << "mysample == 55  -> QCD EMEnriched 250<Pt<350" << endl;
		cout << "mysample == 56  -> QCD EMEnriched 350<Pt<Inf" << endl;
		cout << "-----------------------------------------------------  " << endl;
		cout << "mysample == 61  -> QCD BCtoE 20<Pt<30" << endl;
		cout << "mysample == 62  -> QCD BCtoE 30<Pt<80" << endl;
		cout << "mysample == 63  -> QCD BCtoE 80<Pt<170" << endl;
		cout << "mysample == 64  -> QCD BCtoE 170<Pt<250" << endl;
		cout << "mysample == 65  -> QCD BCtoE 250<Pt<350" << endl;
		cout << "mysample == 66  -> QCD BCtoE 350<Pt<Inf" << endl;
		cout << "-----------------------------------------------------  " << endl;
		cout << "mysample == 71  -> QCD 100<HT<250" << endl;
		cout << "mysample == 72  -> QCD 250<HT<500" << endl;
		cout << "mysample == 73  -> QCD 500<HT<1000" << endl;
		cout << "mysample == 74  -> QCD 1000<HT<inf" << endl;
		cout << "-----------------------------------------------------" << endl;
		throw cms::Exception("OutRange");
		}
		
// test -----------------------------------------------------------------   
		if (mysample == 0){
			file_sample = "Test.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// data -----------------------------------------------------------------
		else if (mysample == 1){
			file_sample = "Photon_Run2012A-13Jul2012-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 2){
			file_sample = "Photon_Run2012A-recover-06Aug2012-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 3){
			file_sample = "SinglePhoton_Run2012B-13Jul2012-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 4){
			file_sample = "SinglePhoton_Run2012C-24Aug2012-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 5){
			file_sample = "SinglePhoton_Run2012C-EcalRecover_11Dec2012-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 6){
			file_sample = "SinglePhoton_Run2012C-PromptReco-v2.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 7){
			file_sample = "SinglePhoton_Run2012D-PromptReco-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// MC signal GJets_HT-xToy ----------------------------------------------  
		else if (mysample == 11){
			file_sample = "GJets_HT-40To100_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V19-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 12){
			file_sample = "GJets_HT-100To200_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V19-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 13){
			file_sample = "GJets_HT-200To400_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 14){
			file_sample = "GJets_HT-400ToInf_8TeV-madgraph_v3_Summer12_DR53X-PU_S10_START53_V7C-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// MC signal G_Pt-XtoY --------------------------------------------------
		else if (mysample == 21){
			file_sample = "G_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 22){
			file_sample = "G_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 23){
			file_sample = "G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 24){
			file_sample = "G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 25){
			file_sample = "G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 26){
			file_sample = "G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 27){
			file_sample = "G_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 28){
			file_sample = "G_Pt-470to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 29){
			file_sample = "G_Pt-800to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 30){
			file_sample = "G_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 31){
			file_sample = "G_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// MC signal DiPhotonJets ------------------------------------------------------
		else if (mysample == 41){
			file_sample = "DiPhotonJets_8TeV-madgraph-tarball-v2_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// MC background QCD_Pt_x_y EMEnriched ----------------------------------
		else if (mysample == 51){
			file_sample = "QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 52){
			file_sample = "QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 53){
			file_sample = "QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 54){
			file_sample = "QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 55){
			file_sample = "QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 56){
			file_sample = "QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// MC background QCD_Pt_x_y BCtoE ----------------------------------
		else if (mysample == 61){
			file_sample = "QCD_Pt_20_30_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 62){
			file_sample = "QCD_Pt_30_80_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 63){
			file_sample = "QCD_Pt_80_170_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 64){
			file_sample = "QCD_Pt_170_250_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 65){
			file_sample = "QCD_Pt_250_350_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 66){
			file_sample = "QCD_Pt_350_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

// MC background QCD HT-xToy --------------------------------------------
		else if (mysample == 71){
			file_sample = "QCD_HT-100To250_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 72){
			file_sample = "QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 73){
			file_sample = "QCD_HT-500To1000_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		else if (mysample == 74){
			file_sample = "QCD_HT-1000ToInf_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root";
			file_address_s = (folder_samples + file_sample).c_str();
			const char * file_address = file_address_s.c_str();
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_address);
			if (!f) {
		  	f = new TFile(file_address);
		  	f->cd("accepted");
			}
		}

		tree = (TTree*)gDirectory->Get("events");
  }

  Init(tree);
}


GJetsAnalyzer::~GJetsAnalyzer() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}


Int_t GJetsAnalyzer::GetEntry(Long64_t entry) {
	// Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}


Long64_t GJetsAnalyzer::LoadTree(Long64_t entry) {
// Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
		fCurrent = chain->GetTreeNumber();
		Notify();
  }
  return centry;
}


void GJetsAnalyzer::Init(TTree *tree) {
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
	// ---- global event variables ----------------------------------------
	isRealData = 0;
	eventNum = 0;
	runNum = 0;
	lumi = 0;
	nVtx = 0;
	nLeptons = 0;
	nPhotons = 0;
	nJets = 0;
	fwnJets = 0;
	rho = 0;
	rho25 = 0;
	rhoQG = 0;
	// ---- met variables -------------------------------------------------
	pfmet = 0;
	pfmetPhi = 0;
	pfhadPt = 0;
	pfSumEt = 0;
	// ---- dilepton variables --------------------------------------------
	llM = 0;
	llPt = 0;
	llPhi = 0;
	llDPhi = 0;
	llY = 0;
	llEta = 0;
	// ---- photon variables ----------------------------------------------
	photonPt = 0;
	photonE = 0;
	photonEta = 0;
	photonPhi = 0;
	photonPassConversionVeto = 0;
	photonPfIsoChargedHad = 0;
	photonPfIsoNeutralHad = 0; 
	photonPfIsoPhoton = 0;
	photonPfIsoPhotons03ForCic = 0;
	photonPfIsoNeutrals03ForCic = 0;
	photonPfIsoCharged03ForCicVtx0 = 0;
	photonPfIsoCharged03BadForCic = 0;
	photonPfIsoPhotons04ForCic = 0;
	photonPfIsoNeutrals04ForCic = 0;
	photonPfIsoCharged04ForCicVtx0 = 0;
	photonPfIsoCharged04BadForCic = 0;
	photonid_sieie = 0;
	photonid_sieip = 0;
	photonid_etawidth = 0;
	photonid_phiwidth = 0;  
	photonid_r9 = 0;
	photonid_lambdaRatio = 0;
	photonid_s4Ratio = 0;
	photonid_e25 = 0;
	photonid_sceta = 0;
	photonid_ESEffSigmaRR = 0;
	photonid_hadronicOverEm = 0;
	photonid_hadronicOverEm2012 = 0;
	photonhcalTowerSumEtConeDR04 = 0;
	photonecalRecHitSumEtConeDR04 = 0;
	photonnTrkSolidConeDR04 = 0;
	photontrkSumPtSolidConeDR04 = 0;
	photonnTrkHollowConeDR04 = 0;
	photontrkSumPtHollowConeDR04 = 0;
	photonIsoFPRCharged = 0;
	photonIsoFPRNeutral = 0;
	photonIsoFPRPhoton = 0;
	photonBit = 0;
	// ---- trigger variables ---------------------------------------------
	fired = 0;
	prescaleL1 = 0;
	prescaleHLT = 0;
	isTriggered = 0;
	// ---- trigger matching variables ---------------------------------------------
	isTriggerMatchedFamily1 = 0;
	isTriggerMatchedFamily2 = 0;
	isTriggerMatchedFamily3 = 0;
	isTriggerMatchedFamily4 = 0;
	isTriggerMatchedFamily5 = 0;
	isTriggerMatchedFamily6 = 0;
	// ---- lepton variables ----------------------------------------------
	lepPt = 0;
	lepEta = 0;
	lepPhi = 0;
	lepE = 0;
	lepPFIsoUnc = 0;
	lepPFIsoDBCor = 0;
	lepPFIsoRhoCor = 0;
	lepChId = 0;
	lepR9orChi2ndof = 0;
	lepId = 0;
	// ---- jet variables -------------------------------------------------
	jetVeto = 0;
	jetPt = 0;
	jetEta = 0;
	jetPhi = 0;
	jetE = 0;
	jetArea = 0;
	jetBeta = 0;
	jetQGL = 0;
	jetPdgId = 0;
//	jetChgQC = 0;
//	jetNeutralPtCut = 0;
//	jetPtDQC = 0;
//	jetAxis1QC = 0;
//	jetAxis2QC = 0;
	jetQGMLP = 0;
	jetQG_axis2_L = 0;
	jetQG_ptD_L = 0;
	jetQG_mult_L = 0;
	jetQG_axis1_MLP = 0;
	jetQG_axis2_MLP = 0;
	jetQG_ptD_MLP = 0;
	jetQG_mult_MLP = 0;
	jetRMS = 0;
	jetBtag = 0;
	jetTagInfoNVtx = 0;
	jetTagInfoNTracks = 0;
	jetTagInfoVtxMass = 0;
	jetMCFlavour = 0;
	jetJEC = 0;
	jetUNC = 0;
	jetllDPhi = 0;
  // ---- forward jets - two leading forward jets------------------------
  fwjetPt = 0;
	fwjetEta = 0;
	fwjetPhi = 0;
	fwjetE = 0;
	// ---- vertex variables ----------------------------------------------
	vtxZ = 0;
	vtxNdof = 0;
	// ---- gen variables -------------------------------------------------
	puINT = 0;
	puOOT = 0;
	puTrueINT = 0;
	puTrueOOT = 0;
	nLeptonsGEN = 0;
	nJetsGEN = 0;
	llMGEN = 0;
	llPtGEN = 0;
	llPhiGEN = 0;
	llDPhiGEN = 0;
	llYGEN = 0;
	llEtaGEN = 0;
	lepPtGEN = 0;
	lepEtaGEN = 0;
	lepPhiGEN = 0;
	lepEGEN = 0;
	lepChIdGEN = 0;
	lepMatchedDRGEN = 0;
	lepMatchedGEN = 0;
	jetPtGEN = 0;
	jetEtaGEN = 0;
	jetPhiGEN = 0;
	jetEGEN = 0;
	jetVetoGEN = 0;
	jetllDPhiGEN = 0;
	jetIdGEN = 0;
	jetNpartonsGEN = 0;
	HTParSum = 0;
	nParton = 0;
	mcWeight = 0;
	qScale = 0;
	alphaQED = 0;
	alphaQCD = 0;
	x1 = 0;
	x2 = 0;
	pdf1Id = 0;
	pdf2Id = 0;
	scalePDF = 0;
	nPhotonsGEN = 0;
	photonPtGEN = 0;
	photonEGEN = 0;
	photonEtaGEN = 0;
	photonPhiGEN = 0;
	photonIsoPtDR03GEN = 0;
	photonIsoSumPtDR03GEN = 0;
	photonIsoEDR03GEN = 0;
	photonIsoPtDR04GEN = 0;
	photonIsoSumPtDR04GEN = 0;
	photonIsoEDR04GEN = 0;
	photonIsoPtDR05GEN = 0;
	photonIsoSumPtDR05GEN = 0;
	photonIsoEDR05GEN = 0;
	photonMotherIdGEN = 0;
	photonRECODRGEN = 0;
	VBPartonDM = 0;
	VBPartonM = 0;
	VBPartonE = 0;
	VBPartonPt = 0;
	VBPartonEta = 0;
	VBPartonPhi = 0;
//	QGVars = 0;
	lepSigmaIEtaIEta = 0;
	lepHadronicOverEm = 0;
	if(isMC && !isTEST){
		eventWeight = 0;
		PUWeight = 0;
	}
	
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  // ---- global event variables ----------------------------------------
  fChain->SetBranchAddress("isRealData", &isRealData, &b_isRealData);
  fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
  fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("nLeptons", &nLeptons, &b_nLeptons);
  fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
  fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
  fChain->SetBranchAddress("fwnJets", &fwnJets, &b_fwnJets);
  fChain->SetBranchAddress("rho", &rho, &b_rho);
  fChain->SetBranchAddress("rho25", &rho25, &b_rho25);
  fChain->SetBranchAddress("rhoQG", &rhoQG, &b_rhoQG);
  // ---- met variables -------------------------------------------------
  fChain->SetBranchAddress("pfmet", &pfmet, &b_pfmet);
  fChain->SetBranchAddress("pfmetPhi", &pfmetPhi, &b_pfmetPhi);
  fChain->SetBranchAddress("pfhadPt", &pfhadPt, &b_pfhadPt);
  fChain->SetBranchAddress("pfSumEt", &pfSumEt, &b_pfSumEt);
  // ---- dilepton variables --------------------------------------------
  fChain->SetBranchAddress("llM", &llM, &b_llM);
  fChain->SetBranchAddress("llPt", &llPt, &b_llPt);
  fChain->SetBranchAddress("llPhi", &llPhi, &b_llPhi);
  fChain->SetBranchAddress("llDPhi", &llDPhi, &b_llDPhi);
  fChain->SetBranchAddress("llY", &llY, &b_llY);
  fChain->SetBranchAddress("llEta", &llEta, &b_llEta);
  // ---- photon variables ----------------------------------------------
  fChain->SetBranchAddress("photonPt", &photonPt, &b_photonPt);
  fChain->SetBranchAddress("photonE", &photonE, &b_photonE);
  fChain->SetBranchAddress("photonEta", &photonEta, &b_photonEta);
  fChain->SetBranchAddress("photonPhi", &photonPhi, &b_photonPhi);
  fChain->SetBranchAddress("photonPassConversionVeto", &photonPassConversionVeto, &b_photonPassConversionVeto);
  fChain->SetBranchAddress("photonPfIsoChargedHad", &photonPfIsoChargedHad, &b_photonPfIsoChargedHad);
  fChain->SetBranchAddress("photonPfIsoNeutralHad", &photonPfIsoNeutralHad, &b_photonPfIsoNeutralHad);
  fChain->SetBranchAddress("photonPfIsoPhoton", &photonPfIsoPhoton, &b_photonPfIsoPhoton);
  fChain->SetBranchAddress("photonPfIsoPhoton03ForCic", &photonPfIsoPhotons03ForCic, &b_photonPfIsoPhotons03ForCic);
  fChain->SetBranchAddress("photonPfIsoNeutrals03ForCic", &photonPfIsoNeutrals03ForCic, &b_photonPfIsoNeutrals03ForCic); 
  fChain->SetBranchAddress("photonPfIsoCharged03ForCicVtx0", &photonPfIsoCharged03ForCicVtx0, &b_photonPfIsoCharged03ForCicVtx0);
  fChain->SetBranchAddress("photonPfIsoCharged03BadForCic", &photonPfIsoCharged03BadForCic, &b_photonPfIsoCharged03BadForCic);
  fChain->SetBranchAddress("photonPfIsoPhoton04ForCic", &photonPfIsoPhotons04ForCic, &b_photonPfIsoPhotons04ForCic);
  fChain->SetBranchAddress("photonPfIsoNeutrals04ForCic", &photonPfIsoNeutrals04ForCic, &b_photonPfIsoNeutrals04ForCic);
  fChain->SetBranchAddress("photonPfIsoCharged04ForCicVtx0", &photonPfIsoCharged04ForCicVtx0, &b_photonPfIsoCharged04ForCicVtx0);
  fChain->SetBranchAddress("photonPfIsoCharged04BadForCic", &photonPfIsoCharged04BadForCic, &b_photonPfIsoCharged04BadForCic);
  fChain->SetBranchAddress("photonid_sieie", &photonid_sieie, &b_photonid_sieie);
  fChain->SetBranchAddress("photonid_sieip", &photonid_sieip, &b_photonid_sieip);
  fChain->SetBranchAddress("photonid_etawidth", &photonid_etawidth, &b_photonid_etawidth);
  fChain->SetBranchAddress("photonid_phiwidth", &photonid_phiwidth, &b_photonid_phiwidth);  
  fChain->SetBranchAddress("photonid_r9", &photonid_r9, &b_photonid_r9);
  fChain->SetBranchAddress("photonid_lambdaRatio", &photonid_lambdaRatio, &b_photonid_lambdaRatio);
  fChain->SetBranchAddress("photonid_s4Ratio", &photonid_s4Ratio, &b_photonid_s4Ratio);
  fChain->SetBranchAddress("photonid_e25", &photonid_e25, &b_photonid_e25);
  fChain->SetBranchAddress("photonid_sceta", &photonid_sceta, &b_photonid_sceta);
  fChain->SetBranchAddress("photonid_ESEffSigmaRR", &photonid_ESEffSigmaRR, &b_photonid_ESEffSigmaRR);
  fChain->SetBranchAddress("photonid_hadronicOverEm", &photonid_hadronicOverEm, &b_photonid_hadronicOverEm);
  fChain->SetBranchAddress("photonid_hadronicOverEm2012", &photonid_hadronicOverEm2012, &b_photonid_hadronicOverEm2012);
  fChain->SetBranchAddress("photonhcalTowerSumEtConeDR04", &photonhcalTowerSumEtConeDR04, &b_photonhcalTowerSumEtConeDR04);
  fChain->SetBranchAddress("photonecalRecHitSumEtConeDR04", &photonecalRecHitSumEtConeDR04, &b_photonecalRecHitSumEtConeDR04);
  fChain->SetBranchAddress("photonnTrkSolidConeDR04", &photonnTrkSolidConeDR04, &b_photonnTrkSolidConeDR04);
  fChain->SetBranchAddress("photontrkSumPtSolidConeDR04", &photontrkSumPtSolidConeDR04, &b_photontrkSumPtSolidConeDR04);
  fChain->SetBranchAddress("photonnTrkHollowConeDR04", &photonnTrkHollowConeDR04, &b_photonnTrkHollowConeDR04);
  fChain->SetBranchAddress("photontrkSumPtHollowConeDR04", &photontrkSumPtHollowConeDR04, &b_photontrkSumPtHollowConeDR04);
  fChain->SetBranchAddress("photonIsoFPRCharged", &photonIsoFPRCharged, &b_photonIsoFPRCharged);
  fChain->SetBranchAddress("photonIsoFPRNeutral", &photonIsoFPRNeutral, &b_photonIsoFPRNeutral);
  fChain->SetBranchAddress("photonIsoFPRPhoton", &photonIsoFPRPhoton, &b_photonIsoFPRPhoton);
  fChain->SetBranchAddress("photonBit", &photonBit, &b_photonBit);
  // ---- trigger variables ---------------------------------------------
  fChain->SetBranchAddress("fired", &fired, &b_fired);
  fChain->SetBranchAddress("prescaleL1", &prescaleL1, &b_prescaleL1);
  fChain->SetBranchAddress("prescaleHLT", &prescaleHLT, &b_prescaleHLT);
  fChain->SetBranchAddress("isTriggered", &isTriggered, &b_isTriggered);
  // ---- trigger matching variables ---------------------------------------------
  fChain->SetBranchAddress("isTriggerMatchedFamily1", &isTriggerMatchedFamily1, &b_isTriggerMatchedFamily1);
  fChain->SetBranchAddress("isTriggerMatchedFamily2", &isTriggerMatchedFamily2, &b_isTriggerMatchedFamily2);
  fChain->SetBranchAddress("isTriggerMatchedFamily3", &isTriggerMatchedFamily3, &b_isTriggerMatchedFamily3);
  fChain->SetBranchAddress("isTriggerMatchedFamily4", &isTriggerMatchedFamily4, &b_isTriggerMatchedFamily4);
  fChain->SetBranchAddress("isTriggerMatchedFamily5", &isTriggerMatchedFamily5, &b_isTriggerMatchedFamily5);
  fChain->SetBranchAddress("isTriggerMatchedFamily6", &isTriggerMatchedFamily6, &b_isTriggerMatchedFamily6);
  // ---- lepton variables ----------------------------------------------
  fChain->SetBranchAddress("lepPt", &lepPt, &b_lepPt);
  fChain->SetBranchAddress("lepEta", &lepEta, &b_lepEta);
  fChain->SetBranchAddress("lepPhi", &lepPhi, &b_lepPhi);
  fChain->SetBranchAddress("lepE", &lepE, &b_lepE);
  fChain->SetBranchAddress("lepPFIsoUnc", &lepPFIsoUnc, &b_lepPFIsoUnc);
  fChain->SetBranchAddress("lepPFIsoDBCor", &lepPFIsoDBCor, &b_lepPFIsoDBCor);
  fChain->SetBranchAddress("lepPFIsoRhoCor", &lepPFIsoRhoCor, &b_lepPFIsoRhoCor);
  fChain->SetBranchAddress("lepChId", &lepChId, &b_lepChId);
  fChain->SetBranchAddress("lepR9orChi2ndof", &lepR9orChi2ndof, &b_lepR9orChi2ndof);
  fChain->SetBranchAddress("lepId", &lepId, &b_lepId);
  // ---- jet variables -------------------------------------------------
  fChain->SetBranchAddress("jetVeto", &jetVeto, &b_jetVeto);
  fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
  fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
  fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
  fChain->SetBranchAddress("jetE", &jetE, &b_jetE);
  fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
  fChain->SetBranchAddress("jetBeta", &jetBeta, &b_jetBeta);
  fChain->SetBranchAddress("jetQGL", &jetQGL, &b_jetQGL);
  fChain->SetBranchAddress("jetPdgId", &jetPdgId, &b_jetPdgId);
//  fChain->SetBranchAddress("jetChgQC", &jetChgQC, &b_jetChgQC);
//  fChain->SetBranchAddress("jetNeutralPtCut", &jetNeutralPtCut, &b_jetNeutralPtCut);
//  fChain->SetBranchAddress("jetPtDQC", &jetPtDQC, &b_jetPtDQC);
//  fChain->SetBranchAddress("jetAxis1QC", &jetAxis1QC, &b_jetAxis1QC);
//  fChain->SetBranchAddress("jetAxis2QC", &jetAxis2QC, &b_jetAxis2QC);
  fChain->SetBranchAddress("jetQGMLP", &jetQGMLP, &b_jetQGMLP);
  fChain->SetBranchAddress("jetQG_axis2_L", &jetQG_axis2_L, &b_jetQG_axis2_L);
  fChain->SetBranchAddress("jetQG_ptD_L", &jetQG_ptD_L, &b_jetQG_ptD_L);
  fChain->SetBranchAddress("jetQG_mult_L", &jetQG_mult_L, &b_jetQG_mult_L);
  fChain->SetBranchAddress("jetQG_axis1_MLP", &jetQG_axis1_MLP, &b_jetQG_axis1_MLP);
  fChain->SetBranchAddress("jetQG_axis2_MLP", &jetQG_axis2_MLP, &b_jetQG_axis2_MLP);
  fChain->SetBranchAddress("jetQG_ptD_MLP", &jetQG_ptD_MLP, &b_jetQG_ptD_MLP);            
  fChain->SetBranchAddress("jetQG_mult_MLP", &jetQG_mult_MLP, &b_jetQG_mult_MLP);
  fChain->SetBranchAddress("jetRMS", &jetRMS, &b_jetRMS);
  fChain->SetBranchAddress("jetBtag", &jetBtag, &b_jetBtag);
  fChain->SetBranchAddress("jetTagInfoNVtx", &jetTagInfoNVtx, &b_jetTagInfoNVtx);
  fChain->SetBranchAddress("jetTagInfoNTracks", &jetTagInfoNTracks, &b_jetTagInfoNTracks);
  fChain->SetBranchAddress("jetTagInfoVtxMass", &jetTagInfoVtxMass, &b_jetTagInfoVtxMass);
  fChain->SetBranchAddress("jetMCFlavour", &jetMCFlavour, &b_jetMCFlavour);
  fChain->SetBranchAddress("jetJEC", &jetJEC, &b_jetJEC);
  fChain->SetBranchAddress("jetUNC", &jetUNC, &b_jetUNC);
  fChain->SetBranchAddress("jetllDPhi", &jetllDPhi, &b_jetllDPhi);
 //-----forward jets - two leading forward jets
  fChain->SetBranchAddress("fwjetPt", &fwjetPt, &b_fwjetPt);
  fChain->SetBranchAddress("fwjetEta", &fwjetEta, &b_fwjetEta);
  fChain->SetBranchAddress("fwjetPhi", &fwjetPhi, &b_fwjetPhi);
  fChain->SetBranchAddress("fwjetE", &fwjetE, &b_fwjetE);
  // ---- vertex variables ----------------------------------------------
  fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
  fChain->SetBranchAddress("vtxNdof", &vtxNdof, &b_vtxNdof);
  // ---- gen variables ----------------------------------------------
  fChain->SetBranchAddress("puINT", &puINT, &b_puINT);
  fChain->SetBranchAddress("puOOT", &puOOT, &b_puOOT);
  fChain->SetBranchAddress("puTrueINT", &puTrueINT, &b_puTrueINT);
  fChain->SetBranchAddress("puTrueOOT", &puTrueOOT, &b_puTrueOOT);
  fChain->SetBranchAddress("nLeptonsGEN", &nLeptonsGEN, &b_nLeptonsGEN);
  fChain->SetBranchAddress("nJetsGEN", &nJetsGEN, &b_nJetsGEN);
  fChain->SetBranchAddress("llMGEN", &llMGEN, &b_llMGEN);
  fChain->SetBranchAddress("llPtGEN", &llPtGEN, &b_llPtGEN);
  fChain->SetBranchAddress("llPhiGEN", &llPhiGEN, &b_llPhiGEN);
  fChain->SetBranchAddress("llDPhiGEN", &llDPhiGEN, &b_llDPhiGEN);
  fChain->SetBranchAddress("llYGEN", &llYGEN, &b_llYGEN);
  fChain->SetBranchAddress("llEtaGEN", &llEtaGEN, &b_llEtaGEN);
  fChain->SetBranchAddress("lepPtGEN", &lepPtGEN, &b_lepPtGEN);
  fChain->SetBranchAddress("lepEtaGEN", &lepEtaGEN, &b_lepEtaGEN);
  fChain->SetBranchAddress("lepPhiGEN", &lepPhiGEN, &b_lepPhiGEN);
  fChain->SetBranchAddress("lepEGEN", &lepEGEN, &b_lepEGEN);
  fChain->SetBranchAddress("lepChIdGEN", &lepChIdGEN, &b_lepChIdGEN);
  fChain->SetBranchAddress("lepMatchedDRGEN", &lepMatchedDRGEN, &b_lepMatchedDRGEN);
  fChain->SetBranchAddress("lepMatchedGEN", &lepMatchedGEN, &b_lepMatchedGEN);
  fChain->SetBranchAddress("jetPtGEN", &jetPtGEN, &b_jetPtGEN);
  fChain->SetBranchAddress("jetEtaGEN", &jetEtaGEN, &b_jetEtaGEN);
  fChain->SetBranchAddress("jetPhiGEN", &jetPhiGEN, &b_jetPhiGEN);
  fChain->SetBranchAddress("jetEGEN", &jetEGEN, &b_jetEGEN);
  fChain->SetBranchAddress("jetVetoGEN", &jetVetoGEN, &b_jetVetoGEN);
  fChain->SetBranchAddress("jetllDPhiGEN", &jetllDPhiGEN, &b_jetllDPhiGEN);
  fChain->SetBranchAddress("jetIdGEN", &jetIdGEN, &b_jetIdGEN);
  fChain->SetBranchAddress("jetNpartonsGEN", &jetNpartonsGEN, &b_jetNpartonsGEN);
  fChain->SetBranchAddress("HTParSum", &HTParSum, &b_HTParSum); 
  fChain->SetBranchAddress("nParton", &nParton, &b_nParton);    
  fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
  fChain->SetBranchAddress("qScale", &qScale, &b_qScale);
  fChain->SetBranchAddress("alphaQED", &alphaQED, &b_alphaQED);
  fChain->SetBranchAddress("alphaQCD", &alphaQCD, &b_alphaQCD);
  fChain->SetBranchAddress("x1", &x1, &b_x1);
  fChain->SetBranchAddress("x2", &x2, &b_x2);
  fChain->SetBranchAddress("pdf1Id", &pdf1Id, &b_pdf1Id);
  fChain->SetBranchAddress("pdf2Id", &pdf2Id, &b_pdf2Id);
  fChain->SetBranchAddress("scalePDF", &scalePDF, &b_scalePDF);
  fChain->SetBranchAddress("nPhotonsGEN", &nPhotonsGEN, &b_nPhotonsGEN);
  fChain->SetBranchAddress("photonPtGEN", &photonPtGEN, &b_photonPtGEN);
  fChain->SetBranchAddress("photonEGEN", &photonEGEN, &b_photonEGEN);
  fChain->SetBranchAddress("photonEtaGEN", &photonEtaGEN, &b_photonEtaGEN);
  fChain->SetBranchAddress("photonPhiGEN", &photonPhiGEN, &b_photonPhiGEN);
  fChain->SetBranchAddress("photonIsoPtDR03GEN", &photonIsoPtDR03GEN, &b_photonIsoPtDR03GEN);
  fChain->SetBranchAddress("photonIsoSumPtDR03GEN", &photonIsoSumPtDR03GEN, &b_photonIsoSumPtDR03GEN);
  fChain->SetBranchAddress("photonIsoEDR03GEN", &photonIsoEDR03GEN, &b_photonIsoEDR03GEN);
  fChain->SetBranchAddress("photonIsoPtDR04GEN", &photonIsoPtDR04GEN, &b_photonIsoPtDR04GEN);
  fChain->SetBranchAddress("photonIsoSumPtDR04GEN", &photonIsoSumPtDR04GEN, &b_photonIsoSumPtDR04GEN);
  fChain->SetBranchAddress("photonIsoEDR04GEN", &photonIsoEDR04GEN, &b_photonIsoEDR04GEN);
  fChain->SetBranchAddress("photonIsoPtDR05GEN", &photonIsoPtDR05GEN, &b_photonIsoPtDR05GEN);
  fChain->SetBranchAddress("photonIsoSumPtDR05GEN", &photonIsoSumPtDR05GEN, &b_photonIsoSumPtDR05GEN);
  fChain->SetBranchAddress("photonIsoEDR05GEN", &photonIsoEDR05GEN, &b_photonIsoEDR05GEN);
  fChain->SetBranchAddress("photonMotherIdGEN", &photonMotherIdGEN, &b_photonMotherIdGEN);
  fChain->SetBranchAddress("photonRECODRGEN", &photonRECODRGEN, &b_photonRECODRGEN);
  fChain->SetBranchAddress("VBPartonDM", &VBPartonDM, &b_VBPartonDM);
  fChain->SetBranchAddress("VBPartonM", &VBPartonM, &b_VBPartonM);
  fChain->SetBranchAddress("VBPartonE", &VBPartonE, &b_VBPartonE);
  fChain->SetBranchAddress("VBPartonPt", &VBPartonPt, &b_VBPartonPt);
  fChain->SetBranchAddress("VBPartonEta", &VBPartonEta, &b_VBPartonEta);
  fChain->SetBranchAddress("VBPartonPhi", &VBPartonPhi, &b_VBPartonPhi);
//	  fChain->SetBranchAddress("QGVars", &QGVars, &b_QGVars);  
  fChain->SetBranchAddress("lepSigmaIEtaIEta", &lepSigmaIEtaIEta, &b_lepSigmaIEtaIEta);
  fChain->SetBranchAddress("lepHadronicOverEm", &lepHadronicOverEm, &b_lepHadronicOverEm);
	if(isMC && !isTEST){
	  fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight); 
	  fChain->SetBranchAddress("PUWeight", &PUWeight, &b_PUWeight);
	}
  Notify();
}


Bool_t GJetsAnalyzer::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


void GJetsAnalyzer::Show(Long64_t entry) {
	// Print contents of entry.
	// If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}


Int_t GJetsAnalyzer::Cut(Long64_t entry) {
	// This function may be called from Loop.
	// returns  1 if entry is accepted.
	// returns -1 otherwise.
	cout << "entry = " << entry << endl;
  return 1;
}

/*
TString GJetsAnalyzer::floatToString(float number){
	ostringstream oss;
	oss << number;
	return oss.str();
}
*/
#endif // #ifdef GJetsAnalyzer_cxx
