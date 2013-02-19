#ifndef GJetsAnalyzer_h
#define GJetsAnalyzer_h

#include <Riostream.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class GJetsAnalyzer {
  public :
  
  	Int_t        mysample;
		TTree       *fChain;   //!pointer to the analyzed TTree or TChain
		Int_t        fCurrent;  //!current Tree number in a TChain

		// Declaration of leaf types
		// ---- global event variables ----------------------------------------
		Int_t        isRealData;
//		Int_t        selRECO;
		ULong64_t    eventNum;
		Int_t        runNum;
		Int_t        lumi;
		Int_t        nVtx;
		Int_t        nLeptons;
		Int_t        nPhotons;
		Int_t        nJets;
//		Int_t        nRJets;
//		Int_t        isZlead;
//		Int_t        isPhotonlead;
		Float_t      rho;
		Float_t      rho25;
//		Float_t      mZj1;
//		Float_t      mZj1j2;
//		Float_t      mZj1j2j3;
//		Float_t      ptZj1;
//		Float_t      costhetaZj1;
//		Float_t      costhetaPhotonj1;
//		Float_t      mj1j2;
//		Float_t      mj1j2j3;
//		Float_t      mrj1rj2;
//		Float_t      mLep;
//		Float_t      htLead;
//		Float_t      j1j2DPhi;
//		Float_t      j1j3DPhi;
//		Float_t      j2j3DPhi;
//		Float_t      j1j2DR;
//		Float_t      j1j3DR;
//		Float_t      j2j3DR;
//		Float_t      jetPtGeMean;
//		Float_t      jetPtArMean;
		// ---- met variables -------------------------------------------------
		Float_t      pfmet;
		Float_t      pfmetPhi;
		Float_t      pfhadPt;
		Float_t      pfSumEt;
//		Float_t      HTJetSum;
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
//		vector<float>  *photonIso;
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
//		vector<float>  *photonID;
		vector<int>  *photonBit;
//		vector<float>  *pfhadPhoPt;
//		vector<float>  *mPhotonj1;
//		vector<float>  *ptPhotonj1;
//		vector<float>  *jetPhotonDPhi;
//		vector<float>  *photonPar;
		// ---- FSRphoton variables ----------------------------------------------
//		Float_t      FSRphotonPt;
//		Float_t      FSRphotonE;
//		Float_t      FSRphotonEta;
//		Float_t      FSRphotonPhi;
//		Float_t      FSRphotonIso;
//		Float_t      FSRphotonID;
//		Int_t        FSRphotonBit;
//		Int_t        FSRphotonJet;
//		vector<float>  *FSRphotonPar;
//		Float_t      FSRphotonllM;
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
		vector<int>    *lepId;
		// ---- jet variables -------------------------------------------------
		vector<int>    *jetVeto;
		vector<float>  *jetPt;
		vector<float>  *jetEta;
		vector<float>  *jetPhi;
		vector<float>  *jetE;
//		vector<float>  *jetY;
		vector<float>  *jetArea;
		vector<float>  *jetBeta;
		vector<float>  *jetQGL;
		vector<float>  *jetRMS;
		vector<float>  *jetBtag;
		vector<float>  *jetTagInfoNVtx;
		vector<float>  *jetTagInfoNTracks;
		vector<float>  *jetTagInfoVtxMass;
		vector<int>    *jetMCFlavour;
		vector<float>  *jetJEC;
		vector<float>  *jetUNC;
		vector<float>  *jetllDPhi;
//		vector<float>  *jetCHF;
//		vector<float>  *jetPHF;
//		vector<float>  *jetNHF;
//		vector<float>  *jetMUF;
//		vector<float>  *jetELF;
//		vector<int>    *jetId;
	 // ---- DR rejected jet variables ------------------------------------
//		vector<float>  *rjetPt;
//		vector<float>  *rjetEta;
//		vector<float>  *rjetPhi;
//		vector<float>  *rjetE;
//		vector<float>  *rjetY;
//		vector<float>  *rjetArea;
//		vector<float>  *rjetBeta;
//		vector<float>  *rjetBtag;
//		vector<float>  *rjetJEC;
//		vector<float>  *rjetUNC;
//		vector<float>  *rjetCHF;
//		vector<float>  *rjetPHF;
//		vector<float>  *rjetNHF;
//		vector<float>  *rjetMUF;
//		vector<float>  *rjetELF;
//		vector<int>    *rjetId;
		// ---- vertex variables ----------------------------------------------
		vector<float>  *vtxZ;
		vector<float>  *vtxNdof;
		// ---- gen variables ----------------------------------------------
