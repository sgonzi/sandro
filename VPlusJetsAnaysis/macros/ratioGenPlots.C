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
  myStyle->SetOptLogy(0);
  myStyle->SetOptLogz(0);

// Postscript options:
  myStyle->SetPaperSize(20.,20.);

  myStyle->cd();
}


void ratioGenPlots(const char* titleh, const char* titlehGJets, const char* titlehZJets_mumu, const char* titlehZJets_ee, const char* titlehZJets_ll, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L GenPlots.C++
  //       ie: GenPlots("HTParSum_","H_{T} Partons Sum", 1, 0, 100);

	setMYStyle();

	// ==================================== choose the tools

	string folder = "14_results_2013_11_24"; // analysis folder

	char geo[100] = "barrel";               // "barrel", "endcaps" or "total"

	bool data_ReReco = true;                // true: data = ReReco
	                                         // false: data = PromptReco

	bool signal_MAD = true;                 // true: signal = MADGRAPH; false: signal = PYTHIA

	Int_t itype = 14;                        // it identifies histos with different analysis 


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
	char root_char[200];
	ss_r << root_string;
	ss_r >> root_char;

	string address = folder_s + geo_s + out_files;


	// ==================================== assign files names

					
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

	Char_t DYJetsToLL_M_50_name[100];	
	
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

	sprintf(DYJetsToLL_M_50_name,"DYJetsToLL_M_50_histos_%d_%s%s",itype, geo, root_char);	
	cout << "DYJets file 91 is: " << DYJetsToLL_M_50_name << endl;
	cout << endl;
	
	// ==================================== load TFiles

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

	TFile *DYJetsToLL_M_50_file;

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
	
	DYJetsToLL_M_50_file = new TFile((address+DYJetsToLL_M_50_name).c_str());	
	
	// ==================================== load TH1F

	Char_t titlehistoGJets[100];
	strcpy(titlehistoGJets,titlehGJets);
 
	Char_t titlehistoZJets_mumu[100];
	strcpy(titlehistoZJets_mumu,titlehZJets_mumu);

	Char_t titlehistoZJets_ee[100];
	strcpy(titlehistoZJets_ee,titlehZJets_ee);

	Char_t titlehistoZJets_ll[100];
	strcpy(titlehistoZJets_ll,titlehZJets_ll);

	cout << "========================" <<endl;	
	cout << endl;	

	cout << "Analyzing Histogram: " << titlehistoGJets << ", " << titlehistoZJets_mumu << ", " << titlehistoZJets_ee << ", " << titlehistoZJets_ll << endl;

	cout << endl;	
	cout << "========================" <<endl;	
	cout << endl;	


	TH1F *GJets_HT_40To100_histo;
	TH1F *GJets_HT_100To200_histo;
	TH1F *GJets_HT_200To400_histo;
	TH1F *GJets_HT_400ToInf_histo;
	TH1F *GJets_HT_xToy_total_histo;
	
	TH1F *G_Pt_15to30_histo;
	TH1F *G_Pt_30to50_histo;
	TH1F *G_Pt_50to80_histo;
	TH1F *G_Pt_80to120_histo;
	TH1F *G_Pt_120to170_histo;
	TH1F *G_Pt_170to300_histo;
	TH1F *G_Pt_300to470_histo;
	TH1F *G_Pt_470to800_histo;
	TH1F *G_Pt_800to1400_histo;
	TH1F *G_Pt_1400to1800_histo;
	TH1F *G_Pt_1800_histo;
	TH1F *G_Pt_XtoY_total_histo;

	TH1F *DiPhotonJets_histo;
	TH1F *DiPhotonJets_total_histo;

	TH1F *DYJetsToLL_M_50_histo_mumu;
	TH1F *DYJetsToLL_M_50_total_histo_mumu;
	TH1F *DYJetsToLL_M_50_histo_ee;
	TH1F *DYJetsToLL_M_50_total_histo_ee;
	TH1F *DYJetsToLL_M_50_histo_ll;
	TH1F *DYJetsToLL_M_50_total_histo_ll;
	
	if(signal_MAD){				
		//--- MC signal GJets_HT-xToy ----------------------------------------------

		GJets_HT_40To100_histo=(TH1F*)GJets_HT_40To100_file->Get(titlehistoGJets);
		GJets_HT_40To100_histo->Rebin(rebin);

		GJets_HT_100To200_histo=(TH1F*)GJets_HT_100To200_file->Get(titlehistoGJets);
		GJets_HT_100To200_histo->Rebin(rebin);

		GJets_HT_200To400_histo=(TH1F*)GJets_HT_200To400_file->Get(titlehistoGJets);
		GJets_HT_200To400_histo->Rebin(rebin);

		GJets_HT_400ToInf_histo=(TH1F*)GJets_HT_400ToInf_file->Get(titlehistoGJets);
		GJets_HT_400ToInf_histo->Rebin(rebin);

		cout << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo->Integral() << endl;
		cout << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo->Integral() << endl;	
		cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;
		cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;
		cout << endl;
		
		GJets_HT_xToy_total_histo = (TH1F*) GJets_HT_40To100_histo->Clone("GJets_HT_xToy_total_histo");
		//--- GJets_HT_xToy_total_histo->Sumw2();
		GJets_HT_xToy_total_histo->Add(GJets_HT_100To200_histo);	
		GJets_HT_xToy_total_histo->Add(GJets_HT_200To400_histo);
		GJets_HT_xToy_total_histo->Add(GJets_HT_400ToInf_histo);  
		GJets_HT_xToy_total_histo->SetLineColor(5);
		GJets_HT_xToy_total_histo->SetLineWidth(3);
		//GJets_HT_xToy_total_histo->SetFillColor(5);  //for colors comment out Sumw2 in code
	}

	else {	
		// MC signal G_Pt-XtoY --------------------------------------------------	
		G_Pt_15to30_histo=(TH1F*)G_Pt_15to30_file->Get(titlehistoGJets);
		G_Pt_15to30_histo->Rebin(rebin);

		G_Pt_30to50_histo=(TH1F*)G_Pt_30to50_file->Get(titlehistoGJets);
		G_Pt_30to50_histo->Rebin(rebin);

		G_Pt_50to80_histo=(TH1F*)G_Pt_50to80_file->Get(titlehistoGJets);
		G_Pt_50to80_histo->Rebin(rebin);

		G_Pt_80to120_histo=(TH1F*)G_Pt_80to120_file->Get(titlehistoGJets);
		G_Pt_80to120_histo->Rebin(rebin);

		G_Pt_120to170_histo=(TH1F*)G_Pt_120to170_file->Get(titlehistoGJets);
		G_Pt_120to170_histo->Rebin(rebin);
	
		G_Pt_170to300_histo=(TH1F*)G_Pt_170to300_file->Get(titlehistoGJets);
		G_Pt_170to300_histo->Rebin(rebin);

		G_Pt_300to470_histo=(TH1F*)G_Pt_300to470_file->Get(titlehistoGJets);
		G_Pt_300to470_histo->Rebin(rebin);

		G_Pt_470to800_histo=(TH1F*)G_Pt_470to800_file->Get(titlehistoGJets);
		G_Pt_470to800_histo->Rebin(rebin);

		G_Pt_800to1400_histo=(TH1F*)G_Pt_800to1400_file->Get(titlehistoGJets);
		G_Pt_800to1400_histo->Rebin(rebin);

		G_Pt_1400to1800_histo=(TH1F*)G_Pt_1400to1800_file->Get(titlehistoGJets);
		G_Pt_1400to1800_histo->Rebin(rebin);

		G_Pt_1800_histo=(TH1F*)G_Pt_1800_file->Get(titlehistoGJets);
		G_Pt_1800_histo->Rebin(rebin);

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
	
		G_Pt_XtoY_total_histo = (TH1F*) G_Pt_15to30_histo->Clone("G_Pt_XtoY_total_histo");
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
		G_Pt_XtoY_total_histo->SetLineColor(kGreen+2);
		G_Pt_XtoY_total_histo->SetLineWidth(3);
		//G_Pt_XtoY_total_histo->SetFillColor(kGreen+2);  //for colors comment out Sumw2 in code
	}

	// MC signal DiPhotonJets --------------------------------------------------
	DiPhotonJets_histo=(TH1F*)DiPhotonJets_file->Get(titlehistoGJets);
	DiPhotonJets_histo->Rebin(rebin);
	
	cout << "DiPhotonJets entries = " << DiPhotonJets_histo->Integral() << endl;
	cout << endl;

	DiPhotonJets_total_histo = (TH1F*) DiPhotonJets_histo->Clone("DiPhotonJets_total_histo");
	//--- DiPhotonJets_total_histo->Sumw2();
	DiPhotonJets_total_histo->SetLineColor(kGray+2);
	DiPhotonJets_total_histo->SetLineWidth(3);
	//DiPhotonJets_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	//--- MC signal DYJetsToLL_M_50 ----------------------------------------------
	DYJetsToLL_M_50_histo_mumu=(TH1F*)DYJetsToLL_M_50_file->Get(titlehistoZJets_mumu);
	DYJetsToLL_M_50_histo_mumu->Rebin(rebin);
		
	DYJetsToLL_M_50_total_histo_mumu = (TH1F*) DYJetsToLL_M_50_histo_mumu->Clone("DYJetsToLL_M_50_total_histo_mumu");
	//--- DYJetsToLL_M_50_total_histo->Sumw2();
	DYJetsToLL_M_50_total_histo_mumu->SetLineColor(kBlue);
	DYJetsToLL_M_50_total_histo_mumu->SetLineWidth(3);
	//DYJetsToLL_M_50_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	//--
	DYJetsToLL_M_50_histo_ee=(TH1F*)DYJetsToLL_M_50_file->Get(titlehistoZJets_ee);
	DYJetsToLL_M_50_histo_ee->Rebin(rebin);
		
	DYJetsToLL_M_50_total_histo_ee = (TH1F*) DYJetsToLL_M_50_histo_ee->Clone("DYJetsToLL_M_50_total_histo_ee");
	//--- DYJetsToLL_M_50_total_histo->Sumw2();
	DYJetsToLL_M_50_total_histo_ee->SetLineColor(kRed);
	DYJetsToLL_M_50_total_histo_ee->SetLineWidth(3);
	//DYJetsToLL_M_50_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	//--
	DYJetsToLL_M_50_histo_ll=(TH1F*)DYJetsToLL_M_50_file->Get(titlehistoZJets_ll);
	DYJetsToLL_M_50_histo_ll->Rebin(rebin);
		
	DYJetsToLL_M_50_total_histo_ll = (TH1F*) DYJetsToLL_M_50_histo_ll->Clone("DYJetsToLL_M_50_total_histo_ll");
	//--- DYJetsToLL_M_50_total_histo->Sumw2();
	DYJetsToLL_M_50_total_histo_ll->SetLineColor(kBlack);
	DYJetsToLL_M_50_total_histo_ll->SetLineWidth(3);
	//DYJetsToLL_M_50_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	// ==================================== print Entries number

	cout << "========================" <<endl;	
	cout << endl;
	
	if(signal_MAD) cout << "GJets total entries = " << GJets_HT_xToy_total_histo->Integral() << endl;  
	else cout << "G total entries = " << G_Pt_XtoY_total_histo->Integral() << endl;

	cout << endl;
	cout << "DiPhotonJets total entries = " << DiPhotonJets_total_histo->Integral() << endl;

	cout << endl;
	cout << "DYJets mumu total entries = " << DYJetsToLL_M_50_total_histo_mumu->Integral() << endl;  

	cout << endl;
	cout << "DYJets ee total entries = " << DYJetsToLL_M_50_total_histo_ee->Integral() << endl;  

	cout << endl;
	cout << "DYJets ll total entries = " << DYJetsToLL_M_50_total_histo_ll->Integral() << endl;  

	cout << "========================" <<endl;	
	cout << endl;
		
	// ==================================== load Canvas
	
  TCanvas *Canva = new TCanvas(titlehistoGJets,titlehistoGJets);  
	TPad* upperPad = new TPad("upperPad", "upperPad",.005, .35, .995, .995);
  TPad* lowerPad = new TPad("lowerPad", "lowerPad",.005, .005, .995, .3475);
  upperPad->Draw(); 			       
  lowerPad->Draw();
  
	//signal total GJets
	TH1F *signalGJets_total_histo;	

	if(signal_MAD){
		signalGJets_total_histo = (TH1F*) GJets_HT_xToy_total_histo->Clone("signalGJets_total_histo");
	}
	else{
		signalGJets_total_histo = (TH1F*) G_Pt_XtoY_total_histo->Clone("signalGJets_total_histo");	
	}
	signalGJets_total_histo->Add(DiPhotonJets_total_histo); 
  
  //ratio NUM and DEN
 	TH1F *ratio_histo_NUM_mumu = new TH1F();
	ratio_histo_NUM_mumu = (TH1F*) DYJetsToLL_M_50_total_histo_mumu->Clone("ratio_histo_NUM_mumu");	

 	TH1F *ratio_histo_NUM_ee = new TH1F();
	ratio_histo_NUM_ee = (TH1F*) DYJetsToLL_M_50_total_histo_ee->Clone("ratio_histo_NUM_ee");	

 	TH1F *ratio_histo_NUM_ll = new TH1F();
	ratio_histo_NUM_ll = (TH1F*) DYJetsToLL_M_50_total_histo_ll->Clone("ratio_histo_NUM_ll");	

	TH1F *ratio_histo_DEN = new TH1F;
	ratio_histo_DEN = (TH1F*) signalGJets_total_histo->Clone("ratio_histo_DEN");

  //ratio 
 	TH1F *ratio_histo_mumu = (TH1F*) ratio_histo_NUM_mumu->Clone("ratio_histo_mumu");
	ratio_histo_mumu->Sumw2();
	ratio_histo_mumu->Divide(ratio_histo_DEN);

 	TH1F *ratio_histo_ee = (TH1F*) ratio_histo_NUM_ee->Clone("ratio_histo_ee");
	ratio_histo_ee->Sumw2();
	ratio_histo_ee->Divide(ratio_histo_DEN);
   
 	TH1F *ratio_histo_ll = (TH1F*) ratio_histo_NUM_ll->Clone("ratio_histo_ll");
	ratio_histo_ll->Sumw2();
	ratio_histo_ll->Divide(ratio_histo_DEN);

	int Nbins;
	double X_min, X_max;

	Nbins =	ratio_histo_NUM_ll->GetNbinsX();

	// upper Pad
  upperPad->cd();

	if (x_min != -999 && x_max != -999){
		if (x_max == ratio_histo_NUM_ll->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == ratio_histo_NUM_ll->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		ratio_histo_DEN->GetXaxis()->SetRangeUser(X_min,X_max);
		ratio_histo_NUM_mumu->GetXaxis()->SetRangeUser(X_min,X_max);
		ratio_histo_NUM_ee->GetXaxis()->SetRangeUser(X_min,X_max);
		ratio_histo_NUM_ll->GetXaxis()->SetRangeUser(X_min,X_max);
	}


	ratio_histo_DEN->Draw();
	ratio_histo_NUM_mumu->Draw("same");
	ratio_histo_NUM_ee->Draw("same");
	ratio_histo_NUM_ll->Draw("same");
	ratio_histo_DEN->GetYaxis()->SetRangeUser(2.,2E7);
	
	gPad->SetLogy();

	ratio_histo_DEN->GetXaxis()->SetTitle(namevariable);
	ratio_histo_DEN->GetXaxis()->SetTitleSize(0.05);
	ratio_histo_DEN->GetYaxis()->SetTitleOffset(1.2);
	ratio_histo_DEN->GetYaxis()->SetTitle("Events");	

	TLegend *leg =new TLegend(0.5762,0.6310,0.8220,0.8668);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	leg->AddEntry(ratio_histo_DEN,"#gamma + 1 jet","l");
	leg->AddEntry(ratio_histo_NUM_mumu,"Z (->#mu^{+}#mu^{-}) + 1 jet","l");
	leg->AddEntry(ratio_histo_NUM_ee,"Z (->e^{+}e^{-}) + 1 jet","l");
	leg->AddEntry(ratio_histo_NUM_ll,"Z (->l^{+}l^{-}) + 1 jet","l");
	leg->Draw();

  TPaveText* text_1 = new TPaveText(0.1194,0.9310,0.3313,0.9780,"NDC");
  text_1->SetFillColor(0);
  text_1->SetFillStyle(0);
  text_1->SetBorderSize(0);
  text_1->AddText("CMS Simulation");
  text_1->SetTextAlign(11);
  text_1->Draw();

  TPaveText* text_2 = new TPaveText(0.5627,0.9310,0.8678,0.9780,"NDC");
  text_2->SetFillColor(0);
  text_2->SetFillStyle(0);
  text_2->SetBorderSize(0);
  if (data_ReReco) text_2->AddText("#sqrt{s} = 8 TeV, L = 19.71 fb^{-1}");
  else text_2->AddText("#sqrt{s} = 8 TeV");
  text_2->SetTextAlign(11);
  text_2->Draw();


	// lower Pad
	lowerPad-> cd();

	if (x_min != -999 && x_max != -999){
		if (x_max == ratio_histo_ll->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == ratio_histo_ll->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

	ratio_histo_mumu->GetXaxis()->SetRangeUser(X_min,X_max);
	ratio_histo_ee->GetXaxis()->SetRangeUser(X_min,X_max);
	ratio_histo_ll->GetXaxis()->SetRangeUser(X_min,X_max);
	}

	ratio_histo_mumu->SetLineWidth(2);
	ratio_histo_mumu->SetMarkerColor(kBlue);
	ratio_histo_mumu->SetMarkerSize(0.4);	
	ratio_histo_ee->SetLineWidth(2);
	ratio_histo_ee->SetMarkerColor(kRed);
	ratio_histo_ee->SetMarkerSize(0.4);	
	ratio_histo_ll->SetLineWidth(2);
	ratio_histo_ll->SetMarkerColor(kBlack);	
	ratio_histo_ll->SetMarkerSize(0.4);		

	ratio_histo_ll->Draw();
	ratio_histo_mumu->Draw("same");	
	ratio_histo_ee->Draw("same");	
	ratio_histo_ll->Draw("AXIS X+ Y+ SAME");
	ratio_histo_ll->Draw("AXIS SAME");
  ratio_histo_ll->GetXaxis()->SetTitle("");
	ratio_histo_ll->GetYaxis()->SetTitle("Z/#gamma ratio");
	ratio_histo_ll->GetYaxis()->SetTitleSize(0.10);
	ratio_histo_ll->GetYaxis()->SetTitleOffset(0.6);
	ratio_histo_ll->GetYaxis()->SetLabelSize(0.1);
	ratio_histo_ll->GetXaxis()->SetLabelSize(0.1);
	ratio_histo_ll->GetYaxis()->SetRangeUser(0.,2.);
	ratio_histo_ll->GetYaxis()->SetNdivisions(505, "kTRUE");
	
	root_string = ".root";
	pdf_string = ".pdf";
  Canva->SaveAs((folder_s + geo_s + GEN_folder + pdf_folder + titleh + pdf_string).c_str());
  Canva->SaveAs((folder_s + geo_s + GEN_folder + root_folder + titleh + root_string).c_str());
	Canva->Close();

	// ==================================== report

	cout << "Writing report file... " << endl;
	ofstream report;
	
	stringstream ss_t;
	char txt_char[200];
	ss_t << folder_s + geo_s + GEN_folder + txt_folder + titleh + txt_string;
	ss_t >> txt_char;
	
	report.open(txt_char);

	report << endl;

	if(signal_MAD){
		report << endl;
		report << "GJets file 21 is: " << GJets_HT_40To100_name << endl;
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

	report << endl;
	report << "DYJets file 91 is: " << DYJetsToLL_M_50_name << endl;

	report << endl;
	report << "========================" <<endl;	
	report << endl;	

	if(signal_MAD) {
		report << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo->Integral() << endl;
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

	report << "DYJets mumu total entries = " << DYJetsToLL_M_50_total_histo_mumu->Integral() << endl;  

	report << "DYJets ee total entries = " << DYJetsToLL_M_50_total_histo_ee->Integral() << endl;  

	report << "DYJets ll total entries = " << DYJetsToLL_M_50_total_histo_ll->Integral() << endl; 

	report << endl;
	report << "========================" <<endl;	
	report << endl;	
	
	if(signal_MAD) report << "GJets total entries = " << GJets_HT_xToy_total_histo->Integral() << endl;  
	else report << "G total entries = " << G_Pt_XtoY_total_histo->Integral() << endl;

	report << endl;
	report << "DiPhotonJets total entries = " << DiPhotonJets_total_histo->Integral() << endl;

	report << endl;
	report << "DYJets mumu total entries = " << DYJetsToLL_M_50_total_histo_mumu->Integral() << endl;  

	report << "DYJets ee total entries = " << DYJetsToLL_M_50_total_histo_ee->Integral() << endl;  

	report << "DYJets ll total entries = " << DYJetsToLL_M_50_total_histo_ll->Integral() << endl; 
	report << endl;
	
	report.close();
	cout << "...writing report file finished. " << endl;

	// ==================================== close files

	
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

	DYJetsToLL_M_50_file->Close();
	
}


void ratioGenPlots_N0(){		
	ratioGenPlots("ratioGenPlot_PtGEN_", "photonPtGEN_N0_", "llPtGEN_mumu_N0_","llPtGEN_ee_N0_","llPtGEN_ll_N0_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} > 0)", 2, 0, 800);
}

void ratioGenPlots_N0_zoom(){
	ratioGenPlots("ratioGenPlot_PtGEN_zoom_", "photonPtGEN_N0_", "llPtGEN_mumu_N0_","llPtGEN_ee_N0_","llPtGEN_ll_N0_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} > 0)", 1, 100, 300);
}


void ratioGenPlots_excl1(){		
	ratioGenPlots("ratioGenPlot_PtGEN_excl1_", "photonPtGEN_excl1_", "llPtGEN_mumu_excl1_","llPtGEN_ee_excl1_","llPtGEN_ll_excl1_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} = 1)", 2, 0, 800);
}

void ratioGenPlots_excl1_zoom(){
	ratioGenPlots("ratioGenPlot_PtGEN_excl1_zoom_", "photonPtGEN_excl1_", "llPtGEN_mumu_excl1_","llPtGEN_ee_excl1_","llPtGEN_ll_excl1_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} = 1)", 1, 100, 300);
}


void ratioGenPlots_excl2(){		
	ratioGenPlots("ratioGenPlot_PtGEN_excl2_", "photonPtGEN_excl2_", "llPtGEN_mumu_excl2_","llPtGEN_ee_excl2_","llPtGEN_ll_excl2_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} = 2)", 2, 0, 800);
}

void ratioGenPlots_excl2_zoom(){
	ratioGenPlots("ratioGenPlot_PtGEN_excl2_zoom_", "photonPtGEN_excl2_", "llPtGEN_mumu_excl2_","llPtGEN_ee_excl2_","llPtGEN_ll_excl2_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} = 2)", 1, 100, 300);
}


void ratioGenPlots_N1(){		
	ratioGenPlots("ratioGenPlot_PtGEN_N1_", "photonPtGEN_N1_", "llPtGEN_mumu_N1_","llPtGEN_ee_N1_","llPtGEN_ll_N1_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} > 1)", 2, 0, 800);
}

void ratioGenPlots_N1_zoom(){
	ratioGenPlots("ratioGenPlot_PtGEN_N1_zoom_", "photonPtGEN_N1_", "llPtGEN_mumu_N1_","llPtGEN_ee_N1_","llPtGEN_ll_N1_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} > 1)", 1, 100, 300);
}


void ratioGenPlots_N2(){		
	ratioGenPlots("ratioGenPlot_PtGEN_N2_", "photonPtGEN_N2_", "llPtGEN_mumu_N2_","llPtGEN_ee_N2_","llPtGEN_ll_N2_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} > 2)", 2, 0, 800);
}

void ratioGenPlots_N2_zoom(){
	ratioGenPlots("ratioGenPlot_PtGEN_N2_zoom_", "photonPtGEN_N2_", "llPtGEN_mumu_N2_","llPtGEN_ee_N2_","llPtGEN_ll_N2_", "p_{T}^{#gamma} [GeV] (N^{jets}_{GEN} > 2)", 1, 100, 300);
}

void ratioGenPlots_TOT(){
	ratioGenPlots_N0();
	ratioGenPlots_N0_zoom();
	ratioGenPlots_excl1();	
	ratioGenPlots_excl1_zoom();	
	ratioGenPlots_excl2();	
	ratioGenPlots_excl2_zoom();	
	ratioGenPlots_N1();
	ratioGenPlots_N1_zoom();
	ratioGenPlots_N2();
	ratioGenPlots_N2_zoom();
}
