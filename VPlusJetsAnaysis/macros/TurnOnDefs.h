// put definitions here

#include <TH1F.h>
#include <TH2F.h>
#include <vector>
#include <TLorentzVector.h>

void Zero_Variables();


// variables
Float_t weight_r, weight_withPU_r;
string sample_r;
Long64_t nentries_r;
Char_t outputname[100];
Char_t textname[100];

Float_t photonPfIsoChargedHad_RhoCorr,
				photonPfIsoNeutralHad_RhoCorr,
				photonPfIsoPhoton_RhoCorr;

Float_t	SelectedPhotons_N,
				SelectedPhotons_N_sel_1,
				SelectedPhotons_N_sel_2,
				SelectedPhotons_N_sel_4,
				SelectedPhotons_N_sel_8,
				SelectedPhotons_N_sel_16,
				SelectedPhotons_N_sel_32,
				SelectedPhotons_N_sel_64,
				SelectedPhotons_N_sel_128,
				SelectedPhotons_N_sel_256,				
				SelectedPhotons_N_sel_512,
				SelectedPhotons_N_sel_1024,
				SelectedPhotons_N_sel_2048,
				SelectedPhotons_N_sel_4096,
				SelectedJets_N,
				SelectedJets_N_sel_1,
				SelectedJets_N_sel_2,
				SelectedJets_N_sel_4,
				SelectedJets_N_sel_8,
				SelectedJets_N_sel_16,
				SelectedJets_N_sel_32,
				SelectedJets_N_sel_64,
				SelectedJets_N_sel_128,
				SelectedJets_N_sel_256,				
				SelectedJets_N_sel_512,
				SelectedJets_N_sel_1024,
				SelectedJets_N_sel_2048,
				SelectedJets_N_sel_4096,
				SelectedJets_HT,
				SelectedJets_HT_sel_1,
				SelectedJets_HT_sel_2,
				SelectedJets_HT_sel_4,
				SelectedJets_HT_sel_8,
				SelectedJets_HT_sel_16,
				SelectedJets_HT_sel_32,
				SelectedJets_HT_sel_64,
				SelectedJets_HT_sel_128,
				SelectedJets_HT_sel_256,				
				SelectedJets_HT_sel_512,
				SelectedJets_HT_sel_1024,
				SelectedJets_HT_sel_2048,
				SelectedJets_HT_sel_4096;

vector<float>	SelectedPhotons_Pt,
							SelectedPhotons_Pt_sel_1,
							SelectedPhotons_Pt_sel_2,
							SelectedPhotons_Pt_sel_4,
							SelectedPhotons_Pt_sel_8,
							SelectedPhotons_Pt_sel_16,
							SelectedPhotons_Pt_sel_32,
							SelectedPhotons_Pt_sel_64,
							SelectedPhotons_Pt_sel_128,
							SelectedPhotons_Pt_sel_256,				
							SelectedPhotons_Pt_sel_512,
							SelectedPhotons_Pt_sel_1024,
							SelectedPhotons_Pt_sel_2048,
							SelectedPhotons_Pt_sel_4096,
							SelectedPhotons_Eta,
							SelectedPhotons_Eta_sel_1,
							SelectedPhotons_Eta_sel_2,
							SelectedPhotons_Eta_sel_4,
							SelectedPhotons_Eta_sel_8,
							SelectedPhotons_Eta_sel_16,
							SelectedPhotons_Eta_sel_32,
							SelectedPhotons_Eta_sel_64,
							SelectedPhotons_Eta_sel_128,
							SelectedPhotons_Eta_sel_256,				
							SelectedPhotons_Eta_sel_512,
							SelectedPhotons_Eta_sel_1024,
							SelectedPhotons_Eta_sel_2048,
							SelectedPhotons_Eta_sel_4096,
							SelectedPhotons_Phi,
							SelectedPhotons_Phi_sel_1,
							SelectedPhotons_Phi_sel_2,
							SelectedPhotons_Phi_sel_4,
							SelectedPhotons_Phi_sel_8,
							SelectedPhotons_Phi_sel_16,
							SelectedPhotons_Phi_sel_32,
							SelectedPhotons_Phi_sel_64,
							SelectedPhotons_Phi_sel_128,
							SelectedPhotons_Phi_sel_256,				
							SelectedPhotons_Phi_sel_512,
							SelectedPhotons_Phi_sel_1024,
							SelectedPhotons_Phi_sel_2048,
							SelectedPhotons_Phi_sel_4096,
							SelectedJets_Pt,
							SelectedJets_Pt_sel_1,
							SelectedJets_Pt_sel_2,
							SelectedJets_Pt_sel_4,
							SelectedJets_Pt_sel_8,
							SelectedJets_Pt_sel_16,
							SelectedJets_Pt_sel_32,
							SelectedJets_Pt_sel_64,
							SelectedJets_Pt_sel_128,
							SelectedJets_Pt_sel_256,				
							SelectedJets_Pt_sel_512,
							SelectedJets_Pt_sel_1024,
							SelectedJets_Pt_sel_2048,
							SelectedJets_Pt_sel_4096;

vector<bool> photonTriMatchF4Path_sel_1,
						 photonTriMatchF4Path_sel_2,
						 photonTriMatchF4Path_sel_4,
						 photonTriMatchF4Path_sel_8,
						 photonTriMatchF4Path_sel_16,
						 photonTriMatchF4Path_sel_32,
						 photonTriMatchF4Path_sel_64,
						 photonTriMatchF4Path_sel_128,
						 photonTriMatchF4Path_sel_256,				
						 photonTriMatchF4Path_sel_512,
						 photonTriMatchF4Path_sel_1024,
						 photonTriMatchF4Path_sel_2048,
						 photonTriMatchF4Path_sel_4096;


// histograms
TH1F *SelectedPhotons_Pt_1_,
		*SelectedPhotons_Pt_1_sel_1_,
		*SelectedPhotons_Pt_1_sel_2_,
		*SelectedPhotons_Pt_1_sel_4_,
		*SelectedPhotons_Pt_1_sel_8_,
		*SelectedPhotons_Pt_1_sel_16_,
		*SelectedPhotons_Pt_1_sel_32_,
		*SelectedPhotons_Pt_1_sel_64_,
		*SelectedPhotons_Pt_1_sel_128_,
		*SelectedPhotons_Pt_1_sel_256_,				
		*SelectedPhotons_Pt_1_sel_512_,
		*SelectedPhotons_Pt_1_sel_1024_,
		*SelectedPhotons_Pt_1_sel_2048_,
		*SelectedPhotons_Pt_1_sel_4096_;


Int_t iSelected0, iSelected1, iSelected2, iSelected3, iSelected4, iSelected5, iSelected6, iSelected7, iSelected8, iSelected9, iSelected10, iSelected11, iSelected12, iSelected13;
