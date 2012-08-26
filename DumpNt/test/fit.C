
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

using namespace std;


//const float c = -1.610;
const float c = -1.653;

//const float d = 0.0805;
//const float d = 0.04025;
const float d = 0.0348;

int EtaBins(float eta, float a, float b){
//	float a = -1.610;
//	float b = 0.0805;

	if (eta<= a+0*b)                  {return 0;}
	if (eta> a+0*b && eta <= a+1*b)   {return 1;}
	if (eta> a+1*b && eta <= a+2*b)   {return 2;}
	if (eta> a+2*b && eta <= a+3*b)   {return 3;}
	if (eta> a+3*b && eta <= a+4*b)   {return 4;}  
	if (eta> a+4*b && eta <= a+5*b)   {return 5;}
	if (eta> a+5*b && eta <= a+6*b)   {return 6;}
	if (eta> a+6*b && eta <= a+7*b)   {return 7;}
	if (eta> a+7*b && eta <= a+8*b)   {return 8;}
	if (eta> a+8*b && eta <= a+9*b)   {return 9;}
	if (eta> a+9*b && eta <= a+10*b)  {return 10;} 
	if (eta> a+10*b && eta <= a+11*b) {return 11;}
	if (eta> a+11*b && eta <= a+12*b) {return 12;}
	if (eta> a+12*b && eta <= a+13*b) {return 13;}
	if (eta> a+13*b && eta <= a+14*b) {return 14;}  
	if (eta> a+14*b && eta <= a+15*b) {return 15;}
	if (eta> a+15*b && eta <= a+16*b) {return 16;}
	if (eta> a+16*b && eta <= a+17*b) {return 17;}
	if (eta> a+17*b && eta <= a+18*b) {return 18;}
	if (eta> a+18*b && eta <= a+19*b) {return 19;}
	if (eta> a+19*b && eta <= a+20*b) {return 20;}  
	if (eta> a+20*b && eta <= a+21*b) {return 21;}  
	if (eta> a+21*b && eta <= a+22*b) {return 22;}  
	if (eta> a+22*b && eta <= a+23*b) {return 23;}  
	if (eta> a+23*b && eta <= a+24*b) {return 24;}  
	if (eta> a+24*b && eta <= a+25*b) {return 25;}  
	if (eta> a+25*b && eta <= a+26*b) {return 26;}  
	if (eta> a+26*b && eta <= a+27*b) {return 27;}  
	if (eta> a+27*b && eta <= a+28*b) {return 28;}  
	if (eta> a+28*b && eta <= a+29*b) {return 29;}  
	if (eta> a+29*b && eta <= a+30*b) {return 30;}  
	if (eta> a+30*b && eta <= a+31*b) {return 31;}  
	if (eta> a+31*b && eta <= a+32*b) {return 32;}  
	if (eta> a+32*b && eta <= a+33*b) {return 33;}  
	if (eta> a+33*b && eta <= a+34*b) {return 34;}  
	if (eta> a+34*b && eta <= a+35*b) {return 35;}  
	if (eta> a+35*b && eta <= a+36*b) {return 36;}  
	if (eta> a+36*b && eta <= a+37*b) {return 37;}  
	if (eta> a+37*b && eta <= a+38*b) {return 38;}  
	if (eta> a+38*b && eta <= a+39*b) {return 39;}  
	if (eta> a+39*b && eta <= a+40*b) {return 40;}
	if (eta> a+40*b && eta <= a+41*b) {return 41;}
	if (eta> a+41*b && eta <= a+42*b) {return 42;}
	if (eta> a+42*b && eta <= a+43*b) {return 43;}
	if (eta> a+43*b && eta <= a+44*b) {return 44;}
	if (eta> a+44*b && eta <= a+45*b) {return 45;}
	if (eta> a+45*b && eta <= a+46*b) {return 46;}
	if (eta> a+46*b && eta <= a+47*b) {return 47;}

	if (eta> a+47*b && eta <= a+48*b) {return 48;}
	if (eta> a+48*b && eta <= a+49*b) {return 49;}
	if (eta> a+49*b && eta <= a+50*b) {return 50;}
	if (eta> a+50*b && eta <= a+51*b) {return 51;}
	if (eta> a+51*b && eta <= a+52*b) {return 52;}
	if (eta> a+52*b && eta <= a+53*b) {return 53;}
	if (eta> a+53*b && eta <= a+54*b) {return 54;}
	if (eta> a+54*b && eta <= a+55*b) {return 55;}
	if (eta> a+55*b && eta <= a+56*b) {return 56;}
	if (eta> a+56*b && eta <= a+57*b) {return 57;}
	if (eta> a+57*b && eta <= a+58*b) {return 58;}
	if (eta> a+58*b && eta <= a+59*b) {return 59;}
	if (eta> a+59*b && eta <= a+60*b) {return 60;}
	if (eta> a+60*b && eta <= a+61*b) {return 61;}
	if (eta> a+61*b && eta <= a+62*b) {return 62;}
	if (eta> a+62*b && eta <= a+63*b) {return 63;}
	if (eta> a+63*b && eta <= a+64*b) {return 64;}
	if (eta> a+64*b && eta <= a+65*b) {return 65;}
	if (eta> a+65*b && eta <= a+66*b) {return 66;}
	if (eta> a+66*b && eta <= a+67*b) {return 67;}
	if (eta> a+67*b && eta <= a+68*b) {return 68;}
	if (eta> a+68*b && eta <= a+69*b) {return 69;}
	if (eta> a+69*b && eta <= a+70*b) {return 70;}
	if (eta> a+70*b && eta <= a+71*b) {return 71;}
	if (eta> a+71*b && eta <= a+72*b) {return 72;}
	if (eta> a+72*b && eta <= a+73*b) {return 73;}
	if (eta> a+73*b && eta <= a+74*b) {return 74;}
	if (eta> a+74*b && eta <= a+75*b) {return 75;}
	if (eta> a+75*b && eta <= a+76*b) {return 76;}
	if (eta> a+76*b && eta <= a+77*b) {return 77;}
	if (eta> a+77*b && eta <= a+78*b) {return 78;}
	if (eta> a+78*b && eta <= a+79*b) {return 79;}
	if (eta> a+79*b && eta <= a+80*b) {return 80;}
	if (eta> a+80*b && eta <= a+81*b) {return 81;}
	if (eta> a+81*b && eta <= a+82*b) {return 82;}
	if (eta> a+82*b && eta <= a+83*b) {return 83;}
	if (eta> a+83*b && eta <= a+84*b) {return 84;}
	if (eta> a+84*b && eta <= a+85*b) {return 85;}
	if (eta> a+85*b && eta <= a+86*b) {return 86;}
	if (eta> a+86*b && eta <= a+87*b) {return 87;}
	if (eta> a+87*b && eta <= a+88*b) {return 88;}
	if (eta> a+88*b && eta <= a+89*b) {return 89;}
	if (eta> a+89*b && eta <= a+90*b) {return 90;}
	if (eta> a+90*b && eta <= a+91*b) {return 91;}
	if (eta> a+91*b && eta <= a+92*b) {return 92;}
	if (eta> a+92*b && eta <= a+93*b) {return 93;}
	if (eta> a+93*b && eta <= a+94*b) {return 94;}
	if (eta> a+94*b && eta <= a+95*b) {return 95;}
  	if (eta> a+95*b)                  {return 96;}  

	return -1;
}



