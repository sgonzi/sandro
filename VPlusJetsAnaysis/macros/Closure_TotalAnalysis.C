#define Closure_TotalAnalysis_cxx
#include "Closure_GJetsAnalyzer.C"

using namespace std;

// ==================================== definitions for Fast Analysis

bool ReReco_data(bool out) {
	bool in = false;
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

void Closure_TotalAnalysis_dataReReco(){

	// data ReReco ----------------------------------------------------------
	Closure_GJetsAnalyzer DATA_RR_Run2012A_22Jan2013(0,1);
	DATA_RR_Run2012A_22Jan2013.Loop();
	
	Closure_GJetsAnalyzer DATA_RR_Run2012B_22Jan2013(0,2);
	DATA_RR_Run2012B_22Jan2013.Loop();

	Closure_GJetsAnalyzer DATA_RR_Run2012C_22Jan2013(0,3);
	DATA_RR_Run2012C_22Jan2013.Loop();

	Closure_GJetsAnalyzer DATA_RR_Run2012D_22Jan2013(0,4);
	DATA_RR_Run2012D_22Jan2013.Loop();
}


void Closure_TotalAnalysis_dataPromptReco(){

	// data PromptReco ------------------------------------------------------
	Closure_GJetsAnalyzer DATA_PR_Run2012A_13Jul2012(0,11);
	DATA_PR_Run2012A_13Jul2012.Loop();
	
	Closure_GJetsAnalyzer DATA_PR_Run2012A_recover_06Aug2012(0,12);
	DATA_PR_Run2012A_recover_06Aug2012.Loop();

	Closure_GJetsAnalyzer DATA_PR_Run2012B_13Jul2012(0,13);
	DATA_PR_Run2012B_13Jul2012.Loop();

	Closure_GJetsAnalyzer DATA_PR_Run2012C_24Aug2012(0,14);
	DATA_PR_Run2012C_24Aug2012.Loop();

	Closure_GJetsAnalyzer DATA_PR_Run2012C_EcalRecover_11Dec2012(0,15);
	DATA_PR_Run2012C_EcalRecover_11Dec2012.Loop();

}


void Closure_TotalAnalysis_GJets_HT_xToy(){

	// MC signal GJets_HT-xToy ----------------------------------------------

	Closure_GJetsAnalyzer MC_GJets_HT_40To100(0,21);
	MC_GJets_HT_40To100.Loop();

	Closure_GJetsAnalyzer MC_GJets_HT_100To200(0,22);
	MC_GJets_HT_100To200.Loop();

	Closure_GJetsAnalyzer MC_GJets_HT_200To400(0,23);
	MC_GJets_HT_200To400.Loop();
	
	Closure_GJetsAnalyzer MC_GJets_HT_400ToInf(0,24);
	MC_GJets_HT_400ToInf.Loop();
}


void Closure_TotalAnalysis_G_Pt_XtoY(){
	
	// MC signal G_Pt-XtoY --------------------------------------------------	
	Closure_GJetsAnalyzer MC_G_Pt_15to30(0,31);
	MC_G_Pt_15to30.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_30to50(0,32);
	MC_G_Pt_30to50.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_50to80(0,33);
	MC_G_Pt_50to80.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_80to120(0,34);
	MC_G_Pt_80to120.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_120to170(0,35);
	MC_G_Pt_120to170.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_170to300(0,36);
	MC_G_Pt_170to300.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_300to470(0,37);
	MC_G_Pt_300to470.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_470to800(0,38);
	MC_G_Pt_470to800.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_800to1400(0,39);
	MC_G_Pt_800to1400.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_1400to1800(0,40);
	MC_G_Pt_1400to1800.Loop();

	Closure_GJetsAnalyzer MC_G_Pt_1800(0,41);
	MC_G_Pt_1800.Loop();
}


void Closure_TotalAnalysis_DiPhotonJets(){

	// MC DiPhotonJets ------------------------------------------------------
	Closure_GJetsAnalyzer MC_DiPhotonJets(0,51);
	MC_DiPhotonJets.Loop();
}


void Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched(){

	// MC background QCD_Pt_x_y EMEnriched ----------------------------------
	Closure_GJetsAnalyzer MC_QCD_Pt_20_30_EMEnriched(0,61);
	MC_QCD_Pt_20_30_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_30_80_EMEnriched(0,62);
	MC_QCD_Pt_30_80_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_80_170_EMEnriched(0,63);
	MC_QCD_Pt_80_170_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_170_250_EMEnriched(0,64);
	MC_QCD_Pt_170_250_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_250_350_EMEnriched(0,65);
	MC_QCD_Pt_250_350_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_350_EMEnriched(0,66);
	MC_QCD_Pt_350_EMEnriched.Loop();
}


void Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE(){

	// MC background QCD_Pt_x_y BCtoE ---------------------------------------
	Closure_GJetsAnalyzer MC_QCD_Pt_20_30_BCtoE(0,71);
	MC_QCD_Pt_20_30_BCtoE.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_30_80_BCtoE(0,72);
	MC_QCD_Pt_30_80_BCtoE.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_80_170_BCtoE(0,73);
	MC_QCD_Pt_80_170_BCtoE.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_170_250_BCtoE(0,74);
	MC_QCD_Pt_170_250_BCtoE.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_250_350_BCtoE(0,75);
	MC_QCD_Pt_250_350_BCtoE.Loop();
	
	Closure_GJetsAnalyzer MC_QCD_Pt_350_BCtoE(0,76);
	MC_QCD_Pt_350_BCtoE.Loop();
}


void Closure_TotalAnalysis_QCD_HT_xToy(){

	// MC background QCD HT-xToy --------------------------------------------
	Closure_GJetsAnalyzer MC_QCD_HT_100To250(0,81);
	MC_QCD_HT_100To250.Loop();		

	Closure_GJetsAnalyzer MC_QCD_HT_250To500(0,82);
	MC_QCD_HT_250To500.Loop();		

	Closure_GJetsAnalyzer MC_QCD_HT_500To1000(0,83);
	MC_QCD_HT_500To1000.Loop();		

	Closure_GJetsAnalyzer MC_QCD_HT_1000ToInf(0,84);
	MC_QCD_HT_1000ToInf.Loop();
}

// PSEUDODATA--

void Closure_TotalAnalysis_PSEUDODATA_GJets_HT_xToy(){

	// PSEUDODATA: MC signal GJets_HT-xToy ----------------------------------------------

	Closure_GJetsAnalyzer PSEUDODATA_MC_GJets_HT_40To100(0,121);
	PSEUDODATA_MC_GJets_HT_40To100.Loop();

	Closure_GJetsAnalyzer PSEUDODATA_MC_GJets_HT_100To200(0,122);
	PSEUDODATA_MC_GJets_HT_100To200.Loop();

	Closure_GJetsAnalyzer PSEUDODATA_MC_GJets_HT_200To400(0,123);
	PSEUDODATA_MC_GJets_HT_200To400.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_GJets_HT_400ToInf(0,124);
	PSEUDODATA_MC_GJets_HT_400ToInf.Loop();
}


void Closure_TotalAnalysis_PSEUDODATA_DiPhotonJets(){

	// PSEUDODATA: MC DiPhotonJets ------------------------------------------------------
	Closure_GJetsAnalyzer PSEUDODATA_MC_DiPhotonJets(0,151);
	PSEUDODATA_MC_DiPhotonJets.Loop();
}


void Closure_TotalAnalysis_PSEUDODATA_QCD_Pt_x_y_EMEnriched(){

	// PSEUDODATA: MC background QCD_Pt_x_y EMEnriched ----------------------------------
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_20_30_EMEnriched(0,161);
	PSEUDODATA_MC_QCD_Pt_20_30_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_30_80_EMEnriched(0,162);
	PSEUDODATA_MC_QCD_Pt_30_80_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_80_170_EMEnriched(0,163);
	PSEUDODATA_MC_QCD_Pt_80_170_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_170_250_EMEnriched(0,164);
	PSEUDODATA_MC_QCD_Pt_170_250_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_250_350_EMEnriched(0,165);
	PSEUDODATA_MC_QCD_Pt_250_350_EMEnriched.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_350_EMEnriched(0,166);
	PSEUDODATA_MC_QCD_Pt_350_EMEnriched.Loop();
}


void Closure_TotalAnalysis_PSEUDODATA_QCD_Pt_x_y_BCtoE(){

	// PSEUDODATA: MC background QCD_Pt_x_y BCtoE ---------------------------------------
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_20_30_BCtoE(0,171);
	PSEUDODATA_MC_QCD_Pt_20_30_BCtoE.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_30_80_BCtoE(0,172);
	PSEUDODATA_MC_QCD_Pt_30_80_BCtoE.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_80_170_BCtoE(0,173);
	PSEUDODATA_MC_QCD_Pt_80_170_BCtoE.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_170_250_BCtoE(0,174);
	PSEUDODATA_MC_QCD_Pt_170_250_BCtoE.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_250_350_BCtoE(0,175);
	PSEUDODATA_MC_QCD_Pt_250_350_BCtoE.Loop();
	
	Closure_GJetsAnalyzer PSEUDODATA_MC_QCD_Pt_350_BCtoE(0,176);
	PSEUDODATA_MC_QCD_Pt_350_BCtoE.Loop();
}


// ==================================== collectives functions

void Closure_FastAnalysis(){

	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) Closure_TotalAnalysis_dataReReco();
	else Closure_TotalAnalysis_dataPromptReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) Closure_TotalAnalysis_GJets_HT_xToy();
	else Closure_TotalAnalysis_G_Pt_XtoY();

	Closure_TotalAnalysis_DiPhotonJets();

	bool b_QCD = false;
	b_QCD = background_QCD(b_QCD);
	if (b_QCD) Closure_TotalAnalysis_QCD_HT_xToy();
	else {
		Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched();
		Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE();
	}
}


