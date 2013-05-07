#define TotalAnalysis_cxx
#include "GJetsAnalyzer.C"



void TotalAnalysis_data(){

	// data -----------------------------------------------------------------

	GJetsAnalyzer DATA_Run2012A_13Jul2012(0,1);
	DATA_Run2012A_13Jul2012.Loop();
	
	GJetsAnalyzer DATA_Run2012A_recover_06Aug2012(0,2);
	DATA_Run2012A_recover_06Aug2012.Loop();

	GJetsAnalyzer DATA_Run2012B_13Jul2012(0,3);
	DATA_Run2012B_13Jul2012.Loop();

	GJetsAnalyzer DATA_Run2012C_24Aug2012(0,4);
	DATA_Run2012C_24Aug2012.Loop();

	GJetsAnalyzer DATA_Run2012C_EcalRecover_11Dec2012(0,5);
	DATA_Run2012C_EcalRecover_11Dec2012.Loop();

	GJetsAnalyzer DATA_Run2012C_PromptReco(0,6);
	DATA_Run2012C_PromptReco.Loop();

	GJetsAnalyzer DATA_Run2012D_PromptReco(0,7);
	DATA_Run2012D_PromptReco.Loop();
}


void TotalAnalysis_GJets_HT_xToy(){

	// MC signal GJets_HT-xToy ----------------------------------------------

	GJetsAnalyzer MC_GJets_HT_200To400(0,11);
	MC_GJets_HT_200To400.Loop();
	
	GJetsAnalyzer MC_GJets_HT_400ToInf(0,12);
	MC_GJets_HT_400ToInf.Loop();
}


void TotalAnalysis_QCD_Pt_x_y_EMEnriched(){

	// MC background QCD_Pt_x_y EMEnriched ----------------------------------
	
	GJetsAnalyzer MC_QCD_Pt_20_30_EMEnriched(0,21);
	MC_QCD_Pt_20_30_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_30_80_EMEnriched(0,22);
	MC_QCD_Pt_30_80_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_80_170_EMEnriched(0,23);
	MC_QCD_Pt_80_170_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_170_250_EMEnriched(0,24);
	MC_QCD_Pt_170_250_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_250_350_EMEnriched(0,25);
	MC_QCD_Pt_250_350_EMEnriched.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_350_EMEnriched(0,26);
	MC_QCD_Pt_350_EMEnriched.Loop();
}


void TotalAnalysis_QCD_Pt_x_y_BCtoE(){

	// MC background QCD_Pt_x_y BCtoE ---------------------------------------

	GJetsAnalyzer MC_QCD_Pt_20_30_BCtoE(0,31);
	MC_QCD_Pt_20_30_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_30_80_BCtoE(0,32);
	MC_QCD_Pt_30_80_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_80_170_BCtoE(0,33);
	MC_QCD_Pt_80_170_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_170_250_BCtoE(0,34);
	MC_QCD_Pt_170_250_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_250_350_BCtoE(0,35);
	MC_QCD_Pt_250_350_BCtoE.Loop();
	
	GJetsAnalyzer MC_QCD_Pt_350_BCtoE(0,36);
	MC_QCD_Pt_350_BCtoE.Loop();
}


void TotalAnalysis_QCD_HT_xToy(){

	// MC background QCD HT-xToy --------------------------------------------
		
	GJetsAnalyzer MC_QCD_HT_100To250(0,41);
	MC_QCD_HT_100To250.Loop();		

	GJetsAnalyzer MC_QCD_HT_250To500(0,42);
	MC_QCD_HT_250To500.Loop();		

	GJetsAnalyzer MC_QCD_HT_500To1000(0,43);
	MC_QCD_HT_500To1000.Loop();		

	GJetsAnalyzer MC_QCD_HT_1000ToInf(0,44);
	MC_QCD_HT_1000ToInf.Loop();
}


void TotalAnalysis_G_Pt_XtoY(){
	
	// MC signal G_Pt-XtoY --------------------------------------------------	
		
	GJetsAnalyzer MC_G_Pt_15to30(0,51);
	MC_G_Pt_15to30.Loop();

	GJetsAnalyzer MC_G_Pt_30to50(0,52);
	MC_G_Pt_30to50.Loop();

	GJetsAnalyzer MC_G_Pt_50to80(0,53);
	MC_G_Pt_50to80.Loop();

	GJetsAnalyzer MC_G_Pt_80to120(0,54);
	MC_G_Pt_80to120.Loop();

	GJetsAnalyzer MC_G_Pt_120to170(0,55);
	MC_G_Pt_120to170.Loop();

	GJetsAnalyzer MC_G_Pt_170to300(0,56);
	MC_G_Pt_170to300.Loop();

	GJetsAnalyzer MC_G_Pt_300to470(0,57);
	MC_G_Pt_300to470.Loop();

	GJetsAnalyzer MC_G_Pt_470to800(0,58);
	MC_G_Pt_470to800.Loop();

	GJetsAnalyzer MC_G_Pt_800to1400(0,59);
	MC_G_Pt_800to1400.Loop();

	GJetsAnalyzer MC_G_Pt_1400to1800(0,60);
	MC_G_Pt_1400to1800.Loop();

	GJetsAnalyzer MC_G_Pt_1800(0,61);
	MC_G_Pt_1800.Loop();
}


void TotalAnalysis_DiPhotonJets(){

	// MC DiPhotonJets ------------------------------------------------------

	GJetsAnalyzer MC_DiPhotonJets(0,71);
	MC_DiPhotonJets.Loop();
}



void TotalAnalysis(){

	TotalAnalysis_data();
	TotalAnalysis_GJets_HT_xToy();
	TotalAnalysis_QCD_Pt_x_y_EMEnriched();
	TotalAnalysis_QCD_Pt_x_y_BCtoE();
	TotalAnalysis_QCD_HT_xToy();
	TotalAnalysis_G_Pt_XtoY();
	TotalAnalysis_DiPhotonJets();
}
