#define corrected_plotsCompare_cxx
#include "corrected_comparestack.C"
#include <string>

string geo_string(string out) {
	string in = "barrel";
	out = in;
	return out;
}

bool inv_sigmaietaieta(bool out) {
	bool in = false;
	out = in;
	return out;
}


void corrected_plotsCompare_01(){

	corrected_comparestack("IDIsoPhotons_N_", "ID-Iso Photons N", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_N_","Selected Photons N", 1, -999, -999);

	corrected_comparestack("Nvtx_", "N^{vtx} ", 1, -999, -999);

	corrected_comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 4, 0, 2000);
	corrected_comparestack("SelectedPhotons_E_1_", "E^{#gamma1} [GeV]", 4, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){ 
		corrected_comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		corrected_comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma1}", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_Phi_1_", "#varphi^{#gamma1}", 20, -999, -999);
	corrected_comparestack("SelectedPhotons_Bit_1_", "bit^{#gamma1}", 1, -999, -999);

	/*
	corrected_comparestack("SelectedPhotons_TeP_SF_1_","Photon SF ", 1, -999, -999);
	*/
}


void corrected_plotsCompare_02(){
	corrected_comparestack("SelectedPhotons_PassConversionVeto_1_","photonPassConversionVeto", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_", "#gamma1 PfIsoChargedHad", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_", "#gamma1 PfIsoNeutralHad", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_", "#gamma1 PfIsoPhoton", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_", "photon PfIso", 4, 0, 20);
}


void corrected_plotsCompare_03(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_", "#gamma1 PfIsoChargedHad #rho corrected", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_", "#gamma1 PfIsoNeutralHad #rho corrected", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_", "#gamma1 PfIsoPhoton #rho corrected", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_", "photon PfIso #rho corrected", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_", "#gamma1 PfIsoChargedHad #rho corrected for Fit", 1, -2, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit", 4, -2, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_", "#gamma1 PfIsoPhoton #rho corrected for Fit", 1, -2, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_", "photon PfIso #rho corrected for Fit", 4, -2, 20);

}


void corrected_plotsCompare_04(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin01_","#gamma1 #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 150", 2, 0, 0.012); 
	}
	else {
	comparestack("SelectedPhotons_id_sieie_1_bin01_","#gamma1 #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 150", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin01_", "#gamma1 PfIsoChargedHad, 100 < p_{T}^{#gamma} < 150", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin01_", "#gamma1 PfIsoNeutralHad, 100 < p_{T}^{#gamma} < 150", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin01_", "#gamma1 PfIsoPhoton, 100 < p_{T}^{#gamma} < 150", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin01_", "photon PfIso, 100 < p_{T}^{#gamma} < 150", 4, 0, 20);
}


void corrected_plotsCompare_05(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_", "#gamma1 PfIsoChargedHad #rho corrected, 100 < p_{T}^{#gamma} < 150", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_", "#gamma1 PfIsoNeutralHad #rho corrected, 100 < p_{T}^{#gamma} < 150", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_", "#gamma1 PfIsoPhoton #rho corrected, 100 < p_{T}^{#gamma} < 150", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin01_", "photon PfIso #rho corrected, 100 < p_{T}^{#gamma} < 150", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 100 < p_{T}^{#gamma} < 150", 1, -2, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 100 < p_{T}^{#gamma} < 150", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 100 < p_{T}^{#gamma} < 150", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_", "photon PfIso #rho corrected for Fit, 100 < p_{T}^{#gamma} < 150", 4, -10, 20);
}


void corrected_plotsCompare_06(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin02_","#gamma1 #sigma_{i#etai#eta}, 150 < p_{T}^{#gamma} < 200", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin02_","#gamma1 #sigma_{i#etai#eta}, 150 < p_{T}^{#gamma} < 200", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin02_", "#gamma1 PfIsoChargedHad, 150 < p_{T}^{#gamma} < 200", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin02_", "#gamma1 PfIsoNeutralHad, 150 < p_{T}^{#gamma} < 200", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin02_", "#gamma1 PfIsoPhoton, 150 < p_{T}^{#gamma} < 200", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin02_", "photon PfIso, 150 < p_{T}^{#gamma} < 200", 4, 0, 20);
}


void corrected_plotsCompare_07(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_", "#gamma1 PfIsoChargedHad #rho corrected, 150 < p_{T}^{#gamma} < 200", 1, 0, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_", "#gamma1 PfIsoNeutralHad #rho corrected, 150 < p_{T}^{#gamma} < 200", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_", "#gamma1 PfIsoPhoton #rho corrected, 150 < p_{T}^{#gamma} < 200", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin02_", "photon PfIso #rho corrected, 150 < p_{T}^{#gamma} < 200", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 150 < p_{T}^{#gamma} < 200", 1, -2, 2);
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 150 < p_{T}^{#gamma} < 200", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 150 < p_{T}^{#gamma} < 200", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_", "photon PfIso #rho corrected for Fit, 150 < p_{T}^{#gamma} < 200", 4, -10, 20);
}


void corrected_plotsCompare_08(){

	bool inv_S = false;	corrected_plotsCompare_34();
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin03_","#gamma1 #sigma_{i#etai#eta}, 200 < p_{T}^{#gamma} < 250", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin03_","#gamma1 #sigma_{i#etai#eta}, 200 < p_{T}^{#gamma} < 250", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin03_", "#gamma1 PfIsoChargedHad, 200 < p_{T}^{#gamma} < 250", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin03_", "#gamma1 PfIsoNeutralHad, 200 < p_{T}^{#gamma} < 250", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin03_", "#gamma1 PfIsoPhoton, 200 < p_{T}^{#gamma} < 250", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin03_", "photon PfIso, 200 < p_{T}^{#gamma} < 250", 4, 0, 20);
}


void corrected_plotsCompare_09(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_", "#gamma1 PfIsoChargedHad #rho corrected, 200 < p_{T}^{#gamma} < 250", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_", "#gamma1 PfIsoNeutralHad #rho corrected, 200 < p_{T}^{#gamma} < 250", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_", "#gamma1 PfIsoPhoton #rho corrected, 200 < p_{T}^{#gamma} < 250", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin03_", "photon PfIso #rho corrected, 200 < p_{T}^{#gamma} < 250", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_", "photon PfIso #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 4, -10, 20);
}


void corrected_plotsCompare_10(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin04_","#gamma1 #sigma_{i#etai#eta}, 250 < p_{T}^{#gamma} < 300", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin04_","#gamma1 #sigma_{i#etai#eta}, 250 < p_{T}^{#gamma} < 300", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin04_", "#gamma1 PfIsoChargedHad, 250 < p_{T}^{#gamma} < 300", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin04_", "#gamma1 PfIsoNeutralHad, 250 < p_{T}^{#gamma} < 300", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin04_", "#gamma1 PfIsoPhoton, 250 < p_{T}^{#gamma} < 300", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin04_", "photon PfIso, 250 < p_{T}^{#gamma} < 300", 4, 0, 20);
}


void corrected_plotsCompare_11(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_", "#gamma1 PfIsoChargedHad #rho corrected, 250 < p_{T}^{#gamma} < 300", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_", "#gamma1 PfIsoNeutralHad #rho corrected, 250 < p_{T}^{#gamma} < 300", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_", "#gamma1 PfIsoPhoton #rho corrected, 250 < p_{T}^{#gamma} < 300", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin04_", "photon PfIso #rho corrected, 250 < p_{T}^{#gamma} < 300", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_", "photon PfIso #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 4, -10, 20);
}


void corrected_plotsCompare_12(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin05_","#gamma1 #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 350", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin05_","#gamma1 #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 350", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin05_", "#gamma1 PfIsoChargedHad, 300 < p_{T}^{#gamma} < 350", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin05_", "#gamma1 PfIsoNeutralHad, 300 < p_{T}^{#gamma} < 350", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin05_", "#gamma1 PfIsoPhoton, 300 < p_{T}^{#gamma} < 350", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin05_", "photon PfIso, 300 < p_{T}^{#gamma} < 350", 4, 0, 20);
}


void corrected_plotsCompare_13(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_", "#gamma1 PfIsoChargedHad #rho corrected, 300 < p_{T}^{#gamma} < 350", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_", "#gamma1 PfIsoNeutralHad #rho corrected, 300 < p_{T}^{#gamma} < 350", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_", "#gamma1 PfIsoPhoton #rho corrected, 300 < p_{T}^{#gamma} < 350", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin05_", "photon PfIso #rho corrected, 300 < p_{T}^{#gamma} < 350", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_", "photon PfIso #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 4, -10, 20);
}


void corrected_plotsCompare_14(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin06_","#gamma1 #sigma_{i#etai#eta}, 350 < p_{T}^{#gamma} < 400", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin06_","#gamma1 #sigma_{i#etai#eta}, 350 < p_{T}^{#gamma} < 400", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin06_", "#gamma1 PfIsoChargedHad, 350 < p_{T}^{#gamma} < 400", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin06_", "#gamma1 PfIsoNeutralHad, 350 < p_{T}^{#gamma} < 400", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin06_", "#gamma1 PfIsoPhoton, 350 < p_{T}^{#gamma} < 400", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin06_", "photon PfIso, 350 < p_{T}^{#gamma} < 400", 4, 0, 20);
}


void corrected_plotsCompare_15(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_", "#gamma1 PfIsoChargedHad #rho corrected, 350 < p_{T}^{#gamma} < 400", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_", "#gamma1 PfIsoNeutralHad #rho corrected, 350 < p_{T}^{#gamma} < 400", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_", "#gamma1 PfIsoPhoton #rho corrected, 350 < p_{T}^{#gamma} < 400", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin06_", "photon PfIso #rho corrected, 350 < p_{T}^{#gamma} < 400", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_", "photon PfIso #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 4, -10, 20);
}


void corrected_plotsCompare_16(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin07_","#gamma1 #sigma_{i#etai#eta}, 400 < p_{T}^{#gamma} < 450", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin07_","#gamma1 #sigma_{i#etai#eta}, 400 < p_{T}^{#gamma} < 450", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin07_", "#gamma1 PfIsoChargedHad, 400 < p_{T}^{#gamma} < 450", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin07_", "#gamma1 PfIsoNeutralHad, 400 < p_{T}^{#gamma} < 450", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin07_", "#gamma1 PfIsoPhoton, 400 < p_{T}^{#gamma} < 450", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin07_", "photon PfIso, 400 < p_{T}^{#gamma} < 450", 4, 0, 20);
}


void corrected_plotsCompare_17(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_", "#gamma1 PfIsoChargedHad #rho corrected, 400 < p_{T}^{#gamma} < 450", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_", "#gamma1 PfIsoNeutralHad #rho corrected, 400 < p_{T}^{#gamma} < 450", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_", "#gamma1 PfIsoPhoton #rho corrected, 400 < p_{T}^{#gamma} < 450", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin07_", "photon PfIso #rho corrected, 400 < p_{T}^{#gamma} < 450", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 400 < p_{T}^{#gamma} < 450", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 400 < p_{T}^{#gamma} < 450", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 400 < p_{T}^{#gamma} < 450", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_", "photon PfIso #rho corrected for Fit, 400 < p_{T}^{#gamma} < 450", 4, -10, 20);
}


void corrected_plotsCompare_18(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin08_","#gamma1 #sigma_{i#etai#eta}, 450 < p_{T}^{#gamma} < 500", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin08_","#gamma1 #sigma_{i#etai#eta}, 450 < p_{T}^{#gamma} < 500", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin08_", "#gamma1 PfIsoChargedHad, 450 < p_{T}^{#gamma} < 500", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin08_", "#gamma1 PfIsoNeutralHad, 450 < p_{T}^{#gamma} < 500", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin08_", "#gamma1 PfIsoPhoton, 450 < p_{T}^{#gamma} < 500", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin08_", "photon PfIso, 450 < p_{T}^{#gamma} < 500", 4, 0, 20);
}


void corrected_plotsCompare_19(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_", "#gamma1 PfIsoChargedHad #rho corrected, 450 < p_{T}^{#gamma} < 500", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_", "#gamma1 PfIsoNeutralHad #rho corrected, 450 < p_{T}^{#gamma} < 500", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_", "#gamma1 PfIsoPhoton #rho corrected, 450 < p_{T}^{#gamma} < 500", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin08_", "photon PfIso #rho corrected, 450 < p_{T}^{#gamma} < 500", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 450 < p_{T}^{#gamma} < 500", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 450 < p_{T}^{#gamma} < 500", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 450 < p_{T}^{#gamma} < 500", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_", "photon PfIso #rho corrected for Fit, 450 < p_{T}^{#gamma} < 500", 4, -10, 20);
}


void corrected_plotsCompare_20(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin09_","#gamma1 #sigma_{i#etai#eta}, 500 < p_{T}^{#gamma} < 550", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin09_","#gamma1 #sigma_{i#etai#eta}, 500 < p_{T}^{#gamma} < 550", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin09_", "#gamma1 PfIsoChargedHad, 500 < p_{T}^{#gamma} < 550", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin09_", "#gamma1 PfIsoNeutralHad, 500 < p_{T}^{#gamma} < 550", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin09_", "#gamma1 PfIsoPhoton, 500 < p_{T}^{#gamma} < 550", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin09_", "photon PfIso, 500 < p_{T}^{#gamma} < 550", 4, 0, 20);
}


void corrected_plotsCompare_21(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_", "#gamma1 PfIsoChargedHad #rho corrected, 500 < p_{T}^{#gamma} < 550", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_", "#gamma1 PfIsoNeutralHad #rho corrected, 500 < p_{T}^{#gamma} < 550", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_", "#gamma1 PfIsoPhoton #rho corrected, 500 < p_{T}^{#gamma} < 550", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin09_", "photon PfIso #rho corrected, 500 < p_{T}^{#gamma} < 550", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 500 < p_{T}^{#gamma} < 550", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 500 < p_{T}^{#gamma} < 550", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 500 < p_{T}^{#gamma} < 550", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_", "photon PfIso #rho corrected for Fit, 500 < p_{T}^{#gamma} < 550", 4, -10, 20);
}


void corrected_plotsCompare_22(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin10_","#gamma1 #sigma_{i#etai#eta}, 550 < p_{T}^{#gamma} < 600", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin10_","#gamma1 #sigma_{i#etai#eta}, 550 < p_{T}^{#gamma} < 600", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin10_", "#gamma1 PfIsoChargedHad, 550 < p_{T}^{#gamma} < 600", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin10_", "#gamma1 PfIsoNeutralHad, 550 < p_{T}^{#gamma} < 600", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin10_", "#gamma1 PfIsoPhoton, 550 < p_{T}^{#gamma} < 600", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin10_", "photon PfIso, 550 < p_{T}^{#gamma} < 600", 4, 0, 20);
}


void corrected_plotsCompare_23(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_", "#gamma1 PfIsoChargedHad #rho corrected, 550 < p_{T}^{#gamma} < 600", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_", "#gamma1 PfIsoNeutralHad #rho corrected, 550 < p_{T}^{#gamma} < 600", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_", "#gamma1 PfIsoPhoton #rho corrected, 550 < p_{T}^{#gamma} < 600", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin10_", "photon PfIso #rho corrected, 550 < p_{T}^{#gamma} < 600", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 550 < p_{T}^{#gamma} < 600", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 550 < p_{T}^{#gamma} < 600", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 550 < p_{T}^{#gamma} < 600", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_", "photon PfIso #rho corrected for Fit, 550 < p_{T}^{#gamma} < 600", 4, -10, 20);
}


void corrected_plotsCompare_24(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin11_","#gamma1 #sigma_{i#etai#eta}, 600 < p_{T}^{#gamma} < 650", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin11_","#gamma1 #sigma_{i#etai#eta}, 600 < p_{T}^{#gamma} < 650", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin11_", "#gamma1 PfIsoChargedHad, 600 < p_{T}^{#gamma} < 650", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin11_", "#gamma1 PfIsoNeutralHad, 600 < p_{T}^{#gamma} < 650", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin11_", "#gamma1 PfIsoPhoton, 600 < p_{T}^{#gamma} < 650", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin11_", "photon PfIso, 600 < p_{T}^{#gamma} < 650", 4, 0, 20);
}


void corrected_plotsCompare_25(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_", "#gamma1 PfIsoChargedHad #rho corrected, 600 < p_{T}^{#gamma} < 650", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_", "#gamma1 PfIsoNeutralHad #rho corrected, 600 < p_{T}^{#gamma} < 650", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_", "#gamma1 PfIsoPhoton #rho corrected, 600 < p_{T}^{#gamma} < 650", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin11_", "photon PfIso #rho corrected, 600 < p_{T}^{#gamma} < 650", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 600 < p_{T}^{#gamma} < 650", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 600 < p_{T}^{#gamma} < 650", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 600 < p_{T}^{#gamma} < 650", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_", "photon PfIso #rho corrected for Fit, 600 < p_{T}^{#gamma} < 650", 4, -10, 20);
}


void corrected_plotsCompare_26(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin12_","#gamma1 #sigma_{i#etai#eta}, 650 < p_{T}^{#gamma} < 700", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin12_","#gamma1 #sigma_{i#etai#eta}, 650 < p_{T}^{#gamma} < 700", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin12_", "#gamma1 PfIsoChargedHad, 650 < p_{T}^{#gamma} < 700", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin12_", "#gamma1 PfIsoNeutralHad, 650 < p_{T}^{#gamma} < 700", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin12_", "#gamma1 PfIsoPhoton, 650 < p_{T}^{#gamma} < 700", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin12_", "photon PfIso, 650 < p_{T}^{#gamma} < 700", 4, 0, 20);
}


void corrected_plotsCompare_27(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_", "#gamma1 PfIsoChargedHad #rho corrected, 650 < p_{T}^{#gamma} < 700", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_", "#gamma1 PfIsoNeutralHad #rho corrected, 650 < p_{T}^{#gamma} < 700", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_", "#gamma1 PfIsoPhoton #rho corrected, 650 < p_{T}^{#gamma} < 700", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin12_", "photon PfIso #rho corrected, 650 < p_{T}^{#gamma} < 700", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 650 < p_{T}^{#gamma} < 700", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 650 < p_{T}^{#gamma} < 700", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 650 < p_{T}^{#gamma} < 700", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_", "photon PfIso #rho corrected for Fit, 650 < p_{T}^{#gamma} < 700", 4, -10, 20);
}


void corrected_plotsCompare_28(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin13_","#gamma1 #sigma_{i#etai#eta}, 700 < p_{T}^{#gamma} < 750", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin13_","#gamma1 #sigma_{i#etai#eta}, 700 < p_{T}^{#gamma} < 750", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin13_", "#gamma1 PfIsoChargedHad, 700 < p_{T}^{#gamma} < 750", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin13_", "#gamma1 PfIsoNeutralHad, 700 < p_{T}^{#gamma} < 750", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin13_", "#gamma1 PfIsoPhoton, 700 < p_{T}^{#gamma} < 750", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin13_", "photon PfIso, 700 < p_{T}^{#gamma} < 750", 4, 0, 20);
}


void corrected_plotsCompare_29(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_", "#gamma1 PfIsoChargedHad #rho corrected, 700 < p_{T}^{#gamma} < 750", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_", "#gamma1 PfIsoNeutralHad #rho corrected, 700 < p_{T}^{#gamma} < 750", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_", "#gamma1 PfIsoPhoton #rho corrected, 700 < p_{T}^{#gamma} < 750", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin13_", "photon PfIso #rho corrected, 700 < p_{T}^{#gamma} < 750", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 700 < p_{T}^{#gamma} < 750", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 700 < p_{T}^{#gamma} < 750", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 700 < p_{T}^{#gamma} < 750", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_", "photon PfIso #rho corrected for Fit, 700 < p_{T}^{#gamma} < 750", 4, -10, 20);
}


void corrected_plotsCompare_30(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin14_","#gamma1 #sigma_{i#etai#eta}, 750 < p_{T}^{#gamma} < 800", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin14_","#gamma1 #sigma_{i#etai#eta}, 750 < p_{T}^{#gamma} < 800", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin14_", "#gamma1 PfIsoChargedHad, 750 < p_{T}^{#gamma} < 800", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin14_", "#gamma1 PfIsoNeutralHad, 750 < p_{T}^{#gamma} < 800", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin14_", "#gamma1 PfIsoPhoton, 750 < p_{T}^{#gamma} < 800", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin14_", "photon PfIso, 750 < p_{T}^{#gamma} < 800", 4, 0, 20);
}


void corrected_plotsCompare_31(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_", "#gamma1 PfIsoChargedHad #rho corrected, 750 < p_{T}^{#gamma} < 800", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_", "#gamma1 PfIsoNeutralHad #rho corrected, 750 < p_{T}^{#gamma} < 800", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_", "#gamma1 PfIsoPhoton #rho corrected, 750 < p_{T}^{#gamma} < 800", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin14_", "photon PfIso #rho corrected, 750 < p_{T}^{#gamma} < 800", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 750 < p_{T}^{#gamma} < 800", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 750 < p_{T}^{#gamma} < 800", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 750 < p_{T}^{#gamma} < 800", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_", "photon PfIso #rho corrected for Fit, 750 < p_{T}^{#gamma} < 800", 4, -10, 20);
}


void corrected_plotsCompare_32(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin15_","#gamma1 #sigma_{i#etai#eta}, 800 < p_{T}^{#gamma} < 850", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin15_","#gamma1 #sigma_{i#etai#eta}, 800 < p_{T}^{#gamma} < 850", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin15_", "#gamma1 PfIsoChargedHad, 800 < p_{T}^{#gamma} < 850", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin15_", "#gamma1 PfIsoNeutralHad, 800 < p_{T}^{#gamma} < 850", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin15_", "#gamma1 PfIsoPhoton, 800 < p_{T}^{#gamma} < 850", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin15_", "photon PfIso, 800 < p_{T}^{#gamma} < 850", 4, 0, 20);
}


void corrected_plotsCompare_33(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_", "#gamma1 PfIsoChargedHad #rho corrected, 800 < p_{T}^{#gamma} < 850", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_", "#gamma1 PfIsoNeutralHad #rho corrected, 800 < p_{T}^{#gamma} < 850", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_", "#gamma1 PfIsoPhoton #rho corrected, 800 < p_{T}^{#gamma} < 850", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin15_", "photon PfIso #rho corrected, 800 < p_{T}^{#gamma} < 850", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 800 < p_{T}^{#gamma} < 850", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 800 < p_{T}^{#gamma} < 850", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 800 < p_{T}^{#gamma} < 850", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_", "photon PfIso #rho corrected for Fit, 800 < p_{T}^{#gamma} < 850", 4, -10, 20);
}


void corrected_plotsCompare_34(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin16_","#gamma1 #sigma_{i#etai#eta}, 850 < p_{T}^{#gamma} < 900", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin16_","#gamma1 #sigma_{i#etai#eta}, 850 < p_{T}^{#gamma} < 900", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin16_", "#gamma1 PfIsoChargedHad, 850 < p_{T}^{#gamma} < 900", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin16_", "#gamma1 PfIsoNeutralHad, 850 < p_{T}^{#gamma} < 900", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin16_", "#gamma1 PfIsoPhoton, 850 < p_{T}^{#gamma} < 900", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin16_", "photon PfIso, 850 < p_{T}^{#gamma} < 900", 4, 0, 20);
}


void corrected_plotsCompare_35(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_", "#gamma1 PfIsoChargedHad #rho corrected, 850 < p_{T}^{#gamma} < 900", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_", "#gamma1 PfIsoNeutralHad #rho corrected, 850 < p_{T}^{#gamma} < 900", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_", "#gamma1 PfIsoPhoton #rho corrected, 850 < p_{T}^{#gamma} < 900", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin16_", "photon PfIso #rho corrected, 850 < p_{T}^{#gamma} < 900", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 850 < p_{T}^{#gamma} < 900", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 850 < p_{T}^{#gamma} < 900", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 850 < p_{T}^{#gamma} < 900", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_", "photon PfIso #rho corrected for Fit, 850 < p_{T}^{#gamma} < 900", 4, -10, 20);
}


void corrected_plotsCompare_36(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin17_","#gamma1 #sigma_{i#etai#eta}, 900 < p_{T}^{#gamma} < 950", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin17_","#gamma1 #sigma_{i#etai#eta}, 900 < p_{T}^{#gamma} < 950", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin17_", "#gamma1 PfIsoChargedHad, 900 < p_{T}^{#gamma} < 950", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin17_", "#gamma1 PfIsoNeutralHad, 900 < p_{T}^{#gamma} < 950", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin17_", "#gamma1 PfIsoPhoton, 900 < p_{T}^{#gamma} < 950", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin17_", "photon PfIso, 900 < p_{T}^{#gamma} < 950", 4, 0, 20);
}


void corrected_plotsCompare_37(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_", "#gamma1 PfIsoChargedHad #rho corrected, 900 < p_{T}^{#gamma} < 950", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_", "#gamma1 PfIsoNeutralHad #rho corrected, 900 < p_{T}^{#gamma} < 950", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_", "#gamma1 PfIsoPhoton #rho corrected, 900 < p_{T}^{#gamma} < 950", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin17_", "photon PfIso #rho corrected, 900 < p_{T}^{#gamma} < 950", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 900 < p_{T}^{#gamma} < 950", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 900 < p_{T}^{#gamma} < 950", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 900 < p_{T}^{#gamma} < 950", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_", "photon PfIso #rho corrected for Fit, 900 < p_{T}^{#gamma} < 950", 4, -10, 20);
}


void corrected_plotsCompare_38(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin18_","#gamma1 #sigma_{i#etai#eta}, 950 < p_{T}^{#gamma} < 1000", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin18_","#gamma1 #sigma_{i#etai#eta}, 950 < p_{T}^{#gamma} < 1000", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin18_", "#gamma1 PfIsoChargedHad, 950 < p_{T}^{#gamma} < 1000", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin18_", "#gamma1 PfIsoNeutralHad, 950 < p_{T}^{#gamma} < 1000", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin18_", "#gamma1 PfIsoPhoton, 950 < p_{T}^{#gamma} < 1000", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin18_", "photon PfIso, 950 < p_{T}^{#gamma} < 1000", 4, 0, 20);
}


void corrected_plotsCompare_39(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_", "#gamma1 PfIsoChargedHad #rho corrected, 950 < p_{T}^{#gamma} < 1000", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_", "#gamma1 PfIsoNeutralHad #rho corrected, 950 < p_{T}^{#gamma} < 1000", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_", "#gamma1 PfIsoPhoton #rho corrected, 950 < p_{T}^{#gamma} < 1000", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin18_", "photon PfIso #rho corrected, 950 < p_{T}^{#gamma} < 1000", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, 950 < p_{T}^{#gamma} < 1000", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, 950 < p_{T}^{#gamma} < 1000", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_", "#gamma1 PfIsoPhoton #rho corrected for Fit, 950 < p_{T}^{#gamma} < 1000", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_", "photon PfIso #rho corrected for Fit, 950 < p_{T}^{#gamma} < 1000", 4, -10, 20);
}


void corrected_plotsCompare_40(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin19_","#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma} > 1000", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin19_","#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma} > 1000", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin19_", "#gamma1 PfIsoChargedHad, p_{T}^{#gamma} > 1000", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin19_", "#gamma1 PfIsoNeutralHad, p_{T}^{#gamma} > 1000", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin19_", "#gamma1 PfIsoPhoton, p_{T}^{#gamma} > 1000", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin19_", "photon PfIso, p_{T}^{#gamma} > 1000", 4, 0, 20);
}


void corrected_plotsCompare_41(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_", "#gamma1 PfIsoChargedHad #rho corrected, p_{T}^{#gamma} > 1000", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_", "#gamma1 PfIsoNeutralHad #rho corrected, p_{T}^{#gamma} > 1000", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_", "#gamma1 PfIsoPhoton #rho corrected, p_{T}^{#gamma} > 1000", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin19_", "photon PfIso #rho corrected, p_{T}^{#gamma} > 1000", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, p_{T}^{#gamma} > 1000", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, p_{T}^{#gamma} > 1000", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_", "#gamma1 PfIsoPhoton #rho corrected for Fit, p_{T}^{#gamma} > 1000", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_", "photon PfIso #rho corrected for Fit, p_{T}^{#gamma} > 1000", 4, -10, 20);
}


void corrected_plotsCompare_42(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		comparestack("SelectedPhotons_id_sieie_1_bin20_","#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma} > 400", 2, 0, 0.012);
	}
	else {
		comparestack("SelectedPhotons_id_sieie_1_bin20_","#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma} > 400", 2, 0.010, 0.025); // inverted
	}
	
	comparestack("SelectedPhotons_PfIsoChargedHad_1_bin20_", "#gamma1 PfIsoChargedHad, p_{T}^{#gamma} > 400", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin20_", "#gamma1 PfIsoNeutralHad, p_{T}^{#gamma} > 400", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_1_bin20_", "#gamma1 PfIsoPhoton, p_{T}^{#gamma} > 400", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_1_bin20_", "photon PfIso, p_{T}^{#gamma} > 400", 4, 0, 20);
}


void corrected_plotsCompare_43(){
	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_", "#gamma1 PfIsoChargedHad #rho corrected, p_{T}^{#gamma} > 400", 1, 0, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_", "#gamma1 PfIsoNeutralHad #rho corrected, p_{T}^{#gamma} > 400", 4, 0, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_", "#gamma1 PfIsoPhoton #rho corrected, p_{T}^{#gamma} > 400", 1, 0, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin20_", "photon PfIso #rho corrected, p_{T}^{#gamma} > 400", 4, 0, 20);

	comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_", "#gamma1 PfIsoChargedHad #rho corrected for Fit, p_{T}^{#gamma} > 400", 1, -2, 2); 
	comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_", "#gamma1 PfIsoNeutralHad #rho corrected for Fit, p_{T}^{#gamma} > 400", 4, -10, 20);
	comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_", "#gamma1 PfIsoPhoton #rho corrected for Fit, p_{T}^{#gamma} > 400", 1, -10, 6);
	comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_", "photon PfIso #rho corrected for Fit, p_{T}^{#gamma} > 400", 4, -10, 20);
}


void corrected_plotsCompare_44(){		
	corrected_comparestack("SelectedPhotons_PfIsoPhotons03ForCic_1_", "#gamma1 PfIsoPhotons03ForCic", 8, 0, 80);
	corrected_comparestack("SelectedPhotons_PfIsoNeutrals03ForCic_1_", "#gamma1 PfIsoNeutrals03ForCic", 4, 0, 40);
	corrected_comparestack("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "#gamma1 PfIsoCharged03ForCicVtx0", 8, 0, 80);
	corrected_comparestack("SelectedPhotons_PfIsoCharged03BadForCic_1_", "#gamma1 PfIsoCharged03BadForCic", 20, 0, 200);
}


void corrected_plotsCompare_45(){		
	corrected_comparestack("SelectedPhotons_PfIsoPhotons04ForCic_1_", "#gamma1 PfIsoPhotons04ForCic", 8, 0, 80);
	corrected_comparestack("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "#gamma1 PfIsoNeutrals04ForCic", 40, 0, 200);
	corrected_comparestack("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "#gamma1  PfIsoCharged04ForCicVtx0", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_PfIsoCharged04BadForCic_1_", "#gamma1 PfIsoCharged04BadForCic", 20, 0, 200);
}


void corrected_plotsCompare_46(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_", "#gamma1 #sigma_{i#etai#eta}", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_", "#gamma1 #sigma_{i#etai#eta}", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_id_sieip_1_", "#gamma1 #sigma_{i#etai#varphi}", 2, 0, 0.014);
	corrected_comparestack("SelectedPhotons_id_etawidth_1_", "#gamma1 #eta width", 4, 0, 0.02);
	corrected_comparestack("SelectedPhotons_id_phiwidth_1_", "#gamma1 #varphi width", 2, 0, 0.15);
	corrected_comparestack("SelectedPhotons_id_r9_1_", "#gamma1 r9", 1, 0, 1.1);
	corrected_comparestack("SelectedPhotons_id_lambdaRatio_1_", "#gamma1 #lambda Ratio", 1, 0, 1.1);
	corrected_comparestack("SelectedPhotons_id_s4Ratio_1_", "#gamma1 s4 Ratio", 1, 0, 1.1);
	corrected_comparestack("SelectedPhotons_id_e25_1_", "#gamma1 #rho25", 2, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){ 
		corrected_comparestack("SelectedPhotons_id_sceta_1_", "#gamma1 SC #eta", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		corrected_comparestack("SelectedPhotons_id_sceta_1_", "#gamma1 SC #eta", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_id_ESEffSigmaRR_1_", "#gamma1 ESEffSigmaRR", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_id_hadronicOverEm_1_", "#gamma1 hadronicOverEm", 20, 0, 0.2);
	corrected_comparestack("SelectedPhotons_id_hadronicOverEm2012_1_", "#gamma1 hadronicOverEm2012", 10, 0, 0.06);
}


void corrected_plotsCompare_47(){
	corrected_comparestack("SelectedPhotons_hcalTowerSumEtConeDR04_1_", "#gamma1 hcalTowerSumEtConeDR04", 2, 0, 200);
	corrected_comparestack("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "#gamma1 ecalRecHitSumEtConeDR04", 2, 0, 200);
	corrected_comparestack("SelectedPhotons_nTrkSolidConeDR04_1_", "#gamma1 nTrkSolidConeDR04", 1, 0, 20);
	corrected_comparestack("SelectedPhotons_trkSumPtSolidConeDR04_1_", "#gamma1 trkSumPtSolidConeDR04", 4, 0, 200);
	corrected_comparestack("SelectedPhotons_nTrkHollowConeDR04_1_", "#gamma1 nTrkHollowConeDR04", 1, 0, 20);
	corrected_comparestack("SelectedPhotons_trkSumPtHollowConeDR04_1_", "#gamma1 trkSumPtHollowConeDR04", 4, 0, 200);
}	


void corrected_plotsCompare_48(){	
	corrected_comparestack("SelectedPhotons_IsoFPRCharged_1_", "#gamma1 IsoFPRCharged", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPRNeutral_1_", "#gamma1 IsoFPRNeutral", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_1_", "#gamma1 IsoFPRPhoton", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPR_1_", "#gamma1 photon IsoFPR", 4, 0, 20);
}


void corrected_plotsCompare_49(){
	corrected_comparestack("SelectedJets_N_", "Selected Jets N", 1, -999, -999);
}


void corrected_plotsCompare_50(){
	corrected_comparestack("SelectedJets_Pt_1_", "p_{T}^{jet1} [GeV/#font[12]{c}]", 4, 0, 2000);
	corrected_comparestack("SelectedJets_E_1_", "E^{jet1}[GeV]", 4, 0, 3000);
	corrected_comparestack("SelectedJets_Eta_1_", "#eta^{jet1}", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_1_", "#varphi^{jet1}", 20, -999, -999);
}


void corrected_plotsCompare_51(){
	corrected_comparestack("SelectedJets_HT_", "Selected Jets H_{T}", 4, 0, 3000);
}


void corrected_plotsCompare_52(){
	corrected_comparestack("DeltaR_photon1_jet1_N0_", "#DeltaR #gamma1-jet1 - N^{jets} #geq 1", 20, 0, 6);
	corrected_comparestack("DeltaEta_photon1_jet1_N0_","#Delta#eta #gamma1-jet1 - N^{jets} #geq 1", 10, 0, 5);
	corrected_comparestack("DeltaPhi_photon1_jet1_N0_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 1", 10, 0, 3.1416);
}


void corrected_plotsCompare_53(){
	corrected_comparestack("thrust_N0_","#tau_{T} - N^{jets} #geq 1", 2, 0, 0.35);
	corrected_comparestack("broad_N0_","broad - N^{jets} #geq 1", 2, 0, 1);
	corrected_comparestack("S3_N0_","S3 - N^{jets} #geq 1", 1, -1, 5);
	corrected_comparestack("S4_N0_","S4 - N^{jets} #geq 1", 1, -0.2, 0.2);

	corrected_comparestack("ln_thrust_N0_","ln #tau_{T} - N^{jets} #geq 1", 3, -30, 0);
	corrected_comparestack("ln_broad_N0_","ln broad - N^{jets} #geq 1", 1, -3, 1);
	corrected_comparestack("ln_S3_N0_","ln S3 - N^{jets} #geq 1", 2, -4, 3);
	corrected_comparestack("ln_S4_N0_","ln S4 - N^{jets} #geq 1", 1, -999, 999);		
}


void corrected_plotsCompare_54(){
	corrected_comparestack("SelectedPhotons_Pt_excl1_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}], 1 jet exclusive", 4, 0, 2000);
	corrected_comparestack("SelectedPhotons_E_excl1_1_", "E^{#gamma1} [GeV], 1 jet exclusive", 4, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){	
		corrected_comparestack("SelectedPhotons_Eta_excl1_1_", "#eta^{#gamma1}, 1 jet exclusive", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		corrected_comparestack("SelectedPhotons_Eta_excl1_1_", "#eta^{#gamma1}, 1 jet exclusive", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_Phi_excl1_1_", "#varphi^{#gamma1}, 1 jet exclusive", 20, -999, -999);
}


void corrected_plotsCompare_55(){
	corrected_comparestack("SelectedJets_Pt_excl1_1_", "p_{T}^{jet1} [GeV/#font[12]{c}], 1 jet exclusive", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_excl1_1_", "E^{jet1} [GeV], 1 jet exclusive", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_excl1_1_", "#eta^{jet1}, 1 jet exclusive", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_excl1_1_", "#varphi^{jet1}, 1 jet exclusive", 20, -999, -999);
}


void corrected_plotsCompare_56(){
	corrected_comparestack("SelectedPhotons_Pt_excl2_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}], 2 jet exclusive", 4, 0, 2000);
	corrected_comparestack("SelectedPhotons_E_excl2_1_", "E^{#gamma1} [GeV], 2 jet exclusive", 4, 0, 2000);
	
	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){
	corrected_comparestack("SelectedPhotons_Eta_excl2_1_", "#eta^{#gamma1}, 2 jet exclusive", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 	
		corrected_comparestack("SelectedPhotons_Eta_excl2_1_", "#eta^{#gamma1}, 2 jet exclusive", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_Phi_excl2_1_", "#varphi^{#gamma1}, 2 jet exclusive", 20, -999, -999);
}


void corrected_plotsCompare_57(){
	corrected_comparestack("SelectedJets_Pt_excl2_1_", "p_{T}^{jet1} [GeV/#font[12]{c}], 2 jet exclusive", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_excl2_1_", "E^{jet1} [GeV], 2 jet exclusive", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_excl2_1_", "#eta^{jet1}, 2 jet exclusive", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_excl2_1_", "#varphi^{jet1}, 2 jet exclusive", 20, -999, -999);
}


void corrected_plotsCompare_58(){
	corrected_comparestack("SelectedJets_Pt_excl2_2_", "p_{T}^{jet2} [GeV/#font[12]{c}], 2 jet exclusive", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_excl2_2_", "E^{jet2} [GeV], 2 jet exclusive", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_excl2_2_", "#eta^{jet2}, 2 jet exclusive", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_excl2_2_", "#varphi^{jet2}, 2 jet exclusive", 20, -999, -999);
	corrected_comparestack("SelectedJets_HT_excl2_", "Selected Jets H_{T}, 2 jet exclusive", 4, 0, 3000);	
}


void corrected_plotsCompare_59(){
	corrected_comparestack("SelectedJets_Pt_2_", "p_{T}^{jet2} [GeV/#font[12]{c}]", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_2_", "E^{jet2} [GeV]", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_2_", "#eta^{jet2}", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_2_", "#varphi^{jet2}", 20, -999, -999);
}

void corrected_plotsCompare_60(){
	corrected_comparestack("DeltaPhi_photon1_jet1_N1_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 2", 10, 0, 3.1416);
	corrected_comparestack("DeltaR_photon1_jet2_N1_", "#DeltaR #gamma1-jet2 - N^{jets} #geq 2", 20, 0, 6);
	corrected_comparestack("DeltaR_jet1_jet2_N1_","#DeltaR jet1-jet2 - N^{jets} #geq 2", 20, 0, 6);
	corrected_comparestack("DeltaEta_jet1_jet2_N1_","#Delta#eta jet1-jet2 - N^{jets} #geq 2", 10, 0, 5);
	corrected_comparestack("DeltaPhi_jet1_jet2_N1_","#Delta#varphi jet1-jet2 - N^{jets} #geq 2", 10, 0, 3.1416);
}


void corrected_plotsCompare_61(){
	corrected_comparestack("SelectedJets_Pt_3_", "p_{T}^{jet3} [GeV/#font[12]{c}]", 4, 0, 1000);
	corrected_comparestack("SelectedJets_E_3_", "E^{jet3} [GeV]", 4, 0, 2000);
	corrected_comparestack("SelectedJets_Eta_3_", "#eta^{jet3}", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_3_", "#varphi^{jet3}", 20, -999, -999);
}


void corrected_plotsCompare_62(){
	corrected_comparestack("DeltaPhi_photon1_jet1_N2_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_photon1_jet2_N2_","#Delta#varphi #gamma1-jet2 - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_photon1_jet3_N2_","#Delta#varphi #gamma1-jet3 - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaR_photon1_jet3_N2_", "#DeltaR #gamma1-jet3 - N^{jets} #geq 3", 20, 0, 6);
	corrected_comparestack("DeltaPhi_jet1_jet2_N2_","#Delta#varphi jet1-jet2 - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_jet1_jet3_N2_","#Delta#varphi jet1-jet3 - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_jet2_jet3_N2_","#Delta#varphi jet2-jet3 - N^{jets} #geq 3", 10, 0, 3.1416);
}


void corrected_plotsCompare_PrePostCuts_01(){
	corrected_comparestack("gamma_Pt_1_precut1_","Photon p_{T} pre cut 1", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut1_","Photon p_{T} post cut 1", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut2_","Photon p_{T} post cut 2", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preTriMatch_","Photon p_{T} pre Trigger Matching cut", 1, -999, -999);
}


void corrected_plotsCompare_PrePostCuts_02(){
	corrected_comparestack("gamma_Pt_1_prePassConversionVeto_","Photon p_{T} pre PassConversionVeto cut", 1, -999, -999);
	corrected_comparestack("gamma_PassConversionVeto_1_prePassConversionVeto_","photonPassConversionVeto pre PassConversionVeto cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_prehadronicOverEm2012_","Photon p_{T} pre hadronicOverEm2012 cut", 1, -999, -999);
	corrected_comparestack("gamma_hadronicOverEm2012_1_prehadronicOverEm2012_","photon ID: hadronicOverEm2012 pre hadronicOverEm2012 cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_presigmaietaieta_","Photon p_{T} pre sigmaietaieta cut", 1, -999, -999);
	corrected_comparestack("gamma_sigmaietaieta_1_presigmaietaieta_","photon ID: #sigma_{i#etai#eta} pre #sigma_{i#etai#eta} cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preiso_CH_","Photon p_{T} pre iso_CH cut", 1, -999, -999);
	corrected_comparestack("gamma_iso_CH_1_preiso_CH_","photon PfIsoChargedHad #rho corrected pre iso_CH cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preiso_NH_","Photon p_{T} pre iso_CH cut", 1, -999, -999);
	corrected_comparestack("gamma_iso_NH_1_preiso_NH_","photon PfIsoNeutralHad #rho corrected pre iso_NH cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preiso_Ph_","Photon p_{T} pre iso_NH cut", 1, -999, -999);
	corrected_comparestack("gamma_iso_Ph_1_preiso_Ph_","photon PfIso #rho corrected pre iso_Ph cut", 1, -999, -999);
}


void corrected_plotsCompare_PrePostCuts_03(){
	corrected_comparestack("gamma_Pt_1_preAcc_","Photon p_{T} pre Acc cut", 1, -999, -999);
	corrected_comparestack("gamma_Eta_1_preAcc_","Photon #eta pre Acc cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut3_","Photon p_{T} post cut 3", 1, -999, -999);
	corrected_comparestack("jets_deltaR_1_predeltaR_","#DeltaR #gamma1-jet1 - N^{jets} #geq 1 pre #DeltaR cut", 1, -999, -999);
	corrected_comparestack("jets_Pt_1_preAcc_","Jet 1 p_{T} pre Acc cut", 1, -999, -999);
	corrected_comparestack("jets_Eta_1_preAcc_","Jet 1 #eta pre Acc cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut4_","Photon p_{T} post cut 4", 1, -999, -999);
	corrected_comparestack("jets_HT_preHT_","Selected Jets H_{T} pre H_{T} cut", 1, -999, -999);
}


// ------------------------------------------------------

void corrected_plotsCompare_TOT(){
	corrected_plotsCompare_01();
	corrected_plotsCompare_02();
	corrected_plotsCompare_03();
	corrected_plotsCompare_04();
	corrected_plotsCompare_05();
	corrected_plotsCompare_06();
	corrected_plotsCompare_07();
	corrected_plotsCompare_08();
	corrected_plotsCompare_09();
	corrected_plotsCompare_10();
	corrected_plotsCompare_11();
	corrected_plotsCompare_12();
	corrected_plotsCompare_13();
	corrected_plotsCompare_14();
	corrected_plotsCompare_15();
	corrected_plotsCompare_16();
	corrected_plotsCompare_17();
	corrected_plotsCompare_18();
	corrected_plotsCompare_19();
	corrected_plotsCompare_20();
	corrected_plotsCompare_21();
	corrected_plotsCompare_22();
	corrected_plotsCompare_23();
	corrected_plotsCompare_24();
	corrected_plotsCompare_25();
	corrected_plotsCompare_26();
	corrected_plotsCompare_27();
	corrected_plotsCompare_28();
	corrected_plotsCompare_29();				
	corrected_plotsCompare_30();				
	corrected_plotsCompare_31();
	corrected_plotsCompare_32();
	corrected_plotsCompare_33();
	corrected_plotsCompare_34();
	corrected_plotsCompare_35();
	corrected_plotsCompare_36();
	corrected_plotsCompare_37();
	corrected_plotsCompare_38();
	corrected_plotsCompare_39();
	corrected_plotsCompare_40();
	corrected_plotsCompare_41();
	corrected_plotsCompare_42();
	corrected_plotsCompare_43();
	corrected_plotsCompare_44();
	corrected_plotsCompare_45();
	corrected_plotsCompare_46();
	corrected_plotsCompare_47();
	corrected_plotsCompare_48();
	corrected_plotsCompare_49();
	corrected_plotsCompare_50();
	corrected_plotsCompare_51();
	corrected_plotsCompare_52();
	corrected_plotsCompare_53();
	corrected_plotsCompare_54();
	corrected_plotsCompare_55();
	corrected_plotsCompare_56();
	corrected_plotsCompare_57();
	corrected_plotsCompare_58();
	corrected_plotsCompare_59();
	corrected_plotsCompare_60();
	corrected_plotsCompare_61();
	corrected_plotsCompare_62();
	corrected_plotsCompare_PrePostCuts_01();
	corrected_plotsCompare_PrePostCuts_02();
	corrected_plotsCompare_PrePostCuts_03();	
}
