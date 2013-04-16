#define plotsCompare_cxx
#include "comparestack.C"

void plotsCompareMC(){

	comparestack("nPhotonsGEN_","Photons GEN N", 1, -999, -999);
	comparestack("photonPtGEN_","Photon GEN p_{T}", 1, -999, -999);
	comparestack("photonEGEN_","Photon GEN E", 1, -999, -999);
	comparestack("photonEtaGEN_","Photon GEN #eta", 30, -1.5, 1.5);
	comparestack("photonPhiGEN_","Photon GEN #varphi", 1, -999, -999);

//	comparestack("CleanedJetsGEN_N_","Cleaned Jets GEN N", 1, -999, -999);
	comparestack("SelectedJetsGEN_N_","Selected Jets GEN N", 1, -999, -999);

	comparestack("SelectedJets_PtGEN_1_","Jet 1 GEN p_{T}", 1, -999, -999);
	comparestack("SelectedJets_EGEN_1_", "jet 1 GEN E", 1, -999, -999);
	comparestack("SelectedJets_EtaGEN_1_","Jet 1 GEN #eta", 1, -1.5, 1.5);
	comparestack("SelectedJets_PhiGEN_1_","Jet 1 GEN #varphi", 1, -999, -999);

//	comparestack("CleanedJetsGEN_HT_","Cleaned Jets H_{T} GEN", 4, 0, 3000);
	comparestack("SelectedJetsGEN_HT_","Selected Jets H_{T} GEN", 4, 0, 3000);

	comparestack("HTParSum_","H_{T} Partons Sum", 1, -999, -999);
}

void plotsCompare1(){

//	comparestack("IDIsoPhotons_N_", "ID-Iso Photons N", 1, -999, -999);
	comparestack("SelectedPhotons_N_","Selected Photons N", 1, -999, -999);

	comparestack("Nvtx_", "N^{vtx} ", 1, -999, -999);

	comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 2, 0, 2000);
	comparestack("SelectedPhotons_E_1_", "E^{#gamma1} [GeV]", 2, 0, 2000);
	comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}", 30, -1.5, 1.5); // barrel
//	comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}", 30, -3, 3); // endcaps or total
	comparestack("SelectedPhotons_Phi_1_", "#varphi^{#gamma1}", 20, -999, -999);
//	comparestack("SelectedPhotons_Bit_1_", "bit^{#gamma1}", 1, -999, -999);
}

