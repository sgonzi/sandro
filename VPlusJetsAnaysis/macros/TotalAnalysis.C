#define TotalAnalysis_cxx
#include "GJetsAnalyzer.C"

bool ReReco_data(bool out) {
	bool in = true;
	out = in;
	return out;
}

bool signal_MAD(bool out) {
	bool in = true;
	out = in;
	return out;
}

bool background_QCD(bool out) {
	bool in = true;
	out = in;
	return out;
}


void TotalAnalysis_dataReReco(){

	// data ReReco ----------------------------------------------------------
	GJetsAnalyzer DATA_RR_Run2012A_22Jan2013(0,1);
	DATA_RR_Run2012A_22Jan2013.Loop();
	
	GJetsAnalyzer DATA_RR_Run2012B_22Jan2013(0,2);
	DATA_RR_Run2012B_22Jan2013.Loop();

	GJetsAnalyzer DATA_RR_Run2012C_22Jan2013(0,3);
	DATA_RR_Run2012C_22Jan2013.Loop();

	GJetsAnalyzer DATA_RR_Run2012D_22Jan2013(0,4);
	DATA_RR_Run2012D_22Jan2013.Loop();
}


void TotalAnalysis_dataPromptReco(){

	// data PromptReco ------------------------------------------------------
	GJetsAnalyzer DATA_PR_Run2012A_13Jul2012(0,11);
	DATA_PR_Run2012A_13Jul2012.Loop();
	
	GJetsAnalyzer DATA_PR_Run2012A_recover_06Aug2012(0,12);
	DATA_PR_Run2012A_recover_06Aug2012.Loop();

	GJetsAnalyzer DATA_PR_Run2012B_13Jul2012(0,13);
	DATA_PR_Run2012B_13Jul2012.Loop();

	GJetsAnalyzer DATA_PR_Run2012C_24Aug2012(0,14);
	DATA_PR_Run2012C_24Aug2012.Loop();

	GJetsAnalyzer DATA_PR_Run2012C_EcalRecover_11Dec2012(0,15);
	DATA_PR_Run2012C_EcalRecover_11Dec2012.Loop();

	GJetsAnalyzer DATA_PR_Run2012C_PromptReco(0,16);
	DATA_PR_Run2012C_PromptReco.Loop();

	GJetsAnalyzer DATA_PR_Run2012D_PromptReco(0,17);
	DATA_PR_Run2012D_PromptReco.Loop();
}


void TotalAnalysis_GJets_HT_xToy(){

	// MC signal GJets_HT-xToy ----------------------------------------------
/*
	GJetsAnalyzer MC_GJets_HT_40To100(0,11);
	MC_GJets_HT_40To100.Loop();
*/

	GJetsAnalyzer MC_GJets_HT_100To200(0,22);
	MC_GJets_HT_100To200.Loop();

	GJetsAnalyzer MC_GJets_HT_200To400(0,23);
	MC_GJets_HT_200To400.Loop();
	
	GJetsAnalyzer MC_GJets_HT_400ToInf(0,24);
	MC_GJets_HT_400ToInf.Loop();
}


void TotalAnalysis_G_Pt_XtoY(){
	
	// MC signal G_Pt-XtoY --------------------------------------------------	
	GJetsAnalyzer MC_G_Pt_15to30(0,31);
	MC_G_Pt_15to30.Loop();

	GJetsAnalyzer MC_G_Pt_30to50(0,32);
	MC_G_Pt_30to50.Loop();

	GJetsAnalyzer MC_G_Pt_50to80(0,33);
	MC_G_Pt_50to80.Loop();

	GJetsAnalyzer MC_G_Pt_80to120(0,34);
	MC_G_Pt_80to120.Loop();

	GJetsAnalyzer MC_G_Pt_120to170(0,35);
	MC_G_Pt_120to170.Loop();

	GJetsAnalyzer MC_G_Pt_170to300(0,36);
	MC_G_Pt_170to300.Loop();

	GJetsAnalyzer MC_G_Pt_300to470(0,37);
	MC_G_Pt_300to470.Loop();

	GJetsAnalyzer MC_G_Pt_470to800(0,38);
	MC_G_Pt_470to800.Loop();

	GJetsAnalyzer MC_G_Pt_800to1400(0,39);
	MC_G_Pt_800to1400.Loop();

	GJetsAnalyzer MC_G_Pt_1400to1800(0,40);
	MC_G_Pt_1400to1800.Loop();

	GJetsAnalyzer MC_G_Pt_1800(0,41);
	MC_G_Pt_1800.Loop();
}