void Closure_FastAnalysis_rest(){

	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) Closure_TotalAnalysis_dataPromptReco(); 
	else Closure_TotalAnalysis_dataReReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) Closure_TotalAnalysis_G_Pt_XtoY();
	else Closure_TotalAnalysis_GJets_HT_xToy();

	bool b_QCD = false;
	b_QCD = background_QCD(b_QCD);
	if (b_QCD) {
		Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched();
		Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE();
	}
	else Closure_TotalAnalysis_QCD_HT_xToy();
}


void Closure_TotalAnalysis(){

	Closure_TotalAnalysis_dataReReco();
	//Closure_TotalAnalysis_dataPromptReco();
	Closure_TotalAnalysis_GJets_HT_xToy();
	Closure_TotalAnalysis_G_Pt_XtoY();
	Closure_TotalAnalysis_DiPhotonJets();
	Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched();
	Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE();
	Closure_TotalAnalysis_QCD_HT_xToy();
}


void Closure_BackgroundExtracted_Analysis(){

	bool RR_d = false;
	RR_d = ReReco_data(RR_d);
	if (RR_d) Closure_TotalAnalysis_dataReReco();
	else Closure_TotalAnalysis_dataPromptReco();

	bool s_MAD = false;
	s_MAD = signal_MAD(s_MAD);
	if (s_MAD) Closure_TotalAnalysis_GJets_HT_xToy();
	else Closure_TotalAnalysis_G_Pt_XtoY();

	Closure_TotalAnalysis_DiPhotonJets();
}


