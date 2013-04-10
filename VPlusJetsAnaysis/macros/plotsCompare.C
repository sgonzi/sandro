#define plotsCompare_cxx
#include "comparestack.C"

void plotsCompare1(){

	comparestack("IDIsoPhotons_N_", "ID-Iso Photons N");
	comparestack("SelectedPhotons_N_","Selected Photons N");

	comparestack("Nvtx_", "N^{vtx} ");

	comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]");
	comparestack("SelectedPhotons_E_1_", "E^{#gamma1} [GeV]");
	comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}");
	comparestack("SelectedPhotons_Phi_1_", "#varphi^{#gamma1}");
	comparestack("SelectedPhotons_Bit_1_", "bit^{#gamma1}");

	comparestack("SelectedPhotons_PassConversionVeto_1_","photonPassConversionVeto");
	comparestack("SelectedPhotons_PfIsoChargedHad_1_", "#gamma1 PfIsoChargedHad");
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_", "#gamma1 PfIsoNeutralHad");
	comparestack("SelectedPhotons_PfIsoPhoton_1_", "#gamma1 PfIsoPhoton");
	comparestack("SelectedPhotons_PfIsoPhotons03ForCic_1_", "#gamma1 PfIsoPhotons03ForCic");
	comparestack("SelectedPhotons_PfIsoNeutrals03ForCic_1_", "#gamma1 PfIsoNeutrals03ForCic");
	comparestack("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "#gamma1 PfIsoCharged03ForCicVtx0");
	comparestack("SelectedPhotons_PfIsoCharged03BadForCic_1_", "#gamma1 PfIsoCharged03BadForCic");
	comparestack("SelectedPhotons_PfIsoPhotons04ForCic_1_", "#gamma1 PfIsoPhotons04ForCic");
	comparestack("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "#gamma1 PfIsoNeutrals04ForCic");
	comparestack("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "#gamma1  PfIsoCharged04ForCicVtx0");
	comparestack("SelectedPhotons_PfIsoCharged04BadForCic_1_", "#gamma1 PfIsoCharged04BadForCic");
	comparestack("SelectedPhotons_id_sieie_1_", "#gamma1 #sigma_{i#etai#eta}");
	comparestack("SelectedPhotons_id_sieip_1_", "#gamma1 #sigma_{i#etai#varphi}");
	comparestack("SelectedPhotons_id_etawidth_1_", "#gamma1 #eta width");
	comparestack("SelectedPhotons_id_phiwidth_1_", "#gamma1 #varphi width");
	comparestack("SelectedPhotons_id_r9_1_", "#gamma1 r9");
	comparestack("SelectedPhotons_id_lambdaRatio_1_", "#gamma1 #lambda Ratio");
	comparestack("SelectedPhotons_id_s4Ratio_1_", "#gamma1 s4 Ratio");
	comparestack("SelectedPhotons_id_e25_1_", "#gamma1 #rho25");
	comparestack("SelectedPhotons_id_sceta_1_", "#gamma1 SC #eta");
	comparestack("SelectedPhotons_id_ESEffSigmaRR_1_", "#gamma1 ESEffSigmaRR");
	comparestack("SelectedPhotons_id_hadronicOverEm_1_", "#gamma1 hadronicOverEm");
	comparestack("SelectedPhotons_id_hadronicOverEm2012_1_", "#gamma1 hadronicOverEm2012");
	comparestack("SelectedPhotons_hcalTowerSumEtConeDR04_1_", "#gamma1 hcalTowerSumEtConeDR04");
	comparestack("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "#gamma1 ecalRecHitSumEtConeDR04");
	comparestack("SelectedPhotons_nTrkSolidConeDR04_1_", "#gamma1 nTrkSolidConeDR04");
	comparestack("SelectedPhotons_trkSumPtSolidConeDR04_1_", "#gamma1 trkSumPtSolidConeDR04");
	comparestack("SelectedPhotons_nTrkHollowConeDR04_1_", "#gamma1 nTrkHollowConeDR04");
	
	comparestack("SelectedPhotons_trkSumPtHollowConeDR04_1_", "#gamma1 trkSumPtHollowConeDR04");
	comparestack("SelectedPhotons_IsoFPRCharged_1_", "#gamma1 IsoFPRCharged/p_{T}");
	comparestack("SelectedPhotons_IsoFPRNeutral_1_", "#gamma1 IsoFPRNeutral/p_{T}");
	comparestack("SelectedPhotons_IsoFPRPhoton_1_", "#gamma1 IsoFPRPhoton/p_{T}");

	comparestack("CleanedJetsLEA_N_", "Cleaned Jets LEA N ");
	comparestack("SelectedJetsLEA_N_", "Selected Jets LEA N");
	comparestack("CleanedJets_N_", "Cleaned Jets N ");
	comparestack("SelectedJets_N_", "Selected Jets N");

	comparestack("SelectedJets_Pt_1_", "p_{T}^{jet1} [GeV/#font[12]{c}]");
	comparestack("SelectedJets_Eta_1_", "#eta^{jet1}");
	comparestack("SelectedJets_Phi_1_", "#varphi^{jet1}");
	comparestack("SelectedJets_E_1_", "E^{jet1}[GeV]");

	comparestack("SelectedJets_Pt_2_", "p_{T}^{jet2} [GeV/#font[12]{c}]");
	comparestack("SelectedJets_Eta_2_", "#eta^{jet2}");
	comparestack("SelectedJets_Phi_2_", "#varphi^{jet2}");
	comparestack("SelectedJets_E_2_", "E^{jet2} [GeV]");

	comparestack("SelectedJets_Pt_3_", "p_{T}^{jet3} [GeV/#font[12]{c}]");
	comparestack("SelectedJets_Eta_3_", "#eta^{jet3}");
	comparestack("SelectedJets_Phi_3_", "#varphi^{jet3}");
	comparestack("SelectedJets_E_3_", "E^{jet3} [GeV]");

	comparestack("DeltaR_photon1_jet1_", "#DeltaR #gamma1-jet1");
	comparestack("DeltaEta_photon1_jet1_","#Delta#eta #gamma1-jet1");
	comparestack("DeltaPhi_photon1_jet1_","#Delta#varphi #gamma1-jet1");

	comparestack("DeltaR_photon1_jet2_", "#DeltaR #gamma1-jet2");
	comparestack("DeltaR_jet1_jet2_","#DeltaR jet1-jet2");
	comparestack("DeltaEta_jet1_jet2_","#Delta#eta jet1-jet2");
	comparestack("DeltaPhi_jet1_jet2_","#Delta#varphi jet1-jet2");
	
	comparestack("DeltaR_photon1_jet3_", "#DeltaR #gamma1-jet3");

	comparestack("CleanedJets_HT_", "Cleaned Jets H_{T}");
	comparestack("SelectedJets_HT_", "Selected Jets H_{T}");

}

void plotsCompare2(){	

	comparestack("SelectedJets_preHT_N_","Selected Jets N pre-H_{T}");
	comparestack("SelectedJets_preHT_Pt_1_","Jet 1 p_{T} pre-H_{T}");
	comparestack("SelectedJets_preHT_Pt_2_","Jet 2 p_{T} pre-H_{T}");
	comparestack("SelectedJets_preHT_Pt_3_","Jet 3 p_{T} pre-H_{T}");
	comparestack("SelectedJets_preHT_HT_","Selected Jets H_{T} pre-H_{T}");
}	


