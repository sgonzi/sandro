#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <string>
#include <stdio.h>
#include <TH1.h>
#include <THStack.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TPad.h>
#include <TBox.h>
#include <TLine.h>
#include <sstream>
#include <fstream>

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "FWCore/Utilities/interface/Exception.h"
#endif


void setMYStyle() {

  TStyle *myStyle = new TStyle("MYStyle","My Style");

// For the canvas:
  myStyle->SetCanvasBorderMode(0);
  myStyle->SetCanvasColor(kWhite);
  myStyle->SetCanvasDefH(600); //Height of canvas
  myStyle->SetCanvasDefW(600); //Width of canvas
  myStyle->SetCanvasDefX(0);   //POsition on screen
  myStyle->SetCanvasDefY(0);

// For the Pad:
  myStyle->SetPadBorderMode(0);
  myStyle->SetPadColor(kWhite);
  myStyle->SetPadGridX(false);
  myStyle->SetPadGridY(false);
  myStyle->SetGridColor(0);
  myStyle->SetGridStyle(3);
  myStyle->SetGridWidth(1);

// For the frame:
  myStyle->SetFrameBorderMode(0);
  myStyle->SetFrameBorderSize(1);
  myStyle->SetFrameFillColor(0);
  myStyle->SetFrameFillStyle(0);
  myStyle->SetFrameLineColor(1);
  myStyle->SetFrameLineStyle(1);
  myStyle->SetFrameLineWidth(1);

// For the histo:
  myStyle->SetHistLineColor(1);
  myStyle->SetHistLineStyle(0);
  myStyle->SetHistLineWidth(1);
  myStyle->SetEndErrorSize(2);
  myStyle->SetErrorX(0.);
  myStyle->SetMarkerStyle(20);

//For the fit/function:
  myStyle->SetOptFit(1);
  myStyle->SetFitFormat("5.4g");
  myStyle->SetFuncColor(2);
  myStyle->SetFuncStyle(1);
  myStyle->SetFuncWidth(1);

//For the date:
  myStyle->SetOptDate(0);

// For the statistics box:
  myStyle->SetOptFile(0);
  myStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  myStyle->SetStatColor(kWhite);
  myStyle->SetStatFont(42);
  myStyle->SetStatFontSize(0.025);
  myStyle->SetStatTextColor(1);
  myStyle->SetStatFormat("6.4g");
  myStyle->SetStatBorderSize(1);
  myStyle->SetStatH(0.1);
  myStyle->SetStatW(0.15);

// Margins:
  myStyle->SetPadTopMargin(0.07);
  myStyle->SetPadBottomMargin(0.13);
  myStyle->SetPadLeftMargin(0.13);
  myStyle->SetPadRightMargin(0.13);

// For the Global title:
  myStyle->SetOptTitle(0);
  myStyle->SetTitleFont(42);
  myStyle->SetTitleColor(1);
  myStyle->SetTitleTextColor(1);
  myStyle->SetTitleFillColor(10);
  myStyle->SetTitleFontSize(0.05);

// For the axis titles:
  myStyle->SetTitleColor(1, "XYZ");
  myStyle->SetTitleFont(42, "XYZ");
  myStyle->SetTitleSize(0.06, "XYZ");
  myStyle->SetTitleXOffset(0.9);
  myStyle->SetTitleYOffset(1.);

// For the axis labels:
  myStyle->SetLabelColor(1, "XYZ");
  myStyle->SetLabelFont(42, "XYZ");
  myStyle->SetLabelOffset(0.007, "XYZ");
  myStyle->SetLabelSize(0.045, "XYZ");

// For the axis:
  myStyle->SetAxisColor(1, "XYZ");
  myStyle->SetStripDecimals(kTRUE);
  myStyle->SetTickLength(0.03, "XYZ");
  myStyle->SetNdivisions(510, "XYZ");
  myStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  myStyle->SetPadTickY(1);

// Change for log plots:
  myStyle->SetOptLogx(0);
  myStyle->SetOptLogy(0);
  myStyle->SetOptLogz(0);

// Postscript options:
  myStyle->SetPaperSize(20.,20.);

  myStyle->cd();
}


