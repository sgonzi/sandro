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

Float_t photonPfIso,
				photonIsoFPR,
				photonPfIsoChargedHad_RhoCorr,
				photonPfIsoNeutralHad_RhoCorr,
				photonPfIsoPhoton_RhoCorr,
				photonPfIso_RhoCorr,
				photonPfIsoChargedHad_RhoCorr_forFit,
				photonPfIsoNeutralHad_RhoCorr_forFit,
				photonPfIsoPhoton_RhoCorr_forFit,
				photonPfIso_RhoCorr_forFit;

Float_t	SelectedJetsGEN_N,
				SelectedJetsGEN_HT,
				IDIsoPhotons_N,
				SelectedPhotons_N,
				SelectedJetsALL_N,
				SelectedJets_N,
				nPhotonsGEN,
				jetPtGEN_1,
				jetEtaGEN_1,
				jetPhiGEN_1,
				jetEGEN_1,
				nJetsGEN,
				HTGEN,
				HTParSum,
				DeltaR_photon1_jet1_N0,
				DeltaEta_photon1_jet1_N0,
				DeltaPhi_photon1_jet1_N0,
				DeltaPhi_photon1_jet1_N1,
				DeltaR_photon1_jet2_N1,
				DeltaR_jet1_jet2_N1,
				DeltaEta_jet1_jet2_N1,
				DeltaPhi_jet1_jet2_N1,
				DeltaPhi_photon1_jet1_N2,
				DeltaPhi_photon1_jet2_N2,
				DeltaPhi_photon1_jet3_N2,
				DeltaR_photon1_jet3_N2,
				DeltaPhi_jet1_jet2_N2,
				DeltaPhi_jet1_jet3_N2,
				DeltaPhi_jet2_jet3_N2,
				SelectedJets_HT;

vector<float> SelectedJetsGEN_Pt,
							SelectedJetsGEN_Eta,
							SelectedJetsGEN_Phi,
							SelectedJetsGEN_E,
							SelectedPhotons_Pt,
							SelectedPhotons_Eta,
							SelectedPhotons_Phi,
							SelectedPhotons_E,
							SelectedPhotons_PassConversionVeto,
							SelectedPhotons_PfIsoChargedHad,
							SelectedPhotons_PfIsoNeutralHad,
							SelectedPhotons_PfIsoPhoton,
							SelectedPhotons_PfIso,
							SelectedPhotons_PfIsoChargedHad_RhoCorr,
							SelectedPhotons_PfIsoNeutralHad_RhoCorr,
							SelectedPhotons_PfIsoPhoton_RhoCorr,
							SelectedPhotons_PfIso_RhoCorr,
							SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit,
							SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit,
							SelectedPhotons_PfIsoPhoton_RhoCorr_forFit,
							SelectedPhotons_PfIso_RhoCorr_forFit,
							SelectedPhotons_PfIsoPhotons03ForCic,
							SelectedPhotons_PfIsoNeutrals03ForCic,
							SelectedPhotons_PfIsoCharged03ForCicVtx0,
							SelectedPhotons_PfIsoCharged03BadForCic,
							SelectedPhotons_PfIsoPhotons04ForCic,
							SelectedPhotons_PfIsoNeutrals04ForCic,
							SelectedPhotons_PfIsoCharged04ForCicVtx0,
							SelectedPhotons_PfIsoCharged04BadForCic,
							SelectedPhotons_id_sieie,
							SelectedPhotons_id_sieip,
							SelectedPhotons_id_etawidth,
							SelectedPhotons_id_phiwidth,
							SelectedPhotons_id_r9,
							SelectedPhotons_id_lambdaRatio,
							SelectedPhotons_id_s4Ratio,
							SelectedPhotons_id_e25,
							SelectedPhotons_id_sceta,
							SelectedPhotons_id_ESEffSigmaRR,
							SelectedPhotons_id_hadronicOverEm,
							SelectedPhotons_id_hadronicOverEm2012,
							SelectedPhotons_hcalTowerSumEtConeDR04,
							SelectedPhotons_ecalRecHitSumEtConeDR04,
							SelectedPhotons_nTrkSolidConeDR04,
							SelectedPhotons_trkSumPtSolidConeDR04,
							SelectedPhotons_nTrkHollowConeDR04,
							SelectedPhotons_trkSumPtHollowConeDR04,
							SelectedPhotons_IsoFPRCharged,
							SelectedPhotons_IsoFPRNeutral,
							SelectedPhotons_IsoFPRPhoton,
							SelectedPhotons_IsoFPR,							
							SelectedPhotons_Bit,
							SelectedPhotons_TeP_SF,
							SelectedPhotons_BackDataDriven_F,							
							SelectedJets_Pt,
							SelectedJets_Eta,
							SelectedJets_Phi,
							SelectedJets_E;

//vector<float> SelectedPhotons_ScaleFactors;

vector<TLorentzVector> vPtEtaPhiE;
vector<double> myEvshpV,
							 TA;
