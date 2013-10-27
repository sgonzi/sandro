#define TurnOn_cxx
#include "TurnOn.h"
#include "TurnOnDefs.h"
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
#include <Riostream.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TH2F.h>
#include <fstream>


#include <DataFormats/Math/interface/deltaR.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "FWCore/Utilities/interface/Exception.h"
#endif


//#ifdef __MAKECINT__
//#pragma link C++ class vector<float>+;
//#endif

//		In a ROOT session, you can do:
//			Root > .L TurnOn.C++
//			Root > TurnOn t(0,4); // Load the analysis on the sample number 4 
//			Root > t.GetEntry(12);	     // Fill t data members with entry number 12
//			Root > t.Show();				     // Show values of entry 12
//			Root > t.Show(16);			     // Read and show values of entry 16
//			Root > t.Loop();				     // Loop on all entries
//

//		This is the loop skeleton where:
//			jentry is the global entry number in the chain;
//			ientry is the entry number in the current Tree.
//		Note that the argument to GetEntry must be:
//			jentry for TChain::GetEntry;
//			ientry for TTree::GetEntry and TBranch::GetEntry.
//
//		To read only selected branches, Insert statements like:
//			METHOD1:
//				fChain->SetBranchStatus("*",0);						// disable all branches
//				fChain->SetBranchStatus("branchname",1);	// activate branchname
//			METHOD2:
//				replace line fChain->GetEntry(jentry);	// read all branches
//				by b_branchname->GetEntry(ientry);			// read only this branch


