#define corrected_plotsCompare_cxx
#include "corrected_comparestack.C"
#include <string>

using namespace std;

// ==================================== definitions

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

// ==================================== functions

void corrected_plotsCompare_01(){

	corrected_comparestack("IDIsoPhotons_N_", "ID-Iso #N^{#gamma}", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_N_", "#N^{#gamma}", 1, -999, -999);

	corrected_comparestack("Nvtx_", "N^{vtx} ", 1, -999, -999);
		
	corrected_comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 4, 0, 2000);
	corrected_comparestack("SelectedPhotons_Pt_LogBin_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, -999, -999);

	corrected_comparestack("SelectedPhotons_E_1_", "E^{#gamma_{1}} [GeV]", 4, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){ 
		corrected_comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma_{1}}", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		corrected_comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma_{1}}", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_Phi_1_", "#varphi^{#gamma_{1}}", 20, -999, -999);
	corrected_comparestack("SelectedPhotons_Bit_1_", "bit^{#gamma_{1}}", 1, -999, -999);

	corrected_comparestack("SelectedPhotons_TriMatchF4Path_AND_pTrange_1_","Trigger Matching: Path^{#gamma_{1}} && p_T^{#gamma_{1}}", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_Tri_PF_1_","Trigger PF^{#gamma_{1}}", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_TeP_SF_1_","SF^{#gamma_{1}}", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_BackDataDriven_F_1_","Background data-driven F^{#gamma_{1}}", 1, -999, -999);	
}


void corrected_plotsCompare_02(){
	corrected_comparestack("SelectedPhotons_PassConversionVeto_1_","Conversion Veto", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}]", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_", "Iso [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_03(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}]", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}]", 1, -2, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 4, -10, 20);
}


