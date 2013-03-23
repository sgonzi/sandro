#define plotsCompare_cxx
#include "comparestack.C"

void plotsCompare1(){
//	comparestack("Nvtx_True_", "N^{vtx} ");
	comparestack("nPhotons_True_", "N^{#gamma}");
	comparestack("photonPt_1_True_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]");
	comparestack("photonE_1_True_", "E^{#gamma1} [GeV]");
	comparestack("photonEta_1_True_", "#eta^{#gamma1}");
//}

//void plotsCompare2(){
	comparestack("photonPhi_1_True_", "#varphi^{#gamma1}");
/*
	comparestack("photonBit_1_True_", "bit^{#gamma1}");
	comparestack("photonPfIsoChargedHad_1_True_", "#gamma1 PfIsoChargedHad");
	comparestack("photonPfIsoNeutralHad_1_True_", "#gamma1 PfIsoNeutralHad");
	comparestack("photonPfIsoPhoton_1_True_", "#gamma1 PfIsoPhoton");
//}

//void plotsCompare3(){
	comparestack("photonPfIsoPhotons03ForCic_1_True_", "#gamma1 PfIsoPhotons03ForCic");
	comparestack("photonPfIsoNeutrals03ForCic_1_True_", "#gamma1 PfIsoNeutrals03ForCic");
	comparestack("photonPfIsoCharged03ForCicVtx0_1_True_", "#gamma1 PfIsoCharged03ForCicVtx0");
	comparestack("photonPfIsoCharged03BadForCic_1_True_", "#gamma1 PfIsoCharged03BadForCic");
	comparestack("photonPfIsoPhotons04ForCic_1_True_", "#gamma1 PfIsoPhotons04ForCic");
//}

//void plotsCompare4(){
	comparestack("photonPfIsoNeutrals04ForCic_1_True_", "#gamma1 PfIsoNeutrals04ForCic");
	comparestack("photonPfIsoCharged04ForCicVtx0_1_True_", "#gamma1  PfIsoCharged04ForCicVtx0");
	comparestack("photonPfIsoCharged04BadForCic_1_True_", "#gamma1 PfIsoCharged04BadForCic");
	comparestack("photonid_sieie_1_True_", "#gamma1 #sigma_{i#etai#eta}");
	comparestack("photonid_sieip_1_True_", "#gamma1 #sigma_{i#etai#varphi}");
//}

//void plotsCompare5(){
	comparestack("photonid_etawidth_1_True_", "#gamma1 #eta width");
	comparestack("photonid_phiwidth_1_True_", "#gamma1 #varphi width");
	comparestack("photonid_r9_1_True_", "#gamma1 r9");
	comparestack("photonid_lambdaRatio_1_True_", "#gamma1 #lambda Ratio");
	comparestack("photonid_s4Ratio_1_True_", "#gamma1 s4 Ratio");
//}

//void plotsCompare6(){
	comparestack("photonid_e25_1_True_", "#gamma1 #rho25");
	comparestack("photonid_sceta_1_True_", "#gamma1 SC #eta");
	comparestack("photonid_ESEffSigmaRR_1_True_", "#gamma1 ESEffSigmaRR");
	comparestack("photonid_hadronicOverEm_1_True_", "#gamma1 hadronicOverEm");
	comparestack("photonid_hadronicOverEm2012_1_True_", "#gamma1 hadronicOverEm2012");
//}

//void plotsCompare7(){
	comparestack("photonhcalTowerSumEtConeDR04_1_True_", "#gamma1 hcalTowerSumEtConeDR04");
	comparestack("photonecalRecHitSumEtConeDR04_1_True_", "#gamma1 ecalRecHitSumEtConeDR04");
	comparestack("photonnTrkSolidConeDR04_1_True_", "#gamma1 nTrkSolidConeDR04");
	comparestack("photontrkSumPtSolidConeDR04_1_True_", "#gamma1 trkSumPtSolidConeDR04");
	comparestack("photonnTrkHollowConeDR04_1_True_", "#gamma1 nTrkHollowConeDR04");
//}

//void plotsCompare8(){
	comparestack("photontrkSumPtHollowConeDR04_1_True_", "#gamma1 trkSumPtHollowConeDR04");
	comparestack("photontrkSumPtHollowConeDR04_True_", "#gamma1 trkSumPtHollowConeDR04");
	comparestack("photonIsoFPRCharged_1_True_", "#gamma1 IsoFPRCharged/p_{T}");
	comparestack("photonIsoFPRNeutral_1_True_", "#gamma1 IsoFPRNeutral/p_{T}");
	comparestack("photonIsoFPRPhoton_1_True_", "#gamma1 IsoFPRPhoton/p_{T}");
*/
	comparestack("nJets_True_", "N^{jets}");
//}

//void plotsCompare9(){
	comparestack("jetPt_1_True_", "p_{T}^{jet1} [GeV/#font[12]{c}]");
	comparestack("jetEta_1_True_", "#eta^{jet1}");
	comparestack("jetPhi_1_True_", "#varphi^{jet1}");
	comparestack("jetE_1_True_", "E^{jet1}[GeV]");
	comparestack("jetPt_2_True_", "p_{T}^{jet2} [GeV/#font[12]{c}]");
//}

//void plotsCompare10(){
	comparestack("jetEta_2_True_", "#eta^{jet2}");
	comparestack("jetPhi_2_True_", "#varphi^{jet2}");
	comparestack("jetE_2_True_", "E^{jet2} [GeV]");
	comparestack("jetPt_3_True_", "p_{T}^{jet3} [GeV/#font[12]{c}]");
	comparestack("jetEta_3_True_", "#eta^{jet3}");
//}

//void plotsCompare11(){
	comparestack("jetPhi_3_True_", "#varphi^{jet3}");
	comparestack("jetE_3_True_", "E^{jet3} [GeV]");
	comparestack("DeltaR_photon1_jet1_True_", "#DeltaR #gamma1-jet1");
	comparestack("DeltaEta_photon1_jet1_True_","#Delta#eta #gamma1-jet1");
	comparestack("DeltaPhi_photon1_jet1_True_","#Delta#varphi #gamma1-jet1");
//}

//void plotsCompare12(){
	comparestack("DeltaR_photon1_jet2_True_", "#DeltaR #gamma1-jet2");
	comparestack("DeltaR_jet1_jet2_True_","#DeltaR jet1-jet2");
	comparestack("DeltaEta_jet1_jet2_True_","#Delta#eta jet1-jet2");
	comparestack("DeltaPhi_jet1_jet2_True_","#Delta#varphi jet1-jet2");
	comparestack("DeltaR_photon1_jet3_True_", "#DeltaR #gamma1-jet3");
	comparestack("HT_True_","H_{T}");
}
