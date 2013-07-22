#define provaTriMa_cxx
#include <TStyle.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>

void provaTriMa() {

	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);	


  TCanvas *Canva1 = new TCanvas("Trigger_Matching_1","Trigger Matching 1");
	Canva1->Divide(3,2);


//*****************
	Canva1->cd(1);

	TChain *ll_new = new TChain("accepted/events");

	ll_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/DoubleElectron.root");
	ll_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/DoubleMu.root");
	
	//grafico 1
	ll_new->SetLineColor(kBlue+2);
	ll_new->SetLineWidth(3);	
	ll_new->Draw("llM>>h1na(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-4 || lepChId[0]*lepChId[1]==-1)");

	//grafico 2
	ll_new->SetLineColor(kGreen+2);
	ll_new->SetLineWidth(3);		
	ll_new->Draw("llM>>h1naT(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && isTriggered&1) || (lepChId[0]*lepChId[1]==-1 && isTriggered&2))","SAME");

	//grafico 3
	ll_new->SetLineColor(kRed+2);
	ll_new->SetLineWidth(3);		
	ll_new->Draw("llM>>h1naTM(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && ((TriMatchF1Path_doubleMu[0]&1 && TriMatchF1Path_doubleMu[1]&1) || (TriMatchF1Path_doubleMu[0]&2 && TriMatchF1Path_doubleMu[1]&2) || (TriMatchF1Path_doubleMu[0]&4 && TriMatchF1Path_doubleMu[1]&4) || (TriMatchF1Path_doubleMu[0]&8 && TriMatchF1Path_doubleMu[1]&8))) || (lepChId[0]*lepChId[1]==-1 && ((TriMatchF2Path_doubleEle[0]&1 && TriMatchF2Path_doubleEle[1]&1) || (TriMatchF2Path_doubleEle[0]&2 && TriMatchF2Path_doubleEle[1]&2))))","SAME");

	TLegend *L1_new_a = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L1_new_a->SetFillColor(0); 
	L1_new_a->SetFillStyle(0); 
	L1_new_a->SetBorderSize(0);
	L1_new_a->AddEntry("h1na","No Trigger");
	L1_new_a->AddEntry("h1naT","With Trigger");
	L1_new_a->AddEntry("h1naTM","#splitline{With new}{TriggerMatching}");
	L1_new_a->Draw();

	TPaveText *T1_new_a = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T1_new_a->SetFillColor(0);
	T1_new_a->SetFillStyle(0);
	T1_new_a->SetBorderSize(1);		
	T1_new_a->AddText("DoubleEle + DoubleMu llM");
	T1_new_a->Draw();

//*****************
	Canva1->cd(4);
	
	TChain *ll_old = new TChain("accepted/events");

	ll_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/DoubleElectron.root");
	ll_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/DoubleMu.root");
	
	//grafico 1
	ll_old->SetLineColor(kBlue+2);
	ll_old->SetLineWidth(3);	
	ll_old->Draw("llM>>h1oa(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-4 || lepChId[0]*lepChId[1]==-1)");

	//grafico 2
	ll_old->SetLineColor(kGreen+2);
	ll_old->SetLineWidth(3);		
	ll_old->Draw("llM>>h1oaT(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && isTriggered&1) || (lepChId[0]*lepChId[1]==-1 && isTriggered&2))","SAME");

	//grafico 3
	ll_old->SetLineColor(kRed+2);
	ll_old->SetLineWidth(3);		
	ll_old->Draw("llM>>h1oaTM(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && isTriggerMatchedFamily1) || (lepChId[0]*lepChId[1]==-1 && isTriggerMatchedFamily2))", "SAME");

	TLegend *L1_old_a = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L1_old_a->SetFillColor(0); 
	L1_old_a->SetFillStyle(0); 
	L1_old_a->SetBorderSize(0);
	L1_old_a->AddEntry("h1oa","No Trigger");
	L1_old_a->AddEntry("h1oaT","With Trigger");
	L1_old_a->AddEntry("h1oaTM","#splitline{With old}{TriggerMatching}");
	L1_old_a->Draw();

	TPaveText *T1_old_a = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T1_old_a->SetFillColor(0);
	T1_old_a->SetFillStyle(0);
	T1_old_a->SetBorderSize(1);		
	T1_old_a->AddText("DoubleEle + DoubleMu llM");
	T1_old_a->Draw();