void ZGenPlots(const char* titleh, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L GenPlots.C++
  //       ie: GenPlots("HTParSum_","H_{T} Partons Sum", 1, 0, 100);

	setMYStyle();

	// ==================================== choose the tools

	string folder = "13_results_2013_07_22"; // analysis folder

	char geo[100] = "barrel";               // "barrel", "endcaps" or "total"

	bool data_ReReco = true;                // true: data = ReReco
	                                         // false: data = PromptReco
	Int_t itype = 13;                        // it identifies histos with different analysis 


	// ==================================== string names

	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string folder_s = folder + "/";
	string GEN_folder;
	GEN_folder = "Gen_plots/";
	string out_files = "output_files/";
	string pdf_folder = "pdf_plots/";
	string pdf_string = ".pdf";
	string root_folder = "root_plots/";
	string root_string = ".root";
	string txt_folder = "txt_plots/";
	string txt_string = ".txt";
	
	stringstream ss_r;
	char root_char[100];
	ss_r << root_string;
	ss_r >> root_char;

	string address = folder_s + geo_s + out_files;


	// ==================================== assign files names

	Char_t DYJetsToLL_M_50_name[100];	

	sprintf(DYJetsToLL_M_50_name,"DYJetsToLL_M_50_histos_%d_%s%s",itype, geo, root_char);	

	cout << "DYJets file 91 is: " << DYJetsToLL_M_50_name << endl;


	// ==================================== load TFiles

	TFile *DYJetsToLL_M_50_file;

	DYJetsToLL_M_50_file = new TFile((address+DYJetsToLL_M_50_name).c_str());	


	// ==================================== load TH1F

	Char_t titlehisto[100];

	strcpy(titlehisto,titleh);

	cout << "========================" <<endl;	
	cout << endl;	

	cout << "Analyzing Histogram " << titlehisto << endl;

	cout << endl;	
	cout << "========================" <<endl;	
	cout << endl;	


	TH1F *DYJetsToLL_M_50_histo;
	TH1F *DYJetsToLL_M_50_total_histo;
			
	//--- MC signal DYJetsToLL_M_50 ----------------------------------------------
	DYJetsToLL_M_50_histo=(TH1F*)DYJetsToLL_M_50_file->Get(titlehisto);
	DYJetsToLL_M_50_histo->Rebin(rebin);
		
	DYJetsToLL_M_50_total_histo = (TH1F*) DYJetsToLL_M_50_histo->Clone("DYJetsToLL_M_50_total_histo");
	//--- DYJetsToLL_M_50_total_histo->Sumw2();
	DYJetsToLL_M_50_total_histo->SetLineColor(kBlack);
	DYJetsToLL_M_50_total_histo->SetLineWidth(3);
	//DYJetsToLL_M_50_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	// ==================================== print Entries number

	cout << "========================" <<endl;	
	cout << endl;
	
	cout << "DYJets total entries = " << DYJetsToLL_M_50_total_histo->Integral() << endl;  

	cout << endl;
	cout << "========================" <<endl;	
	cout << endl;
		
	// ==================================== load Canvas
	
  TCanvas *Canva = new TCanvas(titlehisto,titlehisto);  

	int Nbins;
	double X_min, X_max;

	
	Nbins =	DYJetsToLL_M_50_total_histo->GetNbinsX();
	
	if (x_min != -999 && x_max != -999){
		if (x_max == DYJetsToLL_M_50_total_histo->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == DYJetsToLL_M_50_total_histo->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		DYJetsToLL_M_50_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);
	}

	//signal
	DYJetsToLL_M_50_total_histo->Draw();

	gPad->SetLogy();

	DYJetsToLL_M_50_total_histo->GetXaxis()->SetTitle(namevariable);
	DYJetsToLL_M_50_total_histo->GetXaxis()->SetTitleSize(0.05);
	DYJetsToLL_M_50_total_histo->GetYaxis()->SetTitleOffset(1.2);
	DYJetsToLL_M_50_total_histo->GetYaxis()->SetTitle("Events");


	TLegend *leg =new TLegend(0.6068,0.5478,0.8188,0.7480);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	leg->AddEntry(DYJetsToLL_M_50_total_histo,"Z + jets - MAD","l");
	leg->Draw();

  TPaveText* text = new TPaveText(0.6068,0.7722,0.8188,0.8571,"NDC");
  text->SetFillColor(0);
  text->SetFillStyle(0);
  text->SetBorderSize(0);
  text->AddText("CMS Simulation");
  if (data_ReReco) text->AddText("#sqrt{s} = 8 TeV, L = 19.79 fb^{-1}");
  else text->AddText("#sqrt{s} = 8 TeV, L = 19.03 fb^{-1}");
  text->SetTextAlign(11);
  text->Draw();

	
	root_string = ".root";
	pdf_string = ".pdf";
  Canva->SaveAs((folder_s + geo_s + GEN_folder + pdf_folder + titleh + pdf_string).c_str());
  Canva->SaveAs((folder_s + geo_s + GEN_folder + root_folder + titleh + root_string).c_str());
	Canva->Close();

	// ==================================== report

	cout << "Writing report file... " << endl;
	ofstream report;
	
	stringstream ss_t;
	char txt_char[100];
	ss_t << folder_s + geo_s + GEN_folder + txt_folder + titleh + txt_string;
	ss_t >> txt_char;
	
	report.open(txt_char);

	report << endl;
	report << endl;
	
	report << "DYJets file 91 is: " << DYJetsToLL_M_50_name << endl;
	
	report << endl;
	report << "========================" <<endl;	
	report << endl;	

	report << "DYJetsToLL_M_50 entries = " << DYJetsToLL_M_50_histo->Integral() << endl;

	report << endl;
	report << "========================" <<endl;	
	report << endl;	
	
	report << "ZJets total entries = " << DYJetsToLL_M_50_total_histo->Integral() << endl;  
	report << endl;
	
	report.close();
	cout << "...writing report file finished. " << endl;

	// ==================================== close files

	DYJetsToLL_M_50_file->Close();	
	
}


