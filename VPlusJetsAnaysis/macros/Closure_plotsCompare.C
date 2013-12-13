#define Closure_plotsCompare_cxx
#include "Closure_comparestack.C"
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

void Closure_plotsCompare_01(){

	Closure_comparestack("IDIsoPhotons_N_", "ID-Iso N^{#gamma}", 1, -999, -999);
	Closure_comparestack("SelectedPhotons_N_", "N^{#gamma}", 1, -999, -999);

	Closure_comparestack("Nvtx_", "N^{vtx} ", 1, -999, -999);
		
	Closure_comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 4, 0, 2000);
	Closure_comparestack("SelectedPhotons_Pt_LogBin_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, -999, -999);

	Closure_comparestack("SelectedPhotons_E_1_", "E^{#gamma_{1}} [GeV]", 4, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){ 
		Closure_comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma_{1}}", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		Closure_comparestack("SelectedPhotons_Eta_1_", "#eta^{#gamma_{1}}", 30, -3, 3); // endcaps or total
	}
	
	Closure_comparestack("SelectedPhotons_Phi_1_", "#varphi^{#gamma_{1}}", 20, -999, -999);
	Closure_comparestack("SelectedPhotons_Bit_1_", "bit^{#gamma_{1}}", 1, -999, -999);

	Closure_comparestack("SelectedPhotons_TriMatchF4Path_AND_pTrange_1_","Trigger Matching: Path^{#gamma_{1}} && p_T^{#gamma_{1}}", 1, -999, -999);
	Closure_comparestack("SelectedPhotons_Tri_PF_1_","Trigger PF^{#gamma_{1}}", 1, -999, -999);
	Closure_comparestack("SelectedPhotons_TeP_SF_1_","SF^{#gamma_{1}}", 1, -999, -999);
	Closure_comparestack("SelectedPhotons_BackDataDriven_F_1_","Background data-driven F^{#gamma_{1}}", 1, -999, -999);	
}


void Closure_plotsCompare_02(){
	Closure_comparestack("SelectedPhotons_PassConversionVeto_1_","Conversion Veto", 1, -999, -999);
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}]", 1, 0, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_", "Iso [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_03(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}]", 1, 0, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}]", 1, -2, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 4, -10, 20);
}


