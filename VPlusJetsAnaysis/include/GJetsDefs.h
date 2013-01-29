// put definitions here

// histograms
TH1F *ptPhotonGEN_, *ptPhotonREC_; 
TH1F *DeltaRGENREC_;

TH1F *Nvtx_;
TH1F *nPhotons_;
TH1F *nJets_;
TH1F *ptPhoton_, *etaPhoton_;
TH1F *ptjet1_, *etajet1_, *phijet1_;

void Book_Histos();
void Plot_Histos();
void Zero_Variables();
float deltaPhi(float, float);

// variables
Char_t outputname[100];
Float_t ptGENjet1, etaGENjet1;
Float_t ptjet1, etajet1, phijet1;
Float_t ptPhoton, etaPhoton, phiPhoton;

//counters
Int_t iSelected;
//, iSelected1, iSelected2, iSelected3, iSelected4, iSelected5, iSelected6; 

