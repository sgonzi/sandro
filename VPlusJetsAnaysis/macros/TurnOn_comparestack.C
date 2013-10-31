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

using namespace std;

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
//  myStyle->SetOptLogy(0);
  myStyle->SetOptLogz(0);

// Postscript options:
  myStyle->SetPaperSize(20.,20.);

  myStyle->cd();
}


void TurnOn_comparestack(const char* titleh_NUM, const char* titleh_DEN, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L comparestack.C++
  //       ie: comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 1);

	setMYStyle();

	// ==================================== choose the tools

	string folder = "07_results_2013_10_27"; // analysis folder

	char geo[100] = "barrel";                // "barrel", "endcaps" or "total"

	bool data_ReReco = true;                // true: data = ReReco
	                                         // false: data = PromptReco
	bool signal_MAD = true;                  // true: signal = MADGRAPH; false: signal = PYTHIA
	bool background_QCD = false;             // true: background = MADGRAPH not filtered (QCD HT)
	                                         // false: background = PYTHIA filtered (QCD EMEnriched + BCtoE); 

	Int_t itype = 7;                        // it identifies histos with different analysis 


	// ==================================== string names

	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string folder_s = folder + "/";
	string SB_folder;
	if (signal_MAD && background_QCD) {
		SB_folder = "sM1_bQ1/";
	}
	else if (signal_MAD && !background_QCD) {
		SB_folder = "sM1_bQ0/";
	}
	else if (!signal_MAD && background_QCD) {
		SB_folder = "sM0_bQ1/";
	}
	else {
		SB_folder = "sM0_bQ0/";
	}
	string out_files = "output_files/";
	string pdf_folder = "pdf_plots/";
	string pdf_string = ".pdf";
	string root_folder = "root_plots/";
	string root_string = ".root";
	string txt_folder = "txt_plots/";
	string txt_string = ".txt";
	string TurnOn_s = "_TurnOn";

	root_string = TurnOn_s + root_string;
			
	stringstream ss_r;
	char root_char[200];
	ss_r << root_string;
	ss_r >> root_char;

	string address = folder_s + geo_s + out_files;


	// ==================================== exception controls

	if (!(Geo == "barrel" || Geo == "endcaps" || Geo == "total")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps\" or \"total\"). You wrote: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}	


	// ==================================== assign files names

	Char_t DATA_RR_Run2012A_22Jan2013_name[100];
	Char_t DATA_RR_Run2012B_22Jan2013_name[100];
	Char_t DATA_RR_Run2012C_22Jan2013_name[100];
	Char_t DATA_RR_Run2012D_22Jan2013_name[100];

	Char_t DATA_PR_Run2012A_13Jul2012_name[100];
	Char_t DATA_PR_Run2012A_recover_06Aug2012_name[100];
	Char_t DATA_PR_Run2012B_13Jul2012_name[100];
	Char_t DATA_PR_Run2012C_24Aug2012_name[100];
	Char_t DATA_PR_Run2012C_EcalRecover_11Dec2012_name[100];
	Char_t DATA_PR_Run2012C_PromptReco_name[100];
	Char_t DATA_PR_Run2012D_PromptReco_name[100];
					
	Char_t GJets_HT_40To100_name[100];
	Char_t GJets_HT_100To200_name[100];	
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

	if (data_ReReco){
		sprintf(DATA_RR_Run2012A_22Jan2013_name,"DATA_RR_Run2012A-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_RR_Run2012B_22Jan2013_name,"DATA_RR_Run2012B-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_RR_Run2012C_22Jan2013_name,"DATA_RR_Run2012C-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_RR_Run2012D_22Jan2013_name,"DATA_RR_Run2012D-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
				
		cout << endl;	
		cout << "========================" <<endl;	
		cout << endl;	
		cout << "data RR file 1 is " << DATA_RR_Run2012A_22Jan2013_name << endl;
		cout << "data RR file 2 is " << DATA_RR_Run2012B_22Jan2013_name << endl;
		cout << "data RR file 3 is " << DATA_RR_Run2012C_22Jan2013_name << endl;
		cout << "data RR file 4 is " << DATA_RR_Run2012D_22Jan2013_name << endl;
		cout << endl;
	}
	else{
		sprintf(DATA_PR_Run2012A_13Jul2012_name,"DATA_PR_Run2012A-13Jul2012_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_PR_Run2012A_recover_06Aug2012_name,"DATA_PR_Run2012A-recover-06Aug2012_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_PR_Run2012B_13Jul2012_name,"DATA_PR_Run2012B-13Jul2012_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_PR_Run2012C_24Aug2012_name,"DATA_PR_Run2012C-24Aug2012_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_PR_Run2012C_EcalRecover_11Dec2012_name,"DATA_PR_Run2012C-EcalRecover_11Dec2012_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_PR_Run2012C_PromptReco_name,"DATA_PR_Run2012C-PromptReco_histos_%d_%s%s",itype, geo, root_char);
		sprintf(DATA_PR_Run2012D_PromptReco_name,"DATA_PR_Run2012D-PromptReco_histos_%d_%s%s",itype, geo, root_char);

		cout << endl;	
		cout << "========================" <<endl;	
		cout << endl;	
		cout << "data PR file 11 is " << DATA_PR_Run2012A_13Jul2012_name << endl;
		cout << "data PR file 12 is " << DATA_PR_Run2012A_recover_06Aug2012_name << endl;
		cout << "data PR file 13 is " << DATA_PR_Run2012B_13Jul2012_name << endl;
		cout << "data PR file 14 is " << DATA_PR_Run2012C_24Aug2012_name << endl;
		cout << "data PR file 15 is " << DATA_PR_Run2012C_EcalRecover_11Dec2012_name << endl;
		cout << "data PR file 16 is " << DATA_PR_Run2012C_PromptReco_name << endl;
		cout << "data PR file 17 is " << DATA_PR_Run2012D_PromptReco_name << endl;
		cout << endl;
	}
	
	if(signal_MAD){
		sprintf(GJets_HT_40To100_name,"MC_GJets_HT-40To100_histos_%d_%s%s",itype, geo, root_char);
		sprintf(GJets_HT_100To200_name,"MC_GJets_HT-100To200_histos_%d_%s%s",itype, geo, root_char);	
		sprintf(GJets_HT_200To400_name,"MC_GJets_HT-200To400_histos_%d_%s%s",itype, geo, root_char);
		sprintf(GJets_HT_400ToInf_name,"MC_GJets_HT-400ToInf_histos_%d_%s%s",itype, geo, root_char);

		cout << "GJets file 21 is: " << GJets_HT_40To100_name << endl;
		cout << "GJets file 22 is: " << GJets_HT_100To200_name << endl;	
		cout << "GJets file 23 is: " << GJets_HT_200To400_name << endl;
		cout << "GJets file 24 is: " << GJets_HT_400ToInf_name << endl;
		cout << endl;
	}
	else {
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

		cout << "G file 31 is: " << G_Pt_15to30_name << endl;
		cout << "G file 32 is: " << G_Pt_30to50_name << endl;
		cout << "G file 33 is: " << G_Pt_50to80_name << endl;
		cout << "G file 34 is: " << G_Pt_80to120_name << endl;
		cout << "G file 35 is: " << G_Pt_120to170_name << endl;
		cout << "G file 36 is: " << G_Pt_170to300_name << endl;
		cout << "G file 37 is: " << G_Pt_300to470_name << endl;
		cout << "G file 38 is: " << G_Pt_470to800_name << endl;
		cout << "G file 39 is: " << G_Pt_800to1400_name << endl;
		cout << "G file 40 is: " << G_Pt_1400to1800_name << endl;
		cout << "G file 41 is: " << G_Pt_1800_name << endl;
		cout << endl;	
	}
	
	sprintf(DiPhotonJets_name,"MC_DiPhotonJets_histos_%d_%s%s",itype, geo, root_char);
	cout << "DiPhotonJets file 51 is: " << DiPhotonJets_name << endl;
	cout << endl;

	if (!background_QCD){	
		sprintf(QCD_Pt_20_30_EMEnriched_name,"MC_QCD_Pt_20_30_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_30_80_EMEnriched_name,"MC_QCD_Pt_30_80_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_80_170_EMEnriched_name,"MC_QCD_Pt_80_170_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_170_250_EMEnriched_name,"MC_QCD_Pt_170_250_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_250_350_EMEnriched_name,"MC_QCD_Pt_250_350_EMEnriched_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_350_EMEnriched_name,"MC_QCD_Pt_350_EMEnriched_histos_%d_%s%s",itype, geo, root_char);

		cout << "QCD EMEnriched file 61 is: " << QCD_Pt_20_30_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 62 is: " << QCD_Pt_30_80_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 63 is: " << QCD_Pt_80_170_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 64 is: " << QCD_Pt_170_250_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 65 is: " << QCD_Pt_250_350_EMEnriched_name << endl;
		cout << "QCD EMEnriched file 66 is: " << QCD_Pt_350_EMEnriched_name << endl;
		cout << endl;	
	
		sprintf(QCD_Pt_20_30_BCtoE_name,"MC_QCD_Pt_20_30_BCtoE_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_30_80_BCtoE_name,"MC_QCD_Pt_30_80_BCtoE_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_80_170_BCtoE_name,"MC_QCD_Pt_80_170_BCtoE_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_170_250_BCtoE_name,"MC_QCD_Pt_170_250_BCtoE_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_250_350_BCtoE_name,"MC_QCD_Pt_250_350_BCtoE_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_Pt_350_BCtoE_name,"MC_QCD_Pt_350_BCtoE_histos_%d_%s%s",itype, geo, root_char);

		cout << "QCD BCtoE file 71 is: " << QCD_Pt_20_30_BCtoE_name << endl;
		cout << "QCD BCtoE file 72 is: " << QCD_Pt_30_80_BCtoE_name << endl;
		cout << "QCD BCtoE file 73 is: " << QCD_Pt_80_170_BCtoE_name << endl;
		cout << "QCD BCtoE file 74 is: " << QCD_Pt_170_250_BCtoE_name << endl;
		cout << "QCD BCtoE file 75 is: " << QCD_Pt_250_350_BCtoE_name << endl;
		cout << "QCD BCtoE file 76 is: " << QCD_Pt_350_BCtoE_name << endl;	
		cout << endl;
	}
	else {	
		sprintf(QCD_HT_100To250_name,"MC_QCD_HT-100To250_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_HT_250To500_name,"MC_QCD_HT-250To500_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_HT_500To1000_name,"MC_QCD_HT-500To1000_histos_%d_%s%s",itype, geo, root_char);
		sprintf(QCD_HT_1000ToInf_name,"MC_QCD_HT-1000ToInf_histos_%d_%s%s",itype, geo, root_char);

		cout << "QCD file 81 is: " << QCD_HT_100To250_name << endl;
		cout << "QCD file 82 is: " << QCD_HT_250To500_name << endl;
		cout << "QCD file 83 is: " << QCD_HT_500To1000_name << endl;
		cout << "QCD file 84 is: " << QCD_HT_1000ToInf_name << endl;
		cout << endl;	
	}


	// ==================================== load TFiles

	TFile *DATA_RR_Run2012A_22Jan2013_file;
	TFile *DATA_RR_Run2012B_22Jan2013_file;
	TFile *DATA_RR_Run2012C_22Jan2013_file;
	TFile *DATA_RR_Run2012D_22Jan2013_file;

	TFile *DATA_PR_Run2012A_13Jul2012_file;
	TFile *DATA_PR_Run2012A_recover_06Aug2012_file;
	TFile *DATA_PR_Run2012B_13Jul2012_file;
	TFile *DATA_PR_Run2012C_24Aug2012_file;
	TFile *DATA_PR_Run2012C_EcalRecover_11Dec2012_file;
	TFile *DATA_PR_Run2012C_PromptReco_file;
	TFile *DATA_PR_Run2012D_PromptReco_file;

	TFile *GJets_HT_40To100_file;
	TFile *GJets_HT_100To200_file;	
	TFile *GJets_HT_200To400_file;
	TFile *GJets_HT_400ToInf_file;

	TFile *G_Pt_15to30_file;
	TFile *G_Pt_30to50_file;
	TFile *G_Pt_50to80_file;
	TFile *G_Pt_80to120_file;
	TFile *G_Pt_120to170_file;
	TFile *G_Pt_170to300_file;
	TFile *G_Pt_300to470_file;
	TFile *G_Pt_470to800_file;
	TFile *G_Pt_800to1400_file;
	TFile *G_Pt_1400to1800_file;
	TFile *G_Pt_1800_file;

	TFile *DiPhotonJets_file;

	TFile *QCD_Pt_20_30_EMEnriched_file; 
	TFile *QCD_Pt_30_80_EMEnriched_file;
	TFile *QCD_Pt_80_170_EMEnriched_file;
	TFile *QCD_Pt_170_250_EMEnriched_file;
	TFile *QCD_Pt_250_350_EMEnriched_file;
	TFile *QCD_Pt_350_EMEnriched_file;

	TFile *QCD_Pt_20_30_BCtoE_file; 
	TFile *QCD_Pt_30_80_BCtoE_file;
	TFile *QCD_Pt_80_170_BCtoE_file;
	TFile *QCD_Pt_170_250_BCtoE_file;
	TFile *QCD_Pt_250_350_BCtoE_file;
	TFile *QCD_Pt_350_BCtoE_file;

	TFile *QCD_HT_100To250_file;  
	TFile *QCD_HT_250To500_file;   
	TFile *QCD_HT_500To1000_file; 
	TFile *QCD_HT_1000ToInf_file;

	if (data_ReReco) {
		DATA_RR_Run2012A_22Jan2013_file = new TFile((address+DATA_RR_Run2012A_22Jan2013_name).c_str());
		DATA_RR_Run2012B_22Jan2013_file = new TFile((address+DATA_RR_Run2012B_22Jan2013_name).c_str());
		DATA_RR_Run2012C_22Jan2013_file = new TFile((address+DATA_RR_Run2012C_22Jan2013_name).c_str());
		DATA_RR_Run2012D_22Jan2013_file = new TFile((address+DATA_RR_Run2012D_22Jan2013_name).c_str());				
	}
	else {
		DATA_PR_Run2012A_13Jul2012_file = new TFile((address+DATA_PR_Run2012A_13Jul2012_name).c_str());
  	DATA_PR_Run2012A_recover_06Aug2012_file = new TFile((address+DATA_PR_Run2012A_recover_06Aug2012_name).c_str());
		DATA_PR_Run2012B_13Jul2012_file = new TFile((address+DATA_PR_Run2012B_13Jul2012_name).c_str());
		DATA_PR_Run2012C_24Aug2012_file = new TFile((address+DATA_PR_Run2012C_24Aug2012_name).c_str());
		DATA_PR_Run2012C_EcalRecover_11Dec2012_file = new TFile((address+DATA_PR_Run2012C_EcalRecover_11Dec2012_name).c_str());
		DATA_PR_Run2012C_PromptReco_file = new TFile((address+DATA_PR_Run2012C_PromptReco_name).c_str());
		DATA_PR_Run2012D_PromptReco_file = new TFile((address+DATA_PR_Run2012D_PromptReco_name).c_str());
	}
	
	if(signal_MAD){	
		GJets_HT_40To100_file = new TFile((address+GJets_HT_40To100_name).c_str());	
		GJets_HT_100To200_file = new TFile((address+GJets_HT_100To200_name).c_str());	
		GJets_HT_200To400_file = new TFile((address+GJets_HT_200To400_name).c_str());
		GJets_HT_400ToInf_file = new TFile((address+GJets_HT_400ToInf_name).c_str()); 
	}
	else {	
		G_Pt_15to30_file = new TFile((address+G_Pt_15to30_name).c_str());
		G_Pt_30to50_file = new TFile((address+G_Pt_30to50_name).c_str());
		G_Pt_50to80_file = new TFile((address+G_Pt_50to80_name).c_str());
		G_Pt_80to120_file = new TFile((address+G_Pt_80to120_name).c_str());
		G_Pt_120to170_file = new TFile((address+G_Pt_120to170_name).c_str());
		G_Pt_170to300_file = new TFile((address+G_Pt_170to300_name).c_str());
		G_Pt_300to470_file = new TFile((address+G_Pt_300to470_name).c_str());
		G_Pt_470to800_file = new TFile((address+G_Pt_470to800_name).c_str());
		G_Pt_800to1400_file = new TFile((address+G_Pt_800to1400_name).c_str());
		G_Pt_1400to1800_file = new TFile((address+G_Pt_1400to1800_name).c_str());	
		G_Pt_1800_file = new TFile((address+G_Pt_1800_name).c_str());
	}

	DiPhotonJets_file = new TFile((address+DiPhotonJets_name).c_str());
	
	if (!background_QCD){
		QCD_Pt_20_30_EMEnriched_file = new TFile((address+QCD_Pt_20_30_EMEnriched_name).c_str()); 
		QCD_Pt_30_80_EMEnriched_file = new TFile((address+QCD_Pt_30_80_EMEnriched_name).c_str());
		QCD_Pt_80_170_EMEnriched_file = new TFile((address+QCD_Pt_80_170_EMEnriched_name).c_str());
		QCD_Pt_170_250_EMEnriched_file = new TFile((address+QCD_Pt_170_250_EMEnriched_name).c_str());
		QCD_Pt_250_350_EMEnriched_file = new TFile((address+QCD_Pt_250_350_EMEnriched_name).c_str());
		QCD_Pt_350_EMEnriched_file = new TFile((address+QCD_Pt_350_EMEnriched_name).c_str());

		QCD_Pt_20_30_BCtoE_file = new TFile((address+QCD_Pt_20_30_BCtoE_name).c_str()); 
		QCD_Pt_30_80_BCtoE_file = new TFile((address+QCD_Pt_30_80_BCtoE_name).c_str());
		QCD_Pt_80_170_BCtoE_file = new TFile((address+QCD_Pt_80_170_BCtoE_name).c_str());
		QCD_Pt_170_250_BCtoE_file = new TFile((address+QCD_Pt_170_250_BCtoE_name).c_str());
		QCD_Pt_250_350_BCtoE_file = new TFile((address+QCD_Pt_250_350_BCtoE_name).c_str());
		QCD_Pt_350_BCtoE_file = new TFile((address+QCD_Pt_350_BCtoE_name).c_str());
	}
	else{
		QCD_HT_100To250_file = new TFile((address+QCD_HT_100To250_name).c_str());  
		QCD_HT_250To500_file = new TFile((address+QCD_HT_250To500_name).c_str());   
		QCD_HT_500To1000_file = new TFile((address+QCD_HT_500To1000_name).c_str()); 
		QCD_HT_1000ToInf_file = new TFile((address+QCD_HT_1000ToInf_name).c_str()); 
	}

	// ==================================== load TH1F


	Char_t titlehisto_NUM[100];
	Char_t titlehisto_DEN[100];
	
	strcpy(titlehisto_NUM,titleh_NUM);
	strcpy(titlehisto_DEN,titleh_DEN);

	cout << "========================" <<endl;	
	cout << endl;	

	cout << "Analyzing Histogram: " << endl;
	cout << "Numerator ->"<< titlehisto_NUM << endl;
	cout << "Denominator ->"<< titlehisto_DEN << endl;

	cout << endl;	
	cout << "========================" <<endl;	
	cout << endl;	


	TH1F *DATA_RR_Run2012A_22Jan2013_histo_NUM;
	TH1F *DATA_RR_Run2012B_22Jan2013_histo_NUM;
	TH1F *DATA_RR_Run2012C_22Jan2013_histo_NUM;
	TH1F *DATA_RR_Run2012D_22Jan2013_histo_NUM;

	TH1F *DATA_RR_Run2012A_22Jan2013_histo_DEN;
	TH1F *DATA_RR_Run2012B_22Jan2013_histo_DEN;	
	TH1F *DATA_RR_Run2012C_22Jan2013_histo_DEN;
	TH1F *DATA_RR_Run2012D_22Jan2013_histo_DEN;

	TH1F *DATA_ReReco_total_histo_NUM;
	TH1F *DATA_ReReco_total_histo_DEN;

			
	TH1F *DATA_PR_Run2012A_13Jul2012_histo_NUM;
	TH1F *DATA_PR_Run2012A_recover_06Aug2012_histo_NUM;
	TH1F *DATA_PR_Run2012B_13Jul2012_histo_NUM;
	TH1F *DATA_PR_Run2012C_24Aug2012_histo_NUM;
	TH1F *DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_NUM;
	TH1F *DATA_PR_Run2012C_PromptReco_histo_NUM;
	TH1F *DATA_PR_Run2012D_PromptReco_histo_NUM;

	TH1F *DATA_PR_Run2012A_13Jul2012_histo_DEN;
	TH1F *DATA_PR_Run2012A_recover_06Aug2012_histo_DEN;
	TH1F *DATA_PR_Run2012B_13Jul2012_histo_DEN;
	TH1F *DATA_PR_Run2012C_24Aug2012_histo_DEN;
	TH1F *DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_DEN;
	TH1F *DATA_PR_Run2012C_PromptReco_histo_DEN;
	TH1F *DATA_PR_Run2012D_PromptReco_histo_DEN;

	TH1F *DATA_PromptReco_total_histo_NUM;
	TH1F *DATA_PromptReco_total_histo_DEN;

	TH1F *DATA_total_histo_NUM;
	TH1F *DATA_total_histo_DEN;
	TH1F *DATA_total_histo;


	TH1F *GJets_HT_40To100_histo_NUM;
	TH1F *GJets_HT_100To200_histo_NUM;
	TH1F *GJets_HT_200To400_histo_NUM;
	TH1F *GJets_HT_400ToInf_histo_NUM;

	TH1F *GJets_HT_40To100_histo_DEN;
	TH1F *GJets_HT_100To200_histo_DEN;
	TH1F *GJets_HT_200To400_histo_DEN;
	TH1F *GJets_HT_400ToInf_histo_DEN;

	TH1F *GJets_HT_xToy_total_histo_NUM;
	TH1F *GJets_HT_xToy_total_histo_DEN;
	

	TH1F *G_Pt_15to30_histo_NUM;
	TH1F *G_Pt_30to50_histo_NUM;
	TH1F *G_Pt_50to80_histo_NUM;
	TH1F *G_Pt_80to120_histo_NUM;
	TH1F *G_Pt_120to170_histo_NUM;
	TH1F *G_Pt_170to300_histo_NUM;
	TH1F *G_Pt_300to470_histo_NUM;
	TH1F *G_Pt_470to800_histo_NUM;
	TH1F *G_Pt_800to1400_histo_NUM;
	TH1F *G_Pt_1400to1800_histo_NUM;
	TH1F *G_Pt_1800_histo_NUM;

	TH1F *G_Pt_15to30_histo_DEN;
	TH1F *G_Pt_30to50_histo_DEN;
	TH1F *G_Pt_50to80_histo_DEN;
	TH1F *G_Pt_80to120_histo_DEN;
	TH1F *G_Pt_120to170_histo_DEN;
	TH1F *G_Pt_170to300_histo_DEN;
	TH1F *G_Pt_300to470_histo_DEN;
	TH1F *G_Pt_470to800_histo_DEN;
	TH1F *G_Pt_800to1400_histo_DEN;
	TH1F *G_Pt_1400to1800_histo_DEN;
	TH1F *G_Pt_1800_histo_DEN;

	TH1F *G_Pt_XtoY_total_histo_NUM;
	TH1F *G_Pt_XtoY_total_histo_DEN;


	TH1F *DiPhotonJets_histo_NUM;
	TH1F *DiPhotonJets_histo_DEN;

	TH1F *DiPhotonJets_total_histo_NUM;
	TH1F *DiPhotonJets_total_histo_DEN;


	TH1F *QCD_Pt_20_30_EMEnriched_histo_NUM;
	TH1F *QCD_Pt_30_80_EMEnriched_histo_NUM;
	TH1F *QCD_Pt_80_170_EMEnriched_histo_NUM;
	TH1F *QCD_Pt_170_250_EMEnriched_histo_NUM;
	TH1F *QCD_Pt_250_350_EMEnriched_histo_NUM;
	TH1F *QCD_Pt_350_EMEnriched_histo_NUM;

	TH1F *QCD_Pt_20_30_EMEnriched_histo_DEN;
	TH1F *QCD_Pt_30_80_EMEnriched_histo_DEN;
	TH1F *QCD_Pt_80_170_EMEnriched_histo_DEN;
	TH1F *QCD_Pt_170_250_EMEnriched_histo_DEN;
	TH1F *QCD_Pt_250_350_EMEnriched_histo_DEN;
	TH1F *QCD_Pt_350_EMEnriched_histo_DEN;

	TH1F *QCD_Pt_x_y_EMEnriched_total_histo_NUM;
	TH1F *QCD_Pt_x_y_EMEnriched_total_histo_DEN;


	TH1F *QCD_Pt_20_30_BCtoE_histo_NUM;
	TH1F *QCD_Pt_30_80_BCtoE_histo_NUM;
	TH1F *QCD_Pt_80_170_BCtoE_histo_NUM;
	TH1F *QCD_Pt_170_250_BCtoE_histo_NUM;
	TH1F *QCD_Pt_250_350_BCtoE_histo_NUM;
	TH1F *QCD_Pt_350_BCtoE_histo_NUM;

	TH1F *QCD_Pt_20_30_BCtoE_histo_DEN;
	TH1F *QCD_Pt_30_80_BCtoE_histo_DEN;
	TH1F *QCD_Pt_80_170_BCtoE_histo_DEN;
	TH1F *QCD_Pt_170_250_BCtoE_histo_DEN;
	TH1F *QCD_Pt_250_350_BCtoE_histo_DEN;
	TH1F *QCD_Pt_350_BCtoE_histo_DEN;	

	TH1F *QCD_Pt_x_y_BCtoE_total_histo_NUM;
	TH1F *QCD_Pt_x_y_BCtoE_total_histo_DEN;


	TH1F *QCD_HT_100To250_histo_NUM;
	TH1F *QCD_HT_250To500_histo_NUM;
	TH1F *QCD_HT_500To1000_histo_NUM;
	TH1F *QCD_HT_1000ToInf_histo_NUM;

	TH1F *QCD_HT_100To250_histo_DEN;
	TH1F *QCD_HT_250To500_histo_DEN;
	TH1F *QCD_HT_500To1000_histo_DEN;
	TH1F *QCD_HT_1000ToInf_histo_DEN;

	TH1F *QCD_HT_xToy_total_histo_NUM;	
	TH1F *QCD_HT_xToy_total_histo_DEN;	


	TH1F *MC_total_histo_NUM;
	TH1F *MC_total_histo_DEN;
	TH1F *MC_total_histo;




	if (data_ReReco) {
		//--- data ReReco ----------------------------------------------------------
		DATA_RR_Run2012A_22Jan2013_histo_NUM=(TH1F*)DATA_RR_Run2012A_22Jan2013_file->Get(titlehisto_NUM);
		DATA_RR_Run2012A_22Jan2013_histo_NUM->Rebin(rebin);
		DATA_RR_Run2012A_22Jan2013_histo_DEN=(TH1F*)DATA_RR_Run2012A_22Jan2013_file->Get(titlehisto_DEN);
		DATA_RR_Run2012A_22Jan2013_histo_DEN->Rebin(rebin);

		DATA_RR_Run2012B_22Jan2013_histo_NUM=(TH1F*)DATA_RR_Run2012B_22Jan2013_file->Get(titlehisto_NUM);
		DATA_RR_Run2012B_22Jan2013_histo_NUM->Rebin(rebin);
		DATA_RR_Run2012B_22Jan2013_histo_DEN=(TH1F*)DATA_RR_Run2012B_22Jan2013_file->Get(titlehisto_DEN);
		DATA_RR_Run2012B_22Jan2013_histo_DEN->Rebin(rebin);

		DATA_RR_Run2012C_22Jan2013_histo_NUM=(TH1F*)DATA_RR_Run2012C_22Jan2013_file->Get(titlehisto_NUM);
		DATA_RR_Run2012C_22Jan2013_histo_NUM->Rebin(rebin);
		DATA_RR_Run2012C_22Jan2013_histo_DEN=(TH1F*)DATA_RR_Run2012C_22Jan2013_file->Get(titlehisto_DEN);
		DATA_RR_Run2012C_22Jan2013_histo_DEN->Rebin(rebin);

		DATA_RR_Run2012D_22Jan2013_histo_NUM=(TH1F*)DATA_RR_Run2012D_22Jan2013_file->Get(titlehisto_NUM);
		DATA_RR_Run2012D_22Jan2013_histo_NUM->Rebin(rebin);
		DATA_RR_Run2012D_22Jan2013_histo_DEN=(TH1F*)DATA_RR_Run2012D_22Jan2013_file->Get(titlehisto_DEN);
		DATA_RR_Run2012D_22Jan2013_histo_DEN->Rebin(rebin);

		cout << "DATA_RR_Run2012A_22Jan2013_NUM entries = " << DATA_RR_Run2012A_22Jan2013_histo_NUM->Integral() << endl;  
		cout << "DATA_RR_Run2012B_22Jan2013_NUM entries = " << DATA_RR_Run2012B_22Jan2013_histo_NUM->Integral() << endl;  
		cout << "DATA_RR_Run2012C_22Jan2013_NUM entries = " << DATA_RR_Run2012C_22Jan2013_histo_NUM->Integral() << endl;  
		cout << "DATA_RR_Run2012D_22Jan2013_NUM entries = " << DATA_RR_Run2012D_22Jan2013_histo_NUM->Integral() << endl;  
		cout << endl;	
		cout << "DATA_RR_Run2012A_22Jan2013_DEN entries = " << DATA_RR_Run2012A_22Jan2013_histo_DEN->Integral() << endl;  
		cout << "DATA_RR_Run2012B_22Jan2013_DEN entries = " << DATA_RR_Run2012B_22Jan2013_histo_DEN->Integral() << endl;  
		cout << "DATA_RR_Run2012C_22Jan2013_DEN entries = " << DATA_RR_Run2012C_22Jan2013_histo_DEN->Integral() << endl;  
		cout << "DATA_RR_Run2012D_22Jan2013_DEN entries = " << DATA_RR_Run2012D_22Jan2013_histo_DEN->Integral() << endl;  
		cout << endl;	
	
		DATA_ReReco_total_histo_NUM = (TH1F*) DATA_RR_Run2012A_22Jan2013_histo_NUM->Clone("DATA_ReReco_total_histo_NUM");
		DATA_ReReco_total_histo_NUM->Add(DATA_RR_Run2012B_22Jan2013_histo_NUM);
		DATA_ReReco_total_histo_NUM->Add(DATA_RR_Run2012C_22Jan2013_histo_NUM);
		DATA_ReReco_total_histo_NUM->Add(DATA_RR_Run2012D_22Jan2013_histo_NUM);

		DATA_ReReco_total_histo_DEN = (TH1F*) DATA_RR_Run2012A_22Jan2013_histo_DEN->Clone("DATA_ReReco_total_histo_DEN");
		DATA_ReReco_total_histo_DEN->Add(DATA_RR_Run2012B_22Jan2013_histo_DEN);
		DATA_ReReco_total_histo_DEN->Add(DATA_RR_Run2012C_22Jan2013_histo_DEN);
		DATA_ReReco_total_histo_DEN->Add(DATA_RR_Run2012D_22Jan2013_histo_DEN);

		}
	else {
		//--- data PromptReco-------------------------------------------------------
		DATA_PR_Run2012A_13Jul2012_histo_NUM=(TH1F*)DATA_PR_Run2012A_13Jul2012_file->Get(titlehisto_NUM);
		DATA_PR_Run2012A_13Jul2012_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012A_13Jul2012_histo_DEN=(TH1F*)DATA_PR_Run2012A_13Jul2012_file->Get(titlehisto_DEN);
		DATA_PR_Run2012A_13Jul2012_histo_DEN->Rebin(rebin);
		
		DATA_PR_Run2012A_recover_06Aug2012_histo_NUM=(TH1F*)DATA_PR_Run2012A_recover_06Aug2012_file->Get(titlehisto_NUM);
		DATA_PR_Run2012A_recover_06Aug2012_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012A_recover_06Aug2012_histo_DEN=(TH1F*)DATA_PR_Run2012A_recover_06Aug2012_file->Get(titlehisto_DEN);
		DATA_PR_Run2012A_recover_06Aug2012_histo_DEN->Rebin(rebin);

		DATA_PR_Run2012B_13Jul2012_histo_NUM=(TH1F*)DATA_PR_Run2012B_13Jul2012_file->Get(titlehisto_NUM);
		DATA_PR_Run2012B_13Jul2012_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012B_13Jul2012_histo_DEN=(TH1F*)DATA_PR_Run2012B_13Jul2012_file->Get(titlehisto_DEN);
		DATA_PR_Run2012B_13Jul2012_histo_DEN->Rebin(rebin);

		DATA_PR_Run2012C_24Aug2012_histo_NUM=(TH1F*)DATA_PR_Run2012C_24Aug2012_file->Get(titlehisto_NUM);
		DATA_PR_Run2012C_24Aug2012_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012C_24Aug2012_histo_DEN=(TH1F*)DATA_PR_Run2012C_24Aug2012_file->Get(titlehisto_DEN);
		DATA_PR_Run2012C_24Aug2012_histo_DEN->Rebin(rebin);

		DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_NUM=(TH1F*)DATA_PR_Run2012C_EcalRecover_11Dec2012_file->Get(titlehisto_NUM);
		DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_DEN=(TH1F*)DATA_PR_Run2012C_EcalRecover_11Dec2012_file->Get(titlehisto_DEN);
		DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_DEN->Rebin(rebin);

		DATA_PR_Run2012C_PromptReco_histo_NUM=(TH1F*)DATA_PR_Run2012C_PromptReco_file->Get(titlehisto_NUM);
		DATA_PR_Run2012C_PromptReco_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012C_PromptReco_histo_DEN=(TH1F*)DATA_PR_Run2012C_PromptReco_file->Get(titlehisto_DEN);
		DATA_PR_Run2012C_PromptReco_histo_DEN->Rebin(rebin);

		DATA_PR_Run2012D_PromptReco_histo_NUM=(TH1F*)DATA_PR_Run2012D_PromptReco_file->Get(titlehisto_NUM);
		DATA_PR_Run2012D_PromptReco_histo_NUM->Rebin(rebin);
		DATA_PR_Run2012D_PromptReco_histo_DEN=(TH1F*)DATA_PR_Run2012D_PromptReco_file->Get(titlehisto_DEN);
		DATA_PR_Run2012D_PromptReco_histo_DEN->Rebin(rebin);
		
		cout << "DATA_PR_Run2012A_13Jul2012_NUM entries = " << DATA_PR_Run2012A_13Jul2012_histo_NUM->Integral() << endl;  
		cout << "DATA_PR_Run2012A_recover_06Aug2012_NUM entries = " << DATA_PR_Run2012A_recover_06Aug2012_histo_NUM->Integral() << endl;  
		cout << "DATA_PR_Run2012B_13Jul2012_NUM entries = " << DATA_PR_Run2012B_13Jul2012_histo_NUM->Integral() << endl;  
		cout << "DATA_PR_Run2012C_24Aug2012_NUM entries = " << DATA_PR_Run2012C_24Aug2012_histo_NUM->Integral() << endl;  
		cout << "DATA_PR_Run2012C_EcalRecover_11Dec2012_NUM entries = " << DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_NUM->Integral() << endl;  
		cout << "DATA_PR_Run2012C_PromptReco_NUM entries = " << DATA_PR_Run2012C_PromptReco_histo_NUM->Integral() << endl;  
		cout << "DATA_PR_Run2012D_PromptReco_NUM entries = " << DATA_PR_Run2012D_PromptReco_histo_NUM->Integral() << endl;  
		cout << endl;	
		cout << "DATA_PR_Run2012A_13Jul2012_DEN entries = " << DATA_PR_Run2012A_13Jul2012_histo_DEN->Integral() << endl;  
		cout << "DATA_PR_Run2012A_recover_06Aug2012_DEN entries = " << DATA_PR_Run2012A_recover_06Aug2012_histo_DEN->Integral() << endl;  
		cout << "DATA_PR_Run2012B_13Jul2012_DEN entries = " << DATA_PR_Run2012B_13Jul2012_histo_DEN->Integral() << endl;  
		cout << "DATA_PR_Run2012C_24Aug2012_DEN entries = " << DATA_PR_Run2012C_24Aug2012_histo_DEN->Integral() << endl;  
		cout << "DATA_PR_Run2012C_EcalRecover_11Dec2012_DEN entries = " << DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_DEN->Integral() << endl;  
		cout << "DATA_PR_Run2012C_PromptReco_DEN entries = " << DATA_PR_Run2012C_PromptReco_histo_DEN->Integral() << endl;  
		cout << "DATA_PR_Run2012D_PromptReco_DEN entries = " << DATA_PR_Run2012D_PromptReco_histo_DEN->Integral() << endl;  
		cout << endl;	

	
		DATA_PromptReco_total_histo_NUM = (TH1F*) DATA_PR_Run2012A_13Jul2012_histo_NUM->Clone("DATA_PromptReco_total_histo_NUM");
		DATA_PromptReco_total_histo_NUM->Add(DATA_PR_Run2012A_recover_06Aug2012_histo_NUM);
		DATA_PromptReco_total_histo_NUM->Add(DATA_PR_Run2012B_13Jul2012_histo_NUM);
		DATA_PromptReco_total_histo_NUM->Add(DATA_PR_Run2012C_24Aug2012_histo_NUM);
		DATA_PromptReco_total_histo_NUM->Add(DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_NUM);
		DATA_PromptReco_total_histo_NUM->Add(DATA_PR_Run2012C_PromptReco_histo_NUM);
		DATA_PromptReco_total_histo_NUM->Add(DATA_PR_Run2012D_PromptReco_histo_NUM);

		DATA_PromptReco_total_histo_DEN = (TH1F*) DATA_PR_Run2012A_13Jul2012_histo_DEN->Clone("DATA_PromptReco_total_histo_DEN");
		DATA_PromptReco_total_histo_DEN->Add(DATA_PR_Run2012A_recover_06Aug2012_histo_DEN);
		DATA_PromptReco_total_histo_DEN->Add(DATA_PR_Run2012B_13Jul2012_histo_DEN);
		DATA_PromptReco_total_histo_DEN->Add(DATA_PR_Run2012C_24Aug2012_histo_DEN);
		DATA_PromptReco_total_histo_DEN->Add(DATA_PR_Run2012C_EcalRecover_11Dec2012_histo_DEN);
		DATA_PromptReco_total_histo_DEN->Add(DATA_PR_Run2012C_PromptReco_histo_DEN);
		DATA_PromptReco_total_histo_DEN->Add(DATA_PR_Run2012D_PromptReco_histo_DEN);

	}

	if (data_ReReco) {
		DATA_total_histo_NUM = (TH1F*) DATA_ReReco_total_histo_NUM->Clone("DATA_total_histo_NUM");
		DATA_total_histo_DEN = (TH1F*) DATA_ReReco_total_histo_DEN->Clone("DATA_total_histo_DEN");
	}
	else{
		DATA_total_histo_NUM = (TH1F*) DATA_PromptReco_total_histo_NUM->Clone("DATA_total_histo_NUM");
		DATA_total_histo_DEN = (TH1F*) DATA_PromptReco_total_histo_DEN->Clone("DATA_total_histo_DEN");
	}

		DATA_total_histo = (TH1F*) DATA_total_histo_NUM->Clone("DATA_total_histo");
		DATA_total_histo->Sumw2();
		DATA_total_histo->SetLineColor(1);		
		DATA_total_histo->Divide(DATA_total_histo_DEN);	
	
	
	if(signal_MAD){				
		//--- MC signal GJets_HT-xToy ----------------------------------------------

		GJets_HT_40To100_histo_NUM=(TH1F*)GJets_HT_40To100_file->Get(titlehisto_NUM);
		GJets_HT_40To100_histo_NUM->Rebin(rebin);
		GJets_HT_40To100_histo_DEN=(TH1F*)GJets_HT_40To100_file->Get(titlehisto_DEN);
		GJets_HT_40To100_histo_DEN->Rebin(rebin);
		
		GJets_HT_100To200_histo_NUM=(TH1F*)GJets_HT_100To200_file->Get(titlehisto_NUM);
		GJets_HT_100To200_histo_NUM->Rebin(rebin);
		GJets_HT_100To200_histo_DEN=(TH1F*)GJets_HT_100To200_file->Get(titlehisto_DEN);
		GJets_HT_100To200_histo_DEN->Rebin(rebin);

		GJets_HT_200To400_histo_NUM=(TH1F*)GJets_HT_200To400_file->Get(titlehisto_NUM);
		GJets_HT_200To400_histo_NUM->Rebin(rebin);
		GJets_HT_200To400_histo_DEN=(TH1F*)GJets_HT_200To400_file->Get(titlehisto_DEN);
		GJets_HT_200To400_histo_DEN->Rebin(rebin);

		GJets_HT_400ToInf_histo_NUM=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto_NUM);
		GJets_HT_400ToInf_histo_NUM->Rebin(rebin);
		GJets_HT_400ToInf_histo_DEN=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto_DEN);
		GJets_HT_400ToInf_histo_DEN->Rebin(rebin);

		cout << "GJets_HT_40To100_NUM entries = " << GJets_HT_40To100_histo_NUM->Integral() << endl;
		cout << "GJets_HT_100To200_NUM entries = " << GJets_HT_100To200_histo_NUM->Integral() << endl;	
		cout << "GJets_HT_200To400_NUM entries = " << GJets_HT_200To400_histo_NUM->Integral() << endl;
		cout << "GJets_HT_400ToInf_NUM entries = " << GJets_HT_400ToInf_histo_NUM->Integral() << endl;
		cout << endl;
		cout << "GJets_HT_40To100_DEN entries = " << GJets_HT_40To100_histo_DEN->Integral() << endl;
		cout << "GJets_HT_100To200_DEN entries = " << GJets_HT_100To200_histo_DEN->Integral() << endl;	
		cout << "GJets_HT_200To400_DEN entries = " << GJets_HT_200To400_histo_DEN->Integral() << endl;
		cout << "GJets_HT_400ToInf_DEN entries = " << GJets_HT_400ToInf_histo_DEN->Integral() << endl;
		cout << endl;
		
		GJets_HT_xToy_total_histo_NUM = (TH1F*) GJets_HT_40To100_histo_NUM->Clone("GJets_HT_xToy_total_histo_NUM");
		//--- GJets_HT_xToy_total_histo_NUM->Sumw2();
		GJets_HT_xToy_total_histo_NUM->Add(GJets_HT_100To200_histo_NUM);
		GJets_HT_xToy_total_histo_NUM->Add(GJets_HT_200To400_histo_NUM);
		GJets_HT_xToy_total_histo_NUM->Add(GJets_HT_400ToInf_histo_NUM);  
		GJets_HT_xToy_total_histo_NUM->SetLineColor(1);
		GJets_HT_xToy_total_histo_NUM->SetFillColor(5);  //for colors comment out Sumw2 in code

		GJets_HT_xToy_total_histo_DEN = (TH1F*) GJets_HT_40To100_histo_DEN->Clone("GJets_HT_xToy_total_histo_DEN");
		//--- GJets_HT_xToy_total_histo_DEN->Sumw2();
		GJets_HT_xToy_total_histo_DEN->Add(GJets_HT_100To200_histo_DEN);
		GJets_HT_xToy_total_histo_DEN->Add(GJets_HT_200To400_histo_DEN);
		GJets_HT_xToy_total_histo_DEN->Add(GJets_HT_400ToInf_histo_DEN);  
		GJets_HT_xToy_total_histo_DEN->SetLineColor(1);
		GJets_HT_xToy_total_histo_DEN->SetFillColor(5);  //for colors comment out Sumw2 in code

	}

	else {	
		// MC signal G_Pt-XtoY --------------------------------------------------	
		G_Pt_15to30_histo_NUM=(TH1F*)G_Pt_15to30_file->Get(titlehisto_NUM);
		G_Pt_15to30_histo_NUM->Rebin(rebin);
		G_Pt_15to30_histo_DEN=(TH1F*)G_Pt_15to30_file->Get(titlehisto_DEN);
		G_Pt_15to30_histo_DEN->Rebin(rebin);

		G_Pt_30to50_histo_NUM=(TH1F*)G_Pt_30to50_file->Get(titlehisto_NUM);
		G_Pt_30to50_histo_NUM->Rebin(rebin);
		G_Pt_30to50_histo_DEN=(TH1F*)G_Pt_30to50_file->Get(titlehisto_DEN);
		G_Pt_30to50_histo_DEN->Rebin(rebin);

		G_Pt_50to80_histo_NUM=(TH1F*)G_Pt_50to80_file->Get(titlehisto_NUM);
		G_Pt_50to80_histo_NUM->Rebin(rebin);
		G_Pt_50to80_histo_DEN=(TH1F*)G_Pt_50to80_file->Get(titlehisto_DEN);
		G_Pt_50to80_histo_DEN->Rebin(rebin);

		G_Pt_80to120_histo_NUM=(TH1F*)G_Pt_80to120_file->Get(titlehisto_NUM);
		G_Pt_80to120_histo_NUM->Rebin(rebin);
		G_Pt_80to120_histo_DEN=(TH1F*)G_Pt_80to120_file->Get(titlehisto_DEN);
		G_Pt_80to120_histo_DEN->Rebin(rebin);

		G_Pt_120to170_histo_NUM=(TH1F*)G_Pt_120to170_file->Get(titlehisto_NUM);
		G_Pt_120to170_histo_NUM->Rebin(rebin);
		G_Pt_120to170_histo_DEN=(TH1F*)G_Pt_120to170_file->Get(titlehisto_DEN);
		G_Pt_120to170_histo_DEN->Rebin(rebin);
	
		G_Pt_170to300_histo_NUM=(TH1F*)G_Pt_170to300_file->Get(titlehisto_NUM);
		G_Pt_170to300_histo_NUM->Rebin(rebin);
		G_Pt_170to300_histo_DEN=(TH1F*)G_Pt_170to300_file->Get(titlehisto_DEN);
		G_Pt_170to300_histo_DEN->Rebin(rebin);

		G_Pt_300to470_histo_NUM=(TH1F*)G_Pt_300to470_file->Get(titlehisto_NUM);
		G_Pt_300to470_histo_NUM->Rebin(rebin);
		G_Pt_300to470_histo_DEN=(TH1F*)G_Pt_300to470_file->Get(titlehisto_DEN);
		G_Pt_300to470_histo_DEN->Rebin(rebin);

		G_Pt_470to800_histo_NUM=(TH1F*)G_Pt_470to800_file->Get(titlehisto_NUM);
		G_Pt_470to800_histo_NUM->Rebin(rebin);
		G_Pt_470to800_histo_DEN=(TH1F*)G_Pt_470to800_file->Get(titlehisto_DEN);
		G_Pt_470to800_histo_DEN->Rebin(rebin);

		G_Pt_800to1400_histo_NUM=(TH1F*)G_Pt_800to1400_file->Get(titlehisto_NUM);
		G_Pt_800to1400_histo_NUM->Rebin(rebin);
		G_Pt_800to1400_histo_DEN=(TH1F*)G_Pt_800to1400_file->Get(titlehisto_DEN);
		G_Pt_800to1400_histo_DEN->Rebin(rebin);

		G_Pt_1400to1800_histo_NUM=(TH1F*)G_Pt_1400to1800_file->Get(titlehisto_NUM);
		G_Pt_1400to1800_histo_NUM->Rebin(rebin);
		G_Pt_1400to1800_histo_DEN=(TH1F*)G_Pt_1400to1800_file->Get(titlehisto_DEN);
		G_Pt_1400to1800_histo_DEN->Rebin(rebin);

		G_Pt_1800_histo_NUM=(TH1F*)G_Pt_1800_file->Get(titlehisto_NUM);
		G_Pt_1800_histo_NUM->Rebin(rebin);
		G_Pt_1800_histo_DEN=(TH1F*)G_Pt_1800_file->Get(titlehisto_DEN);
		G_Pt_1800_histo_DEN->Rebin(rebin);

		cout << "G_Pt_15to30_NUM entries = " << G_Pt_15to30_histo_NUM->Integral() << endl;
		cout << "G_Pt_30to50_NUM entries = " << G_Pt_30to50_histo_NUM->Integral() << endl;
		cout << "G_Pt_50to80_NUM entries = " << G_Pt_50to80_histo_NUM->Integral() << endl;
		cout << "G_Pt_80to120_NUM entries = " << G_Pt_80to120_histo_NUM->Integral() << endl;
		cout << "G_Pt_120to170_NUM entries = " << G_Pt_120to170_histo_NUM->Integral() << endl;
		cout << "G_Pt_170to300_NUM entries = " << G_Pt_170to300_histo_NUM->Integral() << endl;
		cout << "G_Pt_300to470_NUM entries = " << G_Pt_300to470_histo_NUM->Integral() << endl;
		cout << "G_Pt_470to800_NUM entries = " << G_Pt_470to800_histo_NUM->Integral() << endl;
		cout << "G_Pt_800to1400_NUM entries = " << G_Pt_800to1400_histo_NUM->Integral() << endl;
		cout << "G_Pt_1400to1800_NUM entries = " << G_Pt_1400to1800_histo_NUM->Integral() << endl;
		cout << "G_Pt_1800_NUM entries = " << G_Pt_1800_histo_NUM->Integral() << endl;
		cout << endl;
		cout << "G_Pt_15to30_DEN entries = " << G_Pt_15to30_histo_DEN->Integral() << endl;
		cout << "G_Pt_30to50_DEN entries = " << G_Pt_30to50_histo_DEN->Integral() << endl;
		cout << "G_Pt_50to80_DEN entries = " << G_Pt_50to80_histo_DEN->Integral() << endl;
		cout << "G_Pt_80to120_DEN entries = " << G_Pt_80to120_histo_DEN->Integral() << endl;
		cout << "G_Pt_120to170_DEN entries = " << G_Pt_120to170_histo_DEN->Integral() << endl;
		cout << "G_Pt_170to300_DEN entries = " << G_Pt_170to300_histo_DEN->Integral() << endl;
		cout << "G_Pt_300to470_DEN entries = " << G_Pt_300to470_histo_DEN->Integral() << endl;
		cout << "G_Pt_470to800_DEN entries = " << G_Pt_470to800_histo_DEN->Integral() << endl;
		cout << "G_Pt_800to1400_DEN entries = " << G_Pt_800to1400_histo_DEN->Integral() << endl;
		cout << "G_Pt_1400to1800_DEN entries = " << G_Pt_1400to1800_histo_DEN->Integral() << endl;
		cout << "G_Pt_1800_DEN entries = " << G_Pt_1800_histo_DEN->Integral() << endl;
		cout << endl;


		G_Pt_XtoY_total_histo_NUM = (TH1F*) G_Pt_15to30_histo_NUM->Clone("G_Pt_XtoY_total_histo_NUM");
		//--- G_Pt_XtoY_total_histo_NUM->Sumw2();
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_30to50_histo_NUM);
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_50to80_histo_NUM);  
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_80to120_histo_NUM);  
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_120to170_histo_NUM);  
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_170to300_histo_NUM);  
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_300to470_histo_NUM);  
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_470to800_histo_NUM);  		
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_800to1400_histo_NUM);
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_1400to1800_histo_NUM);	  	
		G_Pt_XtoY_total_histo_NUM->Add(G_Pt_1800_histo_NUM);	  	
		G_Pt_XtoY_total_histo_NUM->SetLineColor(1);
		G_Pt_XtoY_total_histo_NUM->SetFillColor(kGreen+2);  //for colors comment out Sumw2 in code

		G_Pt_XtoY_total_histo_DEN = (TH1F*) G_Pt_15to30_histo_DEN->Clone("G_Pt_XtoY_total_histo_DEN");
		//--- G_Pt_XtoY_total_histo_DEN->Sumw2();
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_30to50_histo_DEN);
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_50to80_histo_DEN);  
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_80to120_histo_DEN);  
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_120to170_histo_DEN);  
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_170to300_histo_DEN);  
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_300to470_histo_DEN);  
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_470to800_histo_DEN);  		
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_800to1400_histo_DEN);
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_1400to1800_histo_DEN);	  	
		G_Pt_XtoY_total_histo_DEN->Add(G_Pt_1800_histo_DEN);	  	
		G_Pt_XtoY_total_histo_DEN->SetLineColor(1);
		G_Pt_XtoY_total_histo_DEN->SetFillColor(kGreen+2);  //for colors comment out Sumw2 in code

	}
	
	// MC signal DiPhotonJets --------------------------------------------------
	DiPhotonJets_histo_NUM=(TH1F*)DiPhotonJets_file->Get(titlehisto_NUM);
	DiPhotonJets_histo_NUM->Rebin(rebin);
	DiPhotonJets_histo_DEN=(TH1F*)DiPhotonJets_file->Get(titlehisto_DEN);
	DiPhotonJets_histo_DEN->Rebin(rebin);
	
	cout << "DiPhotonJets_NUM entries = " << DiPhotonJets_histo_NUM->Integral() << endl;
	cout << endl;
	cout << "DiPhotonJets_DEN entries = " << DiPhotonJets_histo_DEN->Integral() << endl;
	cout << endl;

	DiPhotonJets_total_histo_NUM = (TH1F*) DiPhotonJets_histo_NUM->Clone("DiPhotonJets_total_histo_NUM");
	//--- DiPhotonJets_total_histo_NUM->Sumw2();
	DiPhotonJets_total_histo_NUM->SetLineColor(1);
	DiPhotonJets_total_histo_NUM->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	DiPhotonJets_total_histo_DEN = (TH1F*) DiPhotonJets_histo_DEN->Clone("DiPhotonJets_total_histo_DEN");
	//--- DiPhotonJets_total_histo_DEN->Sumw2();
	DiPhotonJets_total_histo_DEN->SetLineColor(1);
	DiPhotonJets_total_histo_DEN->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code


	if (!background_QCD){	
		//--- MC background QCD_Pt_x_y EMEnriched ----------------------------------	
		QCD_Pt_20_30_EMEnriched_histo_NUM=(TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto_NUM);
		QCD_Pt_20_30_EMEnriched_histo_NUM->Rebin(rebin);
		QCD_Pt_20_30_EMEnriched_histo_DEN=(TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto_DEN);
		QCD_Pt_20_30_EMEnriched_histo_DEN->Rebin(rebin);

		QCD_Pt_30_80_EMEnriched_histo_NUM=(TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto_NUM);
		QCD_Pt_30_80_EMEnriched_histo_NUM->Rebin(rebin);
		QCD_Pt_30_80_EMEnriched_histo_DEN=(TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto_DEN);
		QCD_Pt_30_80_EMEnriched_histo_DEN->Rebin(rebin);

		QCD_Pt_80_170_EMEnriched_histo_NUM=(TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto_NUM);
		QCD_Pt_80_170_EMEnriched_histo_NUM->Rebin(rebin);
		QCD_Pt_80_170_EMEnriched_histo_DEN=(TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto_DEN);
		QCD_Pt_80_170_EMEnriched_histo_DEN->Rebin(rebin);

		QCD_Pt_170_250_EMEnriched_histo_NUM=(TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto_NUM);
		QCD_Pt_170_250_EMEnriched_histo_NUM->Rebin(rebin);
		QCD_Pt_170_250_EMEnriched_histo_DEN=(TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto_DEN);
		QCD_Pt_170_250_EMEnriched_histo_DEN->Rebin(rebin);

		QCD_Pt_250_350_EMEnriched_histo_NUM=(TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto_NUM);
		QCD_Pt_250_350_EMEnriched_histo_NUM->Rebin(rebin);
		QCD_Pt_250_350_EMEnriched_histo_DEN=(TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto_DEN);
		QCD_Pt_250_350_EMEnriched_histo_DEN->Rebin(rebin);

		QCD_Pt_350_EMEnriched_histo_NUM=(TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto_NUM);
		QCD_Pt_350_EMEnriched_histo_NUM->Rebin(rebin);
		QCD_Pt_350_EMEnriched_histo_DEN=(TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto_DEN);
		QCD_Pt_350_EMEnriched_histo_DEN->Rebin(rebin);

		cout << "QCD_Pt_20_30_EMEnriched_NUM entries = " << QCD_Pt_20_30_EMEnriched_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_30_80_EMEnriched_NUM entries = " << QCD_Pt_30_80_EMEnriched_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_80_170_EMEnriched_NUM entries = " << QCD_Pt_80_170_EMEnriched_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_170_250_EMEnriched_NUM entries = " << QCD_Pt_170_250_EMEnriched_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_250_350_EMEnriched_NUM entries = " << QCD_Pt_250_350_EMEnriched_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_350_EMEnriched_NUM entries = " << QCD_Pt_350_EMEnriched_histo_NUM->Integral() << endl;
		cout << endl;

		cout << "QCD_Pt_20_30_EMEnriched_DEN entries = " << QCD_Pt_20_30_EMEnriched_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_30_80_EMEnriched_DEN entries = " << QCD_Pt_30_80_EMEnriched_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_80_170_EMEnriched_DEN entries = " << QCD_Pt_80_170_EMEnriched_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_170_250_EMEnriched_DEN entries = " << QCD_Pt_170_250_EMEnriched_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_250_350_EMEnriched_DEN entries = " << QCD_Pt_250_350_EMEnriched_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_350_EMEnriched_DEN entries = " << QCD_Pt_350_EMEnriched_histo_DEN->Integral() << endl;
		cout << endl;


		QCD_Pt_x_y_EMEnriched_total_histo_NUM = (TH1F*) QCD_Pt_20_30_EMEnriched_histo_NUM->Clone("QCD_Pt_x_y_EMEnriched_total_histo_NUM");
		//	QCD_Pt_x_y_EMEnriched_total_histo_NUM->Sumw2();
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->Add(QCD_Pt_30_80_EMEnriched_histo_NUM);
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->Add(QCD_Pt_80_170_EMEnriched_histo_NUM);  
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->Add(QCD_Pt_170_250_EMEnriched_histo_NUM);  
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->Add(QCD_Pt_250_350_EMEnriched_histo_NUM);  
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->Add(QCD_Pt_350_EMEnriched_histo_NUM);  
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->SetLineColor(1);
		QCD_Pt_x_y_EMEnriched_total_histo_NUM->SetFillColor(kMagenta+2);

		QCD_Pt_x_y_EMEnriched_total_histo_DEN = (TH1F*) QCD_Pt_20_30_EMEnriched_histo_DEN->Clone("QCD_Pt_x_y_EMEnriched_total_histo_DEN");
		//	QCD_Pt_x_y_EMEnriched_total_histo_DEN->Sumw2();
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->Add(QCD_Pt_30_80_EMEnriched_histo_DEN);
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->Add(QCD_Pt_80_170_EMEnriched_histo_DEN);  
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->Add(QCD_Pt_170_250_EMEnriched_histo_DEN);  
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->Add(QCD_Pt_250_350_EMEnriched_histo_DEN);  
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->Add(QCD_Pt_350_EMEnriched_histo_DEN);  
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->SetLineColor(1);
		QCD_Pt_x_y_EMEnriched_total_histo_DEN->SetFillColor(kMagenta+2);


		//--- MC background QCD_Pt_x_y BCtoE ----------------------------------
		QCD_Pt_20_30_BCtoE_histo_NUM=(TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto_NUM);
		QCD_Pt_20_30_BCtoE_histo_NUM->Rebin(rebin);
		QCD_Pt_20_30_BCtoE_histo_DEN=(TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto_DEN);
		QCD_Pt_20_30_BCtoE_histo_DEN->Rebin(rebin);

		QCD_Pt_30_80_BCtoE_histo_NUM=(TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto_NUM);
		QCD_Pt_30_80_BCtoE_histo_NUM->Rebin(rebin);
		QCD_Pt_30_80_BCtoE_histo_DEN=(TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto_DEN);
		QCD_Pt_30_80_BCtoE_histo_DEN->Rebin(rebin);

		QCD_Pt_80_170_BCtoE_histo_NUM=(TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto_NUM);
		QCD_Pt_80_170_BCtoE_histo_NUM->Rebin(rebin);
		QCD_Pt_80_170_BCtoE_histo_DEN=(TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto_DEN);
		QCD_Pt_80_170_BCtoE_histo_DEN->Rebin(rebin);

		QCD_Pt_170_250_BCtoE_histo_NUM=(TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto_NUM);
		QCD_Pt_170_250_BCtoE_histo_NUM->Rebin(rebin);
		QCD_Pt_170_250_BCtoE_histo_DEN=(TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto_DEN);
		QCD_Pt_170_250_BCtoE_histo_DEN->Rebin(rebin);

		QCD_Pt_250_350_BCtoE_histo_NUM=(TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto_NUM);
		QCD_Pt_250_350_BCtoE_histo_NUM->Rebin(rebin);
		QCD_Pt_250_350_BCtoE_histo_DEN=(TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto_DEN);
		QCD_Pt_250_350_BCtoE_histo_DEN->Rebin(rebin);

		QCD_Pt_350_BCtoE_histo_NUM=(TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto_NUM);
		QCD_Pt_350_BCtoE_histo_NUM->Rebin(rebin);
		QCD_Pt_350_BCtoE_histo_DEN=(TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto_DEN);
		QCD_Pt_350_BCtoE_histo_DEN->Rebin(rebin);

		cout << "QCD_Pt_20_30_BCtoE_NUM entries = " << QCD_Pt_20_30_BCtoE_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_30_80_BCtoE_NUM entries = " << QCD_Pt_30_80_BCtoE_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_80_170_BCtoE_NUM entries = " << QCD_Pt_80_170_BCtoE_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_170_250_BCtoE_NUM entries = " << QCD_Pt_170_250_BCtoE_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_250_350_BCtoE_NUM entries = " << QCD_Pt_250_350_BCtoE_histo_NUM->Integral() << endl;
		cout << "QCD_Pt_350_BCtoE_NUM entries = " << QCD_Pt_350_BCtoE_histo_NUM->Integral() << endl;
		cout << endl;
		cout << "QCD_Pt_20_30_BCtoE_DEN entries = " << QCD_Pt_20_30_BCtoE_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_30_80_BCtoE_DEN entries = " << QCD_Pt_30_80_BCtoE_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_80_170_BCtoE_DEN entries = " << QCD_Pt_80_170_BCtoE_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_170_250_BCtoE_DEN entries = " << QCD_Pt_170_250_BCtoE_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_250_350_BCtoE_DEN entries = " << QCD_Pt_250_350_BCtoE_histo_DEN->Integral() << endl;
		cout << "QCD_Pt_350_BCtoE_DEN entries = " << QCD_Pt_350_BCtoE_histo_DEN->Integral() << endl;
		cout << endl;
		
		QCD_Pt_x_y_BCtoE_total_histo_NUM = (TH1F*) QCD_Pt_20_30_BCtoE_histo_NUM->Clone("QCD_Pt_x_y_BCtoE_total_histo_NUM");
		//	QCD_Pt_x_y_BCtoE_total_histo_NUM->Sumw2();
		QCD_Pt_x_y_BCtoE_total_histo_NUM->Add(QCD_Pt_30_80_BCtoE_histo_NUM);
		QCD_Pt_x_y_BCtoE_total_histo_NUM->Add(QCD_Pt_80_170_BCtoE_histo_NUM);  
		QCD_Pt_x_y_BCtoE_total_histo_NUM->Add(QCD_Pt_170_250_BCtoE_histo_NUM);  
		QCD_Pt_x_y_BCtoE_total_histo_NUM->Add(QCD_Pt_250_350_BCtoE_histo_NUM);  
		QCD_Pt_x_y_BCtoE_total_histo_NUM->Add(QCD_Pt_350_BCtoE_histo_NUM);  
		QCD_Pt_x_y_BCtoE_total_histo_NUM->SetLineColor(1);
		QCD_Pt_x_y_BCtoE_total_histo_NUM->SetFillColor(kBlue-7);

		QCD_Pt_x_y_BCtoE_total_histo_DEN = (TH1F*) QCD_Pt_20_30_BCtoE_histo_DEN->Clone("QCD_Pt_x_y_BCtoE_total_histo_DEN");
		//	QCD_Pt_x_y_BCtoE_total_histo_DEN->Sumw2();
		QCD_Pt_x_y_BCtoE_total_histo_DEN->Add(QCD_Pt_30_80_BCtoE_histo_DEN);
		QCD_Pt_x_y_BCtoE_total_histo_DEN->Add(QCD_Pt_80_170_BCtoE_histo_DEN);  
		QCD_Pt_x_y_BCtoE_total_histo_DEN->Add(QCD_Pt_170_250_BCtoE_histo_DEN);  
		QCD_Pt_x_y_BCtoE_total_histo_DEN->Add(QCD_Pt_250_350_BCtoE_histo_DEN);  
		QCD_Pt_x_y_BCtoE_total_histo_DEN->Add(QCD_Pt_350_BCtoE_histo_DEN);  
		QCD_Pt_x_y_BCtoE_total_histo_DEN->SetLineColor(1);
		QCD_Pt_x_y_BCtoE_total_histo_DEN->SetFillColor(kBlue-7);

	}
	else {	
		// MC background QCD HT-xToy --------------------------------------------
		QCD_HT_100To250_histo_NUM=(TH1F*)QCD_HT_100To250_file->Get(titlehisto_NUM);
		QCD_HT_100To250_histo_NUM->Rebin(rebin);
		QCD_HT_100To250_histo_DEN=(TH1F*)QCD_HT_100To250_file->Get(titlehisto_DEN);
		QCD_HT_100To250_histo_DEN->Rebin(rebin);

		QCD_HT_250To500_histo_NUM=(TH1F*)QCD_HT_250To500_file->Get(titlehisto_NUM);
		QCD_HT_250To500_histo_NUM->Rebin(rebin);
		QCD_HT_250To500_histo_DEN=(TH1F*)QCD_HT_250To500_file->Get(titlehisto_DEN);
		QCD_HT_250To500_histo_DEN->Rebin(rebin);

		QCD_HT_500To1000_histo_NUM=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto_NUM);
		QCD_HT_500To1000_histo_NUM->Rebin(rebin);
		QCD_HT_500To1000_histo_DEN=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto_DEN);
		QCD_HT_500To1000_histo_DEN->Rebin(rebin);

		QCD_HT_1000ToInf_histo_NUM=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto_NUM);
		QCD_HT_1000ToInf_histo_NUM->Rebin(rebin);
		QCD_HT_1000ToInf_histo_DEN=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto_DEN);
		QCD_HT_1000ToInf_histo_DEN->Rebin(rebin);

		cout << "QCD_HT_100To250_NUM entries " << QCD_HT_100To250_histo_NUM->Integral() << endl;  
		cout << "QCD_HT_250To500_NUM entries " << QCD_HT_250To500_histo_NUM->Integral() << endl;  
		cout << "QCD_HT_500To1000_NUM entries " << QCD_HT_500To1000_histo_NUM->Integral() << endl;
		cout << "QCD_HT_1000ToInf_NUM entries " << QCD_HT_1000ToInf_histo_NUM->Integral() << endl;
		cout << endl;
	
		cout << "QCD_HT_100To250_DEN entries " << QCD_HT_100To250_histo_DEN->Integral() << endl;  
		cout << "QCD_HT_250To500_DEN entries " << QCD_HT_250To500_histo_DEN->Integral() << endl;  
		cout << "QCD_HT_500To1000_DEN entries " << QCD_HT_500To1000_histo_DEN->Integral() << endl;
		cout << "QCD_HT_1000ToInf_DEN entries " << QCD_HT_1000ToInf_histo_DEN->Integral() << endl;
		cout << endl;


		QCD_HT_xToy_total_histo_NUM = (TH1F*) QCD_HT_100To250_histo_NUM->Clone("QCD_HT_xToy_total_histo_NUM");
		//	QCD_HT_xToy_total_histo_NUM->Sumw2();
		QCD_HT_xToy_total_histo_NUM->Add(QCD_HT_250To500_histo_NUM);
		QCD_HT_xToy_total_histo_NUM->Add(QCD_HT_500To1000_histo_NUM);  
		QCD_HT_xToy_total_histo_NUM->Add(QCD_HT_1000ToInf_histo_NUM);  
		QCD_HT_xToy_total_histo_NUM->SetLineColor(1);
		QCD_HT_xToy_total_histo_NUM->SetFillColor(kRed+2);

		QCD_HT_xToy_total_histo_DEN = (TH1F*) QCD_HT_100To250_histo_DEN->Clone("QCD_HT_xToy_total_histo_DEN");
		//	QCD_HT_xToy_total_histo_DEN->Sumw2();
		QCD_HT_xToy_total_histo_DEN->Add(QCD_HT_250To500_histo_DEN);
		QCD_HT_xToy_total_histo_DEN->Add(QCD_HT_500To1000_histo_DEN);  
		QCD_HT_xToy_total_histo_DEN->Add(QCD_HT_1000ToInf_histo_DEN);  
		QCD_HT_xToy_total_histo_DEN->SetLineColor(1);
		QCD_HT_xToy_total_histo_DEN->SetFillColor(kRed+2);

	}

	if (signal_MAD) {
		MC_total_histo_NUM = (TH1F*) GJets_HT_xToy_total_histo_NUM->Clone("MC_total_histo_NUM");
		MC_total_histo_DEN = (TH1F*) GJets_HT_xToy_total_histo_DEN->Clone("MC_total_histo_DEN");
	}
	else{
		MC_total_histo_NUM = (TH1F*) G_Pt_XtoY_total_histo_NUM->Clone("MC_total_histo_NUM");
		MC_total_histo_DEN = (TH1F*) G_Pt_XtoY_total_histo_DEN->Clone("MC_total_histo_DEN");
	}
		MC_total_histo_NUM->Add(DiPhotonJets_total_histo_NUM);
		MC_total_histo_DEN->Add(DiPhotonJets_total_histo_DEN);
	if (!background_QCD){	
		MC_total_histo_NUM->Add(QCD_Pt_x_y_EMEnriched_total_histo_NUM);
		MC_total_histo_DEN->Add(QCD_Pt_x_y_EMEnriched_total_histo_DEN);	

		MC_total_histo_NUM->Add(QCD_Pt_x_y_BCtoE_total_histo_NUM);
		MC_total_histo_DEN->Add(QCD_Pt_x_y_BCtoE_total_histo_DEN);	
	}
	else{
		MC_total_histo_NUM->Add(QCD_HT_xToy_total_histo_NUM);
		MC_total_histo_DEN->Add(QCD_HT_xToy_total_histo_DEN);
	}
	
		MC_total_histo = (TH1F*) MC_total_histo_NUM->Clone("MC_total_histo");
