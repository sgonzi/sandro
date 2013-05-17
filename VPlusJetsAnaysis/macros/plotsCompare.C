#define plotsCompare_cxx
#include "comparestack.C"


void plotsCompare_gen_01(){
	comparestack("nPhotonsGEN_","Photons GEN N", 1, -999, -999);
	comparestack("photonPtGEN_","Photon GEN p_{T}", 1, -999, -999);
	comparestack("photonEGEN_","Photon GEN E", 1, -999, -999);
	comparestack("photonEtaGEN_","Photon GEN #eta", 30, -1.5, 1.5);
	comparestack("photonPhiGEN_","Photon GEN #varphi", 1, -999, -999);
}


void plotsCompare_gen_02(){
	comparestack("CleanedJetsGEN_N_","Cleaned Jets GEN N", 1, -999, -999);

	comparestack("SelectedJetsGEN_N_","Selected Jets GEN N", 1, -999, -999);
	comparestack("SelectedJets_PtGEN_1_","Jet 1 GEN p_{T}", 1, -999, -999);
	comparestack("SelectedJets_EGEN_1_", "jet 1 GEN E", 1, -999, -999);
	comparestack("SelectedJets_EtaGEN_1_","Jet 1 GEN #eta", 1, -1.5, 1.5);
	comparestack("SelectedJets_PhiGEN_1_","Jet 1 GEN #varphi", 1, -999, -999);
}


void plotsCompare_gen_03(){
//	comparestack("CleanedJetsGEN_HT_","Cleaned Jets H_{T} GEN", 4, 0, 3000);
	comparestack("SelectedJetsGEN_HT_","Selected Jets H_{T} GEN", 4, 0, 3000);

	comparestack("HTParSum_","H_{T} Partons Sum", 1, -999, -999);

	comparestack("pre_photonIsoPtDR03GEN_","photonIsoPtDR03GEN", 1, -999, -999);	
}


void plotsCompare_01(){
	comparestack("IDIsoPhotons_N_", "ID-Iso Photons N", 1, -999, -999);
	comparestack("SelectedPhotons_N_","Selected Photons N", 1, -999, -999);

	comparestack("Nvtx_", "N^{vtx} ", 1, -999, -999);

	comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 2, 0, 2000);
	comparestack("SelectedPhotons_E_1_", "E^{#gamma1} [GeV]", 2, 0, 2000);
	comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}", 30, -1.5, 1.5); // barrel
//	comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}", 30, -3, 3); // endcaps or total
	comparestack("SelectedPhotons_Phi_1_", "#varphi^{#gamma1}", 20, -999, -999);
	comparestack("SelectedPhotons_Bit_1_", "bit^{#gamma1}", 1, -999, -999);
}


