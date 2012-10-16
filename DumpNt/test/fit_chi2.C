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


double gaussMin = 0.39; 
double gaussMax = 1.61;

int nBinsErecEgen = 250;
double ErecEgenMin = 0.; 
double ErecEgenMax = 2.;

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

/*
Double_t crystal(Double_t *x, Double_t *par){
	Double_t xx = x[0];
	Double_t a = par[0] + par[1]*xx + par[2]*xx*xx + par[3]*xx*xx*xx;
	return a;
}
*/
Double_t crystal(Double_t *x, Double_t *par){

	Double_t xx = x[0];
	Double_t t = (xx-par[0])/par[1];
	if (par[3] < 0) t = -t;

	Double_t absAlpha = fabs((Double_t)par[3]);

	if (t >= -absAlpha) {
		return exp(-0.5*t*t);
	}
	else {
		Double_t a = TMath::Power(par[2]/absAlpha,par[2])*exp(-0.5*absAlpha*absAlpha);
		Double_t b = par[2]/absAlpha - absAlpha; 
		return a/TMath::Power(b - t, par[2]);
	}
}

//void fitCBmod(TH1F *h, Double_t &mean, Double_t &emean, Double_t &sigma, Double_t &esigma, Double_t &n, Double_t &en, Double_t &alpha, Double_t &ealpha, Double_t &FWHM, Double_t &eFWHM, Double_t &chi2, string &stringa, Double_t &alphaStart_y, Double_t &nStart_y, Double_t &u)
void fitCBmod(TH1F *h, Double_t &mean, Double_t &emean, Double_t &sigma, Double_t &esigma, Double_t &n, Double_t &en, Double_t &alpha, Double_t &ealpha, Double_t &FWHM, Double_t &eFWHM, Double_t &chi2, string &stringa, Float_t &u){
	// This is to quantify the fraction of events where the reconstructed energy is below EgenFrac
	// badReco = h->Integral(1,h->FindBin(EgenFrac)) / (Double_t)h->GetEntries();

	// driving gaussian. Used to estimate the fit range
	TF1 *gtmp = 0;

	TCanvas *c1 = new TCanvas("c1","c1",600,600);
	c1->cd();
	h->Draw();

	// more solid peak position with a temporary histogram filled only with the bins above 50% of the peak max
	TH1F *htmp = new TH1F("htmp","htmp",nBinsErecEgen,gaussMin, gaussMax);
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
	Double_t  cbmeanStart =   gtmp->GetParameter(1)+0.025*gtmp->GetParameter(1);
	Double_t  cbmeanMin   =   cbmeanStart-0.5*cbmeanStart;
	Double_t  cbmeanMax   =   cbmeanStart+0.5*cbmeanStart;

	Double_t  cbsigmaStart =   TMath::Abs(gtmp->GetParameter(2))-0.2*TMath::Abs(gtmp->GetParameter(2));
	Double_t  cbsigmaMin   =   cbsigmaStart-0.4*cbsigmaStart;
	Double_t  cbsigmaMax   =   cbsigmaStart+0.4*cbsigmaStart;

/*	Double_t  cbalphaStart_x =   alphaStart_y;
	Double_t  cbalphaStart =   cbalphaStart_x + u;
*/
	Double_t  cbalphaStart =   0.7;
	Double_t  cbalphaMin   =   cbalphaStart-0.4*cbalphaStart;
	Double_t  cbalphaMax   =   cbalphaStart+0.4*cbalphaStart;
/*
	Double_t  cbnStart_x     =   nStart_y;
	Double_t  cbnStart     =   cbnStart_x + u; 
*/
	Double_t  cbnStart     =   1.7;
	Double_t  cbnMin       =   cbnStart-0.4*cbnStart;
	Double_t  cbnMax       =   cbnStart+0.4*cbnStart;

cout << "cbmeanStart = " <<  gtmp->GetParameter(1) << endl;
//cout << "cbmean = " <<  cbmean << endl;
cout << "cbsigmaStart = " <<  gtmp->GetParameter(2) << endl;
//cout << "cbsigma = " <<  cbsigma << endl;
/*
	if (gtmp->GetParameter(1)<0.93){
		cbmeanStart =   gtmp->GetParameter(1)+0.18*gtmp->GetParameter(1);
		cbmeanMin   =   cbmeanStart-0.5*cbmeanStart;
		cbmeanMax   =   cbmeanStart+0.5*cbmeanStart;

		cbsigmaStart =   TMath::Abs(gtmp->GetParameter(2))-0.3*TMath::Abs(gtmp->GetParameter(2));
		cbsigmaMin   =   cbsigmaStart-0.3*cbsigmaStart;
		cbsigmaMax   =   cbsigmaStart+0.3*cbsigmaStart;

		alphaStart =   0.7;
		alphaMin   =   alphaStart-0.4*alphaStart;
		alphaMax   =   alphaStart+0.4*alphaStart;

		nStart     =   1.0;
		nMin       =   nStart-0.3*nStart;
		nMax       =   nStart+0.3*nStart;
	}
*/
	// fit function
	RooRealVar cbalpha("cbalpha",       "cbalpha", cbalphaStart, cbalphaMin, cbalphaMax); 
	RooRealVar cbn    ("cbn"    ,           "cbn", cbnStart, cbnMin, cbnMax); 
	RooRealVar cbmean ("cbmean" ,       "cbmean" , cbmeanStart ,cbmeanMin, cbmeanMax); // ErecEgenMin, ErecEgenMax);
	RooRealVar cbsigma("cbsigma",      "cbsigma" , cbsigmaStart ,cbsigmaMin, cbsigmaMax) ;
	RooCBShape cball  ("cball"  , "crystal ball" , x, cbmean, cbsigma, cbalpha, cbn);

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
*/

	// Fit Range using as units the sigma of the driving gaussian
	//
	Float_t r = u;	
	Float_t nsigmaL = 10 - r;
	Float_t nsigmaR = 2;
	//

	// Fit
	RooFitResult* fitres =cball.fitTo(data,
		                          RooFit::Range(gtmp->GetParameter(1)-nsigmaL*TMath::Abs(gtmp->GetParameter(2)),
					                gtmp->GetParameter(1)+nsigmaR*TMath::Abs(gtmp->GetParameter(2))),
				          RooFit::Minos(kFALSE));    
	cout << "fitres = " << fitres << endl;

	mean   = cbmean.getVal();
	emean  = cbmean.getError();
	sigma  = cbsigma.getVal();
	esigma = cbsigma.getError();
	n      = cbn.getVal();
	en     = cbn.getError();
	alpha  = cbalpha.getVal();
	ealpha = cbalpha.getError();
//	FWHM   = 1;
//	eFWHM  = 1;

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
	string dir = "plots/";
	string ext = ".png";
	cpull->SaveAs((dir + s_cpull + stringa + ext).c_str());
	cpull->Close();

	cpull->Close();


	TCanvas *prova = new TCanvas("prova","prova",600,600);

	double halfMaximum, x_Maximum, x_Sx, x_Dx;
	TF1 *f1 = new TF1("f1",crystal,ErecEgenMin,ErecEgenMax,4);
	f1->SetParameters(mean,sigma,n,alpha);
	f1->SetParError(0,emean);
	f1->SetParError(1,esigma);
	f1->SetParError(2,en);
	f1->SetParError(3,ealpha);
	f1->SetParNames("mean","sigma","n","alpha");

cout << "mean = " << mean << endl;
	x_Maximum = f1->GetMaximumX(); 
cout << "x_Maximum = " << x_Maximum << endl; 
cout << "Maximum = " << f1->GetMaximum() << endl;
	halfMaximum = f1->GetMaximum()/2;
cout << "halfMaximum = " << halfMaximum << endl;
	x_Sx = f1->GetX(halfMaximum,0,x_Maximum);
	x_Dx = f1->GetX(halfMaximum,x_Maximum,2);
cout << "x_Sx = " << x_Sx << endl;
cout << "x Dx = " << x_Dx << endl;
	FWHM = x_Dx-x_Sx;
cout << "FWHM = " << FWHM << endl;
cout << "sigma = " << sigma << endl;
	eFWHM =emean;

	f1->Draw();
	f1->Write();

	prova->Close();


	return;
}