//---------------

//*****************
	Canva1->cd(2);
	  
	TChain *of_new = new TChain("accepted/events");

	of_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MuEG.root");

	//grafico 4
	of_new->SetLineColor(kBlue+2);
	of_new->SetLineWidth(3);	
	of_new->Draw("llM>>h2na(50,60,110)","lepChId[0]*lepChId[1]==-2 && jetPt[0]>30");

	//grafico 5
	of_new->SetLineColor(kGreen+2);
	of_new->SetLineWidth(3);
	of_new->Draw("llM>>h2naT(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-2 && (isTriggered&4))","SAME");

	//grafico 6
	of_new->SetLineColor(kRed+2);
	of_new->SetLineWidth(3);	
	of_new->Draw("llM>>h2naTM(50,60,110)","(lepChId[0]*lepChId[1]==-2 && jetPt[0]>30) && (((TriMatchF3Path_MuEle_muon[0]&1 && TriMatchF3Path_MuEle_electron[1]&1) || (TriMatchF3Path_MuEle_muon[1]&1 && TriMatchF3Path_MuEle_electron[0]&1)) || ((TriMatchF3Path_MuEle_muon[0]&2 && TriMatchF3Path_MuEle_electron[1]&2) || (TriMatchF3Path_MuEle_muon[1]&2 && TriMatchF3Path_MuEle_electron[0]&2)) || ((TriMatchF3Path_MuEle_muon[0]&4 && TriMatchF3Path_MuEle_electron[1]&4) || (TriMatchF3Path_MuEle_muon[1]&4 && TriMatchF3Path_MuEle_electron[0]&4)) || ((TriMatchF3Path_MuEle_muon[0]&8 && TriMatchF3Path_MuEle_electron[1]&8) || (TriMatchF3Path_MuEle_muon[1]&8 && TriMatchF3Path_MuEle_electron[0]&8)) || ((TriMatchF3Path_MuEle_muon[0]&16 && TriMatchF3Path_MuEle_electron[1]&16) || (TriMatchF3Path_MuEle_muon[1]&16 && TriMatchF3Path_MuEle_electron[0]&16)) || ((TriMatchF3Path_MuEle_muon[0]&32 && TriMatchF3Path_MuEle_electron[1]&32) || (TriMatchF3Path_MuEle_muon[1]&32 && TriMatchF3Path_MuEle_electron[0]&32)) || ((TriMatchF3Path_MuEle_muon[0]&64 && TriMatchF3Path_MuEle_electron[1]&64) || (TriMatchF3Path_MuEle_muon[1]&64 && TriMatchF3Path_MuEle_electron[0]&64)) || ((TriMatchF3Path_MuEle_muon[0]&128 && TriMatchF3Path_MuEle_electron[1]&128) || (TriMatchF3Path_MuEle_muon[1]&128 && TriMatchF3Path_MuEle_electron[0]&128)) || ((TriMatchF3Path_MuEle_muon[0]&256 && TriMatchF3Path_MuEle_electron[1]&256) || (TriMatchF3Path_MuEle_muon[1]&256 && TriMatchF3Path_MuEle_electron[0]&256)) || ((TriMatchF3Path_MuEle_muon[0]&512 && TriMatchF3Path_MuEle_electron[1]&512) || (TriMatchF3Path_MuEle_muon[1]&512 && TriMatchF3Path_MuEle_electron[0]&512)) || ((TriMatchF3Path_MuEle_muon[0]&1024 && TriMatchF3Path_MuEle_electron[1]&1024) || (TriMatchF3Path_MuEle_muon[1]&1024 && TriMatchF3Path_MuEle_electron[0]&1024)) || ((TriMatchF3Path_MuEle_muon[0]&2048 && TriMatchF3Path_MuEle_electron[1]&2048) || (TriMatchF3Path_MuEle_muon[1]&2048 && TriMatchF3Path_MuEle_electron[0]&2048)) )","SAME");

	TLegend *L2_new_a = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L2_new_a->SetFillColor(0); 
	L2_new_a->SetFillStyle(0); 
	L2_new_a->SetBorderSize(0);
	L2_new_a->AddEntry("h2na","No Trigger");
	L2_new_a->AddEntry("h2naT","With Trigger");
	L2_new_a->AddEntry("h2naTM","#splitline{With new}{TriggerMatching}");
	L2_new_a->Draw();

	TPaveText *T2_new_a = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T2_new_a->SetFillColor(0);
	T2_new_a->SetFillStyle(0);
	T2_new_a->SetBorderSize(1);		
	T2_new_a->AddText("MuEG llM");
	T2_new_a->Draw();

