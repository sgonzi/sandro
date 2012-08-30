/*
from
http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/donega/ECAL/SC/scCorrections/scCorrections.C?revision=1.10&view=markup
/////
.x loadRoofit.C
.L fit.C++
fit();
/////
*/

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
#include "TAxis.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <algorithm>
#include <math.h>
#include <vector>

//Mauro->Inizio
//#define scCorrections_cxx
//#include "scCorrections.h"
//#include "Utils.C"
//#include <iostream>
#include <fstream>
//#include <sstream>
//#include "TROOT.h"
//#include <TF1.h>
//#include <TH1.h>
//#include <TH2.h>
//#include <TH3.h>
#include "TMath.h"
//#include <TStyle.h>
//#include <TProfile.h>
//#include <TCanvas.h>
//#include <TLegend.h>
#include <TLatex.h>
//#include <TBox.h>
//#include "TFile.h"
#include "TString.h"

#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooPlot.h"
//#include "binning.h"
//Mauro->Fine

//using namespace std;

//Mauro->Inizio
//using namespace RooFit;
//Mauro->Fine

//const int bin = 95;
const int bin = 190;

const float c = -1.653;
//const float d = 0.0348;
const float d = 0.0174;

int nBinsErecEgen = 250;
int ErecEgenMin = 0; 
int ErecEgenMax = 2;

int EtaBins(float eta, float a, float b){

	int z = bin;
	if (eta <= a+0*b)                              {return 0;}

	for(int x = 1; x < (z+1); ++x){
		if (eta > a+(x-1)*b && eta <= a+x*b)   {return x;}
	}

	if (eta > a+z*b)                             {return z+1;} 

	return -1;
}

TString floatToString(float number){
	ostringstream oss;
	oss << number;
	return oss.str();
}

string intToString(int number){
	std::string st;
	std::stringstream out;
	out << number;
	return st = out.str();
}


