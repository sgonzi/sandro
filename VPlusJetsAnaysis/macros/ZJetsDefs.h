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
TH1F *nLeptonsGEN_mumu_,
		 *lepPtGEN_mumu_1_,
		 *lepEGEN_mumu_1_,
		 *lepEtaGEN_mumu_1_,
		 *lepPhiGEN_mumu_1_,
		 *lepPtGEN_mumu_2_,
		 *lepEGEN_mumu_2_,
		 *lepEtaGEN_mumu_2_,
		 *lepPhiGEN_mumu_2_,
		 *llMGEN_mumu_,
		 *llPtGEN_mumu_,
		 *llEtaGEN_mumu_,
		 *llPhiGEN_mumu_,
		 *SelectedJetsGEN_N_mumu_,
		 *SelectedJets_PtGEN_mumu_1_,
		 *SelectedJets_EGEN_mumu_1_,
		 *SelectedJets_EtaGEN_mumu_1_,
		 *SelectedJets_PhiGEN_mumu_1_,
		 *SelectedJetsGEN_HT_mumu_,
		 *nLeptonsGEN_ee_,
		 *lepPtGEN_ee_1_,
		 *lepEGEN_ee_1_,
		 *lepEtaGEN_ee_1_,
		 *lepPhiGEN_ee_1_,
		 *lepPtGEN_ee_2_,
		 *lepEGEN_ee_2_,
		 *lepEtaGEN_ee_2_,
		 *lepPhiGEN_ee_2_,
		 *llMGEN_ee_,
		 *llPtGEN_ee_,
		 *llEtaGEN_ee_,
		 *llPhiGEN_ee_,
		 *SelectedJetsGEN_N_ee_,
		 *SelectedJets_PtGEN_ee_1_,
		 *SelectedJets_EGEN_ee_1_,
		 *SelectedJets_EtaGEN_ee_1_,
		 *SelectedJets_PhiGEN_ee_1_,
		 *SelectedJetsGEN_HT_ee_,
		 *nLeptonsGEN_ll_,
		 *lepPtGEN_ll_1_,
		 *lepEGEN_ll_1_,
		 *lepEtaGEN_ll_1_,
		 *lepPhiGEN_ll_1_,
		 *lepPtGEN_ll_2_,
		 *lepEGEN_ll_2_,
		 *lepEtaGEN_ll_2_,
		 *lepPhiGEN_ll_2_,
		 *llMGEN_ll_,
		 *llPtGEN_ll_,
		 *llEtaGEN_ll_,
		 *llPhiGEN_ll_,
		 *SelectedJetsGEN_N_ll_,
		 *SelectedJets_PtGEN_ll_1_,
		 *SelectedJets_EGEN_ll_1_,
		 *SelectedJets_EtaGEN_ll_1_,
		 *SelectedJets_PhiGEN_ll_1_,
		 *SelectedJetsGEN_HT_ll_,
		 *HTParSum_;