//*****************
	Canva1->cd(5);
	  
	TChain *of_old = new TChain("accepted/events");

	of_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MuEG.root");

	//grafico 4
	of_old->SetLineColor(kBlue+2);
	of_old->SetLineWidth(3);	
	of_old->Draw("llM>>h2oa(50,60,110)","lepChId[0]*lepChId[1]==-2 && jetPt[0]>30");

	//grafico 5
	of_old->SetLineColor(kGreen+2);
	of_old->SetLineWidth(3);
	of_old->Draw("llM>>h2oaT(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-2 && (isTriggered&4))","SAME");

	//grafico 6
	of_old->SetLineColor(kRed+2);
	of_old->SetLineWidth(3);	
	of_old->Draw("llM>>h2oaTM(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-2 && isTriggerMatchedFamily3)", "SAME");

	TLegend *L2_old_a = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L2_old_a->SetFillColor(0); 
	L2_old_a->SetFillStyle(0); 
	L2_old_a->SetBorderSize(0);
	L2_old_a->AddEntry("h2oa","No Trigger");
	L2_old_a->AddEntry("h2oaT","With Trigger");
	L2_old_a->AddEntry("h2oaTM","#splitline{With old}{TriggerMatching}");
	L2_old_a->Draw();

	TPaveText *T2_old_a = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T2_old_a->SetFillColor(0);
	T2_old_a->SetFillStyle(0);
	T2_old_a->SetBorderSize(1);		
	T2_old_a->AddText("MuEG llM");
	T2_old_a->Draw();

//---------------

//*****************
	Canva1->cd(3);

	TChain *ph_new = new TChain("accepted/events");

	ph_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/Photon.root");

	//grafico 4
	ph_new->SetLineColor(kBlue+2);
	ph_new->SetLineWidth(3);	
	ph_new->Draw("photonPt[0]>>h3na(100,0,400)","jetPt[0]>30");

	//grafico 5
	ph_new->SetLineColor(kGreen+2);
	ph_new->SetLineWidth(3);
	ph_new->Draw("photonPt[0]>>h3naT(100,0,400)","jetPt[0]>30 && (isTriggered&8)","SAME");

	//grafico 6
	ph_new->SetLineColor(kRed+2);	
	ph_new->SetLineWidth(3);
	ph_new->Draw("photonPt[0]>>h3naTM(100,0,1000)","jetPt[0]>30 && (TriMatchF4Path_photon[0]&1 || TriMatchF4Path_photon[0]&2 || TriMatchF4Path_photon[0]&4 || TriMatchF4Path_photon[0]&8 || TriMatchF4Path_photon[0]&16 || TriMatchF4Path_photon[0]&32 || TriMatchF4Path_photon[0]&64 || TriMatchF4Path_photon[0]&128 || TriMatchF4Path_photon[0]&256 || TriMatchF4Path_photon[0]&512 || TriMatchF4Path_photon[0]&1024 || TriMatchF4Path_photon[0]&2048 || TriMatchF4Path_photon[0]&4096)","SAME");

	TLegend *L3_new_a = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L3_new_a->SetFillColor(0); 
	L3_new_a->SetFillStyle(0); 
	L3_new_a->SetBorderSize(0);
	L3_new_a->AddEntry("h3na","No Trigger");
	L3_new_a->AddEntry("h3naT","With Trigger");
	L3_new_a->AddEntry("h3naTM","#splitline{With new}{TriggerMatching}");
	L3_new_a->Draw();

	TPaveText *T3_new_a = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T3_new_a->SetFillColor(0);
	T3_new_a->SetFillStyle(0);
	T3_new_a->SetBorderSize(1);		
	T3_new_a->AddText("Photon p_{T}");
	T3_new_a->Draw();


