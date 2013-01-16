//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 24 10:33:24 2012 by ROOT version 5.27/06b
// from TTree events/events
// found on file: /data/zjets/V02-02-02/data_merged/all_photons.root
//////////////////////////////////////////////////////////

#ifndef GJetsClass_h
#define GJetsClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class GJetsClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           isRealData;
   Int_t           selRECO;
   ULong64_t       eventNum;
   Int_t           runNum;
   Int_t           lumi;
   Int_t           nVtx;
   Int_t           nLeptons;
   Int_t           nPhotons;
   Int_t           nJets;
   Int_t           nRJets;
   Int_t           isZlead;
   Int_t           isPhotonlead;
   Float_t         rho;
   Float_t         rho25;
   Float_t         mZj1;
   Float_t         mZj1j2;
   Float_t         mZj1j2j3;
   Float_t         ptZj1;
   Float_t         costhetaZj1;
   Float_t         costhetaPhotonj1;
   Float_t         mj1j2;
   Float_t         mj1j2j3;
   Float_t         mrj1rj2;
   Float_t         mLep;
   Float_t         htLead;
   Float_t         j1j2DPhi;
   Float_t         j1j3DPhi;
   Float_t         j2j3DPhi;
   Float_t         j1j2DR;
   Float_t         j1j3DR;
   Float_t         j2j3DR;
   Float_t         jetPtGeMean;
   Float_t         jetPtArMean;
   Float_t         pfmet;
   Float_t         pfmetPhi;
   Float_t         pfhadPt;
   Float_t         pfSumEt;
   Float_t         HTJetSum;
   Float_t         llM;
   Float_t         llPt;
   Float_t         llPhi;
   Float_t         llDPhi;
   Float_t         llY;
   Float_t         llEta;
   Float_t         photonPt;
   Float_t         photonE;
   Float_t         photonEta;
   Float_t         photonPhi;
   Float_t         photonIso;
   Float_t         photonID;
   Int_t           photonBit;
   Float_t         pfhadPhoPt;
   Float_t         mPhotonj1;
   Float_t         ptPhotonj1;
   vector<float>   *jetPhotonDPhi;
   vector<float>   *photonPar;
   Float_t         FSRphotonPt;
   Float_t         FSRphotonE;
   Float_t         FSRphotonEta;
   Float_t         FSRphotonPhi;
   Float_t         FSRphotonIso;
   Float_t         FSRphotonID;
   Int_t           FSRphotonBit;
   Int_t           FSRphotonJet;
   vector<float>   *FSRphotonPar;
   Float_t         FSRphotonllM;
   vector<int>     *fired;
   vector<int>     *prescaleL1;
   vector<int>     *prescaleHLT;
   Int_t           isTriggered;
   vector<float>   *lepPt;
   vector<float>   *lepEta;
   vector<float>   *lepPhi;
   vector<float>   *lepE;
   vector<float>   *lepIso;
   vector<float>   *lepIsoPF;
   vector<float>   *lepIsoRho;
   vector<int>     *lepChId;
   vector<int>     *lepId;
   vector<float>   *jetPt;
   vector<float>   *jetEta;
   vector<float>   *jetPhi;
   vector<float>   *jetE;
   vector<float>   *jetY;
   vector<float>   *jetArea;
   vector<float>   *jetBeta;
   vector<float>   *jetBetaStar;
   vector<float>   *jetJEC;
   vector<float>   *jetUNC;
   vector<float>   *jetllDPhi;
   vector<float>   *jetCHF;
   vector<float>   *jetPHF;
   vector<float>   *jetNHF;
   vector<float>   *jetMUF;
   vector<float>   *jetELF;
   vector<int>     *jetId;
   vector<float>   *rjetPt;
   vector<float>   *rjetEta;
   vector<float>   *rjetPhi;
   vector<float>   *rjetE;
   vector<float>   *rjetY;
   vector<float>   *rjetArea;
   vector<float>   *rjetBeta;
   vector<float>   *rjetBetaStar;
   vector<float>   *rjetJEC;
   vector<float>   *rjetUNC;
   vector<float>   *rjetCHF;
   vector<float>   *rjetPHF;
   vector<float>   *rjetNHF;
   vector<float>   *rjetMUF;
   vector<float>   *rjetELF;
   vector<int>     *rjetId;
   vector<float>   *vtxZ;
   vector<float>   *vtxNdof;
   Int_t           selGEN;
   Int_t           puINT;
   Int_t           puOOT;
   Int_t           nLeptonsGEN;
   Int_t           nJetsGEN;
   Int_t           isZleadGEN;
   Float_t         mZj1GEN;
   Float_t         ptZj1GEN;
   Float_t         costhetaZj1GEN;
   Float_t         mj1j2GEN;
   Float_t         mLepGEN;
   Float_t         htLeadGEN;
   Float_t         j1j2DPhiGEN;
   Float_t         j1j3DPhiGEN;
   Float_t         j2j3DPhiGEN;
   Float_t         j1j2DRGEN;
   Float_t         j1j3DRGEN;
   Float_t         j2j3DRGEN;
   Float_t         jetPtGeMeanGEN;
   Float_t         jetPtArMeanGEN;
   Float_t         llMGEN;
   Float_t         llPtGEN;
   Float_t         llPhiGEN;
   Float_t         llDPhiGEN;
   Float_t         llYGEN;
   Float_t         llEtaGEN;
   vector<float>   *lepPtGEN;
   vector<float>   *lepEtaGEN;
   vector<float>   *lepPhiGEN;
   vector<float>   *lepEGEN;
   vector<int>     *lepChIdGEN;
   vector<float>   *lepMatchedDRGEN;
   vector<int>     *lepMatchedGEN;
   vector<float>   *jetPtGEN;
   vector<float>   *jetEtaGEN;
   vector<float>   *jetPhiGEN;
   vector<float>   *jetEGEN;
   vector<float>   *jetllDPhiGEN;
   Float_t         HTJetSumGEN;
   Float_t         mcWeight;
   Int_t           nPhotonsGEN;
   Float_t         photonPtGEN;
   Float_t         photonEGEN;
   Float_t         photonEtaGEN;
   Float_t         photonPhiGEN;
   Float_t         photonRECODRGEN;
   Int_t           VBPartonDM;
   Float_t         VBPartonM;
   Float_t         VBPartonE;
   Float_t         VBPartonPt;
   Float_t         VBPartonEta;
   Float_t         VBPartonPhi;
   Double_t        eventWeight;
   Double_t        PUWeight;
   Int_t           nJets50;

   // List of branches
   TBranch        *b_isRealData;   //!
   TBranch        *b_selRECO;   //!
   TBranch        *b_eventNum;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nLeptons;   //!
   TBranch        *b_nPhotons;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_nRJets;   //!
   TBranch        *b_isZlead;   //!
   TBranch        *b_isPhotonlead;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rho25;   //!
   TBranch        *b_mZj1;   //!
   TBranch        *b_mZj1j2;   //!
   TBranch        *b_mZj1j2j3;   //!
   TBranch        *b_ptZj1;   //!
   TBranch        *b_costhetaZj1;   //!
   TBranch        *b_costhetaPhotonj1;   //!
   TBranch        *b_mj1j2;   //!
   TBranch        *b_mj1j2j3;   //!
   TBranch        *b_mrj1rj2;   //!
   TBranch        *b_mLep;   //!
   TBranch        *b_htLead;   //!
   TBranch        *b_j1j2DPhi;   //!
   TBranch        *b_j1j3DPhi;   //!
   TBranch        *b_j2j3DPhi;   //!
   TBranch        *b_j1j2DR;   //!
   TBranch        *b_j1j3DR;   //!
   TBranch        *b_j2j3DR;   //!
   TBranch        *b_jetPtGeMean;   //!
   TBranch        *b_jetPtArMean;   //!
   TBranch        *b_pfmet;   //!
   TBranch        *b_pfmetPhi;   //!
   TBranch        *b_pfhadPt;   //!
   TBranch        *b_pfSumEt;   //!
   TBranch        *b_HTJetSum;   //!
   TBranch        *b_llM;   //!
   TBranch        *b_llPt;   //!
   TBranch        *b_llPhi;   //!
   TBranch        *b_llDPhi;   //!
   TBranch        *b_llY;   //!
   TBranch        *b_llEta;   //!
   TBranch        *b_photonPt;   //!
   TBranch        *b_photonE;   //!
   TBranch        *b_photonEta;   //!
   TBranch        *b_photonPhi;   //!
   TBranch        *b_photonIso;   //!
   TBranch        *b_photonID;   //!
   TBranch        *b_photonBit;   //!
   TBranch        *b_pfhadPhoPt;   //!
   TBranch        *b_mPhotonj1;   //!
   TBranch        *b_ptPhotonj1;   //!
   TBranch        *b_jetPhotonDPhi;   //!
   TBranch        *b_photonPar;   //!
   TBranch        *b_FSRphotonPt;   //!
   TBranch        *b_FSRphotonE;   //!
   TBranch        *b_FSRphotonEta;   //!
   TBranch        *b_FSRphotonPhi;   //!
   TBranch        *b_FSRphotonIso;   //!
   TBranch        *b_FSRphotonID;   //!
   TBranch        *b_FSRphotonBit;   //!
   TBranch        *b_FSRphotonJet;   //!
   TBranch        *b_FSRphotonPar;   //!
   TBranch        *b_FSRphotonllM;   //!
   TBranch        *b_fired;   //!
   TBranch        *b_prescaleL1;   //!
   TBranch        *b_prescaleHLT;   //!
   TBranch        *b_isTriggered;   //!
   TBranch        *b_lepPt;   //!
   TBranch        *b_lepEta;   //!
   TBranch        *b_lepPhi;   //!
   TBranch        *b_lepE;   //!
   TBranch        *b_lepIso;   //!
   TBranch        *b_lepIsoPF;   //!
   TBranch        *b_lepIsoRho;   //!
   TBranch        *b_lepChId;   //!
   TBranch        *b_lepId;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetE;   //!
   TBranch        *b_jetY;   //!
   TBranch        *b_jetArea;   //!
   TBranch        *b_jetBeta;   //!
   TBranch        *b_jetBetaStar;   //!
   TBranch        *b_jetJEC;   //!
   TBranch        *b_jetUNC;   //!
   TBranch        *b_jetllDPhi;   //!
   TBranch        *b_jetCHF;   //!
   TBranch        *b_jetPHF;   //!
   TBranch        *b_jetNHF;   //!
   TBranch        *b_jetMUF;   //!
   TBranch        *b_jetELF;   //!
   TBranch        *b_jetId;   //!
   TBranch        *b_rjetPt;   //!
   TBranch        *b_rjetEta;   //!
   TBranch        *b_rjetPhi;   //!
   TBranch        *b_rjetE;   //!
   TBranch        *b_rjetY;   //!
   TBranch        *b_rjetArea;   //!
   TBranch        *b_rjetBeta;   //!
   TBranch        *b_rjetBetaStar;   //!
   TBranch        *b_rjetJEC;   //!
   TBranch        *b_rjetUNC;   //!
   TBranch        *b_rjetCHF;   //!
   TBranch        *b_rjetPHF;   //!
   TBranch        *b_rjetNHF;   //!
   TBranch        *b_rjetMUF;   //!
   TBranch        *b_rjetELF;   //!
   TBranch        *b_rjetId;   //!
   TBranch        *b_vtxZ;   //!
   TBranch        *b_vtxNdof;   //!
   TBranch        *b_selGEN;   //!
   TBranch        *b_puINT;   //!
   TBranch        *b_puOOT;   //!
   TBranch        *b_nLeptonsGEN;   //!
   TBranch        *b_nJetsGEN;   //!
   TBranch        *b_isZleadGEN;   //!
   TBranch        *b_mZj1GEN;   //!
   TBranch        *b_ptZj1GEN;   //!
   TBranch        *b_costhetaZj1GEN;   //!
   TBranch        *b_mj1j2GEN;   //!
   TBranch        *b_mLepGEN;   //!
   TBranch        *b_htLeadGEN;   //!
   TBranch        *b_j1j2DPhiGEN;   //!
   TBranch        *b_j1j3DPhiGEN;   //!
   TBranch        *b_j2j3DPhiGEN;   //!
   TBranch        *b_j1j2DRGEN;   //!
   TBranch        *b_j1j3DRGEN;   //!
   TBranch        *b_j2j3DRGEN;   //!
   TBranch        *b_jetPtGeMeanGEN;   //!
   TBranch        *b_jetPtArMeanGEN;   //!
   TBranch        *b_llMGEN;   //!
   TBranch        *b_llPtGEN;   //!
   TBranch        *b_llPhiGEN;   //!
   TBranch        *b_llDPhiGEN;   //!
   TBranch        *b_llYGEN;   //!
   TBranch        *b_llEtaGEN;   //!
   TBranch        *b_lepPtGEN;   //!
   TBranch        *b_lepEtaGEN;   //!
   TBranch        *b_lepPhiGEN;   //!
   TBranch        *b_lepEGEN;   //!
   TBranch        *b_lepChIdGEN;   //!
   TBranch        *b_lepMatchedDRGEN;   //!
   TBranch        *b_lepMatchedGEN;   //!
   TBranch        *b_jetPtGEN;   //!
   TBranch        *b_jetEtaGEN;   //!
   TBranch        *b_jetPhiGEN;   //!
   TBranch        *b_jetEGEN;   //!
   TBranch        *b_jetllDPhiGEN;   //!
   TBranch        *b_HTJetSumGEN;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_nPhotonsGEN;   //!
   TBranch        *b_photonPtGEN;   //!
   TBranch        *b_photonEGEN;   //!
   TBranch        *b_photonEtaGEN;   //!
   TBranch        *b_photonPhiGEN;   //!
   TBranch        *b_photonRECODRGEN;   //!
   TBranch        *b_VBPartonDM;   //!
   TBranch        *b_VBPartonM;   //!
   TBranch        *b_VBPartonE;   //!
   TBranch        *b_VBPartonPt;   //!
   TBranch        *b_VBPartonEta;   //!
   TBranch        *b_VBPartonPhi;   //!
   TBranch        *b_eventWeight;   //!
   TBranch        *b_PUWeight;   //!
   TBranch        *b_nJets50;   //!

   GJetsClass(TTree *tree=0);
   virtual ~GJetsClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(Int_t isample);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef GJetsClass_cxx