void plotsCompare2(){
	comparestack("SelectedPhotons_PassConversionVeto_1_","photonPassConversionVeto", 1, -999, -999);
	comparestack("SelectedPhotons_PfIsoChargedHad_1_", "#gamma1 PfIsoChargedHad", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_", "#gamma1 PfIsoNeutralHad", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_", "#gamma1 PfIsoPhoton", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_", "photon PfIso", 4, 0, 20);
	comparestack("SelectedPhotons_PfIso_ov_Pt_1_", "photon PfIso/p_{T}", 1, 0, 0.07);	
	comparestack("SelectedPhotons_PfIsoPhotons03ForCic_1_", "#gamma1 PfIsoPhotons03ForCic", 8, 0, 80);
	comparestack("SelectedPhotons_PfIsoNeutrals03ForCic_1_", "#gamma1 PfIsoNeutrals03ForCic", 4, 0, 40);
	comparestack("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "#gamma1 PfIsoCharged03ForCicVtx0", 8, 0, 80);
	comparestack("SelectedPhotons_PfIsoCharged03BadForCic_1_", "#gamma1 PfIsoCharged03BadForCic", 20, 0, 200);
	comparestack("SelectedPhotons_PfIsoPhotons04ForCic_1_", "#gamma1 PfIsoPhotons04ForCic", 8, 0, 80);
	comparestack("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "#gamma1 PfIsoNeutrals04ForCic", 40, 0, 200);
	comparestack("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "#gamma1  PfIsoCharged04ForCicVtx0", 20, 0, 200);
	comparestack("SelectedPhotons_PfIsoCharged04BadForCic_1_", "#gamma1 PfIsoCharged04BadForCic", 20, 0, 200);
	comparestack("SelectedPhotons_id_sieie_1_", "#gamma1 #sigma_{i#etai#eta}", 2, 0, 0.012);
	comparestack("SelectedPhotons_id_sieip_1_", "#gamma1 #sigma_{i#etai#varphi}", 2, 0, 0.014);
	comparestack("SelectedPhotons_id_etawidth_1_", "#gamma1 #eta width", 4, 0, 0.02);
	comparestack("SelectedPhotons_id_phiwidth_1_", "#gamma1 #varphi width", 2, 0, 0.15);
	comparestack("SelectedPhotons_id_r9_1_", "#gamma1 r9", 1, 0, 1.1);
	comparestack("SelectedPhotons_id_lambdaRatio_1_", "#gamma1 #lambda Ratio", 1, 0, 1.1);
	comparestack("SelectedPhotons_id_s4Ratio_1_", "#gamma1 s4 Ratio", 1, 0, 1.1);
	comparestack("SelectedPhotons_id_e25_1_", "#gamma1 #rho25", 2, 0, 2000);
	comparestack("SelectedPhotons_id_sceta_1_", "#gamma1 SC #eta", 30, -1.5, 1.5); // barrel
//	comparestack("SelectedPhotons_id_sceta_1_", "#gamma1 SC #eta", 30, -3, 3); // endcaps or total
	comparestack("SelectedPhotons_id_ESEffSigmaRR_1_", "#gamma1 ESEffSigmaRR", 1, -999, -999);
	comparestack("SelectedPhotons_id_hadronicOverEm_1_", "#gamma1 hadronicOverEm", 20, 0, 0.2);
	comparestack("SelectedPhotons_id_hadronicOverEm2012_1_", "#gamma1 hadronicOverEm2012", 10, 0, 0.06);
	comparestack("SelectedPhotons_hcalTowerSumEtConeDR04_1_", "#gamma1 hcalTowerSumEtConeDR04", 2, 0, 200);
	comparestack("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "#gamma1 ecalRecHitSumEtConeDR04", 2, 0, 200);
	comparestack("SelectedPhotons_nTrkSolidConeDR04_1_", "#gamma1 nTrkSolidConeDR04", 1, 0, 20);
	comparestack("SelectedPhotons_trkSumPtSolidConeDR04_1_", "#gamma1 trkSumPtSolidConeDR04", 4, 0, 200);
	comparestack("SelectedPhotons_nTrkHollowConeDR04_1_", "#gamma1 nTrkHollowConeDR04", 1, 0, 20);
	comparestack("SelectedPhotons_trkSumPtHollowConeDR04_1_", "#gamma1 trkSumPtHollowConeDR04", 4, 0, 200);
	comparestack("SelectedPhotons_IsoFPRCharged_1_", "#gamma1 IsoFPRCharged", 20, 0, 200);
	comparestack("SelectedPhotons_IsoFPRNeutral_1_", "#gamma1 IsoFPRNeutral", 20, 0, 200);
	comparestack("SelectedPhotons_IsoFPRPhoton_1_", "#gamma1 IsoFPRPhoton", 20, 0, 200);
	comparestack("SelectedPhotons_IsoFPRCharged_ov_Pt_1_", "#gamma1 IsoFPRCharged/p_{T}", 1, -999, -999);
	comparestack("SelectedPhotons_IsoFPRNeutral_ov_Pt_1_", "photon IsoFPRNeutral/p_{T}", 1, -999, -999);
	comparestack("SelectedPhotons_IsoFPRPhoton_ov_Pt_1_", "photon IsoFPRPhoton/p_{T}", 1, -999, -999);
	
}

void plotsCompare3(){
//	comparestack("CleanedJetsLEA_N_", "Cleaned Jets LEA N ", 1, -999, -999);
//	comparestack("SelectedJetsLEA_N_", "Selected Jets LEA N", 1, -999, -999);
//	comparestack("CleanedJets_N_", "Cleaned Jets N ", 1, -999, -999);
	comparestack("SelectedJets_N_", "Selected Jets N", 1, -999, -999);

	comparestack("SelectedJets_Pt_1_", "p_{T}^{jet1} [GeV/#font[12]{c}]", 2, 0, 2000);
	comparestack("SelectedJets_E_1_", "E^{jet1}[GeV]", 2, 0, 3000);
	comparestack("SelectedJets_Eta_1_", "#eta^{jet1}", 50, -3, 3);
	comparestack("SelectedJets_Phi_1_", "#varphi^{jet1}", 20, -999, -999);

	comparestack("DeltaR_photon1_jet1_", "#DeltaR #gamma1-jet1", 1, -999, -999);
	comparestack("DeltaEta_photon1_jet1_","#Delta#eta #gamma1-jet1", 1, -999, -999);
	comparestack("DeltaPhi_photon1_jet1_","#Delta#varphi #gamma1-jet1", 1, -999, -999);

	comparestack("SelectedJets_Pt_2_", "p_{T}^{jet2} [GeV/#font[12]{c}]", 2, 0, 1500);
	comparestack("SelectedJets_E_2_", "E^{jet2} [GeV]", 2, 0, 2500);
	comparestack("SelectedJets_Eta_2_", "#eta^{jet2}", 50, -3, 3);
	comparestack("SelectedJets_Phi_2_", "#varphi^{jet2}", 20, -999, -999);

	comparestack("DeltaR_photon1_jet2_", "#DeltaR #gamma1-jet2", 1, -999, -999);
	comparestack("DeltaR_jet1_jet2_","#DeltaR jet1-jet2", 1, -999, -999);
	comparestack("DeltaEta_jet1_jet2_","#Delta#eta jet1-jet2", 1, -999, -999);
	comparestack("DeltaPhi_jet1_jet2_","#Delta#varphi jet1-jet2", 1, -999, -999);

	comparestack("SelectedJets_Pt_3_", "p_{T}^{jet3} [GeV/#font[12]{c}]", 2, 0, 1000);
	comparestack("SelectedJets_E_3_", "E^{jet3} [GeV]", 2, 0, 2000);
	comparestack("SelectedJets_Eta_3_", "#eta^{jet3}", 50, -3, 3);
	comparestack("SelectedJets_Phi_3_", "#varphi^{jet3}", 20, -999, -999);

	comparestack("DeltaR_photon1_jet3_", "#DeltaR #gamma1-jet3", 1, -999, -999);

//	comparestack("CleanedJets_HT_", "Cleaned Jets H_{T}", 4, 0, 3000);
	comparestack("SelectedJets_HT_", "Selected Jets H_{T}", 4, 0, 3000);
	
//	comparestack("CleanedJetsLEA_preHT_N_","Cleaned Jets LEA N pre-H_{T}", 1, -999, -999);
//	comparestack("SelectedJetsLEA_preHT_N_","Selected Jets LEA N pre-H_{T}", 1, -999, -999);
//	comparestack("CleanedJets_preHT_N_","Cleaned Jets N pre-H_{T}", 1, -999, -999);
	comparestack("SelectedJets_preHT_N_","Selected Jets N pre-H_{T}", 1, -999, -999);
	comparestack("SelectedJets_preHT_Pt_1_","Jet 1 p_{T} pre-H_{T}", 2, 0, 2000);
	comparestack("SelectedJets_preHT_Pt_2_","Jet 2 p_{T} pre-H_{T}", 2, 0, 1500);
	comparestack("SelectedJets_preHT_Pt_3_","Jet 3 p_{T} pre-H_{T}", 2, 0, 1000);
//	comparestack("CleanedJets_preHT_HT_","Cleaned Jets H_{T} pre-H_{T}", 4, 0, 3000);
	comparestack("SelectedJets_preHT_HT_","Selected Jets H_{T} pre-H_{T}", 4, 0, 3000);

	comparestack("thrust_","thrust", 1, -999, -999);
	comparestack("broad_","broad", 1, -999, -999);
	comparestack("S3_","S3", 1, -999, -999);
	comparestack("S4_","S4", 1, -999, -999);
	
}