//		Int_t        selGEN;
		Int_t        puINT;
		Int_t        puTrueINT;		
		Int_t        puOOT;
		Int_t        puTrueOOT;
		Int_t        nLeptonsGEN;
		Int_t        nJetsGEN;
//		Int_t        isZleadGEN;
//		Float_t      mZj1GEN;
//		Float_t      ptZj1GEN;
//		Float_t      costhetaZj1GEN;
//		Float_t      mj1j2GEN;
//		Float_t      mLepGEN;
//		Float_t      htLeadGEN;
//		Float_t      j1j2DPhiGEN;
//		Float_t      j1j3DPhiGEN;
//		Float_t      j2j3DPhiGEN;
//		Float_t      j1j2DRGEN;
//		Float_t      j1j3DRGEN;
//		Float_t      j2j3DRGEN;
//		Float_t      jetPtGeMeanGEN;
//		Float_t      jetPtArMeanGEN;
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
//		Float_t      HTJetSumGEN;
		Float_t      HTParSum;
		Float_t      mcWeight;
		Int_t        nPhotonsGEN;
		Float_t      photonPtGEN;
		Float_t      photonEGEN;
		Float_t      photonEtaGEN;
		Float_t      photonPhiGEN;
		Int_t        photonMotherIdGEN;
		Float_t      photonRECODRGEN;
		Int_t        VBPartonDM;
		Float_t      VBPartonM;
		Float_t      VBPartonE;
		Float_t      VBPartonPt;
		Float_t      VBPartonEta;
		Float_t      VBPartonPhi;
		vector<float>  *QGVars;
		vector<float>  *lepSigmaIEtaIEta;
		vector<float>  *lepHadronicOverEm;

  	// List of branches
	  // ---- global event variables ----------------------------------------
  	TBranch      *b_isRealData;
//  	TBranch      *b_selRECO;
  	TBranch      *b_eventNum;
 		TBranch      *b_runNum;
  	TBranch      *b_lumi;
  	TBranch      *b_nVtx;
  	TBranch      *b_nLeptons;
  	TBranch      *b_nPhotons;
  	TBranch      *b_nJets;
//  	TBranch      *b_nRJets;
//  	TBranch      *b_isZlead;
//  	TBranch      *b_isPhotonlead;
  	TBranch      *b_rho;
  	TBranch      *b_rho25;
//  	TBranch      *b_mZj1;
//  	TBranch      *b_mZj1j2;
//  	TBranch      *b_mZj1j2j3;
//  	TBranch      *b_ptZj1;
//  	TBranch      *b_costhetaZj1;
//  	TBranch      *b_costhetaPhotonj1;
//  	TBranch      *b_mj1j2;
//  	TBranch      *b_mj1j2j3;
//  	TBranch      *b_mrj1rj2;
//  	TBranch      *b_mLep;
//  	TBranch      *b_htLead;
//  	TBranch      *b_j1j2DPhi;
//  	TBranch      *b_j1j3DPhi;
//  	TBranch      *b_j2j3DPhi;
//  	TBranch      *b_j1j2DR;
//  	TBranch      *b_j1j3DR;
//  	TBranch      *b_j2j3DR;
//  	TBranch      *b_jetPtGeMean;
//  	TBranch      *b_jetPtArMean;
	  // ---- met variables -------------------------------------------------
  	TBranch      *b_pfmet;
  	TBranch      *b_pfmetPhi;
  	TBranch      *b_pfhadPt;
  	TBranch      *b_pfSumEt;
//  	TBranch      *b_HTJetSum;
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
//  	TBranch      *b_photonIso;
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
//  	TBranch      *b_photonID;
  	TBranch      *b_photonBit;
//  	TBranch      *b_pfhadPhoPt;
//  	TBranch      *b_mPhotonj1;
//  	TBranch      *b_ptPhotonj1;
//  	TBranch      *b_jetPhotonDPhi;
//  	TBranch      *b_photonPar;
		// ---- FSRphoton variables ----------------------------------------------
