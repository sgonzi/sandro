#define TotalAnalysis_cxx
#include "GJetsAnalyzer.C"

void TotalAnalysis(){

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

// MC signal GJets_HT-xToy ----------------------------------------------

	GJetsAnalyzer MC_GJets_HT_200To400(0,11);
	MC_GJets_HT_200To400.Loop();
	
	GJetsAnalyzer MC_GJets_HT_400ToInf(0,12);
	MC_GJets_HT_400ToInf.Loop();

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