void ZGenPlots_01() {		
	ZGenPlots("nLeptonsGEN_mumu_","Leptons GEN N (Z->#mu#mu)", 1, 0, 10);
	ZGenPlots("lepPtGEN_mumu_1_", "lepton 1 GEN p_{T} (Z->#mu#mu)", 1, 0, 1000);
	ZGenPlots("lepEGEN_mumu_1_", "lepton 1 GEN E (Z->#mu#mu)", 1, 0, 1000);
	ZGenPlots("lepEtaGEN_mumu_1_", "lepton 1 GEN #eta (Z->#mu#mu)", 30, -1.5, 1.5);
	ZGenPlots("lepPhiGEN_mumu_1_", "lepton 1 GEN #phi (Z->#mu#mu)", 20, -999, -999);
}

void ZGenPlots_02(){		
	ZGenPlots("lepPtGEN_mumu_2_", "lepton 2 GEN p_{T} (Z->#mu#mu)", 1, 0, 1000);
	ZGenPlots("lepEGEN_mumu_2_", "lepton 2 GEN E (Z->#mu#mu)", 1, 0, 1000);
	ZGenPlots("lepEtaGEN_mumu_2_", "lepton 2 GEN #eta (Z->#mu#mu)", 30, -1.5, 1.5);
	ZGenPlots("lepPhiGEN_mumu_2_", "lepton 2 GEN #phi (Z->#mu#mu)", 20, -999, -999);
}