//  	TBranch      *b_FSRphotonPt;
//  	TBranch      *b_FSRphotonE;
//		TBranch      *b_FSRphotonEta;
//  	TBranch      *b_FSRphotonPhi;
//  	TBranch      *b_FSRphotonIso;
//  	TBranch      *b_FSRphotonID;
//  	TBranch      *b_FSRphotonBit;
//  	TBranch      *b_FSRphotonJet;
//  	TBranch      *b_FSRphotonPar;
//  	TBranch      *b_FSRphotonllM;
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
  	TBranch      *b_lepId;
	  // ---- jet variables -------------------------------------------------  
  	TBranch      *b_jetPt;
  	TBranch      *b_jetEta;
  	TBranch      *b_jetPhi;
  	TBranch      *b_jetE;
//  	TBranch      *b_jetY;
  	TBranch      *b_jetArea;
  	TBranch      *b_jetBeta;
  	TBranch      *b_jetQGL;
  	TBranch      *b_jetRMS;
  	TBranch      *b_jetBtag;
  	TBranch      *b_jetTagInfoNVtx;
  	TBranch      *b_jetTagInfoNTracks;
  	TBranch      *b_jetTagInfoVtxMass;
  	TBranch      *b_jetMCFlavour;
  	TBranch      *b_jetJEC;
  	TBranch      *b_jetUNC;
  	TBranch      *b_jetllDPhi;
//  	TBranch      *b_jetCHF;
//  	TBranch      *b_jetPHF;
//  	TBranch      *b_jetNHF;
//  	TBranch      *b_jetMUF;
//  	TBranch      *b_jetELF;
//  	TBranch      *b_jetId;
	 // ---- DR rejected jet variables ------------------------------------  
//  	TBranch      *b_rjetPt;
//  	TBranch      *b_rjetEta;
//  	TBranch      *b_rjetPhi;
//  	TBranch      *b_rjetE;
//  	TBranch      *b_rjetY;
//  	TBranch      *b_rjetArea;
//  	TBranch      *b_rjetBeta;
//  	TBranch      *b_rjetBtag;
//  	TBranch      *b_rjetJEC;
//  	TBranch      *b_rjetUNC;
//  	TBranch      *b_rjetCHF;
//  	TBranch      *b_rjetPHF;
//  	TBranch      *b_rjetNHF;
//  	TBranch      *b_rjetMUF;
//  	TBranch      *b_rjetELF;
//  	TBranch      *b_rjetId;
	  // ---- vertex variables ----------------------------------------------  
  	TBranch      *b_vtxZ;
  	TBranch      *b_vtxNdof;
	  // ---- gen variables ----------------------------------------------
//  	TBranch      *b_selGEN;
  	TBranch      *b_puINT;
  	TBranch      *b_puTrueINT;
  	TBranch      *b_puOOT;
  	TBranch      *b_puTrueOOT;
  	TBranch      *b_nLeptonsGEN;
  	TBranch      *b_nJetsGEN;
//  	TBranch      *b_isZleadGEN;
//  	TBranch      *b_mZj1GEN;
//  	TBranch      *b_ptZj1GEN;
//  	TBranch      *b_costhetaZj1GEN;
//  	TBranch      *b_mj1j2GEN;
//  	TBranch      *b_mLepGEN;
//  	TBranch      *b_htLeadGEN;
//  	TBranch      *b_j1j2DPhiGEN;
//  	TBranch      *b_j1j3DPhiGEN;
//  	TBranch      *b_j2j3DPhiGEN;
//  	TBranch      *b_j1j2DRGEN;
//  	TBranch      *b_j1j3DRGEN;
//  	TBranch      *b_j2j3DRGEN;
//  	TBranch      *b_jetPtGeMeanGEN;
//  	TBranch      *b_jetPtArMeanGEN;
  	TBranch      *b_jetVeto;
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
//  	TBranch      *b_HTJetSumGEN;
  	TBranch      *b_HTParSum;
  	TBranch      *b_mcWeight;
  	TBranch      *b_nPhotonsGEN;
  	TBranch      *b_photonPtGEN;
  	TBranch      *b_photonEGEN;
  	TBranch      *b_photonEtaGEN;
  	TBranch      *b_photonPhiGEN;
  	TBranch      *b_photonMotherIdGEN;
  	TBranch      *b_photonRECODRGEN;
  	TBranch      *b_VBPartonDM;
  	TBranch      *b_VBPartonM;
  	TBranch      *b_VBPartonE;
  	TBranch      *b_VBPartonPt;
  	TBranch      *b_VBPartonEta;
  	TBranch      *b_VBPartonPhi;
  	TBranch      *b_QGVars;
  	TBranch      *b_lepSigmaIEtaIEta;
  	TBranch      *b_lepHadronicOverEm;

	
		GJetsAnalyzer(TTree *tree = 0, Int_t isample = -1);
		virtual ~GJetsAnalyzer();
		virtual Int_t    GetEntry(Long64_t entry);
		virtual Long64_t LoadTree(Long64_t entry);
  	virtual void     Init(TTree *tree);
  	virtual Bool_t   Notify();
  	virtual void     Show(Long64_t entry = -1);
		virtual Int_t    Cut(Long64_t entry);
  	virtual void     Loop();

};
#endif