//*****************
	Canva1->cd(6);

	TChain *ph_old = new TChain("accepted/events");

	ph_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/Photon.root");

	//grafico 4
	ph_old->SetLineColor(kBlue+2);
	ph_old->SetLineWidth(3);	
	ph_old->Draw("photonPt[0]>>h3oa(100,0,400)","jetPt[0]>30");

	//grafico 5
	ph_old->SetLineColor(kGreen+2);
	ph_old->SetLineWidth(3);
	ph_old->Draw("photonPt[0]>>h3oaT(100,0,400)","jetPt[0]>30 && (isTriggered&8)","SAME");

	//grafico 6
	ph_old->SetLineColor(kRed+2);	
	ph_old->SetLineWidth(3);
	ph_old->Draw("photonPt[0]>>h3oaTM(100,0,400)","jetPt[0]>30 && isTriggerMatchedFamily4","SAME");

	TLegend *L3_old_a = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L3_old_a->SetFillColor(0); 
	L3_old_a->SetFillStyle(0); 
	L3_old_a->SetBorderSize(0);
	L3_old_a->AddEntry("h3oa","No Trigger");
	L3_old_a->AddEntry("h3oaT","With Trigger");
	L3_old_a->AddEntry("h3oaTM","#splitline{With old}{TriggerMatching}");
	L3_old_a->Draw();

	TPaveText *T3_old_a = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T3_old_a->SetFillColor(0);
	T3_old_a->SetFillStyle(0);
	T3_old_a->SetBorderSize(1);		
	T3_old_a->AddText("Photon p_{T}");
	T3_old_a->Draw();


  Canva1->SaveAs("Canva1.pdf");
  Canva1->SaveAs("Canva1.root");


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//*****************
  TCanvas *Canva2 = new TCanvas("Trigger_Matching_2","Trigger Matching 2");
	Canva2->Divide(3,2);


	Canva2->cd(1);

	TChain *DY_new = new TChain("accepted/events");

	DY_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MC_DYJetsToLL_M-50.root");
	
	//grafico 1
	DY_new->SetLineColor(kBlue+2);
	DY_new->SetLineWidth(3);	
	DY_new->Draw("llM>>h1nb(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-4 || lepChId[0]*lepChId[1]==-1)");

	//grafico 2
	DY_new->SetLineColor(kGreen+2);
	DY_new->SetLineWidth(3);		
	DY_new->Draw("llM>>h1nbT(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && isTriggered&1) || (lepChId[0]*lepChId[1]==-1 && isTriggered&2))","SAME");

	//grafico 3
	DY_new->SetLineColor(kRed+2);
	DY_new->SetLineWidth(3);		
	DY_new->Draw("llM>>h1nbTM(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && ((TriMatchF1Path_doubleMu[0]&1 && TriMatchF1Path_doubleMu[1]&1) || (TriMatchF1Path_doubleMu[0]&2 && TriMatchF1Path_doubleMu[1]&2) || (TriMatchF1Path_doubleMu[0]&4 && TriMatchF1Path_doubleMu[1]&4) || (TriMatchF1Path_doubleMu[0]&8 && TriMatchF1Path_doubleMu[1]&8))) || (lepChId[0]*lepChId[1]==-1 && ((TriMatchF2Path_doubleEle[0]&1 && TriMatchF2Path_doubleEle[1]&1) || (TriMatchF2Path_doubleEle[0]&2 && TriMatchF2Path_doubleEle[1]&2))))","SAME");

	TLegend *L1_new_b = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L1_new_b->SetFillColor(0); 
	L1_new_b->SetFillStyle(0); 
	L1_new_b->SetBorderSize(0);
	L1_new_b->AddEntry("h1nb","No Trigger");
	L1_new_b->AddEntry("h1nbT","With Trigger");
	L1_new_b->AddEntry("h1nbTM","#splitline{With new}{TriggerMatching}");
	L1_new_b->Draw();

	TPaveText *T1_new_b = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T1_new_b->SetFillColor(0);
	T1_new_b->SetFillStyle(0);
	T1_new_b->SetBorderSize(1);		
	T1_new_b->AddText("DYJetsToLL_M-50 llM");
	T1_new_b->Draw();

