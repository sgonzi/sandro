
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
#include <TMath.h>
#include "TF1.h"
#include <TLatex.h>

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooClassFactory.h"
#include "RooFFTConvPdf.h"
#include "RooNumConvPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooGaussModel.h"
#include "RooAddModel.h"
#include "RooDecay.h"


#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "FWCore/Utilities/interface/Exception.h"
#endif

using namespace std;
using namespace RooFit;

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
	myStyle->SetOptFit(0);
	myStyle->SetFitFormat("5.4g");
	myStyle->SetFuncColor(2);
	myStyle->SetFuncStyle(1);
	myStyle->SetFuncWidth(1);

//For the date:
	myStyle->SetOptDate(0);

// For the statistics box:
	myStyle->SetOptFile(0);
	myStyle->SetOptStat(0); // To display the mean and RMS:	 SetOptStat("mr");
	myStyle->SetOptFit(0); // To display the mean and RMS:	 SetOptStat("mr");
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
//	myStyle->SetTitleYOffset(1.);

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


TString floatToString(float number){
	ostringstream oss;
	oss << number;
	return oss.str();
}


void fit_templates (const char* titleh, const char* bin_aa, const char* bin_bb, const char* namevariable, const int rebin, const double x_min, const double x_max){

	setMYStyle();

	// ==================================== choose the tools

	string folder_normal = "04_results_2013_10_25/"; // analysis folder 
	string folder_inverted = "05_results_2013_10_25/"; // analysis folder with inverted sigmaietaieta cut

	char geo[10] = "barrel";                 // "barrel", "endcaps" or "total"

	bool RandomCone = true;								 // Random cone
	bool inv_sigmaietaieta = true;           // inverted sigmaietaieta cut
	bool inv_isolation = false;              // inverted isolation set cut

	bool signal_MAD = true;                 // true: signal = MADGRAPH; false: signal = PYTHIA
	bool background_QCD = false;             // true: background = MADGRAPH not filtered (QCD HT)
	                                        // false: background = PYTHIA filtered (QCD EMEnriched + BCtoE); 
	
	string sample_MC_SIG = "MC_SIG"; // "MC_SIG", "MC_BACK", "DATA" and "MC_BACK_INV", "DATA_INV"
	string sample_MC_BACK = "MC_BACK";
	string sample_DATA = "DATA"; 
	string sample_MC_BACK_INV = "MC_BACK_INV"; 
	string sample_DATA_INV = "DATA_INV"; 

	string histo = titleh;
	string histoRC = "SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin"; 
	string histo_Templ_MC_SIG;
	if (!RandomCone) histo_Templ_MC_SIG = histo + bin_aa; 
	else histo_Templ_MC_SIG = histoRC + bin_aa;
	string histo_Templ_MC_BACK = histo + bin_bb;
	string histo_Templ_DATA = histo + bin_aa;
	string histo_Templ_MC_BACK_INV = histo + bin_bb;
	string histo_Templ_DATA_INV = histo + bin_bb;	

	// ==================================== assign files names
	
	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
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
	string fit_pdf_folder = "fit_pdf_plots/";
	string templates_folder = "templates/";	
	string pdf_string = ".pdf";
	string fit_root_folder = "fit_root_plots/";
	string root_string = ".root";
	string fit_txt_folder = "fit_txt_plots/";
	string txt_string = ".txt";
	string fit = "fit_";
	string shape = "shape_";
	
	
	stringstream ss_r;
	char root_char[10];
	ss_r << root_string;
	ss_r >> root_char;
	
	string address_normal = folder_normal + geo_s + SB_folder + templates_folder;
	string address_inverted = folder_inverted + geo_s  + SB_folder + templates_folder;


	// ==================================== exception controls
	
	if ((inv_sigmaietaieta && inv_isolation) || (!inv_sigmaietaieta && !inv_isolation)){
		cout << "ERROR: you need to invert SIGMAIETAIETA or ISOLATION cut" << endl << endl;
		throw cms::Exception("WrongBool");
	}
	if (!(Geo == "barrel" || Geo == "endcaps" || Geo == "total")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps)\" or \"total\". You wrote: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}	


	// ==================================== open now the input TFile


		string sample_MC_SIG_mod = sample_MC_SIG + "_";
		string sample_MC_BACK_mod = sample_MC_BACK + "_";		
		string sample_DATA_mod = sample_DATA + "_";
		string sample_MC_BACK_INV_mod = sample_MC_BACK_INV + "_";
		string sample_DATA_INV_mod;
	if (inv_sigmaietaieta && !inv_isolation){
		string sigmaietaieta_s = "_sigmaietaieta";
		sample_MC_BACK_INV_mod = sample_MC_BACK_INV + sigmaietaieta_s + "_";
		sample_DATA_INV_mod = sample_DATA_INV + sigmaietaieta_s + "_";
	}
	else if (inv_isolation && !inv_sigmaietaieta){
		string isolation_s = "_isolation";
		sample_MC_BACK_INV_mod = sample_MC_BACK_INV + isolation_s + "_";
		sample_DATA_INV_mod = sample_DATA_INV + isolation_s + "_";
	}
	else cout << "ERROR: you need to invert SIGMAIETAIETA or ISOLATION cut" << endl << endl;

	string templates = "template_";
	string infilename_MC_SIG = (sample_MC_SIG_mod + templates + histo_Templ_MC_SIG + root_string).c_str();
	string infilename_MC_BACK = (sample_MC_BACK_mod + templates + histo_Templ_MC_BACK + root_string).c_str();
	string infilename_DATA = (sample_DATA_mod + templates + histo_Templ_DATA + root_string).c_str();
	string infilename_MC_BACK_INV = (sample_MC_BACK_INV_mod + templates + histo_Templ_MC_BACK_INV + root_string).c_str();
	string infilename_DATA_INV = (sample_DATA_INV_mod + templates + histo_Templ_DATA_INV + root_string).c_str();

	TFile *f_MC_SIG = new TFile((address_normal + infilename_MC_SIG).c_str());
	TFile *f_MC_BACK = new TFile((address_normal + infilename_MC_BACK).c_str());
	TFile *f_DATA = new TFile((address_normal + infilename_DATA).c_str());
	TFile *f_MC_BACK_INV = new TFile((address_inverted + infilename_MC_BACK_INV).c_str());
	TFile *f_DATA_INV = new TFile((address_inverted + infilename_DATA_INV).c_str());

	TH1F* h_MC_SIG = (TH1F*)f_MC_SIG->Get(histo_Templ_MC_SIG.c_str());
	h_MC_SIG->Rebin(rebin);
	TH1F* h_MC_BACK = (TH1F*)f_MC_BACK->Get(histo_Templ_MC_BACK.c_str());
	h_MC_BACK->Rebin(rebin);
	TH1F* h_DATA = (TH1F*)f_DATA->Get(histo_Templ_DATA.c_str());
	h_DATA->Rebin(rebin);
	TH1F* h_MC_BACK_INV = (TH1F*)f_MC_BACK_INV->Get(histo_Templ_MC_BACK_INV.c_str());
	h_MC_BACK_INV->Rebin(rebin);	
	TH1F* h_DATA_INV = (TH1F*)f_DATA_INV->Get(histo_Templ_DATA_INV.c_str());
	h_DATA_INV->Rebin(rebin);


	TH1F* h_MC_BACK_scaled = (TH1F*)h_MC_BACK->Clone("h_MC_BACK_scaled");
	h_MC_BACK_scaled->Sumw2();
	h_MC_BACK_scaled->Scale(h_DATA_INV->Integral()/h_MC_BACK_scaled->Integral());
	TH1F* h_MC_BACK_INV_scaled = (TH1F*)h_MC_BACK_INV->Clone("h_MC_BACK_INV_scaled");
	h_MC_BACK_INV_scaled->Sumw2();
	h_MC_BACK_INV_scaled->Scale(h_DATA_INV->Integral()/h_MC_BACK_INV_scaled->Integral());
	TH1F* h_DATA_INV_scaled = (TH1F*)h_DATA_INV->Clone("h_DATA_INV_scaled");
	h_DATA_INV_scaled->Sumw2();

	TH1F *ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled = (TH1F*) h_DATA_INV_scaled->Clone("ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->Sumw2();
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->Divide(h_MC_BACK_scaled);

	TH1F *ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled = (TH1F*) h_DATA_INV_scaled->Clone("ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->Sumw2();
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->Divide(h_MC_BACK_INV_scaled);


	string s_canva_shape = "shape";
	TCanvas *canva_shape = new TCanvas(s_canva_shape.c_str(),s_canva_shape.c_str(),600,600);
	canva_shape->SetLogy();
	TPad* upperPad_shape = new TPad("upperPad_shape", "upperPad_shape",.005, .25, .995, .995);
  TPad* lowerPad_shape = new TPad("lowerPad_shape", "lowerPad_shape",.005, .005, .995, .2475);
  upperPad_shape->Draw(); 			       
  lowerPad_shape->Draw();

	int Nbins;
	double X_min, X_max;

	Nbins = h_MC_BACK_scaled->GetNbinsX();

	// upper Pad
  upperPad_shape->cd();

	if (x_min != -999 && x_max != -999){
		if (x_max == h_MC_BACK_scaled->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == h_MC_BACK_scaled->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		h_MC_BACK_scaled->GetXaxis()->SetRangeUser(X_min,X_max);
	}
	
	if (background_QCD) {
		h_MC_BACK_scaled->SetLineColor(kRed+2);	
//		h_MC_BACK_INV_scaled->SetLineColor(kRed+2);	
		h_MC_BACK_INV_scaled->SetLineColor(kViolet+2);	
	}
	else {
		h_MC_BACK_scaled->SetLineColor(kGreen+2);		
//		h_MC_BACK_INV_scaled->SetLineColor(kGreen+2);		
		h_MC_BACK_INV_scaled->SetLineColor(kViolet+2);				
	}
	h_MC_BACK_scaled->SetFillColor(0);
	h_MC_BACK_scaled->SetLineWidth(3);
	h_MC_BACK_scaled->Draw("histo");
	h_MC_BACK_INV_scaled->SetFillColor(0);
	h_MC_BACK_INV_scaled->SetLineWidth(3);
	h_MC_BACK_INV_scaled->SetLineStyle(2);	
	h_MC_BACK_INV_scaled->Draw("histo same");
	h_DATA_INV_scaled->SetMarkerSize(0.7);
	h_DATA_INV_scaled->Draw("ESAME");
	gPad->SetLogy();

	TLegend *leg =new TLegend(0.6068,0.6975,0.8188,0.8977);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	leg->AddEntry(h_MC_BACK_scaled,"MC background","l");
	leg->AddEntry(h_MC_BACK_INV_scaled,"#splitline{MC background}{(sidebands)}","l");
	leg->AddEntry(h_DATA_INV_scaled,"#splitline{Data}{(sidebands)}","pL");	
	leg->Draw();

	// lower Pad
	lowerPad_shape-> cd();

	float xbox_min,xbox_max;
	if (x_min == -999 && x_max == -999){
		xbox_min = h_MC_BACK_scaled->GetXaxis()->GetXmin();
		xbox_max = h_MC_BACK_scaled->GetXaxis()->GetXmax();
	}
	else {
		xbox_min = x_min;
		xbox_max = x_max;
	}	

	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->Draw("");
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
		if (x_max == h_MC_BACK_scaled->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == h_MC_BACK_scaled->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetXaxis()->SetRangeUser(X_min,X_max);
	}
	
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->Draw("P E0 SAME");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->Draw("P E0 SAME");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->Draw("AXIS X+ Y+ SAME");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->Draw("AXIS SAME");
  ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetXaxis()->SetTitle("");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetYaxis()->SetTitle("MC/DATA sidebands");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetYaxis()->SetTitleSize(0.10);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetYaxis()->SetTitleOffset(0.6);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetYaxis()->SetLabelSize(0.1);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetXaxis()->SetLabelSize(0.1);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetYaxis()->SetRangeUser(0.1,2);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->GetYaxis()->SetNdivisions(505, "kTRUE");
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->SetMarkerStyle(20);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->SetMarkerColor(kGreen+2);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->SetMarkerSize(0.7);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_scaled->SetLineColor(kGreen+2);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->SetMarkerStyle(20);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->SetMarkerColor(kViolet+2);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->SetMarkerSize(0.7);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->SetLineColor(kViolet+2);
	ratio_histo_DATA_INV_scaled_OV_MC_BACK_INV_scaled->SetLineStyle(2);

//	canva_shape->Update();

	string RandomCone_string = "RandomCone";	
	if (RandomCone){
	pdf_string = RandomCone_string + pdf_string;
	root_string = RandomCone_string + root_string;
	txt_string = RandomCone_string + txt_string;
	}
	else{
		pdf_string = pdf_string;
		root_string = root_string;
		txt_string = txt_string;
	}

	canva_shape->SaveAs((folder_normal + geo_s + SB_folder + fit_pdf_folder + shape + histo + bin_aa + bin_bb + pdf_string).c_str());
	canva_shape->SaveAs((folder_normal + geo_s + SB_folder + fit_root_folder + shape + histo + bin_aa + bin_bb + root_string).c_str());
	
	// ==================================== fit templates

	RooRealVar x("x", namevariable, x_min, x_max);

	RooDataHist RooDataHist_MC_SIG("RooDataHist_MC_SIG","MC signal histo", x, h_MC_SIG); 
	//RooDataHist RooDataHist_MC_BACK("RooDataHist_MC_BACK","MC background histo", x, h_MC_BACK); 
	RooDataHist RooDataHist_DATA("RooDataHist_DATA","DATA histo", x, h_DATA); 
	RooDataHist RooDataHist_DATA_INV("RooDataHist_DATA_INV", "DATA with an inverted cut histo", x, h_DATA_INV); 		

	RooHistPdf RooHistPdf_MC_SIG("RooHistPdf_MC_SIG","MC signal pdf", x, RooDataHist_MC_SIG);
	//RooHistPdf RooHistPdf_MC_BACK("RooHistPdf_MC_BACK","MC background pdf", x, RooDataHist_MC_BACK);
	RooHistPdf RooHistPdf_DATA("RooHistPdf_DATA","DATA pdf", x, RooDataHist_DATA);
	RooHistPdf RooHistPdf_DATA_INV("RooHistPdf_DATA_INV", "DATA with an inverted cut pdf", x, RooDataHist_DATA_INV);

	RooRealVar f("f","purity", 0.5, 0., 1.);
 
	// model(x) = f*RooHistPdf_MC_SIG(x) + (1-f)*RooHistPdf_DATA_INV(x)
 	RooAddPdf model("model", "MC signal and DATA with an inverted cut - Composite model with fraction", RooArgList(RooHistPdf_MC_SIG,RooHistPdf_DATA_INV), f);

	RooPlot* xframe = x.frame(RooFit::Name("xframe"), 
	                          RooFit::Title(namevariable), 
	                          RooFit::Range(x_min, x_max));

	RooDataHist_DATA.plotOn(xframe);

	RooFitResult* fitres = model.fitTo(RooDataHist_DATA,
	                                   RooFit::SumW2Error(kTRUE),
	                                   RooFit::Range(x_min,x_max),
	                                   RooFit::Save(kTRUE),
	                                   Minos(true)
	                                   ); 

	cout << "fitres = " << fitres << endl; 


	model.plotOn (xframe,RooFit::LineColor(kBlue),RooFit::MarkerSize(0.7));
	double chi2;
	chi2  = xframe->chiSquare(1); // dof = 1 = number of floating parametes
	cout << endl;
	cout << "chi2 = " << chi2 << endl;
	cout << endl;
	
	model.plotOn(xframe,Components("RooHistPdf_MC_SIG"),LineStyle(kDashed),LineColor(kGray+3)) ;
	model.plotOn(xframe,Components("RooHistPdf_DATA_INV"),LineStyle(kDashed),LineColor(kRed+2)) ;
		
//	model.paramOn(xframe,RooFit::Layout(0.55,0.98,0.95)); // box dati

//	RooDataHist_DATA.statOn (xframe,RooFit::Layout(0.55,0.98,0.65)); // box statistica

	cout << endl;
	f.Print();
	cout << endl;

	double F;
	F  = f.getVal();
	double ErrLo;
	ErrLo  = f.getAsymErrorLo();
	double ErrHi;
	ErrHi  = f.getAsymErrorHi();

	// ==================================== report

	cout << "Writing report file... " << endl;
	ofstream report;
	
	stringstream ss_t;
	char txt_char[200];
	ss_t << folder_normal + geo_s + SB_folder + fit_txt_folder + fit + histo + bin_aa + bin_bb + txt_string;
	ss_t >> txt_char;
	
	report.open(txt_char);
	
	report << "F = " << F << endl;

	report << "Error Low = " << ErrLo << endl;
	report << "Error High = " << ErrHi << endl;

	report << "chi2 = " << chi2 << endl;
		
	report << F << " & " << ErrLo << " & " << ErrHi << " & " << chi2 << " \\\\" <<endl;	
	report << endl;
	
	report.close();
	cout << "...writing report file finished. " << endl;

	// ==================================== finish report

	TH1F* h_MC_SIG_postFit = (TH1F*) h_MC_SIG->Clone("h_MC_SIG_postFit");
	h_MC_SIG_postFit->Scale(F*h_DATA->Integral()/h_MC_SIG->Integral());

	TH1F* h_DATA_INV_postFit = (TH1F*) h_DATA_INV->Clone("h_DATA_INV_postFit");
	h_DATA_INV_postFit->Scale((1-F)*h_DATA->Integral()/h_DATA_INV->Integral());

	h_MC_SIG_postFit->Add(h_DATA_INV_postFit);

	TH1F *ratio_histo_Data_fit = (TH1F*) h_DATA->Clone("ratio_histo_Data_fit");
	ratio_histo_Data_fit->Sumw2();
	ratio_histo_Data_fit->Divide(h_MC_SIG_postFit);

	
	string s_canva_fit = "fit";
	TCanvas *canva_fit = new TCanvas(s_canva_fit.c_str(),s_canva_fit.c_str(),600,600);
 	canva_fit->SetLogy();
	TPad* upperPad_fit = new TPad("upperPad_fit", "upperPad_fit",.005, .25, .995, .995);
  TPad* lowerPad_fit = new TPad("lowerPad_fit", "lowerPad_fit",.005, .005, .995, .2475);
  upperPad_fit->Draw(); 			       
  lowerPad_fit->Draw();

	// upper Pad
  upperPad_fit->cd();
	
//	TString chi2txt = "#chi^{2}/dof = " + floatToString(xframe->chiSquare(1)) ; // dof = 1 = number of floating parametes
	TString chi2txt = "#chi^{2}/dof = " + floatToString(chi2) ; // dof = 1 = number of floating parametes
	TLatex* txt = new TLatex(0.1638,0.8287,chi2txt);
	txt->SetNDC();
	txt->SetTextSize(0.04) ;
	txt->SetTextColor(kRed) ;
	xframe->addObject(txt) ;

	xframe->GetXaxis()->SetTitleFont(42);
	xframe->GetYaxis()->SetTitleFont(42);
	xframe->GetXaxis()->SetTitleSize(0.05);
	xframe->GetYaxis()->SetTitleSize(0.05);
	xframe->GetXaxis()->SetTitleOffset(1.1);
	xframe->GetYaxis()->SetTitleOffset(1.2);

	string title_X = h_DATA->GetXaxis()->GetTitle();
	xframe->GetXaxis()->SetTitle(title_X.c_str());
	xframe->Draw();
	gPad->SetLogy();


	TLegend *leg_fit =new TLegend(0.6746,0.6922,0.8457,0.8541);
	leg_fit->SetFillColor(0); 
  leg_fit->SetFillStyle(0); 
  leg_fit->SetBorderSize(0);
	leg_fit->AddEntry(h_DATA,"DATA","pL");	
  cout << "xframe objects:\n";
  for (int i=0; i<xframe->numItems(); i++) {
    TString obj_name=xframe->nameOf(i); if (obj_name=="") continue;
    cout << Form("%d. '%s'\n",i,obj_name.Data());}
  TString names[] = {"model_Norm[x]_Range[fit_nll_model_RooDataHist_DATA]_NormRange[fit_nll_model_RooDataHist_DATA]",
  									 "model_Norm[x]_Comp[RooHistPdf_MC_SIG]_Range[fit_nll_model_RooDataHist_DATA]_NormRange[fit_nll_model_RooDataHist_DATA]",
  									 "model_Norm[x]_Comp[RooHistPdf_DATA_INV]_Range[fit_nll_model_RooDataHist_DATA]_NormRange[fit_nll_model_RooDataHist_DATA]",
									   ""
									   };

  TString signs[] = {"Fit",
  									 "Signal",
  									 "Background"
  									 };
  									 
  Int_t i=-1;
  while ( names[++i] != "" ) {
    TObject *obj = xframe->findObject(names[i].Data());
    if (!obj) {
      Warning("fitBi4",Form("Can't find item='%s' in the xframe!\n",names[i].Data()));
      continue;
    }
    leg_fit->AddEntry(obj,signs[i],"l");
  }
	leg_fit->Draw();


	// lower Pad
  lowerPad_fit->cd();

	ratio_histo_Data_fit->Draw("");

	if (x_min == -999 && x_max == -999){
		xbox_min = h_MC_BACK_scaled->GetXaxis()->GetXmin();
		xbox_max = h_MC_BACK_scaled->GetXaxis()->GetXmax();
	}
	else {
		xbox_min = x_min;
		xbox_max = x_max;
	}	

	ratio_histo_Data_fit->Draw("");
	TBox *box_1_fit = new TBox(xbox_min,0.9,xbox_max,1.1);
	box_1_fit->SetFillColor(22);
	box_1_fit->Draw();

	TBox *box_2_fit = new TBox(xbox_min,0.95,xbox_max,1.05);
	box_2_fit->SetFillColor(14);
	box_2_fit->Draw();

  TLine *line_fit = new TLine(xbox_min,1,xbox_max,1);
  line_fit->SetLineColor(kBlack);
  line_fit->Draw();

	if (x_min != -999 && x_max != -999){
		if (x_max == h_MC_BACK_scaled->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == h_MC_BACK_scaled->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

	ratio_histo_Data_fit->GetXaxis()->SetRangeUser(X_min,X_max);
	h_DATA->GetXaxis()->SetRangeUser(X_min,X_max);
	h_MC_SIG_postFit->GetXaxis()->SetRangeUser(X_min,X_max);
	}


	ratio_histo_Data_fit->Draw("P E0 SAME");
	ratio_histo_Data_fit->Draw("AXIS X+ Y+ SAME");
	ratio_histo_Data_fit->Draw("AXIS SAME");
  ratio_histo_Data_fit->GetXaxis()->SetTitle("");
	ratio_histo_Data_fit->GetYaxis()->SetTitle("DATA/fit");
	ratio_histo_Data_fit->GetYaxis()->SetTitleSize(0.10);
	ratio_histo_Data_fit->GetYaxis()->SetTitleOffset(0.6);
	ratio_histo_Data_fit->GetYaxis()->SetLabelSize(0.1);
	ratio_histo_Data_fit->GetXaxis()->SetLabelSize(0.1);
	ratio_histo_Data_fit->GetYaxis()->SetRangeUser(0.1,2.);
	ratio_histo_Data_fit->GetYaxis()->SetNdivisions(505, "kTRUE");
	ratio_histo_Data_fit->SetMarkerStyle(20);
	ratio_histo_Data_fit->SetMarkerColor(kBlack);
	ratio_histo_Data_fit->SetMarkerSize(0.7);
	ratio_histo_Data_fit->SetLineColor(kBlack);

	
//	canva_fit->Update();

	canva_fit->SaveAs((folder_normal + geo_s + SB_folder + fit_pdf_folder + fit +  histo + bin_aa + bin_bb + pdf_string).c_str());
	canva_fit->SaveAs((folder_normal + geo_s + SB_folder + fit_root_folder + fit + histo + bin_aa + bin_bb + root_string).c_str());


}

void fit_templates_id_sieie_20binPt() {
	fit_templates("SelectedPhotons_id_sieie_1_bin", "01_", "01_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "02_", "02_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "03_", "03_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "04_", "04_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "05_", "05_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "06_", "06_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "07_", "07_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "08_", "08_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "09_", "09_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "10_", "10_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "11_", "11_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "12_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "13_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "14_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "15_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "16_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "17_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "18_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);	
	fit_templates("SelectedPhotons_id_sieie_1_bin", "19_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "20_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
	fit_templates("SelectedPhotons_id_sieie_1_bin", "21_", "27_big_", "#sigma_{i#etai#eta}^{#gamma_{1}}", 1, 0, 0.012);
}

void fit_templates_PfIso_RhoCorr_20binPt() {
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "01_", "01_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "02_", "02_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 13.3);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "03_", "03_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "04_", "04_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "05_", "05_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "06_", "06_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "07_", "07_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "08_", "08_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "09_", "09_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "10_", "10_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "11_", "11_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "12_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "13_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "14_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "15_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "16_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "17_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "18_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);	
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "19_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "20_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin", "21_", "27_big_", "Iso^{#gamma_{1} #rho_{corr}} [GeV/#font[12]{c}]", 1, 0, 30);
}


void fit_templates_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_20binPt() {
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "01_", "01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "02_", "02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "03_", "03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "04_", "04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "05_", "05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "06_", "06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "07_", "07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "08_", "08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "09_", "09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "10_", "10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "11_", "11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "12_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "13_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "14_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "15_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "16_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "17_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "18_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "19_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "20_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin", "21_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho} [GeV/#font[12]{c}]", 2, -10, 10);
}


void fit_templates_PfIso_RhoCorr_forFit_20binPt() {
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "01_", "01_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 9);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "02_", "02_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 13);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "03_", "03_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 13);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "04_", "04_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 16);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "05_", "05_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 18);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "06_", "06_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 19);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "07_", "07_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 21);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "08_", "08_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 22);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "09_", "09_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 22);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "10_", "10_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 24);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "11_", "11_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 25);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "12_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 24);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "13_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 25);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "14_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 15);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "15_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 18);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "16_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 15);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "17_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 10);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "18_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 17);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "19_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 2, -8, 18);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "20_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 26);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin", "21_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}} [GeV/#font[12]{c}]", 1, -8, 26);
}


void fit_templates_IsoFPRPhoton_RhoCorr_forFit_20binPt() {
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "01_", "01_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "02_", "02_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "03_", "03_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "04_", "04_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "05_", "05_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 7.5);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "06_", "06_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "07_", "07_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "08_", "08_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "09_", "09_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "10_", "10_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "11_", "11_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "12_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "13_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "14_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "15_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "16_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "17_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "18_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "19_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "20_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
	fit_templates("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin", "21_", "27_big_", "Iso^{#gamma_{1} fit-#rho_{corr}}_{Pho-FPR} [GeV/#font[12]{c}]", 2, -10, 10);
}