void ZGenPlots_03(){		
	ZGenPlots("llMGEN_mumu_", "M^{ll} GEN (Z->#mu#mu)", 5, -999, -999);
	// ZGenPlots("llPtGEN_mumu_", "p_{T}^{ll} GEN (Z->#mu#mu)", 2, 0, 1000);
	ZGenPlots("llPtGEN_mumu_", "p_{T}^{ll} GEN (Z->#mu#mu)", 1, 0, 1000);
	ZGenPlots("llEtaGEN_mumu_", "#eta^{ll} GEN (Z->#mu#mu)", 30, -1.5, 1.5);
	ZGenPlots("llPhiGEN_mumu_", "#phi^{ll} GEN (Z->#mu#mu)", 20, -999, -999);
}

void ZGenPlots_04(){		
	ZGenPlots("SelectedJetsGEN_N_mumu_","Selected Jets GEN N (Z->#mu#mu)", 1, -999, -999);
	ZGenPlots("SelectedJets_PtGEN_mumu_1_","Jet 1 GEN p_{T} (Z->#mu#mu)", 2, 0, 1000);
	ZGenPlots("SelectedJets_EGEN_mumu_1_", "Jet 1 GEN E (Z->#mu#mu)", 2, 0, 1000);
	ZGenPlots("SelectedJets_EtaGEN_mumu_1_","Jet 1 GEN #eta (Z->#mu#mu)", 50, -3, 3);
	ZGenPlots("SelectedJets_PhiGEN_mumu_1_","Jet 1 GEN #varphi (Z->#mu#mu)", 20, -999, -999);
	ZGenPlots("SelectedJetsGEN_HT_mumu_","Selected Jets H_{T} GEN (Z->#mu#mu)", 4, 0, 2000);
}

void ZGenPlots_05(){		
	ZGenPlots("nLeptonsGEN_ee_","Leptons GEN N (Z->ee)", 1, 0, 10);
	ZGenPlots("lepPtGEN_ee_1_", "lepton 1 GEN p_{T} (Z->ee)", 1, 0, 1000);
	ZGenPlots("lepEGEN_ee_1_", "lepton 1 GEN E (Z->ee)", 1, 0, 1000);
	ZGenPlots("lepEtaGEN_ee_1_", "lepton 1 GEN #eta (Z->ee)", 30, -1.5, 1.5);
	ZGenPlots("lepPhiGEN_ee_1_", "lepton 1 GEN #phi (Z->ee)", 20, -999, -999);
}

void ZGenPlots_06(){		
	ZGenPlots("lepPtGEN_ee_2_", "lepton 2 GEN p_{T} (Z->ee)", 1, 0, 1000);
	ZGenPlots("lepEGEN_ee_2_", "lepton 2 GEN E (Z->ee)", 1, 0, 1000);
	ZGenPlots("lepEtaGEN_ee_2_", "lepton 2 GEN #eta (Z->ee)", 30, -1.5, 1.5);
	ZGenPlots("lepPhiGEN_ee_2_", "lepton 2 GEN #phi (Z->ee)", 20, -999, -999);
}

void ZGenPlots_07(){		
	ZGenPlots("llMGEN_ee_", "M^{ll} GEN (Z->ee)",  5, -999, -999);
	// ZGenPlots("llPtGEN_ee_", "p_{T}^{ll} GEN (Z->ee)", 2, 0, 1000); 
	ZGenPlots("llPtGEN_ee_", "p_{T}^{ll} GEN (Z->ee)", 1, 0, 1000); 
	ZGenPlots("llEtaGEN_ee_", "#eta^{ll} GEN (Z->ee)", 30, -1.5, 1.5);
	ZGenPlots("llPhiGEN_ee_", "#phi^{ll} GEN (Z->ee)", 20, -999, -999);
}


void ZGenPlots_08(){		
	ZGenPlots("SelectedJetsGEN_N_ee_","Selected Jets GEN N (Z->ee)", 1, -999, -999);
	ZGenPlots("SelectedJets_PtGEN_ee_1_","Jet 1 GEN p_{T} (Z->ee)", 2, 0, 1000);
	ZGenPlots("SelectedJets_EGEN_ee_1_", "Jet 1 GEN E (Z->ee)", 2, 0, 1000);
	ZGenPlots("SelectedJets_EtaGEN_ee_1_","Jet 1 GEN #eta (Z->ee)", 50, -3, 3);
	ZGenPlots("SelectedJets_PhiGEN_ee_1_","Jet 1 GEN #varphi (Z->ee)", 20, -999, -999);
	ZGenPlots("SelectedJetsGEN_HT_ee_","Selected Jets H_{T} GEN (Z->ee)", 4, 0, 2000);
}