vector<int> Grouping,
						Grouping_test;

Float_t phiTA,
				dphi_TA_BAxis,
				dphi_TA_J1Axis,
				thrust,
				broad,
				S3,
				S4,
				ln_thrust,
				ln_broad,
				ln_S3,
				ln_S4;

// histograms
TH1F *nPhotonsGEN_,
		 *photonPtGEN_,
		 *photonEtaGEN_,
		 *photonPhiGEN_,
		 *photonEGEN_,
		 *SelectedJetsGEN_N_,
		 *SelectedJets_PtGEN_1_,
		 *SelectedJets_EtaGEN_1_,
		 *SelectedJets_PhiGEN_1_,
		 *SelectedJets_EGEN_1_,
		 *SelectedJetsGEN_HT_,
		 *HTParSum_,
		 *pre_photonIsoSumPtDR03GEN_,
		 *IDIsoPhotons_N_,
		 *SelectedPhotons_N_,
		 *Nvtx_,
		 *SelectedPhotons_Pt_1_,
		 *SelectedPhotons_E_1_,
		 *SelectedPhotons_Eta_1_,
		 *SelectedPhotons_Phi_1_,
		 *SelectedPhotons_Bit_1_,
		 /*
		 *SelectedPhotons_TeP_SF_1_,
		 *SelectedPhotons_BackDataDriven_F_1_,
		 */	
		 *SelectedPhotons_PassConversionVeto_1_,
		 *SelectedPhotons_PfIsoChargedHad_1_,
		 *SelectedPhotons_PfIsoNeutralHad_1_,
		 *SelectedPhotons_PfIsoPhoton_1_,
		 *SelectedPhotons_PfIso_1_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_,
		 *SelectedPhotons_PfIso_RhoCorr_1_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_,
		 *SelectedPhotons_id_sieie_1_bin01_,
		 *SelectedPhotons_PfIsoChargedHad_1_bin01_,
		 *SelectedPhotons_PfIsoNeutralHad_1_bin01_,
		 *SelectedPhotons_PfIsoPhoton_1_bin01_,
		 *SelectedPhotons_PfIso_1_bin01_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_,
		 *SelectedPhotons_PfIso_RhoCorr_1_bin01_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_,		 
		 *SelectedPhotons_id_sieie_1_bin02_,		 
		 *SelectedPhotons_PfIsoChargedHad_1_bin02_,
		 *SelectedPhotons_PfIsoNeutralHad_1_bin02_,
		 *SelectedPhotons_PfIsoPhoton_1_bin02_,
		 *SelectedPhotons_PfIso_1_bin02_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_,
		 *SelectedPhotons_PfIso_RhoCorr_1_bin02_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_,
		 *SelectedPhotons_id_sieie_1_bin03_,		 
		 *SelectedPhotons_PfIsoChargedHad_1_bin03_,
		 *SelectedPhotons_PfIsoNeutralHad_1_bin03_,
		 *SelectedPhotons_PfIsoPhoton_1_bin03_,
		 *SelectedPhotons_PfIso_1_bin03_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_,
		 *SelectedPhotons_PfIso_RhoCorr_1_bin03_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_,
		 *SelectedPhotons_id_sieie_1_bin04_,		 
		 *SelectedPhotons_PfIsoChargedHad_1_bin04_,
		 *SelectedPhotons_PfIsoNeutralHad_1_bin04_,
		 *SelectedPhotons_PfIsoPhoton_1_bin04_,
		 *SelectedPhotons_PfIso_1_bin04_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_,
		 *SelectedPhotons_PfIso_RhoCorr_1_bin04_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_,
		 *SelectedPhotons_id_sieie_1_bin05_,		 
		 *SelectedPhotons_PfIsoChargedHad_1_bin05_,
		 *SelectedPhotons_PfIsoNeutralHad_1_bin05_,
		 *SelectedPhotons_PfIsoPhoton_1_bin05_,
		 *SelectedPhotons_PfIso_1_bin05_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_,
		 *SelectedPhotons_PfIso_RhoCorr_1_bin05_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_,
		 *SelectedPhotons_id_sieie_1_bin06_,		 
		 *SelectedPhotons_PfIsoChargedHad_1_bin06_,
		 *SelectedPhotons_PfIsoNeutralHad_1_bin06_,
		 *SelectedPhotons_PfIsoPhoton_1_bin06_,
		 *SelectedPhotons_PfIso_1_bin06_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_,
		 *SelectedPhotons_PfIso_RhoCorr_1_bin06_,
		 *SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_,
		 *SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_,
		 *SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_,
		 *SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_,		 
		 *SelectedPhotons_PfIsoPhotons03ForCic_1_,
		 *SelectedPhotons_PfIsoNeutrals03ForCic_1_,
		 *SelectedPhotons_PfIsoCharged03ForCicVtx0_1_,
		 *SelectedPhotons_PfIsoCharged03BadForCic_1_,
		 *SelectedPhotons_PfIsoPhotons04ForCic_1_,
		 *SelectedPhotons_PfIsoNeutrals04ForCic_1_,
		 *SelectedPhotons_PfIsoCharged04ForCicVtx0_1_,
		 *SelectedPhotons_PfIsoCharged04BadForCic_1_,
		 *SelectedPhotons_id_sieie_1_,
		 *SelectedPhotons_id_sieip_1_,
		 *SelectedPhotons_id_etawidth_1_,
		 *SelectedPhotons_id_phiwidth_1_,
		 *SelectedPhotons_id_r9_1_,
		 *SelectedPhotons_id_lambdaRatio_1_,
		 *SelectedPhotons_id_s4Ratio_1_,
		 *SelectedPhotons_id_e25_1_,
		 *SelectedPhotons_id_sceta_1_,
		 *SelectedPhotons_id_ESEffSigmaRR_1_,
		 *SelectedPhotons_id_hadronicOverEm_1_,
		 *SelectedPhotons_id_hadronicOverEm2012_1_,
		 *SelectedPhotons_hcalTowerSumEtConeDR04_1_,
		 *SelectedPhotons_ecalRecHitSumEtConeDR04_1_,
		 *SelectedPhotons_nTrkSolidConeDR04_1_,
		 *SelectedPhotons_trkSumPtSolidConeDR04_1_,
		 *SelectedPhotons_nTrkHollowConeDR04_1_,
		 *SelectedPhotons_trkSumPtHollowConeDR04_1_,
		 *SelectedPhotons_IsoFPRCharged_1_,
		 *SelectedPhotons_IsoFPRNeutral_1_,
		 *SelectedPhotons_IsoFPRPhoton_1_,
		 *SelectedPhotons_IsoFPR_1_,		 
		 *SelectedJetsALL_N_,
		 *SelectedJets_N_,
		 *SelectedJets_Pt_1_,
		 *SelectedJets_Eta_1_,
		 *SelectedJets_Phi_1_,
		 *SelectedJets_E_1_,
		 *SelectedJets_HT_,
		 *DeltaR_photon1_jet1_N0_,
		 *DeltaEta_photon1_jet1_N0_,
		 *DeltaPhi_photon1_jet1_N0_,
		 *thrust_N0_,
		 *broad_N0_,
		 *S3_N0_,
		 *S4_N0_,
		 *ln_thrust_N0_,
		 *ln_broad_N0_,
		 *ln_S3_N0_,
		 *ln_S4_N0_,
		 *SelectedPhotons_Pt_excl1_1_,
		 *SelectedPhotons_E_excl1_1_,
		 *SelectedPhotons_Eta_excl1_1_,
		 *SelectedPhotons_Phi_excl1_1_,
		 *SelectedJets_Pt_excl1_1_,
		 *SelectedJets_E_excl1_1_,
		 *SelectedJets_Eta_excl1_1_,
		 *SelectedJets_Phi_excl1_1_,		 	 
		 *SelectedPhotons_Pt_excl2_1_,
		 *SelectedPhotons_E_excl2_1_,
		 *SelectedPhotons_Eta_excl2_1_,
		 *SelectedPhotons_Phi_excl2_1_,
		 *SelectedJets_Pt_excl2_1_,
		 *SelectedJets_E_excl2_1_,
		 *SelectedJets_Eta_excl2_1_,
		 *SelectedJets_Phi_excl2_1_,		 	 
		 *SelectedJets_Pt_excl2_2_,
		 *SelectedJets_E_excl2_2_,
		 *SelectedJets_Eta_excl2_2_,
		 *SelectedJets_Phi_excl2_2_,
		 *SelectedJets_HT_excl2_,	 		 	 
		 *SelectedJets_Pt_2_,
		 *SelectedJets_Eta_2_,
		 *SelectedJets_Phi_2_,
		 *SelectedJets_E_2_,
		 *DeltaPhi_photon1_jet1_N1_,
		 *DeltaR_photon1_jet2_N1_,
		 *DeltaR_jet1_jet2_N1_,
		 *DeltaEta_jet1_jet2_N1_,
		 *DeltaPhi_jet1_jet2_N1_,
		 *SelectedJets_Pt_3_,
		 *SelectedJets_Eta_3_,
		 *SelectedJets_Phi_3_,
		 *SelectedJets_E_3_,
		 *DeltaPhi_photon1_jet1_N2_,
		 *DeltaPhi_photon1_jet2_N2_,
		 *DeltaPhi_photon1_jet3_N2_,
		 *DeltaR_photon1_jet3_N2_,
		 *DeltaPhi_jet1_jet2_N2_,
		 *DeltaPhi_jet1_jet3_N2_,
		 *DeltaPhi_jet2_jet3_N2_,
		 *photonIsoSumPtDR03GEN_;

TH2F *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_, 
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_,
 	   *TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_, 	   
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_,
	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_,
 	   *TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_;


Int_t iSelected0, iSelected1, iSelected2, iSelected3, iSelected4;
