
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

#ifndef __CINT__
#include "RooMyPdf_background_1.h"
#include "RooMyPdf_background_2.h"
#endif

using namespace RooFit;

TString floatToString(float number){
	ostringstream oss;
	oss << number;
	return oss.str();
}


void fit_background() {

	string folder = "2_results_2013_05_03/";
	char geo[10] = "barrel"; // "barrel", "endcaps" or "total"
	string pre_histo = "MC_BACK_template_";
	string histo = "SelectedPhotons_PfIso_1_bin01_";
	string inverted = "_inverted";

	stringstream ss_g;
	string Geo;
	ss_g << geo;
	ss_g >> Geo;
	string geo_s = Geo + "/";
	string out_files = "output_files/";
	string pdf_folder = "fit_pdf_plots/";
	string pdf_string = ".pdf";
	string root_folder = "fit_root_plots/";
	string root_string = ".root";
	stringstream ss_r;
	char root_char[10];
	ss_r << root_string;
	ss_r >> root_char;
	string fit = "fit_";
	string address = folder + geo_s + out_files + pre_histo + histo + inverted + root_string;


  TFile *f = new TFile(address.c_str());
  TH1F* h = (TH1F*)f->Get(histo.c_str());
	h->Rebin(2);


  RooRealVar x("x","photon PFIso", 0, 30);

  RooDataHist data("data","photon PFIso", x, h); 
  RooPlot* xframe = x.frame(RooFit::Name("xframe"), RooFit::Title("photon PFIso")) ;
  data.plotOn(xframe);

#ifdef __CINT__
  gROOT->ProcessLineSync(".X RooMyPdf_background_1.cxx++");
  gROOT->ProcessLineSync(".X RooMyPdf_background_2.cxx++") ;
#endif

  // Creat instance of RooMyPdf_background_1 class
	RooRealVar p3("p3","p3",0.,-10.,10.);
	RooRealVar p4("p4","p4",0.,-10.,10.);
	RooRealVar p5("p5","p5",0.,-10.,10.);
	RooRealVar p6("p6","p6",0.,-10.,10.);


  RooMyPdf_background_1 pdf1("pdf1","pdf1",x,p3,p4);
  RooMyPdf_background_2 pdf2("pdf2","pdf2",x,p4,p5,p6);

  // Define sampling frequency
  x.setBins(10000,"fft");
	RooFFTConvPdf conv("conv","pdf1 (X) pdf2", x, pdf1, pdf2);
//	RooNumConvPdf conv("conv","pdf1 (X) pdf2", x, pdf1, pdf2);
  
  
  p3.Print();
  p4.Print();
  p5.Print();
  p6.Print();
  
  RooFitResult* fitres = conv.fitTo(data,
	                                   RooFit::SumW2Error(kTRUE),
	                                   RooFit::Range(0.,30.),
																		 RooFit::Save(kTRUE)); 
	cout << "fitres = " << fitres << endl; 

	conv.plotOn (xframe,RooFit::LineColor(kBlue));	  
	conv.plotOn (xframe,RooFit::LineColor(kBlue),Components(pdf2),LineStyle(kDashed));
	conv.paramOn(xframe,RooFit::Layout(0.55,0.98,0.95));
	data.statOn (xframe,RooFit::Layout(0.55,0.98,0.65));

	double chi2;
	chi2  = xframe->chiSquare(4); // dof = 4 = number fof floating parametes
	cout << "chi2 = " << chi2;
	//cout << "***** CHI2 " << xframe->chiSquare(4) << endl; getchar();

	string s_cpull = "cpull";
	TCanvas *cpull = new TCanvas(s_cpull.c_str(),s_cpull.c_str(),600,600);
	cpull->SetFillColor(0);
	cpull->SetBorderMode(0);
	cpull->SetBorderSize(2);
	cpull->SetFrameBorderMode(0);
	cpull->SetFrameBorderMode(0);
	cpull->SetBottomMargin(0.25);
	TString chi2txt = "#chi^{2}=" + floatToString(xframe->chiSquare(3)) ; // dof = 3= number dof floating parametes
	TLatex* txt = new TLatex(0.65,0.38,chi2txt);
	txt->SetNDC();
	txt->SetTextSize(0.04) ;
	txt->SetTextColor(kRed) ;
	xframe->addObject(txt) ;
	xframe->GetXaxis()->SetTitle("photon PFIso");
	xframe->Draw();
	
	cpull->Update();
	
	cpull->SaveAs((folder + geo_s + pdf_folder + fit + histo + inverted + pdf_string).c_str());
	cpull->SaveAs((folder + geo_s + root_folder + fit + histo + inverted + root_string).c_str());
 
}