void Closure_plotsCompare_04(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin01_","#sigma_{i#etai#eta}^{#gamma_{1}}, 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 2, 0, 0.012); 
	}
	else {
	Closure_comparestack("SelectedPhotons_id_sieie_1_bin01_","#sigma_{i#etai#eta}^{#gamma_{1}}, 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin01_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, 0, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin01_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin01_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin01_", "Iso [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_05(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, 0, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin01_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, -2, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 100 < p_{T}^{#gamma_{1}} < 111 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_06(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin02_","#sigma_{i#etai#eta}^{#gamma_{1}}, 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin02_","#sigma_{i#etai#eta}^{#gamma_{1}}, 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin02_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 1, 0, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin02_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin02_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin02_", "Iso [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_07(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 1, 0, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin02_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 1, -2, 2);
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 111 < p_{T}^{#gamma_{1}} < 123.1", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 111 < p_{T}^{#gamma_{1}} < 123.1", 1, -10, 10);
}


void Closure_plotsCompare_08(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin03_","#sigma_{i#etai#eta}^{#gamma_{1}}, 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin03_","#sigma_{i#etai#eta}^{#gamma_{1}}, 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin03_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin03_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin03_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin03_", "Iso [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_09(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin03_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 123.1 < p_{T}^{#gamma_{1}} < 136.6", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 123.1 < p_{T}^{#gamma_{1}} < 136.6", 1, -10, 10);
}


void Closure_plotsCompare_10(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin04_","#sigma_{i#etai#eta}^{#gamma_{1}}, 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin04_","#sigma_{i#etai#eta}^{#gamma_{1}}, 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin04_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin04_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin04_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin04_", "Iso [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_11(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin04_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 136.6 < p_{T}^{#gamma_{1}} < 151.6", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 136.6 < p_{T}^{#gamma_{1}} < 151.6", 1, -10, 10);
}


void Closure_plotsCompare_12(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin05_","#sigma_{i#etai#eta}^{#gamma_{1}}, 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin05_","#sigma_{i#etai#eta}^{#gamma_{1}}, 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin05_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin05_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin05_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin05_", "Iso [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_13(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin05_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 168.2", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 151.6 < p_{T}^{#gamma_{1}} < 168.2", 1, -10, 10);
}


void Closure_plotsCompare_14(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin06_","#sigma_{i#etai#eta}^{#gamma_{1}}, 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin06_","#sigma_{i#etai#eta}^{#gamma_{1}}, 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin06_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin06_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin06_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin06_", "Iso [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_15(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin06_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 168.2 < p_{T}^{#gamma_{1}} < 186.6", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 168.2 < p_{T}^{#gamma_{1}} < 186.6", 1, -10, 10);
}


void Closure_plotsCompare_16(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin07_","#sigma_{i#etai#eta}^{#gamma_{1}}, 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin07_","#sigma_{i#etai#eta}^{#gamma_{1}}, 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin07_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin07_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin07_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin07_", "Iso [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_17(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin07_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 186.6 < p_{T}^{#gamma_{1}} < 207.1", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 186.6 < p_{T}^{#gamma_{1}} < 207.1", 1, -10, 10);
}


void Closure_plotsCompare_18(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin08_","#sigma_{i#etai#eta}^{#gamma_{1}}, 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin08_","#sigma_{i#etai#eta}^{#gamma_{1}}, 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin08_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin08_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin08_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin08_", "Iso [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_19(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin08_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 207.1 < p_{T}^{#gamma_{1}} < 229.7 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_20(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin09_","#sigma_{i#etai#eta}^{#gamma_{1}}, 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin09_","#sigma_{i#etai#eta}^{#gamma_{1}}, 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin09_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin09_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin09_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin09_", "Iso [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_21(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin09_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 229.7 < p_{T}^{#gamma_{1}} < 254.9 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_22(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin10_","#sigma_{i#etai#eta}^{#gamma_{1}}, 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin10_","#sigma_{i#etai#eta}^{#gamma_{1}}, 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin10_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin10_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin10_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin10_", "Iso [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_23(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin10_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 254.9 < p_{T}^{#gamma_{1}} < 282.8 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_24(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin11_","#sigma_{i#etai#eta}^{#gamma_{1}}, 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin11_","#sigma_{i#etai#eta}^{#gamma_{1}}, 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin11_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin11_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin11_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin11_", "Iso [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_25(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin11_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 282.8 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_26(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin12_","#sigma_{i#etai#eta}^{#gamma_{1}}, 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin12_","#sigma_{i#etai#eta}^{#gamma_{1}}, 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin12_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin12_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin12_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin12_", "Iso [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_27(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin12_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin12_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 313.8 < p_{T}^{#gamma_{1}} < 348.2 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_28(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin13_","#sigma_{i#etai#eta}^{#gamma_{1}}, 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin13_","#sigma_{i#etai#eta}^{#gamma_{1}}, 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin13_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin13_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin13_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin13_", "Iso [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_29(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin13_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin13_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 348.2 < p_{T}^{#gamma_{1}} < 386.4 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_30(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin14_","#sigma_{i#etai#eta}^{#gamma_{1}}, 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin14_","#sigma_{i#etai#eta}^{#gamma_{1}}, 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin14_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin14_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin14_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin14_", "Iso [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_31(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin14_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin14_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 386.4 < p_{T}^{#gamma_{1}} < 428.7 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_32(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin15_","#sigma_{i#etai#eta}^{#gamma_{1}}, 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin15_","#sigma_{i#etai#eta}^{#gamma_{1}}, 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin15_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin15_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin15_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin15_", "Iso [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_33(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin15_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin15_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 428.7 < p_{T}^{#gamma_{1}} < 475.7 [GeV/#font[12]{c}]", 1, -10, 10);
}




void Closure_plotsCompare_34(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin16_","#sigma_{i#etai#eta}^{#gamma_{1}}, 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin16_","#sigma_{i#etai#eta}^{#gamma_{1}}, 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin16_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin16_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin16_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin16_", "Iso [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_35(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin16_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin16_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 475.7 < p_{T}^{#gamma_{1}} < 527.8 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_36(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin17_","#sigma_{i#etai#eta}^{#gamma_{1}}, 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin17_","#sigma_{i#etai#eta}^{#gamma_{1}}, 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin17_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin17_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin17_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin17_", "Iso [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_37(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin17_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin17_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 527.8 < p_{T}^{#gamma_{1}} < 585.6 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_38(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin18_","#sigma_{i#etai#eta}^{#gamma_{1}}, 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin18_","#sigma_{i#etai#eta}^{#gamma_{1}}, 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin18_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin18_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin18_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin18_", "Iso [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_39(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin18_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin18_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 585.6 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_40(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin19_","#sigma_{i#etai#eta}^{#gamma_{1}}, 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin19_","#sigma_{i#etai#eta}^{#gamma_{1}}, 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin19_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin19_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin19_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin19_", "Iso [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_41(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin19_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin19_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 649.8 < p_{T}^{#gamma_{1}} < 721 [GeV/#font[12]{c}]", 1, -10, 10);
}



void Closure_plotsCompare_42(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin20_","#sigma_{i#etai#eta}^{#gamma_{1}}, 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin20_","#sigma_{i#etai#eta}^{#gamma_{1}}, 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin20_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin20_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin20_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin20_", "Iso [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_43(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin20_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin20_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 721 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 10);
}

void Closure_plotsCompare_44(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin21_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin21_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin21_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin21_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin21_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin21_", "Iso [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_45(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin21_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin21_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin21_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin21_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin21_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin21_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin21_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin21_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin21_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin21_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, p_{T}^{#gamma_{1}} > 800 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_46(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin22_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin22_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin22_big_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin22_big_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin22_big_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin22_big_", "Iso [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_47(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin22_big_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin22_big_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin22_big_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin22_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin22_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin22_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin22_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin22_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin22_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin22_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 100 < p_{T}^{#gamma_{1}} < 151.6 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_48(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin23_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin23_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin23_big_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin23_big_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin23_big_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin23_big_", "Iso [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_49(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin23_big_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin23_big_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin23_big_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin23_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin23_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin23_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin23_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin23_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin23_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin23_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 151.6 < p_{T}^{#gamma_{1}} < 201.7 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_50(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin24_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin24_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin24_big_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin24_big_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin24_big_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin24_big_", "Iso [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_51(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin24_big_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin24_big_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin24_big_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin24_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin24_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin24_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin24_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin24_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin24_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin24_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 207.1 < p_{T}^{#gamma_{1}} < 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_52(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin25_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin25_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin25_big_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin25_big_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin25_big_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin25_big_", "Iso [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_53(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin25_big_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin25_big_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin25_big_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin25_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin25_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin25_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin25_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin25_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin25_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin25_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 313.8 < p_{T}^{#gamma_{1}} < 649.8 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_54(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin26_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin26_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin26_big_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin26_big_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin26_big_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin26_big_", "Iso [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_55(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin26_big_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin26_big_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin26_big_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin26_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin26_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin26_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin26_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin26_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin26_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin26_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, 649.8 < p_{T}^{#gamma_{1}} < 800 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_56(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin27_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_bin27_big_","#sigma_{i#etai#eta}^{#gamma_{1}}, p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_1_bin27_big_", "Iso^{#gamma_{1}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_1_bin27_big_", "Iso^{#gamma_{1}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_1_bin27_big_", "Iso^{#gamma_{1}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_1_bin27_big_", "Iso [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
}


void Closure_plotsCompare_57(){
	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin27_big_", "Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin27_big_", "Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin27_big_", "Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, 0, 6);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_1_bin27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{ChHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, -2, 2); 
	Closure_comparestack("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{NeHad} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, -10, 20);
	Closure_comparestack("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 4, -10, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}], p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template, p_{T}^{#gamma_{1}} > 313.8 [GeV/#font[12]{c}]", 1, -10, 10);
}


void Closure_plotsCompare_58(){		
	Closure_comparestack("SelectedPhotons_PfIsoPhotons03ForCic_1_", "PfIsoPhotons03ForCic^{#gamma_{1}}", 8, 0, 80);
	Closure_comparestack("SelectedPhotons_PfIsoNeutrals03ForCic_1_", "PfIsoNeutrals03ForCic^{#gamma_{1}}", 4, 0, 40);
	Closure_comparestack("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "PfIsoCharged03ForCicVtx0^{#gamma_{1}}", 8, 0, 80);
	Closure_comparestack("SelectedPhotons_PfIsoCharged03BadForCic_1_", "PfIsoCharged03BadForCic^{#gamma_{1}}", 20, 0, 200);
}


void Closure_plotsCompare_59(){		
	Closure_comparestack("SelectedPhotons_PfIsoPhotons04ForCic_1_", "PfIsoPhotons04ForCic^{#gamma_{1}}", 8, 0, 80);
	Closure_comparestack("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "PfIsoNeutrals04ForCic^{#gamma_{1}}", 40, 0, 200);
	Closure_comparestack("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "PfIsoCharged04ForCicVtx0^{#gamma_{1}}", 20, 0, 200);
	Closure_comparestack("SelectedPhotons_PfIsoCharged04BadForCic_1_", "PfIsoCharged04BadForCic^{#gamma_{1}}", 20, 0, 200);
}


void Closure_plotsCompare_60(){

	bool inv_S = false;
	inv_S = inv_sigmaietaieta(inv_S);
	if (!inv_S){
		Closure_comparestack("SelectedPhotons_id_sieie_1_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 2, 0, 0.012);
	}
	else {
		Closure_comparestack("SelectedPhotons_id_sieie_1_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 2, 0.010, 0.025); // inverted
	}
	
	Closure_comparestack("SelectedPhotons_id_sieip_1_", "#sigma_{i#etai#varphi}^{#gamma_{1}}", 2, 0, 0.014);
	Closure_comparestack("SelectedPhotons_id_etawidth_1_", "#Delta#eta^{#gamma_{1}}", 4, 0, 0.02);
	Closure_comparestack("SelectedPhotons_id_phiwidth_1_", "#Delta#varphi^{#gamma_{1}}", 2, 0, 0.15);
	Closure_comparestack("SelectedPhotons_id_r9_1_", "r_{9}^{#gamma_{1}}", 1, 0, 1.1);
	Closure_comparestack("SelectedPhotons_id_lambdaRatio_1_", "#lambda Ratio^{#gamma_{1}}", 1, 0, 1.1);
	Closure_comparestack("SelectedPhotons_id_s4Ratio_1_", "s4 Ratio^{#gamma_{1}}", 1, 0, 1.1);
	Closure_comparestack("SelectedPhotons_id_e25_1_", "#rho_{25}^{#gamma_{1}}", 2, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){ 
		Closure_comparestack("SelectedPhotons_id_sceta_1_", "#eta_{SC}^{#gamma_{1}}", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		Closure_comparestack("SelectedPhotons_id_sceta_1_", "#eta_{SC}^{#gamma_{1}}", 30, -3, 3); // endcaps or total
	}
	
	Closure_comparestack("SelectedPhotons_id_ESEffSigmaRR_1_", "ESEffSigmaRR^{#gamma_{1}}", 1, -999, -999);
	Closure_comparestack("SelectedPhotons_id_hadronicOverEm_1_", "H/E^{#gamma_{1}} ", 20, 0, 0.2);
	Closure_comparestack("SelectedPhotons_id_hadronicOverEm2012_1_", "H/E_{2012}^{#gamma_{1}}", 10, 0, 0.06);
}


void Closure_plotsCompare_61(){
	Closure_comparestack("SelectedPhotons_hcalTowerSumEtConeDR04_1_", "hcalTowerSumEtConeDR04^{#gamma_{1}}", 2, 0, 200);
	Closure_comparestack("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "ecalRecHitSumEtConeDR04^{#gamma_{1}}", 2, 0, 200);
	Closure_comparestack("SelectedPhotons_nTrkSolidConeDR04_1_", "nTrkSolidConeDR04^{#gamma_{1}}", 1, 0, 20);
	Closure_comparestack("SelectedPhotons_trkSumPtSolidConeDR04_1_", "trkSumPtSolidConeDR04^{#gamma_{1}}", 4, 0, 200);
	Closure_comparestack("SelectedPhotons_nTrkHollowConeDR04_1_", "nTrkHollowConeDR04^{#gamma_{1}}", 1, 0, 20);
	Closure_comparestack("SelectedPhotons_trkSumPtHollowConeDR04_1_", "trkSumPtHollowConeDR04^{#gamma_{1}}", 4, 0, 200);
}	


void Closure_plotsCompare_62(){	
	Closure_comparestack("SelectedPhotons_IsoFPRCharged_1_", "Iso^{#gamma_{1}}_{ChHad-FPR} [GeV/#font[12]{c}]", 20, 0, 200);
	Closure_comparestack("SelectedPhotons_IsoFPRNeutral_1_", "Iso^{#gamma_{1}}_{NeHad-FPR} [GeV/#font[12]{c}]", 20, 0, 200);
	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_1_", "Iso^{#gamma_{1}}_{Pho-FPR} [GeV/#font[12]{c}]", 20, 0, 200);
	Closure_comparestack("SelectedPhotons_IsoFPR_1_", "Iso^{#gamma_{1}}_{FPR} [GeV/#font[12]{c}]", 4, 0, 20);

	Closure_comparestack("SelectedPhotons_IsoFPRRandomConeCharged_1_", "Iso^{#gamma_{1}}_{ChHad-FPR} [GeV/#font[12]{c}] - template", 20, 0, 200); 
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConeNeutral_1_", "Iso^{#gamma_{1}}_{NeHad-FPR} [GeV/#font[12]{c}] - template", 20, 0, 200);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_1_", "Iso^{#gamma_{1}}_{Pho-FPR} [GeV/#font[12]{c}] - template", 20, 0, 200);

	Closure_comparestack("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 1, -10, 10);
	Closure_comparestack("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}] - template", 1, -10, 10);
}


void Closure_plotsCompare_63(){
	Closure_comparestack("SelectedJets_N_", "N^{jets}", 1, -999, -999);
}


void Closure_plotsCompare_64(){
	Closure_comparestack("SelectedJets_Pt_1_", "p_{T}^{jet_{1}} [GeV/#font[12]{c}]", 4, 0, 2000);
	Closure_comparestack("SelectedJets_E_1_", "E^{jet_{1}}[GeV]", 4, 0, 3000);
	Closure_comparestack("SelectedJets_Eta_1_", "#eta^{jet_{1}}", 50, -3, 3);
	Closure_comparestack("SelectedJets_Phi_1_", "#varphi^{jet_{1}}", 20, -999, -999);
}


void Closure_plotsCompare_65(){
	Closure_comparestack("SelectedJets_HT_", "H_{T} [GeV/#font[12]{c}]", 4, 0, 3000);
}


void Closure_plotsCompare_66(){
	Closure_comparestack("DeltaR_photon1_jet1_N0_", "#Delta R^{#gamma_{1}-jet_{1}} #geq 1", 20, 0, 6);
	Closure_comparestack("DeltaEta_photon1_jet1_N0_","#Delta #eta^{#gamma_{1}-jet_{1}} - N^{jets} #geq 1", 10, 0, 5);
	Closure_comparestack("DeltaPhi_photon1_jet1_N0_","#Delta #varphi^{#gamma_{1}-jet_{1}} - N^{jets} #geq 1", 10, 0, 3.1416);
}


void Closure_plotsCompare_67(){
	Closure_comparestack("thrust_N0_","#tau_{T} - N^{jets} #geq 1", 2, 0, 0.35);
	Closure_comparestack("broad_N0_","broad - N^{jets} #geq 1", 2, 0, 1);
	Closure_comparestack("S3_N0_","S3 - N^{jets} #geq 1", 1, -1, 5);
	Closure_comparestack("S4_N0_","S4 - N^{jets} #geq 1", 1, -0.2, 0.2);

	Closure_comparestack("ln_thrust_N0_","ln #tau_{T} - N^{jets} #geq 1", 3, -30, 0);
	Closure_comparestack("ln_broad_N0_","ln broad - N^{jets} #geq 1", 1, -3, 1);
	Closure_comparestack("ln_S3_N0_","ln S3 - N^{jets} #geq 1", 2, -4, 3);
	Closure_comparestack("ln_S4_N0_","ln S4 - N^{jets} #geq 1", 1, -999, 999);		
}


void Closure_plotsCompare_68(){
	Closure_comparestack("SelectedPhotons_Pt_excl1_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - N^{jets} = 1", 4, 0, 2000);
	Closure_comparestack("SelectedPhotons_E_excl1_1_", "E^{#gamma_{1}} [GeV] - N^{jets} = 1", 4, 0, 2000);

	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){	
		Closure_comparestack("SelectedPhotons_Eta_excl1_1_", "#eta^{#gamma_{1}} - N^{jets} = 1", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 
		Closure_comparestack("SelectedPhotons_Eta_excl1_1_", "#eta^{#gamma_{1}} - N^{jets} = 1", 30, -3, 3); // endcaps or total
	}
	
	Closure_comparestack("SelectedPhotons_Phi_excl1_1_", "#varphi^{#gamma_{1}} - N^{jets} = 1", 20, -999, -999);
}


void Closure_plotsCompare_69(){
	Closure_comparestack("SelectedJets_Pt_excl1_1_", "p_{T}^{jet_{1}} [GeV/#font[12]{c}] - N^{jets} = 1", 4, 0, 1500);
	Closure_comparestack("SelectedJets_E_excl1_1_", "E^{jet_{1}} [GeV] - N^{jets} = 1", 4, 0, 2500);
	Closure_comparestack("SelectedJets_Eta_excl1_1_", "#eta^{jet_{1}} - N^{jets} = 1", 50, -3, 3);
	Closure_comparestack("SelectedJets_Phi_excl1_1_", "#varphi^{jet_{1}} - N^{jets} = 1", 20, -999, -999);
}


void Closure_plotsCompare_70(){
	Closure_comparestack("SelectedPhotons_Pt_excl2_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - N^{jets} = 2", 4, 0, 2000);
	Closure_comparestack("SelectedPhotons_E_excl2_1_", "E^{#gamma_{1}} [GeV] - N^{jets} = 2", 4, 0, 2000);
	
	string geom;
	geom = geo_string(geom);
	if (geom == "barrel"){
	Closure_comparestack("SelectedPhotons_Eta_excl2_1_", "#eta^{#gamma_{1}} - N^{jets} = 2", 30, -1.5, 1.5); // barrel
	}
	if (geom == "endcaps" || geom == "total"){ 	
		Closure_comparestack("SelectedPhotons_Eta_excl2_1_", "#eta^{#gamma_{1}} - N^{jets} = 2", 30, -3, 3); // endcaps or total
	}
	
	Closure_comparestack("SelectedPhotons_Phi_excl2_1_", "#varphi^{#gamma_{1}} - N^{jets} = 2", 20, -999, -999);
}


void Closure_plotsCompare_71(){
	Closure_comparestack("SelectedJets_Pt_excl2_1_", "p_{T}^{jet_{1}} [GeV/#font[12]{c}] - N^{jets} = 2", 4, 0, 1500);
	Closure_comparestack("SelectedJets_E_excl2_1_", "E^{jet_{1}} [GeV] - N^{jets} = 2", 4, 0, 2500);
	Closure_comparestack("SelectedJets_Eta_excl2_1_", "#eta^{jet_{1}} - N^{jets} = 2", 50, -3, 3);
	Closure_comparestack("SelectedJets_Phi_excl2_1_", "#varphi^{jet_{1}} - N^{jets} = 2", 20, -999, -999);
}


void Closure_plotsCompare_72(){
	Closure_comparestack("SelectedJets_Pt_excl2_2_", "p_{T}^{jet_{2}} [GeV/#font[12]{c}] - N^{jets} = 2", 4, 0, 1500);
	Closure_comparestack("SelectedJets_E_excl2_2_", "E^{jet_{2}} [GeV] - N^{jets} = 2", 4, 0, 2500);
	Closure_comparestack("SelectedJets_Eta_excl2_2_", "#eta^{jet_{2}} - N^{jets} = 2", 50, -3, 3);
	Closure_comparestack("SelectedJets_Phi_excl2_2_", "#varphi^{jet_{2}} - N^{jets} = 2", 20, -999, -999);
	Closure_comparestack("SelectedJets_HT_excl2_", "Selected Jets H_{T} - N^{jets} = 2", 4, 0, 3000);	
}


void Closure_plotsCompare_73(){
	Closure_comparestack("SelectedJets_Pt_2_", "p_{T}^{jet_{2}} [GeV/#font[12]{c}]", 4, 0, 1500);
	Closure_comparestack("SelectedJets_E_2_", "E^{jet_{2}} [GeV]", 4, 0, 2500);
	Closure_comparestack("SelectedJets_Eta_2_", "#eta^{jet_{2}}", 50, -3, 3);
	Closure_comparestack("SelectedJets_Phi_2_", "#varphi^{jet_{2}}", 20, -999, -999);
}

void Closure_plotsCompare_74(){
	Closure_comparestack("DeltaPhi_photon1_jet1_N1_","#Delta #varphi^{#gamma_{1}-jet_{1}} - N^{jets} #geq 2", 10, 0, 3.1416);
	Closure_comparestack("DeltaR_photon1_jet2_N1_", "#Delta R^{#gamma_{1}-jet_{2}} - N^{jets} #geq 2", 20, 0, 6);
	Closure_comparestack("DeltaR_jet1_jet2_N1_","#Delta R^{jet_{1}-jet_{2}} - N^{jets} #geq 2", 20, 0, 6);
	Closure_comparestack("DeltaEta_jet1_jet2_N1_","#Delta #eta^{jet_{1}-jet_{2}} - N^{jets} #geq 2", 10, 0, 5);
	Closure_comparestack("DeltaPhi_jet1_jet2_N1_","#Delta #varphi^{jet_{1}-jet_{2}} - N^{jets} #geq 2", 10, 0, 3.1416);
}


void Closure_plotsCompare_75(){
	Closure_comparestack("SelectedJets_Pt_3_", "p_{T}^{jet_{3}} [GeV/#font[12]{c}]", 4, 0, 1000);
	Closure_comparestack("SelectedJets_E_3_", "E^{jet_{3}} [GeV]", 4, 0, 2000);
	Closure_comparestack("SelectedJets_Eta_3_", "#eta^{jet_{3}}", 50, -3, 3);
	Closure_comparestack("SelectedJets_Phi_3_", "#varphi^{jet_{3}}", 20, -999, -999);
}


void Closure_plotsCompare_76(){
	Closure_comparestack("DeltaPhi_photon1_jet1_N2_","#Delta #varphi^{#gamma_{1}-jet_{1}} - N^{jets} #geq 3", 10, 0, 3.1416);
	Closure_comparestack("DeltaPhi_photon1_jet2_N2_","#Delta #varphi^{#gamma_{1}-jet_{2}} - N^{jets} #geq 3", 10, 0, 3.1416);
	Closure_comparestack("DeltaPhi_photon1_jet3_N2_","#Delta #varphi^{#gamma_{1}-jet_{3}} - N^{jets} #geq 3", 10, 0, 3.1416);
	Closure_comparestack("DeltaR_photon1_jet3_N2_"  ,"#Delta R^{#gamma_{1}-jet_{3}} - N^{jets} #geq 3", 20, 0, 6);
	Closure_comparestack("DeltaPhi_jet1_jet2_N2_","#Delta #varphi^{jet_{1}-jet_{2}} - N^{jets} #geq 3", 10, 0, 3.1416);
	Closure_comparestack("DeltaPhi_jet1_jet3_N2_","#Delta #varphi^{jet_{1}-jet_{3}} - N^{jets} #geq 3", 10, 0, 3.1416);
	Closure_comparestack("DeltaPhi_jet2_jet3_N2_","#Delta #varphi^{jet_{2}-jet_{3}} - N^{jets} #geq 3", 10, 0, 3.1416);
}

void Closure_plotsCompare_PrePostCuts_01(){
	Closure_comparestack("gamma_Pt_1_precut1_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre cut 1", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_postcut1_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - post cut 1", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_postcut2_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - post cut 2", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_preTriMatch_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre Trigger Matching cut", 1, -999, -999);
}


void Closure_plotsCompare_PrePostCuts_02(){
	Closure_comparestack("gamma_Pt_1_prePassConversionVeto_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre PassConversionVeto cut", 1, -999, -999);
	Closure_comparestack("gamma_PassConversionVeto_1_prePassConversionVeto_","Conversion Veto^{#gamma_{1}} pre PassConversionVeto cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_prehadronicOverEm2012_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre hadronicOverEm2012 cut", 1, -999, -999);
	Closure_comparestack("gamma_hadronicOverEm2012_1_prehadronicOverEm2012_","photon ID: H/E_{2012}^{#gamma_{1}} pre hadronicOverEm2012 cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_presigmaietaieta_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre sigmaietaieta cut", 1, -999, -999);
	Closure_comparestack("gamma_sigmaietaieta_1_presigmaietaieta_","photon ID: #sigma_{i#etai#eta}^{#gamma_{1}} pre sigmaietaieta cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_preiso_CH_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre iso_CH cut", 1, -999, -999);
	Closure_comparestack("gamma_iso_CH_1_preiso_CH_","Iso^{#gamma_{1} #rho_{corr}}_{ChHad} [GeV/#font[12]{c}]- pre iso_CH cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_preiso_NH_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre iso_NH cut", 1, -999, -999);
	Closure_comparestack("gamma_iso_NH_1_preiso_NH_","Iso^{#gamma_{1} #rho_{corr}}_{NeHad} [GeV/#font[12]{c}] - pre iso_NH cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_preiso_Ph_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre iso_Ph cut", 1, -999, -999);
	Closure_comparestack("gamma_iso_Ph_1_preiso_Ph_","Iso^{#gamma_{1} #rho_{corr}}_{Pho} [GeV/#font[12]{c}] - pre iso_Ph cut", 1, -999, -999);
}


void Closure_plotsCompare_PrePostCuts_03(){
	Closure_comparestack("gamma_Pt_1_preAcc_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - pre Acc cut", 1, -999, -999);
	Closure_comparestack("gamma_Eta_1_preAcc_","#eta^{#gamma_{1}} - pre Acc cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_postcut3_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}] - post cut 3", 1, -999, -999);
	Closure_comparestack("jets_deltaR_1_predeltaR_","#Delta R^{#gamma_{1}-jet_{1}} - N^{jets} #geq 1 - pre #DeltaR cut", 1, -999, -999);
	Closure_comparestack("jets_Pt_1_preAcc_","p_{T}^{jet_{1}} [GeV/#font[12]{c}]- pre Acc cut", 1, -999, -999);
	Closure_comparestack("jets_Eta_1_preAcc_","#eta^{jet_{1}} - pre Acc cut", 1, -999, -999);
	Closure_comparestack("gamma_Pt_1_postcut4_","p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]- post cut 4", 1, -999, -999);
	Closure_comparestack("jets_HT_preHT_","H_{T} [GeV/#font[12]{c}] - pre H_{T} cut", 1, -999, -999);
}


// ==================================== collectives functions

void Closure_plotsCompare_TOT(){
	Closure_plotsCompare_01();
	Closure_plotsCompare_02();
	Closure_plotsCompare_03();
	Closure_plotsCompare_04();
	Closure_plotsCompare_05();
	Closure_plotsCompare_06();
	Closure_plotsCompare_07();
	Closure_plotsCompare_08();
	Closure_plotsCompare_09();
	Closure_plotsCompare_10();
	Closure_plotsCompare_11();
	Closure_plotsCompare_12();
	Closure_plotsCompare_13();
	Closure_plotsCompare_14();
	Closure_plotsCompare_15();
	Closure_plotsCompare_16();
	Closure_plotsCompare_17();
	Closure_plotsCompare_18();
	Closure_plotsCompare_19();
	Closure_plotsCompare_20();
	Closure_plotsCompare_21();
	Closure_plotsCompare_22();
	Closure_plotsCompare_23();
	Closure_plotsCompare_24();
	Closure_plotsCompare_25();
	Closure_plotsCompare_26();
	Closure_plotsCompare_27();
	Closure_plotsCompare_28();
	Closure_plotsCompare_29();				
	Closure_plotsCompare_30();				
	Closure_plotsCompare_31();
	Closure_plotsCompare_32();
	Closure_plotsCompare_33();
	Closure_plotsCompare_34();
	Closure_plotsCompare_34();
	Closure_plotsCompare_35();
	Closure_plotsCompare_36();
	Closure_plotsCompare_37();
	Closure_plotsCompare_38();
	Closure_plotsCompare_39();
	Closure_plotsCompare_40();
	Closure_plotsCompare_41();
	Closure_plotsCompare_42();
	Closure_plotsCompare_43();
	Closure_plotsCompare_44();
	Closure_plotsCompare_45();
	Closure_plotsCompare_46();
	Closure_plotsCompare_47();
	Closure_plotsCompare_48();
	Closure_plotsCompare_49();
	Closure_plotsCompare_50();
	Closure_plotsCompare_51();
	Closure_plotsCompare_52();
	Closure_plotsCompare_53();
	Closure_plotsCompare_54();
	Closure_plotsCompare_55();
	Closure_plotsCompare_56();
	Closure_plotsCompare_57();
	Closure_plotsCompare_58();
	Closure_plotsCompare_59();
	Closure_plotsCompare_60();
	Closure_plotsCompare_61();
	Closure_plotsCompare_62();
	Closure_plotsCompare_PrePostCuts_01();
	Closure_plotsCompare_PrePostCuts_02();
	Closure_plotsCompare_PrePostCuts_03();																							
}


void Closure_plotsCompare_Thesis(){
	Closure_plotsCompare_01();
	Closure_plotsCompare_03();	
	Closure_plotsCompare_60();
	Closure_plotsCompare_61();
	Closure_plotsCompare_62();
	Closure_plotsCompare_63();	
	Closure_plotsCompare_64();
	Closure_plotsCompare_65();
	Closure_plotsCompare_66();		
	Closure_plotsCompare_73();
	Closure_plotsCompare_74();					
}
