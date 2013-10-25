#define GJetsAnalyzer_cxx
#include "GJetsAnalyzer.h"
#include "GJetsDefs.h"
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

#include <DataFormats/Math/interface/deltaPhi.h>
#include <DataFormats/Math/interface/deltaR.h>
#include <TLorentzVector.h>
#include <../../../QCDAnalysis/Tools/interface/EventShapeLorentz.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "FWCore/Utilities/interface/Exception.h"
#endif


//#ifdef __MAKECINT__
//#pragma link C++ class vector<float>+;
//#endif

//		In a ROOT session, you can do:
//			Root > .L GJetsAnalyzer.C++
//			Root > GJetsAnalyzer t(0,4); // Load the analysis on the sample number 4 
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


void GJetsAnalyzer::Loop(){


	// ==================================== choose the tools
	
	bool RedAn = false;								// analysis with a reduced entries number for tests

	bool data_ReReco = true;					// analysis with data ReReco or data PromptReco
	string geo = "barrel";						// barrel or endcaps
	bool SigBack = true;							// to avoid double counting for SIGNAL and BACKGROUND
	bool TeP_corr = true;							// T&P correction
	bool BackDataDriven_corr = false;	// background data-driven correction

	bool RandomCone = false;					// Random Cone data-driven or MC signal template
	bool inv_sigmaietaieta = false;		// inverted sigmaietaieta cut
	bool inv_isolation = false;				// inverted isolation set cut
		
	bool plothistos = false;					// please select which plots to show
	bool textfile = true;							// if you want a text report for each sample
	Int_t itype = 1;									// it identifies histos with different analysis 

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

	if (inv_sigmaietaieta && inv_isolation){
		cout << "ERROR: you are trying to invert both SIGMAIETAIETA and ISOLATION cuts" << endl << endl;
		throw cms::Exception("WrongBool");
	}
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
	Float_t prescale_Tri = 1.;
	Float_t scale_TeP = 1.;
	Float_t scale_BackDataDriven = 1.;	
	Float_t weight_final = 1;

	double fCut_eta_central = 150894; 	//since the Z can be also forward if the momenta of the leptons are added up - choose a very big value

	string geo_s = geo + "/";
	string sample = "";
	string out_files = "output_files/";
	string histos = "_histos_%d_";
	string report = "_report_%d_";
	string root = ".root";
	string txt = ".txt";
	string inverted = "_inv";
	string sigmaietaieta_s = "_sigmaietaieta";
	string isolation_s = "_isolation";
	if (inv_sigmaietaieta && !inv_isolation){
		root = inverted + sigmaietaieta_s + root;
		txt = inverted + sigmaietaieta_s + txt;
	}	
	else if (!inv_sigmaietaieta && inv_isolation){
		root = inverted + isolation_s + root;
		txt = inverted + isolation_s + txt;
	}	
	else {
		root = root;
		txt = txt;
	}
				
	cout << "Analysis on " << geo << endl;
	if (inv_sigmaietaieta && !inv_isolation) {
		cout << "with inverted sigmaietaieta cut" << endl;
		cout << endl;
	}	
	else if (!inv_sigmaietaieta && inv_isolation) {
		cout << "with inverted isolation cuts" << endl;
		cout << endl;
	}	
	else {
		cout << endl;
	}
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

		// ==================================== unfolding

		bool unf_selGEN_N0 = false;
		bool unf_selGEN_excl1 = false;
		bool unf_selGEN_excl2 = false;				
		bool unf_selGEN_N1 = false;
		bool unf_selGEN_N2 = false;

		unf_photonPtGEN_N0 = 0;
		unf_SelectedJetsGEN_N_N0 = 0;
		unf_SelectedJetsGEN_HT_N0 = 0;

		unf_photonPtGEN_excl1 = 0;
		unf_SelectedJetsGEN_N_excl1 = 0;
		unf_SelectedJetsGEN_HT_excl1 = 0;

		unf_photonPtGEN_excl2 = 0;
		unf_SelectedJetsGEN_N_excl2 = 0;
		unf_SelectedJetsGEN_HT_excl2 = 0;

		unf_photonPtGEN_N1 = 0;
		unf_SelectedJetsGEN_N_N1 = 0;
		unf_SelectedJetsGEN_HT_N1 = 0;		

		unf_photonPtGEN_N2 = 0;
		unf_SelectedJetsGEN_N_N2 = 0;
		unf_SelectedJetsGEN_HT_N2 = 0;				

		bool unf_selREC_N0 = false;
		bool unf_selREC_excl1 = false;
		bool unf_selREC_excl2 = false;				
		bool unf_selREC_N1 = false;
		bool unf_selREC_N2 = false;

		unf_SelectedPhotons_Pt_N0_1 = 0;
		unf_SelectedJets_N_N0 = 0;
		unf_SelectedJets_HT_N0 = 0;

		unf_SelectedPhotons_Pt_excl1_1 = 0;
		unf_SelectedJets_N_excl1 = 0;
		unf_SelectedJets_HT_excl1 = 0;

		unf_SelectedPhotons_Pt_excl2_1 = 0;
		unf_SelectedJets_N_excl2 = 0;
		unf_SelectedJets_HT_excl2 = 0;

		unf_SelectedPhotons_Pt_N1_1 = 0;
		unf_SelectedJets_N_N1 = 0;
		unf_SelectedJets_HT_N1 = 0;		

		unf_SelectedPhotons_Pt_N2_1 = 0;
		unf_SelectedJets_N_N2 = 0;
		unf_SelectedJets_HT_N2 = 0;				

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


		// ==================================== GEN selection

		// MC selection for GEN
		if (isMC){

			// jetVeto: jetsGEN vs. PhotonGEN 
			if(nPhotonsGEN > 0 && (nJetsGEN > 0 && (nJetsGEN == (int)jetPtGEN->size())) ){

				SelectedJetsGEN_N = 0;

				for (unsigned int iJetGENPos = 0; iJetGENPos < jetPtGEN->size(); iJetGENPos++) {

					// selection of cleaned jets vs. PhotonGEN
					bool closeGEN = false;
					if ( deltaR(photonEtaGEN, photonPhiGEN, jetEtaGEN->at(iJetGENPos), jetPhiGEN->at(iJetGENPos)) < 0.5 ) {
						closeGEN = true;
					}
					if (!closeGEN){

						// jets kinematic selection
						if(jetPtGEN->at(iJetGENPos) > 30. && TMath::Abs(jetEtaGEN->at(iJetGENPos)) < 2.5 ){
							SelectedJetsGEN_Pt.push_back(jetPtGEN->at(iJetGENPos));
							SelectedJetsGEN_E.push_back(jetEGEN->at(iJetGENPos));
							SelectedJetsGEN_Eta.push_back(jetEtaGEN->at(iJetGENPos));
							SelectedJetsGEN_Phi.push_back(jetPhiGEN->at(iJetGENPos));
							SelectedJetsGEN_N += 1;
						} // end jets kinematic selection
					} // end selection of cleaned jets vs. PhotonGEN
				}
			} // end jetVeto: jetsGEN vs. PhotonGEN

			// collectives jetsGEN properties
			SelectedJetsGEN_HT = 0;
			for(unsigned int zJetGENPos = 0; zJetGENPos < SelectedJetsGEN_Pt.size(); zJetGENPos++) {
				SelectedJetsGEN_HT += SelectedJetsGEN_Pt.at(zJetGENPos);
			} // end collectives jetsGEN properties


			// isolation at GEN level
			if (isoGEN) {

				// photonGEN selection
				if (nPhotonsGEN > 0){

					// eta - definition
					bool geo_selGEN = false;
					if (geo == "barrel") {
						geo_selGEN = TMath::Abs(photonEtaGEN) < 1.479;
					}
					else if (geo == "endcaps"){
						geo_selGEN = TMath::Abs(photonEtaGEN) > 1.479 && TMath::Abs(photonEtaGEN) < 3.;
					}
					else {
						cout << "ERROR: Wrong geometry string written (only barrel or endcaps)" << endl;
					} // end eta - definition

					// photonGEN kinematic selection
					if (photonPtGEN > 100. && geo_selGEN) {
					// if (photonPtGEN > 0. && geo_selGEN) {          // for Z/gamma GEN ratio  
					
						// kin JetsGEN (cleaned vs. photonGEN) selection
						if (SelectedJetsGEN_N > 0){

							// HTGEN selection
							if (SelectedJetsGEN_HT > 0){
								unf_selGEN_N0 = true;

								nPhotonsGEN_N0_->Fill(nPhotonsGEN, weight_withPU);
								
								photonPtGEN_N0_->Fill(photonPtGEN, weight_withPU);
								photonEGEN_N0_->Fill(photonEGEN, weight_withPU);
								photonEtaGEN_N0_->Fill(photonEtaGEN, weight_withPU);
								photonPhiGEN_N0_->Fill(photonPhiGEN, weight_withPU);

								SelectedJetsGEN_N_N0_->Fill(SelectedJetsGEN_N, weight_withPU);

								SelectedJets_PtGEN_N0_1_->Fill(SelectedJetsGEN_Pt.at(0), weight_withPU);
								SelectedJets_EGEN_N0_1_->Fill(SelectedJetsGEN_E.at(0), weight_withPU);
								SelectedJets_EtaGEN_N0_1_->Fill(SelectedJetsGEN_Eta.at(0), weight_withPU);
								SelectedJets_PhiGEN_N0_1_->Fill(SelectedJetsGEN_Phi.at(0), weight_withPU);
								
								SelectedJetsGEN_HT_N0_->Fill(SelectedJetsGEN_HT, weight_withPU);

								if(Sig){
									unf_photonPtGEN_N0 = photonPtGEN;
									unf_SelectedJetsGEN_N_N0 = SelectedJetsGEN_N;
									unf_SelectedJetsGEN_HT_N0 = SelectedJetsGEN_HT;
								}
															
								if (SelectedJetsGEN_N == 1){
									unf_selGEN_excl1 = true;
									photonPtGEN_excl1_->Fill(photonPtGEN, weight_withPU);
									if(Sig){
										unf_photonPtGEN_excl1 = photonPtGEN;
										unf_SelectedJetsGEN_N_excl1 = SelectedJetsGEN_N;
										unf_SelectedJetsGEN_HT_excl1 = SelectedJetsGEN_HT;
									}
								}
								
								if (SelectedJetsGEN_N == 2){
									unf_selGEN_excl2 = true;
									photonPtGEN_excl2_->Fill(photonPtGEN, weight_withPU);
									if(Sig){
										unf_photonPtGEN_excl2 = photonPtGEN;
										unf_SelectedJetsGEN_N_excl2 = SelectedJetsGEN_N;
										unf_SelectedJetsGEN_HT_excl2 = SelectedJetsGEN_HT;
									}
								}

								if (SelectedJetsGEN_N > 1){
									unf_selGEN_N1 = true;
									photonPtGEN_N1_->Fill(photonPtGEN, weight_withPU);
									if(Sig){
										unf_photonPtGEN_N1 = photonPtGEN;
										unf_SelectedJetsGEN_N_N1 = SelectedJetsGEN_N;
										unf_SelectedJetsGEN_HT_N1 = SelectedJetsGEN_HT;
									}
								}
								
								if (SelectedJetsGEN_N > 2){
									unf_selGEN_N2 = true;
									photonPtGEN_N2_->Fill(photonPtGEN, weight_withPU);
									if(Sig){
										unf_photonPtGEN_N2 = photonPtGEN;
										unf_SelectedJetsGEN_N_N2 = SelectedJetsGEN_N;
										unf_SelectedJetsGEN_HT_N2 = SelectedJetsGEN_HT;
									}
								}
							} // end HTGEN selection
						} // end kin JetsGEN (cleaned vs. photonGEN) selection
					} // end photonGEN kinematic selection
				} // end photonGEN selection
			} // end Isolation at GEN level 
			
			pre_photonIsoSumPtDR03GEN_->Fill(photonIsoSumPtDR03GEN, weight_withPU);
			HTParSum_->Fill(HTParSum, weight_withPU);

		} // end MC selection for GEN

		// clean jets GEN
		SelectedJetsGEN_N = 0;
		SelectedJetsGEN_HT = 0;
				
		SelectedJetsGEN_Pt.clear();
		SelectedJetsGEN_E.clear();
		SelectedJetsGEN_Eta.clear();
		SelectedJetsGEN_Phi.clear();
		// end clean jets GEN


		// ==================================== REC selection

			
		// Efficiency corrections
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {

			for(unsigned int iPhoPos = 0; iPhoPos < photonPt->size(); iPhoPos++) {

				// Trigger Prescale factors - definitions	
				bool range_Pt01 = false;
				bool range_Pt02 = false;						
				bool range_Pt03 = false;						
				bool range_Pt04 = false;						
				bool range_Pt05 = false;						

				range_Pt01 = (photonPt->at(iPhoPos) > 0. && photonPt->at(iPhoPos) < 60.);
				range_Pt02 = (photonPt->at(iPhoPos) > 60. && photonPt->at(iPhoPos) < 90.);
				range_Pt03 = (photonPt->at(iPhoPos) > 90. && photonPt->at(iPhoPos) < 100.);
				range_Pt04 = (photonPt->at(iPhoPos) > 100. && photonPt->at(iPhoPos) < 207.1);
				range_Pt05 = (photonPt->at(iPhoPos) > 207.1);
																				
				//bool TriMatchF4Path_sel_1 = false;
				//bool TriMatchF4Path_sel_2 = false;
				//bool TriMatchF4Path_sel_4 = false;
				bool TriMatchF4Path_sel_8 = false;
				//bool TriMatchF4Path_sel_16 = false;
				bool TriMatchF4Path_sel_32 = false;
				//bool TriMatchF4Path_sel_64 = false;
				bool TriMatchF4Path_sel_128 = false;
				//bool TriMatchF4Path_sel_256 = false;
				bool TriMatchF4Path_sel_512 = false;
				//bool TriMatchF4Path_sel_1024 = false;
				//bool TriMatchF4Path_sel_2048 = false;
				bool TriMatchF4Path_sel_4096 = false;																									

				//TriMatchF4Path_sel_1 = TriMatchF4Path_photon->at(iPhoPos)& 1;
				//TriMatchF4Path_sel_2 = TriMatchF4Path_photon->at(iPhoPos)& 2;
				//TriMatchF4Path_sel_4 = TriMatchF4Path_photon->at(iPhoPos)& 4;
				TriMatchF4Path_sel_8 = TriMatchF4Path_photon->at(iPhoPos)& 8;
				//TriMatchF4Path_sel_16 = TriMatchF4Path_photon->at(iPhoPos)& 16;
				TriMatchF4Path_sel_32 = TriMatchF4Path_photon->at(iPhoPos)& 32;
				//TriMatchF4Path_sel_64 = TriMatchF4Path_photon->at(iPhoPos)& 64;
				TriMatchF4Path_sel_128 = TriMatchF4Path_photon->at(iPhoPos)& 128;
				//TriMatchF4Path_sel_256 = TriMatchF4Path_photon->at(iPhoPos)& 256;
				TriMatchF4Path_sel_512 = TriMatchF4Path_photon->at(iPhoPos)& 512;
				//TriMatchF4Path_sel_1024 = TriMatchF4Path_photon->at(iPhoPos)& 1024;
				//TriMatchF4Path_sel_2048 = TriMatchF4Path_photon->at(iPhoPos)& 2048;
				TriMatchF4Path_sel_4096 = TriMatchF4Path_photon->at(iPhoPos)& 4096;

				bool TriMatchF4Path_AND_pTrange;
				float Tri_PF; 

				if (range_Pt01 && TriMatchF4Path_sel_8){
					TriMatchF4Path_AND_pTrange = true;
					if (!isMC) Tri_PF = 1.;	
					else Tri_PF = 1/6886.55;
				}
				else if (range_Pt02 && TriMatchF4Path_sel_32){ 
					TriMatchF4Path_AND_pTrange = true;
					if (!isMC) Tri_PF = 1.;	
					Tri_PF = 1/885.49;
				}
				else if (range_Pt03 && TriMatchF4Path_sel_128){ 
					TriMatchF4Path_AND_pTrange = true;
					if (!isMC) Tri_PF = 1.;	
					Tri_PF = 1/147.59;
				}
				else if (range_Pt04 && TriMatchF4Path_sel_512){ 
					TriMatchF4Path_AND_pTrange = true;
					if (!isMC) Tri_PF = 1.;	
					Tri_PF = 1/70.53;
				}
				else if (range_Pt05 && TriMatchF4Path_sel_4096){ 
					TriMatchF4Path_AND_pTrange = true;
					if (!isMC) Tri_PF = 1.;	
					Tri_PF = 1/1.0;
				}
				else {
					TriMatchF4Path_AND_pTrange = false;
					Tri_PF = 0.;
				}

				photonTriMatchF4Path_AND_pTrange.push_back(TriMatchF4Path_AND_pTrange);
				photonTri_PF.push_back(Tri_PF);
				// end Trigger Prescale factors - definitions

				
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

				// background data-driven correction - definitions
				float BackDataDriven_F;
				if (BackDataDriven_corr) {
					if (isMC) BackDataDriven_F = 1.;
					else {
						bool bin_Pt01 = false;
						bool bin_Pt02 = false;
						bool bin_Pt03 = false;
						bool bin_Pt04 = false;
						bool bin_Pt05 = false;
						bool bin_Pt06 = false;
						bool bin_Pt07 = false;
						bool bin_Pt08 = false;
						bool bin_Pt09 = false;
						bool bin_Pt10 = false;
						bool bin_Pt11 = false;
						bool bin_Pt12 = false;
						bool bin_Pt13 = false;
						bool bin_Pt14 = false;
						bool bin_Pt15 = false;
						bool bin_Pt16 = false;
						bool bin_Pt17 = false;
						bool bin_Pt18 = false;
						bool bin_Pt19 = false;

						bin_Pt01 = (photonPt->at(iPhoPos) > 100.0 && photonPt->at(iPhoPos) < 151.6);
						bin_Pt02 = (photonPt->at(iPhoPos) > 151.6 && photonPt->at(iPhoPos) < 207.1);
						bin_Pt03 = (photonPt->at(iPhoPos) > 207.1 && photonPt->at(iPhoPos) < 313.8);
						bin_Pt04 = (photonPt->at(iPhoPos) > 313.8 && photonPt->at(iPhoPos) < 649.8);
						bin_Pt05 = (photonPt->at(iPhoPos) > 649.8 && photonPt->at(iPhoPos) < 800.0);
						bin_Pt06 = (photonPt->at(iPhoPos) > 800.0);
						bin_Pt07 = false;
						bin_Pt08 = false;
						bin_Pt09 = false;
						bin_Pt10 = false;
						bin_Pt11 = false;
						bin_Pt12 = false;
						bin_Pt13 = false;
						bin_Pt14 = false;
						bin_Pt15 = false;
						bin_Pt16 = false;
						bin_Pt17 = false;								
						bin_Pt18 = false;
						bin_Pt19 = false;

						if (bin_Pt01) BackDataDriven_F = 0.;
						else if (bin_Pt02) BackDataDriven_F = 0.; 
						else if (bin_Pt03) BackDataDriven_F = 0.; 
						else if (bin_Pt04) BackDataDriven_F = 0.; 
						else if (bin_Pt05) BackDataDriven_F = 0.; 
						else if (bin_Pt06) BackDataDriven_F = 0.; 
						else if (bin_Pt07) BackDataDriven_F = 0.; 
						else if (bin_Pt08) BackDataDriven_F = 0.; 
						else if (bin_Pt09) BackDataDriven_F = 0.; 
						else if (bin_Pt10) BackDataDriven_F = 0.; 
						else if (bin_Pt11) BackDataDriven_F = 0.; 
						else if (bin_Pt12) BackDataDriven_F = 0.; 
						else if (bin_Pt13) BackDataDriven_F = 0.; 
						else if (bin_Pt14) BackDataDriven_F = 0.; 
						else if (bin_Pt15) BackDataDriven_F = 0.; 
						else if (bin_Pt16) BackDataDriven_F = 0.; 
						else if (bin_Pt17) BackDataDriven_F = 0.; 
						else if (bin_Pt18) BackDataDriven_F = 0.; 
						else if (bin_Pt19) BackDataDriven_F = 0.; 
						else BackDataDriven_F = 0.;
					}
				}
				else BackDataDriven_F = 1.;

			photonBackDataDriven_F.push_back(BackDataDriven_F);
			// end background data-driven correction - definitions

			}
		}	// end Efficiency corrections


		// SelectedPhotons collection selection
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {

			IDIsoPhotons_N = 0;
			SelectedPhotons_N = 0;					 

			for(unsigned int iPhoPos = 0; iPhoPos < photonPt->size(); iPhoPos++) {

				Photons_Pt_preTriMatch.push_back(photonPt->at(iPhoPos));
				Tri_PF_preTriMatch.push_back(photonTri_PF.at(iPhoPos));
				TeP_SF_preTriMatch.push_back(photonTeP_SF.at(iPhoPos));
				BackDataDriven_F_preTriMatch.push_back(photonBackDataDriven_F.at(iPhoPos));

				// photon trigger matching selection
				bool TriMatchF4Path_sel = photonTriMatchF4Path_AND_pTrange.at(iPhoPos);
				if (TriMatchF4Path_sel) {

					// PF isolation variables - definitions
					photonPfIso = 0;
					photonIsoFPR = 0;
	
					photonPfIso = photonPfIsoChargedHad->at(iPhoPos) + photonPfIsoNeutralHad->at(iPhoPos) + photonPfIsoPhoton->at(iPhoPos);
					photonIsoFPR = photonIsoFPRCharged->at(iPhoPos) + photonIsoFPRNeutral->at(iPhoPos) + photonIsoFPRPhoton->at(iPhoPos);
					// end PF isolation variables - definitions

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

					photonPfIso_RhoCorr = 0;
					photonPfIso_RhoCorr = photonPfIsoChargedHad_RhoCorr + photonPfIsoNeutralHad_RhoCorr + photonPfIsoPhoton_RhoCorr;

					photonPfIsoChargedHad_RhoCorr_forFit = 0;
					photonPfIsoNeutralHad_RhoCorr_forFit = 0;
					photonPfIsoPhoton_RhoCorr_forFit = 0;
					photonPfIsoChargedHad_RhoCorr_forFit = photonPfIsoChargedHad->at(iPhoPos) - rho*EA_CH;
					photonPfIsoNeutralHad_RhoCorr_forFit = photonPfIsoNeutralHad->at(iPhoPos) - rho*EA_NH;
					photonPfIsoPhoton_RhoCorr_forFit = photonPfIsoPhoton->at(iPhoPos) - rho*EA_Ph;

					photonPfIso_RhoCorr_forFit = 0;
					photonPfIso_RhoCorr_forFit = photonPfIsoChargedHad_RhoCorr_forFit + photonPfIsoNeutralHad_RhoCorr_forFit + photonPfIsoPhoton_RhoCorr_forFit;
					// end Rho corrected PF isolation variables - definitions

					// Rho corrected FPR photon isolation variable for Random Cone - definitions
					bool bin_Random_Cone_RhoCorr_pT_Eta01 = false;
					bool bin_Random_Cone_RhoCorr_pT_Eta02 = false;
					bool bin_Random_Cone_RhoCorr_pT_Eta03 = false;

					bin_Random_Cone_RhoCorr_pT_Eta01 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 2000) && (abs(photonEta->at(iPhoPos)) < 0.5);
					bin_Random_Cone_RhoCorr_pT_Eta02 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 2000) && (abs(photonEta->at(iPhoPos)) >= 0.5 && abs(photonEta->at(iPhoPos)) < 1.0);
					bin_Random_Cone_RhoCorr_pT_Eta03 = (photonPt->at(iPhoPos) > 0 && photonPt->at(iPhoPos) < 2000) && (abs(photonEta->at(iPhoPos)) >= 1.0 && abs(photonEta->at(iPhoPos)) < 1.5);

					double effArea_iso, effArea_rho, effArea;
					
					if (bin_Random_Cone_RhoCorr_pT_Eta01) {
						 effArea_iso = 0.092660458139;
						 effArea_rho = 0.772860816663;
					}
					else if (bin_Random_Cone_RhoCorr_pT_Eta02) {
						 effArea_iso = 0.0948585396605;
						 effArea_rho = 0.771699427113;
					}
					else if (bin_Random_Cone_RhoCorr_pT_Eta03) {
						 effArea_iso = 0.0861565536086;
						 effArea_rho = 0.754253114019;
					}
					else {
						 effArea_iso = 0;
						 effArea_rho = 1;
					}
					
					effArea = effArea_iso/effArea_rho;
					
					photonIsoFPRPhoton_RhoCorr_forFit = 0;
					photonIsoFPRPhoton_RhoCorr_forFit = photonIsoFPRPhoton->at(iPhoPos) - rho*effArea;
					
					photonIsoFPRRandomConePhoton_RhoCorr_forFit = 0;
					photonIsoFPRRandomConePhoton_RhoCorr_forFit = photonIsoFPRRandomConePhoton->at(iPhoPos) - rho*effArea;					
					// end Rho corrected FPR photon isolation variable for Random Cone - definitions

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
						if (!inv_sigmaietaieta){
							if (photonid_sieie->at(iPhoPos) < 0.011) sigmaietaieta = true;
							else sigmaietaieta = false;
						}
						else {
							if (photonid_sieie->at(iPhoPos) >= 0.011 && photonid_sieie->at(iPhoPos) <= 0.014) sigmaietaieta = true;
							else sigmaietaieta = false;
						}	
						if (!inv_isolation){
							if(photonPfIsoChargedHad_RhoCorr < 1.5) iso_CH = true;
							else iso_CH = false;
							if(photonPfIsoNeutralHad_RhoCorr < (1.0 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
							else iso_NH = false;
							if(!RandomCone) {
//								if(photonPfIsoPhoton_RhoCorr < (0.7 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
								if(photonPfIsoPhoton_RhoCorr < 10) iso_Ph = true; // Relaxed cut for Fit on that variable
							}
							else {
								if(photonIsoFPRPhoton_RhoCorr_forFit < 10) iso_Ph = true;
							}
							else iso_Ph = false;
						}
						else {
							if(photonPfIsoChargedHad_RhoCorr >= 1.5) iso_CH = true;
							//if(photonPfIsoChargedHad_RhoCorr < 1.5) iso_CH = true;
							else iso_CH = false;
							//if(photonPfIsoNeutralHad_RhoCorr >= (1.0 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;							
							if(photonPfIsoNeutralHad_RhoCorr < (1.0 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
							else iso_NH = false;
							//if(photonPfIsoPhoton_RhoCorr >= (0.7 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
							if(photonPfIsoPhoton_RhoCorr < (0.7 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
							else iso_Ph = false;
						}
					}

					else if (geo == "endcaps"){
						if (!inv_sigmaietaieta){
							if (photonid_sieie->at(iPhoPos) < 0.033) sigmaietaieta = true;
							else sigmaietaieta = false;
						}
						else {
							if (photonid_sieie->at(iPhoPos) >= 0.033) sigmaietaieta = true;
							else sigmaietaieta = false;
						}
						if (!inv_isolation){
							if(photonPfIsoChargedHad_RhoCorr < 1.2) iso_CH = true;
							else iso_CH = false;
							if(photonPfIsoNeutralHad_RhoCorr < (1.5 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
							else iso_NH = false;
							if(!RandomCone) {
//							if(photonPfIsoPhoton_RhoCorr < (1.0 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
								if(photonPfIsoPhoton_RhoCorr < 10) iso_Ph = true; // Relaxed cut for Fit on that variable
							}
							else {
								if(photonIsoFPRPhoton_RhoCorr_forFit < 10) iso_Ph = true;
							}
							else iso_Ph = false;
						}
						else {
							if(photonPfIsoChargedHad_RhoCorr >= 1.2) iso_CH = true;
							else iso_CH = false;
							if(photonPfIsoNeutralHad_RhoCorr < (1.5 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
							else iso_NH = false;
							if(photonPfIsoPhoton_RhoCorr < (1.0 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
							else iso_Ph = false;
						}								
					}
					
					else {
						cout << "ERROR: Wrong geometry string written (only barrel or endcaps)" << endl;
					} 
					// end photon quality selection - definitions

					// Cut Based Photon 2012 - Medium (80%) from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
					bool geo_quality_sel = false;
				
					Photons_Pt_prePassConversionVeto.push_back(photonPt->at(iPhoPos));
					Photon_PassConversionVeto_prePassConversionVeto.push_back(photonPassConversionVeto->at(iPhoPos));
					Tri_PF_prePassConversionVeto.push_back(photonTri_PF.at(iPhoPos));
					TeP_SF_prePassConversionVeto.push_back(photonTeP_SF.at(iPhoPos));
					BackDataDriven_F_prePassConversionVeto.push_back(photonBackDataDriven_F.at(iPhoPos));

					if(PassConversionVeto){ 
				
						Photons_Pt_prehadronicOverEm2012.push_back(photonPt->at(iPhoPos));
						Photons_hadronicOverEm2012_prehadronicOverEm2012.push_back(photonid_hadronicOverEm2012->at(iPhoPos));
						Tri_PF_prehadronicOverEm2012.push_back(photonTri_PF.at(iPhoPos));
						TeP_SF_prehadronicOverEm2012.push_back(photonTeP_SF.at(iPhoPos));
						BackDataDriven_F_prehadronicOverEm2012.push_back(photonBackDataDriven_F.at(iPhoPos));
				
						if(hadronicOverEm2012){

							Photons_Pt_presigmaietaieta.push_back(photonPt->at(iPhoPos));
							Photons_sigmaietaieta_presigmaietaieta.push_back(photonid_sieie->at(iPhoPos));
							Tri_PF_presigmaietaieta.push_back(photonTri_PF.at(iPhoPos));
							TeP_SF_presigmaietaieta.push_back(photonTeP_SF.at(iPhoPos));
							BackDataDriven_F_presigmaietaieta.push_back(photonBackDataDriven_F.at(iPhoPos));

							if (sigmaietaieta) {

								Photons_Pt_preiso_CH.push_back(photonPt->at(iPhoPos));
								Photons_iso_CH_preiso_CH.push_back(photonPfIsoChargedHad_RhoCorr);
								Tri_PF_preiso_CH.push_back(photonTri_PF.at(iPhoPos));
								TeP_SF_preiso_CH.push_back(photonTeP_SF.at(iPhoPos));
								BackDataDriven_F_preiso_CH.push_back(photonBackDataDriven_F.at(iPhoPos));

								if (iso_CH) {

									Photons_Pt_preiso_NH.push_back(photonPt->at(iPhoPos));
									Photons_iso_NH_preiso_NH.push_back(photonPfIsoNeutralHad_RhoCorr);
									Tri_PF_preiso_NH.push_back(photonTri_PF.at(iPhoPos));								
									TeP_SF_preiso_NH.push_back(photonTeP_SF.at(iPhoPos));
									BackDataDriven_F_preiso_NH.push_back(photonBackDataDriven_F.at(iPhoPos));

									if (iso_NH) {

										Photons_Pt_preiso_Ph.push_back(photonPt->at(iPhoPos));
										Photons_iso_Ph_preiso_Ph.push_back(photonPfIsoPhoton_RhoCorr);
										Tri_PF_preiso_Ph.push_back(photonTri_PF.at(iPhoPos));								
										TeP_SF_preiso_Ph.push_back(photonTeP_SF.at(iPhoPos));
										BackDataDriven_F_preiso_Ph.push_back(photonBackDataDriven_F.at(iPhoPos));

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

						IDIsoPhotons_N += 1;

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

						Photons_Pt_preAcc.push_back(photonPt->at(iPhoPos));
						Photons_Eta_preAcc.push_back(photonEta->at(iPhoPos));
						Tri_PF_preAcc.push_back(photonTri_PF.at(iPhoPos));														
						TeP_SF_preAcc.push_back(photonTeP_SF.at(iPhoPos));
						BackDataDriven_F_preAcc.push_back(photonBackDataDriven_F.at(iPhoPos));

						// photon kinematic selection
						if (photonPt->at(iPhoPos) > 100. && geo_sel) {

							SelectedPhotons_Pt.push_back(photonPt->at(iPhoPos));
							SelectedPhotons_E.push_back(photonE->at(iPhoPos));
							SelectedPhotons_Eta.push_back(photonEta->at(iPhoPos)); 
							SelectedPhotons_Phi.push_back(photonPhi->at(iPhoPos));

							SelectedPhotons_PassConversionVeto.push_back(photonPassConversionVeto->at(iPhoPos));

							SelectedPhotons_PfIsoChargedHad.push_back(photonPfIsoChargedHad->at(iPhoPos));
							SelectedPhotons_PfIsoNeutralHad.push_back(photonPfIsoNeutralHad->at(iPhoPos));
							SelectedPhotons_PfIsoPhoton.push_back(photonPfIsoPhoton->at(iPhoPos));
							SelectedPhotons_PfIso.push_back(photonPfIso);

							SelectedPhotons_PfIsoChargedHad_RhoCorr.push_back(photonPfIsoChargedHad_RhoCorr);
							SelectedPhotons_PfIsoNeutralHad_RhoCorr.push_back(photonPfIsoNeutralHad_RhoCorr);
							SelectedPhotons_PfIsoPhoton_RhoCorr.push_back(photonPfIsoPhoton_RhoCorr);
							SelectedPhotons_PfIso_RhoCorr.push_back(photonPfIso_RhoCorr);

							SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.push_back(photonPfIsoChargedHad_RhoCorr_forFit);
							SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.push_back(photonPfIsoNeutralHad_RhoCorr_forFit);
							SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.push_back(photonPfIsoPhoton_RhoCorr_forFit);
							SelectedPhotons_PfIso_RhoCorr_forFit.push_back(photonPfIso_RhoCorr_forFit);

							SelectedPhotons_PfIsoPhotons03ForCic.push_back(photonPfIsoPhotons03ForCic->at(iPhoPos));
							SelectedPhotons_PfIsoNeutrals03ForCic.push_back(photonPfIsoNeutrals03ForCic->at(iPhoPos));
							SelectedPhotons_PfIsoCharged03ForCicVtx0.push_back(photonPfIsoCharged03ForCicVtx0->at(iPhoPos));
							SelectedPhotons_PfIsoCharged03BadForCic.push_back(photonPfIsoCharged03BadForCic->at(iPhoPos));

							SelectedPhotons_PfIsoPhotons04ForCic.push_back(photonPfIsoPhotons04ForCic->at(iPhoPos));
							SelectedPhotons_PfIsoNeutrals04ForCic.push_back(photonPfIsoNeutrals04ForCic->at(iPhoPos));
							SelectedPhotons_PfIsoCharged04ForCicVtx0.push_back(photonPfIsoCharged04ForCicVtx0->at(iPhoPos));
							SelectedPhotons_PfIsoCharged04BadForCic.push_back(photonPfIsoCharged04BadForCic->at(iPhoPos));

							SelectedPhotons_id_sieie.push_back(photonid_sieie->at(iPhoPos));
							SelectedPhotons_id_sieip.push_back(photonid_sieip->at(iPhoPos));
							SelectedPhotons_id_etawidth.push_back(photonid_etawidth->at(iPhoPos));
							SelectedPhotons_id_phiwidth.push_back(photonid_phiwidth->at(iPhoPos));
							SelectedPhotons_id_r9.push_back(photonid_r9->at(iPhoPos));

							SelectedPhotons_id_lambdaRatio.push_back(photonid_lambdaRatio->at(iPhoPos));
							SelectedPhotons_id_s4Ratio.push_back(photonid_s4Ratio->at(iPhoPos));
							SelectedPhotons_id_e25.push_back(photonid_e25->at(iPhoPos));
							SelectedPhotons_id_sceta.push_back(photonid_sceta->at(iPhoPos));

							SelectedPhotons_id_ESEffSigmaRR.push_back(photonid_ESEffSigmaRR->at(iPhoPos));
							SelectedPhotons_id_hadronicOverEm.push_back(photonid_hadronicOverEm->at(iPhoPos));
							SelectedPhotons_id_hadronicOverEm2012.push_back(photonid_hadronicOverEm2012->at(iPhoPos));

							SelectedPhotons_hcalTowerSumEtConeDR04.push_back(photonhcalTowerSumEtConeDR04->at(iPhoPos));
							SelectedPhotons_ecalRecHitSumEtConeDR04.push_back(photonecalRecHitSumEtConeDR04->at(iPhoPos));
							SelectedPhotons_nTrkSolidConeDR04.push_back(photonnTrkSolidConeDR04->at(iPhoPos));
							SelectedPhotons_trkSumPtSolidConeDR04.push_back(photontrkSumPtSolidConeDR04->at(iPhoPos));
							SelectedPhotons_nTrkHollowConeDR04.push_back(photonnTrkHollowConeDR04->at(iPhoPos));
							SelectedPhotons_trkSumPtHollowConeDR04.push_back(photontrkSumPtHollowConeDR04->at(iPhoPos));

							SelectedPhotons_IsoFPRCharged.push_back(photonIsoFPRCharged->at(iPhoPos));
							SelectedPhotons_IsoFPRNeutral.push_back(photonIsoFPRNeutral->at(iPhoPos));
							SelectedPhotons_IsoFPRPhoton.push_back(photonIsoFPRPhoton->at(iPhoPos));
							SelectedPhotons_IsoFPR.push_back(photonIsoFPR);							

							SelectedPhotons_IsoFPRRandomConeCharged.push_back(photonIsoFPRRandomConeCharged->at(iPhoPos));
							SelectedPhotons_IsoFPRRandomConeNeutral.push_back(photonIsoFPRRandomConeNeutral->at(iPhoPos));
							SelectedPhotons_IsoFPRRandomConePhoton.push_back(photonIsoFPRRandomConePhoton->at(iPhoPos));
							
							SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.push_back(photonIsoFPRPhoton_RhoCorr_forFit);
							SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.push_back(photonIsoFPRRandomConePhoton_RhoCorr_forFit);
								
							SelectedPhotons_Bit.push_back(photonBit->at(iPhoPos));
							
							SelectedPhotons_TriMatchF4Path_AND_pTrange.push_back(photonTriMatchF4Path_AND_pTrange.at(iPhoPos));
							SelectedPhotons_Tri_PF.push_back(photonTri_PF.at(iPhoPos));
							SelectedPhotons_TeP_SF.push_back(photonTeP_SF.at(iPhoPos));
							SelectedPhotons_BackDataDriven_F.push_back(photonBackDataDriven_F.at(iPhoPos));
							
							SelectedPhotons_N+=1;

						}	// end photon kinematic selection
					}	// end photon trigger matching selection
				} // end photon quality selection
			} 
		} // end SelectedPhotons collection selection

			
		// jetVeto: jets vs. SelectedPhotons 
		if(SelectedPhotons_N > 0 && (nJets > 0 && (nJets == (int)jetPt->size())) ){

			SelectedJetsALL_N = 0;
			SelectedJets_N = 0;

			for (unsigned int iJetPos = 0; (int)iJetPos < nJets; iJetPos++) {

				// only counting of cleaned jets vs. ALL SelectedPhotons
				bool closeALL = false;
				for (unsigned int jPhoPos = 0; jPhoPos < SelectedPhotons_N; jPhoPos++){
					if ( deltaR(SelectedPhotons_Eta.at(jPhoPos), SelectedPhotons_Phi.at(jPhoPos), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
						closeALL = true;
						break;
					}
				}
				if (!closeALL){
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){
						SelectedJetsALL_N += 1;
					}
				} // end only counting of cleaned jets vs. ALL SelectedPhotons

				// selection of cleaned jets vs. LEADING SelectedPhotons
				bool closeLEA = false;

				if ( deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)) < 0.5) {
					closeLEA = true;
				}
				
				Jets_deltaR_predeltaR.push_back(deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), jetEta->at(iJetPos), jetPhi->at(iJetPos)));

				if (!closeLEA){
						
					Jets_Pt_preAcc.push_back(jetPt->at(iJetPos));
					Jets_Eta_preAcc.push_back(jetEta->at(iJetPos));
					
					// jets kinematic selection
					if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

						// jets pile-up ID correction							
						if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.64) ) {
									
							SelectedJets_Pt.push_back(jetPt->at(iJetPos));
							SelectedJets_E.push_back(jetE->at(iJetPos));
							SelectedJets_Eta.push_back(jetEta->at(iJetPos));
							SelectedJets_Phi.push_back(jetPhi->at(iJetPos));
							SelectedJets_N += 1;
						}	// jets pile-up ID correction
					} // end jets kinematic selection
				} // end selection of cleaned jets vs. LEADING SelectedPhotons
			}
		} // jetVeto: jets vs. SelectedPhotons

		// collectives jets properties
		SelectedJets_HT = 0;
		for(unsigned int zJetPos = 0; zJetPos < SelectedJets_Pt.size(); zJetPos++) {
			SelectedJets_HT += SelectedJets_Pt.at(zJetPos);
		}

		if (SelectedPhotons_N > 0 && SelectedJets_N > 1){
			TLorentzVector PtEtaPhiE_tmpPho = TLorentzVector(0,0,0,0);
			PtEtaPhiE_tmpPho.SetPtEtaPhiE(SelectedPhotons_Pt.at(0), SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedPhotons_E.at(0));
			vPtEtaPhiE.push_back(PtEtaPhiE_tmpPho);

			for(unsigned int zJetPos = 0; zJetPos < SelectedJets_N; zJetPos++) {
				TLorentzVector PtEtaPhiE_tmpJet = TLorentzVector(0,0,0,0);
				PtEtaPhiE_tmpJet.SetPtEtaPhiE(SelectedJets_Pt.at(zJetPos), SelectedJets_Eta.at(zJetPos), SelectedJets_Phi.at(zJetPos), SelectedJets_E.at(zJetPos));
				vPtEtaPhiE.push_back(PtEtaPhiE_tmpJet);
			}

			EventShapeLorentz* myEvshp = new EventShapeLorentz(vPtEtaPhiE, fCut_eta_central ,1);
			myEvshpV = myEvshp->getEventShapes();
			TA = myEvshp->getThrustAxis();
			Grouping = myEvshp->getGrouping();
			Grouping_test = myEvshp->getGrouping_C();
			delete myEvshp;
		}
		// end collectives jets properties


		// scaling factors definitions
		if(SelectedPhotons_N > 0) {
			prescale_Tri = SelectedPhotons_Tri_PF.at(0);		
			scale_TeP = SelectedPhotons_TeP_SF.at(0);
			scale_BackDataDriven = SelectedPhotons_BackDataDriven_F.at(0);
			weight_final = prescale_Tri * scale_TeP * scale_BackDataDriven * weight_withPU;
		} // end scaling factors definitions


		// =========== Analysis selection
		
		// scaling factors pre cuts definitions
		double prescale_Tri_preGammacuts = 1.;
		double scale_TeP_preGammacuts = 1.; 
		double scale_BackDataDriven_preGammacuts= 1.;
		double weight_final_preGammacuts = 1.;
		
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {
			prescale_Tri_preGammacuts = photonTri_PF.at(0);
			scale_TeP_preGammacuts = photonTeP_SF.at(0);
			scale_BackDataDriven_preGammacuts = photonBackDataDriven_F.at(0);
			weight_final_preGammacuts = prescale_Tri_preGammacuts * scale_TeP_preGammacuts * scale_BackDataDriven_preGammacuts * weight_withPU;
		} // end scaling factors pre cuts definitions

		// no selections
		iSelected0++;
		
		if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {
			gamma_Pt_1_precut1_->Fill(photonPt->at(0), weight_final_preGammacuts);
		}
		// end no selections


		// trigger family selection
		if (8 & isTriggered) {
			iSelected1++;


			if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {
				gamma_Pt_1_postcut1_->Fill(photonPt->at(0), weight_final_preGammacuts);
				if(isMC){
					photonIsoSumPtDR03GEN_precut2_->Fill(photonIsoSumPtDR03GEN, weight_final_preGammacuts);
				}
			}


			// Isolation at GEN level
			if (isoGEN) {
				iSelected2++;

				if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {
					gamma_Pt_1_postcut2_->Fill(photonPt->at(0), weight_final_preGammacuts);

					if (Photons_Pt_preTriMatch.size() > 0 && Tri_PF_preTriMatch.size() > 0 && TeP_SF_preTriMatch.size() > 0 && BackDataDriven_F_preTriMatch.size() > 0){
						double weight_final_preTriMatch = Tri_PF_preTriMatch.at(0) * TeP_SF_preTriMatch.at(0) * BackDataDriven_F_preTriMatch.at(0) * weight_withPU;
						gamma_Pt_1_preTriMatch_->Fill(Photons_Pt_preTriMatch.at(0), weight_final_preTriMatch);
					}
			}

					if (Photons_Pt_prePassConversionVeto.size() > 0 && Photon_PassConversionVeto_prePassConversionVeto.size() > 0 && Tri_PF_prePassConversionVeto.size() > 0 && TeP_SF_prePassConversionVeto.size() > 0 && BackDataDriven_F_prePassConversionVeto.size() > 0){
						double weight_final_prePassConversionVeto = Tri_PF_prePassConversionVeto.at(0) * TeP_SF_prePassConversionVeto.at(0) * BackDataDriven_F_prePassConversionVeto.at(0) * weight_withPU;
						gamma_Pt_1_prePassConversionVeto_->Fill(Photons_Pt_prePassConversionVeto.at(0), weight_final_prePassConversionVeto);
						gamma_PassConversionVeto_1_prePassConversionVeto_->Fill(Photon_PassConversionVeto_prePassConversionVeto.at(0), weight_final_prePassConversionVeto);
					}

					if (Photons_Pt_prehadronicOverEm2012.size() > 0 && Photons_hadronicOverEm2012_prehadronicOverEm2012.size() > 0 && Tri_PF_prehadronicOverEm2012.size() > 0 && TeP_SF_prehadronicOverEm2012.size() > 0 &&  BackDataDriven_F_prehadronicOverEm2012.size() > 0) {					
						double weight_final_prehadronicOverEm2012 = Tri_PF_prehadronicOverEm2012.at(0) * TeP_SF_prehadronicOverEm2012.at(0) * BackDataDriven_F_prehadronicOverEm2012.at(0) * weight_withPU;
						gamma_Pt_1_prehadronicOverEm2012_->Fill(Photons_Pt_prehadronicOverEm2012.at(0), weight_final_prehadronicOverEm2012);
						gamma_hadronicOverEm2012_1_prehadronicOverEm2012_->Fill(Photons_hadronicOverEm2012_prehadronicOverEm2012.at(0), weight_final_prehadronicOverEm2012);
					}
					
					if (Photons_Pt_presigmaietaieta.size() > 0 && Photons_sigmaietaieta_presigmaietaieta.size() > 0 && Tri_PF_presigmaietaieta.size() > 0 && TeP_SF_presigmaietaieta.size() > 0 && BackDataDriven_F_presigmaietaieta.size() > 0){
						double weight_final_presigmaietaieta = Tri_PF_presigmaietaieta.at(0) * TeP_SF_presigmaietaieta.at(0) * BackDataDriven_F_presigmaietaieta.at(0) * weight_withPU;
						gamma_Pt_1_presigmaietaieta_->Fill(Photons_Pt_presigmaietaieta.at(0), weight_final_presigmaietaieta);
						gamma_sigmaietaieta_1_presigmaietaieta_->Fill(Photons_sigmaietaieta_presigmaietaieta.at(0), weight_final_presigmaietaieta);
					}
					
					if (Photons_Pt_preiso_CH.size() > 0 && Photons_iso_CH_preiso_CH.size() > 0 && Tri_PF_preiso_CH.size() > 0 && TeP_SF_preiso_CH.size() > 0 && BackDataDriven_F_preiso_CH.size() > 0){
						double weight_final_preiso_CH = Tri_PF_preiso_CH.at(0) * TeP_SF_preiso_CH.at(0) * BackDataDriven_F_preiso_CH.at(0) * weight_withPU;
						gamma_Pt_1_preiso_CH_->Fill(Photons_Pt_preiso_CH.at(0), weight_final_preiso_CH);
						gamma_iso_CH_1_preiso_CH_->Fill(Photons_iso_CH_preiso_CH.at(0), weight_final_preiso_CH);
					}
					
					if (Photons_Pt_preiso_NH.size() > 0 && Photons_iso_NH_preiso_NH.size() > 0 && Tri_PF_preiso_NH.size() > 0 && TeP_SF_preiso_NH.size() > 0 && BackDataDriven_F_preiso_NH.size() > 0){
						double weight_final_preiso_NH = Tri_PF_preiso_NH.at(0) * TeP_SF_preiso_NH.at(0) * BackDataDriven_F_preiso_NH.at(0) * weight_withPU;
						gamma_Pt_1_preiso_NH_->Fill(Photons_Pt_preiso_NH.at(0), weight_final_preiso_NH);
						gamma_iso_NH_1_preiso_NH_->Fill(Photons_iso_NH_preiso_NH.at(0), weight_final_preiso_NH);
					}
					
					if (Photons_Pt_preiso_Ph.size() > 0 && Photons_iso_Ph_preiso_Ph.size() > 0 && Tri_PF_preiso_Ph.size() > 0 && TeP_SF_preiso_Ph.size() > 0 && BackDataDriven_F_preiso_Ph.size() > 0){
						double weight_final_preiso_Ph = Tri_PF_preiso_Ph.at(0) * TeP_SF_preiso_Ph.at(0) * BackDataDriven_F_preiso_Ph.at(0) * weight_withPU;
						gamma_Pt_1_preiso_Ph_->Fill(Photons_Pt_preiso_Ph.at(0), weight_final_preiso_Ph);
						gamma_iso_Ph_1_preiso_Ph_->Fill(Photons_iso_Ph_preiso_Ph.at(0), weight_final_preiso_Ph);
					}

					if (Photons_Pt_preAcc.size() > 0 && Photons_Eta_preAcc.size() > 0 && Tri_PF_preAcc.size() > 0 && TeP_SF_preAcc.size() > 0 && BackDataDriven_F_preAcc.size() > 0){
						double weight_final_preAcc = Tri_PF_preAcc.at(0) * TeP_SF_preAcc.at(0) * BackDataDriven_F_preAcc.at(0) * weight_withPU;
						gamma_Pt_1_preAcc_->Fill(Photons_Pt_preAcc.at(0), weight_final_preAcc);
						gamma_Eta_1_preAcc_->Fill(Photons_Eta_preAcc.at(0), weight_final_preAcc);
					}


				// TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N > 0){
					iSelected3++;

					gamma_Pt_1_postcut3_->Fill(SelectedPhotons_Pt.at(0), weight_final);
					
					if(nJets > 0 && (nJets == (int)jetPt->size()) ){
						if(Jets_deltaR_predeltaR.size() > 0){
							jets_deltaR_1_predeltaR_->Fill(Jets_deltaR_predeltaR.at(0), weight_final);
						}
						if(Jets_Pt_preAcc.size() > 0 && Jets_Eta_preAcc.size() > 0 ){	
							jets_Pt_1_preAcc_->Fill(Jets_Pt_preAcc.at(0), weight_final);
							jets_Eta_1_preAcc_->Fill(Jets_Eta_preAcc.at(0), weight_final);
						}
					}


					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N > 0) {
						iSelected4++;

						gamma_Pt_1_postcut4_->Fill(SelectedPhotons_Pt.at(0), weight_final);
						jets_HT_preHT_->Fill(SelectedJets_HT, weight_final);
							
						// HT selection
						if (SelectedJets_HT > 0){
							iSelected5++;

							unf_selREC_N0 = true;

							Nvtx_->Fill(nVtx, weight_final);

							IDIsoPhotons_N_->Fill(IDIsoPhotons_N, weight_final);
							SelectedPhotons_N_->Fill(SelectedPhotons_N, weight_final);

							SelectedPhotons_Pt_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
							SelectedPhotons_Pt_LogBin_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
							SelectedPhotons_E_1_->Fill(SelectedPhotons_E.at(0), weight_final);
							SelectedPhotons_Eta_1_->Fill(SelectedPhotons_Eta.at(0), weight_final);
							SelectedPhotons_Phi_1_->Fill(SelectedPhotons_Phi.at(0), weight_final);

							SelectedPhotons_PassConversionVeto_1_->Fill(SelectedPhotons_PassConversionVeto.at(0), weight_final);

							SelectedPhotons_PfIsoChargedHad_1_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
							SelectedPhotons_PfIsoNeutralHad_1_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
							SelectedPhotons_PfIsoPhoton_1_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
							SelectedPhotons_PfIso_1_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

							SelectedPhotons_PfIsoChargedHad_RhoCorr_1_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
							SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
							SelectedPhotons_PfIsoPhoton_RhoCorr_1_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);

							SelectedPhotons_PfIso_RhoCorr_1_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
							TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

							SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
							SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
							SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
							TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
														
							SelectedPhotons_PfIso_RhoCorr_forFit_1_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

							if (SelectedPhotons_Pt.at(0) > 100 && SelectedPhotons_Pt.at(0) < 151.6){
								SelectedPhotons_id_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_1_bin01_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin01_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin01_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin01_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin01_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 151.6 && SelectedPhotons_Pt.at(0) < 207.1){
								SelectedPhotons_id_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_1_bin02_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin02_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin02_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin02_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);								
								SelectedPhotons_PfIso_RhoCorr_1_bin02_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}
							
							if (SelectedPhotons_Pt.at(0) > 207.1 && SelectedPhotons_Pt.at(0) < 313.8){
								SelectedPhotons_id_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin03_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin03_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin03_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin03_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin03_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 313.8 && SelectedPhotons_Pt.at(0) < 649.8){
								SelectedPhotons_id_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin04_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin04_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin04_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin04_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin04_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 649.8 && SelectedPhotons_Pt.at(0) < 800.0){
								SelectedPhotons_id_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin05_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin05_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin05_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin05_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin05_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								
								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 800.0){
								SelectedPhotons_id_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin06_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin06_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin06_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin06_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin06_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 313.8){
								SelectedPhotons_id_sieie_1_bin07_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin07_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin07_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin07_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin07_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin07_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin07_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin07_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin07_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin07_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin07_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin07_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin07_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin08_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin08_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin08_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin08_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin08_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin08_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin08_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin08_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin08_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin08_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin08_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin08_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin08_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin09_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin09_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin09_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin09_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin09_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin09_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin09_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin09_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin09_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin09_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin09_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin09_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin09_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin10_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin10_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin10_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin10_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin10_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin10_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin10_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin10_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin10_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin10_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin10_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin10_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin10_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin11_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin11_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin11_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin11_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin11_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin11_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin11_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin11_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin11_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin11_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin11_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin11_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin11_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin12_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin12_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin12_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin12_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin12_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin12_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin12_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin12_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin12_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin12_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin12_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin12_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin12_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin13_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin13_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin13_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin13_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin13_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin13_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin13_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin13_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin13_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin13_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin13_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin13_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin13_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin14_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin14_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin14_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin14_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin14_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin14_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin14_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin14_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin14_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin14_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin14_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin14_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin14_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin15_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin15_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin15_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin15_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin15_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin15_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin15_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin15_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin15_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin15_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin15_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin15_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin15_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin16_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin16_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin16_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin16_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin16_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin16_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin16_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin16_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin16_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin16_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin16_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin16_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin16_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin17_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin17_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin17_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin17_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin17_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin17_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin17_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin17_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin17_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin17_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin17_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin17_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin17_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin18_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin18_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin18_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin18_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin18_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin18_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin18_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin18_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin18_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin18_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin18_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin18_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin18_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin19_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin19_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin19_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin19_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin19_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin19_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin19_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin19_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin19_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin19_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin19_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin19_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin19_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 10000 && SelectedPhotons_Pt.at(0) < 100000){
								SelectedPhotons_id_sieie_1_bin20_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);							

								SelectedPhotons_PfIsoChargedHad_1_bin20_->Fill(SelectedPhotons_PfIsoChargedHad.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_1_bin20_->Fill(SelectedPhotons_PfIsoNeutralHad.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_1_bin20_->Fill(SelectedPhotons_PfIsoPhoton.at(0), weight_final);
								SelectedPhotons_PfIso_1_bin20_->Fill(SelectedPhotons_PfIso.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr.at(0), weight_final);
								SelectedPhotons_PfIso_RhoCorr_1_bin20_->Fill(SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin20_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr.at(0), weight_final);

								SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_->Fill(SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_->Fill(SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_->Fill(SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin20_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.at(0), weight_final);
								
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin20_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);

								SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin20_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin20_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin20_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin20_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							}

							SelectedPhotons_PfIsoPhotons03ForCic_1_->Fill(SelectedPhotons_PfIsoPhotons03ForCic.at(0), weight_final);
							SelectedPhotons_PfIsoNeutrals03ForCic_1_->Fill(SelectedPhotons_PfIsoNeutrals03ForCic.at(0), weight_final);
							SelectedPhotons_PfIsoCharged03ForCicVtx0_1_->Fill(SelectedPhotons_PfIsoCharged03ForCicVtx0.at(0), weight_final);
							SelectedPhotons_PfIsoCharged03BadForCic_1_->Fill(SelectedPhotons_PfIsoCharged03BadForCic.at(0), weight_final);

							SelectedPhotons_PfIsoPhotons04ForCic_1_->Fill(SelectedPhotons_PfIsoPhotons04ForCic.at(0), weight_final);
							SelectedPhotons_PfIsoNeutrals04ForCic_1_->Fill(SelectedPhotons_PfIsoNeutrals04ForCic.at(0), weight_final);
							SelectedPhotons_PfIsoCharged04ForCicVtx0_1_->Fill(SelectedPhotons_PfIsoCharged04ForCicVtx0.at(0), weight_final);
							SelectedPhotons_PfIsoCharged04BadForCic_1_->Fill(SelectedPhotons_PfIsoCharged04BadForCic.at(0), weight_final);

							SelectedPhotons_id_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), weight_final);
							SelectedPhotons_id_sieip_1_->Fill(SelectedPhotons_id_sieip.at(0), weight_final);
							SelectedPhotons_id_etawidth_1_->Fill(SelectedPhotons_id_etawidth.at(0), weight_final);
							SelectedPhotons_id_phiwidth_1_->Fill(SelectedPhotons_id_phiwidth.at(0), weight_final);
							SelectedPhotons_id_r9_1_->Fill(SelectedPhotons_id_r9.at(0), weight_final);

							SelectedPhotons_id_lambdaRatio_1_->Fill(SelectedPhotons_id_lambdaRatio.at(0), weight_final);
							SelectedPhotons_id_s4Ratio_1_->Fill(SelectedPhotons_id_s4Ratio.at(0), weight_final);
							SelectedPhotons_id_e25_1_->Fill(SelectedPhotons_id_e25.at(0), weight_final);
							SelectedPhotons_id_sceta_1_->Fill(SelectedPhotons_id_sceta.at(0), weight_final);

							SelectedPhotons_id_ESEffSigmaRR_1_->Fill(SelectedPhotons_id_ESEffSigmaRR.at(0), weight_final);
							SelectedPhotons_id_hadronicOverEm_1_->Fill(SelectedPhotons_id_hadronicOverEm.at(0), weight_final);
							SelectedPhotons_id_hadronicOverEm2012_1_->Fill(SelectedPhotons_id_hadronicOverEm2012.at(0), weight_final);

							SelectedPhotons_hcalTowerSumEtConeDR04_1_->Fill(SelectedPhotons_hcalTowerSumEtConeDR04.at(0), weight_final);
							SelectedPhotons_ecalRecHitSumEtConeDR04_1_->Fill(SelectedPhotons_ecalRecHitSumEtConeDR04.at(0), weight_final);
							SelectedPhotons_nTrkSolidConeDR04_1_->Fill(SelectedPhotons_nTrkSolidConeDR04.at(0), weight_final);
							SelectedPhotons_trkSumPtSolidConeDR04_1_->Fill(SelectedPhotons_trkSumPtSolidConeDR04.at(0), weight_final);
							SelectedPhotons_nTrkHollowConeDR04_1_->Fill(SelectedPhotons_nTrkHollowConeDR04.at(0), weight_final);
							SelectedPhotons_trkSumPtHollowConeDR04_1_->Fill(SelectedPhotons_trkSumPtHollowConeDR04.at(0), weight_final);

							SelectedPhotons_IsoFPRCharged_1_->Fill(SelectedPhotons_IsoFPRCharged.at(0), weight_final);
							SelectedPhotons_IsoFPRNeutral_1_->Fill(SelectedPhotons_IsoFPRNeutral.at(0), weight_final);
							SelectedPhotons_IsoFPRPhoton_1_->Fill(SelectedPhotons_IsoFPRPhoton.at(0), weight_final);
							SelectedPhotons_IsoFPR_1_->Fill(SelectedPhotons_IsoFPR.at(0), weight_final);

							SelectedPhotons_IsoFPRRandomConeCharged_1_->Fill(SelectedPhotons_IsoFPRRandomConeCharged.at(0), weight_final);
							SelectedPhotons_IsoFPRRandomConeNeutral_1_->Fill(SelectedPhotons_IsoFPRRandomConeNeutral.at(0), weight_final);
							SelectedPhotons_IsoFPRRandomConePhoton_1_->Fill(SelectedPhotons_IsoFPRRandomConePhoton.at(0), weight_final);

							SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_->Fill(SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
							SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_->Fill(SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.at(0), weight_final);
							TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.at(0), weight_final);
							
							SelectedPhotons_Bit_1_->Fill(SelectedPhotons_Bit.at(0), weight_final);

							SelectedPhotons_TriMatchF4Path_AND_pTrange_1_->Fill(SelectedPhotons_TriMatchF4Path_AND_pTrange.at(0), weight_final);
							SelectedPhotons_Tri_PF_1_->Fill(SelectedPhotons_Tri_PF.at(0), weight_final);
							SelectedPhotons_TeP_SF_1_->Fill(SelectedPhotons_TeP_SF.at(0), weight_final);
							SelectedPhotons_BackDataDriven_F_1_->Fill(SelectedPhotons_BackDataDriven_F.at(0), weight_final);

							SelectedJetsALL_N_->Fill(SelectedJetsALL_N, weight_final);

							SelectedJets_N_->Fill(SelectedJets_N, weight_final);

							SelectedJets_Pt_1_->Fill(SelectedJets_Pt.at(0), weight_final);
							SelectedJets_E_1_->Fill(SelectedJets_E.at(0), weight_final);
							SelectedJets_Eta_1_->Fill(SelectedJets_Eta.at(0), weight_final);
							SelectedJets_Phi_1_->Fill(SelectedJets_Phi.at(0), weight_final);

							SelectedJets_HT_->Fill(SelectedJets_HT, weight_final);

							DeltaR_photon1_jet1_N0 = deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedJets_Eta.at(0), SelectedJets_Phi.at(0));
							DeltaEta_photon1_jet1_N0 = deltaEta(SelectedPhotons_Eta.at(0), SelectedJets_Eta.at(0));
							DeltaPhi_photon1_jet1_N0 = abs(deltaPhi(SelectedPhotons_Phi.at(0), SelectedJets_Phi.at(0)));

							DeltaR_photon1_jet1_N0_->Fill(DeltaR_photon1_jet1_N0, weight_final);
							DeltaEta_photon1_jet1_N0_->Fill(DeltaEta_photon1_jet1_N0, weight_final);
							DeltaPhi_photon1_jet1_N0_->Fill(DeltaPhi_photon1_jet1_N0, weight_final);

							phiTA = atan2(TA[1],TA[0]);
							dphi_TA_BAxis = abs(deltaPhi(phiTA, SelectedPhotons_Phi.at(0)));
							if(dphi_TA_BAxis > M_PI/2.0){
								dphi_TA_BAxis = M_PI-dphi_TA_BAxis;
							}
							dphi_TA_J1Axis = abs(deltaPhi(phiTA, SelectedJets_Phi.at(0)));
							if(dphi_TA_J1Axis > M_PI/2.0){
								dphi_TA_J1Axis=M_PI-dphi_TA_J1Axis;
							}
							if(myEvshpV[2] <= 0){
								myEvshpV[2] = 10e-15;
							}
							thrust = myEvshpV[2];
							broad = myEvshpV[6];
							S3 = myEvshpV[8];
							S4 = myEvshpV[9];

							thrust_N0_->Fill(thrust, weight_final);
							broad_N0_->Fill(broad, weight_final);
							S3_N0_->Fill(S3, weight_final);
							S4_N0_->Fill(S4, weight_final);

							ln_thrust = log(thrust);
							ln_broad = log(broad);
							ln_S3 = log(S3);
							ln_S4 = log(S4);

							ln_thrust_N0_->Fill(ln_thrust, weight_final);
							ln_broad_N0_->Fill(ln_broad, weight_final);
							ln_S3_N0_->Fill(ln_S3, weight_final);
							ln_S4_N0_->Fill(ln_S4, weight_final);

							if(Sig){
								unf_SelectedPhotons_Pt_N0_1 = SelectedPhotons_Pt.at(0);
								unf_SelectedJets_N_N0 = SelectedJets_N;
								unf_SelectedJets_HT_N0 = SelectedJets_HT;
							}
							
							if (SelectedJets_N == 1){

								unf_selREC_excl1 = true;
								SelectedPhotons_Pt_excl1_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
								SelectedPhotons_E_excl1_1_->Fill(SelectedPhotons_E.at(0), weight_final);
								SelectedPhotons_Eta_excl1_1_->Fill(SelectedPhotons_Eta.at(0), weight_final);
								SelectedPhotons_Phi_excl1_1_->Fill(SelectedPhotons_Phi.at(0), weight_final);

								SelectedJets_Pt_excl1_1_->Fill(SelectedJets_Pt.at(0), weight_final);
								SelectedJets_E_excl1_1_->Fill(SelectedJets_E.at(0), weight_final);
								SelectedJets_Eta_excl1_1_->Fill(SelectedJets_Eta.at(0), weight_final);
								SelectedJets_Phi_excl1_1_->Fill(SelectedJets_Phi.at(0), weight_final);

								SelectedJets_HT_excl1_->Fill(SelectedJets_HT, weight_final);

								if(Sig){								
									unf_SelectedPhotons_Pt_excl1_1 = SelectedPhotons_Pt.at(0);
									unf_SelectedJets_N_excl1 = SelectedJets_N;
									unf_SelectedJets_HT_excl1 = SelectedJets_HT;
								}
							}
							
							if (SelectedJets_N == 2){

								unf_selREC_excl2 = true;							
								SelectedPhotons_Pt_excl2_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
								SelectedPhotons_E_excl2_1_->Fill(SelectedPhotons_E.at(0), weight_final);
								SelectedPhotons_Eta_excl2_1_->Fill(SelectedPhotons_Eta.at(0), weight_final);
								SelectedPhotons_Phi_excl2_1_->Fill(SelectedPhotons_Phi.at(0), weight_final);

								SelectedJets_Pt_excl2_1_->Fill(SelectedJets_Pt.at(0), weight_final);
								SelectedJets_E_excl2_1_->Fill(SelectedJets_E.at(0), weight_final);
								SelectedJets_Eta_excl2_1_->Fill(SelectedJets_Eta.at(0), weight_final);
								SelectedJets_Phi_excl2_1_->Fill(SelectedJets_Phi.at(0), weight_final);

								SelectedJets_Pt_excl2_2_->Fill(SelectedJets_Pt.at(1), weight_final);
								SelectedJets_E_excl2_2_->Fill(SelectedJets_E.at(1), weight_final);
								SelectedJets_Eta_excl2_2_->Fill(SelectedJets_Eta.at(1), weight_final);
								SelectedJets_Phi_excl2_2_->Fill(SelectedJets_Phi.at(1), weight_final);

								SelectedJets_HT_excl2_->Fill(SelectedJets_HT, weight_final);

								if(Sig){
									unf_SelectedPhotons_Pt_excl2_1 = SelectedPhotons_Pt.at(0);
									unf_SelectedJets_N_excl2 = SelectedJets_N;
									unf_SelectedJets_HT_excl2 = SelectedJets_HT;
								}
							}
							
							if (SelectedJets_N > 1){

								unf_selREC_N1 = true;
								SelectedJets_Pt_2_->Fill(SelectedJets_Pt.at(1), weight_final);
								SelectedJets_E_2_->Fill(SelectedJets_E.at(1), weight_final);
								SelectedJets_Eta_2_->Fill(SelectedJets_Eta.at(1), weight_final);
								SelectedJets_Phi_2_->Fill(SelectedJets_Phi.at(1), weight_final);

								DeltaPhi_photon1_jet1_N1 = abs(deltaPhi(SelectedPhotons_Phi.at(0), SelectedJets_Phi.at(0)));
								DeltaR_photon1_jet2_N1 = deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedJets_Eta.at(1), SelectedJets_Phi.at(1));
								DeltaR_jet1_jet2_N1 = deltaR(SelectedJets_Eta.at(0), SelectedJets_Phi.at(0), SelectedJets_Eta.at(1), SelectedJets_Phi.at(1));
								DeltaEta_jet1_jet2_N1 = deltaEta(SelectedJets_Eta.at(0), SelectedJets_Eta.at(1));
								DeltaPhi_jet1_jet2_N1 = abs(deltaPhi(SelectedJets_Phi.at(0), SelectedJets_Phi.at(1)));

								DeltaPhi_photon1_jet1_N1_->Fill(DeltaPhi_photon1_jet1_N1, weight_final);
								DeltaR_photon1_jet2_N1_->Fill(DeltaR_photon1_jet2_N1, weight_final);
								DeltaR_jet1_jet2_N1_->Fill(DeltaR_jet1_jet2_N1, weight_final);
								DeltaEta_jet1_jet2_N1_->Fill(DeltaEta_jet1_jet2_N1, weight_final);
								DeltaPhi_jet1_jet2_N1_->Fill(DeltaPhi_jet1_jet2_N1, weight_final);

								if(Sig){
									unf_SelectedPhotons_Pt_N1_1 = SelectedPhotons_Pt.at(0);
									unf_SelectedJets_N_N1 = SelectedJets_N;
									unf_SelectedJets_HT_N1 = SelectedJets_HT;
								}
							}
	
							if (SelectedJets_N > 2){
							
								unf_selREC_N2 = true;							
								SelectedJets_Pt_3_->Fill(SelectedJets_Pt.at(2), weight_final);
								SelectedJets_E_3_->Fill(SelectedJets_E.at(2), weight_final);
								SelectedJets_Eta_3_->Fill(SelectedJets_Eta.at(2), weight_final);
								SelectedJets_Phi_3_->Fill(SelectedJets_Phi.at(2), weight_final);

								DeltaPhi_photon1_jet1_N2 = abs(deltaPhi(SelectedPhotons_Phi.at(0), SelectedJets_Phi.at(0)));
								DeltaPhi_photon1_jet2_N2 = abs(deltaPhi(SelectedPhotons_Phi.at(0), SelectedJets_Phi.at(1)));
								DeltaPhi_photon1_jet3_N2 = abs(deltaPhi(SelectedPhotons_Phi.at(0), SelectedJets_Phi.at(2)));
								DeltaR_photon1_jet3_N2 = deltaR(SelectedPhotons_Eta.at(0), SelectedPhotons_Phi.at(0), SelectedJets_Eta.at(2), SelectedJets_Phi.at(2));
								DeltaPhi_jet1_jet2_N2 = abs(deltaPhi(SelectedJets_Phi.at(0), SelectedJets_Phi.at(1)));
								DeltaPhi_jet1_jet3_N2 = abs(deltaPhi(SelectedJets_Phi.at(0), SelectedJets_Phi.at(2)));
								DeltaPhi_jet2_jet3_N2 = abs(deltaPhi(SelectedJets_Phi.at(1), SelectedJets_Phi.at(2)));
																
								DeltaPhi_photon1_jet1_N2_->Fill(DeltaPhi_photon1_jet1_N2, weight_final);
								DeltaPhi_photon1_jet2_N2_->Fill(DeltaPhi_photon1_jet2_N2, weight_final);
								DeltaPhi_photon1_jet3_N2_->Fill(DeltaPhi_photon1_jet3_N2, weight_final);
								DeltaR_photon1_jet3_N2_->Fill(DeltaR_photon1_jet3_N2, weight_final);
								DeltaPhi_jet1_jet2_N2_->Fill(DeltaPhi_jet1_jet2_N2, weight_final);
								DeltaPhi_jet1_jet3_N2_->Fill(DeltaPhi_jet1_jet3_N2, weight_final);
								DeltaPhi_jet2_jet3_N2_->Fill(DeltaPhi_jet2_jet3_N2, weight_final);								

								if(Sig){
									unf_SelectedPhotons_Pt_N2_1 = SelectedPhotons_Pt.at(0);
									unf_SelectedJets_N_N2 = SelectedJets_N;
									unf_SelectedJets_HT_N2 = SelectedJets_HT;
								}
							}
							
							if(isMC){
								photonIsoSumPtDR03GEN_->Fill(photonIsoSumPtDR03GEN, 1);
							}
							
						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end TriMatch+(ID+Iso)+kin Photons selection (then, on the LEADING one)
			} // end Isolation at GEN level
		}// end trigger family selection
		
		// clean jets
		SelectedJetsALL_N = 0;
		SelectedJets_N = 0;
		SelectedJets_HT = 0;
				
		Jets_deltaR_predeltaR.clear();
		Jets_Pt_preAcc.clear();
		Jets_Eta_preAcc.clear();

		SelectedJets_Pt.clear();
		SelectedJets_E.clear();
		SelectedJets_Eta.clear();
		SelectedJets_Phi.clear();

		vPtEtaPhiE.clear();
		// end clean jets

		// clean photons
		IDIsoPhotons_N = 0;
		SelectedPhotons_N = 0;

		photonTriMatchF4Path_AND_pTrange.clear();
		photonTri_PF.clear();
		photonTeP_SF.clear();
		photonBackDataDriven_F.clear();			

		Photons_Pt_prePassConversionVeto.clear();	
		Photon_PassConversionVeto_prePassConversionVeto.clear();
		Tri_PF_prePassConversionVeto.clear();
		TeP_SF_prePassConversionVeto.clear();
		BackDataDriven_F_prePassConversionVeto.clear();

		Photons_Pt_prehadronicOverEm2012.clear();	
		Photons_hadronicOverEm2012_prehadronicOverEm2012.clear();	
		Tri_PF_prehadronicOverEm2012.clear();
		TeP_SF_prehadronicOverEm2012.clear();
		BackDataDriven_F_prehadronicOverEm2012.clear();
		
		Photons_Pt_presigmaietaieta.clear();	
		Photons_sigmaietaieta_presigmaietaieta.clear();	
		Tri_PF_presigmaietaieta.clear();
		TeP_SF_presigmaietaieta.clear();
		BackDataDriven_F_presigmaietaieta.clear();
		
		Photons_Pt_preiso_CH.clear();	
		Photons_iso_CH_preiso_CH.clear();	
		Tri_PF_preiso_CH.clear();
		TeP_SF_preiso_CH.clear();
		BackDataDriven_F_preiso_CH.clear();
		
		Photons_Pt_preiso_NH.clear();	
		Photons_iso_NH_preiso_NH.clear();	
		Tri_PF_preiso_NH.clear();
		TeP_SF_preiso_NH.clear();
		BackDataDriven_F_preiso_NH.clear();
		
		Photons_Pt_preiso_Ph.clear();	
		Photons_iso_Ph_preiso_Ph.clear();	
		Tri_PF_preiso_Ph.clear();
		TeP_SF_preiso_Ph.clear();
		BackDataDriven_F_preiso_Ph.clear();

		Photons_Pt_preAcc.clear();
		Photons_Eta_preAcc.clear();
		Tri_PF_preAcc.clear();
		TeP_SF_preAcc.clear();
		BackDataDriven_F_preAcc.clear();

		Photons_Pt_preTriMatch.clear();
		Tri_PF_preTriMatch.clear();
		TeP_SF_preTriMatch.clear();
		BackDataDriven_F_preTriMatch.clear();

		SelectedPhotons_Pt.clear();
		SelectedPhotons_E.clear();
		SelectedPhotons_Eta.clear();
		SelectedPhotons_Phi.clear();

		SelectedPhotons_PassConversionVeto.clear();

		SelectedPhotons_PfIsoChargedHad.clear();
		SelectedPhotons_PfIsoNeutralHad.clear();
		SelectedPhotons_PfIsoPhoton.clear();
		SelectedPhotons_PfIso.clear();

		SelectedPhotons_PfIsoChargedHad_RhoCorr.clear();
		SelectedPhotons_PfIsoNeutralHad_RhoCorr.clear();
		SelectedPhotons_PfIsoPhoton_RhoCorr.clear();
		SelectedPhotons_PfIso_RhoCorr.clear();

		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit.clear();
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit.clear();
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit.clear();
		SelectedPhotons_PfIso_RhoCorr_forFit.clear();

		SelectedPhotons_PfIsoPhotons03ForCic.clear();
		SelectedPhotons_PfIsoNeutrals03ForCic.clear();
		SelectedPhotons_PfIsoCharged03ForCicVtx0.clear();
		SelectedPhotons_PfIsoCharged03BadForCic.clear();

		SelectedPhotons_PfIsoPhotons04ForCic.clear();
		SelectedPhotons_PfIsoNeutrals04ForCic.clear();
		SelectedPhotons_PfIsoCharged04ForCicVtx0.clear();
		SelectedPhotons_PfIsoCharged04BadForCic.clear();

		SelectedPhotons_id_sieie.clear();
		SelectedPhotons_id_sieip.clear();
		SelectedPhotons_id_etawidth.clear();
		SelectedPhotons_id_phiwidth.clear();
		SelectedPhotons_id_r9.clear();
		SelectedPhotons_id_lambdaRatio.clear();
		SelectedPhotons_id_s4Ratio.clear();
		SelectedPhotons_id_e25.clear();
		SelectedPhotons_id_sceta.clear();

		SelectedPhotons_id_ESEffSigmaRR.clear();
		SelectedPhotons_id_hadronicOverEm.clear();
		SelectedPhotons_id_hadronicOverEm2012.clear();

		SelectedPhotons_hcalTowerSumEtConeDR04.clear();
		SelectedPhotons_ecalRecHitSumEtConeDR04.clear();
		SelectedPhotons_nTrkSolidConeDR04.clear();
		SelectedPhotons_trkSumPtSolidConeDR04.clear();
		SelectedPhotons_nTrkHollowConeDR04.clear();
		SelectedPhotons_trkSumPtHollowConeDR04.clear();

		SelectedPhotons_IsoFPRCharged.clear();
		SelectedPhotons_IsoFPRNeutral.clear();
		SelectedPhotons_IsoFPRPhoton.clear();
		SelectedPhotons_IsoFPR.clear();
		SelectedPhotons_IsoFPRRandomConeCharged.clear();
		SelectedPhotons_IsoFPRRandomConeNeutral.clear();
		SelectedPhotons_IsoFPRRandomConePhoton.clear();

		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit.clear();
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit.clear();
			
		SelectedPhotons_Bit.clear();

		SelectedPhotons_TriMatchF4Path_AND_pTrange.clear();
		SelectedPhotons_Tri_PF.clear();
		SelectedPhotons_TeP_SF.clear();
		SelectedPhotons_BackDataDriven_F.clear();				
		// end clean photons
			 

		// ==================================== unfolding

		// N0
		if (Sig && unf_selGEN_N0){
			unf_photonPtGEN_N0_->Fill(unf_photonPtGEN_N0, weight_withPU);
			unf_SelectedJetsGEN_N_N0_->Fill(unf_SelectedJetsGEN_N_N0, weight_withPU);
			unf_SelectedJetsGEN_HT_N0_->Fill(unf_SelectedJetsGEN_HT_N0, weight_withPU);
		}
		if (Sig && unf_selREC_N0){
			unf_SelectedPhotons_Pt_N0_1_->Fill(unf_SelectedPhotons_Pt_N0_1, weight_final);
			unf_SelectedJets_N_N0_->Fill(unf_SelectedJets_N_N0, weight_final);
			unf_SelectedJets_HT_N0_->Fill(unf_SelectedJets_HT_N0, weight_final);
		}
		if (Sig && (unf_selGEN_N0 && unf_selREC_N0)){
			TH2F_unf_GENREC_Photons_Pt_N0_->Fill(unf_photonPtGEN_N0, unf_SelectedPhotons_Pt_N0_1, weight_final);
			TH2F_unf_GENREC_Jets_N_N0_->Fill(unf_SelectedJetsGEN_N_N0, unf_SelectedJets_N_N0, weight_final);
			TH2F_unf_GENREC_Jets_HT_N0_->Fill(unf_SelectedJetsGEN_HT_N0, unf_SelectedJets_HT_N0, weight_final);
		}
		
		// excl1
		if (Sig && unf_selGEN_excl1){
			unf_photonPtGEN_excl1_->Fill(unf_photonPtGEN_excl1, weight_withPU);
			unf_SelectedJetsGEN_N_excl1_->Fill(unf_SelectedJetsGEN_N_excl1, weight_withPU);
			unf_SelectedJetsGEN_HT_excl1_->Fill(unf_SelectedJetsGEN_HT_excl1, weight_withPU);
		}
		if (Sig && unf_selREC_excl1){
			unf_SelectedPhotons_Pt_excl1_1_->Fill(unf_SelectedPhotons_Pt_excl1_1, weight_final);
			unf_SelectedJets_N_excl1_->Fill(unf_SelectedJets_N_excl1, weight_final);
			unf_SelectedJets_HT_excl1_->Fill(unf_SelectedJets_HT_excl1, weight_final);
		}
		if (Sig && (unf_selGEN_excl1 && unf_selREC_excl1)){
			TH2F_unf_GENREC_Photons_Pt_excl1_->Fill(unf_photonPtGEN_excl1, unf_SelectedPhotons_Pt_excl1_1, weight_final);
			TH2F_unf_GENREC_Jets_N_excl1_->Fill(unf_SelectedJetsGEN_N_excl1, unf_SelectedJets_N_excl1, weight_final);
			TH2F_unf_GENREC_Jets_HT_excl1_->Fill(unf_SelectedJetsGEN_HT_excl1, unf_SelectedJets_HT_excl1, weight_final);
		}

		// excl2
		if (Sig && unf_selGEN_excl2){
			unf_photonPtGEN_excl2_->Fill(unf_photonPtGEN_excl2, weight_withPU);
			unf_SelectedJetsGEN_N_excl2_->Fill(unf_SelectedJetsGEN_N_excl2, weight_withPU);
			unf_SelectedJetsGEN_HT_excl2_->Fill(unf_SelectedJetsGEN_HT_excl2, weight_withPU);
		}
		if (Sig && unf_selREC_excl2){
			unf_SelectedPhotons_Pt_excl2_1_->Fill(unf_SelectedPhotons_Pt_excl2_1, weight_final);
			unf_SelectedJets_N_excl2_->Fill(unf_SelectedJets_N_excl2, weight_final);
			unf_SelectedJets_HT_excl2_->Fill(unf_SelectedJets_HT_excl2, weight_final);
		}
		if (Sig && (unf_selGEN_excl2 && unf_selREC_excl2)){
			TH2F_unf_GENREC_Photons_Pt_excl2_->Fill(unf_photonPtGEN_excl2, unf_SelectedPhotons_Pt_excl2_1, weight_final);
			TH2F_unf_GENREC_Jets_N_excl2_->Fill(unf_SelectedJetsGEN_N_excl2, unf_SelectedJets_N_excl2, weight_final);
			TH2F_unf_GENREC_Jets_HT_excl2_->Fill(unf_SelectedJetsGEN_HT_excl2, unf_SelectedJets_HT_excl2, weight_final);
		}

		// N1
		if (Sig && unf_selGEN_N1){
			unf_photonPtGEN_N1_->Fill(unf_photonPtGEN_N1, weight_withPU);
			unf_SelectedJetsGEN_N_N1_->Fill(unf_SelectedJetsGEN_N_N1, weight_withPU);
			unf_SelectedJetsGEN_HT_N1_->Fill(unf_SelectedJetsGEN_HT_N1, weight_withPU);
		}
		if (Sig && unf_selREC_N1){		
			unf_SelectedPhotons_Pt_N1_1_->Fill(unf_SelectedPhotons_Pt_N1_1, weight_final);
			unf_SelectedJets_N_N1_->Fill(unf_SelectedJets_N_N1, weight_final);
			unf_SelectedJets_HT_N1_->Fill(unf_SelectedJets_HT_N1, weight_final);
		}
		if (Sig && (unf_selGEN_N1 && unf_selREC_N1)){
			TH2F_unf_GENREC_Photons_Pt_N1_->Fill(unf_photonPtGEN_N1, unf_SelectedPhotons_Pt_N1_1, weight_final);
			TH2F_unf_GENREC_Jets_N_N1_->Fill(unf_SelectedJetsGEN_N_N1, unf_SelectedJets_N_N1, weight_final);
			TH2F_unf_GENREC_Jets_HT_N1_->Fill(unf_SelectedJetsGEN_HT_N1, unf_SelectedJets_HT_N1, weight_final);
		}

		//N2
		if (Sig && unf_selGEN_N2){
			unf_photonPtGEN_N2_->Fill(unf_photonPtGEN_N2, weight_withPU);
			unf_SelectedJetsGEN_N_N2_->Fill(unf_SelectedJetsGEN_N_N2, weight_withPU);
			unf_SelectedJetsGEN_HT_N2_->Fill(unf_SelectedJetsGEN_HT_N2, weight_withPU);
		}
		if (Sig && unf_selREC_N2){		
			unf_SelectedPhotons_Pt_N2_1_->Fill(unf_SelectedPhotons_Pt_N2_1, weight_final);
			unf_SelectedJets_N_N2_->Fill(unf_SelectedJets_N_N2, weight_final);
			unf_SelectedJets_HT_N2_->Fill(unf_SelectedJets_HT_N2, weight_final);
		}
		if (Sig && (unf_selGEN_N2 && unf_selREC_N2)){
			TH2F_unf_GENREC_Photons_Pt_N2_->Fill(unf_photonPtGEN_N2, unf_SelectedPhotons_Pt_N2_1, weight_final);
			TH2F_unf_GENREC_Jets_N_N2_->Fill(unf_SelectedJetsGEN_N_N2, unf_SelectedJets_N_N2, weight_final);
			TH2F_unf_GENREC_Jets_HT_N2_->Fill(unf_SelectedJetsGEN_HT_N2, unf_SelectedJets_HT_N2, weight_final);
		}

		// if (Cut(ientry) < 0) continue;
	} // end loop on entries

	// ====================================terminate and plot

	cout << "Analysis selection:" << endl;
	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	cout << "Number of selected events 0 (Ntuple preselection), unweighted = " << iSelected0 << endl;
	cout << "Number of selected events 1 (trigger family 4), unweighted = " << iSelected1 << endl;		
	cout << "Number of selected events 2 (Iso at GEN level), unweighted = " << iSelected2 << endl;
	cout << "Number of selected events 3 (TriMatch+(ID+Iso)+kin Photons: then, on the LEADING one), unweighted = " << iSelected3 << endl;
	cout << "Number of selected events 4 (kin+PU Jets: then, cleaned vs. LEADING Photon), unweighted = " << iSelected4 << endl;
	cout << "Number of selected events 5 (HT), unweighted = " << iSelected5 << endl;
	cout << "Number of selected events (all selections), unweighted = " << iSelected5 << endl;
	cout << "Number of selected events (all selections), weighted = " << iSelected5*weight_r << endl;

	fhistos->Write();

	if (plothistos){
		Plot_Histos();
	}
	if (textfile){
		Text_File();
	}
}


// ----- methods ----------------

void GJetsAnalyzer::Book_Histos(){

	cout << "Booking histograms... " << endl;
	// book the histograms

	const Int_t NBINS = 21;
	Float_t edges[NBINS + 1] = {100.0, 111.0, 123.1, 136.6, 151.6, 168.2, 186.6, 207.1, 229.7, 254.9, 282.8, 313.8, 348.2, 386.4, 428.7, 475.7, 527.8, 585.6, 649.8, 721.0, 800.0, 2000};

	if(isMC){
	
		//plotsCompare_gen_01
		nPhotonsGEN_N0_ = new TH1F("nPhotonsGEN_N0_","Photons GEN N", 50, 0, 50);
		photonPtGEN_N0_ = new TH1F("photonPtGEN_N0_","Photon GEN p_{T}", 800, 0., 4000.);
		photonEGEN_N0_ = new TH1F("photonEGEN_N0_","Photon GEN E", 800, 0., 4000.);
		photonEtaGEN_N0_ = new TH1F("photonEtaGEN_N0_","Photon GEN #eta", 3000, -3, 3);
		photonPhiGEN_N0_ = new TH1F("photonPhiGEN_N0_","Photon GEN #varphi", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_02
		SelectedJetsGEN_N_N0_ = new TH1F("SelectedJetsGEN_N_N0_","Selected Jets GEN N", 10, 0, 10);
		SelectedJets_PtGEN_N0_1_ = new TH1F("SelectedJets_PtGEN_N0_1_","Jet 1 GEN p_{T} ", 800, 0., 4000.);
		SelectedJets_EGEN_N0_1_ = new TH1F("SelectedJets_EGEN_N0_1_", "Jet 1 GEN E", 800, 0., 4000.);
		SelectedJets_EtaGEN_N0_1_ = new TH1F("SelectedJets_EtaGEN_N0_1_","Jet 1 GEN #eta ", 3000, -3, 3);
		SelectedJets_PhiGEN_N0_1_ = new TH1F("SelectedJets_PhiGEN_N0_1_","Jet 1 GEN #varphi ", 1000, -3.1416, 3.1416);

		//plotsCompare_gen_03
		SelectedJetsGEN_HT_N0_ = new TH1F("SelectedJetsGEN_HT_N0_","Selected Jets H_{T} GEN", 400, 0, 4000);
		pre_photonIsoSumPtDR03GEN_ = new TH1F("pre_photonIsoSumPtDR03GEN_","photonIsoSumPtDR03GEN", 1300, -1100, 200);
		photonIsoSumPtDR03GEN_ = new TH1F("photonIsoSumPtDR03GEN_","photonIsoSumPtDR03GEN", 1300, -1100, 200);
		HTParSum_ = new TH1F("HTParSum_","H_{T} Partons Sum", 800, 0, 4000);

		//plotsCompare_gen_04
		photonPtGEN_excl1_ = new TH1F("photonPtGEN_excl1_","Photon GEN p_{T}, N^{jets}_{GEN} = 1", 800, 0., 4000.);
		photonPtGEN_excl2_ = new TH1F("photonPtGEN_excl2_","Photon GEN p_{T}, N^{jets}_{GEN} = 2", 800, 0., 4000.);
		photonPtGEN_N1_ = new TH1F("photonPtGEN_N1_","Photon GEN p_{T}, N^{jets}_{GEN} > 1", 800, 0., 4000.);
		photonPtGEN_N2_ = new TH1F("photonPtGEN_N2_","Photon GEN p_{T}, N^{jets}_{GEN} > 2", 800, 0., 4000.);
	}


	//plotsCompare_01
	IDIsoPhotons_N_ = new TH1F("IDIsoPhotons_N_","ID-Iso Photons N", 10, 0, 10);
	SelectedPhotons_N_ = new TH1F("SelectedPhotons_N_","Selected Photons N", 10, 0, 10);

	Nvtx_ = new TH1F("Nvtx_","Number of vertices ", 50, 0, 50);

	SelectedPhotons_Pt_1_ = new TH1F("SelectedPhotons_Pt_1_","Photon p_{T} ", 800, 0., 4000.);
	SelectedPhotons_Pt_LogBin_1_ = new TH1F("SelectedPhotons_Pt_LogBin_1_","Photon p_{T} ", NBINS, edges);
	SelectedPhotons_E_1_ = new TH1F("SelectedPhotons_E_1_","Photon E ", 800, 0., 4000.);
	SelectedPhotons_Eta_1_ = new TH1F("SelectedPhotons_Eta_1_","Photon #eta ", 3000, -3, 3);
	SelectedPhotons_Phi_1_ = new TH1F("SelectedPhotons_Phi_1_","Photon #varphi ", 1000, -3.1416, 3.1416);
	SelectedPhotons_Bit_1_ = new TH1F("SelectedPhotons_Bit_1_","Photon bit ", 100, 0., 1000.);

	SelectedPhotons_TriMatchF4Path_AND_pTrange_1_ = new TH1F("SelectedPhotons_TriMatchF4Path_AND_pTrange_1_","Photon Trigger Matching result", 2, -1, 3.);
	SelectedPhotons_Tri_PF_1_ = new TH1F("SelectedPhotons_Tri_PF_1_","Photon Trigger Prescale ", 200, 0., 1.);
	SelectedPhotons_TeP_SF_1_ = new TH1F("SelectedPhotons_TeP_SF_1_","Photon SF ", 200, 0.9, 1.1);
	SelectedPhotons_BackDataDriven_F_1_ = new TH1F("SelectedPhotons_BackDataDriven_F_1_","Photon background data-driven F", 100, 0., 1.);

	//plotsCompare_02
	SelectedPhotons_PassConversionVeto_1_ = new TH1F("SelectedPhotons_PassConversionVeto_1_","photonPassConversionVeto ", 10, -2, 2);
	
	SelectedPhotons_PfIsoChargedHad_1_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_", "photon PfIsoChargedHad", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_", "photon PfIsoNeutralHad", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_", "photon PfIsoPhoton", 2000, 0, 200);
	SelectedPhotons_PfIso_1_ = new TH1F("SelectedPhotons_PfIso_1_", "photon PfIso", 2000, 0, 200);

	//plotsCompare_03
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_", "photon PfIsoChargedHad #rho corrected", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_", "photon PfIsoNeutralHad #rho corrected", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_", "photon PfIsoPhoton #rho corrected", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_", "photon PfIso #rho corrected", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_", "photon PfIsoChargedHad #rho corrected for Fit", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_", "photon PfIsoNeutralHad #rho corrected for Fit", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_", "photon PfIsoPhoton #rho corrected for Fit", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_PfIso_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_", "photon PfIso #rho corrected for Fit", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_04
	SelectedPhotons_id_sieie_1_bin01_ = new TH1F("SelectedPhotons_id_sieie_1_bin01_", "photon ID: #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 151.6", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin01_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin01_", "photon PfIsoChargedHad, 100 < p_{T}^{#gamma} < 151.6", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin01_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin01_", "photon PfIsoNeutralHad, 100 < p_{T}^{#gamma} < 151.6", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin01_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin01_", "photon PfIsoPhoton, 100 < p_{T}^{#gamma} < 151.6", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin01_ = new TH1F("SelectedPhotons_PfIso_1_bin01_", "photon PfIso, 100 < p_{T}^{#gamma} < 151.6", 2000, 0, 200);

	//plotsCompare_05
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_", "photon PfIsoChargedHad #rho corrected, 100 < p_{T}^{#gamma} < 151.6", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_", "photon PfIsoNeutralHad #rho corrected, 100 < p_{T}^{#gamma} < 151.6", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_", "photon PfIsoPhoton #rho corrected, 100 < p_{T}^{#gamma} < 151.6", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin01_", "photon PfIso #rho corrected, 100 < p_{T}^{#gamma} < 151.6", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 151.6", 500, 0., 0.050, 2000, 0, 200);
	
	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_", "photon PfIsoChargedHad #rho corrected for Fit, 100 < p_{T}^{#gamma} < 151.6", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_", "photon PfIsoNeutralHad #rho corrected for Fit, 100 < p_{T}^{#gamma} < 151.6", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_", "photon PfIsoPhoton #rho corrected for Fit, 100 < p_{T}^{#gamma} < 151.6", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin01_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin01_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 151.6", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_", "photon PfIso #rho corrected for Fit, 100 < p_{T}^{#gamma} < 151.6", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 151.6", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin01_", "photon IsoFPRPhoton #rho corrected for Fit, 100 < p_{T}^{#gamma} < 151.6", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin01_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 100 < p_{T}^{#gamma} < 151.6", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin01_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin01_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 151.6", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin01_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin01_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 100 < p_{T}^{#gamma} < 151.6", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_06
	SelectedPhotons_id_sieie_1_bin02_ = new TH1F("SelectedPhotons_id_sieie_1_bin02_", "photon ID: #sigma_{i#etai#eta}, 151.6 < p_{T}^{#gamma} < 207.1", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin02_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin02_", "photon PfIsoChargedHad, 151.6 < p_{T}^{#gamma} < 207.1", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin02_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin02_", "photon PfIsoNeutralHad, 151.6 < p_{T}^{#gamma} < 207.1", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin02_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin02_", "photon PfIsoPhoton, 151.6 < p_{T}^{#gamma} < 207.1", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin02_ = new TH1F("SelectedPhotons_PfIso_1_bin02_", "photon PfIso, 151.6 < p_{T}^{#gamma} < 207.1", 2000, 0, 200);

	//plotsCompare_07
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_", "photon PfIsoChargedHad #rho corrected, 151.6 < p_{T}^{#gamma} < 207.1", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_", "photon PfIsoNeutralHad #rho corrected, 151.6 < p_{T}^{#gamma} < 207.1", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_", "photon PfIsoPhoton #rho corrected, 151.6 < p_{T}^{#gamma} < 207.1", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin02_", "photon PfIso #rho corrected, 151.6 < p_{T}^{#gamma} < 207.1", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 151.6 < p_{T}^{#gamma} < 207.1", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_", "photon PfIsoChargedHad #rho corrected for Fit, 151.6 < p_{T}^{#gamma} < 207.1", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_", "photon PfIsoNeutralHad #rho corrected for Fit, 151.6 < p_{T}^{#gamma} < 207.1", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_", "photon PfIsoPhoton #rho corrected for Fit, 151.6 < p_{T}^{#gamma} < 207.1", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin02_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin02_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 151.6 < p_{T}^{#gamma} < 207.1", 500, 0., 0.050, 4000, -200, 200);	
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_", "photon PfIso #rho corrected for Fit, 151.6 < p_{T}^{#gamma} < 207.1", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 151.6 < p_{T}^{#gamma} < 207.1", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin02_", "photon IsoFPRPhoton #rho corrected for Fit, 151.6 < p_{T}^{#gamma} < 207.1", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin02_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 151.6 < p_{T}^{#gamma} < 207.1", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin02_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin02_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 151.6 < p_{T}^{#gamma} < 207.1", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin02_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin02_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 151.6 < p_{T}^{#gamma} < 207.1", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_08
	SelectedPhotons_id_sieie_1_bin03_ = new TH1F("SelectedPhotons_id_sieie_1_bin03_", "photon ID: #sigma_{i#etai#eta}, 207.1 < p_{T}^{#gamma} < 313.8", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin03_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin03_", "photon PfIsoChargedHad, 207.1 < p_{T}^{#gamma} < 313.8", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin03_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin03_", "photon PfIsoNeutralHad, 207.1 < p_{T}^{#gamma} < 313.8", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin03_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin03_", "photon PfIsoPhoton, 207.1 < p_{T}^{#gamma} < 313.8", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin03_ = new TH1F("SelectedPhotons_PfIso_1_bin03_", "photon PfIso, 207.1 < p_{T}^{#gamma} < 313.8", 2000, 0, 200);

	//plotsCompare_09
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_", "photon PfIsoChargedHad #rho corrected, 207.1 < p_{T}^{#gamma} < 313.8", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_", "photon PfIsoNeutralHad #rho corrected, 207.1 < p_{T}^{#gamma} < 313.8", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_", "photon PfIsoPhoton #rho corrected, 207.1 < p_{T}^{#gamma} < 313.8", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin03_", "photon PfIso #rho corrected, 207.1 < p_{T}^{#gamma} < 313.8", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 207.1 < p_{T}^{#gamma} < 313.8", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_", "photon PfIsoChargedHad #rho corrected for Fit, 207.1 < p_{T}^{#gamma} < 313.8", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_", "photon PfIsoNeutralHad #rho corrected for Fit, 207.1 < p_{T}^{#gamma} < 313.8", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_", "photon PfIsoPhoton #rho corrected for Fit, 207.1 < p_{T}^{#gamma} < 313.8", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin03_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin03_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 207.1 < p_{T}^{#gamma} < 313.8", 500, 0., 0.050, 4000, -200, 200);	
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_", "photon PfIso #rho corrected for Fit, 207.1 < p_{T}^{#gamma} < 313.8", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 207.1 < p_{T}^{#gamma} < 313.8", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin03_", "photon IsoFPRPhoton #rho corrected for Fit, 207.1 < p_{T}^{#gamma} < 313.8", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin03_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 207.1 < p_{T}^{#gamma} < 313.8", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin03_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin03_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 207.1 < p_{T}^{#gamma} < 313.8", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin03_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin03_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 207.1 < p_{T}^{#gamma} < 313.8", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_10
	SelectedPhotons_id_sieie_1_bin04_ = new TH1F("SelectedPhotons_id_sieie_1_bin04_", "photon ID: #sigma_{i#etai#eta}, 313.8 < p_{T}^{#gamma} < 649.8", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin04_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin04_", "photon PfIsoChargedHad, 313.8 < p_{T}^{#gamma} < 649.8", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin04_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin04_", "photon PfIsoNeutralHad, 313.8 < p_{T}^{#gamma} < 649.8", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin04_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin04_", "photon PfIsoPhoton, 313.8 < p_{T}^{#gamma} < 649.8", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin04_ = new TH1F("SelectedPhotons_PfIso_1_bin04_", "photon PfIso, 313.8 < p_{T}^{#gamma} < 649.8", 2000, 0, 200);

	//plotsCompare_11
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_", "photon PfIsoChargedHad #rho corrected, 313.8 < p_{T}^{#gamma} < 649.8", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_", "photon PfIsoNeutralHad #rho corrected, 313.8 < p_{T}^{#gamma} < 649.8", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_", "photon PfIsoPhoton #rho corrected, 313.8 < p_{T}^{#gamma} < 649.8", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin04_", "photon PfIso #rho corrected, 313.8 < p_{T}^{#gamma} < 649.8", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 313.8 < p_{T}^{#gamma} < 649.8", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_", "photon PfIsoChargedHad #rho corrected for Fit, 313.8 < p_{T}^{#gamma} < 649.8", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_", "photon PfIsoNeutralHad #rho corrected for Fit, 313.8 < p_{T}^{#gamma} < 649.8", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_", "photon PfIsoPhoton #rho corrected for Fit, 313.8 < p_{T}^{#gamma} < 649.8", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin04_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin04_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 313.8 < p_{T}^{#gamma} < 649.8", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_", "photon PfIso #rho corrected for Fit, 313.8 < p_{T}^{#gamma} < 649.8", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 313.8 < p_{T}^{#gamma} < 649.8", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin04_", "photon IsoFPRPhoton #rho corrected for Fit, 313.8 < p_{T}^{#gamma} < 649.8", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin04_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 313.8 < p_{T}^{#gamma} < 649.8", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin04_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin04_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 313.8 < p_{T}^{#gamma} < 649.8", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin04_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin04_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 313.8 < p_{T}^{#gamma} < 649.8", 500, 0., 0.050, 4000, -200, 200);
	
	//plotsCompare_12
	SelectedPhotons_id_sieie_1_bin05_ = new TH1F("SelectedPhotons_id_sieie_1_bin05_", "photon ID: #sigma_{i#etai#eta}, 649.8 < p_{T}^{#gamma} < 800", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin05_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin05_", "photon PfIsoChargedHad, 649.8 < p_{T}^{#gamma} < 800", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin05_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin05_", "photon PfIsoNeutralHad, 649.8 < p_{T}^{#gamma} < 800", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin05_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin05_", "photon PfIsoPhoton, 649.8 < p_{T}^{#gamma} < 800", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin05_ = new TH1F("SelectedPhotons_PfIso_1_bin05_", "photon PfIso, 649.8 < p_{T}^{#gamma} < 800", 2000, 0, 200);

	//plotsCompare_13
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_", "photon PfIsoChargedHad #rho corrected, 649.8 < p_{T}^{#gamma} < 800", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_", "photon PfIsoNeutralHad #rho corrected, 649.8 < p_{T}^{#gamma} < 800", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_", "photon PfIsoPhoton #rho corrected, 649.8 < p_{T}^{#gamma} < 800", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin05_", "photon PfIso #rho corrected, 649.8 < p_{T}^{#gamma} < 800", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 649.8 < p_{T}^{#gamma} < 800", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_", "photon PfIsoChargedHad #rho corrected for Fit, 649.8 < p_{T}^{#gamma} < 800", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_", "photon PfIsoNeutralHad #rho corrected for Fit, 649.8 < p_{T}^{#gamma} < 800", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_", "photon PfIsoPhoton #rho corrected for Fit, 649.8 < p_{T}^{#gamma} < 800", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin05_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin05_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 649.8 < p_{T}^{#gamma} < 800", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_", "photon PfIso #rho corrected for Fit, 649.8 < p_{T}^{#gamma} < 800", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 649.8 < p_{T}^{#gamma} < 800", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin05_", "photon IsoFPRPhoton #rho corrected for Fit, 649.8 < p_{T}^{#gamma} < 800", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin05_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 649.8 < p_{T}^{#gamma} < 800", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin05_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin05_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 649.8 < p_{T}^{#gamma} < 800", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin05_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin05_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 649.8 < p_{T}^{#gamma} < 800", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_14
	SelectedPhotons_id_sieie_1_bin06_ = new TH1F("SelectedPhotons_id_sieie_1_bin06_", "photon ID: #sigma_{i#etai#eta}, p_{T}^{#gamma} > 800", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin06_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin06_", "photon PfIsoChargedHad, p_{T}^{#gamma} > 800", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin06_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin06_", "photon PfIsoNeutralHad, p_{T}^{#gamma} > 800", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin06_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin06_", "photon PfIsoPhoton, p_{T}^{#gamma} > 800", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin06_ = new TH1F("SelectedPhotons_PfIso_1_bin06_", "photon PfIso, p_{T}^{#gamma} > 800", 2000, 0, 200);

	//plotsCompare_15
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_", "photon PfIsoChargedHad #rho corrected, p_{T}^{#gamma} > 800", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_", "photon PfIsoNeutralHad #rho corrected, p_{T}^{#gamma} > 800", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_", "photon PfIsoPhoton #rho corrected, p_{T}^{#gamma} > 800", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin06_", "photon PfIso #rho corrected, p_{T}^{#gamma} > 800", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 800", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_", "photon PfIsoChargedHad #rho corrected for Fit, p_{T}^{#gamma} > 800", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_", "photon PfIsoNeutralHad #rho corrected for Fit, p_{T}^{#gamma} > 800", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_", "photon PfIsoPhoton #rho corrected for Fit, p_{T}^{#gamma} > 800", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin06_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin06_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 800", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_", "photon PfIso #rho corrected for Fit, p_{T}^{#gamma} > 800", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 800", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin06_", "photon IsoFPRPhoton #rho corrected for Fit, p_{T}^{#gamma} > 800", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin06_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, p_{T}^{#gamma} > 800", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin06_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin06_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 800", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin06_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin06_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 800", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_16
	SelectedPhotons_id_sieie_1_bin07_ = new TH1F("SelectedPhotons_id_sieie_1_bin07_", "photon ID: #sigma_{i#etai#eta}, p_{T}^{#gamma} > 313.8", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin07_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin07_", "photon PfIsoChargedHad, p_{T}^{#gamma} > 313.8", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin07_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin07_", "photon PfIsoNeutralHad, p_{T}^{#gamma} > 313.8", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin07_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin07_", "photon PfIsoPhoton, p_{T}^{#gamma} > 313.8", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin07_ = new TH1F("SelectedPhotons_PfIso_1_bin07_", "photon PfIso, p_{T}^{#gamma} > 313.8", 2000, 0, 200);

	//plotsCompare_17
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_", "photon PfIsoChargedHad #rho corrected, p_{T}^{#gamma} > 313.8", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_", "photon PfIsoNeutralHad #rho corrected, p_{T}^{#gamma} > 313.8", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_", "photon PfIsoPhoton #rho corrected, p_{T}^{#gamma} > 313.8", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin07_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin07_", "photon PfIso #rho corrected, p_{T}^{#gamma} > 313.8", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin07_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin07_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 313.8", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_", "photon PfIsoChargedHad #rho corrected for Fit, p_{T}^{#gamma} > 313.8", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_", "photon PfIsoNeutralHad #rho corrected for Fit, p_{T}^{#gamma} > 313.8", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_", "photon PfIsoPhoton #rho corrected for Fit, p_{T}^{#gamma} > 313.8", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin07_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin07_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 313.8", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_", "photon PfIso #rho corrected for Fit, p_{T}^{#gamma} > 313.8", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin07_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin07_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 313.8", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin07_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin07_", "photon IsoFPRPhoton #rho corrected for Fit, p_{T}^{#gamma} > 313.8", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin07_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin07_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, p_{T}^{#gamma} > 313.8", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin07_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin07_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 313.8", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin07_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin07_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 313.8", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_18
	SelectedPhotons_id_sieie_1_bin08_ = new TH1F("SelectedPhotons_id_sieie_1_bin08_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin08_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin08_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin08_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin08_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin08_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin08_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin08_ = new TH1F("SelectedPhotons_PfIso_1_bin08_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_19
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin08_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin08_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin08_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin08_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin08_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin08_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin08_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin08_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin08_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin08_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin08_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin08_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin08_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin08_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin08_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin08_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_20
	SelectedPhotons_id_sieie_1_bin09_ = new TH1F("SelectedPhotons_id_sieie_1_bin09_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin09_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin09_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin09_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin09_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin09_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin09_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin09_ = new TH1F("SelectedPhotons_PfIso_1_bin09_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_21
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin09_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin09_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin09_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin09_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin09_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin09_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin09_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin09_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin09_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin09_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin09_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin09_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin09_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin09_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin09_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin09_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_22
	SelectedPhotons_id_sieie_1_bin10_ = new TH1F("SelectedPhotons_id_sieie_1_bin10_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin10_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin10_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin10_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin10_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin10_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin10_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin10_ = new TH1F("SelectedPhotons_PfIso_1_bin10_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_23
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin10_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin10_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin10_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin10_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin10_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin10_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin10_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin10_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin10_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin10_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin10_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin10_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin10_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin10_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin10_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin10_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_24
	SelectedPhotons_id_sieie_1_bin11_ = new TH1F("SelectedPhotons_id_sieie_1_bin11_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin11_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin11_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin11_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin11_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin11_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin11_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin11_ = new TH1F("SelectedPhotons_PfIso_1_bin11_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_25
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin11_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin11_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin11_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin11_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin11_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin11_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin11_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin11_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin11_= new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin11_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin11_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin11_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin11_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin11_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin11_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin11_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_26
	SelectedPhotons_id_sieie_1_bin12_ = new TH1F("SelectedPhotons_id_sieie_1_bin12_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin12_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin12_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin12_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin12_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin12_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin12_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin12_ = new TH1F("SelectedPhotons_PfIso_1_bin12_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_27
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin12_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin12_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin12_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin12_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin12_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin12_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin12_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin12_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin12_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin12_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin12_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin12_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin12_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin12_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin12_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin12_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_28
	SelectedPhotons_id_sieie_1_bin13_ = new TH1F("SelectedPhotons_id_sieie_1_bin13_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin13_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin13_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin13_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin13_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin13_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin13_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin13_ = new TH1F("SelectedPhotons_PfIso_1_bin13_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_29
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin13_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin13_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin13_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin13_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin13_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin13_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin13_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin13_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin13_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin13_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin13_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin13_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin13_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin13_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin13_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin13_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_30
	SelectedPhotons_id_sieie_1_bin14_ = new TH1F("SelectedPhotons_id_sieie_1_bin14_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin14_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin14_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin14_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin14_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin14_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin14_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin14_ = new TH1F("SelectedPhotons_PfIso_1_bin14_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_31
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin14_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin14_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin14_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin14_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin14_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin14_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin14_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin14_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin14_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin14_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin14_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin14_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin14_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin14_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin14_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin14_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_32
	SelectedPhotons_id_sieie_1_bin15_ = new TH1F("SelectedPhotons_id_sieie_1_bin15_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin15_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin15_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin15_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin15_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin15_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin15_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin15_ = new TH1F("SelectedPhotons_PfIso_1_bin15_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_33
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin15_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin15_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin15_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin15_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin15_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin15_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin15_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin15_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin15_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin15_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin15_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin15_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin15_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin15_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin15_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin15_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_34
	SelectedPhotons_id_sieie_1_bin16_ = new TH1F("SelectedPhotons_id_sieie_1_bin16_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin16_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin16_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin16_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin16_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin16_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin16_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin16_ = new TH1F("SelectedPhotons_PfIso_1_bin16_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_35
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin16_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin16_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin16_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin16_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin16_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin16_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin16_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin16_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin16_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin16_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin16_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin16_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin16_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin16_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin16_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin16_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_36
	SelectedPhotons_id_sieie_1_bin17_ = new TH1F("SelectedPhotons_id_sieie_1_bin17_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin17_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin17_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin17_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin17_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin17_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin17_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin17_ = new TH1F("SelectedPhotons_PfIso_1_bin17_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_37
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin17_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin17_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin17_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin17_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin17_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin17_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin17_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin17_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin17_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin17_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin17_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin17_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin17_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin17_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin17_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin17_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_38
	SelectedPhotons_id_sieie_1_bin18_ = new TH1F("SelectedPhotons_id_sieie_1_bin18_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin18_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin18_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin18_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin18_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin18_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin18_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin18_ = new TH1F("SelectedPhotons_PfIso_1_bin18_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_39
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin18_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin18_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin18_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin18_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin18_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin18_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin18_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin18_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin18_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin18_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin18_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin18_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin18_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin18_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin18_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin18_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_40
	SelectedPhotons_id_sieie_1_bin19_ = new TH1F("SelectedPhotons_id_sieie_1_bin19_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin19_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin19_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin19_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin19_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin19_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin19_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin19_ = new TH1F("SelectedPhotons_PfIso_1_bin19_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_41
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin19_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin19_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin19_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin19_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin19_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin19_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin19_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin19_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin19_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin19_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin19_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin19_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin19_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin19_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin19_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin19_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_42
	SelectedPhotons_id_sieie_1_bin20_ = new TH1F("SelectedPhotons_id_sieie_1_bin20_", "photon ID: #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin20_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin20_", "photon PfIsoChargedHad, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin20_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin20_", "photon PfIsoNeutralHad, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin20_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin20_", "photon PfIsoPhoton, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin20_ = new TH1F("SelectedPhotons_PfIso_1_bin20_", "photon PfIso, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);

	//plotsCompare_43
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_", "photon PfIsoChargedHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_", "photon PfIsoNeutralHad #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_", "photon PfIsoPhoton #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin20_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin20_", "photon PfIso #rho corrected, 10000 < p_{T}^{#gamma} < 100000", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin20_ = new TH2F("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin20_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_", "photon PfIsoChargedHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_", "photon PfIsoNeutralHad #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_", "photon PfIsoPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin20_ = new TH2F("TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin20_",  "photon PfIsoPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);		
	
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_", "photon PfIso #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin20_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin20_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin20_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin20_", "photon IsoFPRPhoton #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin20_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin20_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit, 10000 < p_{T}^{#gamma} < 100000", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin20_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin20_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin20_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin20_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 10000 < p_{T}^{#gamma} < 100000", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_44
	SelectedPhotons_PfIsoPhotons03ForCic_1_ = new TH1F("SelectedPhotons_PfIsoPhotons03ForCic_1_", "photon PfIsoPhotons03ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoNeutrals03ForCic_1_ = new TH1F("SelectedPhotons_PfIsoNeutrals03ForCic_1_","photon PfIsoNeutrals03ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged03ForCicVtx0_1_ = new TH1F("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "photon PfIsoCharged03ForCicVtx0", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged03BadForCic_1_ = new TH1F("SelectedPhotons_PfIsoCharged03BadForCic_1_", "photon PfIsoCharged03BadForCic", 2000, 0, 200);
	
	//plotsCompare_45
	SelectedPhotons_PfIsoPhotons04ForCic_1_ = new TH1F("SelectedPhotons_PfIsoPhotons04ForCic_1_", "photon PfIsoPhotons04ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoNeutrals04ForCic_1_ = new TH1F("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "photon PfIsoNeutrals04ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged04ForCicVtx0_1_ = new TH1F("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "photon PfIsoCharged04ForCicVtx0", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged04BadForCic_1_ = new TH1F("SelectedPhotons_PfIsoCharged04BadForCic_1_", "photonPfIsoCharged04BadForCic", 2000, 0, 200);
	
	//plotsCompare_46	
	SelectedPhotons_id_sieie_1_ = new TH1F("SelectedPhotons_id_sieie_1_", "photon ID: #sigma_{i#etai#eta}", 500, 0., 0.050);
	SelectedPhotons_id_sieip_1_ = new TH1F("SelectedPhotons_id_sieip_1_", "photon ID: #sigma_{i#etai#varphi}", 400, 0, 0.04);
	SelectedPhotons_id_etawidth_1_ = new TH1F("SelectedPhotons_id_etawidth_1_", "photon ID: #eta width", 400, 0, 0.04);
	SelectedPhotons_id_phiwidth_1_ = new TH1F("SelectedPhotons_id_phiwidth_1_", "photon ID: #varphi width", 200, 0, 0.2);
	SelectedPhotons_id_r9_1_ = new TH1F("SelectedPhotons_id_r9_1_", "photon ID: r9", 200, 0, 2);
	SelectedPhotons_id_lambdaRatio_1_ = new TH1F("SelectedPhotons_id_lambdaRatio_1_", "photon ID: #lambda Ratio", 200, 0, 2);
	SelectedPhotons_id_s4Ratio_1_ = new TH1F("SelectedPhotons_id_s4Ratio_1_","photon ID: s4 Ratio", 200, 0, 2);
	SelectedPhotons_id_e25_1_ = new TH1F("SelectedPhotons_id_e25_1_", "photon ID: #rho25", 400, 0, 4000);
	SelectedPhotons_id_sceta_1_ = new TH1F("SelectedPhotons_id_sceta_1_", "photon ID: SC #eta", 3000, -3, 3);
	SelectedPhotons_id_ESEffSigmaRR_1_ = new TH1F("SelectedPhotons_id_ESEffSigmaRR_1_", "photon ID: ESEffSigmaRR", 200, 0, 2);
	SelectedPhotons_id_hadronicOverEm_1_ = new TH1F("SelectedPhotons_id_hadronicOverEm_1_", "photon ID: hadronicOverEm", 4000, 0, 0.4);
	SelectedPhotons_id_hadronicOverEm2012_1_ = new TH1F("SelectedPhotons_id_hadronicOverEm2012_1_", "photon ID: hadronicOverEm2012", 4000, 0, 0.4);
	
	//plotsCompare_47	
	SelectedPhotons_hcalTowerSumEtConeDR04_1_ = new TH1F("SelectedPhotons_hcalTowerSumEtConeDR04_1_","photon hcalTowerSumEtConeDR04", 1000, 0, 1000);
	SelectedPhotons_ecalRecHitSumEtConeDR04_1_ = new TH1F("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "photon ecalRecHitSumEtConeDR04", 1000, 0, 1000);
	SelectedPhotons_nTrkSolidConeDR04_1_ = new TH1F("SelectedPhotons_nTrkSolidConeDR04_1_", "photon nTrkSolidConeDR04", 2000, 0, 1000);
	SelectedPhotons_trkSumPtSolidConeDR04_1_ = new TH1F("SelectedPhotons_trkSumPtSolidConeDR04_1_","photon trkSumPtSolidConeDR04", 1000, 0, 1000);
	SelectedPhotons_nTrkHollowConeDR04_1_ = new TH1F("SelectedPhotons_nTrkHollowConeDR04_1_", "photon nTrkHollowConeDR04", 200, 0, 100) ;
	SelectedPhotons_trkSumPtHollowConeDR04_1_ = new TH1F("SelectedPhotons_trkSumPtHollowConeDR04_1_", "photon trkSumPtHollowConeDR04", 1000, 0, 1000);
	
	//plotsCompare_48	
	SelectedPhotons_IsoFPRCharged_1_ = new TH1F("SelectedPhotons_IsoFPRCharged_1_", "photon IsoFPRCharged", 2000, 0, 200); 
	SelectedPhotons_IsoFPRNeutral_1_ = new TH1F("SelectedPhotons_IsoFPRNeutral_1_", "photon IsoFPRNeutral", 2000, 0, 200);
	SelectedPhotons_IsoFPRPhoton_1_ = new TH1F("SelectedPhotons_IsoFPRPhoton_1_", "photon IsoFPRPhoton", 2000, 0, 200);
	SelectedPhotons_IsoFPR_1_ = new TH1F("SelectedPhotons_IsoFPR_1_", "photon IsoFPR", 2000, 0, 200);

	SelectedPhotons_IsoFPRRandomConeCharged_1_ = new TH1F("SelectedPhotons_IsoFPRRandomConeCharged_1_", "photon IsoFPRRandomConeCharged", 2000, 0, 200); 
	SelectedPhotons_IsoFPRRandomConeNeutral_1_ = new TH1F("SelectedPhotons_IsoFPRRandomConeNeutral_1_", "photon IsoFPRRandomConeNeutral", 2000, 0, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_1_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_1_", "photon IsoFPRRandomConePhoton", 2000, 0, 200);

	SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_", "photon IsoFPRPhoton #rho corrected for Fit", 4000, -200, 200);
	SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_", "photon IsoFPRPhoton Random Cone #rho corrected for Fit", 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_ = new TH2F("TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_",  "photon IsoFPRPhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 4000, -200, 200);
	TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_ = new TH2F("TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_",  "photon IsoFPRRAndomConePhoton #rho corrected for Fit vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_49
	SelectedJetsALL_N_ = new TH1F("SelectedJetsALL_N_","Selected Jets vs. ALL Photons N", 10, 0, 10);
	SelectedJets_N_ = new TH1F("SelectedJets_N_","Selected Jets N", 10, 0, 10);

	//plotsCompare_50
	SelectedJets_Pt_1_ = new TH1F("SelectedJets_Pt_1_","Jet 1 p_{T} ", 800, 0., 4000.);
	SelectedJets_E_1_ = new TH1F("SelectedJets_E_1_", "Jet 1 E", 800, 0., 4000.);
	SelectedJets_Eta_1_ = new TH1F("SelectedJets_Eta_1_","Jet 1 #eta ", 3000, -3, 3);
	SelectedJets_Phi_1_ = new TH1F("SelectedJets_Phi_1_","Jet 1 #varphi ", 1000, -3.1416, 3.1416);

	//plotsCompare_51
	SelectedJets_HT_ = new TH1F("SelectedJets_HT_","Selected Jets H_{T}", 400, 0, 4000);

	//plotsCompare_52
	DeltaR_photon1_jet1_N0_ = new TH1F("DeltaR_photon1_jet1_N0_","#DeltaR #gamma1-jet1 - N^{jets} #geq 1", 600, 0, 6);
	DeltaEta_photon1_jet1_N0_ = new TH1F("DeltaEta_photon1_jet1_N0_","#Delta#eta #gamma1-jet1 - N^{jets} #geq 1", 500, 0, 5);
	DeltaPhi_photon1_jet1_N0_ = new TH1F("DeltaPhi_photon1_jet1_N0_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 1", 500, 0, 3.1416);

	//plotsCompare_53
	thrust_N0_ = new TH1F("thrust_N0_","#tau_{T} - N^{jets} #geq 1", 100, 0, 0.5);
	broad_N0_ = new TH1F("broad_N0_","broad - N^{jets} #geq 1", 100, 0, 1);
	S3_N0_ = new TH1F("S3_N0_","S3 - N^{jets} #geq 1", 300, -2, 4);
	S4_N0_ = new TH1F("S4_N0_","S4 - N^{jets} #geq 1", 400, -0.2, 0.2);

	ln_thrust_N0_ = new TH1F("ln_thrust_N0_","ln #tau_{T} - N^{jets} #geq 1", 300, -30, 0);
	ln_broad_N0_ = new TH1F("ln_broad_N0_","ln broad - N^{jets} #geq 1", 300, -5, 1);
	ln_S3_N0_ = new TH1F("ln_S3_N0_","ln S3 - N^{jets} #geq 1", 400, -5, 3);
	ln_S4_N0_ = new TH1F("ln_S4_N0_","ln S4 - N^{jets} #geq 1", 200, -1000, 1000);

	//plotsCompare_54
	SelectedPhotons_Pt_excl1_1_ = new TH1F("SelectedPhotons_Pt_excl1_1_","Photon p_{T}, 1 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_E_excl1_1_ = new TH1F("SelectedPhotons_E_excl1_1_","Photon E, 1 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_Eta_excl1_1_ = new TH1F("SelectedPhotons_Eta_excl1_1_","Photon #eta, 1 jet exclusive", 3000, -3, 3);
	SelectedPhotons_Phi_excl1_1_ = new TH1F("SelectedPhotons_Phi_excl1_1_","Photon #varphi, 1 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_55
	SelectedJets_Pt_excl1_1_ = new TH1F("SelectedJets_Pt_excl1_1_","Jet 1 p_{T}, 1 jet exclusive", 800, 0., 4000.);
	SelectedJets_E_excl1_1_ = new TH1F("SelectedJets_E_excl1_1_", "Jet 1 E, 1 jet exclusive", 800, 0., 4000.);
	SelectedJets_Eta_excl1_1_ = new TH1F("SelectedJets_Eta_excl1_1_","Jet 1 #eta, 1 jet exclusive", 3000, -3, 3);
	SelectedJets_Phi_excl1_1_ = new TH1F("SelectedJets_Phi_excl1_1_","Jet 1 #varphi, 1 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_56
	SelectedPhotons_Pt_excl2_1_ = new TH1F("SelectedPhotons_Pt_excl2_1_","Photon p_{T}, 2 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_E_excl2_1_ = new TH1F("SelectedPhotons_E_excl2_1_","Photon E, 2 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_Eta_excl2_1_ = new TH1F("SelectedPhotons_Eta_excl2_1_","Photon #eta, 2 jet exclusive", 3000, -3, 3);
	SelectedPhotons_Phi_excl2_1_ = new TH1F("SelectedPhotons_Phi_excl2_1_","Photon #varphi, 2 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_57
	SelectedJets_Pt_excl2_1_ = new TH1F("SelectedJets_Pt_excl2_1_","Jet 1 p_{T}, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_E_excl2_1_ = new TH1F("SelectedJets_E_excl2_1_", "Jet 1 E, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_Eta_excl2_1_ = new TH1F("SelectedJets_Eta_excl2_1_","Jet 1 #eta, 2 jet exclusive", 3000, -3, 3);
	SelectedJets_Phi_excl2_1_ = new TH1F("SelectedJets_Phi_excl2_1_","Jet 1 #varphi, 2 jet exclusive", 1000, -3.1416, 3.1416);

	SelectedJets_HT_excl1_ = new TH1F("SelectedJets_HT_excl1_","Selected Jets H_{T}, 1 jet exclusive", 400, 0, 4000);

	//plotsCompare_58
	SelectedJets_Pt_excl2_2_ = new TH1F("SelectedJets_Pt_excl2_2_","Jet 2 p_{T}, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_E_excl2_2_ = new TH1F("SelectedJets_E_excl2_2_", "Jet 2 E, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_Eta_excl2_2_ = new TH1F("SelectedJets_Eta_excl2_2_","Jet 2 #eta, 2 jet exclusive", 3000, -3, 3);
	SelectedJets_Phi_excl2_2_ = new TH1F("SelectedJets_Phi_excl2_2_","Jet 2 #varphi, 2 jet exclusive", 1000, -3.1416, 3.1416);

	SelectedJets_HT_excl2_ = new TH1F("SelectedJets_HT_excl2_","Selected Jets H_{T}, 2 jet exclusive", 400, 0, 4000);

	//plotsCompare_59
	SelectedJets_Pt_2_ = new TH1F("SelectedJets_Pt_2_","Jet 2 p_{T} ", 800, 0., 4000.);
	SelectedJets_E_2_ = new TH1F("SelectedJets_E_2_", "Jet 2 E", 800, 0., 4000.);
	SelectedJets_Eta_2_ = new TH1F("SelectedJets_Eta_2_","Jet 2 #eta ", 3000, -3, 3);
	SelectedJets_Phi_2_ = new TH1F("SelectedJets_Phi_2_","Jet 2 #varphi ", 1000, -3.1416, 3.1416);

	//plotsCompare_60
	DeltaPhi_photon1_jet1_N1_ = new TH1F("DeltaPhi_photon1_jet1_N1_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 2", 500, 0, 3.1416);
	DeltaR_photon1_jet2_N1_ = new TH1F("DeltaR_photon1_jet2_N1_","#DeltaR #gamma1-jet2 - N^{jets} #geq 2", 600, 0, 6);
	DeltaR_jet1_jet2_N1_ = new TH1F("DeltaR_jet1_jet2_N1_","#DeltaR jet1-jet2 - N^{jets} #geq 2", 600, 0, 6);
	DeltaEta_jet1_jet2_N1_ = new TH1F("DeltaEta_jet1_jet2_N1_","#Delta#eta jet1-jet2 - N^{jets} #geq 2", 500, 0, 5);
	DeltaPhi_jet1_jet2_N1_ = new TH1F("DeltaPhi_jet1_jet2_N1_","#Delta#varphi jet1-jet2 - N^{jets} #geq 2", 500, 0, 3.1416);

	//plotsCompare_61
	SelectedJets_Pt_3_ = new TH1F("SelectedJets_Pt_3_","Jet 3 p_{T} ", 800, 0., 4000.);
	SelectedJets_E_3_ = new TH1F("SelectedJets_E_3_", "Jet 3 E", 800, 0., 4000.);
	SelectedJets_Eta_3_ = new TH1F("SelectedJets_Eta_3_","Jet 3 #eta ", 3000, -3, 3);
	SelectedJets_Phi_3_ = new TH1F("SelectedJets_Phi_3_","Jet 3 #varphi ", 1000, -3.1416, 3.1416);

	//plotsCompare_62
	DeltaPhi_photon1_jet1_N2_ = new TH1F("DeltaPhi_photon1_jet1_N2_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_photon1_jet2_N2_ = new TH1F("DeltaPhi_photon1_jet2_N2_","#Delta#varphi #gamma1-jet2 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_photon1_jet3_N2_ = new TH1F("DeltaPhi_photon1_jet3_N2_","#Delta#varphi #gamma1-jet3 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaR_photon1_jet3_N2_ = new TH1F("DeltaR_photon1_jet3_N2_","#DeltaR #gamma1-jet3 - N^{jets} #geq 3", 600, 0, 6);
	DeltaPhi_jet1_jet2_N2_ = new TH1F("DeltaPhi_jet1_jet2_N2_","#Delta#varphi jet1-jet2 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_jet1_jet3_N2_ = new TH1F("DeltaPhi_jet1_jet3_N2_","#Delta#varphi jet1-jet3 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_jet2_jet3_N2_ = new TH1F("DeltaPhi_jet2_jet3_N2_","#Delta#varphi jet2-jet3 - N^{jets} #geq 3", 500, 0, 3.1416);

	//plotsCompare_PrePostCuts_01
	gamma_Pt_1_precut1_ = new TH1F("gamma_Pt_1_precut1_","Photon p_{T} pre cut 1", 800, 0., 4000.);

	gamma_Pt_1_postcut1_ = new TH1F("gamma_Pt_1_postcut1_","Photon p_{T} post cut 1", 800, 0., 4000.);
	if(isMC){
		photonIsoSumPtDR03GEN_precut2_ = new TH1F("photonIsoSumPtDR03GEN_precut2_","photonIsoSumPtDR03GEN pre cut 2", 1300, -1100, 200);
	}

	gamma_Pt_1_postcut2_ = new TH1F("gamma_Pt_1_postcut2_","Photon p_{T} post cut 2", 800, 0., 4000.);

	gamma_Pt_1_preTriMatch_ = new TH1F("gamma_Pt_1_preTriMatch_","Photon p_{T} pre Trigger Matching cut", 800, 0., 4000.);

	//plotsCompare_PrePostCuts_02
	gamma_Pt_1_prePassConversionVeto_ = new TH1F("gamma_Pt_1_prePassConversionVeto_","Photon p_{T} pre PassConversionVeto cut", 800, 0., 4000.);
	gamma_PassConversionVeto_1_prePassConversionVeto_ = new TH1F("gamma_PassConversionVeto_1_prePassConversionVeto_","photonPassConversionVeto pre PassConversionVeto cut", 10, -2, 2);

	gamma_Pt_1_prehadronicOverEm2012_ = new TH1F("gamma_Pt_1_prehadronicOverEm2012_","Photon p_{T} pre hadronicOverEm2012 cut", 800, 0., 4000.);
	gamma_hadronicOverEm2012_1_prehadronicOverEm2012_ = new TH1F("gamma_hadronicOverEm2012_1_prehadronicOverEm2012_", "photon ID: hadronicOverEm2012 pre hadronicOverEm2012 cut", 4000, 0, 0.4);

	gamma_Pt_1_presigmaietaieta_ = new TH1F("gamma_Pt_1_presigmaietaieta_","Photon p_{T} pre sigmaietaieta cut", 800, 0., 4000.);
	gamma_sigmaietaieta_1_presigmaietaieta_ = new TH1F("gamma_sigmaietaieta_1_presigmaietaieta_", "photon ID: #sigma_{i#etai#eta} pre #sigma_{i#etai#eta} cut", 500, 0., 0.050);

	gamma_Pt_1_preiso_CH_ = new TH1F("gamma_Pt_1_preiso_CH_","Photon p_{T} pre iso_CH cut", 800, 0., 4000.);
	gamma_iso_CH_1_preiso_CH_ = new TH1F("gamma_iso_CH_1_preiso_CH_", "photon PfIsoChargedHad #rho corrected pre iso_CH cut", 4000, 0, 100);

	gamma_Pt_1_preiso_NH_ = new TH1F("gamma_Pt_1_preiso_NH_","Photon p_{T} pre iso_CH cut", 800, 0., 4000.);
	gamma_iso_NH_1_preiso_NH_ = new TH1F("gamma_iso_NH_1_preiso_NH_", "photon PfIsoNeutralHad #rho corrected pre iso_NH cut", 2000, 0, 200);

	gamma_Pt_1_preiso_Ph_ = new TH1F("gamma_Pt_1_preiso_Ph_","Photon p_{T} pre iso_NH cut", 800, 0., 4000.);
	gamma_iso_Ph_1_preiso_Ph_ = new TH1F("gamma_iso_Ph_1_preiso_Ph_", "photon PfIso #rho corrected pre iso_Ph cut", 2000, 0, 200);

	//plotsCompare_PrePostCuts_03
	gamma_Pt_1_preAcc_ = new TH1F("gamma_Pt_1_preAcc_","Photon p_{T} pre Acc cut", 800, 0., 4000.);
	gamma_Eta_1_preAcc_ = new TH1F("gamma_Eta_1_preAcc_","Photon #eta pre Acc cut", 3000, -3, 3);

	gamma_Pt_1_postcut3_ = new TH1F("gamma_Pt_1_postcut3_","Photon p_{T} post cut 3", 800, 0., 4000.);
	jets_deltaR_1_predeltaR_ = new TH1F("jets_deltaR_1_predeltaR_","#DeltaR #gamma1-jet1 - N^{jets} #geq 1 pre #DeltaR cut", 600, 0, 6);
	jets_Pt_1_preAcc_ = new TH1F("jets_Pt_1_preAcc","Jet 1 p_{T} pre Acc cut", 800, 0., 4000.);
	jets_Eta_1_preAcc_ = new TH1F("jets_Eta_1_preAcc","Jet 1 #eta pre Acc cut", 3000, -3, 3);

	gamma_Pt_1_postcut4_ = new TH1F("gamma_Pt_1_postcut4_","Photon p_{T} post cut 4", 800, 0., 4000.);
	jets_HT_preHT_ = new TH1F("jets_HT_preHT_","Selected Jets H_{T} pre H_{T} cut", 400, 0, 4000);

	if(Sig) { 
	
		//plotsCompare_unf_01
		unf_photonPtGEN_N0_ = new TH1F("unf_photonPtGEN_N0_","Photon GEN p_{T} - N^{jets} #geq 1", 800, 0., 4000.);
		unf_SelectedJetsGEN_N_N0_ = new TH1F("unf_SelectedJetsGEN_N_N0_","Selected Jets GEN N - N^{jets} #geq 1", 10, 0, 10);
		unf_SelectedJetsGEN_HT_N0_ = new TH1F("unf_SelectedJetsGEN_HT_N0_","Selected Jets H_{T} GEN - N^{jets} #geq 1", 400, 0, 4000);
		unf_SelectedPhotons_Pt_N0_1_ = new TH1F("unf_SelectedPhotons_Pt_N0_1_","Photon p_{T} - N^{jets} #geq 1", 800, 0., 4000.);
		unf_SelectedJets_N_N0_ = new TH1F("unf_SelectedJets_N_N0_","Selected Jets N - N^{jets} #geq 1", 10, 0, 10);
		unf_SelectedJets_HT_N0_ = new TH1F("unf_SelectedJets_HT_N0_","Selected Jets H_{T} - N^{jets} #geq 1", 400, 0, 4000);
		TH2F_unf_GENREC_Photons_Pt_N0_ = new TH2F ("TH2F_unf_GENREC_Photons_Pt_N0_", "Photon p_{T} - N^{jets} #geq 1: REC vs GEN", 800, 0., 4000., 800, 0., 4000.);
		TH2F_unf_GENREC_Jets_N_N0_ = new TH2F ("TH2F_unf_GENREC_Jets_N_N0_", "Selected Jets N - N^{jets} #geq 1: REC vs GEN", 10, 0, 10, 10, 0, 10);
		TH2F_unf_GENREC_Jets_HT_N0_ = new TH2F ("TH2F_unf_GENREC_Jets_HT_N0_", "Selected Jets HT - N^{jets} #geq 1: REC vs GEN", 400, 0, 4000, 400, 0, 4000);

		//plotsCompare_unf_02
		unf_photonPtGEN_excl1_ = new TH1F("unf_photonPtGEN_excl1_","Photon GEN p_{T}, 1 jet exclusive", 800, 0., 4000.);
		unf_SelectedJetsGEN_N_excl1_ = new TH1F("unf_SelectedJetsGEN_N_excl1_","Selected Jets GEN N, 1 jet exclusive", 10, 0, 10);
		unf_SelectedJetsGEN_HT_excl1_ = new TH1F("unf_SelectedJetsGEN_HT_excl1_","Selected Jets H_{T} GEN, 1 jet exclusive", 400, 0, 4000);
		unf_SelectedPhotons_Pt_excl1_1_ = new TH1F("unf_SelectedPhotons_Pt_excl1_1_","Photon p_{T}, 1 jet exclusive", 800, 0., 4000.);
		unf_SelectedJets_N_excl1_ = new TH1F("unf_SelectedJets_N_excl1_","Selected Jets N, 1 jet exclusive", 10, 0, 10);
		unf_SelectedJets_HT_excl1_ = new TH1F("unf_SelectedJets_HT_excl1_","Selected Jets H_{T}, 1 jet exclusive", 400, 0, 4000);
		TH2F_unf_GENREC_Photons_Pt_excl1_ = new TH2F ("TH2F_unf_GENREC_Photons_Pt_excl1_", "Photon p_{T} - 1 jet exclusive: REC vs GEN", 800, 0., 4000., 800, 0., 4000.);
		TH2F_unf_GENREC_Jets_N_excl1_ = new TH2F ("TH2F_unf_GENREC_Jets_N_excl1_", "Selected Jets N - 1 jet exclusive: REC vs GEN", 10, 0, 10, 10, 0, 10);
		TH2F_unf_GENREC_Jets_HT_excl1_ = new TH2F ("TH2F_unf_GENREC_Jets_HT_excl1_", "Selected Jets HT - 1 jet exclusive: REC vs GEN", 400, 0, 4000, 400, 0, 4000);

		//plotsCompare_unf_03
		unf_photonPtGEN_excl2_ = new TH1F("unf_photonPtGEN_excl2_","Photon GEN p_{T}, 2 jet exclusive", 800, 0., 4000.);
		unf_SelectedJetsGEN_N_excl2_ = new TH1F("unf_SelectedJetsGEN_N_excl2_","Selected Jets GEN N, 2 jet exclusive", 10, 0, 10);
		unf_SelectedJetsGEN_HT_excl2_ = new TH1F("unf_SelectedJetsGEN_HT_excl2_","Selected Jets H_{T} GEN, 2 jet exclusive", 400, 0, 4000);
		unf_SelectedPhotons_Pt_excl2_1_ = new TH1F("unf_SelectedPhotons_Pt_excl2_1_","Photon p_{T}, 2 jet exclusive", 800, 0., 4000.);
		unf_SelectedJets_N_excl2_ = new TH1F("unf_SelectedJets_N_excl2_","Selected Jets N, 2 jet exclusive", 10, 0, 10);
		unf_SelectedJets_HT_excl2_ = new TH1F("unf_SelectedJets_HT_excl2_","Selected Jets H_{T}, 2 jet exclusive", 400, 0, 4000);
		TH2F_unf_GENREC_Photons_Pt_excl2_ = new TH2F ("TH2F_unf_GENREC_Photons_Pt_excl2_", "Photon p_{T} - 2 jets exclusive: REC vs GEN", 800, 0., 4000., 800, 0., 4000.);
		TH2F_unf_GENREC_Jets_N_excl2_ = new TH2F ("TH2F_unf_GENREC_Jets_N_excl2_", "Selected Jets N - 2 jets exclusive: REC vs GEN", 10, 0, 10, 10, 0, 10);
		TH2F_unf_GENREC_Jets_HT_excl2_ = new TH2F ("TH2F_unf_GENREC_Jets_HT_excl2_", "Selected Jets HT - 2 jets exclusive: REC vs GEN", 400, 0, 4000, 400, 0, 4000);

		//plotsCompare_unf_04
		unf_photonPtGEN_N1_ = new TH1F("unf_photonPtGEN_N1_","Photon GEN p_{T} - N^{jets} #geq 2", 800, 0., 4000.);
		unf_SelectedJetsGEN_N_N1_ = new TH1F("unf_SelectedJetsGEN_N_N1_","Selected Jets GEN N - N^{jets} #geq 2", 10, 0, 10);
		unf_SelectedJetsGEN_HT_N1_ = new TH1F("unf_SelectedJetsGEN_HT_N1_","Selected Jets H_{T} GEN - N^{jets} #geq 2", 400, 0, 4000);
		unf_SelectedPhotons_Pt_N1_1_ = new TH1F("unf_SelectedPhotons_Pt_N1_1_","Photon p_{T} - N^{jets} #geq 2", 800, 0., 4000.);
		unf_SelectedJets_N_N1_ = new TH1F("unf_SelectedJets_N_N1_","Selected Jets N - N^{jets} #geq 2", 10, 0, 10);
		unf_SelectedJets_HT_N1_ = new TH1F("unf_SelectedJets_HT_N1_","Selected Jets H_{T} - N^{jets} #geq 2", 400, 0, 4000);
		TH2F_unf_GENREC_Photons_Pt_N1_ = new TH2F ("TH2F_unf_GENREC_Photons_Pt_N1_", "Photon p_{T} - N^{jets} #geq 2: REC vs GEN", 800, 0., 4000., 800, 0., 4000.);
		TH2F_unf_GENREC_Jets_N_N1_ = new TH2F ("TH2F_unf_GENREC_Jets_N_N1_", "Selected Jets N - N^{jets} #geq 2: REC vs GEN", 10, 0, 10, 10, 0, 10);
		TH2F_unf_GENREC_Jets_HT_N1_ = new TH2F ("TH2F_unf_GENREC_Jets_HT_N1_", "Selected Jets HT - N^{jets} #geq 2: REC vs GEN", 400, 0, 4000, 400, 0, 4000);

		//plotsCompare_unf_05
		unf_photonPtGEN_N2_ = new TH1F("unf_photonPtGEN_N2_","Photon GEN p_{T} - N^{jets} #geq 3", 800, 0., 4000.);
		unf_SelectedJetsGEN_N_N2_ = new TH1F("unf_SelectedJetsGEN_N_N2_","Selected Jets GEN N - N^{jets} #geq 3", 10, 0, 10);
		unf_SelectedJetsGEN_HT_N2_ = new TH1F("unf_SelectedJetsGEN_HT_N2_","Selected Jets H_{T} GEN - N^{jets} #geq 3", 400, 0, 4000);
		unf_SelectedPhotons_Pt_N2_1_ = new TH1F("unf_SelectedPhotons_Pt_N2_1_","Photon p_{T} - N^{jets} #geq 3", 800, 0., 4000.);
		unf_SelectedJets_N_N2_ = new TH1F("unf_SelectedJets_N_N2_","Selected Jets N - N^{jets} #geq 3", 10, 0, 10);
		unf_SelectedJets_HT_N2_ = new TH1F("unf_SelectedJets_HT_N2_","Selected Jets H_{T} - N^{jets} #geq 3", 400, 0, 4000);
		TH2F_unf_GENREC_Photons_Pt_N2_ = new TH2F ("TH2F_unf_GENREC_Photons_Pt_N2_", "Photon p_{T} - N^{jets} #geq 3: REC vs GEN", 800, 0., 4000., 800, 0., 4000.);
		TH2F_unf_GENREC_Jets_N_N2_ = new TH2F ("TH2F_unf_GENREC_Jets_N_N2_", "Selected Jets N - N^{jets} #geq 3: REC vs GEN", 10, 0, 10, 10, 0, 10);
		TH2F_unf_GENREC_Jets_HT_N2_ = new TH2F ("TH2F_unf_GENREC_Jets_HT_N2_", "Selected Jets HT - N^{jets} #geq 3: REC vs GEN", 400, 0, 4000, 400, 0, 4000);
	}

//	ptPhoton_->Sumw2();
//	etaPhoton_->Sumw2();
//	phiPhoton_->Sumw2();

	cout << "...booking histograms finished." << endl;
}


void GJetsAnalyzer::Plot_Histos(){

	// plot few histograms at the end, for check
	cout << "Plots: quick check... " << endl;

	bool plot_gen_01 = false; // GEN photon kinematics
	bool plot_gen_02 = false; // GEN jets variables
	bool plot_gen_03 = false; // GEN H_T
	bool plot_gen_04 = false; // GEN photon kinematics vs. N GEN jets

	bool plot_01 = true; // photon kinematics
	bool plot_02 = false; // photon Isolation
	bool plot_03 = false; // photon Isolation rho corrected
	bool plot_04 = false; // photon Isolation, 100 < p_T gamma < 151.6
	bool plot_05 = false; // photon Isolation rho corrected, 100 < p_T gamma < 151.6
	bool plot_06 = false; // photon Isolation, 151.6 < p_T gamma < 207.1
	bool plot_07 = false; // photon Isolation rho corrected, 151.6 < p_T gamma < 207.1
	bool plot_08 = false; // photon Isolation, 207.1 < p_T gamma < 313.8
	bool plot_09 = false; // photon Isolation rho corrected, 207.1 < p_T gamma < 313.8
	bool plot_10 = false; // photon Isolation, 313.8 < p_T gamma < 649.8
	bool plot_11 = false; // photon Isolation rho corrected, 313.8 < p_T gamma < 649.8
	bool plot_12 = false; // photon Isolation, 649.8 < p_T gamma < 800
	bool plot_13 = false; // photon Isolation rho corrected, 649.8 < p_T gamma < 800
	bool plot_14 = false; // photon Isolation, p_T gamma > 800
	bool plot_15 = false; // photon Isolation rho corrected, p_T gamma > 800
	bool plot_16 = false; // photon Isolation, p_T gamma > 313.8
	bool plot_17 = false; // photon Isolation rho corrected, p_T gamma > 313.8	
	bool plot_18 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_19 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_20 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_21 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_22 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_23 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_24 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_25 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_26 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_27 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_28 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_29 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_30 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_31 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_32 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_33 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_34 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_35 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_36 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_37 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000
	bool plot_38 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_39 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000		
	bool plot_40 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_41 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000		
	bool plot_42 = false; // photon Isolation, 10000 < p_T gamma < 100000
	bool plot_43 = false; // photon Isolation rho corrected, 10000 < p_T gamma < 100000		
	bool plot_44 = false; // photon Isolation cone 03 for Cic
	bool plot_45 = false; // photon Isolation cone 04 for Cic
	bool plot_46 = false; // photon ID
	bool plot_47 = false; // photon E_T-p_T cone 04
	bool plot_48 = false; // photon Isolation FPR
	bool plot_49 = false; // jets counting
	bool plot_50 = false; // Jet 1 kinematics
	bool plot_51 = false; // H_T
	bool plot_52 = false; // Angular variables (>= 1 jet)
	bool plot_53 = false; // Event shape variables
	bool plot_54 = false; // photon kinematics, 1 jet exclusive 
	bool plot_55 = false; // Jet 1 kinematics, 1 jet exclusive
	bool plot_56 = false; // photon kinematics, 2 jet exclusive 
	bool plot_57 = false; // Jet 1 kinematics, 2 jet exclusive
	bool plot_58 = false; // Jet 2 kinematics, 2 jet exclusive
	bool plot_59 = false; // Jet 2 kinematics
	bool plot_60 = false; // Angular variables (>=2 jets)
	bool plot_61 = false; // Jet 3 kinematics
	bool plot_62 = false; // Angular variables (>=3 jets)

	bool plot_PrePost_01 = false; // Pre-Post cuts plots 1
	bool plot_PrePost_02 = false; // Pre-Post cuts plots 2
	bool plot_PrePost_03 = false; // Pre-Post cuts plots 3

	bool plot_unf_01 = false; // Unfolding (>= 1 jet)
	bool plot_unf_02 = false; // Unfolding (1 jet exclusive)
	bool plot_unf_03 = false; // Unfolding (2 jet exclusive)
	bool plot_unf_04 = false; // Unfolding (>= 2 jet)
	bool plot_unf_05 = false; // Unfolding (>= 3 jet)

				
	gStyle->SetOptStat(1111111);

	if(isMC){
		if(plot_gen_01){
			TCanvas *c_gen01 = new TCanvas("c_gen01", "GEN photon kinematics", 10, 10, 700, 700);
			gPad->SetLogy();
			c_gen01->Divide(3,2);
			c_gen01->cd(1);
			nPhotonsGEN_N0_->Draw();
			c_gen01->cd(2);
			photonPtGEN_N0_->Draw();
			c_gen01->cd(3);
			photonEGEN_N0_->Draw();
			c_gen01->cd(4);
			photonEtaGEN_N0_->Draw();
			c_gen01->cd(5);
			photonPhiGEN_N0_->Draw();
			c_gen01->cd(6);
		}

		if(plot_gen_02){
			TCanvas *c_gen02 = new TCanvas("c_gen02", "GEN jets variables", 10, 10, 700, 700);
			gPad->SetLogy();
			c_gen02->Divide(3,2);
			c_gen02->cd(1);
			SelectedJetsGEN_N_N0_->Draw();
			c_gen02->cd(2);
			SelectedJets_PtGEN_N0_1_->Draw();
			c_gen02->cd(3);
			SelectedJets_EGEN_N0_1_->Draw();
			c_gen02->cd(4);
			SelectedJets_EtaGEN_N0_1_->Draw();
			c_gen02->cd(5);
			SelectedJets_PhiGEN_N0_1_->Draw();
		}

		if(plot_gen_03){
			TCanvas *c_gen03 = new TCanvas("c_gen03", "GEN H_T", 10, 10, 700, 700);
			gPad->SetLogy();
			c_gen03->Divide(2,2);
			c_gen03->cd(1);
			SelectedJetsGEN_HT_N0_->Draw();
			c_gen03->cd(2);
			pre_photonIsoSumPtDR03GEN_->Draw();
			c_gen03->cd(3);
			photonIsoSumPtDR03GEN_->Draw();
			c_gen03->cd(4);
			HTParSum_->Draw();
		}

		if(plot_gen_04){
			TCanvas *c_gen04 = new TCanvas("c_gen04", "GEN photon kinematics vs. N GEN jets", 10, 10, 700, 700);
			gPad->SetLogy();
			c_gen04->Divide(3,2);
			c_gen04->cd(1);
			photonPtGEN_excl1_->Draw();
			c_gen04->cd(2);
			photonPtGEN_excl2_->Draw();
			c_gen04->cd(3);
			photonPtGEN_N1_->Draw();
			c_gen04->cd(4);
			photonPtGEN_N2_->Draw();
			c_gen04->cd(4);
			photonIsoSumPtDR03GEN_precut2_->Draw();			
		}
	}

	if(plot_01){
		TCanvas *c01 = new TCanvas("c01", "photon kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c01->Divide(5,3);
		c01->cd(1);
		IDIsoPhotons_N_->Draw();
		c01->cd(2);
		SelectedPhotons_N_->Draw();
		c01->cd(3);
		Nvtx_->Draw();
		c01->cd(4);
		SelectedPhotons_Pt_1_->Draw();
		c01->cd(5);
		SelectedPhotons_Pt_LogBin_1_->Draw();
		c01->cd(6);		
		SelectedPhotons_E_1_->Draw();
		c01->cd(7);
		SelectedPhotons_Eta_1_->Draw();
		c01->cd(8);
		SelectedPhotons_Phi_1_->Draw();
		c01->cd(9);
		SelectedPhotons_Bit_1_->Draw();
		c01->cd(10);
		SelectedPhotons_TriMatchF4Path_AND_pTrange_1_->Draw();
		c01->cd(11);
		SelectedPhotons_Tri_PF_1_->Draw();
		c01->cd(12);
		SelectedPhotons_TeP_SF_1_->Draw();	
		c01->cd(13);
		SelectedPhotons_BackDataDriven_F_1_->Draw();	
	}

	if(plot_02){ 
		TCanvas *c02 = new TCanvas("c02", "photon Isolation", 10, 10, 700, 700);
		gPad->SetLogy();
		c02->Divide(3,2);
		c02->cd(1);
		SelectedPhotons_PassConversionVeto_1_->Draw();
		c02->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_->Draw();
		c02->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_->Draw();
		c02->cd(4);
		SelectedPhotons_PfIsoPhoton_1_->Draw();
		c02->cd(5);
		SelectedPhotons_PfIso_1_->Draw();
	}

	if(plot_03){ 
		TCanvas *c03 = new TCanvas("c03", "photon Isolation, rho corrected", 10, 10, 700, 700);
		gPad->SetLogy();
		c03->Divide(4,3);
		c03->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_->Draw();
		c03->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_->Draw();
		c03->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_->Draw();
		c03->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_->Draw();
		c03->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_->Draw();
		c03->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_->Draw();
		c03->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_->Draw();
		c03->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_->Draw();
		c03->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_->Draw();		
		c03->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_->Draw();
		c03->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_->Draw();
	}

	if(plot_04){ 
		TCanvas *c04 = new TCanvas("c04", "photon Isolation, 100 < pT gamma < 151.6", 10, 10, 700, 700);
		gPad->SetLogy();
		c04->Divide(3,2);
		c04->cd(1);
		SelectedPhotons_id_sieie_1_bin01_->Draw();
		c04->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin01_->Draw();
		c04->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin01_->Draw();
		c04->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin01_->Draw();
		c04->cd(5);
		SelectedPhotons_PfIso_1_bin01_->Draw();
	}

	if(plot_05){ 
		TCanvas *c05 = new TCanvas("c05", "photon Isolation rho corrected, 100 < pT gamma < 151.6", 10, 10, 700, 700);
		gPad->SetLogy();
		c05->Divide(5,3);
		c05->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_->Draw();
		c05->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_->Draw();
		c05->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_->Draw();
		c05->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin01_->Draw();
		c05->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_->Draw();		
		c05->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_->Draw();
		c05->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_->Draw();
		c05->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_->Draw();
		c05->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin01_->Draw();
		c05->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_->Draw();
		c05->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_->Draw();		
		c05->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin01_->Draw();
		c05->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin01_->Draw();		
		c05->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin01_->Draw();
		c05->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin01_->Draw();
	}

	if(plot_06){ 
		TCanvas *c06 = new TCanvas("c06", "photon Isolation, 151.6 < pT gamma < 207.1", 10, 10, 700, 700);
		gPad->SetLogy();
		c06->Divide(3,2);
		c06->cd(1);
		SelectedPhotons_id_sieie_1_bin02_->Draw();		
		c06->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin02_->Draw();
		c06->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin02_->Draw();
		c06->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin02_->Draw();
		c06->cd(5);
		SelectedPhotons_PfIso_1_bin02_->Draw();
	}

	if(plot_07){ 
		TCanvas *c07 = new TCanvas("c07", "photon Isolation rho corrected, 151.6 < pT gamma < 207.1", 10, 10, 700, 700);
		gPad->SetLogy();
		c07->Divide(5,3);
		c07->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_->Draw();
		c07->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_->Draw();
		c07->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_->Draw();
		c07->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin02_->Draw();
		c07->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_->Draw();		
		c07->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_->Draw();
		c07->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_->Draw();
		c07->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_->Draw();
		c07->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin02_->Draw();
		c07->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_->Draw();
		c07->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_->Draw();		
		c07->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin02_->Draw();
		c07->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin02_->Draw();		
		c07->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin02_->Draw();
		c07->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin02_->Draw();
	}

	if(plot_08){ 
		TCanvas *c08 = new TCanvas("c08", "photon Isolation, 207.1 < pT gamma < 313.8", 10, 10, 700, 700);
		gPad->SetLogy();
		c08->Divide(3,2);
		c08->cd(1);
		SelectedPhotons_id_sieie_1_bin03_->Draw();		
		c08->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin03_->Draw();
		c08->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin03_->Draw();
		c08->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin03_->Draw();
		c08->cd(5);
		SelectedPhotons_PfIso_1_bin03_->Draw();
	}

	if(plot_09){ 
		TCanvas *c09 = new TCanvas("c09", "photon Isolation rho corrected, 207.1 < pT gamma < 313.8", 10, 10, 700, 700);
		gPad->SetLogy();
		c09->Divide(5,3);
		c09->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_->Draw();
		c09->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_->Draw();
		c09->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_->Draw();
		c09->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin03_->Draw();
		c09->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_->Draw();		
		c09->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_->Draw();
		c09->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_->Draw();
		c09->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_->Draw();
		c09->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin03_->Draw();		
		c09->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_->Draw();
		c09->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_->Draw();		
		c09->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin03_->Draw();
		c09->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin03_->Draw();		
		c09->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin03_->Draw();
		c09->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin03_->Draw();
	}

	if(plot_10){ 
		TCanvas *c10 = new TCanvas("c10", "photon Isolation, 313.8 < pT gamma < 649.8", 10, 10, 700, 700);
		gPad->SetLogy();
		c10->Divide(3,2);
		c10->cd(1);
		SelectedPhotons_id_sieie_1_bin04_->Draw();		
		c10->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin04_->Draw();
		c10->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin04_->Draw();
		c10->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin04_->Draw();
		c10->cd(5);
		SelectedPhotons_PfIso_1_bin04_->Draw();
	}

	if(plot_11){ 
		TCanvas *c11 = new TCanvas("c11", "photon Isolation rho corrected, 313.8 < pT gamma < 649.8", 10, 10, 700, 700);
		gPad->SetLogy();
		c11->Divide(5,3);
		c11->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_->Draw();
		c11->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_->Draw();
		c11->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_->Draw();
		c11->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin04_->Draw();
		c11->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_->Draw();		
		c11->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_->Draw();
		c11->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_->Draw();
		c11->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_->Draw();
		c11->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin04_->Draw();		
		c11->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_->Draw();
		c11->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_->Draw();		
		c11->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin04_->Draw();
		c11->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin04_->Draw();		
		c11->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin04_->Draw();
		c11->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin04_->Draw();	
	}

	if(plot_12){ 
		TCanvas *c12 = new TCanvas("c12", "photon Isolation, 649.8 < pT gamma < 800", 10, 10, 700, 700);
		gPad->SetLogy();
		c12->Divide(3,2);
		c12->cd(1);
		SelectedPhotons_id_sieie_1_bin05_->Draw();		
		c12->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin05_->Draw();
		c12->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin05_->Draw();
		c12->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin05_->Draw();
		c12->cd(5);
		SelectedPhotons_PfIso_1_bin05_->Draw();
	}

	if(plot_13){ 
		TCanvas *c13 = new TCanvas("c13", "photon Isolation rho corrected, 649.8 < pT gamma < 800", 10, 10, 700, 700);
		gPad->SetLogy();
		c13->Divide(5,3);
		c13->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_->Draw();
		c13->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_->Draw();
		c13->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_->Draw();
		c13->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin05_->Draw();
		c13->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_->Draw();		
		c13->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_->Draw();
		c13->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_->Draw();
		c13->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_->Draw();
		c13->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin05_->Draw();		
		c13->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_->Draw();
		c13->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_->Draw();		
		c13->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin05_->Draw();
		c13->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin05_->Draw();		
		c13->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin05_->Draw();
		c13->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin05_->Draw();	
	}

	if(plot_14){ 
		TCanvas *c14 = new TCanvas("c14", "photon Isolation, pT gamma > 800", 10, 10, 700, 700);
		gPad->SetLogy();
		c14->Divide(3,2);
		c14->cd(1);
		SelectedPhotons_id_sieie_1_bin06_->Draw();		
		c14->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin06_->Draw();
		c14->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin06_->Draw();
		c14->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin06_->Draw();
		c14->cd(5);
		SelectedPhotons_PfIso_1_bin06_->Draw();
	}

	if(plot_15){ 
		TCanvas *c15 = new TCanvas("c15", "photon Isolation rho corrected, pT gamma > 800", 10, 10, 700, 700);
		gPad->SetLogy();
		c15->Divide(5,3);
		c15->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_->Draw();
		c15->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_->Draw();
		c15->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_->Draw();
		c15->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin06_->Draw();
		c15->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_->Draw();		
		c15->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_->Draw();
		c15->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_->Draw();
		c15->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_->Draw();
		c15->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin06_->Draw();		
		c15->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_->Draw();
		c15->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_->Draw();		
		c15->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin06_->Draw();
		c15->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin06_->Draw();		
		c15->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin06_->Draw();
		c15->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin06_->Draw();	
	}

	if(plot_16){ 
		TCanvas *c16 = new TCanvas("c16", "photon Isolation, pT gamma > 313.8", 10, 10, 700, 700);
		gPad->SetLogy();
		c16->Divide(3,2);
		c16->cd(1);
		SelectedPhotons_id_sieie_1_bin07_->Draw();		
		c16->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin07_->Draw();
		c16->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin07_->Draw();
		c16->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin07_->Draw();
		c16->cd(5);
		SelectedPhotons_PfIso_1_bin07_->Draw();
	}

	if(plot_17){ 
		TCanvas *c17 = new TCanvas("c17", "photon Isolation rho corrected, pT gamma > 313.8", 10, 10, 700, 700);
		gPad->SetLogy();
		c17->Divide(5,3);
		c17->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin07_->Draw();
		c17->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin07_->Draw();
		c17->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin07_->Draw();
		c17->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin07_->Draw();
		c17->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin07_->Draw();		
		c17->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin07_->Draw();
		c17->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin07_->Draw();
		c17->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin07_->Draw();
		c17->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin07_->Draw();		
		c17->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin07_->Draw();
		c17->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin07_->Draw();		
		c17->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin07_->Draw();
		c17->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin07_->Draw();		
		c17->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin07_->Draw();
		c17->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin07_->Draw();	
	}

	if(plot_18){ 
		TCanvas *c18 = new TCanvas("c18", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c18->Divide(3,2);
		c18->cd(1);
		SelectedPhotons_id_sieie_1_bin08_->Draw();		
		c18->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin08_->Draw();
		c18->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin08_->Draw();
		c18->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin08_->Draw();
		c18->cd(5);
		SelectedPhotons_PfIso_1_bin08_->Draw();
	}

	if(plot_19){ 
		TCanvas *c19 = new TCanvas("c19", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c19->Divide(5,3);
		c19->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin08_->Draw();
		c19->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin08_->Draw();
		c19->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin08_->Draw();
		c19->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin08_->Draw();
		c19->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin08_->Draw();		
		c19->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin08_->Draw();
		c19->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin08_->Draw();
		c19->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin08_->Draw();
		c19->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin08_->Draw();		
		c19->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin08_->Draw();
		c19->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin08_->Draw();		
		c19->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin08_->Draw();
		c19->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin08_->Draw();		
		c19->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin08_->Draw();
		c19->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin08_->Draw();	
	}

	if(plot_20){ 
		TCanvas *c20 = new TCanvas("c20", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c20->Divide(3,2);
		c20->cd(1);
		SelectedPhotons_id_sieie_1_bin09_->Draw();		
		c20->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin09_->Draw();
		c20->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin09_->Draw();
		c20->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin09_->Draw();
		c20->cd(5);
		SelectedPhotons_PfIso_1_bin09_->Draw();
	}

	if(plot_21){ 
		TCanvas *c21 = new TCanvas("c21", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c21->Divide(5,3);
		c21->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin09_->Draw();
		c21->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin09_->Draw();
		c21->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin09_->Draw();
		c21->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin09_->Draw();
		c21->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin09_->Draw();		
		c21->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin09_->Draw();
		c21->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin09_->Draw();
		c21->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin09_->Draw();
		c21->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin09_->Draw();			
		c21->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin09_->Draw();
		c21->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin09_->Draw();		
		c21->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin09_->Draw();
		c21->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin09_->Draw();		
		c21->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin09_->Draw();
		c21->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin09_->Draw();	
	}

	if(plot_22){ 
		TCanvas *c22 = new TCanvas("c22", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c22->Divide(3,2);
		c22->cd(1);
		SelectedPhotons_id_sieie_1_bin10_->Draw();		
		c22->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin10_->Draw();
		c22->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin10_->Draw();
		c22->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin10_->Draw();
		c22->cd(5);
		SelectedPhotons_PfIso_1_bin10_->Draw();
	}

	if(plot_23){ 
		TCanvas *c23 = new TCanvas("c23", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c23->Divide(5,3);
		c23->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin10_->Draw();
		c23->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin10_->Draw();
		c23->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin10_->Draw();
		c23->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin10_->Draw();
		c23->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin10_->Draw();		
		c23->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin10_->Draw();
		c23->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin10_->Draw();
		c23->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin10_->Draw();
		c23->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin10_->Draw();		
		c23->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin10_->Draw();
		c23->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin10_->Draw();		
		c23->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin10_->Draw();
		c23->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin10_->Draw();		
		c23->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin10_->Draw();
		c23->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin10_->Draw();	
	}

	if(plot_24){ 
		TCanvas *c24 = new TCanvas("c24", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c24->Divide(3,2);
		c24->cd(1);
		SelectedPhotons_id_sieie_1_bin11_->Draw();		
		c24->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin11_->Draw();
		c24->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin11_->Draw();
		c24->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin11_->Draw();
		c24->cd(5);
		SelectedPhotons_PfIso_1_bin11_->Draw();
	}

	if(plot_25){ 
		TCanvas *c25 = new TCanvas("c25", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c25->Divide(5,3);
		c25->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin11_->Draw();
		c25->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin11_->Draw();
		c25->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin11_->Draw();
		c25->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin11_->Draw();
		c25->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin11_->Draw();		
		c25->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin11_->Draw();
		c25->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin11_->Draw();
		c25->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin11_->Draw();
		c25->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin11_->Draw();		
		c25->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin11_->Draw();
		c25->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin11_->Draw();		
		c25->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin11_->Draw();
		c25->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin11_->Draw();		
		c25->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin11_->Draw();
		c25->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin11_->Draw();	
	}

	if(plot_26){ 
		TCanvas *c26 = new TCanvas("c26", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c26->Divide(3,2);
		c26->cd(1);
		SelectedPhotons_id_sieie_1_bin12_->Draw();		
		c26->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin12_->Draw();
		c26->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin12_->Draw();
		c26->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin12_->Draw();
		c26->cd(5);
		SelectedPhotons_PfIso_1_bin12_->Draw();
	}

	if(plot_27){ 
		TCanvas *c27 = new TCanvas("c27", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c27->Divide(5,3);
		c27->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin12_->Draw();
		c27->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin12_->Draw();
		c27->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin12_->Draw();
		c27->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin12_->Draw();
		c27->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin12_->Draw();		
		c27->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin12_->Draw();
		c27->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin12_->Draw();
		c27->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin12_->Draw();
		c27->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin12_->Draw();		
		c27->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin12_->Draw();
		c27->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin12_->Draw();		
		c27->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin12_->Draw();
		c27->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin12_->Draw();		
		c27->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin12_->Draw();
		c27->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin12_->Draw();	
	}

	if(plot_28){ 
		TCanvas *c28 = new TCanvas("c28", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c28->Divide(3,2);
		c28->cd(1);
		SelectedPhotons_id_sieie_1_bin13_->Draw();		
		c28->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin13_->Draw();
		c28->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin13_->Draw();
		c28->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin13_->Draw();
		c28->cd(5);
		SelectedPhotons_PfIso_1_bin13_->Draw();
	}

	if(plot_29){ 
		TCanvas *c29 = new TCanvas("c29", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c29->Divide(5,3);
		c29->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin13_->Draw();
		c29->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin13_->Draw();
		c29->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin13_->Draw();
		c29->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin13_->Draw();
		c29->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin13_->Draw();		
		c29->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin13_->Draw();
		c29->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin13_->Draw();
		c29->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin13_->Draw();
		c29->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin13_->Draw();		
		c29->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin13_->Draw();
		c29->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin13_->Draw();		
		c29->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin13_->Draw();
		c29->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin13_->Draw();		
		c29->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin13_->Draw();
		c29->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin13_->Draw();	
	}

	if(plot_30){ 
		TCanvas *c30 = new TCanvas("c30", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c30->Divide(3,2);
		c30->cd(1);
		SelectedPhotons_id_sieie_1_bin14_->Draw();		
		c30->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin14_->Draw();
		c30->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin14_->Draw();
		c30->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin14_->Draw();
		c30->cd(5);
		SelectedPhotons_PfIso_1_bin14_->Draw();
	}

	if(plot_31){ 
		TCanvas *c31 = new TCanvas("c31", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c31->Divide(5,3);
		c31->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin14_->Draw();
		c31->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin14_->Draw();
		c31->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin14_->Draw();
		c31->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin14_->Draw();
		c31->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin14_->Draw();		
		c31->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin14_->Draw();
		c31->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin14_->Draw();
		c31->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin14_->Draw();
		c31->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin14_->Draw();		
		c31->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin14_->Draw();
		c31->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin14_->Draw();		
		c31->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin14_->Draw();
		c31->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin14_->Draw();		
		c31->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin14_->Draw();
		c31->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin14_->Draw();	
	}

	if(plot_32){ 
		TCanvas *c32 = new TCanvas("c32", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c32->Divide(3,2);
		c32->cd(1);
		SelectedPhotons_id_sieie_1_bin15_->Draw();		
		c32->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin15_->Draw();
		c32->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin15_->Draw();
		c32->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin15_->Draw();
		c32->cd(5);
		SelectedPhotons_PfIso_1_bin15_->Draw();
	}

	if(plot_33){ 
		TCanvas *c33 = new TCanvas("c33", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c33->Divide(5,3);
		c33->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin15_->Draw();
		c33->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin15_->Draw();
		c33->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin15_->Draw();
		c33->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin15_->Draw();
		c33->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin15_->Draw();		
		c33->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin15_->Draw();
		c33->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin15_->Draw();
		c33->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin15_->Draw();
		c33->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin15_->Draw();		
		c33->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin15_->Draw();
		c33->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin15_->Draw();		
		c33->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin15_->Draw();
		c33->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin15_->Draw();		
		c33->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin15_->Draw();
		c33->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin15_->Draw();	
	}

	if(plot_34){ 
		TCanvas *c34 = new TCanvas("c34", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c34->Divide(3,2);
		c34->cd(1);
		SelectedPhotons_id_sieie_1_bin16_->Draw();		
		c34->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin16_->Draw();
		c34->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin16_->Draw();
		c34->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin16_->Draw();
		c34->cd(5);
		SelectedPhotons_PfIso_1_bin16_->Draw();
	}

	if(plot_35){ 
		TCanvas *c35 = new TCanvas("c35", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c35->Divide(5,3);
		c35->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin16_->Draw();
		c35->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin16_->Draw();
		c35->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin16_->Draw();
		c35->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin16_->Draw();
		c35->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin16_->Draw();		
		c35->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin16_->Draw();
		c35->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin16_->Draw();
		c35->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin16_->Draw();
		c35->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin16_->Draw();		
		c35->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin16_->Draw();
		c35->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin16_->Draw();		
		c35->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin16_->Draw();
		c35->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin16_->Draw();		
		c35->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin16_->Draw();
		c35->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin16_->Draw();	
	}

	if(plot_36){ 
		TCanvas *c36 = new TCanvas("c36", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c36->Divide(3,2);
		c36->cd(1);
		SelectedPhotons_id_sieie_1_bin17_->Draw();		
		c36->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin17_->Draw();
		c36->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin17_->Draw();
		c36->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin17_->Draw();
		c36->cd(5);
		SelectedPhotons_PfIso_1_bin17_->Draw();
	}

	if(plot_37){ 
		TCanvas *c37 = new TCanvas("c37", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c37->Divide(5,3);
		c37->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin17_->Draw();
		c37->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin17_->Draw();
		c37->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin17_->Draw();
		c37->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin17_->Draw();
		c37->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin17_->Draw();		
		c37->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin17_->Draw();
		c37->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin17_->Draw();
		c37->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin17_->Draw();
		c37->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin17_->Draw();		
		c37->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin17_->Draw();
		c37->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin17_->Draw();		
		c37->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin17_->Draw();
		c37->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin17_->Draw();		
		c37->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin17_->Draw();
		c37->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin17_->Draw();	
	}

	if(plot_38){ 
		TCanvas *c38 = new TCanvas("c38", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c38->Divide(3,2);
		c38->cd(1);
		SelectedPhotons_id_sieie_1_bin18_->Draw();		
		c38->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin18_->Draw();
		c38->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin18_->Draw();
		c38->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin18_->Draw();
		c38->cd(5);
		SelectedPhotons_PfIso_1_bin18_->Draw();
	}

	if(plot_39){ 
		TCanvas *c39 = new TCanvas("c39", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c39->Divide(5,3);
		c39->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin18_->Draw();
		c39->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin18_->Draw();
		c39->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin18_->Draw();
		c39->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin18_->Draw();
		c39->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin18_->Draw();		
		c39->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin18_->Draw();
		c39->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin18_->Draw();
		c39->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin18_->Draw();
		c39->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin18_->Draw();		
		c39->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin18_->Draw();
		c39->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin18_->Draw();		
		c39->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin18_->Draw();
		c39->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin18_->Draw();		
		c39->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin18_->Draw();
		c39->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin18_->Draw();	
	}

	if(plot_40){ 
		TCanvas *c40 = new TCanvas("c40", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c40->Divide(3,2);
		c40->cd(1);
		SelectedPhotons_id_sieie_1_bin19_->Draw();		
		c40->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin19_->Draw();
		c40->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin19_->Draw();
		c40->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin19_->Draw();
		c40->cd(5);
		SelectedPhotons_PfIso_1_bin19_->Draw();
	}

	if(plot_41){ 
		TCanvas *c41 = new TCanvas("c41", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c41->Divide(5,3);
		c41->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin19_->Draw();
		c41->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin19_->Draw();
		c41->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin19_->Draw();
		c41->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin19_->Draw();
		c41->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin19_->Draw();		
		c41->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin19_->Draw();
		c41->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin19_->Draw();
		c41->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin19_->Draw();
		c41->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin19_->Draw();		
		c41->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin19_->Draw();
		c41->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin19_->Draw();		
		c41->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin19_->Draw();
		c41->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin19_->Draw();		
		c41->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin19_->Draw();
		c41->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin19_->Draw();	
	}

	if(plot_42){ 
		TCanvas *c42 = new TCanvas("c42", "photon Isolation, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c42->Divide(3,2);
		c42->cd(1);
		SelectedPhotons_id_sieie_1_bin20_->Draw();		
		c42->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin20_->Draw();
		c42->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin20_->Draw();
		c42->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin20_->Draw();
		c42->cd(5);
		SelectedPhotons_PfIso_1_bin20_->Draw();
	}

	if(plot_43){ 
		TCanvas *c43 = new TCanvas("c43", "photon Isolation rho corrected, 10000 < pT gamma < 100000", 10, 10, 700, 700);
		gPad->SetLogy();
		c43->Divide(5,3);
		c43->cd(1);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin20_->Draw();
		c43->cd(2);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin20_->Draw();
		c43->cd(3);
		SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin20_->Draw();
		c43->cd(4);
		SelectedPhotons_PfIso_RhoCorr_1_bin20_->Draw();
		c43->cd(5);
		TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin20_->Draw();		
		c43->cd(6);
		SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin20_->Draw();
		c43->cd(7);
		SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin20_->Draw();
		c43->cd(8);
		SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin20_->Draw();
		c43->cd(9);
		TH2F_SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_vs_sieie_1_bin20_->Draw();		
		c43->cd(10);
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin20_->Draw();
		c43->cd(11);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin20_->Draw();		
		c43->cd(12);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_bin20_->Draw();
		c43->cd(13);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_bin20_->Draw();		
		c43->cd(14);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_bin20_->Draw();
		c43->cd(15);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_bin20_->Draw();	
	}

	if(plot_44){
		TCanvas *c44 = new TCanvas("c44", "photon Isolation cone 03 for Cic", 10, 10, 700, 700);
		gPad->SetLogy();
		c44->Divide(2,2);
		c44->cd(1);
		SelectedPhotons_PfIsoPhotons03ForCic_1_->Draw();
		c44->cd(2);
		SelectedPhotons_PfIsoNeutrals03ForCic_1_->Draw();
		c44->cd(3);
		SelectedPhotons_PfIsoCharged03ForCicVtx0_1_->Draw();
		c44->cd(4);
		SelectedPhotons_PfIsoCharged03BadForCic_1_->Draw();
	}

	if(plot_45){
		TCanvas *c45 = new TCanvas("c45", "photon Isolation cone 04 for Cic", 10, 10, 700, 700);
		gPad->SetLogy();
		c45->Divide(2,2);
		c45->cd(1);
		SelectedPhotons_PfIsoPhotons04ForCic_1_->Draw();
		c45->cd(2);
		SelectedPhotons_PfIsoNeutrals04ForCic_1_->Draw();
		c45->cd(3);
		SelectedPhotons_PfIsoCharged04ForCicVtx0_1_->Draw();
		c45->cd(4);
		SelectedPhotons_PfIsoCharged04BadForCic_1_->Draw();
	}

	if(plot_46){
		TCanvas *c46 = new TCanvas("c46", "photon ID", 10, 10, 700, 700);
		gPad->SetLogy();
		c46->Divide(4,3);
		c46->cd(1);
		SelectedPhotons_id_sieie_1_->Draw();
		c46->cd(2);
		SelectedPhotons_id_sieip_1_->Draw();
		c46->cd(3);
		SelectedPhotons_id_etawidth_1_->Draw();
		c46->cd(4);
		SelectedPhotons_id_phiwidth_1_->Draw();
		c46->cd(5);
		SelectedPhotons_id_r9_1_->Draw();
		c46->cd(6);
		SelectedPhotons_id_lambdaRatio_1_->Draw();
		c46->cd(7);
		SelectedPhotons_id_s4Ratio_1_->Draw();
		c46->cd(8);
		SelectedPhotons_id_e25_1_->Draw();
		c46->cd(9);
		SelectedPhotons_id_sceta_1_->Draw();
		c46->cd(10);
		SelectedPhotons_id_ESEffSigmaRR_1_->Draw();
		c46->cd(11);
		SelectedPhotons_id_hadronicOverEm_1_->Draw();
		c46->cd(12);
		SelectedPhotons_id_hadronicOverEm2012_1_->Draw();
	}

	if(plot_47){
		TCanvas *c47 = new TCanvas("c47", "photon E_T-p_T cone 04", 10, 10, 700, 700);
		gPad->SetLogy();
		c47->Divide(3,2);
		c47->cd(1);
		SelectedPhotons_hcalTowerSumEtConeDR04_1_->Draw();
		c47->cd(2);
		SelectedPhotons_ecalRecHitSumEtConeDR04_1_->Draw();
		c47->cd(3);
		SelectedPhotons_nTrkSolidConeDR04_1_->Draw();
		c47->cd(4);
		SelectedPhotons_trkSumPtSolidConeDR04_1_->Draw();
		c47->cd(5);
		SelectedPhotons_nTrkHollowConeDR04_1_->Draw();
		c47->cd(6);
		SelectedPhotons_trkSumPtHollowConeDR04_1_->Draw();
	}

	if(plot_48){
		TCanvas *c48 = new TCanvas("c48", "photon Isolation FPR", 10, 10, 700, 700);
		gPad->SetLogy();
		c48->Divide(4,3);
		c48->cd(1);
		SelectedPhotons_IsoFPRCharged_1_->Draw();
		c48->cd(2);
		SelectedPhotons_IsoFPRNeutral_1_->Draw();
		c48->cd(3);
		SelectedPhotons_IsoFPRPhoton_1_->Draw();
		c48->cd(4);
		SelectedPhotons_IsoFPR_1_->Draw();
		c48->cd(5);
		SelectedPhotons_IsoFPRRandomConeCharged_1_->Draw();
		c48->cd(6);
		SelectedPhotons_IsoFPRRandomConeNeutral_1_->Draw();
		c48->cd(7);
		SelectedPhotons_IsoFPRRandomConePhoton_1_->Draw();
		c48->cd(8);
		SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_1_->Draw();
		c48->cd(9);
		SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_1_->Draw();
		c48->cd(10);
		TH2F_SelectedPhotons_IsoFPRPhoton_RhoCorr_forFit_vs_sieie_1_->Draw();
		c48->cd(11);
		TH2F_SelectedPhotons_IsoFPRRandomConePhoton_RhoCorr_forFit_vs_sieie_1_->Draw();	
	}

	if(plot_49){
		TCanvas *c49 = new TCanvas("c49", "jets counting", 10, 10, 700, 700);
		gPad->SetLogy();
		c49->Divide(2,1);
		c49->cd(1);
		SelectedJetsALL_N_->Draw();
		c49->cd(2);
		SelectedJets_N_->Draw();
	}

	if(plot_50){
		TCanvas *c50 = new TCanvas("c50", "Jet 1 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c50->Divide(2,2);
		c50->cd(1);
		SelectedJets_Pt_1_->Draw();
		c50->cd(2);
		SelectedJets_E_1_->Draw();
		c50->cd(3);
		SelectedJets_Eta_1_->Draw();
		c50->cd(4);
		SelectedJets_Phi_1_->Draw();
	}

	if(plot_51){
		TCanvas *c51 = new TCanvas("c51", "H_T", 10, 10, 700, 700);
		gPad->SetLogy();
		c51->cd();
		SelectedJets_HT_->Draw();
	}

	if(plot_52){
		TCanvas *c52 = new TCanvas("c52", "Angular variables (>= 1 jet)", 10, 10, 700, 700);
		gPad->SetLogy();
		c52->Divide(3,1);
		c52->cd(1);
		DeltaR_photon1_jet1_N0_->Draw();
		c52->cd(2);
		DeltaEta_photon1_jet1_N0_->Draw();
		c52->cd(3);
		DeltaPhi_photon1_jet1_N0_->Draw();
	}

	if(plot_53){
		TCanvas *c53 = new TCanvas("c53", "Event shape variables", 10, 10, 700, 700);
		gPad->SetLogy();
		c53->Divide(4,2);
		c53->cd(1);
		thrust_N0_->Draw();
		c53->cd(2);
		broad_N0_->Draw();
		c53->cd(3);
		S3_N0_->Draw();
		c53->cd(4);
		S4_N0_->Draw();
		c53->cd(5);
		ln_thrust_N0_->Draw();
		c53->cd(6);
		ln_broad_N0_->Draw();
		c53->cd(7);
		ln_S3_N0_->Draw();
		c53->cd(8);
		ln_S4_N0_->Draw();
	}

	if(plot_54){
		TCanvas *c54 = new TCanvas("c54", "photon kinematics, 1 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c54->Divide(2,2);
		c54->cd(1);
		SelectedPhotons_Pt_excl1_1_->Draw();
		c54->cd(2);
		SelectedPhotons_E_excl1_1_->Draw();
		c54->cd(3);
		SelectedPhotons_Eta_excl1_1_->Draw();
		c54->cd(4);
		SelectedPhotons_Phi_excl1_1_->Draw();
	}

	if(plot_55){
		TCanvas *c55 = new TCanvas("c55", "Jet 1 kinematics, 1 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c55->Divide(3,2);
		c55->cd(1);
		SelectedJets_Pt_excl1_1_->Draw();
		c55->cd(2);
		SelectedJets_E_excl1_1_->Draw();
		c55->cd(3);
		SelectedJets_Eta_excl1_1_->Draw();
		c55->cd(4);
		SelectedJets_Phi_excl1_1_->Draw();
		c55->cd(5);
		SelectedJets_HT_excl1_->Draw();
	}

	if(plot_56){
		TCanvas *c56 = new TCanvas("c56", "photon kinematics, 2 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c56->Divide(2,2);
		c56->cd(1);
		SelectedPhotons_Pt_excl2_1_->Draw();
		c56->cd(2);
		SelectedPhotons_E_excl2_1_->Draw();
		c56->cd(3);
		SelectedPhotons_Eta_excl2_1_->Draw();
		c56->cd(4);
		SelectedPhotons_Phi_excl2_1_->Draw();
	}

	if(plot_57){
		TCanvas *c57 = new TCanvas("c57", "Jet 1 kinematics, 2 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c57->Divide(2,2);
		c57->cd(1);
		SelectedJets_Pt_excl2_1_->Draw();
		c57->cd(2);
		SelectedJets_E_excl2_1_->Draw();
		c57->cd(3);
		SelectedJets_Eta_excl2_1_->Draw();
		c57->cd(4);
		SelectedJets_Phi_excl2_1_->Draw();
	}

	if(plot_58){
		TCanvas *c58 = new TCanvas("c58", "Jet 2 kinematics, 2 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c58->Divide(3,2);
		c58->cd(1);
		SelectedJets_Pt_excl2_2_->Draw();
		c58->cd(2);
		SelectedJets_E_excl2_2_->Draw();
		c58->cd(3);
		SelectedJets_Eta_excl2_2_->Draw();
		c58->cd(4);
		SelectedJets_Phi_excl2_2_->Draw();
		c58->cd(5);
		SelectedJets_HT_excl2_->Draw();
	}

	if(plot_59){
		TCanvas *c59 = new TCanvas("c59", "Jet 2 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c59->Divide(2,2);
		c59->cd(1);
		SelectedJets_Pt_2_->Draw();
		c59->cd(2);
		SelectedJets_E_2_->Draw();
		c59->cd(3);
		SelectedJets_Eta_2_->Draw();
		c59->cd(4);
		SelectedJets_Phi_2_->Draw();
	}

	if(plot_60){
		TCanvas *c60 = new TCanvas("c60", "Angular variables (>=2 jets)", 10, 10, 700, 700);
		gPad->SetLogy();
		c60->Divide(3,2);
		c60->cd(1);
		DeltaPhi_photon1_jet1_N1_->Draw();
		c60->cd(2);
		DeltaR_photon1_jet2_N1_->Draw();
		c60->cd(3);
		DeltaR_jet1_jet2_N1_->Draw();
		c60->cd(4);
		DeltaEta_jet1_jet2_N1_->Draw();
		c60->cd(5);
		DeltaPhi_jet1_jet2_N1_->Draw();
	}

	if(plot_61){
		TCanvas *c61 = new TCanvas("c61", "Jet 3 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c61->Divide(2,2);
		c61->cd(1);
		SelectedJets_Pt_3_->Draw();
		c61->cd(2);
		SelectedJets_E_3_->Draw();
		c61->cd(3);
		SelectedJets_Eta_3_->Draw();
		c61->cd(4);
		SelectedJets_Phi_3_->Draw();
	}

	if(plot_62){
		TCanvas *c62 = new TCanvas("c62", "Angular variables (>=3 jets)", 10, 10, 700, 700);
		gPad->SetLogy();
		c62->Divide(4,2);
		c62->cd(1);
		DeltaPhi_photon1_jet1_N2_->Draw();
		c62->cd(2);
		DeltaPhi_photon1_jet2_N2_->Draw();
		c62->cd(3);
		DeltaPhi_photon1_jet3_N2_->Draw();
		c62->cd(4);
		DeltaR_photon1_jet3_N2_->Draw();
		c62->cd(5);
		DeltaPhi_jet1_jet2_N2_->Draw();
		c62->cd(6);
		DeltaPhi_jet1_jet3_N2_->Draw();
		c62->cd(7);
		DeltaPhi_jet2_jet3_N2_->Draw();
	}


	if(plot_PrePost_01){
		TCanvas *c_PrePost01 = new TCanvas("c_PrePost01", "Pre-Post cuts plots 1", 10, 10, 700, 700);
		gPad->SetLogy();
		c_PrePost01->Divide(2,2);
		c_PrePost01->cd(1);
		gamma_Pt_1_precut1_->Draw();
		c_PrePost01->cd(2);
		gamma_Pt_1_postcut1_->Draw();
		c_PrePost01->cd(3);
		gamma_Pt_1_postcut2_->Draw();
		c_PrePost01->cd(4);		
		gamma_Pt_1_preTriMatch_->Draw();		
	}

	if(plot_PrePost_02){
		TCanvas *c_PrePost02 = new TCanvas("c_PrePost02", "Pre-Post cuts plots 2", 10, 10, 700, 700);
		gPad->SetLogy();
		c_PrePost02->Divide(4,3);
		c_PrePost02->cd(1);
		gamma_Pt_1_prePassConversionVeto_->Draw();
		c_PrePost02->cd(2);
		gamma_PassConversionVeto_1_prePassConversionVeto_->Draw();
		c_PrePost02->cd(3);
		gamma_Pt_1_prehadronicOverEm2012_->Draw();
		c_PrePost02->cd(4);
		gamma_hadronicOverEm2012_1_prehadronicOverEm2012_->Draw();
		c_PrePost02->cd(5);
		gamma_Pt_1_presigmaietaieta_->Draw();
		c_PrePost02->cd(6);
		gamma_sigmaietaieta_1_presigmaietaieta_->Draw();		
		c_PrePost02->cd(7);
		gamma_Pt_1_preiso_CH_->Draw();
		c_PrePost02->cd(8);
		gamma_iso_CH_1_preiso_CH_->Draw();
		c_PrePost02->cd(9);
		gamma_Pt_1_preiso_NH_->Draw();
		c_PrePost02->cd(10);
		gamma_iso_NH_1_preiso_NH_->Draw();
		c_PrePost02->cd(11);
		gamma_Pt_1_preiso_Ph_->Draw();
		c_PrePost02->cd(12);
		gamma_iso_Ph_1_preiso_Ph_->Draw();
	}

	if(plot_PrePost_03){
		TCanvas *c_PrePost03 = new TCanvas("c_PrePost03", "Pre-Post cuts plots 3", 10, 10, 700, 700);
		gPad->SetLogy();
		c_PrePost03->Divide(3,3);
		c_PrePost03->cd(1);
		gamma_Pt_1_preAcc_->Draw();
		c_PrePost03->cd(2);
		gamma_Eta_1_preAcc_->Draw();
		c_PrePost03->cd(3);
		gamma_Pt_1_postcut3_->Draw();
		c_PrePost03->cd(4);
		jets_deltaR_1_predeltaR_->Draw();
		c_PrePost03->cd(5);
		jets_Pt_1_preAcc_->Draw();
		c_PrePost03->cd(6);
		jets_Eta_1_preAcc_->Draw();
		c_PrePost03->cd(7);
		gamma_Pt_1_postcut4_->Draw();
		c_PrePost03->cd(8);
		jets_HT_preHT_->Draw();
	}


	if(Sig) {
		if(plot_unf_01){
			TCanvas *c_unf01 = new TCanvas("c_unf01", "Unfolding (>=1 jets)", 10, 10, 700, 700);
			gPad->SetLogy();
			c_unf01->Divide(3,3);
			c_unf01->cd(1);
			unf_photonPtGEN_N0_->Draw();
			c_unf01->cd(2);
			unf_SelectedJetsGEN_N_N0_->Draw();		
			c_unf01->cd(3);
			unf_SelectedJetsGEN_HT_N0_->Draw();
			c_unf01->cd(4);
			unf_SelectedPhotons_Pt_N0_1_->Draw();
			c_unf01->cd(5);
			unf_SelectedJets_N_N0_->Draw();		
			c_unf01->cd(6);
			unf_SelectedJets_HT_N0_->Draw();
			c_unf01->cd(7);
			TH2F_unf_GENREC_Photons_Pt_N0_->Draw();
			c_unf01->cd(8);
			TH2F_unf_GENREC_Jets_N_N0_->Draw();
			c_unf01->cd(9);
			TH2F_unf_GENREC_Jets_HT_N0_->Draw();
		}

		if(plot_unf_02){
			TCanvas *c_unf02 = new TCanvas("c_unf02", "Unfolding, 1 jet exclusive", 10, 10, 700, 700);
			gPad->SetLogy();
			c_unf02->Divide(3,3);
			c_unf02->cd(1);
			unf_photonPtGEN_excl1_->Draw();
			c_unf02->cd(2);
			unf_SelectedJetsGEN_N_excl1_->Draw();		
			c_unf02->cd(3);
			unf_SelectedJetsGEN_HT_excl1_->Draw();
			c_unf02->cd(4);
			unf_SelectedPhotons_Pt_excl1_1_->Draw();
			c_unf02->cd(5);
			unf_SelectedJets_N_excl1_->Draw();		
			c_unf02->cd(6);
			unf_SelectedJets_HT_excl1_->Draw();
			c_unf02->cd(7);
			TH2F_unf_GENREC_Photons_Pt_excl1_->Draw();
			c_unf02->cd(8);
			TH2F_unf_GENREC_Jets_N_excl1_->Draw();
			c_unf02->cd(9);
			TH2F_unf_GENREC_Jets_HT_excl1_->Draw();
		}

		if(plot_unf_03){
			TCanvas *c_unf03 = new TCanvas("c_unf03", "Unfolding, 2 jets exclusive", 10, 10, 700, 700);
			gPad->SetLogy();
			c_unf03->Divide(3,3);
			c_unf03->cd(1);
			unf_photonPtGEN_excl2_->Draw();
			c_unf03->cd(2);
			unf_SelectedJetsGEN_N_excl2_->Draw();		
			c_unf03->cd(3);
			unf_SelectedJetsGEN_HT_excl2_->Draw();
			c_unf03->cd(4);
			unf_SelectedPhotons_Pt_excl2_1_->Draw();
			c_unf03->cd(5);
			unf_SelectedJets_N_excl2_->Draw();		
			c_unf03->cd(6);
			unf_SelectedJets_HT_excl2_->Draw();
			c_unf03->cd(7);
			TH2F_unf_GENREC_Photons_Pt_excl2_->Draw();
			c_unf03->cd(8);
			TH2F_unf_GENREC_Jets_N_excl2_->Draw();
			c_unf03->cd(9);
			TH2F_unf_GENREC_Jets_HT_excl2_->Draw();
		}

		if(plot_unf_04){
			TCanvas *c_unf04 = new TCanvas("c_unf04", "Unfolding (>=2 jets)", 10, 10, 700, 700);
			gPad->SetLogy();
			c_unf04->Divide(3,3);
			c_unf04->cd(1);
			unf_photonPtGEN_N1_->Draw();
			c_unf04->cd(2);
			unf_SelectedJetsGEN_N_N1_->Draw();		
			c_unf04->cd(3);
			unf_SelectedJetsGEN_HT_N1_->Draw();
			c_unf04->cd(4);
			unf_SelectedPhotons_Pt_N1_1_->Draw();
			c_unf04->cd(5);
			unf_SelectedJets_N_N1_->Draw();		
			c_unf04->cd(6);
			unf_SelectedJets_HT_N1_->Draw();
			c_unf04->cd(7);
			TH2F_unf_GENREC_Photons_Pt_N1_->Draw();
			c_unf04->cd(8);
			TH2F_unf_GENREC_Jets_N_N1_->Draw();
			c_unf04->cd(9);
			TH2F_unf_GENREC_Jets_HT_N1_->Draw();
		}

		if(plot_unf_05){
			TCanvas *c_unf05 = new TCanvas("c_unf05", "Unfolding (>=3 jets)", 10, 10, 700, 700);
			gPad->SetLogy();
			c_unf05->Divide(3,3);
			c_unf05->cd(1);
			unf_photonPtGEN_N2_->Draw();
			c_unf05->cd(2);
			unf_SelectedJetsGEN_N_N2_->Draw();		
			c_unf05->cd(3);
			unf_SelectedJetsGEN_HT_N2_->Draw();
			c_unf05->cd(4);
			unf_SelectedPhotons_Pt_N2_1_->Draw();
			c_unf05->cd(5);
			unf_SelectedJets_N_N2_->Draw();		
			c_unf05->cd(6);
			unf_SelectedJets_HT_N2_->Draw();
			c_unf05->cd(7);
			TH2F_unf_GENREC_Photons_Pt_N2_->Draw();
			c_unf05->cd(8);
			TH2F_unf_GENREC_Jets_N_N2_->Draw();
			c_unf05->cd(9);
			TH2F_unf_GENREC_Jets_HT_N2_->Draw();
		}
	}

	cout << "...plots: quick check finished. " << endl;

	}


float deltaEta(float eta1, float eta2) { 

	float result = eta1 - eta2;
	float absresult = TMath::Abs(result);
	return absresult;
}

void Zero_Variables(){
}


void GJetsAnalyzer::Text_File(){

	cout << "Writing text file... " << endl;
	ofstream text;
	text.open(textname);
	text << "Running on " << sample_r << endl;
	text << "Weight is " << weight_r << endl;
	text << "Analysis selection:" << endl;
	text << "Number of selected events 0 (Ntuple preselection), unweighted = " << iSelected0 << endl;
	text << "Number of selected events 1 (trigger family 4), unweighted = " << iSelected1 << endl;		
	text << "Number of selected events 2 (Iso at GEN level), unweighted = " << iSelected2 << endl;
	text << "Number of selected events 3 (TriMatch+(ID+Iso)+kin Photons: then, on the LEADING one), unweighted = " << iSelected3 << endl;
	text << "Number of selected events 4 (kin+PU Jets: then, cleaned vs. LEADING Photon), unweighted = " << iSelected4 << endl;
	text << "Number of selected events 5 (HT), unweighted = " << iSelected5 << endl;
	text << "Number of selected events (all selections), unweighted = " << iSelected5 << endl;
	text << "Number of selected events (all selections), weighted = " << iSelected5*weight_r << endl;
	text.close();
	text << "...writing text file finished. " << endl;
	}