void Closure_GENAnalysis(){

	Closure_TotalAnalysis_GJets_HT_xToy();
	Closure_TotalAnalysis_DiPhotonJets();
}

//---- 

void Closure_PSEUDO_FastAnalysis(){

	Closure_TotalAnalysis_PSEUDODATA_GJets_HT_xToy();
	Closure_TotalAnalysis_PSEUDODATA_DiPhotonJets();
	Closure_TotalAnalysis_PSEUDODATA_QCD_Pt_x_y_EMEnriched();
	Closure_TotalAnalysis_PSEUDODATA_QCD_Pt_x_y_BCtoE();

	Closure_TotalAnalysis_GJets_HT_xToy();
	Closure_TotalAnalysis_DiPhotonJets();
	Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched();
	Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE();
}


void Closure_PSEUDO_FastAnalysis_1(){

	Closure_TotalAnalysis_PSEUDODATA_GJets_HT_xToy();
	Closure_TotalAnalysis_PSEUDODATA_DiPhotonJets();
	Closure_TotalAnalysis_PSEUDODATA_QCD_Pt_x_y_EMEnriched();
	Closure_TotalAnalysis_PSEUDODATA_QCD_Pt_x_y_BCtoE();
}

void Closure_PSEUDO_FastAnalysis_2(){
	Closure_TotalAnalysis_GJets_HT_xToy();
	Closure_TotalAnalysis_DiPhotonJets();
	Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched();
	Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE();
}










void Closure_resto(){

	Closure_TotalAnalysis_dataPromptReco();
	Closure_TotalAnalysis_GJets_HT_xToy();
	Closure_TotalAnalysis_DiPhotonJets();
}

void Closure_resto1(){
	Closure_TotalAnalysis_QCD_Pt_x_y_EMEnriched();
	Closure_TotalAnalysis_QCD_Pt_x_y_BCtoE();
}
