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

//#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

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
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

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
  tdrStyle->SetTitleYOffset(0.9);

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


void All_Draw_fit(){

	setTDRStyle();

	float etaMin = -1.7;
	float etaMax = 1.7;
	float ymin   = 0.6;
	float ymax   = 1.2;

	string pwd_0 = "/raid/sandro/Geometria/Tracker_ECAL/0_Original/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string pwd_1 = "/raid/sandro/Geometria/Tracker_ECAL/1_PixelBarrelConnToST/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string pwd_2 = "/raid/sandro/Geometria/Tracker_ECAL/2_PixelBarrelConn1_and_PixelBarrelConn2/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string pwd_3 = "/raid/sandro/Geometria/Tracker_ECAL/3_TIBFlange/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string pwd_4 = "/raid/sandro/Geometria/Tracker_ECAL/4_TIBTIDServiceCylinder/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string pwd_5 = "/raid/sandro/Geometria/Tracker_ECAL/5_TIBTIDMargherita/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string pwd_6 = "/raid/sandro/Geometria/Tracker_ECAL/6_Geometries_12345/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";

	string infile_0 = "draw_fit_0_Original_MC_ClosestTrackpt.root";
	string infile_1 = "draw_fit_1_PixelBarrelConnToST_MC_ClosestTrackpt.root";
	string infile_2 = "draw_fit_2_PixelBarrelConn1_and_PixelBarrelConn2_MC_ClosestTrackpt.root";
	string infile_3 = "draw_fit_3_TIBFlange_MC_ClosestTrackpt.root";
	string infile_4 = "draw_fit_4_TIBTIDServiceCylinder_MC_ClosestTrackpt.root";
	string infile_5 = "draw_fit_5_TIBTIDMargherita_MC_ClosestTrackpt.root";
	string infile_6 = "draw_fit_6_Geometries_12345_MC_ClosestTrackpt.root";

	TFile *f_0 = TFile::Open((pwd_0+infile_0).c_str());
	TFile *f_1 = TFile::Open((pwd_1+infile_1).c_str());
	TFile *f_2 = TFile::Open((pwd_2+infile_2).c_str());
	TFile *f_3 = TFile::Open((pwd_3+infile_3).c_str());
	TFile *f_4 = TFile::Open((pwd_4+infile_4).c_str());
	TFile *f_5 = TFile::Open((pwd_5+infile_5).c_str());
	TFile *f_6 = TFile::Open((pwd_6+infile_6).c_str());

	TFile *outfile = new TFile("all_draw_fit.root","recreate");

	TGraphErrors* g_ptOverGenpt_MC_0 = (TGraphErrors*)f_0->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_0 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_0 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_0 -> SetMarkerColor(1); 

	TGraphErrors* g_ptOverGenpt_MC_1 = (TGraphErrors*)f_1->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_1 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_1 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_1 -> SetMarkerColor(2); 

	TGraphErrors* g_ptOverGenpt_MC_2 = (TGraphErrors*)f_2->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_2 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_2 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_2 -> SetMarkerColor(3); 

	TGraphErrors* g_ptOverGenpt_MC_3 = (TGraphErrors*)f_3->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_3 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_3 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_3 -> SetMarkerColor(4); 

	TGraphErrors* g_ptOverGenpt_MC_4 = (TGraphErrors*)f_4->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_4 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_4 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_4 -> SetMarkerColor(5); 

	TGraphErrors* g_ptOverGenpt_MC_5 = (TGraphErrors*)f_5->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_5 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_5 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_5 -> SetMarkerColor(6); 

	TGraphErrors* g_ptOverGenpt_MC_6 = (TGraphErrors*)f_6->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC_6 -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_6 -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_6 -> SetMarkerColor(7); 


	TCanvas* c_g_all = new TCanvas("g_all", "g_all",100,100,1000,600);

	TH1F *hPad = (TH1F*) gPad->DrawFrame(etaMin,ymin, etaMax,ymax);
	hPad->GetXaxis()->SetTitle("#eta_{SC}");
	hPad->GetYaxis()->SetTitle("p_{T}/p_{T}^{True}"); 

	TBox *box_1 = new TBox(-1.4616,ymin,-1.1484,ymax);
	box_1->SetFillColor(22);
	box_1->Draw();

	TBox *box_2 = new TBox(1.1484,ymin,1.4616,ymax);
	box_2->SetFillColor(22);
	box_2->Draw();

	TLegend *legend = new TLegend(0.37,0.60,0.78,0.88);
	legend ->SetFillColor(0); 
 	legend ->SetFillStyle(0); 
 	legend ->SetBorderSize(0);  
	legend ->AddEntry(g_ptOverGenpt_MC_0, "Original", "LP");
	legend ->AddEntry(g_ptOverGenpt_MC_1, "PixelBarrelConnToST", "LP");
	legend ->AddEntry(g_ptOverGenpt_MC_2, "PixelBarrelConn1_and_PixelBarrelConn2", "LP");
	legend ->AddEntry(g_ptOverGenpt_MC_3, "TIBFlange", "LP");
	legend ->AddEntry(g_ptOverGenpt_MC_4, "TIBTIDServiceCylinder", "LP");
	legend ->AddEntry(g_ptOverGenpt_MC_5, "TIBTIDMargherita", "LP");
	legend ->AddEntry(g_ptOverGenpt_MC_6, "Total effect", "LP");
	legend ->AddEntry(box_1, "ECAL 4^{th} module", "F");
	legend ->Draw();

	g_ptOverGenpt_MC_0 -> Draw("PL");
	g_ptOverGenpt_MC_1 -> Draw("PL same");
	g_ptOverGenpt_MC_2 -> Draw("PL same");
	g_ptOverGenpt_MC_3 -> Draw("PL same");
	g_ptOverGenpt_MC_4 -> Draw("PL same");
	g_ptOverGenpt_MC_5 -> Draw("PL same");
	g_ptOverGenpt_MC_6 -> Draw("PL same");

	c_g_all->SetGrid();

	outfile->cd();
	c_g_all->Write();
	c_g_all->SaveAs("all_draw_fit.png");

}