GJetsClass::GJetsClass(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

     Int_t isample=3;

     if(isample==0){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/data_merged/all_photons.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/data_merged/all_photons.root");
         f->cd("/data/zjets/V02-02-02/data_merged/all_photons.root:/accepted");
      }
     }
    
     else if(isample==1){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_40_HT_100_7TeV-madgraph.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_40_HT_100_7TeV-madgraph.root");
         f->cd("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_40_HT_100_7TeV-madgraph.root:/accepted");
      }
     }

     else if(isample==2){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_100_HT_200_7TeV-madgraph.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_100_HT_200_7TeV-madgraph.root");
         f->cd("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_100_HT_200_7TeV-madgraph.root:/accepted");
      }
     }
    

     else if(isample==3){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_200_HT_inf_7TeV-madgraph.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_200_HT_inf_7TeV-madgraph.root");
         f->cd("/data/zjets/V02-02-02/mc/files/GJets_TuneZ2_200_HT_inf_7TeV-madgraph.root:/accepted");
      }
     }

     else if(isample==4){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-250To500_7TeV-madgraph.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-250To500_7TeV-madgraph.root");
         f->cd("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-250To500_7TeV-madgraph.root:/accepted");
      }
     }

     else if(isample==5){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-500To1000_7TeV-madgraph.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-500To1000_7TeV-madgraph.root");
         f->cd("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-500To1000_7TeV-madgraph.root:/accepted");
      }
     }

      else if(isample==6){
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-1000_7TeV-madgraph.root");
      if (!f) {
         f = new TFile("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-1000_7TeV-madgraph.root");
         f->cd("/data/zjets/V02-02-02/mc/files/QCD_TuneZ2_HT-1000_7TeV-madgraph.root:/accepted");
      }
     }
   




      tree = (TTree*)gDirectory->Get("events");

   }
   Init(tree);
}

