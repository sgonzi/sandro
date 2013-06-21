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


void templates(const char* titleh, const char* namevariable, const int rebin, const double x_min, const double x_max){

  // Usage is: .L comparestack.C+
  //       ie: comparestack("SelectedPhotons_Pt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]", 1);

	setMYStyle();
	
	// ==================================== choose the tools
	
	string folder = "2_results_2013_06_18"; // analysis folder
	
	char geo[100] = "barrel";               // "barrel", "endcaps" or "total"

	bool data_ReReco = true;                // true: data = ReReco
	                                        // false: data = PromptReco
	                                         
	bool inv_sigmaietaieta = true;         // inverted sigmaietaieta cut
	bool inv_isolation = false;             // inverted isolation set cut

	bool signal_MAD = true;                 // true: signal = MADGRAPH; false: signal = PYTHIA
	bool background_QCD = true;             // true: background = PYTHIA filtered (QCD EMEnriched + BCtoE); 
	                                        // false: background = MADGRAPH not filtered (QCD HT)
	Int_t itype = 2;                        // it identifies histos with different analysis 
	
	string sample = "DATA_INV"; // "MC_SIG", "MC_BACK", "DATA" or "DATA_INV"


	// ==================================== string names
	
	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string folder_s = folder + "/";
	string out_files = "output_files/";
	string fit_pdf_folder = "fit_pdf_plots/";
	string pdf_string = ".pdf";
	string fit_root_folder = "fit_root_plots/";
	string root_string = ".root";
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
	

	// ==================================== open now the output TFile

	root_string = ".root";
	pdf_string = ".pdf";
	string sample_mod = "";
	if (inv_sigmaietaieta && !inv_isolation){
		sample_mod = sample + sigmaietaieta_s + "_";
	}
	else if (inv_isolation && !inv_sigmaietaieta){
		sample_mod = sample + isolation_s + "_";
	}
	else sample_mod = sample + "_";
	string templates = "template_";
	string outfilename = (sample_mod + templates + titleh + root_string).c_str();

	TFile *outfile = new TFile((address + outfilename).c_str(),"recreate");


	// ==================================== load TH1F

	Char_t titlehisto[100];

	strcpy(titlehisto,titleh);

	cout << "========================" <<endl;	
	cout << endl;	

	cout << "Analyzing Histogram " << titlehisto << endl;

	cout << endl;	
	cout << "========================" <<endl;	
	cout << endl;	

	TH1F *DATA_RR_Run2012A_22Jan2013_histo;
	TH1F *DATA_RR_Run2012B_22Jan2013_histo;
	TH1F *DATA_RR_Run2012C_22Jan2013_histo;
	TH1F *DATA_RR_Run2012D_22Jan2013_histo;
	TH1F *DATA_ReReco_total_histo;
			
	TH1F *DATA_PR_Run2012A_13Jul2012_histo;
	TH1F *DATA_PR_Run2012A_recover_06Aug2012_histo;
	TH1F *DATA_PR_Run2012B_13Jul2012_histo;
	TH1F *DATA_PR_Run2012C_24Aug2012_histo;
	TH1F *DATA_PR_Run2012C_EcalRecover_11Dec2012_histo;
	TH1F *DATA_PR_Run2012C_PromptReco_histo;
	TH1F *DATA_PR_Run2012D_PromptReco_histo;
	TH1F *DATA_PromptReco_total_histo;

//	TH1F *GJets_HT_40To100_histo;
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

	TH1F *QCD_Pt_20_30_EMEnriched_histo;
	TH1F *QCD_Pt_30_80_EMEnriched_histo;
	TH1F *QCD_Pt_80_170_EMEnriched_histo;
	TH1F *QCD_Pt_170_250_EMEnriched_histo;
	TH1F *QCD_Pt_250_350_EMEnriched_histo;
	TH1F *QCD_Pt_350_EMEnriched_histo;
	TH1F *QCD_Pt_x_y_EMEnriched_total_histo;

	TH1F *QCD_Pt_20_30_BCtoE_histo;
	TH1F *QCD_Pt_30_80_BCtoE_histo;
	TH1F *QCD_Pt_80_170_BCtoE_histo;
	TH1F *QCD_Pt_170_250_BCtoE_histo;
	TH1F *QCD_Pt_250_350_BCtoE_histo;
	TH1F *QCD_Pt_350_BCtoE_histo;;
	TH1F *QCD_Pt_x_y_BCtoE_total_histo;

	TH1F *QCD_HT_100To250_histo;
	TH1F *QCD_HT_250To500_histo;
	TH1F *QCD_HT_500To1000_histo;
	TH1F *QCD_HT_1000ToInf_histo;
	TH1F *QCD_HT_xToy_total_histo;	

	
	if (data_ReReco) {
		//--- data ReReco ----------------------------------------------------------
		DATA_RR_Run2012A_22Jan2013_histo=(TH1F*)DATA_RR_Run2012A_22Jan2013_file->Get(titlehisto);
		DATA_RR_Run2012A_22Jan2013_histo->Rebin(rebin);

		DATA_RR_Run2012B_22Jan2013_histo=(TH1F*)DATA_RR_Run2012B_22Jan2013_file->Get(titlehisto);
		DATA_RR_Run2012B_22Jan2013_histo->Rebin(rebin);

		DATA_RR_Run2012C_22Jan2013_histo=(TH1F*)DATA_RR_Run2012C_22Jan2013_file->Get(titlehisto);
		DATA_RR_Run2012C_22Jan2013_histo->Rebin(rebin);

		DATA_RR_Run2012D_22Jan2013_histo=(TH1F*)DATA_RR_Run2012D_22Jan2013_file->Get(titlehisto);
		DATA_RR_Run2012D_22Jan2013_histo->Rebin(rebin);

		cout << "DATA_RR_Run2012A_22Jan2013 entries = " << DATA_RR_Run2012A_22Jan2013_histo->Integral() << endl;  
		cout << "DATA_RR_Run2012B_22Jan2013 entries = " << DATA_RR_Run2012B_22Jan2013_histo->Integral() << endl;  
		cout << "DATA_RR_Run2012C_22Jan2013 entries = " << DATA_RR_Run2012C_22Jan2013_histo->Integral() << endl;  
		cout << "DATA_RR_Run2012D_22Jan2013 entries = " << DATA_RR_Run2012D_22Jan2013_histo->Integral() << endl;  
		cout << endl;	
	
		DATA_ReReco_total_histo = (TH1F*) DATA_RR_Run2012A_22Jan2013_histo->Clone("DATA_ReReco_total_histo");
		DATA_ReReco_total_histo->Add(DATA_RR_Run2012B_22Jan2013_histo);
		DATA_ReReco_total_histo->Add(DATA_RR_Run2012C_22Jan2013_histo);
		DATA_ReReco_total_histo->Add(DATA_RR_Run2012D_22Jan2013_histo);
		}
	else {
		//--- data PromptReco-------------------------------------------------------
		DATA_PR_Run2012A_13Jul2012_histo=(TH1F*)DATA_PR_Run2012A_13Jul2012_file->Get(titlehisto);
		DATA_PR_Run2012A_13Jul2012_histo->Rebin(rebin);

		DATA_PR_Run2012A_recover_06Aug2012_histo=(TH1F*)DATA_PR_Run2012A_recover_06Aug2012_file->Get(titlehisto);
		DATA_PR_Run2012A_recover_06Aug2012_histo->Rebin(rebin);

		DATA_PR_Run2012B_13Jul2012_histo=(TH1F*)DATA_PR_Run2012B_13Jul2012_file->Get(titlehisto);
		DATA_PR_Run2012B_13Jul2012_histo->Rebin(rebin);

		DATA_PR_Run2012C_24Aug2012_histo=(TH1F*)DATA_PR_Run2012C_24Aug2012_file->Get(titlehisto);
		DATA_PR_Run2012C_24Aug2012_histo->Rebin(rebin);

		DATA_PR_Run2012C_EcalRecover_11Dec2012_histo=(TH1F*)DATA_PR_Run2012C_EcalRecover_11Dec2012_file->Get(titlehisto);
		DATA_PR_Run2012C_EcalRecover_11Dec2012_histo->Rebin(rebin);

		DATA_PR_Run2012C_PromptReco_histo=(TH1F*)DATA_PR_Run2012C_PromptReco_file->Get(titlehisto);
		DATA_PR_Run2012C_PromptReco_histo->Rebin(rebin);

		DATA_PR_Run2012D_PromptReco_histo=(TH1F*)DATA_PR_Run2012D_PromptReco_file->Get(titlehisto);
		DATA_PR_Run2012D_PromptReco_histo->Rebin(rebin);

		cout << "DATA_PR_Run2012A_13Jul2012 entries = " << DATA_PR_Run2012A_13Jul2012_histo->Integral() << endl;  
		cout << "DATA_PR_Run2012A_recover_06Aug2012 entries = " << DATA_PR_Run2012A_recover_06Aug2012_histo->Integral() << endl;  
		cout << "DATA_PR_Run2012B_13Jul2012 entries = " << DATA_PR_Run2012B_13Jul2012_histo->Integral() << endl;  
		cout << "DATA_PR_Run2012C_24Aug2012 entries = " << DATA_PR_Run2012C_24Aug2012_histo->Integral() << endl;  
		cout << "DATA_PR_Run2012C_EcalRecover_11Dec2012 entries = " << DATA_PR_Run2012C_EcalRecover_11Dec2012_histo->Integral() << endl;  
		cout << "DATA_PR_Run2012C_PromptReco entries = " << DATA_PR_Run2012C_PromptReco_histo->Integral() << endl;  
		cout << "DATA_PR_Run2012D_PromptReco entries = " << DATA_PR_Run2012D_PromptReco_histo->Integral() << endl;  
		cout << endl;	
	
		DATA_PromptReco_total_histo = (TH1F*) DATA_PR_Run2012A_13Jul2012_histo->Clone("DATA_PromptReco_total_histo");
		DATA_PromptReco_total_histo->Add(DATA_PR_Run2012A_recover_06Aug2012_histo);
		DATA_PromptReco_total_histo->Add(DATA_PR_Run2012B_13Jul2012_histo);
		DATA_PromptReco_total_histo->Add(DATA_PR_Run2012C_24Aug2012_histo);
		DATA_PromptReco_total_histo->Add(DATA_PR_Run2012C_EcalRecover_11Dec2012_histo);
		DATA_PromptReco_total_histo->Add(DATA_PR_Run2012C_PromptReco_histo);
		DATA_PromptReco_total_histo->Add(DATA_PR_Run2012D_PromptReco_histo);
	}
	TH1F *DATA_total_histo;
	if (data_ReReco) {
		DATA_total_histo = (TH1F*) DATA_ReReco_total_histo->Clone("DATA_total_histo");
	}
	else{
		DATA_total_histo = (TH1F*) DATA_PromptReco_total_histo->Clone("DATA_total_histo");
	}

	if(signal_MAD){				
		//--- MC signal GJets_HT-xToy ----------------------------------------------
/*
		GJets_HT_40To100_histo=(TH1F*)GJets_HT_40To100_file->Get(titlehisto);
		GJets_HT_40To100_histo->Rebin(rebin);
*/
		
		GJets_HT_100To200_histo=(TH1F*)GJets_HT_100To200_file->Get(titlehisto);
		GJets_HT_100To200_histo->Rebin(rebin);

		GJets_HT_200To400_histo=(TH1F*)GJets_HT_200To400_file->Get(titlehisto);
		GJets_HT_200To400_histo->Rebin(rebin);

		GJets_HT_400ToInf_histo=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto);
		GJets_HT_400ToInf_histo->Rebin(rebin);

//		cout << "GJets_HT_40To100 entries = " << GJets_HT_40To100_histo->Integral() << endl;
		cout << "GJets_HT_100To200 entries = " << GJets_HT_100To200_histo->Integral() << endl;	
		cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;
		cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;
		cout << endl;
		
		GJets_HT_xToy_total_histo = (TH1F*) GJets_HT_100To200_histo->Clone("GJets_HT_xToy_total_histo");
		//--- GJets_HT_xToy_total_histo->Sumw2();
//		GJets_HT_xToy_total_histo->Add(GJets_HT_40To100_histo);	
		GJets_HT_xToy_total_histo->Add(GJets_HT_200To400_histo);
		GJets_HT_xToy_total_histo->Add(GJets_HT_400ToInf_histo);  
		GJets_HT_xToy_total_histo->SetLineColor(1);
		GJets_HT_xToy_total_histo->SetFillColor(5);  //for colors comment out Sumw2 in code
	}

	else {	
		// MC signal G_Pt-XtoY --------------------------------------------------	
		G_Pt_15to30_histo=(TH1F*)G_Pt_15to30_file->Get(titlehisto);
		G_Pt_15to30_histo->Rebin(rebin);

		G_Pt_30to50_histo=(TH1F*)G_Pt_30to50_file->Get(titlehisto);
		G_Pt_30to50_histo->Rebin(rebin);

		G_Pt_50to80_histo=(TH1F*)G_Pt_50to80_file->Get(titlehisto);
		G_Pt_50to80_histo->Rebin(rebin);

		G_Pt_80to120_histo=(TH1F*)G_Pt_80to120_file->Get(titlehisto);
		G_Pt_80to120_histo->Rebin(rebin);

		G_Pt_120to170_histo=(TH1F*)G_Pt_120to170_file->Get(titlehisto);
		G_Pt_120to170_histo->Rebin(rebin);
	
		G_Pt_170to300_histo=(TH1F*)G_Pt_170to300_file->Get(titlehisto);
		G_Pt_170to300_histo->Rebin(rebin);

		G_Pt_300to470_histo=(TH1F*)G_Pt_300to470_file->Get(titlehisto);
		G_Pt_300to470_histo->Rebin(rebin);

		G_Pt_470to800_histo=(TH1F*)G_Pt_470to800_file->Get(titlehisto);
		G_Pt_470to800_histo->Rebin(rebin);

		G_Pt_800to1400_histo=(TH1F*)G_Pt_800to1400_file->Get(titlehisto);
		G_Pt_800to1400_histo->Rebin(rebin);

		G_Pt_1400to1800_histo=(TH1F*)G_Pt_1400to1800_file->Get(titlehisto);
		G_Pt_1400to1800_histo->Rebin(rebin);

		G_Pt_1800_histo=(TH1F*)G_Pt_1800_file->Get(titlehisto);
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
		G_Pt_XtoY_total_histo->SetLineColor(1);
		G_Pt_XtoY_total_histo->SetFillColor(kGreen+2);  //for colors comment out Sumw2 in code
	}
	
	// MC signal DiPhotonJets --------------------------------------------------
	DiPhotonJets_histo=(TH1F*)DiPhotonJets_file->Get(titlehisto);
	DiPhotonJets_histo->Rebin(rebin);
	
	cout << "DiPhotonJets entries = " << DiPhotonJets_histo->Integral() << endl;
	cout << endl;

	DiPhotonJets_total_histo = (TH1F*) DiPhotonJets_histo->Clone("DiPhotonJets_total_histo");
	//--- DiPhotonJets_total_histo->Sumw2();
	DiPhotonJets_total_histo->SetLineColor(1);
	DiPhotonJets_total_histo->SetFillColor(kGray+2);  //for colors comment out Sumw2 in code

	if (!background_QCD){	
		//--- MC background QCD_Pt_x_y EMEnriched ----------------------------------	
		QCD_Pt_20_30_EMEnriched_histo=(TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto);
		QCD_Pt_20_30_EMEnriched_histo->Rebin(rebin);

		QCD_Pt_30_80_EMEnriched_histo=(TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto);
		QCD_Pt_30_80_EMEnriched_histo->Rebin(rebin);

		QCD_Pt_80_170_EMEnriched_histo=(TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto);
		QCD_Pt_80_170_EMEnriched_histo->Rebin(rebin);

		QCD_Pt_170_250_EMEnriched_histo=(TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto);
		QCD_Pt_170_250_EMEnriched_histo->Rebin(rebin);

		QCD_Pt_250_350_EMEnriched_histo=(TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto);
		QCD_Pt_250_350_EMEnriched_histo->Rebin(rebin);

		QCD_Pt_350_EMEnriched_histo=(TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto);
		QCD_Pt_350_EMEnriched_histo->Rebin(rebin);

		cout << "QCD_Pt_20_30_EMEnriched entries = " << QCD_Pt_20_30_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_30_80_EMEnriched entries = " << QCD_Pt_30_80_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_80_170_EMEnriched entries = " << QCD_Pt_80_170_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_170_250_EMEnriched entries = " << QCD_Pt_170_250_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_250_350_EMEnriched entries = " << QCD_Pt_250_350_EMEnriched_histo->Integral() << endl;
		cout << "QCD_Pt_350_EMEnriched entries = " << QCD_Pt_350_EMEnriched_histo->Integral() << endl;
		cout << endl;

		QCD_Pt_x_y_EMEnriched_total_histo = (TH1F*) QCD_Pt_20_30_EMEnriched_histo->Clone("QCD_Pt_x_y_EMEnriched_total_histo");
		//	QCD_Pt_x_y_EMEnriched_total_histo->Sumw2();
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_30_80_EMEnriched_histo);
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_80_170_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_170_250_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_250_350_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_350_EMEnriched_histo);  
		QCD_Pt_x_y_EMEnriched_total_histo->SetLineColor(1);
		QCD_Pt_x_y_EMEnriched_total_histo->SetFillColor(kMagenta+2);


		//--- MC background QCD_Pt_x_y BCtoE ----------------------------------
		QCD_Pt_20_30_BCtoE_histo=(TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto);
		QCD_Pt_20_30_BCtoE_histo->Rebin(rebin);

		QCD_Pt_30_80_BCtoE_histo=(TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto);
		QCD_Pt_30_80_BCtoE_histo->Rebin(rebin);

		QCD_Pt_80_170_BCtoE_histo=(TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto);
		QCD_Pt_80_170_BCtoE_histo->Rebin(rebin);

		QCD_Pt_170_250_BCtoE_histo=(TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto);
		QCD_Pt_170_250_BCtoE_histo->Rebin(rebin);

		QCD_Pt_250_350_BCtoE_histo=(TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto);
		QCD_Pt_250_350_BCtoE_histo->Rebin(rebin);

		QCD_Pt_350_BCtoE_histo=(TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto);
		QCD_Pt_350_BCtoE_histo->Rebin(rebin);

		cout << "QCD_Pt_20_30_BCtoE entries = " << QCD_Pt_20_30_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_30_80_BCtoE entries = " << QCD_Pt_30_80_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_80_170_BCtoE entries = " << QCD_Pt_80_170_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_170_250_BCtoE entries = " << QCD_Pt_170_250_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_250_350_BCtoE entries = " << QCD_Pt_250_350_BCtoE_histo->Integral() << endl;
		cout << "QCD_Pt_350_BCtoE entries = " << QCD_Pt_350_BCtoE_histo->Integral() << endl;
		cout << endl;

		QCD_Pt_x_y_BCtoE_total_histo = (TH1F*) QCD_Pt_20_30_BCtoE_histo->Clone("QCD_Pt_x_y_BCtoE_total_histo");
		//	QCD_Pt_x_y_BCtoE_total_histo->Sumw2();
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_30_80_BCtoE_histo);
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_80_170_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_170_250_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_250_350_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_350_BCtoE_histo);  
		QCD_Pt_x_y_BCtoE_total_histo->SetLineColor(1);
		QCD_Pt_x_y_BCtoE_total_histo->SetFillColor(kBlue-7);
	}
	else {	
		// MC background QCD HT-xToy --------------------------------------------
		QCD_HT_100To250_histo=(TH1F*)QCD_HT_100To250_file->Get(titlehisto);
		QCD_HT_100To250_histo->Rebin(rebin);

		QCD_HT_250To500_histo=(TH1F*)QCD_HT_250To500_file->Get(titlehisto);
		QCD_HT_250To500_histo->Rebin(rebin);

		QCD_HT_500To1000_histo=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto);
		QCD_HT_500To1000_histo->Rebin(rebin);

		QCD_HT_1000ToInf_histo=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto);
		QCD_HT_1000ToInf_histo->Rebin(rebin);

		cout << "QCD_HT_100To250 entries " << QCD_HT_100To250_histo->Integral() << endl;  
		cout << "QCD_HT_250To500 entries " << QCD_HT_250To500_histo->Integral() << endl;  
		cout << "QCD_HT_500To1000 entries " << QCD_HT_500To1000_histo->Integral() << endl;
		cout << "QCD_HT_1000ToInf entries " << QCD_HT_1000ToInf_histo->Integral() << endl;
		cout << endl;
	
		QCD_HT_xToy_total_histo = (TH1F*) QCD_HT_100To250_histo->Clone("QCD_HT_xToy_total_histo");
		//	QCD_HT_xToy_total_histo->Sumw2();
		QCD_HT_xToy_total_histo->Add(QCD_HT_250To500_histo);
		QCD_HT_xToy_total_histo->Add(QCD_HT_500To1000_histo);  
		QCD_HT_xToy_total_histo->Add(QCD_HT_1000ToInf_histo);  
		QCD_HT_xToy_total_histo->SetLineColor(1);
		QCD_HT_xToy_total_histo->SetFillColor(kRed+2);
	}

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

	// ==================================== print Entries number

	cout << "========================" <<endl;	
	cout << endl;
	
	if (data_ReReco) cout << "DATA ReReco total entries = " << DATA_ReReco_total_histo->Integral() << endl;
	else cout << "DATA PromptReco total entries = " << DATA_PromptReco_total_histo->Integral() << endl;

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

	cout << "MC SIGNAL total entries = " << MC_SIG_total_histo->Integral() <<endl;
	cout << "MC BACKGROUND total entries = " << MC_BACK_total_histo->Integral() <<endl;
	cout << "DATA INVERTED total entries = " << DATA_INV_total_histo->Integral() <<endl;
	if (data_ReReco) cout << "DATA total entries = " << DATA_ReReco_total_histo->Integral() << endl;
	else cout << "DATA total entries = " << DATA_PromptReco_total_histo->Integral() << endl;

	cout << "========================" <<endl;	
	cout << endl;
	
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
		MC_SIG_total_histo->GetXaxis()->SetTitleSize(0.045);
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
		MC_BACK_total_histo->GetXaxis()->SetTitleSize(0.045);
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
		DATA_INV_total_histo->GetXaxis()->SetTitleSize(0.045);
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
		DATA_total_histo->GetXaxis()->SetTitleSize(0.045);
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
	 	if (data_ReReco){ 
			if (inv_sigmaietaieta && !inv_isolation){
				leg->AddEntry(DATA_INV_total_histo,"DATA ReReco, inverted #sigma_{i #eta i #eta}","pL");
			}
			else if (!inv_sigmaietaieta && inv_isolation){
				leg->AddEntry(DATA_INV_total_histo,"DATA ReReco, inverted isolation","pL");
			}
			else {
				cout << "ERROR: Wrong geometry string (only \"MC_SIG\" or \"MC_BACK\" or \"DATA\" or \"DATA_INV\"). You writed: \"" << geo << "\"" << endl << endl;
			}
		}
		else{
			if (inv_sigmaietaieta && !inv_isolation){
				leg->AddEntry(DATA_INV_total_histo,"DATA PromptReco, inverted #sigma_{i #eta i #eta}","pL");
			}
			else if (!inv_sigmaietaieta && inv_isolation){
				leg->AddEntry(DATA_INV_total_histo,"DATA PromptReco, inverted isolation","pL");
			}
			else {
				cout << "ERROR: Wrong geometry string (only \"MC_SIG\" or \"MC_BACK\" or \"DATA\" or \"DATA_INV\"). You writed: \"" << geo << "\"" << endl << endl;
			}
		
		}
	}  
	else {
	 	if (data_ReReco){ 
			leg->AddEntry(DATA_total_histo,"Data ReReco","pL");
		}
		else {
			leg->AddEntry(DATA_total_histo,"Data PromptReco","pL");		
		}
	}  
	leg->Draw();


  TPaveText* text = new TPaveText(0.6068,0.7722,0.8188,0.8571,"NDC");
  text->SetFillColor(0);
  text->SetFillStyle(0);
  text->SetBorderSize(0);
  text->AddText("CMS Preliminary");
  if (data_ReReco) text->AddText("#sqrt{s} = 8 TeV, L = 19.79 fb^{-1}");
  else text->AddText("#sqrt{s} = 8 TeV, L = 19.03 fb^{-1}");
  text->SetTextAlign(11);
  text->Draw();

  Canva->SaveAs((folder_s + geo_s + fit_pdf_folder + sample_mod + titleh + pdf_string).c_str());
  Canva->SaveAs((folder_s + geo_s + fit_root_folder + sample_mod + titleh + root_string).c_str());
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