void TurnOn::Loop(){


	// ==================================== choose the tools
	
	bool RedAn = false;								// analysis with a reduced entries number for tests

	bool data_ReReco = true;					// analysis with data ReReco or data PromptReco
	string geo = "barrel";						// barrel or endcaps
	bool SigBack = true;							// to avoid double counting for SIGNAL and BACKGROUND
	bool TeP_corr = true;							// T&P correction
		
	bool plothistos = false;					// please select which plots to show
	bool textfile = true;							// if you want a text report for each sample
	Int_t itype = 7;									// it identifies histos with different analysis 

	// choose the sample:
	// -----------------------------------------------------
	// mysample == 0   -> Test
	// -----------------------------------------------------
	// mysample == 1   -> DATA RR Run2012A-22Jan2013
	// mysample == 2   -> DATA RR Run2012B-22Jan2013
	// mysample == 3   -> DATA RR Run2012C-22Jan2013
	// mysample == 4   -> DATA RR Run2012D-22Jan2013
	// -----------------------------------------------------
	// mysample == 11  -> DATA PR Run2012A-13Jul2012
	// mysample == 12  -> DATA PR Run2012A-recover-06Aug2012
	// mysample == 13  -> DATA PR Run2012B-13Jul2012
	// mysample == 14  -> DATA PR Run2012C-24Aug2012
	// mysample == 15  -> DATA PR Run2012C-EcalRecover_11Dec2012
	// mysample == 16  -> DATA PR Run2012C-PromptReco
	// mysample == 17  -> DATA PR Run2012D-PromptReco
	// -----------------------------------------------------
	// mysample == 21  -> GJets 40<HT<100
	// mysample == 22  -> GJets 100<HT<200
	// mysample == 23  -> GJets 200<HT<400		
	// mysample == 24  -> Gjets 400<HT<Inf
	// -----------------------------------------------------
	// mysample == 31  -> G 15<Pt<30
	// mysample == 32  -> G 30<Pt<50
	// mysample == 33  -> G 50<Pt<80
	// mysample == 34  -> G 80<Pt<120
	// mysample == 35  -> G 120<Pt<170
	// mysample == 36  -> G 170<Pt<300
	// mysample == 37  -> G 300<Pt<470
	// mysample == 38  -> G 470<Pt<800
	// mysample == 39  -> G 800<Pt<1400
	// mysample == 40  -> G 1400<Pt<1800
	// mysample == 41  -> G 1800<Pt<Inf
	// -----------------------------------------------------
	// mysample == 51  -> DiPhotonJets
	// -----------------------------------------------------
	// mysample == 61  -> QCD EMEnriched 20<Pt<30
	// mysample == 62  -> QCD EMEnriched 30<Pt<80
	// mysample == 63  -> QCD EMEnriched 80<Pt<170
	// mysample == 64  -> QCD EMEnriched 170<Pt<250
	// mysample == 65  -> QCD EMEnriched 250<Pt<350
	// mysample == 66  -> QCD EMEnriched 350<Pt<Inf
	// -----------------------------------------------------
	// mysample == 71  -> QCD BCtoE 20<Pt<30
	// mysample == 72  -> QCD BCtoE 30<Pt<80
	// mysample == 73  -> QCD BCtoE 80<Pt<170
	// mysample == 74  -> QCD BCtoE 170<Pt<250
	// mysample == 75  -> QCD BCtoE 250<Pt<350
	// mysample == 76  -> QCD BCtoE 350<Pt<Inf
	// -----------------------------------------------------
	// mysample == 81  -> QCD 100<HT<250
	// mysample == 82  -> QCD 250<HT<500
	// mysample == 83  -> QCD 500<HT<1000
	// mysample == 84  -> QCD 1000<HT<Inf
	// -----------------------------------------------------


	// ==================================== exception controls

	if (!(geo == "barrel" || geo == "endcaps")) {
		cout << "ERROR: Wrong geometry string (only \"barrel\" or \"endcaps)\". You wrote: \"" << geo << "\"" << endl << endl;
		throw cms::Exception("WrongString");
	}


	// ==================================== numeric and definition side of the code
	
	double Lumi_t;
	if (data_ReReco) Lumi_t = 19712.; // /pb
	else Lumi_t = 19027.853; // /pb
	double xsec = 1.;
	double FiltEff = 1.;
	double kFac = 1.;
	double nEvents = 1.;

	Float_t weight = 1; 
	Float_t weight_withPU = 1;
	Float_t scale_TeP = 1.;
	Float_t scale_TeP_sel_1 = 1.;
	Float_t scale_TeP_sel_2 = 1.;
	Float_t scale_TeP_sel_4 = 1.;
	Float_t scale_TeP_sel_8 = 1.;
	Float_t scale_TeP_sel_16 = 1.;
	Float_t scale_TeP_sel_32 = 1.;
	Float_t scale_TeP_sel_64 = 1.;
	Float_t scale_TeP_sel_128 = 1.;
	Float_t scale_TeP_sel_256 = 1.;
	Float_t scale_TeP_sel_512 = 1.;
	Float_t scale_TeP_sel_1024 = 1.;
	Float_t scale_TeP_sel_2048 = 1.;
	Float_t scale_TeP_sel_4096 = 1.;
	Float_t weight_final = 1;
	Float_t weight_final_sel_1 = 1.;
	Float_t weight_final_sel_2 = 1.;
	Float_t weight_final_sel_4 = 1.;
	Float_t weight_final_sel_8 = 1.;
	Float_t weight_final_sel_16 = 1.;
	Float_t weight_final_sel_32 = 1.;
	Float_t weight_final_sel_64 = 1.;
	Float_t weight_final_sel_128 = 1.;
	Float_t weight_final_sel_256 = 1.;
	Float_t weight_final_sel_512 = 1.;
	Float_t weight_final_sel_1024 = 1.;
	Float_t weight_final_sel_2048 = 1.;
	Float_t weight_final_sel_4096 = 1.;


	string geo_s = geo + "/";
	string sample = "";
	string out_files = "output_files/";
	string histos = "_histos_%d_";
	string report = "_report_%d_";
	string root = ".root";
	string txt = ".txt";
	string TurnOn_s = "_TurnOn";

	root = TurnOn_s + root;
	txt = TurnOn_s + txt;
				
	cout << endl;
	cout << "mysample is " << mysample << endl;

	// test -----------------------------------------------------------------
	if (mysample == 0){
		sample = "TEST";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	// data ReReco ----------------------------------------------------------
	else if (mysample == 1) {
		sample = "DATA_RR_Run2012A-22Jan2013";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 2) {
		sample = "DATA_RR_Run2012B-22Jan2013";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 3) {
		sample = "DATA_RR_Run2012C-22Jan2013";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 4) {
		sample = "DATA_RR_Run2012D-22Jan2013";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	// data PromptReco ------------------------------------------------------
	else if (mysample == 11) {
		sample = "DATA_PR_Run2012A-13Jul2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 12) {
		sample = "DATA_PR_Run2012A-recover-06Aug2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 13) {
		sample = "DATA_PR_Run2012B-13Jul2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 14) {
		sample = "DATA_PR_Run2012C-24Aug2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 15) {
		sample = "DATA_PR_Run2012C-EcalRecover_11Dec2012";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 16) {
		sample = "DATA_PR_Run2012C-PromptReco";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	else if (mysample == 17) {
		sample = "DATA_PR_Run2012D-PromptReco";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		weight = 1.;
		cout << "Running on " << sample << endl;
		cout<<"Integrated luminosity is "<< Lumi_t << " /pb" << endl;
	}

	// MC signal GJets_HT-xToy ----------------------------------------------
	else if (mysample == 21){ 
		sample = "MC_GJets_HT-40To100";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 19857930.;
		xsec = 20930.;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 22){ 
		sample = "MC_GJets_HT-100To200";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 9612703;
		xsec = 5325.77; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 23){ 
		sample = "MC_GJets_HT-200To400";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 58627147;
		xsec = 1008.03;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 24){
		sample = "MC_GJets_HT-400ToInf";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 42391678;
		xsec = 105.418;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	// MC signal G_Pt-XtoY --------------------------------------------------
	else if (mysample == 31){
		sample = "MC_G_Pt-15to30";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1970745;
		xsec = 200061.7; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 32){
		sample = "MC_G_Pt-30to50";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1993325;
		xsec = 19931.62; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 33){
		sample = "MC_G_Pt-50to80";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1995062;
		xsec = 3322.309; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 34){
		sample = "MC_G_Pt-80to120";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1992627;
		xsec = 558.2865;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 35){
		sample = "MC_G_Pt-120to170";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 2000043;
		xsec = 108.0068;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 36){
		sample = "MC_G_Pt-170to300";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 2000069;
		xsec = 30.12207;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 37){
		sample = "MC_G_Pt-300to470";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 2000130;
		xsec = 2.138632;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 38){
		sample = "MC_G_Pt-470to800";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1975231;
		xsec = 0.2119244;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 39){
		sample = "MC_G_Pt-800to1400";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1973504;
		xsec = 0.007077847;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 40){
		sample = "MC_G_Pt-1400to1800";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1984890;
		xsec = 4.510327E-5; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 41){
		sample = "MC_G_Pt-1800";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1939122;
		xsec = 1.867141E-6; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	// MC signal DiPhotonJets -----------------------------------------------
	else if (mysample == 51){
		sample = "MC_DiPhotonJets";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1156284;
		xsec = 75.39;
		FiltEff = 1;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	// MC background QCD_Pt_x_y EMEnriched ----------------------------------
	else if (mysample == 61){
		sample = "MC_QCD_Pt_20_30_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34940695;
		xsec = 2.88651E8; 
		FiltEff = 0.0101;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 62){
		sample = "MC_QCD_Pt_30_80_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 33088888;
		xsec = 7.43031E7; 
		FiltEff = 0.0621;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 63){
		sample = "MC_QCD_Pt_80_170_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34542763;
		xsec = 1.19391E6; 
		FiltEff = 0.1539;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 64){
		sample = "MC_QCD_Pt_170_250_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 31697066;
		xsec = 30980.0; 
		FiltEff = 0.148;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 65){
		sample = "MC_QCD_Pt_250_350_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34511322;
		xsec = 4245.29; 
		FiltEff = 0.131;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 66){
		sample = "MC_QCD_Pt_350_EMEnriched";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 34030562;
		xsec = 810.454;
		FiltEff = 0.11;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	// MC background QCD_Pt_x_y BCtoE ---------------------------------------
	else if (mysample == 71){
		sample = "MC_QCD_Pt_20_30_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1740229;
		xsec = 2.886E8;
		FiltEff = 5.8E-4;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 72){
		sample = "MC_QCD_Pt_30_80_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 2048152;
		xsec = 7.424E7;
		FiltEff = 0.00225;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 73){
		sample = "MC_QCD_Pt_80_170_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1945525;
		xsec = 1191000.0;
		FiltEff = 0.0109;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 74){
		sample = "MC_QCD_Pt_170_250_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1948112;
		xsec = 30980.0; 
		FiltEff = 0.0204;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 75){
		sample = "MC_QCD_Pt_250_350_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 2026521;
		xsec = 4250.0;
		FiltEff = 0.0243;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 76){
		sample = "MC_QCD_Pt_350_BCtoE";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 1948532;
		xsec = 811.0;
		FiltEff = 0.0295;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}


	// MC background QCD HT-xToy --------------------------------------------
	else if (mysample == 81){
		sample = "MC_QCD_HT-100To250";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype); 
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 50129518;
		xsec = 1.0515E7; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 82){
		sample = "MC_QCD_HT-250To500";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 27062078;
		xsec = 276000.0; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 83){
		sample = "MC_QCD_HT-500To1000";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 30599292;
		xsec = 8631.07; 
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}

	else if (mysample == 84){
		sample = "MC_QCD_HT-1000ToInf";
		sprintf(outputname, (geo_s+out_files+sample+histos+geo+root).c_str(), itype);
		sprintf(textname, (geo_s+out_files+sample+report+geo+txt).c_str(), itype);
		nEvents = 13843863;
		xsec = 210.585;
		FiltEff = 1.;
		kFac = 1.;
		// weight = 1.; // temporary weight=1 for eff. calculation
		weight = Lumi_t /(nEvents/(xsec*FiltEff*kFac));
		cout << "Running on " << sample << endl;
		cout << "Weight is " << weight << endl;
	}
	
	weight_r = weight;
	sample_r = sample;
	// end numeric and definition side of the code

	if (fChain == 0) return;

	// ==================================== initialize and book histograms
	
	TFile *fhistos= new TFile(outputname, "RECREATE");
	Book_Histos();
 
	iSelected0 = 0; 
	iSelected1 = 0;
	iSelected2 = 0;
	iSelected3 = 0;
	iSelected4 = 0;
	iSelected5 = 0;
	iSelected6 = 0;
	iSelected7 = 0;	
	iSelected8 = 0;
	iSelected9 = 0;
	iSelected10 = 0;	
	iSelected11 = 0;	
	iSelected12 = 0;
	iSelected13 = 0;
			
	// ==================================== loop on entries
	
	Long64_t nentries;
	if(RedAn){
		nentries = 1000000; // analysis with a reduced entries number
	}
	else{
		nentries = fChain->GetEntriesFast();
	}

	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries << endl;
	nentries_r = nentries; 

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if(jentry<1) cout << "Entering first event" << endl;
		if(jentry%100000 == 0) cout << jentry << endl;
		Zero_Variables();


		// ==================================== weight
		
		if (isMC && !isTEST) {
			weight_withPU = PUWeight*Lumi_t/1000.; // MC
		}
		else {
			weight_withPU = 1.; // data & Test
		}
		weight_withPU_r = weight_withPU;


		// ==================================== SIGNAL and BACKGROUND separated behaviour to avoid double counting
		
		bool isoGEN; 
		if (SigBack) {
			isoGEN = false; 
			if(isMC) {
				if(Sig) { 
					isoGEN = (photonIsoSumPtDR03GEN >= 0. && photonIsoSumPtDR03GEN <= 10.); // SIGNAL
				}
				else {
					isoGEN = (photonIsoSumPtDR03GEN < 0); // BACKGROUND 
				}
			}
			else isoGEN = true;
		}
		else {
			isoGEN = true; 
		}

		// ==================================== REC selection

			
		// Efficiency corrections
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {

			for(unsigned int iPhoPos = 0; iPhoPos < photonPt->size(); iPhoPos++) {

				// Trigger Matching - definitions	
				bool TriMatchF4Path_sel_1 = false;
				bool TriMatchF4Path_sel_2 = false;
				bool TriMatchF4Path_sel_4 = false;
				bool TriMatchF4Path_sel_8 = false;
				bool TriMatchF4Path_sel_16 = false;
				bool TriMatchF4Path_sel_32 = false;
				bool TriMatchF4Path_sel_64 = false;
				bool TriMatchF4Path_sel_128 = false;
				bool TriMatchF4Path_sel_256 = false;
				bool TriMatchF4Path_sel_512 = false;
				bool TriMatchF4Path_sel_1024 = false;
				bool TriMatchF4Path_sel_2048 = false;
				bool TriMatchF4Path_sel_4096 = false;																									

				TriMatchF4Path_sel_1 = TriMatchF4Path_photon->at(iPhoPos)& 1;
				TriMatchF4Path_sel_2 = TriMatchF4Path_photon->at(iPhoPos)& 2;
				TriMatchF4Path_sel_4 = TriMatchF4Path_photon->at(iPhoPos)& 4;
				TriMatchF4Path_sel_8 = TriMatchF4Path_photon->at(iPhoPos)& 8;
				TriMatchF4Path_sel_16 = TriMatchF4Path_photon->at(iPhoPos)& 16;
				TriMatchF4Path_sel_32 = TriMatchF4Path_photon->at(iPhoPos)& 32;
				TriMatchF4Path_sel_64 = TriMatchF4Path_photon->at(iPhoPos)& 64;
				TriMatchF4Path_sel_128 = TriMatchF4Path_photon->at(iPhoPos)& 128;
				TriMatchF4Path_sel_256 = TriMatchF4Path_photon->at(iPhoPos)& 256;
				TriMatchF4Path_sel_512 = TriMatchF4Path_photon->at(iPhoPos)& 512;
				TriMatchF4Path_sel_1024 = TriMatchF4Path_photon->at(iPhoPos)& 1024;
				TriMatchF4Path_sel_2048 = TriMatchF4Path_photon->at(iPhoPos)& 2048;
				TriMatchF4Path_sel_4096 = TriMatchF4Path_photon->at(iPhoPos)& 4096;

				photonTriMatchF4Path_sel_1.push_back(TriMatchF4Path_sel_1);
				photonTriMatchF4Path_sel_2.push_back(TriMatchF4Path_sel_2);
				photonTriMatchF4Path_sel_4.push_back(TriMatchF4Path_sel_4);
				photonTriMatchF4Path_sel_8.push_back(TriMatchF4Path_sel_8);
				photonTriMatchF4Path_sel_16.push_back(TriMatchF4Path_sel_16);
				photonTriMatchF4Path_sel_32.push_back(TriMatchF4Path_sel_32);
				photonTriMatchF4Path_sel_64.push_back(TriMatchF4Path_sel_64);
				photonTriMatchF4Path_sel_128.push_back(TriMatchF4Path_sel_128);
				photonTriMatchF4Path_sel_256.push_back(TriMatchF4Path_sel_256);				
				photonTriMatchF4Path_sel_512.push_back(TriMatchF4Path_sel_512);
				photonTriMatchF4Path_sel_1024.push_back(TriMatchF4Path_sel_1024);
				photonTriMatchF4Path_sel_2048.push_back(TriMatchF4Path_sel_2048);
				photonTriMatchF4Path_sel_4096.push_back(TriMatchF4Path_sel_4096);
				// end Trigger Matching - definitions

				
				// T&P scale factors - definitions	
				float TeP_SF;
				if (TeP_corr) {
					if (!isMC) TeP_SF = 1.;
					else {
						bool reg_Pt1_Eta1 = false;
						bool reg_Pt2_Eta1 = false;
						bool reg_Pt3_Eta1 = false;
						bool reg_Pt4_Eta1 = false;
						bool reg_Pt5_Eta1 = false;
						bool reg_Pt6_Eta1 = false;
						bool reg_Pt7_Eta1 = false;
						bool reg_Pt8_Eta1 = false;
						bool reg_Pt9_Eta1 = false;
						bool reg_Pt10_Eta1 = false;
						bool reg_Pt11_Eta1 = false;
						bool reg_Pt12_Eta1 = false;
						bool reg_Pt13_Eta1 = false;
						bool reg_Pt14_Eta1 = false;
						bool reg_Pt15_Eta1 = false;								
						bool reg_Pt16_Eta1 = false;

						bool reg_Pt1_Eta2 = false;
						bool reg_Pt2_Eta2 = false;
						bool reg_Pt3_Eta2 = false;
						bool reg_Pt4_Eta2 = false;
						bool reg_Pt5_Eta2 = false;
						bool reg_Pt6_Eta2 = false;
						bool reg_Pt7_Eta2 = false;
						bool reg_Pt8_Eta2 = false;
						bool reg_Pt9_Eta2 = false;
						bool reg_Pt10_Eta2 = false;
						bool reg_Pt11_Eta2 = false;
						bool reg_Pt12_Eta2 = false;
						bool reg_Pt13_Eta2 = false;
						bool reg_Pt14_Eta2 = false;
						bool reg_Pt15_Eta2 = false;								
						bool reg_Pt16_Eta2 = false;
								
						reg_Pt1_Eta1 = (photonPt->at(iPhoPos) > 35. && photonPt->at(iPhoPos) < 37.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt2_Eta1 = (photonPt->at(iPhoPos) > 37. && photonPt->at(iPhoPos) < 39.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt3_Eta1 = (photonPt->at(iPhoPos) > 39. && photonPt->at(iPhoPos) < 41.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt4_Eta1 = (photonPt->at(iPhoPos) > 41. && photonPt->at(iPhoPos) < 43.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt5_Eta1 = (photonPt->at(iPhoPos) > 43. && photonPt->at(iPhoPos) < 45.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt6_Eta1 = (photonPt->at(iPhoPos) > 45. && photonPt->at(iPhoPos) < 50.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt7_Eta1 = (photonPt->at(iPhoPos) > 50. && photonPt->at(iPhoPos) < 60.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt8_Eta1 = (photonPt->at(iPhoPos) > 60. && photonPt->at(iPhoPos) < 70.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt9_Eta1 = (photonPt->at(iPhoPos) > 70. && photonPt->at(iPhoPos) < 80.) && 
						               (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt10_Eta1 = (photonPt->at(iPhoPos) > 80. && photonPt->at(iPhoPos) < 90.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt11_Eta1 = (photonPt->at(iPhoPos) > 90. && photonPt->at(iPhoPos) < 100.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt12_Eta1 = (photonPt->at(iPhoPos) > 100. && photonPt->at(iPhoPos) < 150.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt13_Eta1 = (photonPt->at(iPhoPos) > 150. && photonPt->at(iPhoPos) < 200.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt14_Eta1 = (photonPt->at(iPhoPos) > 200. && photonPt->at(iPhoPos) < 300.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt15_Eta1 = (photonPt->at(iPhoPos) > 300. && photonPt->at(iPhoPos) < 500.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt16_Eta1 = (photonPt->at(iPhoPos) > 500. && photonPt->at(iPhoPos) < 1000.) && 
						                (abs(photonEta->at(iPhoPos)) < 1.5);

						reg_Pt1_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt2_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt3_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt4_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt5_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt6_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt7_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt8_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt9_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						               (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt10_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt11_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt12_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt13_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt14_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt15_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);

						reg_Pt16_Eta2 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 200) && 
						                (abs(photonEta->at(iPhoPos)) > 1.5 && abs(photonEta->at(iPhoPos)) < 2.5);


						if (reg_Pt1_Eta1) TeP_SF = 0.9746492;
						else if (reg_Pt2_Eta1) TeP_SF = 0.9628126;
						else if (reg_Pt3_Eta1) TeP_SF = 0.9692172;
						else if (reg_Pt4_Eta1) TeP_SF = 0.9691368;
						else if (reg_Pt5_Eta1) TeP_SF = 0.9724859;
						else if (reg_Pt6_Eta1) TeP_SF = 0.9761798;
						else if (reg_Pt7_Eta1) TeP_SF = 0.9656683;
						else if (reg_Pt8_Eta1) TeP_SF = 0.9699661;
						else if (reg_Pt9_Eta1) TeP_SF = 0.9877847;
						else if (reg_Pt10_Eta1) TeP_SF = 0.9851634;
						else if (reg_Pt11_Eta1) TeP_SF = 0.9913975;
						else if (reg_Pt12_Eta1) TeP_SF = 0.9747586;
						else if (reg_Pt13_Eta1) TeP_SF = 0.9704033;
						else if (reg_Pt14_Eta1) TeP_SF = 0.965103;
						else if (reg_Pt15_Eta1) TeP_SF = 1.010107;
						else if (reg_Pt16_Eta1) TeP_SF = 1.008818;

						else if (reg_Pt1_Eta2) TeP_SF = 0.9794486;
						else if (reg_Pt2_Eta2) TeP_SF = 0.9839308;
						else if (reg_Pt3_Eta2) TeP_SF = 0.9836198;
						else if (reg_Pt4_Eta2) TeP_SF = 0.9832776;
						else if (reg_Pt5_Eta2) TeP_SF = 0.9798149;
						else if (reg_Pt6_Eta2) TeP_SF = 0.9827082;
						else if (reg_Pt7_Eta2) TeP_SF = 0.9937122;
						else if (reg_Pt8_Eta2) TeP_SF = 0.9990523;
						else if (reg_Pt9_Eta2) TeP_SF = 1.011939;
						else if (reg_Pt10_Eta2) TeP_SF = 1.004887;
						else if (reg_Pt11_Eta2) TeP_SF = 0.9614111;
						else if (reg_Pt12_Eta2) TeP_SF = 0.9437025;
						else if (reg_Pt13_Eta2) TeP_SF = 0.9266722;
						else if (reg_Pt14_Eta2) TeP_SF = 0.9656222;
						else if (reg_Pt15_Eta2) TeP_SF = 0.6447101;
						else if (reg_Pt16_Eta2) TeP_SF = 0.9;
								
						else TeP_SF = 1.;
					}
				}
				else TeP_SF = 1.;
				
				photonTeP_SF.push_back(TeP_SF);
				// end T&P scale factors - definitions

			}
		}	// end Efficiency corrections


		// SelectedPhotons collection selection
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {

			SelectedPhotons_N = 0;					 

			for(unsigned int iPhoPos = 0; iPhoPos < photonPt->size(); iPhoPos++) {

				// Rho corrected PF isolation variables - definitions
				bool bin_RhoCorr_Eta01 = false;
				bool bin_RhoCorr_Eta02 = false;
				bool bin_RhoCorr_Eta03 = false;
				bool bin_RhoCorr_Eta04 = false;
				bool bin_RhoCorr_Eta05 = false;	
				bool bin_RhoCorr_Eta06 = false;									

				bin_RhoCorr_Eta01 = abs(photonEta->at(iPhoPos)) < 1.0;
				bin_RhoCorr_Eta02 = abs(photonEta->at(iPhoPos)) >= 1.0 && abs(photonEta->at(iPhoPos)) < 1.479;
				bin_RhoCorr_Eta03 = abs(photonEta->at(iPhoPos)) >= 1.479 && abs(photonEta->at(iPhoPos)) < 2.0;
				bin_RhoCorr_Eta04 = abs(photonEta->at(iPhoPos)) >= 2.0 && abs(photonEta->at(iPhoPos)) < 2.2;
				bin_RhoCorr_Eta05 = abs(photonEta->at(iPhoPos)) >= 2.2 && abs(photonEta->at(iPhoPos)) < 2.3;
				bin_RhoCorr_Eta06 = abs(photonEta->at(iPhoPos)) >= 2.3 && abs(photonEta->at(iPhoPos)) < 2.4;							

				double EA_CH, EA_NH, EA_Ph;
					
				if (bin_RhoCorr_Eta01) {
					 EA_CH = 0.012;
					 EA_NH = 0.030;
					 EA_Ph = 0.148;
				}
				else if (bin_RhoCorr_Eta02) {
					 EA_CH = 0.010;
					 EA_NH = 0.057;
					 EA_Ph = 0.130;
				}
				else if (bin_RhoCorr_Eta03) {
					 EA_CH = 0.014;
					 EA_NH = 0.039;
					 EA_Ph = 0.112;
				}
				else if (bin_RhoCorr_Eta04) {
					 EA_CH = 0.012;
					 EA_NH = 0.015;
					 EA_Ph = 0.216;	
				}
				else if (bin_RhoCorr_Eta05) {
					 EA_CH = 0.016;
					 EA_NH = 0.024;
					 EA_Ph = 0.262;	
				}
				else if (bin_RhoCorr_Eta06) {
					 EA_CH = 0.020;
					 EA_NH = 0.039;
					 EA_Ph = 0.260; 	
				}
				else {
					 EA_CH = 0.012;
					 EA_NH = 0.072;
					 EA_Ph = 0.266; 
				}
					
				photonPfIsoChargedHad_RhoCorr = 0;
				photonPfIsoNeutralHad_RhoCorr = 0;
				photonPfIsoPhoton_RhoCorr = 0;
				photonPfIsoChargedHad_RhoCorr = max(photonPfIsoChargedHad->at(iPhoPos) - rho*EA_CH, 0.);
				photonPfIsoNeutralHad_RhoCorr = max(photonPfIsoNeutralHad->at(iPhoPos) - rho*EA_NH, 0.);
				photonPfIsoPhoton_RhoCorr = max(photonPfIsoPhoton->at(iPhoPos) - rho*EA_Ph, 0.);
				// end Rho corrected PF isolation variables - definitions

				// photon quality selection - definitions
				bool PassConversionVeto = false;
				bool hadronicOverEm2012 = false;
				bool sigmaietaieta = false;
				bool iso_CH = false;
				bool iso_NH = false;
				bool iso_Ph = false;

				if (photonPassConversionVeto->at(iPhoPos) == 1) PassConversionVeto = true;
				else PassConversionVeto = false;
				if (photonid_hadronicOverEm2012->at(iPhoPos) < 0.05) hadronicOverEm2012 = true;
				else hadronicOverEm2012 = false;
				
				if (geo == "barrel") {
					if (photonid_sieie->at(iPhoPos) < 0.011) sigmaietaieta = true;
					else sigmaietaieta = false;

					if(photonPfIsoChargedHad_RhoCorr < 1.5) iso_CH = true;
					else iso_CH = false;
					if(photonPfIsoNeutralHad_RhoCorr < (1.0 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
					else iso_NH = false;
					if(photonPfIsoPhoton_RhoCorr < (0.7 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
					else iso_Ph = false;
				}

				else if (geo == "endcaps"){
					if (photonid_sieie->at(iPhoPos) < 0.033) sigmaietaieta = true;
					else sigmaietaieta = false;

					if(photonPfIsoChargedHad_RhoCorr < 1.2) iso_CH = true;
					else iso_CH = false;
					if(photonPfIsoNeutralHad_RhoCorr < (1.5 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
					else iso_NH = false;
					if(photonPfIsoPhoton_RhoCorr < (1.0 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
					else iso_Ph = false;
				}

				else {
					cout << "ERROR: Wrong geometry string written (only barrel or endcaps)" << endl;
				} 
				// end photon quality selection - definitions

				// Cut Based Photon 2012 - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
				bool geo_quality_sel = false;
				
				if(PassConversionVeto){ 
					if(hadronicOverEm2012){
						if (sigmaietaieta) {
							if (iso_CH) {
								if (iso_NH) {
									if (iso_Ph) {

										geo_quality_sel = true;
									}
								}
							}			
						}
					}
				}
				// end Cut Based Photon 2012 - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012

				// photon quality selection
				if(geo_quality_sel){ 

					// eta - definition
					// (photonBit |= (it->isEB() << 0) => (*photonBit)[0]&1) with 2^0 = 1
					bool geo_sel = false;
					if (geo == "barrel") {
						geo_sel = photonBit->at(iPhoPos)&1;
					}
					else if (geo == "endcaps"){
						geo_sel = photonBit->at(iPhoPos)&2;
					}
					else {
						cout << "Error: Wrong geometry string written" << endl;
					} // end eta - definition

					// photon kinematic selection
					if (photonPt->at(iPhoPos) > 0. && geo_sel) {

						SelectedPhotons_Pt.push_back(photonPt->at(iPhoPos));
						SelectedPhotons_Eta.push_back(photonEta->at(iPhoPos)); 
						SelectedPhotons_Phi.push_back(photonPhi->at(iPhoPos));
						SelectedPhotons_TeP_SF.push_back(photonTeP_SF.at(iPhoPos));
						SelectedPhotons_N+=1;

						// photon trigger matching selection
						bool TriMatchF4Path_sel_1 = photonTriMatchF4Path_sel_1.at(iPhoPos);
						bool TriMatchF4Path_sel_2 = photonTriMatchF4Path_sel_2.at(iPhoPos);
						bool TriMatchF4Path_sel_4 = photonTriMatchF4Path_sel_4.at(iPhoPos);	
						bool TriMatchF4Path_sel_8 = photonTriMatchF4Path_sel_8.at(iPhoPos);
						bool TriMatchF4Path_sel_16 = photonTriMatchF4Path_sel_16.at(iPhoPos);
						bool TriMatchF4Path_sel_32 = photonTriMatchF4Path_sel_32.at(iPhoPos);
						bool TriMatchF4Path_sel_64 = photonTriMatchF4Path_sel_64.at(iPhoPos);
						bool TriMatchF4Path_sel_128 = photonTriMatchF4Path_sel_128.at(iPhoPos);																								
						bool TriMatchF4Path_sel_256 = photonTriMatchF4Path_sel_256.at(iPhoPos);
						bool TriMatchF4Path_sel_512 = photonTriMatchF4Path_sel_512.at(iPhoPos);
						bool TriMatchF4Path_sel_1024 = photonTriMatchF4Path_sel_1024.at(iPhoPos);
						bool TriMatchF4Path_sel_2048 = photonTriMatchF4Path_sel_2048.at(iPhoPos);
						bool TriMatchF4Path_sel_4096 = photonTriMatchF4Path_sel_4096.at(iPhoPos);

						if (TriMatchF4Path_sel_1) {
							SelectedPhotons_Pt_sel_1.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_1.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_1.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_1.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_1+=1;
						} 

						if (TriMatchF4Path_sel_2) {
							SelectedPhotons_Pt_sel_2.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_2.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_2.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_2.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_2+=1;
						} 
						
						if (TriMatchF4Path_sel_4) {
							SelectedPhotons_Pt_sel_4.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_4.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_4.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_4.push_back(photonTeP_SF.at(iPhoPos));							
							SelectedPhotons_N_sel_4+=1;
						} 

						if (TriMatchF4Path_sel_8) {
							SelectedPhotons_Pt_sel_8.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_8.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_8.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_8.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_8+=1;
						} 

						if (TriMatchF4Path_sel_16) {
							SelectedPhotons_Pt_sel_16.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_16.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_16.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_16.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_16+=1;
						} 

						if (TriMatchF4Path_sel_32) {
							SelectedPhotons_Pt_sel_32.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_32.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_32.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_32.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_32+=1;
						} 

						if (TriMatchF4Path_sel_64) {
							SelectedPhotons_Pt_sel_64.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_64.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_64.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_64.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_64+=1;
						} 
					
						if (TriMatchF4Path_sel_128) {
							SelectedPhotons_Pt_sel_128.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_128.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_128.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_128.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_128+=1;
						} 

						if (TriMatchF4Path_sel_256) {
							SelectedPhotons_Pt_sel_256.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_256.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_256.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_256.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_256+=1;
						} 

						if (TriMatchF4Path_sel_512) {
							SelectedPhotons_Pt_sel_512.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_512.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_512.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_512.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_512+=1;
						} 

						if (TriMatchF4Path_sel_1024) {
							SelectedPhotons_Pt_sel_1024.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_1024.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_1024.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_1024.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_1024+=1;
						} 

						if (TriMatchF4Path_sel_2048) {
							SelectedPhotons_Pt_sel_2048.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_2048.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_2048.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_2048.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_2048+=1;
						} 

						if (TriMatchF4Path_sel_4096) {
							SelectedPhotons_Pt_sel_4096.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_Eta_sel_4096.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi_sel_4096.push_back(photonPhi->at(iPhoPos));
							SelectedPhotons_TeP_SF_sel_4096.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_N_sel_4096+=1;
						} 

					}	// end photon kinematic selection
				}	// end photon quality selection
			} 
		} // end SelectedPhotons collection selection

			

		// jetVeto: jets vs. SelectedPhotons 
		if(SelectedPhotons_N > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt.push_back(jetPt->at(iJetPos));
							SelectedJets_N+= 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons
			}
		} // jetVeto: jets vs. SelectedPhotons


		// jetVeto: jets vs. SelectedPhotons_sel_1
		if(SelectedPhotons_N_sel_1 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_1 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_1
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_1.at(0), SelectedPhotons_Phi_sel_1.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_1.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_1 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_1
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_1


		// jetVeto: jets vs. SelectedPhotons_sel_2 
		if(SelectedPhotons_N_sel_2 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_2 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_2
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_2.at(0), SelectedPhotons_Phi_sel_2.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {

							SelectedJets_Pt_sel_2.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_2 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_2
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_2


		// jetVeto: jets vs. SelectedPhotons_sel_4 
		if(SelectedPhotons_N_sel_4 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_4 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_4
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_4.at(0), SelectedPhotons_Phi_sel_4.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_4.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_4 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_4
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_4



		// jetVeto: jets vs. SelectedPhotons_sel_8
		if(SelectedPhotons_N_sel_8 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_8 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_8
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_8.at(0), SelectedPhotons_Phi_sel_8.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_8.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_8 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_8
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_8



		// jetVeto: jets vs. SelectedPhotons_sel_16 
		if(SelectedPhotons_N_sel_16 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_16 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_16
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_16.at(0), SelectedPhotons_Phi_sel_16.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_16.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_16 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_16
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_16



		// jetVeto: jets vs. SelectedPhotons_sel_32
		if(SelectedPhotons_N_sel_32 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_32 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_32
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_32.at(0), SelectedPhotons_Phi_sel_32.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_32.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_32 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_32
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_32


		// jetVeto: jets vs. SelectedPhotons_sel_64 
		if(SelectedPhotons_N_sel_64 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_64 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_64
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_64.at(0), SelectedPhotons_Phi_sel_64.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_64.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_64 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_64
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_64


		// jetVeto: jets vs. SelectedPhotons_sel_128
		if(SelectedPhotons_N_sel_128 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_128 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_128
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_128.at(0), SelectedPhotons_Phi_sel_128.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_128.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_128 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_128
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_128


		// jetVeto: jets vs. SelectedPhotons_sel_256
		if(SelectedPhotons_N_sel_256 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_256 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_256
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_256.at(0), SelectedPhotons_Phi_sel_256.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_256.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_256 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_256
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_256
		

		// jetVeto: jets vs. SelectedPhotons_sel_512 
		if(SelectedPhotons_N_sel_512 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_512 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_512
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_512.at(0), SelectedPhotons_Phi_sel_512.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_512.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_512 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_512
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_512
		
		

		// jetVeto: jets vs. SelectedPhotons_sel_1024
		if(SelectedPhotons_N_sel_1024 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_1024 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_1024
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_1024.at(0), SelectedPhotons_Phi_sel_1024.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_1024.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_1024 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_1024
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_1024
		
		

		// jetVeto: jets vs. SelectedPhotons_sel_2048
		if(SelectedPhotons_N_sel_2048 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_2048 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_2048
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_2048.at(0), SelectedPhotons_Phi_sel_2048.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_2048.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_2048 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_2048
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_2048
		
		

		// jetVeto: jets vs. SelectedPhotons_sel_4096 
		if(SelectedPhotons_N_sel_4096 > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJets_N_sel_4096 = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// selection of cleaned jets vs. LEADING SelectedPhotons_sel_4096
				bool closeLEA = false;
				if ( deltaR(SelectedPhotons_Eta_sel_4096.at(0), SelectedPhotons_Phi_sel_4096.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				if (!closeLEA){
											
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt_sel_4096.push_back(jetPt->at(iJetPos));
							SelectedJets_N_sel_4096 += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons_sel_4096
			}
		} // jetVeto: jets vs. SelectedPhotons_sel_4096


		// collectives jets properties
		SelectedJets_HT = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt.size(); zJetPos++) {
			SelectedJets_HT += SelectedJets_Pt.at(zJetPos);
		}

		SelectedJets_HT_sel_1 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_1.size(); zJetPos++) {
			SelectedJets_HT_sel_1 += SelectedJets_Pt_sel_1.at(zJetPos);
		}

		SelectedJets_HT_sel_2 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_2.size(); zJetPos++) {
			SelectedJets_HT_sel_2 += SelectedJets_Pt_sel_2.at(zJetPos);
		}

		SelectedJets_HT_sel_4 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_4.size(); zJetPos++) {
			SelectedJets_HT_sel_4 += SelectedJets_Pt_sel_4.at(zJetPos);
		}

		SelectedJets_HT_sel_8 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_8.size(); zJetPos++) {
			SelectedJets_HT_sel_8 += SelectedJets_Pt_sel_8.at(zJetPos);
		}

		SelectedJets_HT_sel_16 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_16.size(); zJetPos++) {
			SelectedJets_HT_sel_16 += SelectedJets_Pt_sel_16.at(zJetPos);
		}

		SelectedJets_HT_sel_32 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_32.size(); zJetPos++) {
			SelectedJets_HT_sel_32 += SelectedJets_Pt_sel_32.at(zJetPos);
		}

		SelectedJets_HT_sel_64 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_64.size(); zJetPos++) {
			SelectedJets_HT_sel_64 += SelectedJets_Pt_sel_64.at(zJetPos);
		}

		SelectedJets_HT_sel_128 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_128.size(); zJetPos++) {
			SelectedJets_HT_sel_128 += SelectedJets_Pt_sel_128.at(zJetPos);
		}

		SelectedJets_HT_sel_256 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_256.size(); zJetPos++) {
			SelectedJets_HT_sel_256 += SelectedJets_Pt_sel_256.at(zJetPos);
		}

		SelectedJets_HT_sel_512 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_512.size(); zJetPos++) {
			SelectedJets_HT_sel_512 += SelectedJets_Pt_sel_512.at(zJetPos);
		}

		SelectedJets_HT_sel_1024 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_1024.size(); zJetPos++) {
			SelectedJets_HT_sel_1024 += SelectedJets_Pt_sel_1024.at(zJetPos);
		}

		SelectedJets_HT_sel_2048 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_2048.size(); zJetPos++) {
			SelectedJets_HT_sel_2048 += SelectedJets_Pt_sel_2048.at(zJetPos);
		}

		SelectedJets_HT_sel_4096 = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt_sel_4096.size(); zJetPos++) {
			SelectedJets_HT_sel_4096 += SelectedJets_Pt_sel_4096.at(zJetPos);
		}
		// end collectives jets properties


		// scaling factors definitions
		if(SelectedPhotons_N > 0) {
			scale_TeP = SelectedPhotons_TeP_SF.at(0);
			weight_final = scale_TeP * weight_withPU;
		} 
		if(SelectedPhotons_N_sel_1 > 0) {
			scale_TeP_sel_1 = SelectedPhotons_TeP_SF_sel_1.at(0);
			weight_final_sel_1 = scale_TeP_sel_1 * weight_withPU;
		} 		
		if(SelectedPhotons_N_sel_2 > 0) {
			scale_TeP_sel_2 = SelectedPhotons_TeP_SF_sel_2.at(0);
			weight_final_sel_2 = scale_TeP_sel_2 * weight_withPU;
		} 		
		if(SelectedPhotons_N_sel_4 > 0) {
			scale_TeP_sel_4 = SelectedPhotons_TeP_SF_sel_4.at(0);
			weight_final_sel_4 = scale_TeP_sel_4 * weight_withPU;
		} 		
		if(SelectedPhotons_N_sel_8 > 0) {
			scale_TeP_sel_8 = SelectedPhotons_TeP_SF_sel_8.at(0);
			weight_final_sel_8 = scale_TeP_sel_8 * weight_withPU;
		} 		
		if(SelectedPhotons_N_sel_16 > 0) {
			scale_TeP_sel_16 = SelectedPhotons_TeP_SF_sel_16.at(0);
			weight_final_sel_16 = scale_TeP_sel_16 * weight_withPU;
		} 		
					if(SelectedPhotons_N_sel_32 > 0) {
			scale_TeP_sel_32 = SelectedPhotons_TeP_SF_sel_32.at(0);
			weight_final_sel_32 = scale_TeP_sel_32 * weight_withPU;
		} 			
		if(SelectedPhotons_N_sel_64 > 0) {
			scale_TeP_sel_64 = SelectedPhotons_TeP_SF_sel_64.at(0);
			weight_final_sel_64 = scale_TeP_sel_64 * weight_withPU;
		}
		if(SelectedPhotons_N_sel_128 > 0) {
			scale_TeP_sel_128 = SelectedPhotons_TeP_SF_sel_128.at(0);
			weight_final_sel_128 = scale_TeP_sel_128 * weight_withPU;
		} 
		if(SelectedPhotons_N_sel_256 > 0) {
			scale_TeP_sel_256 = SelectedPhotons_TeP_SF_sel_256.at(0);
			weight_final_sel_256 = scale_TeP_sel_256 * weight_withPU;
		} 				
		if(SelectedPhotons_N_sel_512 > 0) {
			scale_TeP_sel_512 = SelectedPhotons_TeP_SF_sel_512.at(0);
			weight_final_sel_512 = scale_TeP_sel_512 * weight_withPU;
		} 				
		if(SelectedPhotons_N_sel_4096 > 0) {
			scale_TeP_sel_4096 = SelectedPhotons_TeP_SF_sel_4096.at(0);
			weight_final_sel_4096 = scale_TeP_sel_4096 * weight_withPU;
		} 				
		if(SelectedPhotons_N_sel_1024 > 0) {
			scale_TeP_sel_1024 = SelectedPhotons_TeP_SF_sel_1024.at(0);
			weight_final_sel_1024 = scale_TeP_sel_1024 * weight_withPU;
		} 				
		if(SelectedPhotons_N_sel_2048 > 0) {
			scale_TeP_sel_2048 = SelectedPhotons_TeP_SF_sel_2048.at(0);
			weight_final_sel_2048 = scale_TeP_sel_2048 * weight_withPU;
		} 		
		// end scaling factors definitions


		// =========== Analysis selection
		
		// trigger family selection
		if ((1 & isTriggered) || (32 & isTriggered)) {

			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N > 0) {
						// HT selection
						if (SelectedJets_HT > 0){
							iSelected0++;

							SelectedPhotons_Pt_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
							
						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level

			
			// sel_1
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_1 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_1 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_1 > 0){
							iSelected1++;

							SelectedPhotons_Pt_1_sel_1_->Fill(SelectedPhotons_Pt_sel_1.at(0), weight_final_sel_1);
						
						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_1

			// sel_2
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_2 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_2 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_2 > 0){
							iSelected2++;

							SelectedPhotons_Pt_1_sel_2_->Fill(SelectedPhotons_Pt_sel_2.at(0), weight_final_sel_2);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_2

			// sel_4
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_4 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_4 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_4 > 0){
							iSelected3++;

							SelectedPhotons_Pt_1_sel_4_->Fill(SelectedPhotons_Pt_sel_4.at(0), weight_final_sel_4);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_4

			// sel_8
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_8 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_8 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_8 > 0){
							iSelected4++;

							SelectedPhotons_Pt_1_sel_8_->Fill(SelectedPhotons_Pt_sel_8.at(0), weight_final_sel_8);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_8

			// sel_16
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_16 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_16 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_16 > 0){
							iSelected5++;

							SelectedPhotons_Pt_1_sel_16_->Fill(SelectedPhotons_Pt_sel_16.at(0), weight_final_sel_16);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_16

			// sel_32
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_32 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_32 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_32 > 0){
							iSelected6++;

							SelectedPhotons_Pt_1_sel_32_->Fill(SelectedPhotons_Pt_sel_32.at(0), weight_final_sel_32);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_32

			// sel_64
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_64 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_64 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_64 > 0){
							iSelected7++;

							SelectedPhotons_Pt_1_sel_64_->Fill(SelectedPhotons_Pt_sel_64.at(0), weight_final_sel_64);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_64

			// sel_128
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_128 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_128 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_128 > 0){
							iSelected8++;

							SelectedPhotons_Pt_1_sel_128_->Fill(SelectedPhotons_Pt_sel_128.at(0), weight_final_sel_128);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_128

			// sel_256
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_256 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_256 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_256 > 0){
							iSelected9++;

							SelectedPhotons_Pt_1_sel_256_->Fill(SelectedPhotons_Pt_sel_256.at(0), weight_final_sel_256);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_256

			// sel_512
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_512 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_512 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_512 > 0){
							iSelected10++;

							SelectedPhotons_Pt_1_sel_512_->Fill(SelectedPhotons_Pt_sel_512.at(0), weight_final_sel_512);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_512

			// sel_1024
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_1024 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_1024 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_1024 > 0){
							iSelected11++;

							SelectedPhotons_Pt_1_sel_1024_->Fill(SelectedPhotons_Pt_sel_1024.at(0), weight_final_sel_1024);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_1024

			// sel_2048
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_2048 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_2048 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_2048 > 0){
							iSelected12++;

							SelectedPhotons_Pt_1_sel_2048_->Fill(SelectedPhotons_Pt_sel_2048.at(0), weight_final_sel_2048);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_2048

			// sel_4096
			// Isolation at GEN level
			if (isoGEN) {
				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N_sel_4096 > 0){
					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N_sel_4096 > 0) {
						// HT selection
						if (SelectedJets_HT_sel_4096 > 0){
							iSelected13++;

							SelectedPhotons_Pt_1_sel_4096_->Fill(SelectedPhotons_Pt_sel_4096.at(0), weight_final_sel_4096);

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
			// end sel_4096			
			
		}// end trigger family selection
		
		// clean jets
		SelectedJets_N = 0;
		SelectedJets_N_sel_1 = 0;
		SelectedJets_N_sel_2 = 0;
		SelectedJets_N_sel_4 = 0;
		SelectedJets_N_sel_8 = 0;
		SelectedJets_N_sel_16 = 0;
		SelectedJets_N_sel_32 = 0;
		SelectedJets_N_sel_64 = 0;
		SelectedJets_N_sel_128 = 0;
		SelectedJets_N_sel_256 = 0;
		SelectedJets_N_sel_512 = 0;
		SelectedJets_N_sel_1024 = 0;
		SelectedJets_N_sel_2048 = 0;
		SelectedJets_N_sel_4096 = 0;	

		SelectedJets_HT = 0;
		SelectedJets_HT_sel_1 = 0;
		SelectedJets_HT_sel_2 = 0;
		SelectedJets_HT_sel_4 = 0;
		SelectedJets_HT_sel_8 = 0;
		SelectedJets_HT_sel_16 = 0;
		SelectedJets_HT_sel_32 = 0;
		SelectedJets_HT_sel_64 = 0;
		SelectedJets_HT_sel_128 = 0;
		SelectedJets_HT_sel_256 = 0;
		SelectedJets_HT_sel_512 = 0;
		SelectedJets_HT_sel_1024 = 0;
		SelectedJets_HT_sel_2048 = 0;
		SelectedJets_HT_sel_4096 = 0;
				
		SelectedJets_Pt.clear();
		SelectedJets_Pt_sel_1.clear();
		SelectedJets_Pt_sel_2.clear();
		SelectedJets_Pt_sel_4.clear();
		SelectedJets_Pt_sel_8.clear();
		SelectedJets_Pt_sel_16.clear();
		SelectedJets_Pt_sel_32.clear();
		SelectedJets_Pt_sel_64.clear();
		SelectedJets_Pt_sel_128.clear();
		SelectedJets_Pt_sel_256.clear();
		SelectedJets_Pt_sel_512.clear();
		SelectedJets_Pt_sel_1024.clear();
		SelectedJets_Pt_sel_2048.clear();
		SelectedJets_Pt_sel_4096.clear();
		// end clean jets

		// clean photons
		SelectedPhotons_N = 0;
		SelectedPhotons_N_sel_1 = 0;
		SelectedPhotons_N_sel_2 = 0;
		SelectedPhotons_N_sel_4 = 0;
		SelectedPhotons_N_sel_8 = 0;
		SelectedPhotons_N_sel_16 = 0;
		SelectedPhotons_N_sel_32 = 0;
		SelectedPhotons_N_sel_64 = 0;
		SelectedPhotons_N_sel_128 = 0;
		SelectedPhotons_N_sel_256 = 0;
		SelectedPhotons_N_sel_512 = 0;
		SelectedPhotons_N_sel_1024 = 0;
		SelectedPhotons_N_sel_2048 = 0;
		SelectedPhotons_N_sel_4096 = 0;

		photonTriMatchF4Path_sel_1.clear();
		photonTriMatchF4Path_sel_2.clear();
		photonTriMatchF4Path_sel_4.clear();
		photonTriMatchF4Path_sel_8.clear();
		photonTriMatchF4Path_sel_16.clear();
		photonTriMatchF4Path_sel_32.clear();
		photonTriMatchF4Path_sel_64.clear();
		photonTriMatchF4Path_sel_128.clear();
		photonTriMatchF4Path_sel_256.clear();
		photonTriMatchF4Path_sel_512.clear();
		photonTriMatchF4Path_sel_1024.clear();		
		photonTriMatchF4Path_sel_2048.clear();		
		photonTriMatchF4Path_sel_4096.clear();
						
		photonTeP_SF.clear();

		SelectedPhotons_Pt.clear();
		SelectedPhotons_Pt_sel_1.clear();
		SelectedPhotons_Pt_sel_2.clear();
		SelectedPhotons_Pt_sel_4.clear();
		SelectedPhotons_Pt_sel_8.clear();
		SelectedPhotons_Pt_sel_16.clear();
		SelectedPhotons_Pt_sel_32.clear();
		SelectedPhotons_Pt_sel_64.clear();
		SelectedPhotons_Pt_sel_128.clear();
		SelectedPhotons_Pt_sel_256.clear();
		SelectedPhotons_Pt_sel_512.clear();
		SelectedPhotons_Pt_sel_1024.clear();
		SelectedPhotons_Pt_sel_2048.clear();
		SelectedPhotons_Pt_sel_4096.clear();

		SelectedPhotons_Eta.clear();
		SelectedPhotons_Eta_sel_1.clear();
		SelectedPhotons_Eta_sel_2.clear();
		SelectedPhotons_Eta_sel_4.clear();
		SelectedPhotons_Eta_sel_8.clear();
		SelectedPhotons_Eta_sel_16.clear();
		SelectedPhotons_Eta_sel_32.clear();
		SelectedPhotons_Eta_sel_64.clear();
		SelectedPhotons_Eta_sel_128.clear();
		SelectedPhotons_Eta_sel_256.clear();
		SelectedPhotons_Eta_sel_512.clear();
		SelectedPhotons_Eta_sel_1024.clear();
		SelectedPhotons_Eta_sel_2048.clear();
		SelectedPhotons_Eta_sel_4096.clear();

		SelectedPhotons_Phi.clear();
		SelectedPhotons_Phi_sel_1.clear();
		SelectedPhotons_Phi_sel_2.clear();
		SelectedPhotons_Phi_sel_4.clear();
		SelectedPhotons_Phi_sel_8.clear();
		SelectedPhotons_Phi_sel_16.clear();
		SelectedPhotons_Phi_sel_32.clear();
		SelectedPhotons_Phi_sel_64.clear();
		SelectedPhotons_Phi_sel_128.clear();
		SelectedPhotons_Phi_sel_256.clear();
		SelectedPhotons_Phi_sel_512.clear();
		SelectedPhotons_Phi_sel_1024.clear();
		SelectedPhotons_Phi_sel_2048.clear();
		SelectedPhotons_Phi_sel_4096.clear();

		SelectedPhotons_TeP_SF.clear();
		SelectedPhotons_TeP_SF_sel_1.clear();
		SelectedPhotons_TeP_SF_sel_2.clear();
		SelectedPhotons_TeP_SF_sel_4.clear();
		SelectedPhotons_TeP_SF_sel_8.clear();
		SelectedPhotons_TeP_SF_sel_16.clear();
		SelectedPhotons_TeP_SF_sel_32.clear();
		SelectedPhotons_TeP_SF_sel_64.clear();
		SelectedPhotons_TeP_SF_sel_128.clear();
		SelectedPhotons_TeP_SF_sel_256.clear();
		SelectedPhotons_TeP_SF_sel_512.clear();
		SelectedPhotons_TeP_SF_sel_1024.clear();
		SelectedPhotons_TeP_SF_sel_2048.clear();
		SelectedPhotons_TeP_SF_sel_4096.clear();
		// end clean photons
			 
		// if (Cut(ientry) < 0) continue;
	} // end loop on entries

	// ====================================terminate and plot

	cout << "Analysis selection:" << endl;
	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	cout << "Number of selected events 0 no Trigger Matching, unweighted = " << iSelected0 << endl;
	cout << "Number of selected events 1: Trigger Matching 1, unweighted = " << iSelected1 << endl;
	cout << "Number of selected events 2: Trigger Matching 2, unweighted = " << iSelected2 << endl;
	cout << "Number of selected events 3: Trigger Matching 4, unweighted = " << iSelected3 << endl;
	cout << "Number of selected events 4: Trigger Matching 8, unweighted = " << iSelected4 << endl;			
	cout << "Number of selected events 5: Trigger Matching 16, unweighted = " << iSelected5 << endl;
	cout << "Number of selected events 6: Trigger Matching 32, unweighted = " << iSelected6 << endl;
	cout << "Number of selected events 7: Trigger Matching 64, unweighted = " << iSelected7 << endl;
	cout << "Number of selected events 8: Trigger Matching 128, unweighted = " << iSelected8 << endl;
	cout << "Number of selected events 9: Trigger Matching 256, unweighted = " << iSelected9 << endl;
	cout << "Number of selected events 10: Trigger Matching 512, unweighted = " << iSelected10 << endl;
	cout << "Number of selected events 11: Trigger Matching 1024, unweighted = " << iSelected11 << endl;
	cout << "Number of selected events 12: Trigger Matching 2048, unweighted = " << iSelected12 << endl;
	cout << "Number of selected events 13: Trigger Matching 4096, unweighted = " << iSelected13 << endl;

	fhistos->Write();

	if (plothistos){
		Plot_Histos();
	}
	if (textfile){
		Text_File();
	}
}


// ----- methods ----------------

void TurnOn::Book_Histos(){

	cout << "Booking histograms... " << endl;
	// book the histograms

	//plotsCompare_01
	SelectedPhotons_Pt_1_ = new TH1F("SelectedPhotons_Pt_1_","Photon p_{T} ", 800, 0., 4000.);
	
	SelectedPhotons_Pt_1_sel_1_ = new TH1F("SelectedPhotons_Pt_1_sel_1_","Photon p_{T}: Trigger Matching path 1", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_2_ = new TH1F("SelectedPhotons_Pt_1_sel_2_","Photon p_{T}: Trigger Matching path 2", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_4_ = new TH1F("SelectedPhotons_Pt_1_sel_4_","Photon p_{T}: Trigger Matching path 4", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_8_ = new TH1F("SelectedPhotons_Pt_1_sel_8_","Photon p_{T}: Trigger Matching path 8", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_16_ = new TH1F("SelectedPhotons_Pt_1_sel_16_","Photon p_{T}: Trigger Matching path 16", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_32_ = new TH1F("SelectedPhotons_Pt_1_sel_32_","Photon p_{T}: Trigger Matching path 32", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_64_ = new TH1F("SelectedPhotons_Pt_1_sel_64_","Photon p_{T}: Trigger Matching path 64", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_128_ = new TH1F("SelectedPhotons_Pt_1_sel_128_","Photon p_{T}: Trigger Matching path 128", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_256_ = new TH1F("SelectedPhotons_Pt_1_sel_256_","Photon p_{T}: Trigger Matching path 256", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_512_ = new TH1F("SelectedPhotons_Pt_1_sel_512_","Photon p_{T}: Trigger Matching path 512", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_1024_ = new TH1F("SelectedPhotons_Pt_1_sel_1024_","Photon p_{T}: Trigger Matching path 1024", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_2048_ = new TH1F("SelectedPhotons_Pt_1_sel_2048_","Photon p_{T}: Trigger Matching path 2048", 800, 0., 4000.);
	SelectedPhotons_Pt_1_sel_4096_ = new TH1F("SelectedPhotons_Pt_1_sel_4096_","Photon p_{T}: Trigger Matching path 4096", 800, 0., 4000.);

	cout << "...booking histograms finished." << endl;
}


void TurnOn::Plot_Histos(){

	// plot few histograms at the end, for check
	cout << "Plots: quick check... " << endl;


	bool plot_01 = true; // photon p_T

	gStyle->SetOptStat(1111111);

	if(plot_01){
		TCanvas *c01 = new TCanvas("c01", "photon kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c01->Divide(5,3);
		c01->cd(1);
		SelectedPhotons_Pt_1_->Draw();
		c01->cd(2);
		SelectedPhotons_Pt_1_sel_1_->Draw();
		c01->cd(3);
		SelectedPhotons_Pt_1_sel_2_->Draw();
		c01->cd(4);
		SelectedPhotons_Pt_1_sel_4_->Draw();
		c01->cd(5);
		SelectedPhotons_Pt_1_sel_8_->Draw();
		c01->cd(6);		
		SelectedPhotons_Pt_1_sel_16_->Draw();
		c01->cd(7);
		SelectedPhotons_Pt_1_sel_32_->Draw();
		c01->cd(8);
		SelectedPhotons_Pt_1_sel_64_->Draw();
		c01->cd(9);
		SelectedPhotons_Pt_1_sel_128_->Draw();
		c01->cd(10);
		SelectedPhotons_Pt_1_sel_256_->Draw();
		c01->cd(11);
		SelectedPhotons_Pt_1_sel_512_->Draw();
		c01->cd(12);
		SelectedPhotons_Pt_1_sel_1024_->Draw();	
		c01->cd(13);
		SelectedPhotons_Pt_1_sel_2048_->Draw();	
		c01->cd(14);
		SelectedPhotons_Pt_1_sel_4096_->Draw();	
	}

	cout << "...plots: quick check finished. " << endl;
	
}



void Zero_Variables(){
}


void TurnOn::Text_File(){

	cout << "Writing text file... " << endl;
	ofstream text;
	text.open(textname);
	text << "Running on " << sample_r << endl;
	text << "Weight is " << weight_r << endl;
	text << "Analysis selection:" << endl;
	text << "Number of selected events 0 no Trigger Matching, unweighted = " << iSelected0 << endl;
	text << "Number of selected events 1: Trigger Matching 1, unweighted = " << iSelected1 << endl;
	text << "Number of selected events 2: Trigger Matching 2, unweighted = " << iSelected2 << endl;
	text << "Number of selected events 3: Trigger Matching 4, unweighted = " << iSelected3 << endl;
	text << "Number of selected events 4: Trigger Matching 8, unweighted = " << iSelected4 << endl;			
	text << "Number of selected events 5: Trigger Matching 16, unweighted = " << iSelected5 << endl;
	text << "Number of selected events 6: Trigger Matching 32, unweighted = " << iSelected6 << endl;
	text << "Number of selected events 7: Trigger Matching 64, unweighted = " << iSelected7 << endl;
	text << "Number of selected events 8: Trigger Matching 128, unweighted = " << iSelected8 << endl;
	text << "Number of selected events 9: Trigger Matching 256, unweighted = " << iSelected9 << endl;
	text << "Number of selected events 10: Trigger Matching 512, unweighted = " << iSelected10 << endl;
	text << "Number of selected events 11: Trigger Matching 1024, unweighted = " << iSelected11 << endl;
	text << "Number of selected events 12: Trigger Matching 2048, unweighted = " << iSelected12 << endl;
	text << "Number of selected events 13: Trigger Matching 4096, unweighted = " << iSelected13 << endl;
	text.close();
	text << "...writing text file finished. " << endl;
	}
