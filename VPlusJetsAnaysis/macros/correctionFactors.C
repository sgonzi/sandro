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

using namespace std;

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


void correctionFactor(const char* titleh1, const char* titleh2, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L correctionFactor.C++
  //       ie: 	comparestack("photonPtGEN_N0_LogBin_", "SelectedPhotons_Pt_LogBin_1_", "p_{T}^{#gamma_{1}} [GeV/#font[12]{c}]", 1, -999, -999);

	setMYStyle();

	// ==================================== choose the tools

	string folder = "17_results_2013_11_25";         // analysis folder

	char geo[100] = "barrel";                // "barrel", "endcaps" or "total"
	                                         
	bool logX = true;											// log X scale for p_T plot	
	bool inv_sigmaietaieta = false;          // inverted sigmaietaieta cut
	bool inv_isolation = false;              // inverted isolation set cut

	bool signal_MAD = true;                  // true: signal = MADGRAPH; false: signal = PYTHIA

	Int_t itype = 17;                        // it identifies histos with different analysis 


	// ==================================== string names

	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string folder_s = folder + "/";
	string SB_folder;
		SB_folder = "sM1_bQ0/";
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
	char root_char[200];
	ss_r << root_string;
	ss_r >> root_char;

	string address = folder_s + geo_s + out_files;


	// ==================================== exception controls

	if (inv_sigmaietaieta && inv_isolation){
		cout << "ERROR: you are trying to invert both SIGMAIETAIETA and ISOLATION cuts" << endl << endl;
		throw cms::Exception("WrongBool");
	}
	if (!(Geo == "barrel" || Geo == "endcaps" || Geo == "total")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps\" or \"total\"). You wrote: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}	


	// ==================================== assign files names

	Char_t DATA_RR_Run2012A_22Jan2013_name[100];
	Char_t DATA_RR_Run2012B_22Jan2013_name[100];
	Char_t DATA_RR_Run2012C_22Jan2013_name[100];
	Char_t DATA_RR_Run2012D_22Jan2013_name[100];
					
	Char_t GJets_HT_40To100_name[100];
	Char_t GJets_HT_100To200_name[100];	
	Char_t GJets_HT_200To400_name[100];
	Char_t GJets_HT_400ToInf_name[100];

	Char_t DiPhotonJets_name[100];

	sprintf(DATA_RR_Run2012A_22Jan2013_name,"DATA_RR_Run2012A-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_RR_Run2012B_22Jan2013_name,"DATA_RR_Run2012B-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_RR_Run2012C_22Jan2013_name,"DATA_RR_Run2012C-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
	sprintf(DATA_RR_Run2012D_22Jan2013_name,"DATA_RR_Run2012D-22Jan2013_histos_%d_%s%s",itype, geo, root_char);
	

	sprintf(GJets_HT_40To100_name,"MC_GJets_HT-40To100_histos_%d_%s%s",itype, geo, root_char);
	sprintf(GJets_HT_100To200_name,"MC_GJets_HT-100To200_histos_%d_%s%s",itype, geo, root_char);	
	sprintf(GJets_HT_200To400_name,"MC_GJets_HT-200To400_histos_%d_%s%s",itype, geo, root_char);
	sprintf(GJets_HT_400ToInf_name,"MC_GJets_HT-400ToInf_histos_%d_%s%s",itype, geo, root_char);

	cout << "GJets file 21 is: " << GJets_HT_40To100_name << endl;
	cout << "GJets file 22 is: " << GJets_HT_100To200_name << endl;	
	cout << "GJets file 23 is: " << GJets_HT_200To400_name << endl;
	cout << "GJets file 24 is: " << GJets_HT_400ToInf_name << endl;
	cout << endl;

	
	sprintf(DiPhotonJets_name,"MC_DiPhotonJets_histos_%d_%s%s",itype, geo, root_char);
	cout << "DiPhotonJets file 51 is: " << DiPhotonJets_name << endl;
	cout << endl;



	// ==================================== load TFiles

	TFile *DATA_RR_Run2012A_22Jan2013_file;
	TFile *DATA_RR_Run2012B_22Jan2013_file;
	TFile *DATA_RR_Run2012C_22Jan2013_file;
	TFile *DATA_RR_Run2012D_22Jan2013_file;

	TFile *GJets_HT_40To100_file;
	TFile *GJets_HT_100To200_file;	
	TFile *GJets_HT_200To400_file;
	TFile *GJets_HT_400ToInf_file;


	TFile *DiPhotonJets_file;

	DATA_RR_Run2012A_22Jan2013_file = new TFile((address+DATA_RR_Run2012A_22Jan2013_name).c_str());
	DATA_RR_Run2012B_22Jan2013_file = new TFile((address+DATA_RR_Run2012B_22Jan2013_name).c_str());
	DATA_RR_Run2012C_22Jan2013_file = new TFile((address+DATA_RR_Run2012C_22Jan2013_name).c_str());
	DATA_RR_Run2012D_22Jan2013_file = new TFile((address+DATA_RR_Run2012D_22Jan2013_name).c_str());				


	GJets_HT_40To100_file = new TFile((address+GJets_HT_40To100_name).c_str());	
	GJets_HT_100To200_file = new TFile((address+GJets_HT_100To200_name).c_str());	
	GJets_HT_200To400_file = new TFile((address+GJets_HT_200To400_name).c_str());
	GJets_HT_400ToInf_file = new TFile((address+GJets_HT_400ToInf_name).c_str()); 

	DiPhotonJets_file = new TFile((address+DiPhotonJets_name).c_str());
	

	// ==================================== load TH1F

	Char_t titlehisto1[100];
	Char_t titlehisto2[100];

	strcpy(titlehisto1,titleh1);
	strcpy(titlehisto2,titleh2);

	Char_t namevariable1[200];
	
	strcpy(namevariable1,namevariable);


	cout << "========================" <<endl;	
	cout << endl;	

	cout << "Analyzing Histogram " << titlehisto1 << endl;
	cout << "and " << titlehisto2 << endl;

	cout << endl;	
	cout << "========================" <<endl;	
	cout << endl;	

	// histo1	
	TH1F *GJets_HT_40To100_histo1;
	TH1F *GJets_HT_100To200_histo1;
	TH1F *GJets_HT_200To400_histo1;
	TH1F *GJets_HT_400ToInf_histo1;
	TH1F *GJets_HT_xToy_total_histo1;

	TH1F *DiPhotonJets_histo1;
	TH1F *DiPhotonJets_total_histo1;

	TH1F *Signal_total_histo1;

	// histo2
	TH1F *DATA_RR_Run2012A_22Jan2013_histo2;
	TH1F *DATA_RR_Run2012B_22Jan2013_histo2;
	TH1F *DATA_RR_Run2012C_22Jan2013_histo2;
	TH1F *DATA_RR_Run2012D_22Jan2013_histo2;
	TH1F *DATA_total_histo2;

	TH1F *GJets_HT_40To100_histo2;
	TH1F *GJets_HT_100To200_histo2;
	TH1F *GJets_HT_200To400_histo2;
	TH1F *GJets_HT_400ToInf_histo2;
	TH1F *GJets_HT_xToy_total_histo2;

	TH1F *DiPhotonJets_histo2;
	TH1F *DiPhotonJets_total_histo2;

	TH1F *Signal_total_histo2;

	TH1F *ratio_histo;


	// histo1
		//--- data ReReco ----------------------------------------------------------
		DATA_RR_Run2012A_22Jan2013_histo2=(TH1F*)DATA_RR_Run2012A_22Jan2013_file->Get(titlehisto2);
		DATA_RR_Run2012A_22Jan2013_histo2->Rebin(rebin);

		DATA_RR_Run2012B_22Jan2013_histo2=(TH1F*)DATA_RR_Run2012B_22Jan2013_file->Get(titlehisto2);
		DATA_RR_Run2012B_22Jan2013_histo2->Rebin(rebin);

		DATA_RR_Run2012C_22Jan2013_histo2=(TH1F*)DATA_RR_Run2012C_22Jan2013_file->Get(titlehisto2);
		DATA_RR_Run2012C_22Jan2013_histo2->Rebin(rebin);

		DATA_RR_Run2012D_22Jan2013_histo2=(TH1F*)DATA_RR_Run2012D_22Jan2013_file->Get(titlehisto2);
		DATA_RR_Run2012D_22Jan2013_histo2->Rebin(rebin);

		DATA_total_histo2 = (TH1F*) DATA_RR_Run2012A_22Jan2013_histo2->Clone("DATA_total_histo2");
		DATA_total_histo2->Add(DATA_RR_Run2012B_22Jan2013_histo2);
		DATA_total_histo2->Add(DATA_RR_Run2012C_22Jan2013_histo2);
		DATA_total_histo2->Add(DATA_RR_Run2012D_22Jan2013_histo2);

	
	//--- MC signal GJets_HT-xToy ----------------------------------------------

		GJets_HT_40To100_histo1=(TH1F*)GJets_HT_40To100_file->Get(titlehisto1);
		GJets_HT_40To100_histo1->Rebin(rebin);
		
		GJets_HT_100To200_histo1=(TH1F*)GJets_HT_100To200_file->Get(titlehisto1);
		GJets_HT_100To200_histo1->Rebin(rebin);

		GJets_HT_200To400_histo1=(TH1F*)GJets_HT_200To400_file->Get(titlehisto1);
		GJets_HT_200To400_histo1->Rebin(rebin);

		GJets_HT_400ToInf_histo1=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto1);
		GJets_HT_400ToInf_histo1->Rebin(rebin);

		cout << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo1->Integral() << endl;
		cout << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo1->Integral() << endl;	
		cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo1->Integral() << endl;
		cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo1->Integral() << endl;
		cout << endl;
		
		GJets_HT_xToy_total_histo1 = (TH1F*) GJets_HT_40To100_histo1->Clone("GJets_HT_xToy_total_histo1");
		//--- GJets_HT_xToy_total_histo1->Sumw2();
		GJets_HT_xToy_total_histo1->Add(GJets_HT_100To200_histo1);
		GJets_HT_xToy_total_histo1->Add(GJets_HT_200To400_histo1);
		GJets_HT_xToy_total_histo1->Add(GJets_HT_400ToInf_histo1);  
//		GJets_HT_xToy_total_histo1->SetLineColor(1);
//		GJets_HT_xToy_total_histo1->SetFillColor(5);  //for colors comment out Sumw2 in code
	
	// MC signal DiPhotonJets --------------------------------------------------
	DiPhotonJets_histo1=(TH1F*)DiPhotonJets_file->Get(titlehisto1);
	DiPhotonJets_histo1->Rebin(rebin);
	
	cout << "DiPhotonJets entries = " << DiPhotonJets_histo1->Integral() << endl;
	cout << endl;

	DiPhotonJets_total_histo1 = (TH1F*) DiPhotonJets_histo1->Clone("DiPhotonJets_total_histo1");
	//--- DiPhotonJets_total_histo1->Sumw2();
//	DiPhotonJets_total_histo1->SetLineColor(1);
//	DiPhotonJets_total_histo1->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	Signal_total_histo1 = (TH1F*) GJets_HT_xToy_total_histo1->Clone("Signal_total_histo1");
	Signal_total_histo1->Add(DiPhotonJets_total_histo1);
	Signal_total_histo1->Sumw2();

	// histo2	
	//--- MC signal GJets_HT-xToy ----------------------------------------------

		GJets_HT_40To100_histo2=(TH1F*)GJets_HT_40To100_file->Get(titlehisto2);
		GJets_HT_40To100_histo2->Rebin(rebin);
		
		GJets_HT_100To200_histo2=(TH1F*)GJets_HT_100To200_file->Get(titlehisto2);
		GJets_HT_100To200_histo2->Rebin(rebin);

		GJets_HT_200To400_histo2=(TH1F*)GJets_HT_200To400_file->Get(titlehisto2);
		GJets_HT_200To400_histo2->Rebin(rebin);

		GJets_HT_400ToInf_histo2=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto2);
		GJets_HT_400ToInf_histo2->Rebin(rebin);

		cout << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo2->Integral() << endl;
		cout << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo2->Integral() << endl;	
		cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo2->Integral() << endl;
		cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo2->Integral() << endl;
		cout << endl;
		
		GJets_HT_xToy_total_histo2 = (TH1F*) GJets_HT_40To100_histo2->Clone("GJets_HT_xToy_total_histo2");
		//--- GJets_HT_xToy_total_histo2->Sumw2();
		GJets_HT_xToy_total_histo2->Add(GJets_HT_100To200_histo2);
		GJets_HT_xToy_total_histo2->Add(GJets_HT_200To400_histo2);
		GJets_HT_xToy_total_histo2->Add(GJets_HT_400ToInf_histo2);  
//		GJets_HT_xToy_total_histo2->SetLineColor(1);
//		GJets_HT_xToy_total_histo2->SetFillColor(5);  //for colors comment out Sumw2 in code
	
	// MC signal DiPhotonJets --------------------------------------------------
	DiPhotonJets_histo2=(TH1F*)DiPhotonJets_file->Get(titlehisto2);
	DiPhotonJets_histo2->Rebin(rebin);
	
	cout << "DiPhotonJets entries = " << DiPhotonJets_histo2->Integral() << endl;
	cout << endl;

	DiPhotonJets_total_histo2 = (TH1F*) DiPhotonJets_histo2->Clone("DiPhotonJets_total_histo2");
	//--- DiPhotonJets_total_histo2->Sumw2();
//	DiPhotonJets_total_histo2->SetLineColor(1);
//	DiPhotonJets_total_histo2->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	Signal_total_histo2 = (TH1F*) GJets_HT_xToy_total_histo2->Clone("Signal_total_histo2");
	Signal_total_histo2->Add(DiPhotonJets_total_histo2);
	Signal_total_histo2->Sumw2();

	// ==================================== print Entries number

	cout << "========================" <<endl;	
	cout << endl;
	cout << "Signal total GEN entries = " << Signal_total_histo1->Integral() << endl;	
	cout << endl;
	cout << "Signal total REC entries = " << Signal_total_histo2->Integral() << endl;  
	cout << endl;
	cout << "DATA total entries = " << DATA_total_histo2->Integral() << endl;
	cout << endl;

	cout << "========================" <<endl;	
	cout << endl;
		
	// ==================================== load Canvas

	string titleCanva1 = "LogpTGENREC";
  TCanvas *Canva1 = new TCanvas(titleCanva1.c_str(),titleCanva1.c_str());  

	Signal_total_histo1->Draw("histo");
	Signal_total_histo2->Draw("histo same");
	Signal_total_histo1->SetLineWidth(2);
	Signal_total_histo2->SetLineWidth(2);
	Signal_total_histo1->SetLineColor(2);
	Signal_total_histo2->SetLineColor(4);

	DATA_total_histo2->SetMarkerSize(0.7);
	DATA_total_histo2->SetMarkerStyle(20);
	DATA_total_histo2->SetMinimum(0.1);
	DATA_total_histo2->Draw("E same");

	gPad->SetLogy();
	if (logX){
		gPad->SetLogx(); // for p_T plot	
	}


	Signal_total_histo1->GetYaxis()->SetRangeUser(100,200000);
//	Signal_total_histo1->GetXaxis()->SetTitleOffset(0.8);
	Signal_total_histo1->Draw("AXIS X+ Y+ SAME");
	Signal_total_histo1->Draw("AXIS SAME");
	Signal_total_histo1->GetYaxis()->SetTitleOffset(1.3);		
	Signal_total_histo1->GetXaxis()->SetTitle(namevariable1);
//	Signal_total_histo1->GetXaxis()->SetTitleSize(0.05);
	Signal_total_histo1->GetYaxis()->SetTitle("Events");

	TLegend *leg1 =new TLegend(0.637,0.666,0.830,0.8756);
	leg1->SetFillColor(0); 
  leg1->SetFillStyle(0); 
  leg1->SetBorderSize(0);
	leg1->AddEntry(DATA_total_histo2,"Data","pL");
	leg1->AddEntry(Signal_total_histo1,"GEN signal","l");
	leg1->AddEntry(Signal_total_histo2,"REC signal","l");
	leg1->Draw();

  TPaveText* text1_1 = new TPaveText(0.1194,0.9310,0.3313,0.9780,"NDC");
  text1_1->SetFillColor(0);
  text1_1->SetFillStyle(0);
  text1_1->SetBorderSize(0);
  text1_1->AddText("CMS Preliminary");
  text1_1->SetTextAlign(11);
  text1_1->Draw();

  TPaveText* text1_2 = new TPaveText(0.5627,0.9310,0.8678,0.9780,"NDC");
  text1_2->SetFillColor(0);
  text1_2->SetFillStyle(0);
  text1_2->SetBorderSize(0);
  text1_2->AddText("#sqrt{s} = 8 TeV, L = 19.71 fb^{-1}");
  text1_2->SetTextAlign(11);
  text1_2->Draw();

	string titleCanva2 = "LogpTcorrectionfactors";
  TCanvas *Canva2 = new TCanvas(titleCanva2.c_str(),titleCanva2.c_str());  

	ratio_histo = (TH1F*) Signal_total_histo2->Clone("ratio_histo");
	ratio_histo->Divide(Signal_total_histo1);
	ratio_histo->Sumw2();

	if (logX){
		gPad->SetLogx(); // for p_T plot	
	}

	ratio_histo->GetYaxis()->SetRangeUser(0.4,0.8);
	ratio_histo->Draw("P");
	ratio_histo->Draw("AXIS X+ Y+ SAME");
	ratio_histo->Draw("AXIS SAME");
  ratio_histo->GetYaxis()->SetTitleOffset(1.3);
  ratio_histo->GetXaxis()->SetTitle(namevariable1);
	ratio_histo->GetYaxis()->SetTitle("C_{i}(#gamma)");
//	ratio_histo->GetYaxis()->SetNdivisions(505, "kTRUE");
	ratio_histo->SetMarkerStyle(20);
	ratio_histo->SetMarkerColor(kViolet);
	ratio_histo->SetMarkerSize(0.7);
	ratio_histo->SetLineColor(kViolet);

  TPaveText* text2_1 = new TPaveText(0.1194,0.9310,0.3313,0.9780,"NDC");
  text2_1->SetFillColor(0);
  text2_1->SetFillStyle(0);
  text2_1->SetBorderSize(0);
  text2_1->AddText("CMS Preliminary");
  text2_1->SetTextAlign(11);
  text2_1->Draw();

  TPaveText* text2_2 = new TPaveText(0.5627,0.9310,0.8678,0.9780,"NDC");
  text2_2->SetFillColor(0);
  text2_2->SetFillStyle(0);
  text2_2->SetBorderSize(0);
  text2_2->AddText("#sqrt{s} = 8 TeV, L = 19.71 fb^{-1}");
  text2_2->SetTextAlign(11);
  text2_2->Draw();



	root_string = ".root";
	pdf_string = ".pdf";
	string C_string = ".C";
  Canva1->SaveAs((folder_s + geo_s + SB_folder + pdf_folder + titleCanva1 + pdf_string).c_str());
  Canva1->SaveAs((folder_s + geo_s + SB_folder + root_folder + titleCanva1 + root_string).c_str());
  Canva1->SaveAs((folder_s + geo_s + SB_folder + root_folder + titleCanva1 + C_string).c_str());
	Canva1->Close();

  Canva2->SaveAs((folder_s + geo_s + SB_folder + pdf_folder + titleCanva2 + pdf_string).c_str());
  Canva2->SaveAs((folder_s + geo_s + SB_folder + root_folder + titleCanva2 + root_string).c_str());
  Canva2->SaveAs((folder_s + geo_s + SB_folder + root_folder + titleCanva2 + C_string).c_str());
	Canva2->Close();


	// ==================================== close files

	GJets_HT_40To100_file->Close();	
	GJets_HT_100To200_file->Close();	
	GJets_HT_200To400_file->Close();
	GJets_HT_400ToInf_file->Close(); 
	
	DiPhotonJets_file->Close();

}