void templates_PfIsoChargedHad_RhoCorrected_4binPt() {
	templates("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_", "PfIsoChargedHad #rho corrected, 180 < p_{T}^{#gamma1} < 300", 1, 0, 1.6);
	templates("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_", "PfIsoChargedHad #rho corrected, 300 < p_{T}^{#gamma1} < 400", 1, 0, 1.6);
	templates("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_", "PfIsoChargedHad #rho corrected, 400 < p_{T}^{#gamma1} < 500", 1, 0, 1.6);
	templates("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_", "PfIsoChargedHad #rho corrected, p_{T}^{#gamma1} > 500" ,1 , 0, 1.6);
}


void templates_PfIsoNeutralHad_RhoCorrected_4binPt() {
	templates("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_", "PfIsoNeutralHad #rho corrected, 180 < p_{T}^{#gamma1} < 300", 4, 0, 20);
	templates("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_", "PfIsoNeutralHad #rho corrected, 300 < p_{T}^{#gamma1} < 400", 4, 0, 20);
	templates("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_", "PfIsoNeutralHad #rho corrected, 400 < p_{T}^{#gamma1} < 500", 4, 0, 20);
	templates("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_", "PfIsoNeutralHad #rho corrected, p_{T}^{#gamma1} > 500", 4, 0, 20);
}


