#define TotalTurnOn_cxx
#include "TurnOn.C"

// ==================================== definitions for Fast Analysis

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
	bool in = false;
	out = in;
	return out;
}


// ==================================== functions

void TotalTurnOn_dataReReco(){

	// data ReReco ----------------------------------------------------------
	TurnOn DATA_RR_Run2012A_22Jan2013(0,1);
	DATA_RR_Run2012A_22Jan2013.Loop();
	
	TurnOn DATA_RR_Run2012B_22Jan2013(0,2);
	DATA_RR_Run2012B_22Jan2013.Loop();

	TurnOn DATA_RR_Run2012C_22Jan2013(0,3);
	DATA_RR_Run2012C_22Jan2013.Loop();

	TurnOn DATA_RR_Run2012D_22Jan2013(0,4);
	DATA_RR_Run2012D_22Jan2013.Loop();
}


void TotalTurnOn_dataPromptReco(){

	// data PromptReco ------------------------------------------------------
	TurnOn DATA_PR_Run2012A_13Jul2012(0,11);
	DATA_PR_Run2012A_13Jul2012.Loop();
	
	TurnOn DATA_PR_Run2012A_recover_06Aug2012(0,12);
	DATA_PR_Run2012A_recover_06Aug2012.Loop();

	TurnOn DATA_PR_Run2012B_13Jul2012(0,13);
	DATA_PR_Run2012B_13Jul2012.Loop();

	TurnOn DATA_PR_Run2012C_24Aug2012(0,14);
	DATA_PR_Run2012C_24Aug2012.Loop();

	TurnOn DATA_PR_Run2012C_EcalRecover_11Dec2012(0,15);
	DATA_PR_Run2012C_EcalRecover_11Dec2012.Loop();

	TurnOn DATA_PR_Run2012C_PromptReco(0,16);
	DATA_PR_Run2012C_PromptReco.Loop();

	TurnOn DATA_PR_Run2012D_PromptReco(0,17);
	DATA_PR_Run2012D_PromptReco.Loop();
}


void TotalTurnOn_GJets_HT_xToy(){

	// MC signal GJets_HT-xToy ----------------------------------------------

	TurnOn MC_GJets_HT_40To100(0,21);
	MC_GJets_HT_40To100.Loop();

	TurnOn MC_GJets_HT_100To200(0,22);
	MC_GJets_HT_100To200.Loop();

	TurnOn MC_GJets_HT_200To400(0,23);
	MC_GJets_HT_200To400.Loop();
	
	TurnOn MC_GJets_HT_400ToInf(0,24);
	MC_GJets_HT_400ToInf.Loop();
}


void TotalTurnOn_G_Pt_XtoY(){
	
	// MC signal G_Pt-XtoY --------------------------------------------------	
	TurnOn MC_G_Pt_15to30(0,31);
	MC_G_Pt_15to30.Loop();

	TurnOn MC_G_Pt_30to50(0,32);
	MC_G_Pt_30to50.Loop();

	TurnOn MC_G_Pt_50to80(0,33);
	MC_G_Pt_50to80.Loop();

	TurnOn MC_G_Pt_80to120(0,34);
	MC_G_Pt_80to120.Loop();

	TurnOn MC_G_Pt_120to170(0,35);
	MC_G_Pt_120to170.Loop();

	TurnOn MC_G_Pt_170to300(0,36);
	MC_G_Pt_170to300.Loop();

	TurnOn MC_G_Pt_300to470(0,37);
	MC_G_Pt_300to470.Loop();

	TurnOn MC_G_Pt_470to800(0,38);
	MC_G_Pt_470to800.Loop();

	TurnOn MC_G_Pt_800to1400(0,39);
	MC_G_Pt_800to1400.Loop();

	TurnOn MC_G_Pt_1400to1800(0,40);
	MC_G_Pt_1400to1800.Loop();

	TurnOn MC_G_Pt_1800(0,41);
	MC_G_Pt_1800.Loop();
}


void TotalTurnOn_DiPhotonJets(){

	// MC DiPhotonJets ------------------------------------------------------
	TurnOn MC_DiPhotonJets(0,51);
	MC_DiPhotonJets.Loop();
}