void ZGenPlots_09(){		
	ZGenPlots("nLeptonsGEN_ll_","Leptons GEN N (Z->ll)", 1, 0, 10);
	ZGenPlots("lepPtGEN_ll_1_", "lepton 1 GEN p_{T} (Z->ll)", 1, 0, 1000);
	ZGenPlots("lepEGEN_ll_1_", "lepton 1 GEN E (Z->ll)", 1, 0, 1000);
	ZGenPlots("lepEtaGEN_ll_1_", "lepton 1 GEN #eta (Z->ll)", 30, -1.5, 1.5);
	ZGenPlots("lepPhiGEN_ll_1_", "lepton 1 GEN #phi (Z->ll)", 20, -999, -999);
}

void ZGenPlots_10(){		
	ZGenPlots("lepPtGEN_ll_2_", "lepton 2 GEN p_{T} (Z->ll)", 1, 0, 1000);
	ZGenPlots("lepEGEN_ll_2_", "lepton 2 GEN E (Z->ll)", 1, 0, 1000);
	ZGenPlots("lepEtaGEN_ll_2_", "lepton 2 GEN #eta (Z->ll)", 30, -1.5, 1.5);
	ZGenPlots("lepPhiGEN_ll_2_", "lepton 2 GEN #phi (Z->ll)", 20, -999, -999);
}

void ZGenPlots_11(){		
	ZGenPlots("llMGEN_ll_", "M^{ll} GEN (Z->ll)",  5, -999, -999);
	// ZGenPlots("llPtGEN_ll_", "p_{T}^{ll} GEN (Z->ll)", 2, 0, 1000); 
	ZGenPlots("llPtGEN_ll_", "p_{T}^{ll} GEN (Z->ll)", 1, 0, 1000); 
	ZGenPlots("llEtaGEN_ll_", "#eta^{ll} GEN (Z->ll)", 30, -1.5, 1.5);
	ZGenPlots("llPhiGEN_ll_", "#phi^{ll} GEN (Z->ll)", 20, -999, -999);
}

void ZGenPlots_12(){		
	ZGenPlots("SelectedJetsGEN_N_ll_","Selected Jets GEN N (Z->ll)", 1, -999, -999);
	ZGenPlots("SelectedJets_PtGEN_ll_1_","Jet 1 GEN p_{T} (Z->ll)", 2, 0, 1000);
	ZGenPlots("SelectedJets_EGEN_ll_1_", "Jet 1 GEN E (Z->ll)", 2, 0, 1000);
	ZGenPlots("SelectedJets_EtaGEN_ll_1_","Jet 1 GEN #eta (Z->ll)", 50, -3, 3);
	ZGenPlots("SelectedJets_PhiGEN_ll_1_","Jet 1 GEN #varphi (Z->ll)", 20, -999, -999);
	ZGenPlots("SelectedJetsGEN_HT_ll_","Selected Jets H_{T} GEN (Z->ll)", 4, 0, 2000);
}

void ZGenPlots_13(){		
	ZGenPlots("HTParSum_","H_{T} Partons Sum", 2, 0, 2000);
}

void ZGenPlots_TOT(){	
	ZGenPlots_01();
	ZGenPlots_02();
	ZGenPlots_03();
	ZGenPlots_04();
	ZGenPlots_05();
	ZGenPlots_06();
	ZGenPlots_07();
	ZGenPlots_08();
	ZGenPlots_09();
	ZGenPlots_10();
	ZGenPlots_11();
	ZGenPlots_12();
	ZGenPlots_13();	
}

