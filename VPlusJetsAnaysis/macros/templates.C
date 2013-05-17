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
#include <TMath.h>
#include "TF1.h"
#include <TLatex.h>


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


void templates(const char* titleh, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L comparestack.C+
  //       ie: comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 1);

	string folder = "4_results_2013_05_10/";
	char geo[10] = "barrel"; // "barrel", "endcaps" or "total"
	bool inv = false; // inverted sigmaietaieta cut
	bool signal_MAD = true;
	bool background_QCD = false;
		
	Int_t itype = 4; // identifica histo con analisi diverse

	string sample = "MC_SIG"; // "MC_SIG", "MC_BACK", "DATA_INV" or "DATA"

	setMYStyle();


	// ==================================== definitions
		
	Char_t DATA_Run2012A_13Jul2012_name[100];
	Char_t DATA_Run2012A_recover_06Aug2012_name[100];
	Char_t DATA_Run2012B_13Jul2012_name[100];
	Char_t DATA_Run2012C_24Aug2012_name[100];
	Char_t DATA_Run2012C_EcalRecover_11Dec2012_name[100];
	Char_t DATA_Run2012C_PromptReco_name[100];
	Char_t DATA_Run2012D_PromptReco_name[100];

/*							
	Char_t GJets_HT_40To100_name[100];
	Char_t GJets_HT_100To200_name[100];	
*/
	Char_t GJets_HT_200To400_name[100];
	Char_t GJets_HT_400ToInf_name[100];

	Char_t G_Pt_15to30_name[100];
	Char_t G_Pt_30to50_name[100];
	Char_t G_Pt_50to80_name[100];
	Char_t G_Pt_80to120_name[100];	
	Char_t G_Pt_120to170_name[100];
	Char_t G_Pt_170to300_name[100];	
	Char_t G_Pt_300to470_name[100];
	Char_t G_Pt_470to800_name[100];
	Char_t G_Pt_800to1400_name[100];
	Char_t G_Pt_1400to1800_name[100];
	Char_t G_Pt_1800_name[100];

	Char_t DiPhotonJets_name[100];

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
	
	Char_t QCD_HT_100To250_name[100];
	Char_t QCD_HT_250To500_name[100];
	Char_t QCD_HT_500To1000_name[100];
	Char_t QCD_HT_1000ToInf_name[100];


	// ==================================== assign files names
	
	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string out_files = "output_files/";
	string fit_pdf_folder = "fit_pdf_plots/";
	string pdf_string = ".pdf";
	string fit_root_folder = "fit_root_plots/";
	string root_string = ".root";
	string inverted = "_inverted";
	if (inv) root_string = inverted + root_string;		
	stringstream ss_r;
	char root_char[10];
	ss_r << root_string;
	ss_r >> root_char;
	string address = folder + geo_s + out_files;
	
			
	sprintf(DATA_Run2012A_13Jul2012_name,"DATA_Run2012A-13Jul2012_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_Run2012A_recover_06Aug2012_name,"DATA_Run2012A-recover-06Aug2012_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_Run2012B_13Jul2012_name,"DATA_Run2012B-13Jul2012_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_Run2012C_24Aug2012_name,"DATA_Run2012C-24Aug2012_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_Run2012C_EcalRecover_11Dec2012_name,"DATA_Run2012C-EcalRecover_11Dec2012_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_Run2012C_PromptReco_name,"DATA_Run2012C-PromptReco_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_Run2012D_PromptReco_name,"DATA_Run2012D-PromptReco_histos_%d_%s%s",itype, geo, root_char);

	cout << "data file 1 is " << DATA_Run2012A_13Jul2012_name << endl;
	cout << "data file 2 is " << DATA_Run2012A_recover_06Aug2012_name << endl;
	cout << "data file 3 is " << DATA_Run2012B_13Jul2012_name << endl;
	cout << "data file 4 is " << DATA_Run2012C_24Aug2012_name << endl;
	cout << "data file 5 is " << DATA_Run2012C_EcalRecover_11Dec2012_name << endl;
	cout << "data file 6 is " << DATA_Run2012C_PromptReco_name << endl;
	cout << "data file 7 is " << DATA_Run2012D_PromptReco_name << endl;

/*
	sprintf(GJets_HT_40To100_name,"MC_GJets_HT-40To100_histos_%d_%s%s",itype, geo, root_char);
	sprintf(GJets_HT_100To200_name,"MC_GJets_HT-100To200_histos_%d_%s%s",itype, geo, root_char);	
*/
	sprintf(GJets_HT_200To400_name,"MC_GJets_HT-200To400_histos_%d_%s%s",itype, geo, root_char);
	sprintf(GJets_HT_400ToInf_name,"MC_GJets_HT-400ToInf_histos_%d_%s%s",itype, geo, root_char);

	if(signal_MAD){
/*	
		cout << "GJets file 11 is: " << GJets_HT_40To100_name << endl;
		cout << "GJets file 12 is: " << GJets_HT_100To200_name << endl;	
*/
		cout << "GJets file 13 is: " << GJets_HT_200To400_name << endl;
		cout << "GJets file 14 is: " << GJets_HT_400ToInf_name << endl;
	}
	
	sprintf(G_Pt_15to30_name,"MC_G_Pt-15to30_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_30to50_name,"MC_G_Pt-30to50_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_50to80_name,"MC_G_Pt-50to80_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_80to120_name,"MC_G_Pt-80to120_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_120to170_name,"MC_G_Pt-120to170_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_170to300_name,"MC_G_Pt-170to300_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_300to470_name,"MC_G_Pt-300to470_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_470to800_name,"MC_G_Pt-470to800_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_800to1400_name,"MC_G_Pt-800to1400_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_1400to1800_name,"MC_G_Pt-1400to1800_histos_%d_%s%s",itype, geo, root_char);
	sprintf(G_Pt_1800_name,"MC_G_Pt-1800_histos_%d_%s%s",itype, geo, root_char);

	if (!signal_MAD){
		cout << "G file 21 is: " << G_Pt_15to30_name << endl;
		cout << "G file 22 is: " << G_Pt_30to50_name << endl;
		cout << "G file 23 is: " << G_Pt_50to80_name << endl;
		cout << "G file 24 is: " << G_Pt_80to120_name << endl;
		cout << "G file 25 is: " << G_Pt_120to170_name << endl;
		cout << "G file 26 is: " << G_Pt_170to300_name << endl;
		cout << "G file 27 is: " << G_Pt_300to470_name << endl;
		cout << "G file 28 is: " << G_Pt_470to800_name << endl;
		cout << "G file 29 is: " << G_Pt_800to1400_name << endl;
		cout << "G file 30 is: " << G_Pt_1400to1800_name << endl;
		cout << "G file 31 is: " << G_Pt_1800_name << endl;
	}
	
	sprintf(DiPhotonJets_name,"MC_DiPhotonJets_histos_%d_%s%s",itype, geo, root_char);
	cout << "DiPhotonJets file 41 is: " << DiPhotonJets_name << endl;

	sprintf(QCD_Pt_20_30_EMEnriched_name,"MC_QCD_Pt_20_30_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_30_80_EMEnriched_name,"MC_QCD_Pt_30_80_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_80_170_EMEnriched_name,"MC_QCD_Pt_80_170_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_170_250_EMEnriched_name,"MC_QCD_Pt_170_250_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_250_350_EMEnriched_name,"MC_QCD_Pt_250_350_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_350_EMEnriched_name,"MC_QCD_Pt_350_EMEnriched_histos_%d_%s%s",itype, geo, root_char);

	if (!background_QCD){
		cout << "QCD EMEnriched file 51 is: " << QCD_Pt_20_30_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 52 is: " << QCD_Pt_30_80_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 53 is: " << QCD_Pt_80_170_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 54 is: " << QCD_Pt_170_250_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 55 is: " << QCD_Pt_250_350_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 56 is: " << QCD_Pt_350_EMEnriched_name << endl;
	}
	sprintf(QCD_Pt_20_30_BCtoE_name,"MC_QCD_Pt_20_30_BCtoE_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_30_80_BCtoE_name,"MC_QCD_Pt_30_80_BCtoE_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_80_170_BCtoE_name,"MC_QCD_Pt_80_170_BCtoE_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_170_250_BCtoE_name,"MC_QCD_Pt_170_250_BCtoE_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_250_350_BCtoE_name,"MC_QCD_Pt_250_350_BCtoE_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_Pt_350_BCtoE_name,"MC_QCD_Pt_350_BCtoE_histos_%d_%s%s",itype, geo, root_char);
	
	if (!background_QCD){	
		cout << "QCD BCtoE file 61 is: " << QCD_Pt_20_30_BCtoE_name << endl;
		cout << "QCD BCtoE file 62 is: " << QCD_Pt_30_80_BCtoE_name << endl;
		cout << "QCD BCtoE file 63 is: " << QCD_Pt_80_170_BCtoE_name << endl;
		cout << "QCD BCtoE file 64 is: " << QCD_Pt_170_250_BCtoE_name << endl;
		cout << "QCD BCtoE file 65 is: " << QCD_Pt_250_350_BCtoE_name << endl;
		cout << "QCD BCtoE file 66 is: " << QCD_Pt_350_BCtoE_name << endl;	
	}
	sprintf(QCD_HT_100To250_name,"MC_QCD_HT-100To250_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_HT_250To500_name,"MC_QCD_HT-250To500_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_HT_500To1000_name,"MC_QCD_HT-500To1000_histos_%d_%s%s",itype, geo, root_char);
	sprintf(QCD_HT_1000ToInf_name,"MC_QCD_HT-1000ToInf_histos_%d_%s%s",itype, geo, root_char);

	if (background_QCD){
		cout << "QCD file 71 is: " << QCD_HT_100To250_name << endl;
		cout << "QCD file 72 is: " << QCD_HT_250To500_name << endl;
		cout << "QCD file 73 is: " << QCD_HT_500To1000_name << endl;
		cout << "QCD file 74 is: " << QCD_HT_1000ToInf_name << endl;
	}


	// ==================================== load TFiles

	TFile *DATA_Run2012A_13Jul2012_file = new TFile((address+DATA_Run2012A_13Jul2012_name).c_str());
	TFile *DATA_Run2012A_recover_06Aug2012_file = new TFile((address+DATA_Run2012A_recover_06Aug2012_name).c_str());
	TFile *DATA_Run2012B_13Jul2012_file = new TFile((address+DATA_Run2012B_13Jul2012_name).c_str());
	TFile *DATA_Run2012C_24Aug2012_file = new TFile((address+DATA_Run2012C_24Aug2012_name).c_str());
	TFile *DATA_Run2012C_EcalRecover_11Dec2012_file = new TFile((address+DATA_Run2012C_EcalRecover_11Dec2012_name).c_str());
	TFile *DATA_Run2012C_PromptReco_file = new TFile((address+DATA_Run2012C_PromptReco_name).c_str());
	TFile *DATA_Run2012D_PromptReco_file = new TFile((address+DATA_Run2012D_PromptReco_name).c_str());

/*	
	TFile *GJets_HT_40To100_file = new TFile((address+GJets_HT_40To100_name).c_str());	
	TFile *GJets_HT_100To200_file = new TFile((address+GJets_HT_100To200_name).c_str());	
*/
	TFile *GJets_HT_200To400_file = new TFile((address+GJets_HT_200To400_name).c_str());
	TFile *GJets_HT_400ToInf_file = new TFile((address+GJets_HT_400ToInf_name).c_str()); 

	TFile *G_Pt_15to30_file = new TFile((address+G_Pt_15to30_name).c_str());
	TFile *G_Pt_30to50_file = new TFile((address+G_Pt_30to50_name).c_str());
	TFile *G_Pt_50to80_file = new TFile((address+G_Pt_50to80_name).c_str());
	TFile *G_Pt_80to120_file = new TFile((address+G_Pt_80to120_name).c_str());
	TFile *G_Pt_120to170_file = new TFile((address+G_Pt_120to170_name).c_str());
	TFile *G_Pt_170to300_file = new TFile((address+G_Pt_170to300_name).c_str());
	TFile *G_Pt_300to470_file = new TFile((address+G_Pt_300to470_name).c_str());
	TFile *G_Pt_470to800_file = new TFile((address+G_Pt_470to800_name).c_str());
	TFile *G_Pt_800to1400_file = new TFile((address+G_Pt_800to1400_name).c_str());
	TFile *G_Pt_1400to1800_file = new TFile((address+G_Pt_1400to1800_name).c_str());	
	TFile *G_Pt_1800_file = new TFile((address+G_Pt_1800_name).c_str());

	TFile *DiPhotonJets_file = new TFile((address+DiPhotonJets_name).c_str());
	
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

	TFile *QCD_HT_100To250_file = new TFile((address+QCD_HT_100To250_name).c_str());  
	TFile *QCD_HT_250To500_file = new TFile((address+QCD_HT_250To500_name).c_str());   
	TFile *QCD_HT_500To1000_file = new TFile((address+QCD_HT_500To1000_name).c_str()); 
	TFile *QCD_HT_1000ToInf_file = new TFile((address+QCD_HT_1000ToInf_name).c_str()); 
	

	// ==================================== open now the output TFile

	root_string = ".root";
	pdf_string = ".pdf";
	string sample_mod = "";
	if (inv) sample_mod = sample + inverted + "_";
	else sample_mod = sample + "_";
	string templates = "template_";
	string outfilename = (sample_mod + templates + titleh + root_string).c_str();

	TFile *outfile = new TFile((address + outfilename).c_str(),"recreate");

	// ==================================== load TH1F

	Char_t titlehisto[100];

	strcpy(titlehisto,titleh);
	cout << "Analyzing Histogram " << titlehisto << endl;

	//--- data -----------------------------------------------------------------
	TH1F *DATA_Run2012A_13Jul2012_histo=(TH1F*)DATA_Run2012A_13Jul2012_file->Get(titlehisto);
	DATA_Run2012A_13Jul2012_histo->Rebin(rebin);

	TH1F *DATA_Run2012A_recover_06Aug2012_histo=(TH1F*)DATA_Run2012A_recover_06Aug2012_file->Get(titlehisto);
	DATA_Run2012A_recover_06Aug2012_histo->Rebin(rebin);

	TH1F *DATA_Run2012B_13Jul2012_histo=(TH1F*)DATA_Run2012B_13Jul2012_file->Get(titlehisto);
	DATA_Run2012B_13Jul2012_histo->Rebin(rebin);

	TH1F *DATA_Run2012C_24Aug2012_histo=(TH1F*)DATA_Run2012C_24Aug2012_file->Get(titlehisto);
	DATA_Run2012C_24Aug2012_histo->Rebin(rebin);

	TH1F *DATA_Run2012C_EcalRecover_11Dec2012_histo=(TH1F*)DATA_Run2012C_EcalRecover_11Dec2012_file->Get(titlehisto);
	DATA_Run2012C_EcalRecover_11Dec2012_histo->Rebin(rebin);

	TH1F *DATA_Run2012C_PromptReco_histo=(TH1F*)DATA_Run2012C_PromptReco_file->Get(titlehisto);
	DATA_Run2012C_PromptReco_histo->Rebin(rebin);

	TH1F *DATA_Run2012D_PromptReco_histo=(TH1F*)DATA_Run2012D_PromptReco_file->Get(titlehisto);
	DATA_Run2012D_PromptReco_histo->Rebin(rebin);

	cout << "DATA_Run2012A_13Jul2012 entries = " << DATA_Run2012A_13Jul2012_histo->Integral() << endl;  
	cout << "DATA_Run2012A_recover_06Aug2012 entries = " << DATA_Run2012A_recover_06Aug2012_histo->Integral() << endl;  
	cout << "DATA_Run2012B_13Jul2012 entries = " << DATA_Run2012B_13Jul2012_histo->Integral() << endl;  
	cout << "DATA_Run2012C_24Aug2012 entries = " << DATA_Run2012C_24Aug2012_histo->Integral() << endl;  
	cout << "DATA_Run2012C_EcalRecover_11Dec2012 entries = " << DATA_Run2012C_EcalRecover_11Dec2012_histo->Integral() << endl;  
	cout << "DATA_Run2012C_PromptReco entries = " << DATA_Run2012C_PromptReco_histo->Integral() << endl;  
	cout << "DATA_Run2012D_PromptReco entries = " << DATA_Run2012D_PromptReco_histo->Integral() << endl;  

	TH1F *DATA_total_histo = (TH1F*) DATA_Run2012A_13Jul2012_histo->Clone("DATA_total_histo");
	DATA_total_histo->Add(DATA_Run2012A_recover_06Aug2012_histo);
	DATA_total_histo->Add(DATA_Run2012B_13Jul2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_24Aug2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_EcalRecover_11Dec2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_PromptReco_histo);
	DATA_total_histo->Add(DATA_Run2012D_PromptReco_histo);

				
	//--- MC signal GJets_HT-xToy ----------------------------------------------
/*
	TH1F *GJets_HT_40To100_histo=(TH1F*)GJets_HT_40To100_file->Get(titlehisto);
	GJets_HT_40To100_histo->Rebin(rebin);

	TH1F *GJets_HT_100To200_histo=(TH1F*)GJets_HT_100To200_file->Get(titlehisto);
	GJets_HT_100To200_histo->Rebin(rebin);
*/
	TH1F *GJets_HT_200To400_histo=(TH1F*)GJets_HT_200To400_file->Get(titlehisto);
	GJets_HT_200To400_histo->Rebin(rebin);

	TH1F *GJets_HT_400ToInf_histo=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto);
	GJets_HT_400ToInf_histo->Rebin(rebin);

	if(signal_MAD){
/*	
		cout << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo->Integral() << endl;
		cout << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo->Integral() << endl;	
*/
		cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;
		cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;
	}
	
	TH1F *GJets_HT_xToy_total_histo = (TH1F*) GJets_HT_200To400_histo->Clone("GJets_HT_xToy_total_histo");
	//--- GJets_HT_xToy_total_histo->Sumw2();
/*	
	GJets_HT_xToy_total_histo->Add(GJets_HT_40To100_histo);	
	GJets_HT_xToy_total_histo->Add(GJets_HT_100To200_histo);
*/
	GJets_HT_xToy_total_histo->Add(GJets_HT_400ToInf_histo);  
	GJets_HT_xToy_total_histo->SetLineColor(1);
	GJets_HT_xToy_total_histo->SetFillColor(5);  //for colors comment out Sumw2 in code


	// MC signal G_Pt-XtoY --------------------------------------------------
	TH1F *G_Pt_15to30_histo=(TH1F*)G_Pt_15to30_file->Get(titlehisto);
	G_Pt_15to30_histo->Rebin(rebin);

	TH1F *G_Pt_30to50_histo=(TH1F*)G_Pt_30to50_file->Get(titlehisto);
	G_Pt_30to50_histo->Rebin(rebin);

	TH1F *G_Pt_50to80_histo=(TH1F*)G_Pt_50to80_file->Get(titlehisto);
	G_Pt_50to80_histo->Rebin(rebin);

	TH1F *G_Pt_80to120_histo=(TH1F*)G_Pt_80to120_file->Get(titlehisto);
	G_Pt_80to120_histo->Rebin(rebin);

	TH1F *G_Pt_120to170_histo=(TH1F*)G_Pt_120to170_file->Get(titlehisto);
	G_Pt_120to170_histo->Rebin(rebin);
	
	TH1F *G_Pt_170to300_histo=(TH1F*)G_Pt_170to300_file->Get(titlehisto);
	G_Pt_170to300_histo->Rebin(rebin);

	TH1F *G_Pt_300to470_histo=(TH1F*)G_Pt_300to470_file->Get(titlehisto);
	G_Pt_300to470_histo->Rebin(rebin);

	TH1F *G_Pt_470to800_histo=(TH1F*)G_Pt_470to800_file->Get(titlehisto);
	G_Pt_470to800_histo->Rebin(rebin);

	TH1F *G_Pt_800to1400_histo=(TH1F*)G_Pt_800to1400_file->Get(titlehisto);
	G_Pt_800to1400_histo->Rebin(rebin);

	TH1F *G_Pt_1400to1800_histo=(TH1F*)G_Pt_1400to1800_file->Get(titlehisto);
	G_Pt_1400to1800_histo->Rebin(rebin);

	TH1F *G_Pt_1800_histo=(TH1F*)G_Pt_1800_file->Get(titlehisto);
	G_Pt_1800_histo->Rebin(rebin);

	if(!signal_MAD){
		cout << "G_Pt_15to30 entries = " << G_Pt_15to30_histo->Integral() << endl;
		cout << "G_Pt_30to50 entries = " << G_Pt_30to50_histo->Integral() << endl;
		cout << "G_Pt_50to80 entries = " << G_Pt_50to80_histo->Integral() << endl;
		cout << "G_Pt_80to120 entries = " << G_Pt_80to120_histo->Integral() << endl;
		cout << "G_Pt_120to170 entries = " << G_Pt_120to170_histo->Integral() << endl;
		cout << "G_Pt_170to300 entries = " << G_Pt_170to300_histo->Integral() << endl;
		cout << "G_Pt_300to470 entries = " << G_Pt_300to470_histo->Integral() << endl;
		cout << "G_Pt_470to800 entries = " << G_Pt_470to800_histo->Integral() << endl;
		cout << "G_Pt_800to1400 entries = " << G_Pt_800to1400_histo->Integral() << endl;
		cout << "G_Pt_1400to1800 entries = " << G_Pt_1400to1800_histo->Integral() << endl;
		cout << "G_Pt_1800 entries = " << G_Pt_1800_histo->Integral() << endl;
	}
	
	TH1F *G_Pt_XtoY_total_histo = (TH1F*) G_Pt_15to30_histo->Clone("G_Pt_XtoY_total_histo");
	//--- G_Pt_XtoY_total_histo->Sumw2();
	G_Pt_XtoY_total_histo->Add(G_Pt_30to50_histo);
	G_Pt_XtoY_total_histo->Add(G_Pt_50to80_histo);  
	G_Pt_XtoY_total_histo->Add(G_Pt_80to120_histo);  
	G_Pt_XtoY_total_histo->Add(G_Pt_120to170_histo);  
	G_Pt_XtoY_total_histo->Add(G_Pt_170to300_histo);  
	G_Pt_XtoY_total_histo->Add(G_Pt_300to470_histo);  
	G_Pt_XtoY_total_histo->Add(G_Pt_470to800_histo);  		
	G_Pt_XtoY_total_histo->Add(G_Pt_800to1400_histo);
	G_Pt_XtoY_total_histo->Add(G_Pt_1400to1800_histo);	  	
	G_Pt_XtoY_total_histo->Add(G_Pt_1800_histo);	  	
	G_Pt_XtoY_total_histo->SetLineColor(1);
	G_Pt_XtoY_total_histo->SetFillColor(kGreen+2);  //for colors comment out Sumw2 in code


	// MC signal DiPhotonJets --------------------------------------------------
	TH1F *DiPhotonJets_histo=(TH1F*)DiPhotonJets_file->Get(titlehisto);
	DiPhotonJets_histo->Rebin(rebin);
	
	cout << "DiPhotonJets entries = " << DiPhotonJets_histo->Integral() << endl;

	TH1F *DiPhotonJets_total_histo = (TH1F*) DiPhotonJets_histo->Clone("DiPhotonJets_total_histo");
	//--- DiPhotonJets_total_histo->Sumw2();
	DiPhotonJets_total_histo->SetLineColor(1);
	DiPhotonJets_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code


	//--- MC background QCD_Pt_x_y EMEnriched ----------------------------------
	TH1F *QCD_Pt_20_30_EMEnriched_histo=(TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto);
	QCD_Pt_20_30_EMEnriched_histo->Rebin(rebin);

	TH1F *QCD_Pt_30_80_EMEnriched_histo=(TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto);
	QCD_Pt_30_80_EMEnriched_histo->Rebin(rebin);

	TH1F *QCD_Pt_80_170_EMEnriched_histo=(TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto);
	QCD_Pt_80_170_EMEnriched_histo->Rebin(rebin);

	TH1F *QCD_Pt_170_250_EMEnriched_histo=(TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto);
	QCD_Pt_170_250_EMEnriched_histo->Rebin(rebin);

	TH1F *QCD_Pt_250_350_EMEnriched_histo=(TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto);
	QCD_Pt_250_350_EMEnriched_histo->Rebin(rebin);

	TH1F *QCD_Pt_350_EMEnriched_histo=(TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto);
	QCD_Pt_350_EMEnriched_histo->Rebin(rebin);

	if (!background_QCD){
		cout << "QCD_Pt_20_30_EMEnriched entries = " << QCD_Pt_20_30_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_30_80_EMEnriched entries = " << QCD_Pt_30_80_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_80_170_EMEnriched entries = " << QCD_Pt_80_170_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_170_250_EMEnriched entries = " << QCD_Pt_170_250_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_250_350_EMEnriched entries = " << QCD_Pt_250_350_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_350_EMEnriched entries = " << QCD_Pt_350_EMEnriched_histo->Integral() << endl;
	}

	TH1F *QCD_Pt_x_y_EMEnriched_total_histo = (TH1F*) QCD_Pt_20_30_EMEnriched_histo->Clone("QCD_Pt_x_y_EMEnriched_total_histo");
	//	QCD_Pt_x_y_EMEnriched_total_histo->Sumw2();
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_30_80_EMEnriched_histo);
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_80_170_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_170_250_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_250_350_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_350_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->SetLineColor(1);
	QCD_Pt_x_y_EMEnriched_total_histo->SetFillColor(kMagenta+2);


	//--- MC background QCD_Pt_x_y BCtoE ----------------------------------
	TH1F *QCD_Pt_20_30_BCtoE_histo=(TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto);
	QCD_Pt_20_30_BCtoE_histo->Rebin(rebin);

	TH1F *QCD_Pt_30_80_BCtoE_histo=(TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto);
	QCD_Pt_30_80_BCtoE_histo->Rebin(rebin);

	TH1F *QCD_Pt_80_170_BCtoE_histo=(TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto);
	QCD_Pt_80_170_BCtoE_histo->Rebin(rebin);

	TH1F *QCD_Pt_170_250_BCtoE_histo=(TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto);
	QCD_Pt_170_250_BCtoE_histo->Rebin(rebin);

	TH1F *QCD_Pt_250_350_BCtoE_histo=(TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto);
	QCD_Pt_250_350_BCtoE_histo->Rebin(rebin);

	TH1F *QCD_Pt_350_BCtoE_histo=(TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto);
	QCD_Pt_350_BCtoE_histo->Rebin(rebin);

	if (!background_QCD){
		cout << "QCD_Pt_20_30_BCtoE entries = " << QCD_Pt_20_30_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_30_80_BCtoE entries = " << QCD_Pt_30_80_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_80_170_BCtoE entries = " << QCD_Pt_80_170_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_170_250_BCtoE entries = " << QCD_Pt_170_250_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_250_350_BCtoE entries = " << QCD_Pt_250_350_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_350_BCtoE entries = " << QCD_Pt_350_BCtoE_histo->Integral() << endl;
	}
	
	TH1F *QCD_Pt_x_y_BCtoE_total_histo = (TH1F*) QCD_Pt_20_30_BCtoE_histo->Clone("QCD_Pt_x_y_BCtoE_total_histo");
	//	QCD_Pt_x_y_BCtoE_total_histo->Sumw2();
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_30_80_BCtoE_histo);
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_80_170_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_170_250_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_250_350_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_350_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->SetLineColor(1);
	QCD_Pt_x_y_BCtoE_total_histo->SetFillColor(kBlue-7);


	// MC background QCD HT-xToy --------------------------------------------
	TH1F *QCD_HT_100To250_histo=(TH1F*)QCD_HT_100To250_file->Get(titlehisto);
	QCD_HT_100To250_histo->Rebin(rebin);

	TH1F *QCD_HT_250To500_histo=(TH1F*)QCD_HT_250To500_file->Get(titlehisto);
	QCD_HT_250To500_histo->Rebin(rebin);

	TH1F *QCD_HT_500To1000_histo=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto);
	QCD_HT_500To1000_histo->Rebin(rebin);

	TH1F *QCD_HT_1000ToInf_histo=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto);
	QCD_HT_1000ToInf_histo->Rebin(rebin);

	if (background_QCD){
		cout << "QCD_HT_100To250 entries " << QCD_HT_100To250_histo->Integral() << endl;  
		cout << "QCD_HT_250To500 entries " << QCD_HT_250To500_histo->Integral() << endl;  
		cout << "QCD_HT_500To1000 entries " << QCD_HT_500To1000_histo->Integral() << endl;
		cout << "QCD_HT_1000ToInf entries " << QCD_HT_1000ToInf_histo->Integral() << endl;
	}
	
	TH1F *QCD_HT_xToy_total_histo = (TH1F*) QCD_HT_100To250_histo->Clone("QCD_HT_xToy_total_histo");
	//	QCD_HT_xToy_total_histo->Sumw2();
	QCD_HT_xToy_total_histo->Add(QCD_HT_250To500_histo);
	QCD_HT_xToy_total_histo->Add(QCD_HT_500To1000_histo);  
	QCD_HT_xToy_total_histo->Add(QCD_HT_1000ToInf_histo);  
	QCD_HT_xToy_total_histo->SetLineColor(1);
	QCD_HT_xToy_total_histo->SetFillColor(kRed+2);


	// ==================================== print Entries number

	cout << endl;
	cout << "DATA total entries = " << DATA_total_histo->Integral() << endl;

	cout << endl;
	if(signal_MAD) cout << "GJets total entries = " << GJets_HT_xToy_total_histo->Integral() << endl;  
	else cout << "G total entries = " << G_Pt_XtoY_total_histo->Integral() << endl;

	cout << endl;
	cout << "DiPhotonJets total entries = " << DiPhotonJets_total_histo->Integral() << endl;

	cout << endl;
	if (!background_QCD){	  
	cout << "QCD EMEnriched total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() << endl;  
	cout << "QCD BCtoE total entries = " << QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;
	cout << "QCD (EMEnriched + BCtoE) total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() +
	                                                       QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;
	}	 
	else cout << "QCD HT total entries = " << QCD_HT_xToy_total_histo->Integral() << endl;  
	cout << endl;
	

	// ==================================== preparing MC SIGNAL and MC BACKGROUND added histos

	// MC SIGNAL total 
	TH1F *MC_SIG_total_histo;
	if(signal_MAD){
	MC_SIG_total_histo = (TH1F*) GJets_HT_xToy_total_histo->Clone("MC_SIG_total_histo");
	}
	else{
	MC_SIG_total_histo = (TH1F*) G_Pt_XtoY_total_histo->Clone("MC_SIG_total_histo");
	}
	MC_SIG_total_histo->Add(DiPhotonJets_total_histo);
				
	// MC BACKGROUND total
	TH1F *MC_BACK_total_histo;
	if (!background_QCD){	
		MC_BACK_total_histo = (TH1F*) QCD_Pt_x_y_EMEnriched_total_histo->Clone("MC_BACK_total_histo");
		MC_BACK_total_histo->Add(QCD_Pt_x_y_BCtoE_total_histo);
	}	
	else MC_BACK_total_histo = (TH1F*) QCD_HT_xToy_total_histo->Clone("MC_BACK_total_histo");

	// DATA INVERTED total
	TH1F *DATA_INV_total_histo = (TH1F*) DATA_total_histo->Clone("DATA_INV_total_histo");
	
	
	// ==================================== load Canvas

  TCanvas *Canva = new TCanvas(titlehisto,titlehisto);  
	int Nbins;
	double X_min, X_max;
	
	if (sample == "MC_SIG") {
		
		MC_SIG_total_histo->Sumw2();

		Nbins = MC_SIG_total_histo->GetNbinsX();

		if (x_min != -999 && x_max != -999){
			if (x_max == MC_SIG_total_histo->GetXaxis()->GetXmax()) X_max = x_max;
			else X_max = x_max - (x_max-x_min)/Nbins;
			if (x_min == MC_SIG_total_histo->GetXaxis()->GetXmin()) X_min = x_min;
			else X_min = x_min + (x_max-x_min)/Nbins;

			MC_SIG_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);
		}

		MC_SIG_total_histo->SetMarkerStyle(20);
		MC_SIG_total_histo->SetMinimum(0.1);

		MC_SIG_total_histo->Draw("E");
		gPad->SetLogy();
		MC_SIG_total_histo->Draw("AXIS X+ Y+ SAME");
		MC_SIG_total_histo->Draw("AXIS SAME");
		MC_SIG_total_histo->GetXaxis()->SetTitle(namevariable);
		MC_SIG_total_histo->GetXaxis()->SetTitleSize(0.05);
		MC_SIG_total_histo->GetYaxis()->SetTitle("Events");

		MC_SIG_total_histo->Write(titleh) ;
		outfile-> Write();

	}

	else if (sample == "MC_BACK") {	

		MC_BACK_total_histo->Sumw2();

		Nbins = MC_BACK_total_histo->GetNbinsX();

		if (x_min != -999 && x_max != -999){
			if (x_max == MC_BACK_total_histo->GetXaxis()->GetXmax()) X_max = x_max;
			else X_max = x_max - (x_max-x_min)/Nbins;
			if (x_min == MC_BACK_total_histo->GetXaxis()->GetXmin()) X_min = x_min;
			else X_min = x_min + (x_max-x_min)/Nbins;

			MC_BACK_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);
		}

		MC_BACK_total_histo->SetMarkerStyle(20);
		MC_BACK_total_histo->SetMinimum(0.1);

		MC_BACK_total_histo->Draw("E");
		gPad->SetLogy();
		MC_BACK_total_histo->Draw("AXIS X+ Y+ SAME");
		MC_BACK_total_histo->Draw("AXIS SAME");
		MC_BACK_total_histo->GetXaxis()->SetTitle(namevariable);
		MC_BACK_total_histo->GetXaxis()->SetTitleSize(0.05);
		MC_BACK_total_histo->GetYaxis()->SetTitle("Events");

		MC_BACK_total_histo->Write(titleh) ;
		outfile-> Write();
	}	

	else if (sample == "DATA_INV") {	

		DATA_INV_total_histo->Sumw2();

		Nbins = DATA_INV_total_histo->GetNbinsX();

		if (x_min != -999 && x_max != -999){
			if (x_max == DATA_INV_total_histo->GetXaxis()->GetXmax()) X_max = x_max;
			else X_max = x_max - (x_max-x_min)/Nbins;
			if (x_min == DATA_INV_total_histo->GetXaxis()->GetXmin()) X_min = x_min;
			else X_min = x_min + (x_max-x_min)/Nbins;

			DATA_INV_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);
		}

		DATA_INV_total_histo->SetMarkerStyle(20);
		DATA_INV_total_histo->SetMinimum(0.1);

		DATA_INV_total_histo->Draw("E");
		gPad->SetLogy();
		DATA_INV_total_histo->Draw("AXIS X+ Y+ SAME");
		DATA_INV_total_histo->Draw("AXIS SAME");
		DATA_INV_total_histo->GetXaxis()->SetTitle(namevariable);
		DATA_INV_total_histo->GetXaxis()->SetTitleSize(0.05);
		DATA_INV_total_histo->GetYaxis()->SetTitle("Events");

		DATA_INV_total_histo->Write(titleh) ;
		outfile-> Write();
	}	

	else {	

		DATA_total_histo->Sumw2();

		Nbins = DATA_total_histo->GetNbinsX();

		if (x_min != -999 && x_max != -999){
			if (x_max == DATA_total_histo->GetXaxis()->GetXmax()) X_max = x_max;
			else X_max = x_max - (x_max-x_min)/Nbins;
			if (x_min == DATA_total_histo->GetXaxis()->GetXmin()) X_min = x_min;
			else X_min = x_min + (x_max-x_min)/Nbins;

			DATA_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);
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

		DATA_total_histo->Write(titleh) ;
		outfile-> Write();	
	}	


	TLegend *leg =new TLegend(0.6068,0.6923,0.83,0.7490);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	if (sample == "MC_SIG") {
		leg->AddEntry(MC_SIG_total_histo,"MC signal","pL");
	}  
	else if (sample == "MC_BACK") {
		leg->AddEntry(MC_BACK_total_histo,"MC background","pL");
	}  
	else if (sample == "DATA_INV") {
		leg->AddEntry(DATA_INV_total_histo,"DATA inverted #sigma_{i #eta i #eta}","pL");
	}  
	else {
		leg->AddEntry(DATA_total_histo,"Data","pL");
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

  Canva->SaveAs((folder + geo_s + fit_pdf_folder + sample_mod + titleh + pdf_string).c_str());
  Canva->SaveAs((folder + geo_s + fit_root_folder + sample_mod + titleh + root_string).c_str());
	Canva->Close();


	// ==================================== close files

	DATA_Run2012A_13Jul2012_file->Close();
	DATA_Run2012A_recover_06Aug2012_file->Close();
	DATA_Run2012B_13Jul2012_file->Close();
	DATA_Run2012C_24Aug2012_file->Close();
	DATA_Run2012C_EcalRecover_11Dec2012_file->Close();
	DATA_Run2012C_PromptReco_file->Close();
	DATA_Run2012D_PromptReco_file->Close();

/*
	GJets_HT_40To100_file->Close();
	GJets_HT_100To200_file->Close();	
*/
	GJets_HT_200To400_file->Close();
	GJets_HT_400ToInf_file->Close(); 

	G_Pt_15to30_file->Close();
	G_Pt_30to50_file->Close();
	G_Pt_50to80_file->Close();
	G_Pt_80to120_file->Close();
	G_Pt_120to170_file->Close();			
	G_Pt_170to300_file->Close();	
	G_Pt_300to470_file->Close();	
	G_Pt_470to800_file->Close();	
	G_Pt_800to1400_file->Close();
	G_Pt_1400to1800_file->Close();		
	G_Pt_1800_file->Close();

	DiPhotonJets_file->Close();

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

	QCD_HT_100To250_file->Close();  
	QCD_HT_250To500_file->Close();
	QCD_HT_500To1000_file->Close();
	QCD_HT_1000ToInf_file->Close(); 

}


void templates_3binPt() {
	templates("SelectedPhotons_PfIso_1_bin01_", "photon PfIso, 150 < p_{T}^{#gamma} < 300", 2, 0, 30);
	templates("SelectedPhotons_PfIso_1_bin02_", "photon PfIso, 300 < p_{T}^{#gamma} < 500", 2, 0, 30);
	templates("SelectedPhotons_PfIso_1_bin03_", "photon PfIso, p_{T}^{#gamma} > 500", 2, 0, 30);
}

