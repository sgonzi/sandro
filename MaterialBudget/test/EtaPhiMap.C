#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TChain.h"
#include "TVirtualFitter.h"
#include "TBox.h"
#include "TPaveText.h"
#include "TColor.h"

//#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <algorithm>
#include <math.h>
#include <vector>

void setTDRStyle() {

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  tdrStyle->SetEndErrorSize(2);
  tdrStyle->SetErrorX(0.);
  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.13);
  tdrStyle->SetPadRightMargin(0.15);

// For the Global title:
  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);

// For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);

// For the axis labels:
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);

  tdrStyle->cd();
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


// data dirs
TString theDirName = "EtaPhiMap";
//


//
float xmin = -4;
float xmax = 4; 

float ymin = -3.1416;
float ymax = 3.1416;

float zmin_x0 = 0; 
float zmax_x0 = 2.2;

float zmin_lambdaI = 0; 
float zmax_lambdaI = 0.7;

//

using namespace std;

// Main
void EtaPhiMap() {

	//TDR style
	setTDRStyle(); 
	//palette colori
	palette();

	TString subDetectorFileName = "matbdg_Tracker.root";

	// open file
	TFile *subDetectorFile = new TFile(subDetectorFileName);
	cout << "*** Open file... " << endl;
	cout << subDetectorFileName << endl;
	cout << "***" << endl;

	//case t/X0
	TProfile *prof_x0_Tracker = (TProfile*)subDetectorFile->Get("30");

	// canvas
	TCanvas can_x0("can_x0","can_x0",800,800);
//	can_x0.Range(0,0,25,25);
	
	// Draw
	prof_x0_Tracker->GetXaxis()->SetLimits(xmin,xmax);
	prof_x0_Tracker->GetYaxis()->SetLimits(ymin,ymax);
	prof_x0_Tracker->SetMinimum(zmin_x0);
	prof_x0_Tracker->SetMaximum(zmax_x0);
//	prof_x0_Tracker->GetZaxis()->SetLimits(zmin_x0,zmax_x0);
	prof_x0_Tracker->Draw("zcol");
	prof_x0_Tracker->GetXaxis()->SetTitle("#eta");
	prof_x0_Tracker->GetYaxis()->SetTitle("#varphi");
	prof_x0_Tracker->GetZaxis()->SetTitle("t/X_{0}");
	prof_x0_Tracker->GetZaxis()->SetTitleOffset(1.3);

	// text
	TPaveText* text_x0 = new TPaveText(0.,0.,0.22,0.06,"NDC");
	text_x0->SetFillColor(0);
	text_x0->SetBorderSize(0);
	text_x0->AddText("CMS Simulation");
	text_x0->SetTextAlign(11);
	text_x0->Draw();

	// Store
	can_x0.Update();
	//  can_x0.SaveAs( Form( "%s/EtaPhiMap_x0.eps",  theDirName.Data() ) );
	//  can_x0.SaveAs( Form( "%s/EtaPhiMap_x0.gif",  theDirName.Data() ) );
	can_x0.SaveAs( Form( "%s/EtaPhiMap_x0.pdf",  theDirName.Data() ) );
	can_x0.SaveAs( Form( "%s/EtaPhiMap_x0.png",  theDirName.Data() ) );
	can_x0.SaveAs( Form( "%s/EtaPhiMap_x0.root",  theDirName.Data() ) );
	//  can_x0.SaveAs( Form( "%s/EtaPhiMap_x0.C",  theDirName.Data() ) );
	//

//----------------

	//case t/lambdaI
	TProfile *prof_lambdaI_Tracker = (TProfile*)subDetectorFile->Get("1030");

	// canvas
	TCanvas can_lambdaI("can_lambdaI","can_lambdaI",800,800);
//	can_lambdaI.Range(0,0,25,25);
	
	// Draw
	prof_lambdaI_Tracker->GetXaxis()->SetLimits(xmin,xmax);
	prof_lambdaI_Tracker->GetYaxis()->SetLimits(ymin,ymax);
	prof_lambdaI_Tracker->SetMinimum(zmin_lambdaI);
	prof_lambdaI_Tracker->SetMaximum(zmax_lambdaI);
//	prof_lambdaI_Tracker->GetZaxis()->SetLimits(zmin_lambdaI,zmax_lambdaI);
	prof_lambdaI_Tracker->Draw("zcol");

	prof_lambdaI_Tracker->GetXaxis()->SetTitle("#eta");
	prof_lambdaI_Tracker->GetYaxis()->SetTitle("#varphi");
	prof_lambdaI_Tracker->GetZaxis()->SetTitle("t/#lambda_{I}");
	prof_lambdaI_Tracker->GetZaxis()->SetTitleOffset(1.3);

	// text
	TPaveText* text_lambdaI = new TPaveText(0.,0.,0.22,0.06,"NDC");
	text_lambdaI->SetFillColor(0);
	text_lambdaI->SetBorderSize(0);
	text_lambdaI->AddText("CMS Simulation");
	text_lambdaI->SetTextAlign(11);
	text_lambdaI->Draw();

	// Store
	can_lambdaI.Update();
	//  can_lambdaI.SaveAs( Form( "%s/EtaPhiMap_lambdaI.eps",  theDirName.Data() ) );
	//  can_lambdaI.SaveAs( Form( "%s/EtaPhiMap_lambdaI.gif",  theDirName.Data() ) );
	can_lambdaI.SaveAs( Form( "%s/EtaPhiMap_lambdaI.pdf",  theDirName.Data() ) );
	can_lambdaI.SaveAs( Form( "%s/EtaPhiMap_lambdaI.png",  theDirName.Data() ) );
	can_lambdaI.SaveAs( Form( "%s/EtaPhiMap_lambdaI.root",  theDirName.Data() ) );
	//  can_lambdaI.SaveAs( Form( "%s/EtaPhiMap_lambdaI.C",  theDirName.Data() ) );
	//



}