void fitCB(TH1F *h, Double_t &mean, Double_t &emean, Double_t &chi2, string &stringa)
{
	// This is to quantify the fraction of events where the reconstructed energy is below EgenFrac
	// badReco = h->Integral(1,h->FindBin(EgenFrac)) / (Double_t)h->GetEntries();

	// driving gaussian. Used to estimate the fit range
	TF1 *gtmp = 0;

	TCanvas *c1 = new TCanvas("c1","c1",600,600);
	c1->cd();
	h->Draw();

	// more solid peak position with a temporary histogram filled only with the bins above 50% of the peak max
	TH1F *htmp = new TH1F("htmp","htmp",nBinsErecEgen,ErecEgenMin, ErecEgenMax);
	// protect the fits from small statistics rebinning
	if (h->GetMaximum()< 50.) { h->Rebin(2); htmp->Rebin(2); }
	if (h->GetMaximum()< 25.) { h->Rebin(2); htmp->Rebin(2); }
	for (Int_t i=0; i<h->GetNbinsX(); ++i) {
		if (h->GetBinContent(i) > h->GetMaximum()/2.) htmp->SetBinContent(i,h->GetBinContent(i));
	}
	htmp->Draw();
	c1->Update();

	
	// driving gaussian
	gtmp = new TF1("gtmp","gaus(0)",0,2.0);	
	// use the mean and RMS of the Erec/Egen as initial parameters for the driving gaussian
	// gtmp->SetParameters(10,1,0.05);
	cout << h->GetMaximum() << " " 
	     << h->GetMean() << " " 
	     << h->GetRMS() << " " 
	     << htmp->GetMean() << " " 
	     << htmp->GetRMS() << " " 
	     << endl;
	gtmp->SetParameters(10, htmp->GetMean(), htmp->GetRMS());
	h->Fit("gtmp","","",htmp->GetMean()-5*htmp->GetRMS(),htmp->GetMean()+5*htmp->GetRMS()); // 0.8,1.1);
	h->Fit("gtmp","","",
	       gtmp->GetParameter(1)-2*TMath::Abs(gtmp->GetParameter(2)),
	       gtmp->GetParameter(1)+2*TMath::Abs(gtmp->GetParameter(2)));
	cout << "***** GTMP " 
	     << gtmp->GetParameter(0) << " " 
	     << gtmp->GetParameter(1) << " " 
	     << gtmp->GetParameter(2) << " "
	     << endl;
	c1->Update();

	delete htmp;
	 
	// RooDataHist from TH1F
	RooRealVar x("x","x", ErecEgenMin, ErecEgenMax);
	RooDataHist data("data","p_{T}/p_{T}^{True}",x,h); 
	RooPlot* xframe = x.frame(RooFit::Name("xframe"),RooFit::Title("p_{T}/p_{T}^{True}")) ;
	data.plotOn(xframe);

	// Initialize CB parameters
	Double_t  alphaStart =   0.5;
	Double_t  alphaMin   =   0.1;
	Double_t  alphaMax   =   2.0;
	Double_t  nStart     =  50.0;
	Double_t  nMin       =   0.0;
	Double_t  nMax       = 200.0;
	if ( gtmp->GetParameter(1) < 0.95 && gtmp->GetParameter(2) > 0.03 ) {
		alphaStart =   0.4;
		alphaMin   =   0.;
		alphaMax   =   1.0;
		nStart     =  20.;
		nMin       =   0.;
		nMax       = 100.;
	}

	// fit function
	RooRealVar alpha  ("alpha"  ,        "alpha" , alphaStart, alphaMin, alphaMax); 
	RooRealVar n      ("n"      ,            "n" , nStart, nMin, nMax); 
	RooRealVar cbmean ("cbmean" ,       "cbmean" , gtmp->GetParameter(1) ,0.5, 1.2); // ErecEgenMin, ErecEgenMax);
	RooRealVar cbsigma("cbsigma",      "cbsigma" , 0.01, 0.001,0.1) ;
	RooCBShape cball  ("cball"  , "crystal ball" , x, cbmean, cbsigma, alpha, n);

/*
	// other functions
	// CB (x) Gaussian
	//   RooRealVar mg("mg","mg",1) ;
	//   RooRealVar sg("sg","sg",0.1,0.01,0.2) ;
	//   RooGaussian gauss("gauss","gauss",x,mg,sg) ; 
	//   RooFFTConvPdf CBgaus("CBgaus","CB (X) gauss",x,cball,gauss);
	//
	// CB + Gaussian
	//   RooRealVar ng("ng","ng",100,1,10000);
	//   RooRealVar nc("nc","nc",10, 1,10000);
	//   RooAddPdf CBgaus("CBgaus","CB + gauss",RooArgList(cball,gauss),RooArgList(nc,ng));

	// Fit Range using as units the sigma of the driving gaussian
	//
	Float_t nsigmaL = 10;
	Float_t nsigmaR = 2;
	//
	// Fit

	RooFitResult* fitres =cball.fitTo(data,
				          RooFit::Range(gtmp->GetParameter(1)-nsigmaL*TMath::Abs(gtmp->GetParameter(2)),
					  gtmp->GetParameter(1)+nsigmaR*TMath::Abs(gtmp->GetParameter(2))),
				          RooFit::Minos(kFALSE));    
*/
	mean  = cbmean.getVal();
	emean = cbmean.getError();
	cball.plotOn (xframe,RooFit::LineColor(kBlue));
	cball.paramOn(xframe,RooFit::Layout(0.55,0.98,0.95));
	data. statOn (xframe,RooFit::Layout(0.55,0.98,0.65));
	chi2  = xframe->chiSquare(4); // dof = 4 = number fof floating parametes
	//cout << "***** CHI2 " << xframe->chiSquare(4) << endl; getchar();


	// plot
	// gStyle->SetOptFit(1);

	string s_cpull = "cpull";
	TCanvas *cpull = new TCanvas((s_cpull + stringa).c_str(),(s_cpull + stringa).c_str(),600,600);
	cpull->SetFillColor(0);
	cpull->SetBorderMode(0);
	cpull->SetBorderSize(2);
	cpull->SetFrameBorderMode(0);
	cpull->SetFrameBorderMode(0);
	cpull->SetBottomMargin(0.25);
	TString chi2txt = "#chi^{2}=" + floatToString(xframe->chiSquare(4)) ; // dof = 4 = number dof floating parametes
	TLatex* txt = new TLatex(0.65,0.38,chi2txt);
	txt->SetNDC();
	txt->SetTextSize(0.04) ;
	txt->SetTextColor(kRed) ;
	xframe->addObject(txt) ;
	xframe->GetXaxis()->SetTitle("p_{T}/p_{T}^{True}");
	xframe->Draw();

	cpull->Update();
	cpull->Write();
	cpull->Close();

	return;
}

