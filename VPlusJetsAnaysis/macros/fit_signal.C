
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
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooClassFactory.h"
#include "RooFFTConvPdf.h"
#include "RooNumConvPdf.h"
#include "RooAddPdf.h"
#include "RooGaussModel.h"
#include "RooAddModel.h"
#include "RooDecay.h"

#ifndef __CINT__
#include "RooMyPdf_signal_1.h"
#include "RooMyPdf_signal_2.h"
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
//  myStyle->SetTitleYOffset(1.);

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


void fit_signal() {

	setMYStyle();

	string folder = "4_results_2013_05_10/";
	char geo[10] = "barrel"; // "barrel", "endcaps" or "total"
	bool inv = false; // inverted sigmaietaieta cut
		
	string sample = "MC_SIG"; // "MC_SIG", "MC_BACK" "DATA_INV" or "DATA"

	string histo = "SelectedPhotons_PfIso_1_bin01_";


	// ==================================== assign files names
	
	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string out_files = "output_files/";
	string fit_pdf_folder = "fit_pdf_plots/";
	string pdf_string = ".pdf";
	string fit_root_folder = "fit_root_plots/";
	string root_string = ".root";
	string inverted = "_inverted";
	string fit = "fit_";
	stringstream ss_r;
	char root_char[10];
	ss_r << root_string;
	ss_r >> root_char;
	
	string address = folder + geo_s + out_files;


	// ==================================== open now the input TFile

	string sample_mod = "";
	if (inv) sample_mod = sample + "_" + inverted + "_";
	else sample_mod = sample + "_";
	string templates = "template_";

	string infilename = (sample_mod + templates + histo + root_string).c_str();

  TFile *f = new TFile((address+infilename).c_str());
  TH1F* h = (TH1F*)f->Get(histo.c_str());
//	h->Rebin(2);

	// ==================================== driving function
	
	// Used to estimate the fit range
	TF1 *gtmp1 = 0;

	TCanvas *c_training1 = new TCanvas("c_training1","c_training1",600,600);
	c_training1->cd();
	c_training1->SetLogy();

	TH1F *h_1 = (TH1F*) h->Clone("h_1");
	h_1->GetYaxis()->SetTitleOffset(1.2);	
	h_1->Draw();

	// driving function
	gtmp1 = new TF1("gtmp1","[0]*exp(-0.5*((x-[1])/[2])**2)",0.,15.);

	gtmp1->SetParameters(1, 1, 10);	
	gtmp1-> Draw();
	gtmp1->SetLineColor(kRed);
	gtmp1->SetLineWidth(3);
	h_1->Fit("gtmp1","","",0.2,4.);     

	cout << endl;	       
	cout << "***** GTMP1 parameters *****" << endl; 
	cout << "gtmp1->GetParameter(0) = "<< gtmp1->GetParameter(0) << endl;
	cout << "gtmp1->GetParameter(1) = "<< gtmp1->GetParameter(1) << endl;
	cout << "gtmp1->GetParameter(2) = "<< gtmp1->GetParameter(2) << endl;
	cout << "***************************" << endl; 
	cout << endl;

	c_training1->Update();


	TF1 *gtmp2 = 0;

	TCanvas *c_training2 = new TCanvas("c_training2","c_training2",600,600);
	c_training2->cd();
	c_training2->SetLogy();
		
	TH1F *h_2 = (TH1F*) h->Clone("h_2");
	h_2->GetYaxis()->SetTitleOffset(1.2);		
	h_2->Draw();

	// driving function
	gtmp2 = new TF1("gtmp2","[0]*exp(-0.5*((x-[1])/[2])**2)",0.,15.);
	gtmp2->SetParameters(1., 1., 1.);	
	gtmp2-> Draw();
	gtmp2->SetLineColor(kRed);
	gtmp2->SetLineWidth(3);
	h_2->Fit("gtmp2","","",5.,11.);     

	cout << endl;	       
	cout << "***** GTMP2 parameters *****" << endl; 
	cout << "gtmp2->GetParameter(0) = "<< gtmp2->GetParameter(0) << endl;
	cout << "gtmp2->GetParameter(1) = "<< gtmp2->GetParameter(1) << endl;
	cout << "gtmp2->GetParameter(2) = "<< gtmp2->GetParameter(2) << endl;
	cout << "***************************" << endl; 
	cout << endl;

	c_training2->Update();


	TF1 *gtmp3 = 0;

	TCanvas *c_training3 = new TCanvas("c_training3","c_training3",600,600);
	c_training3->cd();
	c_training3->SetLogy();

	TH1F *h_3 = (TH1F*) h->Clone("h_3");
	h_3->GetYaxis()->SetTitleOffset(1.2);		
	h_3->Draw();

	gtmp3 = new TF1("gtmp3","[0]*exp(-x/[1])",0.,15.);

	gtmp3->SetParameters(1., 1.);	
	gtmp3-> Draw();
	gtmp3->SetLineColor(kRed);
	gtmp3->SetLineWidth(3);
	h_3->Fit("gtmp3","","",10.,14.);     

	cout << endl;	       
	cout << "***** GTMP3 parameters *****" << endl; 
	cout << "gtmp3->GetParameter(0) = "<< gtmp3->GetParameter(0) << endl;
	cout << "gtmp3->GetParameter(1) = "<< gtmp3->GetParameter(1) << endl;
	cout << "***************************" << endl; 
	cout << endl;

	c_training3->Update();


	// ==================================== fit signal

  RooRealVar x("x","photon PFIso", h->GetXaxis()->GetXmin(), 13.5); //h->GetXaxis()->GetXmax());

  RooDataHist data("data","photon PFIso", x, h); 
  RooPlot* xframe = x.frame(RooFit::Name("xframe"), RooFit::Title("photon PFIso"), RooFit::Range(0.,13.5)) ;

  data.plotOn(xframe);

#ifdef __CINT__
  gROOT->ProcessLineSync(".X RooMyPdf_signal_1.cxx++");
  gROOT->ProcessLineSync(".X RooMyPdf_signal_2.cxx++");
#endif

/*
	RooRealVar mean("mean","mean", gtmp1->GetParameter(1), 0., 1.);
	RooRealVar sigma_core("sigma_core","sigma core", gtmp1->GetParameter(2), 0., 10.);
	RooGaussModel gaussm_core("gaussm_core","core gauss", x, mean, sigma_core);

	RooRealVar sigma_tail("sigma_tail","sigma tail", gtmp2->GetParameter(2), 0., 10.);
	RooGaussModel gaussm_tail("gaussm_tail","tail gauss", x, mean, sigma_tail);

	RooRealVar frac_core("frac_core","core fraction",0.9, 0.8, 1.);
	RooAddModel gaussm("gaussm","core + tail gauss", RooArgList(gaussm_core, gaussm_tail), frac_core) ;

	RooRealVar tau("tau","lifetime", gtmp3->GetParameter(1), 0., 10.);
	RooDecay model("model","decay (x) gauss", x, tau, gaussm, RooDecay::SingleSided);
*/

	RooRealVar mean("mean","mean", 0.283721, 0.283721-1, 0.283721+1); //+/- 0.747948
	RooRealVar sigma_core("sigma_core","sigma core", 0.71567, 0.71567-0.8, 0.71567+0.8);// +/- 0.516118, 0., 10.);
	RooGaussModel gaussm_core("gaussm_core","core gauss", x, mean, sigma_core);

	RooRealVar sigma_tail("sigma_tail","sigma tail", 4.31749, 4.31749-0.001, 4.31749+0.001 );// +/- 0.000542988);
	RooGaussModel gaussm_tail("gaussm_tail","tail gauss", x, mean, sigma_tail);

	RooRealVar frac_core("frac_core","core fraction",0.864556, 0.864556-0.0001, 0.864556+0.0001);//+/- 7.03355e-05
	RooAddModel gaussm("gaussm","core + tail gauss", RooArgList(gaussm_core, gaussm_tail), frac_core) ;

	RooRealVar tau("tau","lifetime", 0.870602, 0.870602-0.0001, 0.870602+0.0001);// +/- 7.47083e-05);
	RooDecay model("model","decay (x) gauss", x, tau, gaussm, RooDecay::SingleSided);


  RooFitResult* fitres = model.fitTo(data,
	                                  RooFit::SumW2Error(kTRUE),
	                                  RooFit::Range(0.2,13.5),
	                                  RooFit::Save(kTRUE)); 

	cout << "fitres = " << fitres << endl; 

	model.plotOn (xframe,RooFit::LineColor(kBlue));	  
	model.paramOn(xframe,RooFit::Layout(0.55,0.98,0.95));

//	gaussm_core.plotOn (xframe,RooFit::LineColor(kOrange));
//	gaussm_tail.plotOn (xframe,RooFit::LineColor(kGreen));
//	gaussm.plotOn (xframe,RooFit::LineColor(kRed));
//	tau.plotOn (xframe,RooFit::LineColor(kViolet));

	data.statOn (xframe,RooFit::Layout(0.55,0.98,0.65));

	cout << endl;
	frac_core.Print();
  mean.Print();
  sigma_core.Print();
  sigma_tail.Print();
  tau.Print();
	cout << endl;

	double chi2;
	chi2  = xframe->chiSquare(5); // dof = 5 = number of floating parametes
	cout << endl;
	cout << "chi2 = " << chi2 << endl;
	cout << endl;	

	string s_canva_fit = "fit";
	TCanvas *canva_fit = new TCanvas(s_canva_fit.c_str(),s_canva_fit.c_str(),600,600);
 	canva_fit->SetLogy();
	
	TString chi2txt = "#chi^{2}/dof = " + floatToString(xframe->chiSquare(5)) ; // dof = 5 = number of floating parametes
	TLatex* txt = new TLatex(0.231,0.277,chi2txt);
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

	string title_X = h->GetXaxis()->GetTitle();
	xframe->GetXaxis()->SetTitle(title_X.c_str());
	xframe->Draw();
	

/*
	TF1 *gtmp1 = 0;
	gtmp1 = new TF1("gtmp1","1/[0] * exp(pow([2],2)/(2*pow([0],2))-((x-[1])/[0]))",0,15);
	gtmp1->SetParameter(0,gtmp->GetParameter(0));
	gtmp1->SetParameter(1,gtmp->GetParameter(1));
	gtmp1->SetParameter(2,gtmp->GetParameter(2));
	gtmp1->SetLineColor(kOrange);
	gtmp1->Draw("same");
	
	TF1 *gtmp2 = 0;
	gtmp2 = new TF1("gtmp2","1 - TMath::Freq([2]/[0] - (x-[1])/[2])",0.,15.0);
	gtmp2 = new TF1("gtmp2","1 -TMath::Freq(x)",0.,15.0);	
	gtmp2->SetParameter(0,gtmp->GetParameter(0));
	gtmp2->SetParameter(1,gtmp->GetParameter(1));
	gtmp2->SetParameter(2,gtmp->GetParameter(2));
	gtmp2->SetLineColor(kRed);
	gtmp2->Draw("same");

	TF1 *gtmp3 = 0;
	gtmp3 = new TF1("gtmp3","[0]*exp(-(x-[1])/[2])",0.,15.0);	
	gtmp3->SetParameter(0,1);
	gtmp3->SetParameter(1,1);
	gtmp3->SetParameter(2,1);
	gtmp3->SetLineColor(kRed);
	gtmp3->Draw("same");
*/

	canva_fit->Update();

	canva_fit->SaveAs((folder + geo_s + fit_pdf_folder + fit + sample_mod + histo + pdf_string).c_str());
	canva_fit->SaveAs((folder + geo_s + fit_root_folder + fit + sample_mod + histo + root_string).c_str());

}
