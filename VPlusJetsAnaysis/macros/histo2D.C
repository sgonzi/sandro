#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <string>
#include <stdio.h>
#include <TH1.h>
#include <TH2.h>
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
#include <TColor.h>
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
  myStyle->SetPadRightMargin(0.19);

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

void palette(){

	const Int_t NRGBs = 5;
	const Int_t NCont = 255;

	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
}


void histo2D(const char* titleh, string string_pT, const int rebinX, const int rebinY, const double x_min, const double x_max, const double y_min, const double y_max){

  // Usage is: .L comparestack.C++
  //       ie: comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 1);

	setMYStyle();
	palette();

	// ==================================== choose the tools

	string folder = "7_results_2013_06_25"; // analysis folder

	char geo[100] = "barrel";                // "barrel", "endcaps" or "total"

	bool inv_sigmaietaieta = true;          // inverted sigmaietaieta cut
	bool inv_isolation = false;              // inverted isolation set cut

	bool signal_MAD = true;                  // true: signal = MADGRAPH; false: signal = PYTHIA
	bool background_QCD = true;             // true: background = MADGRAPH not filtered (QCD HT)
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
	string inverted = "_inv";
	string sigmaietaieta_s = "_sigmaietaieta";
	string isolation_s = "_isolation";
	if (inv_sigmaietaieta && !inv_isolation) {
		root_string = inverted + sigmaietaieta_s + root_string;	
	}	
	else if (!inv_sigmaietaieta && inv_isolation) {
		root_string = inverted + isolation_s + root_string;
		}		
	else {
		root_string = root_string;
	}	
	
	stringstream ss_r;
	char root_char[100];
	ss_r << root_string;
	ss_r >> root_char;

	string address = folder_s + geo_s + out_files;


	// ==================================== exception controls

	if (inv_sigmaietaieta && inv_isolation){
		cout << "ERROR: you are trying to invert both SIGMAIETAIETA and ISOLATION cuts" << endl << endl;
		throw cms::Exception("WrongBool");
	}
	if (!(Geo == "barrel" || Geo == "endcaps" || Geo == "total")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps\" or \"total\"). You writed: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}	


	// ==================================== assign files names

					
//	Char_t GJets_HT_40To100_name[100];
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

	
	if(signal_MAD){
//		sprintf(GJets_HT_40To100_name,"MC_GJets_HT-40To100_histos_%d_%s%s",itype, geo, root_char);
		sprintf(GJets_HT_100To200_name,"MC_GJets_HT-100To200_histos_%d_%s%s",itype, geo, root_char);	
		sprintf(GJets_HT_200To400_name,"MC_GJets_HT-200To400_histos_%d_%s%s",itype, geo, root_char);
		sprintf(GJets_HT_400ToInf_name,"MC_GJets_HT-400ToInf_histos_%d_%s%s",itype, geo, root_char);

//		cout << "GJets file 21 is: " << GJets_HT_40To100_name << endl;
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

//	TFile *GJets_HT_40To100_file;
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


	if(signal_MAD){	
		//GJets_HT_40To100_file = new TFile((address+GJets_HT_40To100_name).c_str());	
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

	// ==================================== load TH2F

	Char_t titlehisto[100];

	strcpy(titlehisto,titleh);

	cout << "========================" <<endl;	
	cout << endl;	

	cout << "Analyzing Histogram " << titlehisto << endl;

	cout << endl;	
	cout << "========================" <<endl;	
	cout << endl;	

//	TH2F *GJets_HT_40To100_histo;
	TH2F *GJets_HT_100To200_histo;
	TH2F *GJets_HT_200To400_histo;
	TH2F *GJets_HT_400ToInf_histo;
	TH2F *GJets_HT_xToy_total_histo;

	TH2F *G_Pt_15to30_histo;
	TH2F *G_Pt_30to50_histo;
	TH2F *G_Pt_50to80_histo;
	TH2F *G_Pt_80to120_histo;
	TH2F *G_Pt_120to170_histo;
	TH2F *G_Pt_170to300_histo;
	TH2F *G_Pt_300to470_histo;
	TH2F *G_Pt_470to800_histo;
	TH2F *G_Pt_800to1400_histo;
	TH2F *G_Pt_1400to1800_histo;
	TH2F *G_Pt_1800_histo;
	TH2F *G_Pt_XtoY_total_histo;

	TH2F *DiPhotonJets_histo;
	TH2F *DiPhotonJets_total_histo;

	TH2F *QCD_Pt_20_30_EMEnriched_histo;
	TH2F *QCD_Pt_30_80_EMEnriched_histo;
	TH2F *QCD_Pt_80_170_EMEnriched_histo;
	TH2F *QCD_Pt_170_250_EMEnriched_histo;
	TH2F *QCD_Pt_250_350_EMEnriched_histo;
	TH2F *QCD_Pt_350_EMEnriched_histo;
	TH2F *QCD_Pt_x_y_EMEnriched_total_histo;

	TH2F *QCD_Pt_20_30_BCtoE_histo;
	TH2F *QCD_Pt_30_80_BCtoE_histo;
	TH2F *QCD_Pt_80_170_BCtoE_histo;
	TH2F *QCD_Pt_170_250_BCtoE_histo;
	TH2F *QCD_Pt_250_350_BCtoE_histo;
	TH2F *QCD_Pt_350_BCtoE_histo;;
	TH2F *QCD_Pt_x_y_BCtoE_total_histo;

	TH2F *QCD_HT_100To250_histo;
	TH2F *QCD_HT_250To500_histo;
	TH2F *QCD_HT_500To1000_histo;
	TH2F *QCD_HT_1000ToInf_histo;
	TH2F *QCD_HT_xToy_total_histo;	
	
	
	if(signal_MAD){				
		//--- MC signal GJets_HT-xToy ----------------------------------------------
/*
		GJets_HT_40To100_histo=(TH2F*)GJets_HT_40To100_file->Get(titlehisto);
		GJets_HT_40To100_histo->Rebin2D(rebinX, rebinY);
*/
		
		GJets_HT_100To200_histo=(TH2F*)GJets_HT_100To200_file->Get(titlehisto);
		GJets_HT_100To200_histo->Rebin2D(rebinX, rebinY);

		GJets_HT_200To400_histo=(TH2F*)GJets_HT_200To400_file->Get(titlehisto);
		GJets_HT_200To400_histo->Rebin2D(rebinX, rebinY);

		GJets_HT_400ToInf_histo=(TH2F*)GJets_HT_400ToInf_file->Get(titlehisto);
		GJets_HT_400ToInf_histo->Rebin2D(rebinX, rebinY);

//		cout << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo->Integral() << endl;
		cout << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo->Integral() << endl;	
		cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;
		cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;
		cout << endl;
		
		GJets_HT_xToy_total_histo = (TH2F*) GJets_HT_100To200_histo->Clone("GJets_HT_xToy_total_histo");
		//--- GJets_HT_xToy_total_histo->Sumw2();
//		GJets_HT_xToy_total_histo->Add(GJets_HT_40To100_histo);	
		GJets_HT_xToy_total_histo->Add(GJets_HT_200To400_histo);
		GJets_HT_xToy_total_histo->Add(GJets_HT_400ToInf_histo);  
		GJets_HT_xToy_total_histo->SetLineColor(1);
		//GJets_HT_xToy_total_histo->SetFillColor(5);  //for colors comment out Sumw2 in code
		GJets_HT_xToy_total_histo->GetXaxis()->SetRangeUser(x_min, x_max);		
		GJets_HT_xToy_total_histo->GetYaxis()->SetRangeUser(y_min, y_max);		
	}

	else {	
		// MC signal G_Pt-XtoY --------------------------------------------------	
		G_Pt_15to30_histo=(TH2F*)G_Pt_15to30_file->Get(titlehisto);
		G_Pt_15to30_histo->Rebin2D(rebinX, rebinY);

		G_Pt_30to50_histo=(TH2F*)G_Pt_30to50_file->Get(titlehisto);
		G_Pt_30to50_histo->Rebin2D(rebinX, rebinY);

		G_Pt_50to80_histo=(TH2F*)G_Pt_50to80_file->Get(titlehisto);
		G_Pt_50to80_histo->Rebin2D(rebinX, rebinY);

		G_Pt_80to120_histo=(TH2F*)G_Pt_80to120_file->Get(titlehisto);
		G_Pt_80to120_histo->Rebin2D(rebinX, rebinY);

		G_Pt_120to170_histo=(TH2F*)G_Pt_120to170_file->Get(titlehisto);
		G_Pt_120to170_histo->Rebin2D(rebinX, rebinY);
	
		G_Pt_170to300_histo=(TH2F*)G_Pt_170to300_file->Get(titlehisto);
		G_Pt_170to300_histo->Rebin2D(rebinX, rebinY);

		G_Pt_300to470_histo=(TH2F*)G_Pt_300to470_file->Get(titlehisto);
		G_Pt_300to470_histo->Rebin2D(rebinX, rebinY);

		G_Pt_470to800_histo=(TH2F*)G_Pt_470to800_file->Get(titlehisto);
		G_Pt_470to800_histo->Rebin2D(rebinX, rebinY);

		G_Pt_800to1400_histo=(TH2F*)G_Pt_800to1400_file->Get(titlehisto);
		G_Pt_800to1400_histo->Rebin2D(rebinX, rebinY);

		G_Pt_1400to1800_histo=(TH2F*)G_Pt_1400to1800_file->Get(titlehisto);
		G_Pt_1400to1800_histo->Rebin2D(rebinX, rebinY);

		G_Pt_1800_histo=(TH2F*)G_Pt_1800_file->Get(titlehisto);
		G_Pt_1800_histo->Rebin2D(rebinX, rebinY);

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
		cout << endl;
	
		G_Pt_XtoY_total_histo = (TH2F*) G_Pt_15to30_histo->Clone("G_Pt_XtoY_total_histo");
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
		//G_Pt_XtoY_total_histo->SetFillColor(kGreen+2);  //for colors comment out Sumw2 in code
		G_Pt_XtoY_total_histo->GetXaxis()->SetRangeUser(x_min, x_max);		
		G_Pt_XtoY_total_histo->GetYaxis()->SetRangeUser(y_min, y_max);		

	}
	
	// MC signal DiPhotonJets --------------------------------------------------
	DiPhotonJets_histo=(TH2F*)DiPhotonJets_file->Get(titlehisto);
	DiPhotonJets_histo->Rebin2D(rebinX, rebinY);
	
	cout << "DiPhotonJets entries = " << DiPhotonJets_histo->Integral() << endl;
	cout << endl;

	DiPhotonJets_total_histo = (TH2F*) DiPhotonJets_histo->Clone("DiPhotonJets_total_histo");
	//--- DiPhotonJets_total_histo->Sumw2();
	DiPhotonJets_total_histo->SetLineColor(1);
	//DiPhotonJets_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code
	DiPhotonJets_total_histo->GetXaxis()->SetRangeUser(x_min, x_max);		
	DiPhotonJets_total_histo->GetYaxis()->SetRangeUser(y_min, y_max);		


	if (!background_QCD){	
		//--- MC background QCD_Pt_x_y EMEnriched ----------------------------------	
		QCD_Pt_20_30_EMEnriched_histo=(TH2F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto);
		QCD_Pt_20_30_EMEnriched_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_30_80_EMEnriched_histo=(TH2F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto);
		QCD_Pt_30_80_EMEnriched_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_80_170_EMEnriched_histo=(TH2F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto);
		QCD_Pt_80_170_EMEnriched_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_170_250_EMEnriched_histo=(TH2F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto);
		QCD_Pt_170_250_EMEnriched_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_250_350_EMEnriched_histo=(TH2F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto);
		QCD_Pt_250_350_EMEnriched_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_350_EMEnriched_histo=(TH2F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto);
		QCD_Pt_350_EMEnriched_histo->Rebin2D(rebinX, rebinY);

		cout << "QCD_Pt_20_30_EMEnriched entries = " << QCD_Pt_20_30_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_30_80_EMEnriched entries = " << QCD_Pt_30_80_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_80_170_EMEnriched entries = " << QCD_Pt_80_170_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_170_250_EMEnriched entries = " << QCD_Pt_170_250_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_250_350_EMEnriched entries = " << QCD_Pt_250_350_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_350_EMEnriched entries = " << QCD_Pt_350_EMEnriched_histo->Integral() << endl;
		cout << endl;

		QCD_Pt_x_y_EMEnriched_total_histo = (TH2F*) QCD_Pt_20_30_EMEnriched_histo->Clone("QCD_Pt_x_y_EMEnriched_total_histo");
		//	QCD_Pt_x_y_EMEnriched_total_histo->Sumw2();
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_30_80_EMEnriched_histo);
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_80_170_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_170_250_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_250_350_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_350_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->SetLineColor(1);
		//QCD_Pt_x_y_EMEnriched_total_histo->SetFillColor(kMagenta+2);
		QCD_Pt_x_y_EMEnriched_total_histo->GetXaxis()->SetRangeUser(x_min, x_max);		
		QCD_Pt_x_y_EMEnriched_total_histo->GetYaxis()->SetRangeUser(y_min, y_max);		


		//--- MC background QCD_Pt_x_y BCtoE ----------------------------------
		QCD_Pt_20_30_BCtoE_histo=(TH2F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto);
		QCD_Pt_20_30_BCtoE_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_30_80_BCtoE_histo=(TH2F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto);
		QCD_Pt_30_80_BCtoE_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_80_170_BCtoE_histo=(TH2F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto);
		QCD_Pt_80_170_BCtoE_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_170_250_BCtoE_histo=(TH2F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto);
		QCD_Pt_170_250_BCtoE_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_250_350_BCtoE_histo=(TH2F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto);
		QCD_Pt_250_350_BCtoE_histo->Rebin2D(rebinX, rebinY);

		QCD_Pt_350_BCtoE_histo=(TH2F*)QCD_Pt_350_BCtoE_file->Get(titlehisto);
		QCD_Pt_350_BCtoE_histo->Rebin2D(rebinX, rebinY);

		cout << "QCD_Pt_20_30_BCtoE entries = " << QCD_Pt_20_30_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_30_80_BCtoE entries = " << QCD_Pt_30_80_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_80_170_BCtoE entries = " << QCD_Pt_80_170_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_170_250_BCtoE entries = " << QCD_Pt_170_250_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_250_350_BCtoE entries = " << QCD_Pt_250_350_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_350_BCtoE entries = " << QCD_Pt_350_BCtoE_histo->Integral() << endl;
		cout << endl;

		QCD_Pt_x_y_BCtoE_total_histo = (TH2F*) QCD_Pt_20_30_BCtoE_histo->Clone("QCD_Pt_x_y_BCtoE_total_histo");
		//	QCD_Pt_x_y_BCtoE_total_histo->Sumw2();
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_30_80_BCtoE_histo);
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_80_170_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_170_250_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_250_350_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_350_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->SetLineColor(1);
		//QCD_Pt_x_y_BCtoE_total_histo->SetFillColor(kBlue-7);
		QCD_Pt_x_y_BCtoE_total_histo->GetXaxis()->SetRangeUser(x_min, x_max);		
		QCD_Pt_x_y_BCtoE_total_histo->GetYaxis()->SetRangeUser(y_min, y_max);		
	}
	else {	
		// MC background QCD HT-xToy --------------------------------------------
		QCD_HT_100To250_histo=(TH2F*)QCD_HT_100To250_file->Get(titlehisto);
		QCD_HT_100To250_histo->Rebin2D(rebinX, rebinY);

		QCD_HT_250To500_histo=(TH2F*)QCD_HT_250To500_file->Get(titlehisto);
		QCD_HT_250To500_histo->Rebin2D(rebinX, rebinY);

		QCD_HT_500To1000_histo=(TH2F*)QCD_HT_500To1000_file->Get(titlehisto);
		QCD_HT_500To1000_histo->Rebin2D(rebinX, rebinY);

		QCD_HT_1000ToInf_histo=(TH2F*)QCD_HT_1000ToInf_file->Get(titlehisto);
		QCD_HT_1000ToInf_histo->Rebin2D(rebinX, rebinY);

		cout << "QCD_HT_100To250 entries " << QCD_HT_100To250_histo->Integral() << endl;  
		cout << "QCD_HT_250To500 entries " << QCD_HT_250To500_histo->Integral() << endl;  
		cout << "QCD_HT_500To1000 entries " << QCD_HT_500To1000_histo->Integral() << endl;
		cout << "QCD_HT_1000ToInf entries " << QCD_HT_1000ToInf_histo->Integral() << endl;
		cout << endl;
	
		QCD_HT_xToy_total_histo = (TH2F*) QCD_HT_100To250_histo->Clone("QCD_HT_xToy_total_histo");
		//	QCD_HT_xToy_total_histo->Sumw2();
		QCD_HT_xToy_total_histo->Add(QCD_HT_250To500_histo);
		QCD_HT_xToy_total_histo->Add(QCD_HT_500To1000_histo);  
		QCD_HT_xToy_total_histo->Add(QCD_HT_1000ToInf_histo);  
		QCD_HT_xToy_total_histo->SetLineColor(1);
		//QCD_HT_xToy_total_histo->SetFillColor(kRed+2);
		QCD_HT_xToy_total_histo->GetXaxis()->SetRangeUser(x_min, x_max);		
		QCD_HT_xToy_total_histo->GetYaxis()->SetRangeUser(y_min, y_max);		
	}


	// ==================================== print Entries number

	cout << "========================" <<endl;	
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

	cout << "========================" <<endl;	
	cout << endl;
		
	// ==================================== load Canvas
	
  TCanvas *Canva = new TCanvas(titlehisto,titlehisto);  

	TH2F *BACK_histo;
	TH2F *SIG_histo;
	if (!background_QCD){		
		BACK_histo = (TH2F*) QCD_Pt_x_y_BCtoE_total_histo->Clone("BACK_histo");
		BACK_histo->Add(QCD_Pt_x_y_EMEnriched_total_histo);
	}	
	else {
		BACK_histo = (TH2F*) QCD_HT_xToy_total_histo->Clone("BACK_histo");
	}
	//signal
	SIG_histo = (TH2F*) DiPhotonJets_total_histo->Clone("SIG_histo");
	if(signal_MAD){
		SIG_histo->Add(GJets_HT_xToy_total_histo);
	}
	else{
		SIG_histo->Add(G_Pt_XtoY_total_histo);
	}

	BACK_histo->SetFillColor(kBlack);
	SIG_histo->GetXaxis()->SetTitle("#gamma1 #sigma_{i#etai#eta}");
	SIG_histo->GetXaxis()->SetTitleOffset(1.1);
	SIG_histo->GetYaxis()->SetTitle("#gamma1 PfIso #rho corrected");
	SIG_histo->GetYaxis()->SetTitleOffset(1.1);
	SIG_histo->GetZaxis()->SetTitle("Events");
	SIG_histo->GetZaxis()->SetTitleOffset(1.3);
	
	SIG_histo->Draw("colz");
	BACK_histo->Draw("box1 same");

	
/*
	THStack *MC_stack= new THStack();

	// backgrounds
	if (!background_QCD){		
		MC_stack->Add(QCD_Pt_x_y_BCtoE_total_histo);
		MC_stack->Add(QCD_Pt_x_y_EMEnriched_total_histo);
	}	
	else {
		MC_stack->Add(QCD_HT_xToy_total_histo);
	}
	//signal
	MC_stack->Add(DiPhotonJets_total_histo);
	if(signal_MAD){
		MC_stack->Add(GJets_HT_xToy_total_histo);
	}
	else{
		MC_stack->Add(G_Pt_XtoY_total_histo);
	}
	
	MC_stack->Draw("lego1");
	gPad->SetLogz();
*/

	gPad->SetLogz();

	TLegend *leg =new TLegend(0.1778,0.5478,0.5151,0.7480);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	if(signal_MAD){
		leg->AddEntry(SIG_histo,"#splitline{SIGNAL:}{#gamma + jets (MAD) and DiPhotonJets}","f");
	}
	else{
		leg->AddEntry(SIG_histo,"#splitline{SIGNAL:}{#gamma + jets (PYT) and DiPhotonJets}","f");
	}
	if (!background_QCD){
		leg->AddEntry(BACK_histo, "#splitline{BACKGROUND:}{QCD EMEnriched and QCD BCtoE}","f");
	}
	else {
		leg->AddEntry(BACK_histo, "#splitline{BACKGROUND:}{QCD HT}","f");
	}
	leg->Draw();


  TPaveText* text = new TPaveText(0.1678,0.8042,0.3809,0.8899,"NDC");
  text->SetFillColor(0);
  text->SetFillStyle(0);
  text->SetBorderSize(0);
  text->AddText("CMS Preliminary");
	text->AddText("#sqrt{s} = 8 TeV");
  text->SetTextAlign(11);
  text->Draw();

	TPaveText *Tex_pT = new TPaveText(0.0034,0.0035,0.3104,0.0507,"NDC");
	Tex_pT->SetFillColor(0);
	Tex_pT->SetBorderSize(0);
	Tex_pT->AddText(string_pT.c_str());
  Tex_pT->Draw();

	root_string = ".root";
	pdf_string = ".pdf";
  Canva->SaveAs((folder_s + geo_s + SB_folder + pdf_folder + titleh + pdf_string).c_str());
  Canva->SaveAs((folder_s + geo_s + SB_folder + root_folder + titleh + root_string).c_str());
	Canva->Close();

	// ==================================== report

	cout << "Writing report file... " << endl;
	ofstream report;
	
	stringstream ss_t;
	char txt_char[100];
	ss_t << folder_s + geo_s + SB_folder + txt_folder + titleh + txt_string;
	ss_t >> txt_char;
	
	report.open(txt_char);
	
	report << endl;

	if(signal_MAD){
		report << endl;
//		report << "GJets file 21 is: " << GJets_HT_40To100_name << endl;
		report << "GJets file 22 is: " << GJets_HT_100To200_name << endl;	
		report << "GJets file 23 is: " << GJets_HT_200To400_name << endl;
		report << "GJets file 24 is: " << GJets_HT_400ToInf_name << endl;
	}
	
	else {
		report << endl;
		report << "G file 31 is: " << G_Pt_15to30_name << endl;
		report << "G file 32 is: " << G_Pt_30to50_name << endl;
		report << "G file 33 is: " << G_Pt_50to80_name << endl;
		report << "G file 34 is: " << G_Pt_80to120_name << endl;
		report << "G file 35 is: " << G_Pt_120to170_name << endl;
		report << "G file 36 is: " << G_Pt_170to300_name << endl;
		report << "G file 37 is: " << G_Pt_300to470_name << endl;
		report << "G file 38 is: " << G_Pt_470to800_name << endl;
		report << "G file 39 is: " << G_Pt_800to1400_name << endl;
		report << "G file 40 is: " << G_Pt_1400to1800_name << endl;
		report << "G file 41 is: " << G_Pt_1800_name << endl;
	}

	report << endl;
	report << "DiPhotonJets file 51 is: " << DiPhotonJets_name << endl;

	if (!background_QCD){
		report << endl;	
		report << "QCD EMEnriched file 61 is: " << QCD_Pt_20_30_EMEnriched_name << endl;
		report << "QCD EMEnriched file 62 is: " << QCD_Pt_30_80_EMEnriched_name << endl;
		report << "QCD EMEnriched file 63 is: " << QCD_Pt_80_170_EMEnriched_name << endl;
		report << "QCD EMEnriched file 64 is: " << QCD_Pt_170_250_EMEnriched_name << endl;
		report << "QCD EMEnriched file 65 is: " << QCD_Pt_250_350_EMEnriched_name << endl;
		report << "QCD EMEnriched file 66 is: " << QCD_Pt_350_EMEnriched_name << endl;
		report << endl;
		report << "QCD BCtoE file 71 is: " << QCD_Pt_20_30_BCtoE_name << endl;
		report << "QCD BCtoE file 72 is: " << QCD_Pt_30_80_BCtoE_name << endl;
		report << "QCD BCtoE file 73 is: " << QCD_Pt_80_170_BCtoE_name << endl;
		report << "QCD BCtoE file 74 is: " << QCD_Pt_170_250_BCtoE_name << endl;
		report << "QCD BCtoE file 75 is: " << QCD_Pt_250_350_BCtoE_name << endl;
		report << "QCD BCtoE file 76 is: " << QCD_Pt_350_BCtoE_name << endl;	
	}

	else {
		report << endl;	
		report << "QCD file 81 is: " << QCD_HT_100To250_name << endl;
		report << "QCD file 82 is: " << QCD_HT_250To500_name << endl;
		report << "QCD file 83 is: " << QCD_HT_500To1000_name << endl;
		report << "QCD file 84 is: " << QCD_HT_1000ToInf_name << endl;
	}
	report << endl;
	report << "========================" <<endl;	
	report << endl;	

	if(signal_MAD) {
//		report << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo->Integral() << endl;
		report << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo->Integral() << endl;	
		report << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;
		report << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;
	}
	else {
		report << "G_Pt_15to30 entries = " << G_Pt_15to30_histo->Integral() << endl;
		report << "G_Pt_30to50 entries = " << G_Pt_30to50_histo->Integral() << endl;
		report << "G_Pt_50to80 entries = " << G_Pt_50to80_histo->Integral() << endl;
		report << "G_Pt_80to120 entries = " << G_Pt_80to120_histo->Integral() << endl;
		report << "G_Pt_120to170 entries = " << G_Pt_120to170_histo->Integral() << endl;
		report << "G_Pt_170to300 entries = " << G_Pt_170to300_histo->Integral() << endl;
		report << "G_Pt_300to470 entries = " << G_Pt_300to470_histo->Integral() << endl;
		report << "G_Pt_470to800 entries = " << G_Pt_470to800_histo->Integral() << endl;
		report << "G_Pt_800to1400 entries = " << G_Pt_800to1400_histo->Integral() << endl;
		report << "G_Pt_1400to1800 entries = " << G_Pt_1400to1800_histo->Integral() << endl;
		report << "G_Pt_1800 entries = " << G_Pt_1800_histo->Integral() << endl;
	}
	
	report << "DiPhotonJets entries = " << DiPhotonJets_histo->Integral() << endl;

	if (!background_QCD){
		report << "QCD_Pt_20_30_EMEnriched entries = " << QCD_Pt_20_30_EMEnriched_histo->Integral() << endl;
		report << "QCD_Pt_30_80_EMEnriched entries = " << QCD_Pt_30_80_EMEnriched_histo->Integral() << endl;
		report << "QCD_Pt_80_170_EMEnriched entries = " << QCD_Pt_80_170_EMEnriched_histo->Integral() << endl;
		report << "QCD_Pt_170_250_EMEnriched entries = " << QCD_Pt_170_250_EMEnriched_histo->Integral() << endl;
		report << "QCD_Pt_250_350_EMEnriched entries = " << QCD_Pt_250_350_EMEnriched_histo->Integral() << endl;
		report << "QCD_Pt_350_EMEnriched entries = " << QCD_Pt_350_EMEnriched_histo->Integral() << endl;
		report << endl;
		report << "QCD_Pt_20_30_BCtoE entries = " << QCD_Pt_20_30_BCtoE_histo->Integral() << endl;
		report << "QCD_Pt_30_80_BCtoE entries = " << QCD_Pt_30_80_BCtoE_histo->Integral() << endl;
		report << "QCD_Pt_80_170_BCtoE entries = " << QCD_Pt_80_170_BCtoE_histo->Integral() << endl;
		report << "QCD_Pt_170_250_BCtoE entries = " << QCD_Pt_170_250_BCtoE_histo->Integral() << endl;
		report << "QCD_Pt_250_350_BCtoE entries = " << QCD_Pt_250_350_BCtoE_histo->Integral() << endl;
		report << "QCD_Pt_350_BCtoE entries = " << QCD_Pt_350_BCtoE_histo->Integral() << endl;
	}
	else {	
		report << "QCD_HT_100To250 entries " << QCD_HT_100To250_histo->Integral() << endl;  
		report << "QCD_HT_250To500 entries " << QCD_HT_250To500_histo->Integral() << endl;  
		report << "QCD_HT_500To1000 entries " << QCD_HT_500To1000_histo->Integral() << endl;
		report << "QCD_HT_1000ToInf entries " << QCD_HT_1000ToInf_histo->Integral() << endl;
	}

	report << endl;
	report << "========================" <<endl;	
	report << endl;	

	if(signal_MAD) report << "GJets total entries = " << GJets_HT_xToy_total_histo->Integral() << endl;  
	else report << "G total entries = " << G_Pt_XtoY_total_histo->Integral() << endl;

	report << endl;
	report << "DiPhotonJets total entries = " << DiPhotonJets_total_histo->Integral() << endl;

	report << endl;
	if (!background_QCD){	  
	report << "QCD EMEnriched total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() << endl;  
	report << "QCD BCtoE total entries = " << QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;
	report << "QCD (EMEnriched + BCtoE) total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() +
	                                                       QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;
	}	 
	else report << "QCD HT total entries = " << QCD_HT_xToy_total_histo->Integral() << endl;  
	report << endl;
	
	report.close();
	cout << "...writing report file finished. " << endl;

	// ==================================== close files

	
	if(signal_MAD){	
	//	GJets_HT_40To100_file->Close();	
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

void histo2D_normal() {
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_", "p_{T}^{#gamma} > 180 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_", "180 < p_{T}^{#gamma} < 200 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_", "200 < p_{T}^{#gamma} < 250 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_", "250 < p_{T}^{#gamma} < 300 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_", "300 < p_{T}^{#gamma} < 350 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_", "350 < p_{T}^{#gamma} < 400 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_", "p_{T}^{#gamma} > 400 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, 0., 20.);

	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_", "p_{T}^{#gamma} > 180 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_", "180 < p_{T}^{#gamma} < 200 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_", "200 < p_{T}^{#gamma} < 250 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_", "250 < p_{T}^{#gamma} < 300 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_", "300 < p_{T}^{#gamma} < 350 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_", "350 < p_{T}^{#gamma} < 400 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_", "p_{T}^{#gamma} > 400 [GeV/#font[12]{c}]", 2, 4, 0., 0.012, -2., 20.);
}

void histo2D_inverted_sieie() {
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_", "p_{T}^{#gamma} > 180 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_", "180 < p_{T}^{#gamma} < 200 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_", "200 < p_{T}^{#gamma} < 250 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_", "250 < p_{T}^{#gamma} < 300 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_", "300 < p_{T}^{#gamma} < 350 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_", "350 < p_{T}^{#gamma} < 400 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_", "p_{T}^{#gamma} > 400 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, 0., 20.);

	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_", "p_{T}^{#gamma} > 180 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_", "180 < p_{T}^{#gamma} < 200 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_", "200 < p_{T}^{#gamma} < 250 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_", "250 < p_{T}^{#gamma} < 300 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_", "300 < p_{T}^{#gamma} < 350 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_", "350 < p_{T}^{#gamma} < 400 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
	histo2D("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_", "p_{T}^{#gamma} > 400 [GeV/#font[12]{c}] - inv. #sigma_{i#etai#eta}", 2, 4, 0.010, 0.025, -2., 20.);
}