void TotalTurnOn_QCD_Pt_x_y_EMEnriched(){

	// MC background QCD_Pt_x_y EMEnriched ----------------------------------
	TurnOn MC_QCD_Pt_20_30_EMEnriched(0,61);
	MC_QCD_Pt_20_30_EMEnriched.Loop();
	
	TurnOn MC_QCD_Pt_30_80_EMEnriched(0,62);
	MC_QCD_Pt_30_80_EMEnriched.Loop();
	
	TurnOn MC_QCD_Pt_80_170_EMEnriched(0,63);
	MC_QCD_Pt_80_170_EMEnriched.Loop();
	
	TurnOn MC_QCD_Pt_170_250_EMEnriched(0,64);
	MC_QCD_Pt_170_250_EMEnriched.Loop();
	
	TurnOn MC_QCD_Pt_250_350_EMEnriched(0,65);
	MC_QCD_Pt_250_350_EMEnriched.Loop();
	
	TurnOn MC_QCD_Pt_350_EMEnriched(0,66);
	MC_QCD_Pt_350_EMEnriched.Loop();
}


void TotalTurnOn_QCD_Pt_x_y_BCtoE(){

	// MC background QCD_Pt_x_y BCtoE ---------------------------------------
	TurnOn MC_QCD_Pt_20_30_BCtoE(0,71);
	MC_QCD_Pt_20_30_BCtoE.Loop();
	
	TurnOn MC_QCD_Pt_30_80_BCtoE(0,72);
	MC_QCD_Pt_30_80_BCtoE.Loop();
	
	TurnOn MC_QCD_Pt_80_170_BCtoE(0,73);
	MC_QCD_Pt_80_170_BCtoE.Loop();
	
	TurnOn MC_QCD_Pt_170_250_BCtoE(0,74);
	MC_QCD_Pt_170_250_BCtoE.Loop();
	
	TurnOn MC_QCD_Pt_250_350_BCtoE(0,75);
	MC_QCD_Pt_250_350_BCtoE.Loop();
	
	TurnOn MC_QCD_Pt_350_BCtoE(0,76);
	MC_QCD_Pt_350_BCtoE.Loop();
}


void TotalTurnOn_QCD_HT_xToy(){

	// MC background QCD HT-xToy --------------------------------------------
	TurnOn MC_QCD_HT_100To250(0,81);
	MC_QCD_HT_100To250.Loop();		

	TurnOn MC_QCD_HT_250To500(0,82);
	MC_QCD_HT_250To500.Loop();		

	TurnOn MC_QCD_HT_500To1000(0,83);
	MC_QCD_HT_500To1000.Loop();		

	TurnOn MC_QCD_HT_1000ToInf(0,84);
	MC_QCD_HT_1000ToInf.Loop();
}


// ==================================== collectives functions

void FastAnalysis(){


	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) TotalTurnOn_dataReReco();
	else TotalTurnOn_dataPromptReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) TotalTurnOn_GJets_HT_xToy();
	else TotalTurnOn_G_Pt_XtoY();

	TotalTurnOn_DiPhotonJets();

	bool b_QCD = false;
	b_QCD = background_QCD(b_QCD);
	if (b_QCD) TotalTurnOn_QCD_HT_xToy();
	else {
		TotalTurnOn_QCD_Pt_x_y_EMEnriched();
		TotalTurnOn_QCD_Pt_x_y_BCtoE();
	}
}


void FastAnalysis_rest(){

	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) TotalTurnOn_dataPromptReco(); 
	else TotalTurnOn_dataReReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) TotalTurnOn_G_Pt_XtoY();
	else TotalTurnOn_GJets_HT_xToy();

	bool b_QCD = false;
	b_QCD = background_QCD(b_QCD);
	if (b_QCD) {
		TotalTurnOn_QCD_Pt_x_y_EMEnriched();
		TotalTurnOn_QCD_Pt_x_y_BCtoE();
	}
	else TotalTurnOn_QCD_HT_xToy();
}


void TotalTurnOn(){

	TotalTurnOn_dataReReco();
	//TotalTurnOn_dataPromptReco();
	TotalTurnOn_GJets_HT_xToy();
	TotalTurnOn_G_Pt_XtoY();
	TotalTurnOn_DiPhotonJets();
	TotalTurnOn_QCD_Pt_x_y_EMEnriched();
	TotalTurnOn_QCD_Pt_x_y_BCtoE();
	TotalTurnOn_QCD_HT_xToy();
}