void templates_PfIsoPhoton_RhoCorrected_4binPt() {
	templates("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_", "PfIsoPhoton #rho corrected, 180 < p_{T}^{#gamma1} < 300", 1, 0, 6);
	templates("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_", "PfIsoPhoton #rho corrected, 300 < p_{T}^{#gamma1} < 400", 1, 0, 6);
	templates("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_", "PfIsoPhoton #rho corrected, 400 < p_{T}^{#gamma1} < 500", 1, 0, 6);
	templates("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_", "PfIsoPhoton #rho corrected, p_{T}^{#gamma1} > 500", 1, 0, 6);
}


void templates_PfIso_RhoCorrected_4binPt() {
	templates("SelectedPhotons_PfIso_RhoCorr_1_bin01_", "PfIso #rho corrected, 180 < p_{T}^{#gamma1} < 300", 4, 0, 20);
	templates("SelectedPhotons_PfIso_RhoCorr_1_bin02_", "PfIso #rho corrected, 300 < p_{T}^{#gamma1} < 400", 4, 0, 20);
	templates("SelectedPhotons_PfIso_RhoCorr_1_bin03_", "PfIso #rho corrected, 400 < p_{T}^{#gamma1} < 500", 4, 0, 20);
	templates("SelectedPhotons_PfIso_RhoCorr_1_bin04_", "PfIso #rho corrected, p_{T}^{#gamma1} > 500", 4, 0, 20);
}

void templates_id_sieie_4binPt() {
	templates("SelectedPhotons_id_sieie_1_bin01_", "#gamma1 #sigma_{i#etai#eta}, 180 < p_{T}^{#gamma1} < 300", 2, 0., 0.012);
	templates("SelectedPhotons_id_sieie_1_bin02_", "#gamma1 #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma1} < 400", 2, 0., 0.012);
	templates("SelectedPhotons_id_sieie_1_bin03_", "#gamma1 #sigma_{i#etai#eta}, 400 < p_{T}^{#gamma1} < 500", 2, 0., 0.012);
	templates("SelectedPhotons_id_sieie_1_bin04_", "#gamma1 #sigma_{i#etai#eta}, p_{T}^{#gamma1} > 500", 2, 0., 0.012);
}


void templates_Total() {
	templates_PfIsoChargedHad_RhoCorrected_4binPt();
	templates_PfIsoNeutralHad_RhoCorrected_4binPt();
	templates_PfIsoPhoton_RhoCorrected_4binPt();
	templates_PfIso_RhoCorrected_4binPt();
	templates_id_sieie_4binPt();
}	