//*****************
	Canva2->cd(4);
	
	TChain *DY_old = new TChain("accepted/events");

	DY_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MC_DYJetsToLL_M-50.root");
	
	//grafico 1
	DY_old->SetLineColor(kBlue+2);
	DY_old->SetLineWidth(3);	
	DY_old->Draw("llM>>h1ob(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-4 || lepChId[0]*lepChId[1]==-1)");

	//grafico 2
	DY_old->SetLineColor(kGreen+2);
	DY_old->SetLineWidth(3);		
	DY_old->Draw("llM>>h1obT(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && isTriggered&1) || (lepChId[0]*lepChId[1]==-1 && isTriggered&2))","SAME");

	//grafico 3
	DY_old->SetLineColor(kRed+2);
	DY_old->SetLineWidth(3);		
	DY_old->Draw("llM>>h1obTM(50,60,110)","jetPt[0]>30 && ((lepChId[0]*lepChId[1]==-4 && isTriggerMatchedFamily1) || (lepChId[0]*lepChId[1]==-1 && isTriggerMatchedFamily2))", "SAME");

	TLegend *L1_old_b = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L1_old_b->SetFillColor(0); 
	L1_old_b->SetFillStyle(0); 
	L1_old_b->SetBorderSize(0);
	L1_old_b->AddEntry("h1ob","No Trigger");
	L1_old_b->AddEntry("h1obT","With Trigger");
	L1_old_b->AddEntry("h1obTM","#splitline{With old}{TriggerMatching}");
	L1_old_b->Draw();

	TPaveText *T1_old_b = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T1_old_b->SetFillColor(0);
	T1_old_b->SetFillStyle(0);
	T1_old_b->SetBorderSize(1);		
	T1_old_b->AddText("DYJetsToLL_M-50 llM");
	T1_old_b->Draw();

//---------------

//*****************
	Canva2->cd(2);
	  
	TChain *TT_new = new TChain("accepted/events");

	TT_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MC_TTJets_FullLeptMGDecays.root");

	//grafico 4
	TT_new->SetLineColor(kBlue+2);
	TT_new->SetLineWidth(3);	
	TT_new->Draw("llM>>h2nb(50,60,110)","lepChId[0]*lepChId[1]==-2 && jetPt[0]>30");

	//grafico 5
	TT_new->SetLineColor(kGreen+2);
	TT_new->SetLineWidth(3);
	TT_new->Draw("llM>>h2nbT(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-2 && (isTriggered&4))","SAME");

	//grafico 6
	TT_new->SetLineColor(kRed+2);
	TT_new->SetLineWidth(3);	
	TT_new->Draw("llM>>h2nbTM(50,60,110)","(lepChId[0]*lepChId[1]==-2 && jetPt[0]>30) && (((TriMatchF3Path_MuEle_muon[0]&1 && TriMatchF3Path_MuEle_electron[1]&1) || (TriMatchF3Path_MuEle_muon[1]&1 && TriMatchF3Path_MuEle_electron[0]&1)) || ((TriMatchF3Path_MuEle_muon[0]&2 && TriMatchF3Path_MuEle_electron[1]&2) || (TriMatchF3Path_MuEle_muon[1]&2 && TriMatchF3Path_MuEle_electron[0]&2)) || ((TriMatchF3Path_MuEle_muon[0]&4 && TriMatchF3Path_MuEle_electron[1]&4) || (TriMatchF3Path_MuEle_muon[1]&4 && TriMatchF3Path_MuEle_electron[0]&4)) || ((TriMatchF3Path_MuEle_muon[0]&8 && TriMatchF3Path_MuEle_electron[1]&8) || (TriMatchF3Path_MuEle_muon[1]&8 && TriMatchF3Path_MuEle_electron[0]&8)) || ((TriMatchF3Path_MuEle_muon[0]&16 && TriMatchF3Path_MuEle_electron[1]&16) || (TriMatchF3Path_MuEle_muon[1]&16 && TriMatchF3Path_MuEle_electron[0]&16)) || ((TriMatchF3Path_MuEle_muon[0]&32 && TriMatchF3Path_MuEle_electron[1]&32) || (TriMatchF3Path_MuEle_muon[1]&32 && TriMatchF3Path_MuEle_electron[0]&32)) || ((TriMatchF3Path_MuEle_muon[0]&64 && TriMatchF3Path_MuEle_electron[1]&64) || (TriMatchF3Path_MuEle_muon[1]&64 && TriMatchF3Path_MuEle_electron[0]&64)) || ((TriMatchF3Path_MuEle_muon[0]&128 && TriMatchF3Path_MuEle_electron[1]&128) || (TriMatchF3Path_MuEle_muon[1]&128 && TriMatchF3Path_MuEle_electron[0]&128)) || ((TriMatchF3Path_MuEle_muon[0]&256 && TriMatchF3Path_MuEle_electron[1]&256) || (TriMatchF3Path_MuEle_muon[1]&256 && TriMatchF3Path_MuEle_electron[0]&256)) || ((TriMatchF3Path_MuEle_muon[0]&512 && TriMatchF3Path_MuEle_electron[1]&512) || (TriMatchF3Path_MuEle_muon[1]&512 && TriMatchF3Path_MuEle_electron[0]&512)) || ((TriMatchF3Path_MuEle_muon[0]&1024 && TriMatchF3Path_MuEle_electron[1]&1024) || (TriMatchF3Path_MuEle_muon[1]&1024 && TriMatchF3Path_MuEle_electron[0]&1024)) || ((TriMatchF3Path_MuEle_muon[0]&2048 && TriMatchF3Path_MuEle_electron[1]&2048) || (TriMatchF3Path_MuEle_muon[1]&2048 && TriMatchF3Path_MuEle_electron[0]&2048)) )","SAME");

	TLegend *L2_new_b = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L2_new_b->SetFillColor(0); 
	L2_new_b->SetFillStyle(0); 
	L2_new_b->SetBorderSize(0);
	L2_new_b->AddEntry("h2nb","No Trigger");
	L2_new_b->AddEntry("h2nbT","With Trigger");
	L2_new_b->AddEntry("h2nbTM","#splitline{With new}{TriggerMatching}");
	L2_new_b->Draw();

	TPaveText *T2_new_b = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T2_new_b->SetFillColor(0);
	T2_new_b->SetFillStyle(0);
	T2_new_b->SetBorderSize(1);		
	T2_new_b->AddText("TTJets_FullLeptMGDecays llM");
	T2_new_b->Draw();