#ifdef GJetsAnalyzer_cxx
GJetsAnalyzer::GJetsAnalyzer(TTree *tree, Int_t isample) {
	// if parameter tree is not specified (or zero), connect the file
	// used to generate this class and read the Tree.

	mysample = isample;
	
  if (tree == 0) {

		if (mysample < 0 || mysample > 13){
		cout << "Error: mysample range is 0-13"<< endl;
		}
		
// data -----------------------------------------------------------------
		else if (mysample == 0){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DATA_all_photons.root");
			if (!f) {
				f = new TFile("DATA_all_photons.root");
				f->cd("accepted");
			}
		}

// MC signal GJets_HT-xToy ----------------------------------------------  
		else if (mysample == 1){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_GJets_HT-200To400_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_GJets_HT-200To400_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 2){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_GJets_HT-400ToInf_Summer12.root");
			if (!f) {
				f = new TFile("MC_GJets_HT-400ToInf_Summer12.root");
				f->cd("accepted");
			}
		}

// MC background QCD_Pt_x_y EMEnriched ----------------------------------
		else if (mysample == 3){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_Pt_20_30_EMEnriched_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_Pt_20_30_EMEnriched_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 4){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_Pt_30_80_EMEnriched_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_Pt_30_80_EMEnriched_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 5){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_Pt_80_170_EMEnriched_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_Pt_80_170_EMEnriched_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 6){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_Pt_170_250_EMEnriched_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_Pt_170_250_EMEnriched_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 7){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_Pt_250_350_EMEnriched_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_Pt_250_350_EMEnriched_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 8){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_Pt_350_EMEnriched_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_Pt_350_EMEnriched_Summer12.root");
		  	f->cd("accepted");
			}
		}

// test -----------------------------------------------------------------   
		else if (mysample == 9){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Test.root");
			if (!f) {
		  	f = new TFile("Test.root");
		  	f->cd("accepted");
			}
		}

// MC background QCD HT-xToy --------------------------------------------
		else if (mysample == 10){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_HT-100To250_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_HT-100To250_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 11){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_HT-250To500_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_HT-250To500_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 12){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_HT-500To1000_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_HT-500To1000_Summer12.root");
		  	f->cd("accepted");
			}
		}

		else if (mysample == 13){
			TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MC_QCD_HT-1000Toinf_Summer12.root");
			if (!f) {
		  	f = new TFile("MC_QCD_HT-1000ToInf_Summer12.root");
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
//	selRECO = 0;
	eventNum = 0;
	runNum = 0;
	lumi = 0;
	nVtx = 0;
	nLeptons = 0;
	nPhotons = 0;
	nJets = 0;
//	nRJets = 0;
//	isZlead = 0;
//	isPhotonlead = 0;
	rho = 0;
	rho25 = 0;
//	mZj1 = 0;
//	mZj1j2 = 0;
//	mZj1j2j3 = 0;
//	ptZj1 = 0;
//	costhetaZj1 = 0;
//	costhetaPhotonj1 = 0;
//	mj1j2 = 0;
//	mj1j2j3 = 0;
//	mrj1rj2 = 0;
//	mLep = 0;
//	htLead = 0;
//	j1j2DPhi = 0;
//	j1j3DPhi = 0;
//	j2j3DPhi = 0;
//	j1j2DR = 0;
//	j1j3DR = 0;
//	j2j3DR = 0;
//	jetPtGeMean = 0;
//	jetPtArMean = 0;
	// ---- met variables -------------------------------------------------
	pfmet = 0;
	pfmetPhi = 0;
	pfhadPt = 0;
	pfSumEt = 0;
//	HTJetSum = 0;
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
//	photonIso = 0;
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
//	photonID = 0;
	photonBit = 0;
//	pfhadPhoPt = 0;
//	mPhotonj1 = 0;
//	ptPhotonj1 = 0;
//	jetPhotonDPhi = 0;
//	photonPar = 0;
	// ---- FSRphoton variables ----------------------------------------------
//	FSRphotonPt = 0;
//	FSRphotonE = 0;
//	FSRphotonEta = 0;
//	FSRphotonPhi = 0;
//	FSRphotonIso = 0;
//	FSRphotonID = 0;
//	FSRphotonBit = 0;
//	FSRphotonJet = 0;
//	FSRphotonPar = 0;
//	FSRphotonllM = 0;
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
	lepId = 0;
	// ---- jet variables -------------------------------------------------
	jetPt = 0;
	jetEta = 0;
	jetPhi = 0;
	jetE = 0;
//	jetY = 0;
	jetArea = 0;
	jetBeta = 0;
	jetQGL = 0;
	jetRMS = 0;
	jetBtag = 0;
	jetTagInfoNVtx = 0;
	jetTagInfoNTracks = 0;
	jetTagInfoVtxMass = 0;
	jetMCFlavour = 0;
	jetJEC = 0;
	jetUNC = 0;
	jetllDPhi = 0;
//	jetCHF = 0;
//	jetPHF = 0;
//	jetNHF = 0;
//	jetMUF = 0;
//	jetELF = 0;
//	jetId = 0;
	// ---- DR rejected jet variables ------------------------------------
//	rjetPt = 0;
//	rjetEta = 0;
//	rjetPhi = 0;
//	rjetE = 0;
//	rjetY = 0;
//	rjetArea = 0;
//	rjetBeta = 0;
//	rjetBtag = 0;
//	rjetJEC = 0;
//	rjetUNC = 0;
//	rjetCHF = 0;
//	rjetPHF = 0;
//	rjetNHF = 0;
//	rjetMUF = 0;
//	rjetELF = 0;
//	rjetId = 0;
	// ---- vertex variables ----------------------------------------------
	vtxZ = 0;
	vtxNdof = 0;
	// ---- gen variables ----------------------------------------------
//	selGEN = 0;
	puINT = 0;
	puTrueINT = 0;
	puOOT = 0;
	puTrueOOT = 0;
	nLeptonsGEN = 0;
	nJetsGEN = 0;
//	isZleadGEN = 0;
//	mZj1GEN = 0;
//	ptZj1GEN = 0;
//	costhetaZj1GEN = 0;
//	mj1j2GEN = 0;
//	mLepGEN = 0;
//	htLeadGEN = 0;
//	j1j2DPhiGEN = 0;
//	j1j3DPhiGEN = 0;
//	j2j3DPhiGEN = 0;
//	j1j2DRGEN = 0;
//	j1j3DRGEN = 0;
//	j2j3DRGEN = 0;
//	jetPtGeMeanGEN = 0;
//	jetPtArMeanGEN = 0;
	jetVeto = 0;
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
//	HTJetSumGEN = 0;
	HTParSum = 0;
	mcWeight = 0;
	nPhotonsGEN = 0;
	photonPtGEN = 0;
	photonEGEN = 0;
	photonEtaGEN = 0;
	photonPhiGEN = 0;
	photonMotherIdGEN = 0;
	photonRECODRGEN = 0;
	VBPartonDM = 0;
	VBPartonM = 0;
	VBPartonE = 0;
	VBPartonPt = 0;
	VBPartonEta = 0;
	VBPartonPhi = 0;
	QGVars = 0;
	lepSigmaIEtaIEta = 0;
	lepHadronicOverEm = 0;

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  // ---- global event variables ----------------------------------------
  fChain->SetBranchAddress("isRealData", &isRealData, &b_isRealData);
//  fChain->SetBranchAddress("selRECO", &selRECO, &b_selRECO);
  fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
  fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("nLeptons", &nLeptons, &b_nLeptons);
  fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
  fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
//  fChain->SetBranchAddress("nRJets", &nRJets, &b_nRJets);
//  fChain->SetBranchAddress("isZlead", &isZlead, &b_isZlead);
//  fChain->SetBranchAddress("isPhotonlead", &isPhotonlead, &b_isPhotonlead);
  fChain->SetBranchAddress("rho", &rho, &b_rho);
  fChain->SetBranchAddress("rho25", &rho25, &b_rho25);
//  fChain->SetBranchAddress("mZj1", &mZj1, &b_mZj1);
//  fChain->SetBranchAddress("mZj1j2", &mZj1j2, &b_mZj1j2);
//  fChain->SetBranchAddress("mZj1j2j3", &mZj1j2j3, &b_mZj1j2j3);
//  fChain->SetBranchAddress("ptZj1", &ptZj1, &b_ptZj1);
//  fChain->SetBranchAddress("costhetaZj1", &costhetaZj1, &b_costhetaZj1);
//  fChain->SetBranchAddress("costhetaPhotonj1", &costhetaPhotonj1, &b_costhetaPhotonj1);
//  fChain->SetBranchAddress("mj1j2", &mj1j2, &b_mj1j2);
//  fChain->SetBranchAddress("mj1j2j3", &mj1j2j3, &b_mj1j2j3);
//  fChain->SetBranchAddress("mrj1rj2", &mrj1rj2, &b_mrj1rj2);
//  fChain->SetBranchAddress("mLep", &mLep, &b_mLep);
//  fChain->SetBranchAddress("htLead", &htLead, &b_htLead);
//  fChain->SetBranchAddress("j1j2DPhi", &j1j2DPhi, &b_j1j2DPhi);
//  fChain->SetBranchAddress("j1j3DPhi", &j1j3DPhi, &b_j1j3DPhi);
//  fChain->SetBranchAddress("j2j3DPhi", &j2j3DPhi, &b_j2j3DPhi);
//  fChain->SetBranchAddress("j1j2DR", &j1j2DR, &b_j1j2DR);
//  fChain->SetBranchAddress("j1j3DR", &j1j3DR, &b_j1j3DR);
//  fChain->SetBranchAddress("j2j3DR", &j2j3DR, &b_j2j3DR);
//  fChain->SetBranchAddress("jetPtGeMean", &jetPtGeMean, &b_jetPtGeMean);
//  fChain->SetBranchAddress("jetPtArMean", &jetPtArMean, &b_jetPtArMean);
  // ---- met variables -------------------------------------------------
  fChain->SetBranchAddress("pfmet", &pfmet, &b_pfmet);
  fChain->SetBranchAddress("pfmetPhi", &pfmetPhi, &b_pfmetPhi);
  fChain->SetBranchAddress("pfhadPt", &pfhadPt, &b_pfhadPt);
  fChain->SetBranchAddress("pfSumEt", &pfSumEt, &b_pfSumEt);
//  fChain->SetBranchAddress("HTJetSum", &HTJetSum, &b_HTJetSum);
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
//  fChain->SetBranchAddress("photonIso", &photonIso, &b_photonIso);
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
//  fChain->SetBranchAddress("photonID", &photonID, &b_photonID);
  fChain->SetBranchAddress("photonBit", &photonBit, &b_photonBit);
//  fChain->SetBranchAddress("pfhadPhoPt", &pfhadPhoPt, &b_pfhadPhoPt);
//  fChain->SetBranchAddress("mPhotonj1", &mPhotonj1, &b_mPhotonj1);
//  fChain->SetBranchAddress("ptPhotonj1", &ptPhotonj1, &b_ptPhotonj1);
//  fChain->SetBranchAddress("jetPhotonDPhi", &jetPhotonDPhi, &b_jetPhotonDPhi);
//  fChain->SetBranchAddress("photonPar", &photonPar, &b_photonPar);
  // ---- FSRphoton variables ----------------------------------------------
//  fChain->SetBranchAddress("FSRphotonPt", &FSRphotonPt, &b_FSRphotonPt);
//  fChain->SetBranchAddress("FSRphotonE", &FSRphotonE, &b_FSRphotonE);
//  fChain->SetBranchAddress("FSRphotonEta", &FSRphotonEta, &b_FSRphotonEta);
//  fChain->SetBranchAddress("FSRphotonPhi", &FSRphotonPhi, &b_FSRphotonPhi);
//  fChain->SetBranchAddress("FSRphotonIso", &FSRphotonIso, &b_FSRphotonIso);
//  fChain->SetBranchAddress("FSRphotonID", &FSRphotonID, &b_FSRphotonID);
//  fChain->SetBranchAddress("FSRphotonBit", &FSRphotonBit, &b_FSRphotonBit);
//  fChain->SetBranchAddress("FSRphotonJet", &FSRphotonJet, &b_FSRphotonJet);
//  fChain->SetBranchAddress("FSRphotonPar", &FSRphotonPar, &b_FSRphotonPar);
//  fChain->SetBranchAddress("FSRphotonllM", &FSRphotonllM, &b_FSRphotonllM);
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
  fChain->SetBranchAddress("lepId", &lepId, &b_lepId);
  // ---- jet variables -------------------------------------------------
  fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
  fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
  fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
  fChain->SetBranchAddress("jetE", &jetE, &b_jetE);
//  fChain->SetBranchAddress("jetY", &jetY, &b_jetY);
  fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
  fChain->SetBranchAddress("jetBeta", &jetBeta, &b_jetBeta);
  fChain->SetBranchAddress("jetQGL", &jetQGL, &b_jetQGL);
  fChain->SetBranchAddress("jetRMS", &jetRMS, &b_jetRMS);
  fChain->SetBranchAddress("jetBtag", &jetBtag, &b_jetBtag);
  fChain->SetBranchAddress("jetTagInfoNVtx", &jetTagInfoNVtx, &b_jetTagInfoNVtx);
  fChain->SetBranchAddress("jetTagInfoNTracks", &jetTagInfoNTracks, &b_jetTagInfoNTracks);
  fChain->SetBranchAddress("jetTagInfoVtxMass", &jetTagInfoVtxMass, &b_jetTagInfoVtxMass);
  fChain->SetBranchAddress("jetMCFlavour", &jetMCFlavour, &b_jetMCFlavour);
  fChain->SetBranchAddress("jetJEC", &jetJEC, &b_jetJEC);
  fChain->SetBranchAddress("jetUNC", &jetUNC, &b_jetUNC);
  fChain->SetBranchAddress("jetllDPhi", &jetllDPhi, &b_jetllDPhi);
//  fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
//  fChain->SetBranchAddress("jetPHF", &jetPHF, &b_jetPHF);
//  fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
//  fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
//  fChain->SetBranchAddress("jetELF", &jetELF, &b_jetELF);
//  fChain->SetBranchAddress("jetId", &jetId, &b_jetId);
  // ---- DR rejected jet variables ------------------------------------
//  fChain->SetBranchAddress("rjetPt", &rjetPt, &b_rjetPt);
//  fChain->SetBranchAddress("rjetEta", &rjetEta, &b_rjetEta);
//  fChain->SetBranchAddress("rjetPhi", &rjetPhi, &b_rjetPhi);
//  fChain->SetBranchAddress("rjetE", &rjetE, &b_rjetE);
//  fChain->SetBranchAddress("rjetY", &rjetY, &b_rjetY);
//  fChain->SetBranchAddress("rjetArea", &rjetArea, &b_rjetArea);
//  fChain->SetBranchAddress("rjetBeta", &rjetBeta, &b_rjetBeta);
//  fChain->SetBranchAddress("rjetBtag", &rjetBtag, &b_rjetBtag);
//  fChain->SetBranchAddress("rjetJEC", &rjetJEC, &b_rjetJEC);
//  fChain->SetBranchAddress("rjetUNC", &rjetUNC, &b_rjetUNC);
//  fChain->SetBranchAddress("rjetCHF", &rjetCHF, &b_rjetCHF);
//  fChain->SetBranchAddress("rjetPHF", &rjetPHF, &b_rjetPHF);
//  fChain->SetBranchAddress("rjetNHF", &rjetNHF, &b_rjetNHF);
//  fChain->SetBranchAddress("rjetMUF", &rjetMUF, &b_rjetMUF);
//  fChain->SetBranchAddress("rjetELF", &rjetELF, &b_rjetELF);
//  fChain->SetBranchAddress("rjetId", &rjetId, &b_rjetId);
  // ---- vertex variables ----------------------------------------------
  fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
  fChain->SetBranchAddress("vtxNdof", &vtxNdof, &b_vtxNdof);
  // ---- gen variables ----------------------------------------------
//  fChain->SetBranchAddress("selGEN", &selGEN, &b_selGEN);
  fChain->SetBranchAddress("puINT", &puINT, &b_puINT);
  fChain->SetBranchAddress("puTrueINT", &puTrueINT, &b_puTrueINT);
  fChain->SetBranchAddress("puOOT", &puOOT, &b_puOOT);
  fChain->SetBranchAddress("puTrueOOT", &puTrueOOT, &b_puTrueOOT);
  fChain->SetBranchAddress("nLeptonsGEN", &nLeptonsGEN, &b_nLeptonsGEN);
  fChain->SetBranchAddress("nJetsGEN", &nJetsGEN, &b_nJetsGEN);
//  fChain->SetBranchAddress("isZleadGEN", &isZleadGEN, &b_isZleadGEN);
//  fChain->SetBranchAddress("mZj1GEN", &mZj1GEN, &b_mZj1GEN);
//  fChain->SetBranchAddress("ptZj1GEN", &ptZj1GEN, &b_ptZj1GEN);
//  fChain->SetBranchAddress("costhetaZj1GEN", &costhetaZj1GEN, &b_costhetaZj1GEN);
//  fChain->SetBranchAddress("mj1j2GEN", &mj1j2GEN, &b_mj1j2GEN);
//  fChain->SetBranchAddress("mLepGEN", &mLepGEN, &b_mLepGEN);
//  fChain->SetBranchAddress("htLeadGEN", &htLeadGEN, &b_htLeadGEN);
//  fChain->SetBranchAddress("j1j2DPhiGEN", &j1j2DPhiGEN, &b_j1j2DPhiGEN);
//  fChain->SetBranchAddress("j1j3DPhiGEN", &j1j3DPhiGEN, &b_j1j3DPhiGEN);
//  fChain->SetBranchAddress("j2j3DPhiGEN", &j2j3DPhiGEN, &b_j2j3DPhiGEN);
//  fChain->SetBranchAddress("j1j2DRGEN", &j1j2DRGEN, &b_j1j2DRGEN);
//  fChain->SetBranchAddress("j1j3DRGEN", &j1j3DRGEN, &b_j1j3DRGEN);
//  fChain->SetBranchAddress("j2j3DRGEN", &j2j3DRGEN, &b_j2j3DRGEN);
//  fChain->SetBranchAddress("jetPtGeMeanGEN", &jetPtGeMeanGEN, &b_jetPtGeMeanGEN);
//  fChain->SetBranchAddress("jetPtArMeanGEN", &jetPtArMeanGEN, &b_jetPtArMeanGEN);
  fChain->SetBranchAddress("jetVeto", &jetVeto, &b_jetVeto);
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
//  fChain->SetBranchAddress("HTJetSumGEN", &HTJetSumGEN, &b_HTJetSumGEN);
  fChain->SetBranchAddress("HTParSum", &HTParSum, &b_HTParSum);  
  fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
  fChain->SetBranchAddress("nPhotonsGEN", &nPhotonsGEN, &b_nPhotonsGEN);
  fChain->SetBranchAddress("photonPtGEN", &photonPtGEN, &b_photonPtGEN);
  fChain->SetBranchAddress("photonEGEN", &photonEGEN, &b_photonEGEN);
  fChain->SetBranchAddress("photonEtaGEN", &photonEtaGEN, &b_photonEtaGEN);
  fChain->SetBranchAddress("photonPhiGEN", &photonPhiGEN, &b_photonPhiGEN);
  fChain->SetBranchAddress("photonMotherIdGEN", &photonMotherIdGEN, &b_photonMotherIdGEN);
  fChain->SetBranchAddress("photonRECODRGEN", &photonRECODRGEN, &b_photonRECODRGEN);
  fChain->SetBranchAddress("VBPartonDM", &VBPartonDM, &b_VBPartonDM);
  fChain->SetBranchAddress("VBPartonM", &VBPartonM, &b_VBPartonM);
  fChain->SetBranchAddress("VBPartonE", &VBPartonE, &b_VBPartonE);
  fChain->SetBranchAddress("VBPartonPt", &VBPartonPt, &b_VBPartonPt);
  fChain->SetBranchAddress("VBPartonEta", &VBPartonEta, &b_VBPartonEta);
  fChain->SetBranchAddress("VBPartonPhi", &VBPartonPhi, &b_VBPartonPhi);
  fChain->SetBranchAddress("QGVars", &QGVars, &b_QGVars);
  fChain->SetBranchAddress("lepSigmaIEtaIEta", &lepSigmaIEtaIEta, &b_lepSigmaIEtaIEta);
  fChain->SetBranchAddress("lepHadronicOverEm", &lepHadronicOverEm, &b_lepHadronicOverEm);
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
//	cout << "entry = " << entry << endl;
  return 1;
}

#endif // #ifdef GJetsAnalyzer_cxx
