#define plotsCompare_cxx
#include "comparestack.C"

void plotsCompare1(){

	comparestack("Nvtx_cl_", "N^{vtx} ");
	comparestack("nPhotons_cl_", "N^{#gamma}");
	comparestack("photonPt_1_cl_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]");
	comparestack("photonE_1_cl_", "E^{#gamma1} [GeV]");
	comparestack("photonEta_1_cl_", "#eta^{#gamma1}");
	comparestack("photonPhi_1_cl_", "#varphi^{#gamma1}");
	comparestack("photonBit_1_cl_", "bit^{#gamma1}");
}

void plotsCompare2(){
	comparestack("photonPfIsoChargedHad_1_cl_", "#gamma1 PfIsoChargedHad");
	comparestack("photonPfIsoNeutralHad_1_cl_", "#gamma1 PfIsoNeutralHad");
	comparestack("photonPfIsoPhoton_1_cl_", "#gamma1 PfIsoPhoton");
	comparestack("photonPfIsoPhotons03ForCic_1_cl_", "#gamma1 PfIsoPhotons03ForCic");
	comparestack("photonPfIsoNeutrals03ForCic_1_cl_", "#gamma1 PfIsoNeutrals03ForCic");
	comparestack("photonPfIsoCharged03ForCicVtx0_1_cl_", "#gamma1 PfIsoCharged03ForCicVtx0");
	comparestack("photonPfIsoCharged03BadForCic_1_cl_", "#gamma1 PfIsoCharged03BadForCic");
	comparestack("photonPfIsoPhotons04ForCic_1_cl_", "#gamma1 PfIsoPhotons04ForCic");
	comparestack("photonPfIsoNeutrals04ForCic_1_cl_", "#gamma1 PfIsoNeutrals04ForCic");
	comparestack("photonPfIsoCharged04ForCicVtx0_1_cl_", "#gamma1  PfIsoCharged04ForCicVtx0");
	comparestack("photonPfIsoCharged04BadForCic_1_cl_", "#gamma1 PfIsoCharged04BadForCic");
}

void plotsCompare3(){
	comparestack("photonid_sieie_1_cl_", "#gamma1 #sigma_{i#etai#eta}");
	comparestack("photonid_sieip_1_cl_", "#gamma1 #sigma_{i#etai#varphi}");
	comparestack("photonid_etawidth_1_cl_", "#gamma1 #eta width");
	comparestack("photonid_phiwidth_1_cl_", "#gamma1 #varphi width");
	comparestack("photonid_r9_1_cl_", "#gamma1 r9");
	comparestack("photonid_lambdaRatio_1_cl_", "#gamma1 #lambda Ratio");
	comparestack("photonid_s4Ratio_1_cl_", "#gamma1 s4 Ratio");
	comparestack("photonid_e25_1_cl_", "#gamma1 #rho25");
	comparestack("photonid_sceta_1_cl_", "#gamma1 SC #eta");
}

void plotsCompare4(){
	comparestack("photonid_ESEffSigmaRR_1_cl_", "#gamma1 ESEffSigmaRR");
	comparestack("photonid_hadronicOverEm_1_cl_", "#gamma1 hadronicOverEm");
	comparestack("photonid_hadronicOverEm2012_1_cl_", "#gamma1 hadronicOverEm2012");
	comparestack("photonhcalTowerSumEtConeDR04_1_cl_", "#gamma1 hcalTowerSumEtConeDR04");
	comparestack("photonecalRecHitSumEtConeDR04_1_cl_", "#gamma1 ecalRecHitSumEtConeDR04");
	comparestack("photonnTrkSolidConeDR04_1_cl_", "#gamma1 nTrkSolidConeDR04");
	comparestack("photontrkSumPtSolidConeDR04_1_cl_", "#gamma1 trkSumPtSolidConeDR04");
	comparestack("photonnTrkHollowConeDR04_1_cl_", "#gamma1 nTrkHollowConeDR04");
	comparestack("photontrkSumPtHollowConeDR04_", "#gamma1 trkSumPtHollowConeDR04");
	comparestack("photonIsoFPRCharged_1_cl_", "#gamma1 IsoFPRCharged");
	comparestack("photonIsoFPRNeutral_1_cl_", "#gamma1 IsoFPRNeutral");
	comparestack("photonIsoFPRPhoton_1_cl_", "#gamma1 IsoFPRPhoton");
}

void plotsCompare5(){
	comparestack("nJets_cl_", "N^{jets}");
	comparestack("jetPt_1_cl_", "p_{T}^{jet1} [GeV/#font[12]{c}]");
	comparestack("jetEta_1_cl_", "#eta^{jet1}");
	comparestack("jetPhi_1_cl_", "#varphi^{jet1}");
	comparestack("jetE_1_cl_", "E^{jet1}[GeV]");
	comparestack("jetPt_2_cl_", "p_{T}^{jet2} [GeV/#font[12]{c}]");
	comparestack("jetEta_2_cl_", "#eta^{jet2}");

	comparestack("jetPhi_2_cl_", "#varphi^{jet2}");
	comparestack("jetE_2_cl_", "E^{jet2} [GeV]");
	comparestack("jetPt_3_cl_", "p_{T}^{jet3} [GeV/#font[12]{c}]");
	comparestack("jetEta_3_cl_", "#eta^{jet3}");

	comparestack("jetPhi_3_cl_", "#varphi^{jet3}");
	comparestack("jetE_3_cl_", "E^{jet3} [GeV]");
	comparestack("DeltaR_photon1_jet1_cl_", "#DeltaR #gamma1-jet1");
	comparestack("DeltaR_photon1_jet2_cl_", "#DeltaR #gamma1-jet2");
	comparestack("DeltaR_photon1_jet3_cl_", "#DeltaR #gamma1-jet3");

	comparestack("DeltaPhi_photon1_jet1_cl_","#Delta#varphi photon1-jet1");
	comparestack("DeltaEta_jet1_jet2_cl_","#Delta#eta jet1-jet2");
	comparestack("DeltaPhi_jet1_jet2_cl_","#Delta#varphi jet1-jet2");
	comparestack("HT_cl_","H_{T}");
}