GJetsClass::~GJetsClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GJetsClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GJetsClass::LoadTree(Long64_t entry)
{
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

void GJetsClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jetPhotonDPhi = 0;
   photonPar = 0;
   FSRphotonPar = 0;
   fired = 0;
   prescaleL1 = 0;
   prescaleHLT = 0;
   lepPt = 0;
   lepEta = 0;
   lepPhi = 0;
   lepE = 0;
   lepIso = 0;
   lepIsoPF = 0;
   lepIsoRho = 0;
   lepChId = 0;
   lepId = 0;
   jetPt = 0;
   jetEta = 0;
   jetPhi = 0;
   jetE = 0;
   jetY = 0;
   jetArea = 0;
   jetBeta = 0;
   jetBetaStar = 0;
   jetJEC = 0;
   jetUNC = 0;
   jetllDPhi = 0;
   jetCHF = 0;
   jetPHF = 0;
   jetNHF = 0;
   jetMUF = 0;
   jetELF = 0;
   jetId = 0;
   rjetPt = 0;
   rjetEta = 0;
   rjetPhi = 0;
   rjetE = 0;
   rjetY = 0;
   rjetArea = 0;
   rjetBeta = 0;
   rjetBetaStar = 0;
   rjetJEC = 0;
   rjetUNC = 0;
   rjetCHF = 0;
   rjetPHF = 0;
   rjetNHF = 0;
   rjetMUF = 0;
   rjetELF = 0;
   rjetId = 0;
   vtxZ = 0;
   vtxNdof = 0;
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
   jetllDPhiGEN = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("isRealData", &isRealData, &b_isRealData);
   fChain->SetBranchAddress("selRECO", &selRECO, &b_selRECO);
   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
   fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nLeptons", &nLeptons, &b_nLeptons);
   fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("nRJets", &nRJets, &b_nRJets);
   fChain->SetBranchAddress("isZlead", &isZlead, &b_isZlead);
   fChain->SetBranchAddress("isPhotonlead", &isPhotonlead, &b_isPhotonlead);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rho25", &rho25, &b_rho25);
   fChain->SetBranchAddress("mZj1", &mZj1, &b_mZj1);
   fChain->SetBranchAddress("mZj1j2", &mZj1j2, &b_mZj1j2);
   fChain->SetBranchAddress("mZj1j2j3", &mZj1j2j3, &b_mZj1j2j3);
   fChain->SetBranchAddress("ptZj1", &ptZj1, &b_ptZj1);
   fChain->SetBranchAddress("costhetaZj1", &costhetaZj1, &b_costhetaZj1);
   fChain->SetBranchAddress("costhetaPhotonj1", &costhetaPhotonj1, &b_costhetaPhotonj1);
   fChain->SetBranchAddress("mj1j2", &mj1j2, &b_mj1j2);
   fChain->SetBranchAddress("mj1j2j3", &mj1j2j3, &b_mj1j2j3);
   fChain->SetBranchAddress("mrj1rj2", &mrj1rj2, &b_mrj1rj2);
   fChain->SetBranchAddress("mLep", &mLep, &b_mLep);
   fChain->SetBranchAddress("htLead", &htLead, &b_htLead);
   fChain->SetBranchAddress("j1j2DPhi", &j1j2DPhi, &b_j1j2DPhi);
   fChain->SetBranchAddress("j1j3DPhi", &j1j3DPhi, &b_j1j3DPhi);
   fChain->SetBranchAddress("j2j3DPhi", &j2j3DPhi, &b_j2j3DPhi);
   fChain->SetBranchAddress("j1j2DR", &j1j2DR, &b_j1j2DR);
   fChain->SetBranchAddress("j1j3DR", &j1j3DR, &b_j1j3DR);
   fChain->SetBranchAddress("j2j3DR", &j2j3DR, &b_j2j3DR);
   fChain->SetBranchAddress("jetPtGeMean", &jetPtGeMean, &b_jetPtGeMean);
   fChain->SetBranchAddress("jetPtArMean", &jetPtArMean, &b_jetPtArMean);
   fChain->SetBranchAddress("pfmet", &pfmet, &b_pfmet);
   fChain->SetBranchAddress("pfmetPhi", &pfmetPhi, &b_pfmetPhi);
   fChain->SetBranchAddress("pfhadPt", &pfhadPt, &b_pfhadPt);
   fChain->SetBranchAddress("pfSumEt", &pfSumEt, &b_pfSumEt);
   fChain->SetBranchAddress("HTJetSum", &HTJetSum, &b_HTJetSum);
   fChain->SetBranchAddress("llM", &llM, &b_llM);
   fChain->SetBranchAddress("llPt", &llPt, &b_llPt);
   fChain->SetBranchAddress("llPhi", &llPhi, &b_llPhi);
   fChain->SetBranchAddress("llDPhi", &llDPhi, &b_llDPhi);
   fChain->SetBranchAddress("llY", &llY, &b_llY);
   fChain->SetBranchAddress("llEta", &llEta, &b_llEta);
   fChain->SetBranchAddress("photonPt", &photonPt, &b_photonPt);
   fChain->SetBranchAddress("photonE", &photonE, &b_photonE);
   fChain->SetBranchAddress("photonEta", &photonEta, &b_photonEta);
   fChain->SetBranchAddress("photonPhi", &photonPhi, &b_photonPhi);
   fChain->SetBranchAddress("photonIso", &photonIso, &b_photonIso);
   fChain->SetBranchAddress("photonID", &photonID, &b_photonID);
   fChain->SetBranchAddress("photonBit", &photonBit, &b_photonBit);
   fChain->SetBranchAddress("pfhadPhoPt", &pfhadPhoPt, &b_pfhadPhoPt);
   fChain->SetBranchAddress("mPhotonj1", &mPhotonj1, &b_mPhotonj1);
   fChain->SetBranchAddress("ptPhotonj1", &ptPhotonj1, &b_ptPhotonj1);
   fChain->SetBranchAddress("jetPhotonDPhi", &jetPhotonDPhi, &b_jetPhotonDPhi);
   fChain->SetBranchAddress("photonPar", &photonPar, &b_photonPar);
   fChain->SetBranchAddress("FSRphotonPt", &FSRphotonPt, &b_FSRphotonPt);
   fChain->SetBranchAddress("FSRphotonE", &FSRphotonE, &b_FSRphotonE);
   fChain->SetBranchAddress("FSRphotonEta", &FSRphotonEta, &b_FSRphotonEta);
   fChain->SetBranchAddress("FSRphotonPhi", &FSRphotonPhi, &b_FSRphotonPhi);
   fChain->SetBranchAddress("FSRphotonIso", &FSRphotonIso, &b_FSRphotonIso);
   fChain->SetBranchAddress("FSRphotonID", &FSRphotonID, &b_FSRphotonID);
   fChain->SetBranchAddress("FSRphotonBit", &FSRphotonBit, &b_FSRphotonBit);
   fChain->SetBranchAddress("FSRphotonJet", &FSRphotonJet, &b_FSRphotonJet);
   fChain->SetBranchAddress("FSRphotonPar", &FSRphotonPar, &b_FSRphotonPar);
   fChain->SetBranchAddress("FSRphotonllM", &FSRphotonllM, &b_FSRphotonllM);
   fChain->SetBranchAddress("fired", &fired, &b_fired);
   fChain->SetBranchAddress("prescaleL1", &prescaleL1, &b_prescaleL1);
   fChain->SetBranchAddress("prescaleHLT", &prescaleHLT, &b_prescaleHLT);
   fChain->SetBranchAddress("isTriggered", &isTriggered, &b_isTriggered);
   fChain->SetBranchAddress("lepPt", &lepPt, &b_lepPt);
   fChain->SetBranchAddress("lepEta", &lepEta, &b_lepEta);
   fChain->SetBranchAddress("lepPhi", &lepPhi, &b_lepPhi);
   fChain->SetBranchAddress("lepE", &lepE, &b_lepE);
   fChain->SetBranchAddress("lepIso", &lepIso, &b_lepIso);
   fChain->SetBranchAddress("lepIsoPF", &lepIsoPF, &b_lepIsoPF);
   fChain->SetBranchAddress("lepIsoRho", &lepIsoRho, &b_lepIsoRho);
   fChain->SetBranchAddress("lepChId", &lepChId, &b_lepChId);
   fChain->SetBranchAddress("lepId", &lepId, &b_lepId);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetE", &jetE, &b_jetE);
   fChain->SetBranchAddress("jetY", &jetY, &b_jetY);
   fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
   fChain->SetBranchAddress("jetBeta", &jetBeta, &b_jetBeta);
   fChain->SetBranchAddress("jetBetaStar", &jetBetaStar, &b_jetBetaStar);
   fChain->SetBranchAddress("jetJEC", &jetJEC, &b_jetJEC);
   fChain->SetBranchAddress("jetUNC", &jetUNC, &b_jetUNC);
   fChain->SetBranchAddress("jetllDPhi", &jetllDPhi, &b_jetllDPhi);
   fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
   fChain->SetBranchAddress("jetPHF", &jetPHF, &b_jetPHF);
   fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
   fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
   fChain->SetBranchAddress("jetELF", &jetELF, &b_jetELF);
   fChain->SetBranchAddress("jetId", &jetId, &b_jetId);
   fChain->SetBranchAddress("rjetPt", &rjetPt, &b_rjetPt);
   fChain->SetBranchAddress("rjetEta", &rjetEta, &b_rjetEta);
   fChain->SetBranchAddress("rjetPhi", &rjetPhi, &b_rjetPhi);
   fChain->SetBranchAddress("rjetE", &rjetE, &b_rjetE);
   fChain->SetBranchAddress("rjetY", &rjetY, &b_rjetY);
   fChain->SetBranchAddress("rjetArea", &rjetArea, &b_rjetArea);
   fChain->SetBranchAddress("rjetBeta", &rjetBeta, &b_rjetBeta);
   fChain->SetBranchAddress("rjetBetaStar", &rjetBetaStar, &b_rjetBetaStar);
   fChain->SetBranchAddress("rjetJEC", &rjetJEC, &b_rjetJEC);
   fChain->SetBranchAddress("rjetUNC", &rjetUNC, &b_rjetUNC);
   fChain->SetBranchAddress("rjetCHF", &rjetCHF, &b_rjetCHF);
   fChain->SetBranchAddress("rjetPHF", &rjetPHF, &b_rjetPHF);
   fChain->SetBranchAddress("rjetNHF", &rjetNHF, &b_rjetNHF);
   fChain->SetBranchAddress("rjetMUF", &rjetMUF, &b_rjetMUF);
   fChain->SetBranchAddress("rjetELF", &rjetELF, &b_rjetELF);
   fChain->SetBranchAddress("rjetId", &rjetId, &b_rjetId);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
   fChain->SetBranchAddress("vtxNdof", &vtxNdof, &b_vtxNdof);
   fChain->SetBranchAddress("selGEN", &selGEN, &b_selGEN);
   fChain->SetBranchAddress("puINT", &puINT, &b_puINT);
   fChain->SetBranchAddress("puOOT", &puOOT, &b_puOOT);
   fChain->SetBranchAddress("nLeptonsGEN", &nLeptonsGEN, &b_nLeptonsGEN);
   fChain->SetBranchAddress("nJetsGEN", &nJetsGEN, &b_nJetsGEN);
   fChain->SetBranchAddress("isZleadGEN", &isZleadGEN, &b_isZleadGEN);
   fChain->SetBranchAddress("mZj1GEN", &mZj1GEN, &b_mZj1GEN);
   fChain->SetBranchAddress("ptZj1GEN", &ptZj1GEN, &b_ptZj1GEN);
   fChain->SetBranchAddress("costhetaZj1GEN", &costhetaZj1GEN, &b_costhetaZj1GEN);
   fChain->SetBranchAddress("mj1j2GEN", &mj1j2GEN, &b_mj1j2GEN);
   fChain->SetBranchAddress("mLepGEN", &mLepGEN, &b_mLepGEN);
   fChain->SetBranchAddress("htLeadGEN", &htLeadGEN, &b_htLeadGEN);
   fChain->SetBranchAddress("j1j2DPhiGEN", &j1j2DPhiGEN, &b_j1j2DPhiGEN);
   fChain->SetBranchAddress("j1j3DPhiGEN", &j1j3DPhiGEN, &b_j1j3DPhiGEN);
   fChain->SetBranchAddress("j2j3DPhiGEN", &j2j3DPhiGEN, &b_j2j3DPhiGEN);
   fChain->SetBranchAddress("j1j2DRGEN", &j1j2DRGEN, &b_j1j2DRGEN);
   fChain->SetBranchAddress("j1j3DRGEN", &j1j3DRGEN, &b_j1j3DRGEN);
   fChain->SetBranchAddress("j2j3DRGEN", &j2j3DRGEN, &b_j2j3DRGEN);
   fChain->SetBranchAddress("jetPtGeMeanGEN", &jetPtGeMeanGEN, &b_jetPtGeMeanGEN);
   fChain->SetBranchAddress("jetPtArMeanGEN", &jetPtArMeanGEN, &b_jetPtArMeanGEN);
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
   fChain->SetBranchAddress("jetllDPhiGEN", &jetllDPhiGEN, &b_jetllDPhiGEN);
   fChain->SetBranchAddress("HTJetSumGEN", &HTJetSumGEN, &b_HTJetSumGEN);
   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("nPhotonsGEN", &nPhotonsGEN, &b_nPhotonsGEN);
   fChain->SetBranchAddress("photonPtGEN", &photonPtGEN, &b_photonPtGEN);
   fChain->SetBranchAddress("photonEGEN", &photonEGEN, &b_photonEGEN);
   fChain->SetBranchAddress("photonEtaGEN", &photonEtaGEN, &b_photonEtaGEN);
   fChain->SetBranchAddress("photonPhiGEN", &photonPhiGEN, &b_photonPhiGEN);
   fChain->SetBranchAddress("photonRECODRGEN", &photonRECODRGEN, &b_photonRECODRGEN);
   fChain->SetBranchAddress("VBPartonDM", &VBPartonDM, &b_VBPartonDM);
   fChain->SetBranchAddress("VBPartonM", &VBPartonM, &b_VBPartonM);
   fChain->SetBranchAddress("VBPartonE", &VBPartonE, &b_VBPartonE);
   fChain->SetBranchAddress("VBPartonPt", &VBPartonPt, &b_VBPartonPt);
   fChain->SetBranchAddress("VBPartonEta", &VBPartonEta, &b_VBPartonEta);
   fChain->SetBranchAddress("VBPartonPhi", &VBPartonPhi, &b_VBPartonPhi);
   fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
   fChain->SetBranchAddress("PUWeight", &PUWeight, &b_PUWeight);
   fChain->SetBranchAddress("nJets50", &nJets50, &b_nJets50);
   Notify();
}

Bool_t GJetsClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GJetsClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GJetsClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GJetsClass_cxx
