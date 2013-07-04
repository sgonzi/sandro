
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


void fit_templates (const char* titleh, const int rebin, const double x_min, const double x_max){

	setMYStyle();

	// ==================================== choose the tools

	string folder_normal = "6_results_2013_06_25/"; // analysis folder 
	string folder_inverted = "7_results_2013_06_25/"; // analysis folder with inverted sigmaietaieta cut

	char geo[10] = "barrel";                 // "barrel", "endcaps" or "total"

	bool inv_sigmaietaieta = true;          // inverted sigmaietaieta cut
	bool inv_isolation = false;              // inverted isolation set cut
	
	string sample_MC_SIG = "MC_SIG"; // "MC_SIG", "MC_BACK", "DATA" or "DATA_INV"
	string sample_MC_BACK = "MC_BACK"; // "MC_SIG", "MC_BACK", "DATA" or "DATA_INV"
	string sample_DATA = "DATA"; // "MC_SIG", "MC_BACK", "DATA" or "DATA_INV"
	string sample_DATA_INV = "DATA_INV"; // "MC_SIG", "MC_BACK", "DATA" or "DATA_INV"

	string histo = titleh; 


	// ==================================== assign files names
	
	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
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
	string pdf_string = ".pdf";
	string fit_root_folder = "fit_root_plots/";
	string root_string = ".root";
	string fit = "fit_";
	string shape = "shape_";	
	stringstream ss_r;
	char root_char[10];
	ss_r << root_string;
	ss_r >> root_char;
	
	string address_normal = folder_normal + geo_s + out_files;
	string address_inverted = folder_inverted + geo_s + out_files;


	// ==================================== exception controls
	
	if ((inv_sigmaietaieta && inv_isolation) || (!inv_sigmaietaieta && !inv_isolation)){
		cout << "ERROR: you need to invert SIGMAIETAIETA or ISOLATION cut" << endl << endl;
		throw cms::Exception("WrongBool");
	}
	if (!(Geo == "barrel" || Geo == "endcaps" || Geo == "total")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps)\" or \"total\". You writed: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}	


	// ==================================== open now the input TFile


		string sample_MC_SIG_mod = sample_MC_SIG + "_";
		string sample_MC_BACK_mod = sample_MC_BACK + "_";		
		string sample_DATA_mod = sample_DATA + "_";
		string sample_DATA_INV_mod;
	if (inv_sigmaietaieta && !inv_isolation){
		string sigmaietaieta_s = "_sigmaietaieta";
		sample_DATA_INV_mod = sample_DATA_INV + sigmaietaieta_s + "_";
	}
	else if (inv_isolation && !inv_sigmaietaieta){
		string isolation_s = "_isolation";
		sample_DATA_INV_mod = sample_DATA_INV + isolation_s + "_";
	}
	else cout << "ERROR: you need to invert SIGMAIETAIETA or ISOLATION cut" << endl << endl;

	string templates = "template_";
	string infilename_MC_SIG = (sample_MC_SIG_mod + templates + histo + root_string).c_str();
	string infilename_MC_BACK = (sample_MC_BACK_mod + templates + histo + root_string).c_str();
	string infilename_DATA = (sample_DATA_mod + templates + histo + root_string).c_str();
	string infilename_DATA_INV = (sample_DATA_INV_mod + templates + histo + root_string).c_str();

	TFile *f_MC_SIG = new TFile((address_normal + infilename_MC_SIG).c_str());
	TFile *f_MC_BACK = new TFile((address_normal + infilename_MC_BACK).c_str());
	TFile *f_DATA = new TFile((address_normal + infilename_DATA).c_str());
	TFile *f_DATA_INV = new TFile((address_inverted + infilename_DATA_INV).c_str());

	TH1F* h_MC_SIG = (TH1F*)f_MC_SIG->Get(histo.c_str());
	h_MC_SIG->Rebin(rebin);
	TH1F* h_MC_BACK = (TH1F*)f_MC_BACK->Get(histo.c_str());
	h_MC_BACK->Rebin(rebin);
	TH1F* h_DATA = (TH1F*)f_DATA->Get(histo.c_str());
	h_DATA->Rebin(rebin);
	TH1F* h_DATA_INV = (TH1F*)f_DATA_INV->Get(histo.c_str());
	h_DATA_INV->Rebin(rebin);

	string s_canva_shape = "shape";
	TCanvas *canva_shape = new TCanvas(s_canva_shape.c_str(),s_canva_shape.c_str(),600,600);
	canva_shape->SetLogy();

	int Nbins;
	double X_min, X_max;

	Nbins = h_MC_BACK->GetNbinsX();

	if (x_min != -999 && x_max != -999){
		if (x_max == h_MC_BACK->GetXaxis()->GetXmax()) X_max = x_max;
		else X_max = x_max - (x_max-x_min)/Nbins;
		if (x_min == h_MC_BACK->GetXaxis()->GetXmin()) X_min = x_min;
		else X_min = x_min + (x_max-x_min)/Nbins;

		h_MC_BACK->GetXaxis()->SetRangeUser(X_min,X_max);
	}
	
	h_MC_BACK->Draw("histo");
	h_DATA_INV->Draw("ESAME");

	TLegend *leg =new TLegend(0.6068,0.5478,0.8188,0.7480);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	leg->AddEntry(h_MC_BACK,"MC background","f");
	leg->AddEntry(h_MC_BACK,"DATA (inverted cut)","pL");	
	leg->Draw();

	canva_shape->Update();

	canva_shape->SaveAs((folder_normal + geo_s + fit_pdf_folder + shape +  histo + pdf_string).c_str());
	canva_shape->SaveAs((folder_normal + geo_s + fit_root_folder + shape + histo + root_string).c_str());
	
	// ==================================== fit templates

	RooRealVar x("x","PfIsoPhoton #rho corrected", x_min, x_max);

	RooDataHist RooDataHist_MC_SIG("RooDataHist_MC_SIG","MC signal histo", x, h_MC_SIG); 
	RooDataHist RooDataHist_MC_BACK("RooDataHist_MC_BACK","MC background histo", x, h_MC_BACK); 
	RooDataHist RooDataHist_DATA("RooDataHist_DATA","DATA histo", x, h_DATA); 
	RooDataHist RooDataHist_DATA_INV("RooDataHist_DATA_INV", "DATA with an inverted cut histo", x, h_DATA_INV); 		

	RooHistPdf RooHistPdf_MC_SIG("RooHistPdf_MC_SIG","MC signal pdf", x, RooDataHist_MC_SIG);
	RooHistPdf RooHistPdf_MC_BACK("RooHistPdf_MC_BACK","MC background pdf", x, RooDataHist_MC_BACK);
	RooHistPdf RooHistPdf_DATA("RooHistPdf_DATA","DATA pdf", x, RooDataHist_DATA);
	RooHistPdf RooHistPdf_DATA_INV("RooHistPdf_DATA_INV", "DATA with an inverted cut pdf", x, RooDataHist_DATA_INV);

	RooRealVar f("f","purity", 0.9, 0.9, 1.);
cout << "pispolo" << endl; 
	// model(x) = f*RooHistPdf_MC_SIG(x) + (1-f)*RooHistPdf_DATA_INV(x)
 	RooAddPdf model("model", "MC signal and DATA with an inverted cut - Composite model with fraction", RooArgList(RooHistPdf_MC_SIG,RooHistPdf_DATA_INV), f);

	RooPlot* xframe = x.frame(RooFit::Name("xframe"), 
	                          RooFit::Title("PfIsoPhoton #rho corrected"), 
	                          RooFit::Range(x_min, x_max));

	RooDataHist_DATA.plotOn(xframe);

	RooFitResult* fitres = model.fitTo(RooDataHist_DATA,
	                                   RooFit::SumW2Error(kTRUE),
	                                   RooFit::Range(x_min,x_max),
	                                   RooFit::Save(kTRUE)); 

	cout << "fitres = " << fitres << endl; 

	model.plotOn (xframe,RooFit::LineColor(kBlue));
	model.paramOn(xframe,RooFit::Layout(0.55,0.98,0.95));

	RooDataHist_DATA.statOn (xframe,RooFit::Layout(0.55,0.98,0.65));

	cout << endl;
	f.Print();
	cout << endl;

	double chi2;
	chi2  = xframe->chiSquare(1); // dof = 1 = number of floating parametes
	cout << endl;
	cout << "chi2 = " << chi2 << endl;
	cout << endl;	

	string s_canva_fit = "fit";
	TCanvas *canva_fit = new TCanvas(s_canva_fit.c_str(),s_canva_fit.c_str(),600,600);
 	canva_fit->SetLogy();
	
	TString chi2txt = "#chi^{2}/dof = " + floatToString(xframe->chiSquare(1)) ; // dof = 1 = number of floating parametes
	TLatex* txt = new TLatex(0.1695,0.1766,chi2txt);
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
	
	canva_fit->Update();

	canva_fit->SaveAs((folder_normal + geo_s + SB_folder + fit_pdf_folder + fit +  histo + pdf_string).c_str());
	canva_fit->SaveAs((folder_normal + geo_s + SB_folder + fit_root_folder + fit + histo + root_string).c_str());

}


void fit_templates_PfIso_RhoCorrected_6binPt() {
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin01_", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin02_", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin03_", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin04_", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin05_", 1, 0, 20);
	fit_templates("SelectedPhotons_PfIso_RhoCorr_1_bin06_", 1, 0, 20);
}

