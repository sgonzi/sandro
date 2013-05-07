
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
#include "RooMyPdf_signal_1.h"
#include "RooMyPdf_signal_2.h"
#endif

using namespace RooFit;

TString floatToString(float number){
	ostringstream oss;
	oss << number;
	return oss.str();
}


void fit_signal() {


	string folder = "1_results_2013_05_02/";
	char geo[10] = "barrel"; // "barrel", "endcaps" or "total"
	string pre_histo = "MC_SIG_template_";
	string histo = "SelectedPhotons_PfIso_1_bin02_";

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
	string address = folder + geo_s + out_files + pre_histo + histo + root_string;


  TFile *f = new TFile(address.c_str());
  TH1F* h = (TH1F*)f->Get(histo.c_str());
	h->Rebin(2);

	
	// driving gaussian. Used to estimate the fit range
	TF1 *gtmp = 0;

	TCanvas *c_gaus_training = new TCanvas("c_gaus_training","c_gaus_training",600,600);
	c_gaus_training->cd();
	//gPad->SetLogy();
	h->Draw();

	// more solid peak position with a temporary histogram filled only with the bins above 50% of the peak max
	TH1F *htmp = new TH1F("htmp","htmp", 100, 0, 30);
cout << "h->GetNbinsX() = " << h->GetNbinsX() << endl;
	if (h->GetMaximum()< h->GetMaximum()/2.) { h->Rebin(2); htmp->Rebin(2); }
	for (Int_t i=0; i<h->GetNbinsX(); ++i) {
		if (h->GetBinContent(i) > h->GetMaximum()/2.) htmp->SetBinContent(i,h->GetBinContent(i));
	}
	htmp->Draw();
	c_gaus_training->Update();
	
	// driving gaussian
	gtmp = new TF1("gtmp","gaus(0)",0,30.0);	
	// use the mean and RMS of the Erec/Egen as initial parameters for the driving gaussian
	// gtmp->SetParameters(10,1,0.05);
	cout << "h->GetMaximum() = " << h->GetMaximum() << endl;
	cout << "h->GetMean() = " << h->GetMean() << endl;
	cout << "h->GetRMS() = " << h->GetRMS() << endl;
	cout << "htmp->GetMaximum() = " << htmp->GetMaximum() << endl;
	cout << "htmp->GetMean() = " << htmp->GetMean() << endl;
	cout << "htmp->GetRMS() = " << htmp->GetRMS() << endl;
	gtmp->SetParameters(htmp->GetMaximum(), htmp->GetMean(), htmp->GetRMS());
	gtmp-> Draw();
//	h->Fit("gtmp","","",0,htmp->GetMean()+5*htmp->GetRMS()); // 0.8,1.1);
//	h->Fit("gtmp","","",
//	       gtmp->GetParameter(1)-2*TMath::Abs(gtmp->GetParameter(2)),
//	       gtmp->GetParameter(1)+2*TMath::Abs(gtmp->GetParameter(2)));
	h->Fit("gtmp","","",0,htmp->GetMean()+10*htmp->GetRMS()); 	       
	       
	cout << "***** GTMP parameters *****" << endl; 
	cout << "gtmp->GetParameter(0) = "<< gtmp->GetParameter(0) << endl;
	cout << "gtmp->GetParameter(1) = "<< gtmp->GetParameter(1) << endl;
	cout << "gtmp->GetParameter(2) = "<< gtmp->GetParameter(2) << endl;

	c_gaus_training->Update();

	delete htmp;



  RooRealVar x("x","photon PFIso", 0, 30);

  RooDataHist data("data","photon PFIso", x, h); 
  RooPlot* xframe = x.frame(RooFit::Name("xframe"), RooFit::Title("photon PFIso")) ;
  data.plotOn(xframe);

#ifdef __CINT__
  gROOT->ProcessLineSync(".X RooMyPdf_signal_1.cxx++");
  gROOT->ProcessLineSync(".X RooMyPdf_signal_2.cxx++") ;
#endif

  // Creat instance of RooMyPdf_signal_1 class
	RooRealVar p0("p0","p0",0., -10., -10.);
	RooRealVar p1("p1","p1",0.,-10.,10.);
	RooRealVar p2("p2","p2",0.,-10.,10.);

  RooMyPdf_signal_1 pdf1("pdf1","pdf1",x,p0,p1,p2);
  RooMyPdf_signal_2 pdf2("pdf2","pdf2",x,p0,p1,p2);

  // Define sampling frequency
  x.setBins(10000,"fft");
	RooFFTConvPdf conv("conv","pdf1 (X) pdf2", x, pdf1, pdf2);
//	RooNumConvPdf conv("conv","pdf1 (X) pdf2", x, pdf1, pdf2);
  
  
  p0.Print();
  p1.Print();
  p2.Print();

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
	chi2  = xframe->chiSquare(3); // dof = 3 = number fof floating parametes
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
	
	/*
	TF1 *gtmp1 = 0;
	gtmp1 = new TF1("gtmp1","1/[0] * exp(pow([2],2)/(2*pow([0],2))-((x-[1])/[0]))",0,30.0);
	gtmp1->SetParameter(0,1.73269);
	gtmp1->SetParameter(1,-10);
	gtmp1->SetParameter(2,-10);
	gtmp1->SetLineColor(kOrange);
	gtmp1->Draw("same");
*/

	cpull->Update();

	cpull->SaveAs((folder + geo_s + pdf_folder + fit + histo + pdf_string).c_str());
	cpull->SaveAs((folder + geo_s + root_folder + fit + histo + root_string).c_str());
 
}