/*void fitCBmod1(TH1F *h, Double_t &mean, Double_t &emean, Double_t &sigma, Double_t &esigma, Double_t &n, Double_t &en, Double_t &alpha, Double_t &ealpha, Double_t &FWHM, Double_t &eFWHM, Double_t &chi2, string &stringa, Double_t &alphaStart_y, Double_t &nStart_y, Double_t &u, Double_t &k, Double_t &z)
{
	fitCBmod(h, mean, emean, sigma, esigma, n, en, alpha, ealpha, FWHM, eFWHM, chi2, stringa, alphaStart_y, nStart_y, u);
	k = n;
	z = alpha;
}
*/

void fit_chi2(){

	//---- output file to save graphs
	char outfilename[20];
	sprintf(outfilename,"fit_0_Original_MC_ClosestTrackpt_chi2.root");

	//out file
	TFile outfile(outfilename,"recreate");

	// --- NTUPLES
	TChain *ntu_MC = new TChain("ntu");

	//---- MC Particle Gun
	ntu_MC->Add("outfile_0_Original_MC.root/Tree");

	std::cout << "     MC    : " << ntu_MC->GetEntries() << " entries in MC sample." << std::endl;

	//---- Observables
	float ptOverGenpt, el_scEta;

	//---- Set branch addresses for MC
	ntu_MC->SetBranchAddress("ClosestTrackpt_Over_Genpt", &ptOverGenpt);
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

	TGraphErrors* g_ptOverGenpt_MC_mean  = new TGraphErrors();
	g_ptOverGenpt_MC_mean->SetName("g_ptOverGenpt_MC_mean");

	TGraphErrors* g_ptOverGenpt_MC_sigma  = new TGraphErrors();
	g_ptOverGenpt_MC_sigma->SetName("g_ptOverGenpt_MC_sigma");

	TGraphErrors* g_ptOverGenpt_MC_n  = new TGraphErrors();
	g_ptOverGenpt_MC_n->SetName("g_ptOverGenpt_MC_n");

	TGraphErrors* g_ptOverGenpt_MC_alpha  = new TGraphErrors();
	g_ptOverGenpt_MC_alpha->SetName("g_ptOverGenpt_MC_alpha");

	TGraphErrors* g_ptOverGenpt_MC_FWHM  = new TGraphErrors();
	g_ptOverGenpt_MC_FWHM->SetName("g_ptOverGenpt_MC_FWHM");


	for (int imod = 1; imod < Ntempl-1; imod++) {
//	for (int imod = 15; imod < 16; imod++) {
		double mean    = 1;
		double emean   = 0;
		double sigma   = 1;
		double esigma  = 0;
		double n       = 1;
		double en      = 0;
		double alpha   = 1;
		double ealpha  = 0;
		double FWHM    = 1;
		double eFWHM   = 0;

		double chi2    = 0;
		string s      = "_";
		s += intToString(imod);

//		double nStart = 0.6;
//		double alphaStart = 1.6;
		float u = 0.0;
//		double k = 0.1;
//		double z = 0.1;
//	fitCBmod(h_ptOverGenpt_MC[imod], mean, emean, sigma, esigma, n, en, alpha, ealpha, FWHM, eFWHM, chi2, s, alphaStart, nStart, u);
	fitCBmod(h_ptOverGenpt_MC[imod], mean, emean, sigma, esigma, n, en, alpha, ealpha, FWHM, eFWHM, chi2, s, u);
//		nStart = 0.1;
//		alphaStart = 0.1;
//		u = 0.01;
		if (chi2>2){
		
		do {fitCBmod(h_ptOverGenpt_MC[imod], mean, emean, sigma, esigma, n, en, alpha, ealpha, FWHM, eFWHM, chi2, s, u);
		u = u+0.1;}
//		nStart = k;
//		alphaStart = z; 

		while (chi2 > 2);
		}

		float Iniz = imod-1;
		float xval = ((c + (imod-1)*d) + (c + imod*d))/2;

		float yval_mean = mean;
		float yvalErr_mean = emean;
		float yval_sigma = sigma;
		float yvalErr_sigma = esigma;
		float yval_n = n;
		float yvalErr_n = en;
		float yval_alpha = alpha;
		float yvalErr_alpha = ealpha;
		float yval_FWHM = FWHM;
		float yvalErr_FWHM = eFWHM;


//cout << "imod = " << imod << endl; 
//cout << "(c + (imod-1)*d) = " << (c + (imod-1)*d) << endl; 
//cout << "(c + imod*d) = " << (c + imod*d) << endl; 
//cout << "xval = " << xval << endl;
//cout << "yval = " << yval << endl;
//cout << "yvalErr = " << yvalErr << endl;
//cout << "chi2 = " << chi2 << endl;
//cout << "----------------------------------" << endl; 

		g_ptOverGenpt_MC_mean -> SetPoint(Iniz, xval , yval_mean);
		g_ptOverGenpt_MC_mean -> SetPointError(Iniz, 0., yvalErr_mean);

		g_ptOverGenpt_MC_sigma -> SetPoint(Iniz, xval , yval_sigma);
		g_ptOverGenpt_MC_sigma -> SetPointError(Iniz, 0., yvalErr_sigma);

		g_ptOverGenpt_MC_n -> SetPoint(Iniz, xval , yval_n);
		g_ptOverGenpt_MC_n -> SetPointError(Iniz, 0., yvalErr_n);

		g_ptOverGenpt_MC_alpha -> SetPoint(Iniz, xval , yval_alpha);
		g_ptOverGenpt_MC_alpha -> SetPointError(Iniz, 0., yvalErr_alpha);

		g_ptOverGenpt_MC_FWHM -> SetPoint(Iniz, xval , yval_FWHM);
		g_ptOverGenpt_MC_FWHM -> SetPointError(Iniz, 0., yvalErr_FWHM);

	}



	for (int jmod = 0; jmod < Ntempl; jmod++){
		h_ptOverGenpt_MC[jmod]->Write();
	}
	g_ptOverGenpt_MC_mean -> Write(); 
	g_ptOverGenpt_MC_sigma -> Write(); 
	g_ptOverGenpt_MC_n -> Write(); 
	g_ptOverGenpt_MC_alpha -> Write(); 
	g_ptOverGenpt_MC_FWHM -> Write(); 
}