//*****************
	Canva2->cd(5);
	  
	TChain *TT_old = new TChain("accepted/events");

	TT_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MC_TTJets_FullLeptMGDecays.root");

	//grafico 4
	TT_old->SetLineColor(kBlue+2);
	TT_old->SetLineWidth(3);	
	TT_old->Draw("llM>>h2ob(50,60,110)","lepChId[0]*lepChId[1]==-2 && jetPt[0]>30");

	//grafico 5
	TT_old->SetLineColor(kGreen+2);
	TT_old->SetLineWidth(3);
	TT_old->Draw("llM>>h2obT(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-2 && (isTriggered&4))","SAME");

	//grafico 6
	TT_old->SetLineColor(kRed+2);
	TT_old->SetLineWidth(3);	
	TT_old->Draw("llM>>h2obTM(50,60,110)","jetPt[0]>30 && (lepChId[0]*lepChId[1]==-2 && isTriggerMatchedFamily3)", "SAME");

	TLegend *L2_old_b = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L2_old_b->SetFillColor(0); 
	L2_old_b->SetFillStyle(0); 
	L2_old_b->SetBorderSize(0);
	L2_old_b->AddEntry("h2ob","No Trigger");
	L2_old_b->AddEntry("h2obT","With Trigger");
	L2_old_b->AddEntry("h2obTM","#splitline{With old}{TriggerMatching}");
	L2_old_b->Draw();

	TPaveText *T2_old_b = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T2_old_b->SetFillColor(0);
	T2_old_b->SetFillStyle(0);
	T2_old_b->SetBorderSize(1);		
	T2_old_b->AddText("TTJets_FullLeptMGDecays llM");
	T2_old_b->Draw();

//---------------