void corrected_plotsCompare_04(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin01_","#sigma_{i#etai#eta}^{#gamma_{1}}, 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 2, 0, 0.012); 
	}
	else {
	corrected_comparestack("SelectedPhotons_id_sieie_1_bin01_","#sigma_{i#etai#eta}^{#gamma_{1}}, 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin01_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin01_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin01_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin01_", "Iso [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_05(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -2, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma} < 151.6", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 100 < p_{T}^{#gamma} < 151.6", 1, -10, 6);
}


void corrected_plotsCompare_06(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin02_","#sigma_{i#etai#eta}^{#gamma_{1}}, 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin02_","#sigma_{i#etai#eta}^{#gamma_{1}}, 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin02_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin02_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin02_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin02_", "Iso [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_07(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, -2, 2);
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 207.1", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 151.6 < p_{T}^{#gamma_{1}} < 207.1", 1, -10, 6);
}


void corrected_plotsCompare_08(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin03_","#sigma_{i#etai#eta}^{#gamma_{1}}, 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin03_","#sigma_{i#etai#eta}^{#gamma_{1}}, 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin03_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin03_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin03_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin03_", "Iso [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_09(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 207.1 < p_{T}^{#gamma_{1}} < 313.8", 1, -10, 6);
}


void corrected_plotsCompare_10(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin04_","#sigma_{i#etai#eta}^{#gamma_{1}}, 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin04_","#sigma_{i#etai#eta}^{#gamma_{1}}, 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin04_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin04_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin04_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin04_", "Iso [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_11(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 313.8 < p_{T}^{#gamma_{1}} < 649.8", 1, -10, 6);
}


void corrected_plotsCompare_12(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin05_","#sigma_{i#etai#eta}^{#gamma_{1}}, 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin05_","#sigma_{i#etai#eta}^{#gamma_{1}}, 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin05_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin05_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin05_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin05_", "Iso [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_13(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 649.8 < p_{T}^{#gamma_{1}} < 800", 1, -10, 6);
}


void corrected_plotsCompare_14(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin06_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin06_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin06_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin06_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin06_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin06_", "Iso [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_15(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, p_{T}^{#gamma_{1}} > 800", 1, -10, 6);
}


void corrected_plotsCompare_16(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin07_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin07_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin07_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin07_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin07_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin07_", "Iso [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_17(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, p_{T}^{#gamma_{1}} > 313.8", 1, -10, 6);
}


void corrected_plotsCompare_18(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin08_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin08_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin08_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin08_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin08_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin08_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_19(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_20(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin09_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin09_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin09_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin09_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin09_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin09_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_21(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}


void corrected_plotsCompare_22(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin10_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin10_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin10_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin10_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin10_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin10_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_23(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_24(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin11_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin11_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin11_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin11_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin11_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin11_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_25(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_26(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin12_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin12_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin12_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin12_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin12_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin12_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_27(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_28(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin13_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin13_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin13_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin13_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin13_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin13_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_29(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_30(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin14_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin14_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin14_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin14_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin14_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin14_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_31(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_32(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin15_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin15_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin15_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin15_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin15_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin15_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_33(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}




void corrected_plotsCompare_34(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin16_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin16_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin16_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin16_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin16_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin16_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_35(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_36(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin17_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin17_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin17_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin17_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin17_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin17_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_37(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_38(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin18_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin18_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin18_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin18_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin18_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin18_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_39(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_40(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin19_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin19_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin19_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin19_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin19_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin19_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_41(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_42(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin20_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_bin20_","#sigma_{i#etai#eta}^{#gamma_{1}}, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin20_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin20_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_1_bin20_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_1_bin20_", "Iso [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
}


void corrected_plotsCompare_43(){
	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, 0, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -2, 2); 
	corrected_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);
	corrected_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 4, -10, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 10000 < p_{T}^{#gamma_{1}} < 100000 [GeV/#font[12]{c}]", 1, -10, 6);
}



void corrected_plotsCompare_44(){		
	corrected_comparestack("SelectedPhotons_PfIsoPhotons03ForCic_1_", "PfIsoPhotons03ForCic^{#gamma_{1}}", 8, 0, 80);
	corrected_comparestack("SelectedPhotons_PfIsoNeutrals03ForCic_1_", "PfIsoNeutrals03ForCic^{#gamma_{1}}", 4, 0, 40);
	corrected_comparestack("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "PfIsoCharged03ForCicVtx0^{#gamma_{1}}", 8, 0, 80);
	corrected_comparestack("SelectedPhotons_PfIsoCharged03BadForCic_1_", "PfIsoCharged03BadForCic^{#gamma_{1}}", 20, 0, 200);
}


void corrected_plotsCompare_45(){		
	corrected_comparestack("SelectedPhotons_PfIsoPhotons04ForCic_1_", "PfIsoPhotons04ForCic^{#gamma_{1}}", 8, 0, 80);
	corrected_comparestack("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "PfIsoNeutrals04ForCic^{#gamma_{1}}", 40, 0, 200);
	corrected_comparestack("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "PfIsoCharged04ForCicVtx0^{#gamma_{1}}", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_PfIsoCharged04BadForCic_1_", "PfIsoCharged04BadForCic^{#gamma_{1}}", 20, 0, 200);
}


void corrected_plotsCompare_46(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		corrected_comparestack("SelectedPhotons_id_sieie_1_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 2, 0, 0.012);
	}
	else {
		corrected_comparestack("SelectedPhotons_id_sieie_1_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 2, 0.010, 0.025); // inverted
	}
	
	corrected_comparestack("SelectedPhotons_id_sieip_1_", "#sigma_{i#etai#varphi}^{#gamma_{1}}", 2, 0, 0.014);
	corrected_comparestack("SelectedPhotons_id_etawidth_1_", "#Delta#eta^{#gamma_{1}}", 4, 0, 0.02);
	corrected_comparestack("SelectedPhotons_id_phiwidth_1_", "#Delta#varphi^{#gamma_{1}}", 2, 0, 0.15);
	corrected_comparestack("SelectedPhotons_id_r9_1_", "r_{9}^{#gamma_{1}}", 1, 0, 1.1);
	corrected_comparestack("SelectedPhotons_id_lambdaRatio_1_", "#lambda Ratio^{#gamma_{1}}", 1, 0, 1.1);
	corrected_comparestack("SelectedPhotons_id_s4Ratio_1_", "s4 Ratio^{#gamma_{1}}", 1, 0, 1.1);
	corrected_comparestack("SelectedPhotons_id_e25_1_", "#rho_{25}^{#gamma_{1}}", 2, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){ 
		corrected_comparestack("SelectedPhotons_id_sceta_1_", "#eta_{SC}^{#gamma_{1}}", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		corrected_comparestack("SelectedPhotons_id_sceta_1_", "#eta_{SC}^{#gamma_{1}}", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_id_ESEffSigmaRR_1_", "ESEffSigmaRR^{#gamma_{1}}", 1, -999, -999);
	corrected_comparestack("SelectedPhotons_id_hadronicOverEm_1_", "H/E^{#gamma_{1}} ", 20, 0, 0.2);
	corrected_comparestack("SelectedPhotons_id_hadronicOverEm2012_1_", "H/E_{2012}^{#gamma_{1}}", 10, 0, 0.06);
}


void corrected_plotsCompare_47(){
	corrected_comparestack("SelectedPhotons_hcalTowerSumEtConeDR04_1_", "hcalTowerSumEtConeDR04^{#gamma_{1}}", 2, 0, 200);
	corrected_comparestack("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "ecalRecHitSumEtConeDR04^{#gamma_{1}}", 2, 0, 200);
	corrected_comparestack("SelectedPhotons_nTrkSolidConeDR04_1_", "nTrkSolidConeDR04^{#gamma_{1}}", 1, 0, 20);
	corrected_comparestack("SelectedPhotons_trkSumPtSolidConeDR04_1_", "trkSumPtSolidConeDR04^{#gamma_{1}}", 4, 0, 200);
	corrected_comparestack("SelectedPhotons_nTrkHollowConeDR04_1_", "nTrkHollowConeDR04^{#gamma_{1}}", 1, 0, 20);
	corrected_comparestack("SelectedPhotons_trkSumPtHollowConeDR04_1_", "trkSumPtHollowConeDR04^{#gamma_{1}}", 4, 0, 200);
}	


void corrected_plotsCompare_48(){	
	corrected_comparestack("SelectedPhotons_IsoFPRCharged_1_", "Iso^{#gamma_{1}}_{ChHad-FPR} [GeV/#font[12]{c}]", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPRNeutral_1_", "Iso^{#gamma_{1}}_{NeHad-FPR} [GeV/#font[12]{c}]", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_1_", "Iso^{#gamma_{1}}_{Pho-FPR} [GeV/#font[12]{c}]", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPR_1_", "Iso^{#gamma_{1}}_{FPR} [GeV/#font[12]{c}]", 4, 0, 20);

	corrected_comparestack("SelectedPhotons_IsoFPRRandomConeCharged_1_", "Iso^{#gamma_{1}}_{ChHad-FPR} [GeV/#font[12]{c}] - template", 20, 0, 200); 
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConeNeutral_1_", "Iso^{#gamma_{1}}_{NeHad-FPR} [GeV/#font[12]{c}] - template", 20, 0, 200);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_1_", "Iso^{#gamma_{1}}_{Pho-FPR} [GeV/#font[12]{c}] - template", 20, 0, 200);

	corrected_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 1, -10, 6);
	corrected_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template", 1, -10, 6);
}


void corrected_plotsCompare_49(){
	corrected_comparestack("SelectedJets_N_", "N^{jets}", 1, -999, -999);
}


void corrected_plotsCompare_50(){
	corrected_comparestack("SelectedJets_Pt_1_", "p_{T}^{jet_{1}} [GeV/#font[12]{c}]", 4, 0, 2000);
	corrected_comparestack("SelectedJets_E_1_", "E^{jet_{1}}[GeV]", 4, 0, 3000);
	corrected_comparestack("SelectedJets_Eta_1_", "#eta^{jet_{1}}", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_1_", "#varphi^{jet_{1}}", 20, -999, -999);
}


void corrected_plotsCompare_51(){
	corrected_comparestack("SelectedJets_HT_", "H_{T} [GeV/#font[12]{c}]", 4, 0, 3000);
}


void corrected_plotsCompare_52(){
	corrected_comparestack("DeltaR_photon1_jet_{1}_N0_", "#Delta R^{{{#gamma}_1}-{{jet}_1}} #geq 1", 20, 0, 6);
	corrected_comparestack("DeltaEta_photon1_jet_{1}_N0_","#Delta #eta^{{{#gamma}_1}-{{jet}_1}} - N^{jets} #geq 1", 10, 0, 5);
	corrected_comparestack("DeltaPhi_photon1_jet_{1}_N0_","#Delta #varphi^{{{#gamma}_1}-{{jet}_1}} - N^{jets} #geq 1", 10, 0, 3.1416);
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
	corrected_comparestack("SelectedPhotons_Pt_excl1_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - N^{jets} = 1", 4, 0, 2000);
	corrected_comparestack("SelectedPhotons_E_excl1_1_", "E^{#gamma_{1}} [GeV] - N^{jets} = 1", 4, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){	
		corrected_comparestack("SelectedPhotons_Eta_excl1_1_", "#eta^{#gamma_{1}} - N^{jets} = 1", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		corrected_comparestack("SelectedPhotons_Eta_excl1_1_", "#eta^{#gamma_{1}} - N^{jets} = 1", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_Phi_excl1_1_", "#varphi^{#gamma_{1}} - N^{jets} = 1", 20, -999, -999);
}


void corrected_plotsCompare_55(){
	corrected_comparestack("SelectedJets_Pt_excl1_1_", "p_{T}^{jet_{1}} [GeV/#font[12]{c}] - N^{jets} = 1", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_excl1_1_", "E^{jet_{1}} [GeV] - N^{jets} = 1", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_excl1_1_", "#eta^{jet_{1}} - N^{jets} = 1", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_excl1_1_", "#varphi^{jet_{1}} - N^{jets} = 1", 20, -999, -999);
}


void corrected_plotsCompare_56(){
	corrected_comparestack("SelectedPhotons_Pt_excl2_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - N^{jets} = 2", 4, 0, 2000);
	corrected_comparestack("SelectedPhotons_E_excl2_1_", "E^{#gamma_{1}} [GeV] - N^{jets} = 2", 4, 0, 2000);
	
	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){
	corrected_comparestack("SelectedPhotons_Eta_excl2_1_", "#eta^{#gamma_{1}} - N^{jets} = 2", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 	
		corrected_comparestack("SelectedPhotons_Eta_excl2_1_", "#eta^{#gamma_{1}} - N^{jets} = 2", 30, -3, 3); // endcaps or total
	}
	
	corrected_comparestack("SelectedPhotons_Phi_excl2_1_", "#varphi^{#gamma_{1}} - N^{jets} = 2", 20, -999, -999);
}


void corrected_plotsCompare_57(){
	corrected_comparestack("SelectedJets_Pt_excl2_1_", "p_{T}^{jet_{1}} [GeV/#font[12]{c}] - N^{jets} = 2", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_excl2_1_", "E^{jet_{1}} [GeV] - N^{jets} = 2", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_excl2_1_", "#eta^{jet_{1}} - N^{jets} = 2", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_excl2_1_", "#varphi^{jet_{1}} - N^{jets} = 2", 20, -999, -999);
}


void corrected_plotsCompare_58(){
	corrected_comparestack("SelectedJets_Pt_excl2_2_", "p_{T}^{jet_{2}} [GeV/#font[12]{c}] - N^{jets} = 2", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_excl2_2_", "E^{jet_{2}} [GeV] - N^{jets} = 2", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_excl2_2_", "#eta^{jet_{2}} - N^{jets} = 2", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_excl2_2_", "#varphi^{jet_{2}} - N^{jets} = 2", 20, -999, -999);
	corrected_comparestack("SelectedJets_HT_excl2_", "Selected Jets H_{T} - N^{jets} = 2", 4, 0, 3000);	
}


void corrected_plotsCompare_59(){
	corrected_comparestack("SelectedJets_Pt_2_", "p_{T}^{jet_{2}} [GeV/#font[12]{c}]", 4, 0, 1500);
	corrected_comparestack("SelectedJets_E_2_", "E^{jet_{2}} [GeV]", 4, 0, 2500);
	corrected_comparestack("SelectedJets_Eta_2_", "#eta^{jet_{2}}", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_2_", "#varphi^{jet_{2}}", 20, -999, -999);
}

void corrected_plotsCompare_60(){
	corrected_comparestack("DeltaPhi_photon1_jet_{1}_N1_","#Delta #varphi^{{{#gamma}_1}-{{jet}_1}} - N^{jets} #geq 2", 10, 0, 3.1416);
	corrected_comparestack("DeltaR_photon1_jet_{2}_N1_", "#Delta R^{{{#gamma}_1}-{{jet}_2}} - N^{jets} #geq 2", 20, 0, 6);
	corrected_comparestack("DeltaR_jet_{1}_jet_{2}_N1_","#Delta R^{{{jet}_1}}-{{jet}_2}} - N^{jets} #geq 2", 20, 0, 6);
	corrected_comparestack("DeltaEta_jet_{1}_jet_{2}_N1_","#Delta #eta^{{{jet}_1}}-{{jet}_2}} - N^{jets} #geq 2", 10, 0, 5);
	corrected_comparestack("DeltaPhi_jet_{1}_jet_{2}_N1_","#Delta #varphi^{{{jet}_1}}-{{jet}_2}} - N^{jets} #geq 2", 10, 0, 3.1416);
}


void corrected_plotsCompare_61(){
	corrected_comparestack("SelectedJets_Pt_3_", "p_{T}^{jet_{3}} [GeV/#font[12]{c}]", 4, 0, 1000);
	corrected_comparestack("SelectedJets_E_3_", "E^{jet_{3}} [GeV]", 4, 0, 2000);
	corrected_comparestack("SelectedJets_Eta_3_", "#eta^{jet_{3}}", 50, -3, 3);
	corrected_comparestack("SelectedJets_Phi_3_", "#varphi^{jet_{3}}", 20, -999, -999);
}


void corrected_plotsCompare_62(){
	corrected_comparestack("DeltaPhi_photon1_jet_{1}_N2_","#Delta #varphi^{{{#gamma}_1}-{{jet}_1}} - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_photon1_jet_{2}_N2_","#Delta #varphi^{{{#gamma}_1}-{{jet}_2}} - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_photon1_jet_{3}_N2_","#Delta #varphi^{{{#gamma}_1}-{{jet}_3}} - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaR_photon1_jet_{3}_N2_"  ,"#Delta R^{{{#gamma}_1}-{{jet}_3}} - N^{jets} #geq 3", 20, 0, 6);
	corrected_comparestack("DeltaPhi_jet_{1}_jet_{2}_N2_","#Delta #varphi^{{{jet}_1}}-{{jet}_2}} - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_jet_{1}_jet_{3}_N2_","#Delta #varphi^{{{jet}_1}}-{{jet}_3}} - N^{jets} #geq 3", 10, 0, 3.1416);
	corrected_comparestack("DeltaPhi_jet_{2}_jet_{3}_N2_","#Delta #varphi^{{{jet}_2}}-{{jet}_3}} - N^{jets} #geq 3", 10, 0, 3.1416);
}


void corrected_plotsCompare_PrePostCuts_01(){
	corrected_comparestack("gamma_Pt_1_precut1_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre cut 1", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut1_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - post cut 1", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut2_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - post cut 2", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preTriMatch_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre Trigger Matching cut", 1, -999, -999);
}


void corrected_plotsCompare_PrePostCuts_02(){
	corrected_comparestack("gamma_Pt_1_prePassConversionVeto_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre PassConversionVeto cut", 1, -999, -999);
	corrected_comparestack("gamma_PassConversionVeto_1_prePassConversionVeto_","Conversion Veto^{#gamma_{1}} pre PassConversionVeto cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_prehadronicOverEm2012_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre hadronicOverEm2012 cut", 1, -999, -999);
	corrected_comparestack("gamma_hadronicOverEm2012_1_prehadronicOverEm2012_","photon ID: H/E_{2012}^{#gamma_{1}} pre hadronicOverEm2012 cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_presigmaietaieta_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre sigmaietaieta cut", 1, -999, -999);
	corrected_comparestack("gamma_sigmaietaieta_1_presigmaietaieta_","photon ID: #sigma_{i#etai#eta}^{#gamma_{1}} pre sigmaietaieta cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preiso_CH_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre iso_CH cut", 1, -999, -999);
	corrected_comparestack("gamma_iso_CH_1_preiso_CH_","Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}]- pre iso_CH cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preiso_NH_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre iso_NH cut", 1, -999, -999);
	corrected_comparestack("gamma_iso_NH_1_preiso_NH_","Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}] - pre iso_NH cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_preiso_Ph_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre iso_Ph cut", 1, -999, -999);
	corrected_comparestack("gamma_iso_Ph_1_preiso_Ph_","Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}] - pre iso_Ph cut", 1, -999, -999);
}


void corrected_plotsCompare_PrePostCuts_03(){
	corrected_comparestack("gamma_Pt_1_preAcc_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre Acc cut", 1, -999, -999);
	corrected_comparestack("gamma_Eta_1_preAcc_","#eta^{#gamma_{1}} - pre Acc cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut3_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - post cut 3", 1, -999, -999);
	corrected_comparestack("jets_deltaR_1_predeltaR_","#Delta R^{{{#gamma}_1}-{{jet}_1}} - N^{jets} #geq 1 - pre #DeltaR cut", 1, -999, -999);
	corrected_comparestack("jets_Pt_1_preAcc_","p_{T}^{jet_{1}} [GeV/#font[12]{c}]- pre Acc cut", 1, -999, -999);
	corrected_comparestack("jets_Eta_1_preAcc_","#eta^{jet_{1}} - pre Acc cut", 1, -999, -999);
	corrected_comparestack("gamma_Pt_1_postcut4_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]- post cut 4", 1, -999, -999);
	corrected_comparestack("jets_HT_preHT_","H_{T} [GeV/#font[12]{c}] - pre H_{T} cut", 1, -999, -999);
}


// ==================================== collectives functions

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