//		MC_total_histo->Sumw2();
		MC_total_histo->SetLineColor(2);
		MC_total_histo->SetLineWidth(2);
		MC_total_histo->SetFillColor(0);
		MC_total_histo->Divide(MC_total_histo_DEN);	

		
	// ==================================== load Canvas
	
  TCanvas *Canva = new TCanvas(titlehisto_NUM,titlehisto_NUM);  
	TPad* upperPad = new TPad("upperPad", "upperPad",.005, .25, .995, .995);
  TPad* lowerPad = new TPad("lowerPad", "lowerPad",.005, .005, .995, .2475);
  upperPad->Draw(); 			       
  lowerPad->Draw(); 

	TH1F *ratio_histo_NUM = new TH1F();
	ratio_histo_NUM = (TH1F*) DATA_total_histo->Clone("ratio_histo_NUM");	
	ratio_histo_NUM->Sumw2();


	TH1F *ratio_histo_DEN = new TH1F;
	ratio_histo_DEN = (TH1F*) MC_total_histo->Clone("ratio_histo_DEN");	
	ratio_histo_DEN->Sumw2();
	ratio_histo_DEN->Sumw2();

	
	TH1F *ratio_histo = (TH1F*) ratio_histo_NUM->Clone("ratio_histo");
	ratio_histo->Sumw2();
	ratio_histo->Divide(ratio_histo_DEN);

	int Nbins;
	double X_min, X_max;

	Nbins = ratio_histo->GetNbinsX();

	// upper Pad
  upperPad->cd();
  
  TLine *line_99e9 = new TLine(xbox_min,0.999,xbox_max,0.999);
  line_99e9->SetLineColor(kBlack);
  line_99e9->Draw();

  TLine *line_99 = new TLine(xbox_min,0.99,xbox_max,0.99);
  line_99->SetLineColor(kRed);
  line_99->Draw();
  
  TLine *line_95 = new TLine(xbox_min,0.95,xbox_max,0.95);
  line_95->SetLineColor(kBlue);
  line_95->Draw();
  