void plotsCompare_02(){
	comparestack("SelectedPhotons_PassConversionVeto_1_","photonPassConversionVeto", 1, -999, -999);
	comparestack("SelectedPhotons_PfIsoChargedHad_1_", "#gamma1 PfIsoChargedHad", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_", "#gamma1 PfIsoNeutralHad", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_", "#gamma1 PfIsoPhoton", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_", "photon PfIso", 4, 0, 20);
	comparestack("SelectedPhotons_PfIso_ov_Pt_1_", "photon PfIso/p_{T}", 1, 0, 0.07);
}


void plotsCompare_03(){
	comparestack("SelectedPhotons_id_sieie_1_bin01_","#gamma1 #sigma_{i#etai#eta}, 150 < p_{T}^{#gamma} < 300", 2, 0, 0.012); 
//	comparestack("SelectedPhotons_id_sieie_1_bin01_","#gamma1 #sigma_{i#etai#eta}, 150 < p_{T}^{#gamma} < 300", 2, 0.010, 0.025); // inverted
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin01_", "#gamma1 PfIsoChargedHad, 150 < p_{T}^{#gamma} < 300", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin01_", "#gamma1 PfIsoNeutralHad, 150 < p_{T}^{#gamma} < 300", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin01_", "#gamma1 PfIsoPhoton, 150 < p_{T}^{#gamma} < 300", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin01_", "photon PfIso, 150 < p_{T}^{#gamma} < 300", 4, 0, 20);
	comparestack("SelectedPhotons_PfIso_ov_Pt_1_bin01_", "photon PfIso/p_{T}, 150 < p_{T}^{#gamma} < 300", 1, 0, 0.07);
}


void plotsCompare_04(){
	comparestack("SelectedPhotons_id_sieie_1_bin02_","#gamma1 #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 500", 2, 0, 0.012);
//	comparestack("SelectedPhotons_id_sieie_1_bin02_","#gamma1 #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 500", 2, 0.010, 0.025); // inverted
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin02_", "#gamma1 PfIsoChargedHad, 300 < p_{T}^{#gamma} < 500", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin02_", "#gamma1 PfIsoNeutralHad, 300 < p_{T}^{#gamma} < 500", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin02_", "#gamma1 PfIsoPhoton, 300 < p_{T}^{#gamma} < 500", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin02_", "photon PfIso, 300 < p_{T}^{#gamma} < 500", 4, 0, 20);
	comparestack("SelectedPhotons_PfIso_ov_Pt_1_bin02_", "photon PfIso/p_{T}, 300 < p_{T}^{#gamma} < 500", 1, 0, 0.07);
}


void plotsCompare_05(){
	comparestack("SelectedPhotons_id_sieie_1_bin03_","#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma} > 500", 2, 0, 0.012);
//	comparestack("SelectedPhotons_id_sieie_1_bin03_","#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma} > 500", 2, 0.010, 0.025); // inverted
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin03_", "#gamma1 PfIsoChargedHad, p_{T}^{#gamma} > 500", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin03_", "#gamma1 PfIsoNeutralHad, p_{T}^{#gamma} > 500", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin03_", "#gamma1 PfIsoPhoton, p_{T}^{#gamma} > 500", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin03_", "photon PfIso, p_{T}^{#gamma} > 500", 4, 0, 20);
	comparestack("SelectedPhotons_PfIso_ov_Pt_1_bin03_", "photon PfIso/p_{T}, p_{T}^{#gamma} > 500", 1, 0, 0.07);
}


void plotsCompare_06(){		
	comparestack("SelectedPhotons_PfIsoPhotons03ForCic_1_", "#gamma1 PfIsoPhotons03ForCic", 8, 0, 80);
	comparestack("SelectedPhotons_PfIsoNeutrals03ForCic_1_", "#gamma1 PfIsoNeutrals03ForCic", 4, 0, 40);
	comparestack("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "#gamma1 PfIsoCharged03ForCicVtx0", 8, 0, 80);
	comparestack("SelectedPhotons_PfIsoCharged03BadForCic_1_", "#gamma1 PfIsoCharged03BadForCic", 20, 0, 200);
}


void plotsCompare_07(){		
	comparestack("SelectedPhotons_PfIsoPhotons04ForCic_1_", "#gamma1 PfIsoPhotons04ForCic", 8, 0, 80);
	comparestack("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "#gamma1 PfIsoNeutrals04ForCic", 40, 0, 200);
	comparestack("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "#gamma1  PfIsoCharged04ForCicVtx0", 20, 0, 200);
	comparestack("SelectedPhotons_PfIsoCharged04BadForCic_1_", "#gamma1 PfIsoCharged04BadForCic", 20, 0, 200);
}


void plotsCompare_08(){
	comparestack("SelectedPhotons_id_sieie_1_", "#gamma1 #sigma_{i#etai#eta}", 2, 0, 0.012);
//	comparestack("SelectedPhotons_id_sieie_1_", "#gamma1 #sigma_{i#etai#eta}", 2, 0.010, 0.025); // inverted
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
}


void plotsCompare_09(){
	comparestack("SelectedPhotons_hcalTowerSumEtConeDR04_1_", "#gamma1 hcalTowerSumEtConeDR04", 2, 0, 200);
	comparestack("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "#gamma1 ecalRecHitSumEtConeDR04", 2, 0, 200);
	comparestack("SelectedPhotons_nTrkSolidConeDR04_1_", "#gamma1 nTrkSolidConeDR04", 1, 0, 20);
	comparestack("SelectedPhotons_trkSumPtSolidConeDR04_1_", "#gamma1 trkSumPtSolidConeDR04", 4, 0, 200);
	comparestack("SelectedPhotons_nTrkHollowConeDR04_1_", "#gamma1 nTrkHollowConeDR04", 1, 0, 20);
	comparestack("SelectedPhotons_trkSumPtHollowConeDR04_1_", "#gamma1 trkSumPtHollowConeDR04", 4, 0, 200);
}	


void plotsCompare_10(){	
	comparestack("SelectedPhotons_IsoFPRCharged_1_", "#gamma1 IsoFPRCharged", 20, 0, 200);
	comparestack("SelectedPhotons_IsoFPRNeutral_1_", "#gamma1 IsoFPRNeutral", 20, 0, 200);
	comparestack("SelectedPhotons_IsoFPRPhoton_1_", "#gamma1 IsoFPRPhoton", 20, 0, 200);
	comparestack("SelectedPhotons_IsoFPRCharged_ov_Pt_1_", "#gamma1 IsoFPRCharged/p_{T}", 1, -999, -999);
	comparestack("SelectedPhotons_IsoFPRNeutral_ov_Pt_1_", "photon IsoFPRNeutral/p_{T}", 1, -999, -999);
	comparestack("SelectedPhotons_IsoFPRPhoton_ov_Pt_1_", "photon IsoFPRPhoton/p_{T}", 1, -999, -999);
}


void plotsCompare_11(){
//	comparestack("CleanedJetsLEA_N_", "Cleaned Jets LEA N ", 1, -999, -999);
//	comparestack("SelectedJetsLEA_N_", "Selected Jets LEA N", 1, -999, -999);
//	comparestack("CleanedJets_N_", "Cleaned Jets N ", 1, -999, -999);
	comparestack("SelectedJets_N_", "Selected Jets N", 1, -999, -999);
}


void plotsCompare_12(){
	comparestack("SelectedJets_Pt_1_", "p_{T}^{jet1} [GeV/#font[12]{c}]", 2, 0, 2000);
	comparestack("SelectedJets_E_1_", "E^{jet1}[GeV]", 2, 0, 3000);
	comparestack("SelectedJets_Eta_1_", "#eta^{jet1}", 50, -3, 3);
	comparestack("SelectedJets_Phi_1_", "#varphi^{jet1}", 20, -999, -999);
}


void plotsCompare_13(){
//	comparestack("CleanedJets_HT_", "Cleaned Jets H_{T}", 4, 0, 3000);
	comparestack("SelectedJets_HT_", "Selected Jets H_{T}", 4, 0, 3000);
}


void plotsCompare_14(){
	comparestack("thrust_N0_","#tau_{T} - N^{jets} #geq 1", 2, 0, 0.35);
	comparestack("broad_N0_","broad - N^{jets} #geq 1", 2, 0, 1);
	comparestack("S3_N0_","S3 - N^{jets} #geq 1", 1, -1, 5);
	comparestack("S4_N0_","S4 - N^{jets} #geq 1", 1, -0.2, 0.2);

	comparestack("ln_thrust_N0_","ln #tau_{T} - N^{jets} #geq 1", 3, -30, 0);
	comparestack("ln_broad_N0_","ln broad - N^{jets} #geq 1", 1, -3, 1);
	comparestack("ln_S3_N0_","ln S3 - N^{jets} #geq 1", 2, -4, 3);
	comparestack("ln_S4_N0_","ln S4 - N^{jets} #geq 1", 1, -999, 999);		
}


void plotsCompare_15(){
	comparestack("DeltaR_photon1_jet1_N0_", "#DeltaR #gamma1-jet1 - N^{jets} #geq 1", 20, 0, 6);
	comparestack("DeltaEta_photon1_jet1_N0_","#Delta#eta #gamma1-jet1 - N^{jets} #geq 1", 10, 0, 5);
	comparestack("DeltaPhi_photon1_jet1_N0_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 1", 10, 0, 3.1416);
}


void plotsCompare_16(){
	comparestack("SelectedJets_Pt_2_", "p_{T}^{jet2} [GeV/#font[12]{c}]", 2, 0, 1500);
	comparestack("SelectedJets_E_2_", "E^{jet2} [GeV]", 2, 0, 2500);
	comparestack("SelectedJets_Eta_2_", "#eta^{jet2}", 50, -3, 3);
	comparestack("SelectedJets_Phi_2_", "#varphi^{jet2}", 20, -999, -999);
}

void plotsCompare_17(){
	comparestack("DeltaPhi_photon1_jet1_N1_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 2", 10, 0, 3.1416);
	comparestack("DeltaR_photon1_jet2_N1_", "#DeltaR #gamma1-jet2 - N^{jets} #geq 2", 20, 0, 6);
	comparestack("DeltaR_jet1_jet2_N1_","#DeltaR jet1-jet2 - N^{jets} #geq 2", 20, 0, 6);
	comparestack("DeltaEta_jet1_jet2_N1_","#Delta#eta jet1-jet2 - N^{jets} #geq 2", 10, 0, 5);
	comparestack("DeltaPhi_jet1_jet2_N1_","#Delta#varphi jet1-jet2 - N^{jets} #geq 2", 10, 0, 3.1416);
}


void plotsCompare_18(){
	comparestack("SelectedJets_Pt_3_", "p_{T}^{jet3} [GeV/#font[12]{c}]", 2, 0, 1000);
	comparestack("SelectedJets_E_3_", "E^{jet3} [GeV]", 2, 0, 2000);
	comparestack("SelectedJets_Eta_3_", "#eta^{jet3}", 50, -3, 3);
	comparestack("SelectedJets_Phi_3_", "#varphi^{jet3}", 20, -999, -999);
}


void plotsCompare_19(){
	comparestack("DeltaPhi_photon1_jet1_N2_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 3", 10, 0, 3.1416);
	comparestack("DeltaPhi_photon1_jet2_N2_","#Delta#varphi #gamma1-jet2 - N^{jets} #geq 3", 10, 0, 3.1416);
	comparestack("DeltaPhi_photon1_jet3_N2_","#Delta#varphi #gamma1-jet3 - N^{jets} #geq 3", 10, 0, 3.1416);
	comparestack("DeltaR_photon1_jet3_N2_", "#DeltaR #gamma1-jet3 - N^{jets} #geq 3", 20, 0, 6);
	comparestack("DeltaPhi_jet1_jet2_N2_","#Delta#varphi jet1-jet2 - N^{jets} #geq 3", 10, 0, 3.1416);
	comparestack("DeltaPhi_jet1_jet3_N2_","#Delta#varphi jet1-jet3 - N^{jets} #geq 3", 10, 0, 3.1416);
	comparestack("DeltaPhi_jet2_jet3_N2_","#Delta#varphi jet2-jet3 - N^{jets} #geq 3", 10, 0, 3.1416);
}


void plotsCompare_20(){	
//	comparestack("CleanedJetsLEA_preHT_N_","Cleaned Jets LEA N pre-H_{T}", 1, -999, -999);
//	comparestack("SelectedJetsLEA_preHT_N_","Selected Jets LEA N pre-H_{T}", 1, -999, -999);
//	comparestack("CleanedJets_preHT_N_","Cleaned Jets N pre-H_{T}", 1, -999, -999);
	comparestack("SelectedJets_preHT_N_","Selected Jets N pre-H_{T}", 1, -999, -999);
	comparestack("SelectedJets_preHT_Pt_1_","Jet 1 p_{T} pre-H_{T}", 2, 0, 2000);
	comparestack("SelectedJets_preHT_Pt_2_","Jet 2 p_{T} pre-H_{T}", 2, 0, 1500);
	comparestack("SelectedJets_preHT_Pt_3_","Jet 3 p_{T} pre-H_{T}", 2, 0, 1000);
//	comparestack("CleanedJets_preHT_HT_","Cleaned Jets H_{T} pre-H_{T}", 4, 0, 3000);
	comparestack("SelectedJets_preHT_HT_","Selected Jets H_{T} pre-H_{T}", 4, 0, 3000);
}


// ------------------------------------------------------

void plotsCompare_gen_TOT(){
	plotsCompare_gen_01();
	plotsCompare_gen_02();
	plotsCompare_gen_03();
}


void plotsCompare_TOT(){
	plotsCompare_01();
	plotsCompare_02();
	plotsCompare_03();
	plotsCompare_04();
	plotsCompare_05();
	plotsCompare_06();
	plotsCompare_07();
	plotsCompare_08();
	plotsCompare_09();
	plotsCompare_10();
	plotsCompare_11();
	plotsCompare_12();
	plotsCompare_13();
	plotsCompare_14();
	plotsCompare_15();
	plotsCompare_16();
	plotsCompare_17();
	plotsCompare_18();
	plotsCompare_19();
	plotsCompare_20();
}