//*****************
	Canva2->cd(3);

	TChain *GJ_new = new TChain("accepted/events");

	GJ_new->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_07_08_TriMatchTest/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MC_GJets_HT-200To400.root");

	//grafico 4
	GJ_new->SetLineColor(kBlue+2);
	GJ_new->SetLineWidth(3);	
	GJ_new->Draw("photonPt[0]>>h3nb(100,0,400)","jetPt[0]>30");

	//grafico 5
	GJ_new->SetLineColor(kGreen+2);
	GJ_new->SetLineWidth(3);
	GJ_new->Draw("photonPt[0]>>h3nbT(100,0,400)","jetPt[0]>30 && (isTriggered&8)","SAME");

	//grafico 6
	GJ_new->SetLineColor(kRed+2);	
	GJ_new->SetLineWidth(3);
	GJ_new->Draw("photonPt[0]>>h3nbTM(100,0,1000)","jetPt[0]>30 && (TriMatchF4Path_photon[0]&1 || TriMatchF4Path_photon[0]&2 || TriMatchF4Path_photon[0]&4 || TriMatchF4Path_photon[0]&8 || TriMatchF4Path_photon[0]&16 || TriMatchF4Path_photon[0]&32 || TriMatchF4Path_photon[0]&64 || TriMatchF4Path_photon[0]&128 || TriMatchF4Path_photon[0]&256 || TriMatchF4Path_photon[0]&512 || TriMatchF4Path_photon[0]&1024 || TriMatchF4Path_photon[0]&2048 || TriMatchF4Path_photon[0]&4096)","SAME");

	TLegend *L3_new_b = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L3_new_b->SetFillColor(0); 
	L3_new_b->SetFillStyle(0); 
	L3_new_b->SetBorderSize(0);
	L3_new_b->AddEntry("h3nb","No Trigger");
	L3_new_b->AddEntry("h3nbT","With Trigger");
	L3_new_b->AddEntry("h3nbTM","#splitline{With new}{TriggerMatching}");
	L3_new_b->Draw();

	TPaveText *T3_new_b = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T3_new_b->SetFillColor(0);
	T3_new_b->SetFillStyle(0);
	T3_new_b->SetBorderSize(1);		
	T3_new_b->AddText("GJets_HT-200To400 p_{T}");
	T3_new_b->Draw();


//*****************
	Canva2->cd(6);

	TChain *GJ_old = new TChain("accepted/events");

	GJ_old->Add("/data/sandro/Analisi/GammaJets/CMSSW_5_3_6xxx2013_06_17_control/CMSSW_5_3_6/src/amarini/VPlusJets/test/test_TriMatch/MC_GJets_HT-200To400.root");

	//grafico 4
	GJ_old->SetLineColor(kBlue+2);
	GJ_old->SetLineWidth(3);	
	GJ_old->Draw("photonPt[0]>>h3ob(100,0,400)","jetPt[0]>30");

	//grafico 5
	GJ_old->SetLineColor(kGreen+2);
	GJ_old->SetLineWidth(3);
	GJ_old->Draw("photonPt[0]>>h3obT(100,0,400)","jetPt[0]>30 && (isTriggered&8)","SAME");

	//grafico 6
	GJ_old->SetLineColor(kRed+2);	
	GJ_old->SetLineWidth(3);
	GJ_old->Draw("photonPt[0]>>h3obTM(100,0,400)","jetPt[0]>30 && isTriggerMatchedFamily4","SAME");

	TLegend *L3_old_b = new TLegend(0.6382, 0.4859, 0.8913, 0.8800);
	L3_old_b->SetFillColor(0); 
	L3_old_b->SetFillStyle(0); 
	L3_old_b->SetBorderSize(0);
	L3_old_b->AddEntry("h3ob","No Trigger");
	L3_old_b->AddEntry("h3obT","With Trigger");
	L3_old_b->AddEntry("h3obTM","#splitline{With old}{TriggerMatching}");
	L3_old_b->Draw();

	TPaveText *T3_old_b = new TPaveText(0.0079, 0.9395, 0.7085, 0.9958,"NDC");
	T3_old_b->SetFillColor(0);
	T3_old_b->SetFillStyle(0);
	T3_old_b->SetBorderSize(1);		
	T3_old_b->AddText("GJets_HT-200To400 p_{T}");
	T3_old_b->Draw();


  Canva2->SaveAs("Canva2.pdf");
  Canva2->SaveAs("Canva2.root");


}
