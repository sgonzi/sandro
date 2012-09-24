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


void Draw_fit(){

	setTDRStyle();

	float etaMin = -1.7;
	float etaMax = 1.7;
	float ymin   = 0.6;
	float ymax   = 1.2;

	TFile *f = TFile::Open("fit_6_Geometries_12345_MC.root");

	TFile *outfile = new TFile("draw_fit_6_Geometries_12345_MC.root","recreate");

	TGraphErrors* g_ptOverGenpt_MC = (TGraphErrors*)f->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC -> SetLineColor(7); 
	g_ptOverGenpt_MC -> SetMarkerStyle(21);
	g_ptOverGenpt_MC -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC -> SetMarkerColor(7); 

	TCanvas* c_g_fit = new TCanvas("g_fit", "g_fit",100,100,1000,600);

	TH1F *hPad = (TH1F*) gPad->DrawFrame(etaMin,ymin, etaMax,ymax);
	hPad->GetXaxis()->SetTitle("#eta_{SC}");
	hPad->GetYaxis()->SetTitle("p_{T}/p_{T}^{True}"); 

	TPaveText *Titolo = new TPaveText(0,0,0.39,0.06,"NDC");
	Titolo ->SetTextAlign(11);
	Titolo ->SetFillColor(0);
	Titolo ->SetBorderSize(0);
	Titolo ->AddText(Form("Total effect"));
   	Titolo ->Draw();

	TBox *box_1 = new TBox(-1.4616,ymin,-1.1484,ymax);
	box_1->SetFillColor(22);
	box_1->Draw();

	TBox *box_2 = new TBox(1.1484,ymin,1.4616,ymax);
	box_2->SetFillColor(22);
	box_2->Draw();

	TLegend *legend = new TLegend(0.37,0.76,0.78,0.88);
	legend ->SetFillColor(0); 
 	legend ->SetFillStyle(0); 
 	legend ->SetBorderSize(0);  
	legend ->AddEntry(g_ptOverGenpt_MC, "Total effect", "LP");
	legend ->AddEntry(box_1, "ECAL 4^{th} module", "F");
	legend ->Draw();

	g_ptOverGenpt_MC -> Draw("PL");
	g_ptOverGenpt_MC -> Write("g_ptOverGenpt_MC");

	c_g_fit->SetGrid();

	c_g_fit->Write();
	c_g_fit->SaveAs("draw_fit_6_Geometries_12345_MC.png");


//-------------

	string Original_pwd = "/raid/sandro/Geometria/Tracker_ECAL/0_Original/CMSSW_5_2_5/src/DumpNt/DumpNt/test/";
	string Original = "fit_0_Original_MC.root";

	TFile *f_Original = TFile::Open((Original_pwd+Original).c_str());

	TGraphErrors* g_ptOverGenpt_MC_Original = (TGraphErrors*)f_Original->Get("g_ptOverGenpt_MC");
	g_ptOverGenpt_MC -> SetLineColor(1); 
	g_ptOverGenpt_MC_Original -> SetMarkerStyle(21);
	g_ptOverGenpt_MC_Original -> SetMarkerSize(0.7);
	g_ptOverGenpt_MC_Original -> SetMarkerColor(1); 

	TCanvas* c_g_fit_Original = new TCanvas("g_fit_Original", "g_fit_Original",100,100,1000,600);

	TH1F *hPad_Original = (TH1F*) gPad->DrawFrame(etaMin,ymin, etaMax,ymax);
	hPad_Original->GetXaxis()->SetTitle("#eta_{SC}");
	hPad_Original->GetYaxis()->SetTitle("p_{T}/p_{T}^{True}"); 

	TPaveText *Titolo_Original = new TPaveText(0,0,0.39,0.06,"NDC");
	Titolo_Original ->SetTextAlign(11);
	Titolo_Original ->SetFillColor(0);
	Titolo_Original ->SetBorderSize(0);
	Titolo_Original ->AddText(Form("Original"));
   	Titolo_Original ->Draw();

	TBox *box_1_Original = new TBox(-1.4616,ymin,-1.1484,ymax);
	box_1_Original->SetFillColor(22);
	box_1_Original->Draw();

	TBox *box_2_Original = new TBox(1.1484,ymin,1.4616,ymax);
	box_2_Original->SetFillColor(22);
	box_2_Original->Draw();

	TLegend *legend_Original = new TLegend(0.37,0.76,0.78,0.88);
	legend_Original ->SetFillColor(0); 
 	legend_Original ->SetFillStyle(0); 
 	legend_Original ->SetBorderSize(0);  
	legend_Original ->AddEntry(g_ptOverGenpt_MC_Original, "Original", "LP");
	legend_Original ->AddEntry(box_1, "ECAL 4^{th} module", "F");
	legend_Original ->Draw();


	g_ptOverGenpt_MC_Original -> Draw("PL");
	outfile->cd();
	g_ptOverGenpt_MC_Original -> Write("g_ptOverGenpt_MC_Original");

	c_g_fit_Original->SetGrid();


	c_g_fit_Original->Write();
	c_g_fit_Original->SaveAs("draw_fit_Original_MC.png");

//-------------

	TCanvas* c_g_fit_double = new TCanvas("g_fit_double", "g_fit_double",100,100,1000,600);

	TH1F *hPad_double = (TH1F*) gPad->DrawFrame(etaMin,ymin, etaMax,ymax);
	hPad_double->GetXaxis()->SetTitle("#eta_{SC}");
	hPad_double->GetYaxis()->SetTitle("p_{T}/p_{T}^{True}"); 

	TBox *box_1_double = new TBox(-1.4616,ymin,-1.1484,ymax);
	box_1_double->SetFillColor(22);
	box_1_double->Draw();

	TBox *box_2_double = new TBox(1.1484,ymin,1.4616,ymax);
	box_2_double->SetFillColor(22);
	box_2_double->Draw();

	g_ptOverGenpt_MC_Original -> Draw("PL");
	g_ptOverGenpt_MC -> Draw("PL same");

	TLegend *legend_double = new TLegend(0.37,0.76,0.78,0.88);
	legend_double->SetFillColor(0); 
 	legend_double->SetFillStyle(0); 
 	legend_double->SetBorderSize(0);  
	legend_double->AddEntry(g_ptOverGenpt_MC_Original, "Original", "LP");
	legend_double->AddEntry(g_ptOverGenpt_MC, "Total effect", "LP");
	legend_double->AddEntry(box_1_double, "ECAL 4^{th} module", "F");
	legend_double->Draw();

	c_g_fit_double->SetGrid();

	outfile->cd();
	c_g_fit_double->Write();
	c_g_fit_double->SaveAs("draw_fit_double_MC.png");

}

