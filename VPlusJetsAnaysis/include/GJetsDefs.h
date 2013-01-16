// put definitions here
// histograms

TH1F *Nvtx_;
TH1F *ptPhoton_,*etaPhoton_;
TH1F *ptPhotonREC150_, *ptPhotonGEN150_;  // for efficiencies studies range 150-200 HT100-200 sample
TH1F *ptPhotonREC200_, *ptPhotonGEN200_;  // for efficiencies studies range 200-inf HT200-inf sample
TH1F *DeltaRGENREC_;

     
void Book_Histos();
void Plot_Histos();
void Zero_Variables();
float deltaPhi(float, float);

// variables
Char_t outputname[100];
Float_t ptPhoton, etaPhoton;
Float_t ptjet1,etajet1,phijet1;
Float_t ptGENjet1,etaGENjet1;

//counters
Int_t iSelected, iSelectedWithCuts; 
Float_t iSelectedWithWeights;
