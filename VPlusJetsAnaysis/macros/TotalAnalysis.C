#define TotalAnalysis_cxx
#include "GJetsAnalyzer.C"

void TotalAnalysis(){
	
	GJetsAnalyzer data(0,0);
	data.Loop();
	
	GJetsAnalyzer mc_Signal1(0,1);
	mc_Signal1.Loop();
	
	GJetsAnalyzer mc_Signal2(0,2);
	mc_Signal2.Loop();
	
	GJetsAnalyzer mc_Background3(0,3);
	mc_Background3.Loop();
	
	GJetsAnalyzer mc_Background4(0,4);
	mc_Background4.Loop();
	
	GJetsAnalyzer mc_Background5(0,5);
	mc_Background5.Loop();
	
	GJetsAnalyzer mc_Background6(0,6);
	mc_Background6.Loop();
	
	GJetsAnalyzer mc_Background7(0,7);
	mc_Background7.Loop();
	
	GJetsAnalyzer mc_Background8(0,8);
	mc_Background8.Loop();
}