/*
	if (x_min != -999 && x_max != -999){
		if (x_max == MC_total_histo->GetMaximum()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == MC_total_histo->GetMinimum()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		MC_total_histo->Draw("");
		MC_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);		
	}
	
	MC_total_histo->Draw("histo");
*/


	if (x_min != -999 && x_max != -999){
		if (x_max == DATA_total_histo->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == DATA_total_histo->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		DATA_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);
	}

	DATA_total_histo->SetMarkerSize(0.7);
	DATA_total_histo->SetMarkerStyle(20);
	DATA_total_histo->Draw("E");


	if (x_min != -999 && x_max != -999){
		if (x_max == MC_total_histo->GetMaximum()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == MC_total_histo->GetMinimum()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		MC_total_histo->Draw("SAME");
		MC_total_histo->GetXaxis()->SetRangeUser(X_min,X_max);		
	}
	
	MC_total_histo->Draw("histo SAME");

	DATA_total_histo->Draw("ESAME");
//	gPad->SetLogy();
	DATA_total_histo->Draw("AXIS X+ Y+ SAME");
	DATA_total_histo->Draw("AXIS SAME");
	DATA_total_histo->GetXaxis()->SetTitle(namevariable);
	DATA_total_histo->GetXaxis()->SetTitleSize(0.05);
	DATA_total_histo->GetYaxis()->SetTitle("Turn-On Ratio");

	TLegend *leg =new TLegend(0.6068,0.5478,0.8188,0.7480);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
 	if (data_ReReco) leg->AddEntry(DATA_total_histo,"Data","pL");
	else leg->AddEntry(DATA_total_histo,"Data PromptReco","pL");
	leg->AddEntry(MC_total_histo,"MC","l");
	leg->Draw();

  TPaveText* text_1 = new TPaveText(0.1194,0.9310,0.3313,0.9780,"NDC");
  text_1->SetFillColor(0);
  text_1->SetFillStyle(0);
  text_1->SetBorderSize(0);
  text_1->AddText("CMS Preliminary");
  text_1->SetTextAlign(11);
  text_1->Draw();

  TPaveText* text_2 = new TPaveText(0.5627,0.9310,0.8678,0.9780,"NDC");
  text_2->SetFillColor(0);
  text_2->SetFillStyle(0);
  text_2->SetBorderSize(0);
  if (data_ReReco) text_2->AddText("#sqrt{s} = 8 TeV, L = 19.71 fb^{-1}");
  else text_2->AddText("#sqrt{s} = 8 TeV, L = 19.03 fb^{-1}");
  text_2->SetTextAlign(11);
  text_2->Draw();


	
	// lower Pad
	lowerPad-> cd();
	
	float xbox_min,xbox_max;
	if (x_min == -999 && x_max == -999){
		xbox_min = ratio_histo->GetXaxis()->GetXmin();
		xbox_max = ratio_histo->GetXaxis()->GetXmax();
	}
	else {
		xbox_min = x_min;
		xbox_max = x_max;
	}	

	ratio_histo->Draw("");
	TBox *box_1 = new TBox(xbox_min,0.9,xbox_max,1.1);
	box_1->SetFillColor(22);
	box_1->Draw();

	TBox *box_2 = new TBox(xbox_min,0.95,xbox_max,1.05);
	box_2->SetFillColor(14);
	box_2->Draw();

  TLine *line = new TLine(xbox_min,1,xbox_max,1);
  line->SetLineColor(kBlack);
  line->Draw();

	if (x_min != -999 && x_max != -999){
		if (x_max == ratio_histo->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == ratio_histo->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

	ratio_histo->GetXaxis()->SetRangeUser(X_min,X_max);
	}
	
	ratio_histo->Draw("P E0 SAME");
	ratio_histo->Draw("AXIS X+ Y+ SAME");
	ratio_histo->Draw("AXIS SAME");
  ratio_histo->GetXaxis()->SetTitle("");
	ratio_histo->GetYaxis()->SetTitle("Data/MC");
	ratio_histo->GetYaxis()->SetTitleSize(0.10);
	ratio_histo->GetYaxis()->SetTitleOffset(0.6);
	ratio_histo->GetYaxis()->SetLabelSize(0.1);
	ratio_histo->GetXaxis()->SetLabelSize(0.1);
	ratio_histo->GetYaxis()->SetRangeUser(0.75,1.25);
	ratio_histo->GetYaxis()->SetNdivisions(505, "kTRUE");
	ratio_histo->SetMarkerStyle(20);
	ratio_histo->SetMarkerColor(kBlue);
	ratio_histo->SetMarkerSize(0.7);
	ratio_histo->SetLineColor(kBlue);

	root_string = ".root";
	pdf_string = ".pdf";
  Canva->SaveAs((folder_s + geo_s + SB_folder + pdf_folder + titleh_NUM + pdf_string).c_str());
  Canva->SaveAs((folder_s + geo_s + SB_folder + root_folder + titleh_NUM + root_string).c_str());
	Canva->Close();

	// ==================================== close files

 	if (data_ReReco) {
		DATA_RR_Run2012A_22Jan2013_file->Close();
		DATA_RR_Run2012B_22Jan2013_file->Close();
		DATA_RR_Run2012C_22Jan2013_file->Close();
		DATA_RR_Run2012D_22Jan2013_file->Close();
	}
	else{
		DATA_PR_Run2012A_13Jul2012_file->Close();
		DATA_PR_Run2012A_recover_06Aug2012_file->Close();
		DATA_PR_Run2012B_13Jul2012_file->Close();
		DATA_PR_Run2012C_24Aug2012_file->Close();
		DATA_PR_Run2012C_EcalRecover_11Dec2012_file->Close();
		DATA_PR_Run2012C_PromptReco_file->Close();
		DATA_PR_Run2012D_PromptReco_file->Close();
	}
	
	if(signal_MAD){	
		GJets_HT_40To100_file->Close();	
		GJets_HT_100To200_file->Close();	
		GJets_HT_200To400_file->Close();
		GJets_HT_400ToInf_file->Close(); 
	}
	else{
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
	}
	
	DiPhotonJets_file->Close();

	if (!background_QCD){
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
	}
	else {
		QCD_HT_100To250_file->Close();  
		QCD_HT_250To500_file->Close();
		QCD_HT_500To1000_file->Close();
		QCD_HT_1000ToInf_file->Close(); 
	}
	
}



void TurnOn_plots(){

	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_1_", "SelectedPhotons_Pt_1_D1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_2_", "SelectedPhotons_Pt_1_D1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_4_", "SelectedPhotons_Pt_1_D8_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_8_", "SelectedPhotons_Pt_1_D8_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_16_", "SelectedPhotons_Pt_1_D8_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_32_", "SelectedPhotons_Pt_1_D8_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_64_", "SelectedPhotons_Pt_1_D8_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_128_", "SelectedPhotons_Pt_1_D32_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_256_", "SelectedPhotons_Pt_1_D32_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_512_", "SelectedPhotons_Pt_1_D128_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_1024_", "SelectedPhotons_Pt_1_D128_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_2048_", "SelectedPhotons_Pt_1_D512_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	TurnOn_comparestack("SelectedPhotons_Pt_1_sel_4096_", "SelectedPhotons_Pt_1_D2048_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, 30, 200);
	
}	




