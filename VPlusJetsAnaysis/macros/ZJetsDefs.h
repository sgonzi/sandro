// put definitions here

#include <TH1F.h>
#include <TH2F.h>
#include <vector>
#include <TLorentzVector.h>

void Zero_Variables();

float deltaEta(float, float);


// variables
Float_t weight_r, weight_withPU_r;
string sample_r;
Long64_t nentries_r;
Char_t outputname[100];
Char_t textname[100];

Float_t	SelectedJetsGEN_N,
				SelectedJetsGEN_HT;


vector<float> SelectedJetsGEN_Pt,
							SelectedJetsGEN_E,
							SelectedJetsGEN_Eta,
							SelectedJetsGEN_Phi;



// histograms
TH1F *nLeptonsGEN_mumu_N0_,
		 *lepPtGEN_mumu_N0_1_,
		 *lepEGEN_mumu_N0_1_,
		 *lepEtaGEN_mumu_N0_1_,
		 *lepPhiGEN_mumu_N0_1_,
		 *lepPtGEN_mumu_N0_2_,
		 *lepEGEN_mumu_N0_2_,
		 *lepEtaGEN_mumu_N0_2_,
		 *lepPhiGEN_mumu_N0_2_,
		 *llMGEN_mumu_N0_,
		 *llPtGEN_mumu_N0_,
		 *llEtaGEN_mumu_N0_,
		 *llPhiGEN_mumu_N0_,
		 *SelectedJetsGEN_N_mumu_N0_,
		 *SelectedJets_PtGEN_mumu_N0_1_,
		 *SelectedJets_EGEN_mumu_N0_1_,
		 *SelectedJets_EtaGEN_mumu_N0_1_,
		 *SelectedJets_PhiGEN_mumu_N0_1_,
		 *SelectedJetsGEN_HT_mumu_N0_,
		 *nLeptonsGEN_ee_N0_,
		 *lepPtGEN_ee_N0_1_,
		 *lepEGEN_ee_N0_1_,
		 *lepEtaGEN_ee_N0_1_,
		 *lepPhiGEN_ee_N0_1_,
		 *lepPtGEN_ee_N0_2_,
		 *lepEGEN_ee_N0_2_,
		 *lepEtaGEN_ee_N0_2_,
		 *lepPhiGEN_ee_N0_2_,
		 *llMGEN_ee_N0_,
		 *llPtGEN_ee_N0_,
		 *llEtaGEN_ee_N0_,
		 *llPhiGEN_ee_N0_,
		 *SelectedJetsGEN_N_ee_N0_,
		 *SelectedJets_PtGEN_ee_N0_1_,
		 *SelectedJets_EGEN_ee_N0_1_,
		 *SelectedJets_EtaGEN_ee_N0_1_,
		 *SelectedJets_PhiGEN_ee_N0_1_,
		 *SelectedJetsGEN_HT_ee_N0_,
		 *nLeptonsGEN_ll_N0_,
		 *lepPtGEN_ll_N0_1_,
		 *lepEGEN_ll_N0_1_,
		 *lepEtaGEN_ll_N0_1_,
		 *lepPhiGEN_ll_N0_1_,
		 *lepPtGEN_ll_N0_2_,
		 *lepEGEN_ll_N0_2_,
		 *lepEtaGEN_ll_N0_2_,
		 *lepPhiGEN_ll_N0_2_,
		 *llMGEN_ll_N0_,
		 *llPtGEN_ll_N0_,
		 *llEtaGEN_ll_N0_,
		 *llPhiGEN_ll_N0_,
		 *SelectedJetsGEN_N_ll_N0_,
		 *SelectedJets_PtGEN_ll_N0_1_,
		 *SelectedJets_EGEN_ll_N0_1_,
		 *SelectedJets_EtaGEN_ll_N0_1_,
		 *SelectedJets_PhiGEN_ll_N0_1_,
		 *SelectedJetsGEN_HT_ll_N0_,
		 *HTParSum_,
		 *llPtGEN_mumu_excl1_,
		 *llPtGEN_ee_excl1_,		 
		 *llPtGEN_ll_excl1_,		 
		 *llPtGEN_mumu_excl2_,
		 *llPtGEN_ee_excl2_,		 
		 *llPtGEN_ll_excl2_,	 
		 *llPtGEN_mumu_N1_,
		 *llPtGEN_ee_N1_,		 
		 *llPtGEN_ll_N1_,		 
		 *llPtGEN_mumu_N2_,
		 *llPtGEN_ee_N2_,		 
		 *llPtGEN_ll_N2_;
