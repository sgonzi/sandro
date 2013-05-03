// 
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


void fitSidebands(const char* titleh, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L comparestack.C+
  //       ie: comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 1);

	char geo[10] = "barrel"; // "barrel", "endcaps" or "total"
	Int_t itype = 9; // identifica histo con analisi diverse
	string sample = "MC"; // "DATA" or "MC"

	setMYStyle();

//	string DATA_Run2012A_13Jul2012_name;
	Char_t DATA_Run2012A_13Jul2012_name[100];
	Char_t DATA_Run2012A_recover_06Aug2012_name[100];
	Char_t DATA_Run2012B_13Jul2012_name[100];
	Char_t DATA_Run2012C_24Aug2012_name[100];
	Char_t DATA_Run2012C_EcalRecover_11Dec2012_name[100];
	Char_t DATA_Run2012C_PromptReco_name[100];
	Char_t DATA_Run2012D_PromptReco_name[100];
						
	Char_t GJets_HT_200To400_name[100];
	Char_t GJets_HT_400ToInf_name[100];
	
	Char_t QCD_Pt_20_30_EMEnriched_name[100];
	Char_t QCD_Pt_30_80_EMEnriched_name[100];
	Char_t QCD_Pt_80_170_EMEnriched_name[100];
	Char_t QCD_Pt_170_250_EMEnriched_name[100];
	Char_t QCD_Pt_250_350_EMEnriched_name[100];
	Char_t QCD_Pt_350_EMEnriched_name[100];

	Char_t QCD_Pt_20_30_BCtoE_name[100];
	Char_t QCD_Pt_30_80_BCtoE_name[100];
	Char_t QCD_Pt_80_170_BCtoE_name[100];
	Char_t QCD_Pt_170_250_BCtoE_name[100];
	Char_t QCD_Pt_250_350_BCtoE_name[100];
	Char_t QCD_Pt_350_BCtoE_name[100];

/*
	Char_t QCD_HT_100To250_name[100];
	Char_t QCD_HT_250To500_name[100];
	Char_t QCD_HT_500To1000_name[100];
	Char_t QCD_HT_1000ToInf_name[100];
*/

	stringstream ss;
	string Geo;
	ss << geo;
	ss >> Geo;
	string geo_s = Geo + "/";
	string out_files = "output_files/";
	string pdf_folder = "fit_pdf_plots/";
	string pdf_string = ".pdf";
	string root_folder = "fit_root_plots/";
	string root_string = ".root";

	sprintf(DATA_Run2012A_13Jul2012_name,"DATA_Run2012A-13Jul2012_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 1 is " << DATA_Run2012A_13Jul2012_name << endl;
	sprintf(DATA_Run2012A_recover_06Aug2012_name,"DATA_Run2012A-recover-06Aug2012_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 2 is " << DATA_Run2012A_recover_06Aug2012_name << endl;
	sprintf(DATA_Run2012B_13Jul2012_name,"DATA_Run2012B-13Jul2012_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 3 is " << DATA_Run2012B_13Jul2012_name << endl;
	sprintf(DATA_Run2012C_24Aug2012_name,"DATA_Run2012C-24Aug2012_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 4 is " << DATA_Run2012C_24Aug2012_name << endl;
	sprintf(DATA_Run2012C_EcalRecover_11Dec2012_name,"DATA_Run2012C-EcalRecover_11Dec2012_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 5 is " << DATA_Run2012C_EcalRecover_11Dec2012_name << endl;
	sprintf(DATA_Run2012C_PromptReco_name,"DATA_Run2012C-PromptReco_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 6 is " << DATA_Run2012C_PromptReco_name << endl;
	sprintf(DATA_Run2012D_PromptReco_name,"DATA_Run2012D-PromptReco_histos_%d_inverted_%s.root",itype, geo);
	cout << "data file 7 is " << DATA_Run2012D_PromptReco_name << endl;


	sprintf(GJets_HT_200To400_name,"MC_GJets_HT-200To400_histos_%d_inverted_%s.root",itype, geo);
	cout << "GJets file 11 is: " << GJets_HT_200To400_name << endl;
	sprintf(GJets_HT_400ToInf_name,"MC_GJets_HT-400ToInf_histos_%d_inverted_%s.root",itype, geo);
	cout << "GJets file 12 is: " << GJets_HT_400ToInf_name << endl;
	sprintf(QCD_Pt_20_30_EMEnriched_name,"MC_QCD_Pt_20_30_EMEnriched_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 21 is: " << QCD_Pt_20_30_EMEnriched_name << endl;
	sprintf(QCD_Pt_30_80_EMEnriched_name,"MC_QCD_Pt_30_80_EMEnriched_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 22 is: " << QCD_Pt_30_80_EMEnriched_name << endl;
	sprintf(QCD_Pt_80_170_EMEnriched_name,"MC_QCD_Pt_80_170_EMEnriched_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 23 is: " << QCD_Pt_80_170_EMEnriched_name << endl;
	sprintf(QCD_Pt_170_250_EMEnriched_name,"MC_QCD_Pt_170_250_EMEnriched_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 24 is: " << QCD_Pt_170_250_EMEnriched_name << endl;
	sprintf(QCD_Pt_250_350_EMEnriched_name,"MC_QCD_Pt_250_350_EMEnriched_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 25 is: " << QCD_Pt_250_350_EMEnriched_name << endl;
	sprintf(QCD_Pt_350_EMEnriched_name,"MC_QCD_Pt_350_EMEnriched_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 26 is: " << QCD_Pt_350_EMEnriched_name << endl;

	sprintf(QCD_Pt_20_30_BCtoE_name,"MC_QCD_Pt_20_30_BCtoE_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 31 is: " << QCD_Pt_20_30_BCtoE_name << endl;
	sprintf(QCD_Pt_30_80_BCtoE_name,"MC_QCD_Pt_30_80_BCtoE_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 32 is: " << QCD_Pt_30_80_BCtoE_name << endl;
	sprintf(QCD_Pt_80_170_BCtoE_name,"MC_QCD_Pt_80_170_BCtoE_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 33 is: " << QCD_Pt_80_170_BCtoE_name << endl;
	sprintf(QCD_Pt_170_250_BCtoE_name,"MC_QCD_Pt_170_250_BCtoE_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 34 is: " << QCD_Pt_170_250_BCtoE_name << endl;
	sprintf(QCD_Pt_250_350_BCtoE_name,"MC_QCD_Pt_250_350_BCtoE_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 35 is: " << QCD_Pt_250_350_BCtoE_name << endl;
	sprintf(QCD_Pt_350_BCtoE_name,"MC_QCD_Pt_350_BCtoE_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 36 is: " << QCD_Pt_350_BCtoE_name << endl;	
	
/*
	sprintf(QCD_HT_100To250_name,"mc_QCD_HT-100To250_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 41 is: " << QCD_HT_100To250_name << endl;
	sprintf(QCD_HT_250To500_name,"mc_QCD_HT-250To500_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 42 is: " << QCD_HT_250To500_name << endl;
	sprintf(QCD_HT_500To1000_name,"mc_QCD_HT-500To1000_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 43 is: " << QCD_HT_500To1000_name << endl;
	sprintf(QCD_HT_1000ToInf_name,"mc_QCD_HT-1000ToInf_histos_%d_inverted_%s.root",itype, geo);
	cout << "QCD file 44 is: " << QCD_HT_1000ToInf_name << endl;
*/

	
	string address = geo_s + out_files;

	TFile *DATA_Run2012A_13Jul2012_file = new TFile((address+DATA_Run2012A_13Jul2012_name).c_str());
	TFile *DATA_Run2012A_recover_06Aug2012_file = new TFile((address+DATA_Run2012A_recover_06Aug2012_name).c_str());
	TFile *DATA_Run2012B_13Jul2012_file = new TFile((address+DATA_Run2012B_13Jul2012_name).c_str());
	TFile *DATA_Run2012C_24Aug2012_file = new TFile((address+DATA_Run2012C_24Aug2012_name).c_str());
	TFile *DATA_Run2012C_EcalRecover_11Dec2012_file = new TFile((address+DATA_Run2012C_EcalRecover_11Dec2012_name).c_str());
	TFile *DATA_Run2012C_PromptReco_file = new TFile((address+DATA_Run2012C_PromptReco_name).c_str());
	TFile *DATA_Run2012D_PromptReco_file = new TFile((address+DATA_Run2012D_PromptReco_name).c_str());


	TFile *GJets_HT_200To400_file = new TFile((address+GJets_HT_200To400_name).c_str());
	TFile *GJets_HT_400ToInf_file = new TFile((address+GJets_HT_400ToInf_name).c_str()); 
	TFile *QCD_Pt_20_30_EMEnriched_file = new TFile((address+QCD_Pt_20_30_EMEnriched_name).c_str()); 
	TFile *QCD_Pt_30_80_EMEnriched_file = new TFile((address+QCD_Pt_30_80_EMEnriched_name).c_str());
	TFile *QCD_Pt_80_170_EMEnriched_file = new TFile((address+QCD_Pt_80_170_EMEnriched_name).c_str());
	TFile *QCD_Pt_170_250_EMEnriched_file = new TFile((address+QCD_Pt_170_250_EMEnriched_name).c_str());
	TFile *QCD_Pt_250_350_EMEnriched_file = new TFile((address+QCD_Pt_250_350_EMEnriched_name).c_str());
	TFile *QCD_Pt_350_EMEnriched_file = new TFile((address+QCD_Pt_350_EMEnriched_name).c_str());

	TFile *QCD_Pt_20_30_BCtoE_file = new TFile((address+QCD_Pt_20_30_BCtoE_name).c_str()); 
	TFile *QCD_Pt_30_80_BCtoE_file = new TFile((address+QCD_Pt_30_80_BCtoE_name).c_str());
	TFile *QCD_Pt_80_170_BCtoE_file = new TFile((address+QCD_Pt_80_170_BCtoE_name).c_str());
	TFile *QCD_Pt_170_250_BCtoE_file = new TFile((address+QCD_Pt_170_250_BCtoE_name).c_str());
	TFile *QCD_Pt_250_350_BCtoE_file = new TFile((address+QCD_Pt_250_350_BCtoE_name).c_str());
	TFile *QCD_Pt_350_BCtoE_file = new TFile((address+QCD_Pt_350_BCtoE_name).c_str());

/*
	TFile *QCD_HT_100To250_file = new TFile((address+QCD_HT_100To250_name).c_str());  
	TFile *QCD_HT_250To500_file = new TFile((address+QCD_HT_250To500_name).c_str());   
	TFile *QCD_HT_500To1000_file = new TFile((address+QCD_HT_500To1000_name).c_str()); 
	TFile *QCD_HT_1000ToInf_file = new TFile((address+QCD_HT_1000ToInf_name).c_str()); 
*/

	Char_t titlehisto[100];

	strcpy(titlehisto,titleh);
	cout << "Analyzing Histogram " << titlehisto << endl;

	//--- data -----------------------------------------------------------------
	TH1F *DATA_Run2012A_13Jul2012_histo=(TH1F*)DATA_Run2012A_13Jul2012_file->Get(titlehisto);
	DATA_Run2012A_13Jul2012_histo->Rebin(rebin);
	cout << "DATA_Run2012A_13Jul2012 entries = " << DATA_Run2012A_13Jul2012_histo->Integral() << endl;  

	TH1F *DATA_Run2012A_recover_06Aug2012_histo=(TH1F*)DATA_Run2012A_recover_06Aug2012_file->Get(titlehisto);
	DATA_Run2012A_recover_06Aug2012_histo->Rebin(rebin);
	cout << "DATA_Run2012A_recover_06Aug2012 entries = " << DATA_Run2012A_recover_06Aug2012_histo->Integral() << endl;  

	TH1F *DATA_Run2012B_13Jul2012_histo=(TH1F*)DATA_Run2012B_13Jul2012_file->Get(titlehisto);
	DATA_Run2012B_13Jul2012_histo->Rebin(rebin);
	cout << "DATA_Run2012B_13Jul2012 entries = " << DATA_Run2012B_13Jul2012_histo->Integral() << endl;  

	TH1F *DATA_Run2012C_24Aug2012_histo=(TH1F*)DATA_Run2012C_24Aug2012_file->Get(titlehisto);
	DATA_Run2012C_24Aug2012_histo->Rebin(rebin);
	cout << "DATA_Run2012C_24Aug2012 entries = " << DATA_Run2012C_24Aug2012_histo->Integral() << endl;  

	TH1F *DATA_Run2012C_EcalRecover_11Dec2012_histo=(TH1F*)DATA_Run2012C_EcalRecover_11Dec2012_file->Get(titlehisto);
	DATA_Run2012C_EcalRecover_11Dec2012_histo->Rebin(rebin);
	cout << "DATA_Run2012C_EcalRecover_11Dec2012 entries = " << DATA_Run2012C_EcalRecover_11Dec2012_histo->Integral() << endl;  

	TH1F *DATA_Run2012C_PromptReco_histo=(TH1F*)DATA_Run2012C_PromptReco_file->Get(titlehisto);
	DATA_Run2012C_PromptReco_histo->Rebin(rebin);
	cout << "DATA_Run2012C_PromptReco entries = " << DATA_Run2012C_PromptReco_histo->Integral() << endl;  

	TH1F *DATA_Run2012D_PromptReco_histo=(TH1F*)DATA_Run2012D_PromptReco_file->Get(titlehisto);
	DATA_Run2012D_PromptReco_histo->Rebin(rebin);
	cout << "DATA_Run2012D_PromptReco entries = " << DATA_Run2012D_PromptReco_histo->Integral() << endl;  

	TH1F *DATA_total_histo = (TH1F*) DATA_Run2012A_13Jul2012_histo->Clone("DATA_total_histo");
	DATA_total_histo->Add(DATA_Run2012A_recover_06Aug2012_histo);
	DATA_total_histo->Add(DATA_Run2012B_13Jul2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_24Aug2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_EcalRecover_11Dec2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_PromptReco_histo);
	DATA_total_histo->Add(DATA_Run2012D_PromptReco_histo);


		
	//--- MC signal GJets_HT-xToy ----------------------------------------------
	TH1F *GJets_HT_200To400_histo=(TH1F*)GJets_HT_200To400_file->Get(titlehisto);
	GJets_HT_200To400_histo->Rebin(rebin);
	cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;

	TH1F *GJets_HT_400ToInf_histo=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto);
	GJets_HT_400ToInf_histo->Rebin(rebin);
	cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;

	TH1F *GJets_HT_xToy_total_histo = (TH1F*) GJets_HT_200To400_histo->Clone("GJets_HT_xToy_total_histo");
	//--- GJets_HT_xToy_total_histo->Sumw2();
	GJets_HT_xToy_total_histo->Add(GJets_HT_400ToInf_histo);  
//	GJets_HT_xToy_total_histo->SetLineColor(1);
//	GJets_HT_xToy_total_histo->SetFillColor(5);  //for colors comment out Sumw2 in code

	//--- MC background QCD_Pt_x_y EMEnriched ----------------------------------
	TH1F *QCD_Pt_20_30_EMEnriched_histo=(TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto);
	QCD_Pt_20_30_EMEnriched_histo->Rebin(rebin);
	cout << "QCD_Pt_20_30_EMEnriched entries = " << QCD_Pt_20_30_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_30_80_EMEnriched_histo=(TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto);
	QCD_Pt_30_80_EMEnriched_histo->Rebin(rebin);
	cout << "QCD_Pt_30_80_EMEnriched entries = " << QCD_Pt_30_80_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_80_170_EMEnriched_histo=(TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto);
	QCD_Pt_80_170_EMEnriched_histo->Rebin(rebin);
	cout << "QCD_Pt_80_170_EMEnriched entries = " << QCD_Pt_80_170_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_170_250_EMEnriched_histo=(TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto);
	QCD_Pt_170_250_EMEnriched_histo->Rebin(rebin);
	cout << "QCD_Pt_170_250_EMEnriched entries = " << QCD_Pt_170_250_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_250_350_EMEnriched_histo=(TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto);
	QCD_Pt_250_350_EMEnriched_histo->Rebin(rebin);
	cout << "QCD_Pt_250_350_EMEnriched entries = " << QCD_Pt_250_350_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_350_EMEnriched_histo=(TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto);
	QCD_Pt_350_EMEnriched_histo->Rebin(rebin);
	cout << "QCD_Pt_350_EMEnriched entries = " << QCD_Pt_350_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_x_y_EMEnriched_total_histo = (TH1F*) QCD_Pt_20_30_EMEnriched_histo->Clone("QCD_Pt_x_y_EMEnriched_total_histo");
	//	QCD_Pt_x_y_EMEnriched_total_histo->Sumw2();
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_30_80_EMEnriched_histo);
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_80_170_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_170_250_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_250_350_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_350_EMEnriched_histo);  
//	QCD_Pt_x_y_EMEnriched_total_histo->SetLineColor(1);
//	QCD_Pt_x_y_EMEnriched_total_histo->SetFillColor(kMagenta+2);


	//--- MC background QCD_Pt_x_y BCtoE ----------------------------------
	TH1F *QCD_Pt_20_30_BCtoE_histo=(TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto);
	QCD_Pt_20_30_BCtoE_histo->Rebin(rebin);
	cout << "QCD_Pt_20_30_BCtoE entries = " << QCD_Pt_20_30_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_30_80_BCtoE_histo=(TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto);
	QCD_Pt_30_80_BCtoE_histo->Rebin(rebin);
	cout << "QCD_Pt_30_80_BCtoE entries = " << QCD_Pt_30_80_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_80_170_BCtoE_histo=(TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto);
	QCD_Pt_80_170_BCtoE_histo->Rebin(rebin);
	cout << "QCD_Pt_80_170_BCtoE entries = " << QCD_Pt_80_170_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_170_250_BCtoE_histo=(TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto);
	QCD_Pt_170_250_BCtoE_histo->Rebin(rebin);
	cout << "QCD_Pt_170_250_BCtoE entries = " << QCD_Pt_170_250_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_250_350_BCtoE_histo=(TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto);
	QCD_Pt_250_350_BCtoE_histo->Rebin(rebin);
	cout << "QCD_Pt_250_350_BCtoE entries = " << QCD_Pt_250_350_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_350_BCtoE_histo=(TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto);
	QCD_Pt_350_BCtoE_histo->Rebin(rebin);
	cout << "QCD_Pt_350_BCtoE entries = " << QCD_Pt_350_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_x_y_BCtoE_total_histo = (TH1F*) QCD_Pt_20_30_BCtoE_histo->Clone("QCD_Pt_x_y_BCtoE_total_histo");
//	QCD_Pt_x_y_BCtoE_total_histo->Sumw2();
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_30_80_BCtoE_histo);
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_80_170_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_170_250_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_250_350_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_350_BCtoE_histo);  
//	QCD_Pt_x_y_BCtoE_total_histo->SetLineColor(1);
//	QCD_Pt_x_y_BCtoE_total_histo->SetFillColor(kBlue-7);

/*
	// MC background QCD HT-xToy --------------------------------------------
	TH1F *QCD_HT_100To250_histo=(TH1F*)QCD_HT_100To250_file->Get(titlehisto);
	QCD_HT_100To250_histo->Rebin(rebin);
	cout << "QCD_HT_100To250 entries " << QCD_HT_100To250_histo->Integral() << endl;  

	TH1F *QCD_HT_250To500_histo=(TH1F*)QCD_HT_250To500_file->Get(titlehisto);
	QCD_HT_250To500_histo->Rebin(rebin);
	cout << "QCD_HT_250To500 entries " << QCD_HT_250To500_histo->Integral() << endl;  

	TH1F *QCD_HT_500To1000_histo=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto);
	QCD_HT_500To1000_histo->Rebin(rebin);
	cout << "QCD_HT_500To1000 entries " << QCD_HT_500To1000_histo->Integral() << endl;

	TH1F *QCD_HT_1000ToInf_histo=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto);
	QCD_HT_1000ToInf_histo->Rebin(rebin);
	cout << "QCD_HT_1000ToInf entries " << QCD_HT_1000ToInf_histo->Integral() << endl;

	TH1F *QCD_HT_xToy_total_histo = (TH1F*) QCD_HT_100To250_histo->Clone("QCD_HT_xToy_total_histo");
//	QCD_HT_xToy_total_histo->Sumw2();
	QCD_HT_xToy_total_histo->Add(QCD_HT_250To500_histo);
	QCD_HT_xToy_total_histo->Add(QCD_HT_500To1000_histo);  
	QCD_HT_xToy_total_histo->Add(QCD_HT_1000ToInf_histo);  
//	QCD_HT_xToy_total_histo->SetLineColor(1);
//	QCD_HT_xToy_total_histo->SetFillColor(kRed+2);

*/

	cout << "GJets total entries = " << GJets_HT_xToy_total_histo->Integral() << endl;  
	cout << "QCD EMEnriched total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() << endl;  
	cout << "QCD BCtoE total entries = " << QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;
	cout << "QCD total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() + QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;	 
//	cout << "QCD HT total entries = " << QCD_HT_xToy_total_histo->Integral() << endl;  

	TH1F *MC_total_histo = (TH1F*) QCD_Pt_x_y_BCtoE_total_histo->Clone("MC_total_histo");
	MC_total_histo->Add(QCD_Pt_x_y_EMEnriched_total_histo);
	MC_total_histo->Add(GJets_HT_xToy_total_histo);


  TCanvas *Canva = new TCanvas(titlehisto,titlehisto);  
	int Nbins;

	if (sample == "DATA") {	

		DATA_total_histo->Sumw2();

		Nbins = DATA_total_histo->GetNbinsX();	
cout << Nbins << endl;
		if (x_min != -999 && x_max != -999){
			DATA_total_histo->GetXaxis()->SetRangeUser(x_min,x_max-x_max/Nbins);
		}	
		
		DATA_total_histo->SetMarkerStyle(20);
		DATA_total_histo->SetMinimum(0.1);

		DATA_total_histo->Draw("E");
		gPad->SetLogy();
		DATA_total_histo->Draw("AXIS X+ Y+ SAME");
		DATA_total_histo->Draw("AXIS SAME");
		DATA_total_histo->GetXaxis()->SetTitle(namevariable);
		DATA_total_histo->GetXaxis()->SetTitleSize(0.05);
		DATA_total_histo->GetYaxis()->SetTitle("Events");
		//DATA_total_histo->GetYaxis()->SetTitleOffset(0.8);
		//DATA_total_histo->GetYaxis()->SetTitleSize(0.05);
		//DATA_total_histo->GetYaxis()->SetLabelSize(0.03);
	}	

	else if (sample == "MC") {
		
		MC_total_histo->Sumw2();

		Nbins = 	MC_total_histo->GetNbinsX();

		if (x_min != -999 && x_max != -999){
			MC_total_histo->GetXaxis()->SetRangeUser(x_min,x_max-x_max/Nbins);
		}

		MC_total_histo->SetMarkerStyle(20);
		MC_total_histo->SetMinimum(0.1);

		MC_total_histo->Draw("E");
		gPad->SetLogy();
		MC_total_histo->Draw("AXIS X+ Y+ SAME");
		MC_total_histo->Draw("AXIS SAME");
		MC_total_histo->GetXaxis()->SetTitle(namevariable);
		MC_total_histo->GetXaxis()->SetTitleSize(0.05);
		MC_total_histo->GetYaxis()->SetTitle("Events");
		//MC_total_histo->GetYaxis()->SetTitleOffset(0.8);
		//MC_total_histo->GetYaxis()->SetTitleSize(0.05);
		//MC_total_histo->GetYaxis()->SetLabelSize(0.03);
	}


	TLegend *leg =new TLegend(0.6068,0.6923,0.6929,0.7480);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	if (sample == "DATA") {
		leg->AddEntry(DATA_total_histo,"Data","pL");
	}  
	if (sample == "MC") {
		leg->AddEntry(MC_total_histo,"MC","pL");
	}  
	leg->Draw();

  TPaveText* text = new TPaveText(0.6068,0.7722,0.8188,0.8571,"NDC");
  text->SetFillColor(0);
  text->SetFillStyle(0);
  text->SetBorderSize(0);
  text->AddText("CMS Preliminary");
  text->AddText("#sqrt{s} = 8 TeV, L = 19.03 fb^{-1}");
  text->SetTextAlign(11);
  text->Draw();
	
  Canva->SaveAs((geo_s + pdf_folder + titleh + sample + pdf_string).c_str());
  Canva->SaveAs((geo_s + root_folder + titleh + sample + root_string).c_str());
	Canva->Close();

	if (sample == "DATA") {	
		DATA_Run2012A_13Jul2012_file->Close();
		DATA_Run2012A_recover_06Aug2012_file->Close();
		DATA_Run2012B_13Jul2012_file->Close();
		DATA_Run2012C_24Aug2012_file->Close();
		DATA_Run2012C_EcalRecover_11Dec2012_file->Close();
		DATA_Run2012C_PromptReco_file->Close();
		DATA_Run2012D_PromptReco_file->Close();
	}	

	if (sample == "MC") {	
		GJets_HT_200To400_file->Close();
		GJets_HT_400ToInf_file->Close(); 

		QCD_Pt_20_30_EMEnriched_file->Close();
		QCD_Pt_30_80_EMEnriched_file->Close();
		QCD_Pt_80_170_EMEnriched_file->Close();
		QCD_Pt_170_250_EMEnriched_file->Close();
		QCD_Pt_250_350_EMEnriched_file->Close();
		QCD_Pt_350_EMEnriched_file->Close();

		QCD_Pt_20_30_BCtoE_file->Close();
		QCD_Pt_30_80_BCtoE_file->Close();
		QCD_Pt_80_170_BCtoE_file->Close();
		QCD_Pt_170_250_BCtoE_file->Close();
		QCD_Pt_250_350_BCtoE_file->Close();
		QCD_Pt_350_BCtoE_file->Close();

/*
		QCD_HT_100To250_file->Close();  
		QCD_HT_250To500_file->Close();
		QCD_HT_500To1000_file->Close();
		QCD_HT_1000ToInf_file->Close(); 
*/
	}
}