void Grafici_dopo_incontro(){

	//---- output file to save graphs
	char outfilename[20];
	sprintf(outfilename,"fit_dopo_incontro.root");

	// --- NTUPLES
	TChain *ntu_MC = new TChain("ntu");

	//---- MC Particle Gun
	ntu_MC->Add("outfile_0_Original_MC.root/Tree");

	std::cout << "     MC    : " << ntu_MC->GetEntries() << " entries in MC sample." << std::endl;

	//---- Observables
	float ptOverGenpt, el_scEta;

	//---- Set branch addresses for MC
	ntu_MC->SetBranchAddress("ptOverGenpt", &ptOverGenpt);
	ntu_MC->SetBranchAddress("el_scEta",    &el_scEta);

	//---- book histos
	const int Ntempl = 97;
	TH1F* h_ptOverGenpt_MC[Ntempl];
	for(int i = 0; i < Ntempl; ++i){
		char histoName[20];
		sprintf(histoName, "h_ptOverGenpt_MC_%d", i);
		h_ptOverGenpt_MC[i] = new TH1F(histoName, "", 1000, 0., 2.);
	}


	//******************************************************************************************
	//*************************************** MC  ********************************************** 
   
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

		h_ptOverGenpt_MC[imod]-> Rebin(4);

		TFitResultPtr rp;
//		int fStatus; 
//		for (int trial = 0; trial < 5; trial++) {
			TF1 *f1 = new TF1("f1", "gaus", 0, 2);
			rp = h_ptOverGenpt_MC[imod] -> Fit(f1, "EMQRLS+");
//			fStatus = rp;
//			if (fStatus < 2) break; 

			float Iniz = imod-1;
			float xval = ((c + (imod-1)*d) + (c + imod*d))/2;
			float yval = f1->GetParameter(1);
			float yvalErr = f1->GetParError(1);
cout << "imod = " << imod << endl; 
cout << "(c + (imod-1)*d) = " << (c + (imod-1)*d) << endl; 
cout << "(c + imod*d) = " << (c + imod*d) << endl; 
cout << "xval = " << xval << endl;
cout << "yval = " << yval << endl;
cout << "yvalErr = " << yvalErr << endl;
cout << "----------------------------------" << endl; 

			g_ptOverGenpt_MC -> SetPoint(Iniz, xval , yval);
			g_ptOverGenpt_MC -> SetPointError(Iniz, 0., yvalErr);

//		}
	}

	//out file
	TFile outfile(outfilename,"recreate");

	for (int jmod = 0; jmod < Ntempl; jmod++){
		h_ptOverGenpt_MC[jmod]->Write();
	}
	g_ptOverGenpt_MC -> Write(); 
}