void fit(){

	//---- output file to save graphs
	char outfilename[20];
	sprintf(outfilename,"fit_2_PixelBarrelConn1_and_PixelBarrelConn2_MC.root");

	//out file
	TFile outfile(outfilename,"recreate");

	// --- NTUPLES
	TChain *ntu_MC = new TChain("ntu");

	//---- MC Particle Gun
	ntu_MC->Add("outfile_2_PixelBarrelConn1_and_PixelBarrelConn2_MC.root/Tree");

	std::cout << "     MC    : " << ntu_MC->GetEntries() << " entries in MC sample." << std::endl;

	//---- Observables
	float ptOverGenpt, el_scEta;

	//---- Set branch addresses for MC
	ntu_MC->SetBranchAddress("ptOverGenpt", &ptOverGenpt);
	ntu_MC->SetBranchAddress("el_scEta",    &el_scEta);

	//---- book histos
	const int Ntempl = bin+2;
	TH1F* h_ptOverGenpt_MC[Ntempl];
	for(int i = 0; i < Ntempl; ++i){
		char histoName[20];
		sprintf(histoName, "h_ptOverGenpt_MC_%d", i);
		h_ptOverGenpt_MC[i] = new TH1F(histoName, "", nBinsErecEgen, ErecEgenMin, ErecEgenMax);
	}


	//******************************************************************************************
	//*************************************** MC ********************************************** 

	std::cout << "Loop in MC events " << endl; 
	//--------------- loop on MC, make reference and fit distributions
	for(int entry = 0; entry < ntu_MC->GetEntries(); ++entry) {
		if( entry%100000 == 0 ) std::cout << "reading MC saved entry " << entry << "\r" << std::flush;

		ntu_MC->GetEntry(entry);
		int mod = EtaBins(el_scEta, c, d);
		h_ptOverGenpt_MC[mod]-> Fill(ptOverGenpt);
		h_ptOverGenpt_MC[mod]->GetXaxis()->SetTitle("p_{T}/p_{T}^{True}");
		h_ptOverGenpt_MC[mod]->GetYaxis()->SetTitle("Events");
 	}


	//************************************* FITTING ***************************************************//

	TGraphErrors* g_ptOverGenpt_MC  = new TGraphErrors();
	g_ptOverGenpt_MC->SetName("g_ptOverGenpt_MC");


	for (int imod = 1; imod < Ntempl-1; imod++) {

		double mean    = 1;
		double emean   = 0;
		double chi2    = 0;
		string s      = "_";
		s += intToString(imod);

		fitCB(h_ptOverGenpt_MC[imod], mean, emean, chi2, s);

		float Iniz = imod-1;
		float xval = ((c + (imod-1)*d) + (c + imod*d))/2;
		float yval = mean;
		float yvalErr = emean;
cout << "imod = " << imod << endl; 
cout << "(c + (imod-1)*d) = " << (c + (imod-1)*d) << endl; 
cout << "(c + imod*d) = " << (c + imod*d) << endl; 
cout << "xval = " << xval << endl;
cout << "yval = " << yval << endl;
cout << "yvalErr = " << yvalErr << endl;
cout << "----------------------------------" << endl; 

		g_ptOverGenpt_MC -> SetPoint(Iniz, xval , yval);
		g_ptOverGenpt_MC -> SetPointError(Iniz, 0., yvalErr);

	}



	for (int jmod = 0; jmod < Ntempl; jmod++){
		h_ptOverGenpt_MC[jmod]->Write();
	}
	g_ptOverGenpt_MC -> Write(); 
}