void TotalAnalysis_DiPhotonJets(){

	// MC DiPhotonJets ------------------------------------------------------
	GJetsAnalyzer MC_DiPhotonJets(0,51);
	MC_DiPhotonJets.Loop();
}


void TotalAnalysis_QCD_Pt_x_y_EMEnriched(){

	// MC background QCD_Pt_x_y EMEnriched ----------------------------------
	GJetsAnalyzer MC_QCD_Pt_20_30_EMEnriched(0,61);
	MC_QCD_Pt_20_30_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_30_80_EMEnriched(0,62);
	MC_QCD_Pt_30_80_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_80_170_EMEnriched(0,63);
	MC_QCD_Pt_80_170_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_170_250_EMEnriched(0,64);
	MC_QCD_Pt_170_250_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_250_350_EMEnriched(0,65);
	MC_QCD_Pt_250_350_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_350_EMEnriched(0,66);
	MC_QCD_Pt_350_EMEnriched.Loop();
}


void TotalAnalysis_QCD_Pt_x_y_BCtoE(){

	// MC background QCD_Pt_x_y BCtoE ---------------------------------------
	GJetsAnalyzer MC_QCD_Pt_20_30_BCtoE(0,71);
	MC_QCD_Pt_20_30_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_30_80_BCtoE(0,72);
	MC_QCD_Pt_30_80_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_80_170_BCtoE(0,73);
	MC_QCD_Pt_80_170_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_170_250_BCtoE(0,74);
	MC_QCD_Pt_170_250_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_250_350_BCtoE(0,75);
	MC_QCD_Pt_250_350_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_350_BCtoE(0,76);
	MC_QCD_Pt_350_BCtoE.Loop();
}


void TotalAnalysis_QCD_HT_xToy(){

	// MC background QCD HT-xToy --------------------------------------------
	GJetsAnalyzer MC_QCD_HT_100To250(0,81);
	MC_QCD_HT_100To250.Loop();		

	GJetsAnalyzer MC_QCD_HT_250To500(0,82);
	MC_QCD_HT_250To500.Loop();		

	GJetsAnalyzer MC_QCD_HT_500To1000(0,83);
	MC_QCD_HT_500To1000.Loop();		

	GJetsAnalyzer MC_QCD_HT_1000ToInf(0,84);
	MC_QCD_HT_1000ToInf.Loop();
}


void FastAnalysis(){

	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) TotalAnalysis_dataReReco();
	else TotalAnalysis_dataPromptReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) TotalAnalysis_GJets_HT_xToy();
	else TotalAnalysis_G_Pt_XtoY();

	TotalAnalysis_DiPhotonJets();

	bool b_QCD = false;
	b_QCD = background_QCD(b_QCD);
	if (b_QCD) TotalAnalysis_QCD_HT_xToy();
	else {
		TotalAnalysis_QCD_Pt_x_y_EMEnriched();
		TotalAnalysis_QCD_Pt_x_y_BCtoE();
	}
}


void FastAnalysis_rest(){

	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) TotalAnalysis_dataPromptReco(); 
	else TotalAnalysis_dataReReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) TotalAnalysis_G_Pt_XtoY();
	else TotalAnalysis_GJets_HT_xToy();

	bool b_QCD = false;
	b_QCD = background_QCD(b_QCD);
	if (b_QCD) {
		TotalAnalysis_QCD_Pt_x_y_EMEnriched();
		TotalAnalysis_QCD_Pt_x_y_BCtoE();
	}
	else TotalAnalysis_QCD_HT_xToy();
}


void TotalAnalysis(){

	TotalAnalysis_dataPromptReco();
	TotalAnalysis_GJets_HT_xToy();
	TotalAnalysis_G_Pt_XtoY();
	TotalAnalysis_DiPhotonJets();
	TotalAnalysis_QCD_Pt_x_y_EMEnriched();
	TotalAnalysis_QCD_Pt_x_y_BCtoE();
	TotalAnalysis_QCD_HT_xToy();
}
