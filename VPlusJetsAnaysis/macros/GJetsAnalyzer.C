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
	bool TeP_corr = true;							// T&P correction
	bool BackDataDriven_corr = false;	// background data-driven correction
	bool SigBack = true;							// to avoid double counting for SIGNAL and BACKGROUND
	bool inv_sigmaietaieta = false;		// inverted sigmaietaieta cut
	bool inv_isolation = false;				// inverted isolation set cut
		
	bool plothistos = false;					// please select which plots to show
	bool textfile = true;							// if you want a text report for each sample
	Int_t itype = 17;									// it identifies histos with different analysis 

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
	if (data_ReReco) Lumi_t = 19789.; // /pb
	else Lumi_t = 19027.853; // /pb
	double xsec = 1.;
	double FiltEff = 1.;
	double kFac = 1.;
	double nEvents = 1.;

	Float_t weight = 1; 
	Float_t weight_withPU = 1;
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
		nEvents = 1.;
		xsec = 1.; //da cambiare
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
		xsec = 5212.0; //da cambiare
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
		xsec = 1008.03; //da cambiare
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
		nEvents = 42345850;
		xsec = 105.418; //da cambiare
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
		xsec = 200061.7; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 19931.62; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 3322.309; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 558.2865; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 108.0068; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 30.12207; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 2.138632; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 0.2119244; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 0.007077847; //da cambiare
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 0.000045103; //da cambiare 4.510327E-5
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 0.000001867; //da cambiare 1.867141E-6
		FiltEff = 1.;
		kFac = 1.3;
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
		xsec = 75.39; //da cambiare
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
		nEvents = 35040695;
		xsec = 2.88651E8; //da cambiare
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
		xsec = 7.43031E7; //da cambiare
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
		xsec = 1.19391E6; //da cambiare
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
		nEvents = 31761753;
		xsec = 30980.0; //da cambiare
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
		nEvents = 34611322;
		xsec = 4245.29; //da cambiare
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
		nEvents = 34080562;
		xsec = 810.454; //da cambiare
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
		nEvents = 1948532 ;
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
		xsec = 1.0515E7; //da cambiare
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
		xsec = 276000.0; //da cambiare
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
		xsec = 8631.07; //da cambiare
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
		xsec = 210.585; //da cambiare
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
		
		bool Sig = (mysample == 0) || (mysample > 20 && mysample < 25)  || (mysample > 30 && mysample < 42) || (mysample == 51);
		bool isoGEN; 
		if (SigBack) {
			isoGEN = false; 
			if(isMC) {
				if(Sig) { 
					isoGEN = (photonIsoSumPtDR03GEN >= 0. && photonIsoSumPtDR03GEN <= 10.); // SIGNAL
				}
				else {
					isoGEN = (photonIsoSumPtDR03GEN < 0); // BACKGROUND it was (photonIsoSumPtDR03GEN < 0 || photonIsoSumPtDR03GEN > 10); in the previous N-tuple production step  
				}
			}
			else isoGEN = true;
		}
		else {
			isoGEN = true; 
		}
		if (isoGEN) {

			// ==================================== GEN selection
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
						cout << "ERROR: Wrong geometry string writed (only barrel or endcaps)" << endl;
					} // end eta - definition

					// photonGEN kinematic selection
//					if (photonPtGEN > 180. && geo_selGEN) {
					if (photonPtGEN > 0. && geo_selGEN) {

						// kin JetsGEN (cleaned vs. photonGEN) selection
						if (SelectedJetsGEN_N > 0){

							// HTGEN selection
							if (SelectedJetsGEN_HT > 0){

								nPhotonsGEN_N0_->Fill(nPhotonsGEN, weight);
								
								photonPtGEN_N0_->Fill(photonPtGEN, weight);
								photonEGEN_N0_->Fill(photonEGEN, weight);
								photonEtaGEN_N0_->Fill(photonEtaGEN, weight);
								photonPhiGEN_N0_->Fill(photonPhiGEN, weight);

								SelectedJetsGEN_N_N0_->Fill(SelectedJetsGEN_N, weight);

								SelectedJets_PtGEN_N0_1_->Fill(SelectedJetsGEN_Pt.at(0), weight);
								SelectedJets_EGEN_N0_1_->Fill(SelectedJetsGEN_E.at(0), weight);
								SelectedJets_EtaGEN_N0_1_->Fill(SelectedJetsGEN_Eta.at(0), weight);
								SelectedJets_PhiGEN_N0_1_->Fill(SelectedJetsGEN_Phi.at(0), weight);
								
								SelectedJetsGEN_HT_N0_->Fill(SelectedJetsGEN_HT, weight);

								if (SelectedJetsGEN_N == 1){
									photonPtGEN_excl1_->Fill(photonPtGEN, weight);
								}

								if (SelectedJetsGEN_N == 2){
									photonPtGEN_excl2_->Fill(photonPtGEN, weight);
								}

								if (SelectedJetsGEN_N > 1){
									photonPtGEN_N1_->Fill(photonPtGEN, weight);
								}

								if (SelectedJetsGEN_N > 2){
									photonPtGEN_N2_->Fill(photonPtGEN, weight);
								}
							} // end HTGEN selection
						} // end kin JetsGEN (cleaned vs. photonGEN) selection
					} // end photonGEN kinematic selection
				} // end photonGEN selection

				pre_photonIsoSumPtDR03GEN_->Fill(photonIsoSumPtDR03GEN, weight);
				HTParSum_->Fill(HTParSum, weight);

				// clean jets GEN
				SelectedJetsGEN_N = 0;
				SelectedJetsGEN_HT = 0;
				
				SelectedJetsGEN_Pt.clear();
				SelectedJetsGEN_E.clear();
				SelectedJetsGEN_Eta.clear();
				SelectedJetsGEN_Phi.clear();
				// end clean jets GEN

			} // end GEN selection


			// ==================================== REC selection

			iSelected0++;
			// trigger family selection
			if (8 & isTriggered) {
			
				// photon selection
				if(nPhotons > 0 && (nPhotons == (int)photonPt->size()) ) {

					IDIsoPhotons_N = 0;
					SelectedPhotons_N = 0;

					// SelectedPhotons collection selection 
					for(unsigned int iPhoPos = 0; iPhoPos < photonPt->size(); iPhoPos++) {
					
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
						// end T&P scale factors - definitions

						// background data-driven correction - definitions
						float BackDataDriven_F;
						if (BackDataDriven_corr) {
							if (isMC) BackDataDriven_F = 1.;
							else {
								bool bin_Pt1 = false;
								bool bin_Pt2 = false;
								bool bin_Pt3 = false;
								bool bin_Pt4 = false;
								bool bin_Pt5 = false;
								bool bin_Pt6 = false;

								bin_Pt1 = (photonPt->at(iPhoPos) > 180 && photonPt->at(iPhoPos) < 200);
								bin_Pt2 = (photonPt->at(iPhoPos) > 200 && photonPt->at(iPhoPos) < 250);
								bin_Pt3 = (photonPt->at(iPhoPos) > 250 && photonPt->at(iPhoPos) < 300);
								bin_Pt4 = (photonPt->at(iPhoPos) > 300 && photonPt->at(iPhoPos) < 350);
								bin_Pt5 = (photonPt->at(iPhoPos) > 350 && photonPt->at(iPhoPos) < 400);
								bin_Pt6 = (photonPt->at(iPhoPos) > 400);

								if (bin_Pt1) BackDataDriven_F = 0.907928; // 0.898643;
								else if (bin_Pt2) BackDataDriven_F = 0.921654; // 0.906496;
								else if (bin_Pt3) BackDataDriven_F = 0.910021; // 0.916848;
								else if (bin_Pt4) BackDataDriven_F = 0.947525; // 0.937596;
								else if (bin_Pt5) BackDataDriven_F = 0.977818; // 0.985119;
								else if (bin_Pt6) BackDataDriven_F = 0.982116; // 0.96313;
								else BackDataDriven_F = 1.;
							}
						}
						else BackDataDriven_F = 1.;
						// end background data-driven correction - definitions


						// PF isolation variables - definitions
						photonPfIso = 0;
						photonIsoFPR = 0;
	
						photonPfIso = photonPfIsoChargedHad->at(iPhoPos) + photonPfIsoNeutralHad->at(iPhoPos) + photonPfIsoPhoton->at(iPhoPos);
						photonIsoFPR = photonIsoFPRCharged->at(iPhoPos) + photonIsoFPRNeutral->at(iPhoPos) + photonIsoFPRPhoton->at(iPhoPos);
						// end PF isolation variables - definitions

						// Rho corrected PF isolation variables - definitions
						double EA_CH, EA_NH, EA_Ph;
						if (abs(photonEta->at(iPhoPos)) < 1.0) {
							 EA_CH = 0.012;
							 EA_NH = 0.030;
							 EA_Ph = 0.148;
						}
						else if (abs(photonEta->at(iPhoPos)) >= 1.0 && abs(photonEta->at(iPhoPos)) < 1.479) {
							 EA_CH = 0.010;
							 EA_NH = 0.057;
							 EA_Ph = 0.130;
						}
						else if (abs(photonEta->at(iPhoPos)) >= 1.479 && abs(photonEta->at(iPhoPos)) < 2.0) {
							 EA_CH = 0.014;
							 EA_NH = 0.039;
							 EA_Ph = 0.112;
						}
						else if (abs(photonEta->at(iPhoPos)) >= 2.0 && abs(photonEta->at(iPhoPos)) < 2.2) {
							 EA_CH = 0.012;
							 EA_NH = 0.015;
							 EA_Ph = 0.216;	
						}
						else if (abs(photonEta->at(iPhoPos)) >= 2.2 && abs(photonEta->at(iPhoPos)) < 2.3) {
							 EA_CH = 0.016;
							 EA_NH = 0.024;
							 EA_Ph = 0.262;	
						}
						else if (abs(photonEta->at(iPhoPos)) >= 2.3 && abs(photonEta->at(iPhoPos)) < 2.4) {
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
								if (photonid_sieie->at(iPhoPos) >= 0.011 && photonid_sieie->at(iPhoPos) <= 0.017) sigmaietaieta = true;
								else sigmaietaieta = false;
							}	
							if (!inv_isolation){
								if(photonPfIsoChargedHad_RhoCorr < 1.5) iso_CH = true;
								else iso_CH = false;
								if(photonPfIsoNeutralHad_RhoCorr < (1.0 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
								else iso_NH = false;
								if(photonPfIsoPhoton_RhoCorr < (0.7 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
								else iso_Ph = false;
							}
							else {
								if(photonPfIsoChargedHad_RhoCorr >= 1.5) iso_CH = true;
								else iso_CH = false;
								if(photonPfIsoNeutralHad_RhoCorr < (1.0 + 0.04*photonPt->at(iPhoPos))) iso_NH = true;
								else iso_NH = false;
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
								if(photonPfIsoPhoton_RhoCorr < (1.0 + 0.005*photonPt->at(iPhoPos))) iso_Ph = true;
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
							cout << "ERROR: Wrong geometry string writed (only barrel or endcaps)" << endl;
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

							IDIsoPhotons_N += 1;

							// eta - definition
							bool geo_sel = false;
							if (geo == "barrel") {
								geo_sel = photonBit->at(iPhoPos)&1;
							}
							else if (geo == "endcaps"){
								geo_sel = photonBit->at(iPhoPos)&2;
							}
							else {
								cout << "Error: Wrong geometry string writed" << endl;
							} // end eta - definition

							// photon kinematic selection
							if (photonPt->at(iPhoPos) > 180. && geo_sel) {

								// photon trigger matching selection (to be changed in the next N-tuple production step)
								if (isTriggerMatchedFamily4) {

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
								
									SelectedPhotons_Bit.push_back(photonBit->at(iPhoPos));
									SelectedPhotons_TeP_SF.push_back(TeP_SF);
									SelectedPhotons_BackDataDriven_F.push_back(BackDataDriven_F);
							
									SelectedPhotons_N+=1;

								}	// end photon kinematic selection
							}	// end photon trigger matching selection
						} // end photon quality selection
					} // end SelectedPhotons collection selection
				} // end photon selection

			
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
				
						if (!closeLEA){
						
							// jets kinematic selection
							if(jetPt->at(iJetPos) > 30. && TMath::Abs(jetEta->at(iJetPos)) < 2.5 ){

								// jets pile-up ID correction							
								if ( pow(jetRMS->at(iJetPos),2) <  0.06 || (1-jetBeta->at(iJetPos)) < 0.2 * TMath::Log(nVtx-0.65) ) {
									
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

				if (SelectedPhotons_N > 0 && SelectedJets_N > 0){
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


				// =========== Analysis selection
				// (photonBit |= (it->isEB() << 0) => (*photonBit)[0]&1) with 2^0 = 1
				iSelected1++;

				// ID+Iso+kin Photons selection (then, on the LEADING one)
				if (SelectedPhotons_N > 0){

					scale_TeP = SelectedPhotons_TeP_SF.at(0);
					scale_BackDataDriven = SelectedPhotons_BackDataDriven_F.at(0);
					weight_final = scale_TeP * scale_BackDataDriven * weight_withPU;

					iSelected2++;

					// kin Jets (cleaned vs. Photons) selection
					if (SelectedJets_N > 0) {
						iSelected3++;

						// HT selection
						if (SelectedJets_HT > 0){
							iSelected4++;

							Nvtx_->Fill(nVtx, weight_final);

							IDIsoPhotons_N_->Fill(IDIsoPhotons_N, weight_final);
							SelectedPhotons_N_->Fill(SelectedPhotons_N, weight_final);

							SelectedPhotons_Pt_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
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
							SelectedPhotons_PfIso_RhoCorr_forFit_1_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);


							if (SelectedPhotons_Pt.at(0) > 180 && SelectedPhotons_Pt.at(0) < 200){
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
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 200 && SelectedPhotons_Pt.at(0) < 250){
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
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							}
							
							if (SelectedPhotons_Pt.at(0) > 250 && SelectedPhotons_Pt.at(0) < 300){
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
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 300 && SelectedPhotons_Pt.at(0) < 350){
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
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 350 && SelectedPhotons_Pt.at(0) < 400){
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
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
							}

							if (SelectedPhotons_Pt.at(0) > 400){
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
								SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_->Fill(SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
								TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_->Fill(SelectedPhotons_id_sieie.at(0), SelectedPhotons_PfIso_RhoCorr_forFit.at(0), weight_final);
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
							
							SelectedPhotons_Bit_1_->Fill(SelectedPhotons_Bit.at(0), weight_final);

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

							if (SelectedJets_N == 1){
								SelectedPhotons_Pt_excl1_1_->Fill(SelectedPhotons_Pt.at(0), weight_final);
								SelectedPhotons_E_excl1_1_->Fill(SelectedPhotons_E.at(0), weight_final);
								SelectedPhotons_Eta_excl1_1_->Fill(SelectedPhotons_Eta.at(0), weight_final);
								SelectedPhotons_Phi_excl1_1_->Fill(SelectedPhotons_Phi.at(0), weight_final);

								SelectedJets_Pt_excl1_1_->Fill(SelectedJets_Pt.at(0), weight_final);
								SelectedJets_E_excl1_1_->Fill(SelectedJets_E.at(0), weight_final);
								SelectedJets_Eta_excl1_1_->Fill(SelectedJets_Eta.at(0), weight_final);
								SelectedJets_Phi_excl1_1_->Fill(SelectedJets_Phi.at(0), weight_final);
							}

							if (SelectedJets_N == 2){
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
							}

							if (SelectedJets_N > 1){
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
							}
	
							if (SelectedJets_N > 2){
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
							}

							if(isMC){
								photonIsoSumPtDR03GEN_->Fill(photonIsoSumPtDR03GEN, 1);
							}

						} // end HT selection
					} // end kin Jets (cleaned vs. Photons) selection 
				} // end ID+Iso+kin Photons selection (then, on the LEADING one)

				// clean jets
				SelectedJetsALL_N = 0;
				SelectedJets_N = 0;
				SelectedJets_HT = 0;
				
				SelectedJets_Pt.clear();
				SelectedJets_E.clear();
				SelectedJets_Eta.clear();
				SelectedJets_Phi.clear();

				vPtEtaPhiE.clear();
				// end clean jets

				// clean photons
				IDIsoPhotons_N = 0;
				SelectedPhotons_N = 0;
			
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
			
				SelectedPhotons_Bit.clear();

				SelectedPhotons_TeP_SF.clear();
				SelectedPhotons_BackDataDriven_F.clear();				
				// end clean photons

			}// end trigger family selection
			 // end REC selection
			 
		} // end SIGNAL and BACKGROUND separated behaviour to avoid double counting

		// if (Cut(ientry) < 0) continue;
	} // end loop on entries

	// ====================================terminate and plot

	cout << "Analysis selection:" << endl;
	cout << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	cout << "Number of selected events 0 (Iso at GEN level), unweighted = " << iSelected0 << endl;
	cout << "Number of selected events 1 (trigger family 4), unweighted = " << iSelected1 << endl;
	cout << "Number of selected events 2 (ID+Iso+kin Photons: then, on the LEADING one), unweighted = " << iSelected2 << endl;
	cout << "Number of selected events 3 (kin Jets: cleaned vs. LEADING Photons), unweighted = " << iSelected3 << endl;
	cout << "Number of selected events 4 (HT), unweighted = " << iSelected4 << endl;
	cout << "Number of selected events (all selections), unweighted = " << iSelected4 << endl;
	cout << "Number of selected events (all selections), weighted = " << iSelected4*weight_r << endl;

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
	SelectedPhotons_E_1_ = new TH1F("SelectedPhotons_E_1_","Photon E ", 800, 0., 4000.);
	SelectedPhotons_Eta_1_ = new TH1F("SelectedPhotons_Eta_1_","Photon #eta ", 3000, -3, 3);
	SelectedPhotons_Phi_1_ = new TH1F("SelectedPhotons_Phi_1_","Photon #varphi ", 1000, -3.1416, 3.1416);
	SelectedPhotons_Bit_1_ = new TH1F("SelectedPhotons_Bit_1_","Photon bit ", 100, 0., 1000.);

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
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_", "photon PfIsoChargedHad #rho corrected for Fit", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_", "photon PfIsoNeutralHad #rho corrected for Fit", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_", "photon PfIsoPhoton #rho corrected for Fit", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_", "photon PfIso #rho corrected for Fit", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_04
	SelectedPhotons_id_sieie_1_bin01_ = new TH1F("SelectedPhotons_id_sieie_1_bin01_", "photon ID: #sigma_{i#etai#eta}, 180 < p_{T}^{#gamma} < 200", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin01_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin01_", "photon PfIsoChargedHad, 180 < p_{T}^{#gamma} < 200", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin01_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin01_", "photon PfIsoNeutralHad, 180 < p_{T}^{#gamma} < 200", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin01_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin01_", "photon PfIsoPhoton, 180 < p_{T}^{#gamma} < 200", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin01_ = new TH1F("SelectedPhotons_PfIso_1_bin01_", "photon PfIso, 180 < p_{T}^{#gamma} < 200", 2000, 0, 200);

	//plotsCompare_05
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin01_", "photon PfIsoChargedHad #rho corrected, 180 < p_{T}^{#gamma} < 200", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin01_", "photon PfIsoNeutralHad #rho corrected, 180 < p_{T}^{#gamma} < 200", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin01_", "photon PfIsoPhoton #rho corrected, 180 < p_{T}^{#gamma} < 200", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin01_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin01_", "photon PfIso #rho corrected, 180 < p_{T}^{#gamma} < 200", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin01_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 180 < p_{T}^{#gamma} < 200", 500, 0., 0.050, 2000, 0, 200);
	
	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin01_", "photon PfIsoChargedHad #rho corrected for Fit, 180 < p_{T}^{#gamma} < 200", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin01_", "photon PfIsoNeutralHad #rho corrected for Fit, 180 < p_{T}^{#gamma} < 200", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin01_", "photon PfIsoPhoton #rho corrected for Fit, 180 < p_{T}^{#gamma} < 200", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_", "photon PfIso #rho corrected for Fit, 180 < p_{T}^{#gamma} < 200", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 180 < p_{T}^{#gamma} < 200", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_06
	SelectedPhotons_id_sieie_1_bin02_ = new TH1F("SelectedPhotons_id_sieie_1_bin02_", "photon ID: #sigma_{i#etai#eta}, 200 < p_{T}^{#gamma} < 250", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin02_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin02_", "photon PfIsoChargedHad, 200 < p_{T}^{#gamma} < 250", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin02_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin02_", "photon PfIsoNeutralHad, 200 < p_{T}^{#gamma} < 250", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin02_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin02_", "photon PfIsoPhoton, 200 < p_{T}^{#gamma} < 250", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin02_ = new TH1F("SelectedPhotons_PfIso_1_bin02_", "photon PfIso, 200 < p_{T}^{#gamma} < 250", 2000, 0, 200);

	//plotsCompare_07
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin02_", "photon PfIsoChargedHad #rho corrected, 200 < p_{T}^{#gamma} < 250", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin02_", "photon PfIsoNeutralHad #rho corrected, 200 < p_{T}^{#gamma} < 250", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin02_", "photon PfIsoPhoton #rho corrected, 200 < p_{T}^{#gamma} < 250", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin02_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin02_", "photon PfIso #rho corrected, 200 < p_{T}^{#gamma} < 250", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin02_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 200 < p_{T}^{#gamma} < 250", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin02_", "photon PfIsoChargedHad #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin02_", "photon PfIsoNeutralHad #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin02_", "photon PfIsoPhoton #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_", "photon PfIso #rho corrected for Fit, 200 < p_{T}^{#gamma} < 250", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 200 < p_{T}^{#gamma} < 250", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_08
	SelectedPhotons_id_sieie_1_bin03_ = new TH1F("SelectedPhotons_id_sieie_1_bin03_", "photon ID: #sigma_{i#etai#eta}, 250 < p_{T}^{#gamma} < 300", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin03_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin03_", "photon PfIsoChargedHad, 250 < p_{T}^{#gamma} < 300", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin03_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin03_", "photon PfIsoNeutralHad, 250 < p_{T}^{#gamma} < 300", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin03_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin03_", "photon PfIsoPhoton, 250 < p_{T}^{#gamma} < 300", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin03_ = new TH1F("SelectedPhotons_PfIso_1_bin03_", "photon PfIso, 250 < p_{T}^{#gamma} < 300", 2000, 0, 200);

	//plotsCompare_09
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin03_", "photon PfIsoChargedHad #rho corrected, 250 < p_{T}^{#gamma} < 300", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin03_", "photon PfIsoNeutralHad #rho corrected, 250 < p_{T}^{#gamma} < 300", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin03_", "photon PfIsoPhoton #rho corrected, 250 < p_{T}^{#gamma} < 300", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin03_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin03_", "photon PfIso #rho corrected, 250 < p_{T}^{#gamma} < 300", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin03_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 250 < p_{T}^{#gamma} < 300", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin03_", "photon PfIsoChargedHad #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin03_", "photon PfIsoNeutralHad #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin03_", "photon PfIsoPhoton #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_", "photon PfIso #rho corrected for Fit, 250 < p_{T}^{#gamma} < 300", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 250 < p_{T}^{#gamma} < 300", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_10
	SelectedPhotons_id_sieie_1_bin04_ = new TH1F("SelectedPhotons_id_sieie_1_bin04_", "photon ID: #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 350", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin04_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin04_", "photon PfIsoChargedHad, 300 < p_{T}^{#gamma} < 350", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin04_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin04_", "photon PfIsoNeutralHad, 300 < p_{T}^{#gamma} < 350", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin04_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin04_", "photon PfIsoPhoton, 300 < p_{T}^{#gamma} < 350", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin04_ = new TH1F("SelectedPhotons_PfIso_1_bin04_", "photon PfIso, 300 < p_{T}^{#gamma} < 350", 2000, 0, 200);

	//plotsCompare_11
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin04_", "photon PfIsoChargedHad #rho corrected, 300 < p_{T}^{#gamma} < 350", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin04_", "photon PfIsoNeutralHad #rho corrected, 300 < p_{T}^{#gamma} < 350", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin04_", "photon PfIsoPhoton #rho corrected, 300 < p_{T}^{#gamma} < 350", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin04_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin04_", "photon PfIso #rho corrected, 300 < p_{T}^{#gamma} < 350", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin04_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 350", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin04_", "photon PfIsoChargedHad #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin04_", "photon PfIsoNeutralHad #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin04_", "photon PfIsoPhoton #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_", "photon PfIso #rho corrected for Fit, 300 < p_{T}^{#gamma} < 350", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 300 < p_{T}^{#gamma} < 350", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_12
	SelectedPhotons_id_sieie_1_bin05_ = new TH1F("SelectedPhotons_id_sieie_1_bin05_", "photon ID: #sigma_{i#etai#eta}, 350 < p_{T}^{#gamma} < 400", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin05_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin05_", "photon PfIsoChargedHad, 350 < p_{T}^{#gamma} < 400", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin05_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin05_", "photon PfIsoNeutralHad, 350 < p_{T}^{#gamma} < 400", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin05_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin05_", "photon PfIsoPhoton, 350 < p_{T}^{#gamma} < 400", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin05_ = new TH1F("SelectedPhotons_PfIso_1_bin05_", "photon PfIso, 350 < p_{T}^{#gamma} < 400", 2000, 0, 200);

	//plotsCompare_13
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin05_", "photon PfIsoChargedHad #rho corrected, 350 < p_{T}^{#gamma} < 400", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin05_", "photon PfIsoNeutralHad #rho corrected, 350 < p_{T}^{#gamma} < 400", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin05_", "photon PfIsoPhoton #rho corrected, 350 < p_{T}^{#gamma} < 400", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin05_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin05_", "photon PfIso #rho corrected, 350 < p_{T}^{#gamma} < 400", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin05_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, 350 < p_{T}^{#gamma} < 400", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin05_", "photon PfIsoChargedHad #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin05_", "photon PfIsoNeutralHad #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin05_", "photon PfIsoPhoton #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_", "photon PfIso #rho corrected for Fit, 350 < p_{T}^{#gamma} < 400", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, 350 < p_{T}^{#gamma} < 400", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_14
	SelectedPhotons_id_sieie_1_bin06_ = new TH1F("SelectedPhotons_id_sieie_1_bin06_", "photon ID: #sigma_{i#etai#eta}, p_{T}^{#gamma} > 400", 500, 0., 0.050);
	SelectedPhotons_PfIsoChargedHad_1_bin06_ = new TH1F("SelectedPhotons_PfIsoChargedHad_1_bin06_", "photon PfIsoChargedHad, p_{T}^{#gamma} > 400", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_1_bin06_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_1_bin06_", "photon PfIsoNeutralHad, p_{T}^{#gamma} > 400", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_1_bin06_ = new TH1F("SelectedPhotons_PfIsoPhoton_1_bin06_", "photon PfIsoPhoton, p_{T}^{#gamma} > 500", 2000, 0, 200);
	SelectedPhotons_PfIso_1_bin06_ = new TH1F("SelectedPhotons_PfIso_1_bin06_", "photon PfIso, p_{T}^{#gamma} > 400", 2000, 0, 200);

	//plotsCompare_15
	SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_1_bin06_", "photon PfIsoChargedHad #rho corrected, p_{T}^{#gamma} > 400", 4000, 0, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_1_bin06_", "photon PfIsoNeutralHad #rho corrected, p_{T}^{#gamma} > 400", 2000, 0, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_1_bin06_", "photon PfIsoPhoton #rho corrected, p_{T}^{#gamma} > 400", 2000, 0, 200);
	SelectedPhotons_PfIso_RhoCorr_1_bin06_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_1_bin06_", "photon PfIso #rho corrected, p_{T}^{#gamma} > 400", 2000, 0, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_vs_sieie_1_bin06_",  "photon PfIso #rho corrected vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 400", 500, 0., 0.050, 2000, 0, 200);

	SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIsoChargedHad_RhoCorr_forFit_1_bin06_", "photon PfIsoChargedHad #rho corrected for Fit, p_{T}^{#gamma} > 400", 8000, -100, 100);
	SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIsoNeutralHad_RhoCorr_forFit_1_bin06_", "photon PfIsoNeutralHad #rho corrected for Fit, p_{T}^{#gamma} > 400", 4000, -200, 200);
	SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIsoPhoton_RhoCorr_forFit_1_bin06_", "photon PfIsoPhoton #rho corrected for Fit, p_{T}^{#gamma} > 400", 4000, -200, 200);
	SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_ = new TH1F("SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_", "photon PfIso #rho corrected for Fit, p_{T}^{#gamma} > 400", 4000, -200, 200);
	TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_ = new TH2F ("TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_",  "photon PfIso #rho corrected for Fit vs. photon #sigma_{i#etai#eta}, p_{T}^{#gamma} > 400", 500, 0., 0.050, 4000, -200, 200);

	//plotsCompare_16
	SelectedPhotons_PfIsoPhotons03ForCic_1_ = new TH1F("SelectedPhotons_PfIsoPhotons03ForCic_1_", "photon PfIsoPhotons03ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoNeutrals03ForCic_1_ = new TH1F("SelectedPhotons_PfIsoNeutrals03ForCic_1_","photon PfIsoNeutrals03ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged03ForCicVtx0_1_ = new TH1F("SelectedPhotons_PfIsoCharged03ForCicVtx0_1_", "photon PfIsoCharged03ForCicVtx0", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged03BadForCic_1_ = new TH1F("SelectedPhotons_PfIsoCharged03BadForCic_1_", "photon PfIsoCharged03BadForCic", 2000, 0, 200);
	
	//plotsCompare_17
	SelectedPhotons_PfIsoPhotons04ForCic_1_ = new TH1F("SelectedPhotons_PfIsoPhotons04ForCic_1_", "photon PfIsoPhotons04ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoNeutrals04ForCic_1_ = new TH1F("SelectedPhotons_PfIsoNeutrals04ForCic_1_", "photon PfIsoNeutrals04ForCic", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged04ForCicVtx0_1_ = new TH1F("SelectedPhotons_PfIsoCharged04ForCicVtx0_1_", "photon PfIsoCharged04ForCicVtx0", 2000, 0, 200);
	SelectedPhotons_PfIsoCharged04BadForCic_1_ = new TH1F("SelectedPhotons_PfIsoCharged04BadForCic_1_", "photonPfIsoCharged04BadForCic", 2000, 0, 200);
	
	//plotsCompare_18	
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
	
	//plotsCompare_19	
	SelectedPhotons_hcalTowerSumEtConeDR04_1_ = new TH1F("SelectedPhotons_hcalTowerSumEtConeDR04_1_","photon hcalTowerSumEtConeDR04", 1000, 0, 1000);
	SelectedPhotons_ecalRecHitSumEtConeDR04_1_ = new TH1F("SelectedPhotons_ecalRecHitSumEtConeDR04_1_", "photon ecalRecHitSumEtConeDR04", 1000, 0, 1000);
	SelectedPhotons_nTrkSolidConeDR04_1_ = new TH1F("SelectedPhotons_nTrkSolidConeDR04_1_", "photon nTrkSolidConeDR04", 2000, 0, 1000);
	SelectedPhotons_trkSumPtSolidConeDR04_1_ = new TH1F("SelectedPhotons_trkSumPtSolidConeDR04_1_","photon trkSumPtSolidConeDR04", 1000, 0, 1000);
	SelectedPhotons_nTrkHollowConeDR04_1_ = new TH1F("SelectedPhotons_nTrkHollowConeDR04_1_", "photon nTrkHollowConeDR04", 200, 0, 100) ;
	SelectedPhotons_trkSumPtHollowConeDR04_1_ = new TH1F("SelectedPhotons_trkSumPtHollowConeDR04_1_", "photon trkSumPtHollowConeDR04", 1000, 0, 1000);
	
	//plotsCompare_20	
	SelectedPhotons_IsoFPRCharged_1_ = new TH1F("SelectedPhotons_IsoFPRCharged_1_", "photon IsoFPRCharged", 2000, 0, 200); 
	SelectedPhotons_IsoFPRNeutral_1_ = new TH1F("SelectedPhotons_IsoFPRNeutral_1_", "photon IsoFPRNeutral", 2000, 0, 200);
	SelectedPhotons_IsoFPRPhoton_1_ = new TH1F("SelectedPhotons_IsoFPRPhoton_1_", "photon IsoFPRPhoton", 2000, 0, 200);
	SelectedPhotons_IsoFPR_1_ = new TH1F("SelectedPhotons_IsoFPR_1_", "photon IsoFPR", 2000, 0, 200);

	//plotsCompare_21
	SelectedJetsALL_N_ = new TH1F("SelectedJetsALL_N_","Selected Jets vs. ALL Photons N", 10, 0, 10);
	SelectedJets_N_ = new TH1F("SelectedJets_N_","Selected Jets N", 10, 0, 10);

	//plotsCompare_22
	SelectedJets_Pt_1_ = new TH1F("SelectedJets_Pt_1_","Jet 1 p_{T} ", 800, 0., 4000.);
	SelectedJets_E_1_ = new TH1F("SelectedJets_E_1_", "Jet 1 E", 800, 0., 4000.);
	SelectedJets_Eta_1_ = new TH1F("SelectedJets_Eta_1_","Jet 1 #eta ", 3000, -3, 3);
	SelectedJets_Phi_1_ = new TH1F("SelectedJets_Phi_1_","Jet 1 #varphi ", 1000, -3.1416, 3.1416);

	//plotsCompare_23
	SelectedJets_HT_ = new TH1F("SelectedJets_HT_","Selected Jets H_{T}", 400, 0, 4000);

	//plotsCompare_24
	DeltaR_photon1_jet1_N0_ = new TH1F("DeltaR_photon1_jet1_N0_","#DeltaR #gamma1-jet1 - N^{jets} #geq 1", 600, 0, 6);
	DeltaEta_photon1_jet1_N0_ = new TH1F("DeltaEta_photon1_jet1_N0_","#Delta#eta #gamma1-jet1 - N^{jets} #geq 1", 500, 0, 5);
	DeltaPhi_photon1_jet1_N0_ = new TH1F("DeltaPhi_photon1_jet1_N0_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 1", 500, 0, 3.1416);

	//plotsCompare_25
	thrust_N0_ = new TH1F("thrust_N0_","#tau_{T} - N^{jets} #geq 1", 100, 0, 0.5);
	broad_N0_ = new TH1F("broad_N0_","broad - N^{jets} #geq 1", 100, 0, 1);
	S3_N0_ = new TH1F("S3_N0_","S3 - N^{jets} #geq 1", 300, -2, 4);
	S4_N0_ = new TH1F("S4_N0_","S4 - N^{jets} #geq 1", 400, -0.2, 0.2);

	ln_thrust_N0_ = new TH1F("ln_thrust_N0_","ln #tau_{T} - N^{jets} #geq 1", 300, -30, 0);
	ln_broad_N0_ = new TH1F("ln_broad_N0_","ln broad - N^{jets} #geq 1", 300, -5, 1);
	ln_S3_N0_ = new TH1F("ln_S3_N0_","ln S3 - N^{jets} #geq 1", 400, -5, 3);
	ln_S4_N0_ = new TH1F("ln_S4_N0_","ln S4 - N^{jets} #geq 1", 200, -1000, 1000);

	//plotsCompare_26
	SelectedPhotons_Pt_excl1_1_ = new TH1F("SelectedPhotons_Pt_excl1_1_","Photon p_{T}, 1 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_E_excl1_1_ = new TH1F("SelectedPhotons_E_excl1_1_","Photon E, 1 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_Eta_excl1_1_ = new TH1F("SelectedPhotons_Eta_excl1_1_","Photon #eta, 1 jet exclusive", 3000, -3, 3);
	SelectedPhotons_Phi_excl1_1_ = new TH1F("SelectedPhotons_Phi_excl1_1_","Photon #varphi, 1 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_27
	SelectedJets_Pt_excl1_1_ = new TH1F("SelectedJets_Pt_excl1_1_","Jet 1 p_{T}, 1 jet exclusive", 800, 0., 4000.);
	SelectedJets_E_excl1_1_ = new TH1F("SelectedJets_E_excl1_1_", "Jet 1 E, 1 jet exclusive", 800, 0., 4000.);
	SelectedJets_Eta_excl1_1_ = new TH1F("SelectedJets_Eta_excl1_1_","Jet 1 #eta, 1 jet exclusive", 3000, -3, 3);
	SelectedJets_Phi_excl1_1_ = new TH1F("SelectedJets_Phi_excl1_1_","Jet 1 #varphi, 1 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_28
	SelectedPhotons_Pt_excl2_1_ = new TH1F("SelectedPhotons_Pt_excl2_1_","Photon p_{T}, 2 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_E_excl2_1_ = new TH1F("SelectedPhotons_E_excl2_1_","Photon E, 2 jet exclusive", 800, 0., 4000.);
	SelectedPhotons_Eta_excl2_1_ = new TH1F("SelectedPhotons_Eta_excl2_1_","Photon #eta, 2 jet exclusive", 3000, -3, 3);
	SelectedPhotons_Phi_excl2_1_ = new TH1F("SelectedPhotons_Phi_excl2_1_","Photon #varphi, 2 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_29
	SelectedJets_Pt_excl2_1_ = new TH1F("SelectedJets_Pt_excl2_1_","Jet 1 p_{T}, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_E_excl2_1_ = new TH1F("SelectedJets_E_excl2_1_", "Jet 1 E, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_Eta_excl2_1_ = new TH1F("SelectedJets_Eta_excl2_1_","Jet 1 #eta, 2 jet exclusive", 3000, -3, 3);
	SelectedJets_Phi_excl2_1_ = new TH1F("SelectedJets_Phi_excl2_1_","Jet 1 #varphi, 2 jet exclusive", 1000, -3.1416, 3.1416);

	//plotsCompare_30
	SelectedJets_Pt_excl2_2_ = new TH1F("SelectedJets_Pt_excl2_2_","Jet 2 p_{T}, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_E_excl2_2_ = new TH1F("SelectedJets_E_excl2_2_", "Jet 2 E, 2 jet exclusive", 800, 0., 4000.);
	SelectedJets_Eta_excl2_2_ = new TH1F("SelectedJets_Eta_excl2_2_","Jet 2 #eta, 2 jet exclusive", 3000, -3, 3);
	SelectedJets_Phi_excl2_2_ = new TH1F("SelectedJets_Phi_excl2_2_","Jet 2 #varphi, 2 jet exclusive", 1000, -3.1416, 3.1416);

	SelectedJets_HT_excl2_ = new TH1F("SelectedJets_HT_excl2_","Selected Jets H_{T}, 2 jet exclusive", 400, 0, 4000);

	//plotsCompare_31
	SelectedJets_Pt_2_ = new TH1F("SelectedJets_Pt_2_","Jet 2 p_{T} ", 800, 0., 4000.);
	SelectedJets_E_2_ = new TH1F("SelectedJets_E_2_", "Jet 2 E", 800, 0., 4000.);
	SelectedJets_Eta_2_ = new TH1F("SelectedJets_Eta_2_","Jet 2 #eta ", 3000, -3, 3);
	SelectedJets_Phi_2_ = new TH1F("SelectedJets_Phi_2_","Jet 2 #varphi ", 1000, -3.1416, 3.1416);

	//plotsCompare_32
	DeltaPhi_photon1_jet1_N1_ = new TH1F("DeltaPhi_photon1_jet1_N1_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 2", 500, 0, 3.1416);
	DeltaR_photon1_jet2_N1_ = new TH1F("DeltaR_photon1_jet2_N1_","#DeltaR #gamma1-jet2 - N^{jets} #geq 2", 600, 0, 6);
	DeltaR_jet1_jet2_N1_ = new TH1F("DeltaR_jet1_jet2_N1_","#DeltaR jet1-jet2 - N^{jets} #geq 2", 600, 0, 6);
	DeltaEta_jet1_jet2_N1_ = new TH1F("DeltaEta_jet1_jet2_N1_","#Delta#eta jet1-jet2 - N^{jets} #geq 2", 500, 0, 5);
	DeltaPhi_jet1_jet2_N1_ = new TH1F("DeltaPhi_jet1_jet2_N1_","#Delta#varphi jet1-jet2 - N^{jets} #geq 2", 500, 0, 3.1416);

	//plotsCompare_33
	SelectedJets_Pt_3_ = new TH1F("SelectedJets_Pt_3_","Jet 3 p_{T} ", 800, 0., 4000.);
	SelectedJets_E_3_ = new TH1F("SelectedJets_E_3_", "Jet 3 E", 800, 0., 4000.);
	SelectedJets_Eta_3_ = new TH1F("SelectedJets_Eta_3_","Jet 3 #eta ", 3000, -3, 3);
	SelectedJets_Phi_3_ = new TH1F("SelectedJets_Phi_3_","Jet 3 #varphi ", 1000, -3.1416, 3.1416);

	//plotsCompare_34
	DeltaPhi_photon1_jet1_N2_ = new TH1F("DeltaPhi_photon1_jet1_N2_","#Delta#varphi #gamma1-jet1 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_photon1_jet2_N2_ = new TH1F("DeltaPhi_photon1_jet2_N2_","#Delta#varphi #gamma1-jet2 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_photon1_jet3_N2_ = new TH1F("DeltaPhi_photon1_jet3_N2_","#Delta#varphi #gamma1-jet3 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaR_photon1_jet3_N2_ = new TH1F("DeltaR_photon1_jet3_N2_","#DeltaR #gamma1-jet3 - N^{jets} #geq 3", 600, 0, 6);
	DeltaPhi_jet1_jet2_N2_ = new TH1F("DeltaPhi_jet1_jet2_N2_","#Delta#varphi jet1-jet2 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_jet1_jet3_N2_ = new TH1F("DeltaPhi_jet1_jet3_N2_","#Delta#varphi jet1-jet3 - N^{jets} #geq 3", 500, 0, 3.1416);
	DeltaPhi_jet2_jet3_N2_ = new TH1F("DeltaPhi_jet2_jet3_N2_","#Delta#varphi jet2-jet3 - N^{jets} #geq 3", 500, 0, 3.1416);
	
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

	bool plot_01 = false; // photon kinematics
	bool plot_02 = false; // photon Isolation
	bool plot_03 = false; // photon Isolation rho corrected
	bool plot_04 = false; // photon Isolation, 180 < p_T gamma < 200
	bool plot_05 = false; // photon Isolation rho corrected, 180 < p_T gamma < 200
	bool plot_06 = false; // photon Isolation, 200 < p_T gamma < 250
	bool plot_07 = false; // photon Isolation rho corrected, 200 < p_T gamma < 250
	bool plot_08 = false; // photon Isolation, 250 < p_T gamma < 300
	bool plot_09 = false; // photon Isolation rho corrected, 250 < p_T gamma < 300
	bool plot_10 = false; // photon Isolation, 300 < p_T gamma < 350
	bool plot_11 = false; // photon Isolation rho corrected, 300 < p_T gamma < 350
	bool plot_12 = false; // photon Isolation, 350 < p_T gamma < 400
	bool plot_13 = false; // photon Isolation rho corrected, 350 < p_T gamma < 400
	bool plot_14 = false; // photon Isolation rho corrected, p_T gamma > 400
	bool plot_15 = false; // photon Isolation rho corrected, p_T gamma > 400
	bool plot_16 = false; // photon Isolation cone 03 for Cic
	bool plot_17 = false; // photon Isolation cone 04 for Cic
	bool plot_18 = false; // photon ID
	bool plot_19 = false; // photon E_T-p_T cone 04
	bool plot_20 = false; // photon Isolation FPR
	bool plot_21 = false; // jets counting
	bool plot_22 = false; // Jet 1 kinematics
	bool plot_23 = false; // H_T
	bool plot_24 = false; // Angular variables (>= 1 jet)
	bool plot_25 = false; // Event shape variables
	bool plot_26 = false; // photon kinematics, 1 jet exclusive 
	bool plot_27 = false; // Jet 1 kinematics, 1 jet exclusive
	bool plot_28 = false; // photon kinematics, 2 jet exclusive 
	bool plot_29 = false; // Jet 1 kinematics, 2 jet exclusive
	bool plot_30 = false; // Jet 2 kinematics, 2 jet exclusive
	bool plot_31 = false; // Jet 2 kinematics
	bool plot_32 = false; // Angular variables (>=2 jets)
	bool plot_33 = false; // Jet 3 kinematics
	bool plot_34 = false; // Angular variables (>=3 jets)
	
	gStyle->SetOptStat(1111111);

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
		c_gen04->Divide(2,2);
		c_gen04->cd(1);
		photonPtGEN_excl1_->Draw();
		c_gen04->cd(2);
		photonPtGEN_excl2_->Draw();
		c_gen04->cd(3);
		photonPtGEN_N1_->Draw();
		c_gen04->cd(4);
		photonPtGEN_N2_->Draw();
	}


	if(plot_01){
		TCanvas *c01 = new TCanvas("c01", "photon kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c01->Divide(5,2);
		c01->cd(1);
		IDIsoPhotons_N_->Draw();
		c01->cd(2);
		SelectedPhotons_N_->Draw();
		c01->cd(3);
		Nvtx_->Draw();
		c01->cd(4);
		SelectedPhotons_Pt_1_->Draw();
		c01->cd(5);
		SelectedPhotons_E_1_->Draw();
		c01->cd(6);
		SelectedPhotons_Eta_1_->Draw();
		c01->cd(7);
		SelectedPhotons_Phi_1_->Draw();
		c01->cd(8);
		SelectedPhotons_Bit_1_->Draw();
		c01->cd(9);
		SelectedPhotons_TeP_SF_1_->Draw();	
		c01->cd(10);
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
		c03->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_->Draw();
		c03->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_->Draw();

	}

	if(plot_04){ 
		TCanvas *c04 = new TCanvas("c04", "photon Isolation, 180 < pT gamma < 200", 10, 10, 700, 700);
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
		TCanvas *c05 = new TCanvas("c05", "photon Isolation rho corrected, 180 < pT gamma < 200", 10, 10, 700, 700);
		gPad->SetLogy();
		c05->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin01_->Draw();
		c05->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin01_->Draw();		
	}

	if(plot_06){ 
		TCanvas *c06 = new TCanvas("c06", "photon Isolation, 200 < pT gamma < 250", 10, 10, 700, 700);
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
		TCanvas *c07 = new TCanvas("c07", "photon Isolation rho corrected, 200 < pT gamma < 250", 10, 10, 700, 700);
		gPad->SetLogy();
		c07->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin02_->Draw();
		c07->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin02_->Draw();		
	}

	if(plot_08){ 
		TCanvas *c08 = new TCanvas("c08", "photon Isolation, 250 < pT gamma < 300", 10, 10, 700, 700);
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
		TCanvas *c09 = new TCanvas("c09", "photon Isolation rho corrected, 250 < pT gamma < 300", 10, 10, 700, 700);
		gPad->SetLogy();
		c09->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin03_->Draw();
		c09->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin03_->Draw();		
	}

	if(plot_10){ 
		TCanvas *c10 = new TCanvas("c10", "photon Isolation, 300 < pT gamma < 350", 10, 10, 700, 700);
		gPad->SetLogy();
		c10->Divide(3,2);
		c10->cd(1);
		SelectedPhotons_id_sieie_1_bin03_->Draw();		
		c10->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin03_->Draw();
		c10->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin03_->Draw();
		c10->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin03_->Draw();
		c10->cd(5);
		SelectedPhotons_PfIso_1_bin03_->Draw();
	}

	if(plot_11){ 
		TCanvas *c11 = new TCanvas("c11", "photon Isolation rho corrected, 300 < pT gamma < 350", 10, 10, 700, 700);
		gPad->SetLogy();
		c11->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin04_->Draw();
		c11->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin04_->Draw();		
	}

	if(plot_12){ 
		TCanvas *c12 = new TCanvas("c12", "photon Isolation, 350 < pT gamma < 400", 10, 10, 700, 700);
		gPad->SetLogy();
		c12->Divide(3,2);
		c12->cd(1);
		SelectedPhotons_id_sieie_1_bin03_->Draw();		
		c12->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin03_->Draw();
		c12->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin03_->Draw();
		c12->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin03_->Draw();
		c12->cd(5);
		SelectedPhotons_PfIso_1_bin03_->Draw();
	}

	if(plot_13){ 
		TCanvas *c13 = new TCanvas("c13", "photon Isolation rho corrected, 350 < pT gamma < 400", 10, 10, 700, 700);
		gPad->SetLogy();
		c13->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin05_->Draw();
		c13->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin05_->Draw();		
	}

	if(plot_14){ 
		TCanvas *c14 = new TCanvas("c14", "photon Isolation, pT gamma > 400", 10, 10, 700, 700);
		gPad->SetLogy();
		c14->Divide(3,2);
		c14->cd(1);
		SelectedPhotons_id_sieie_1_bin04_->Draw();		
		c14->cd(2);
		SelectedPhotons_PfIsoChargedHad_1_bin04_->Draw();
		c14->cd(3);
		SelectedPhotons_PfIsoNeutralHad_1_bin04_->Draw();
		c14->cd(4);
		SelectedPhotons_PfIsoPhoton_1_bin04_->Draw();
		c14->cd(5);
		SelectedPhotons_PfIso_1_bin04_->Draw();
	}

	if(plot_15){ 
		TCanvas *c15 = new TCanvas("c15", "photon Isolation rho corrected, pT gamma > 400", 10, 10, 700, 700);
		gPad->SetLogy();
		c15->Divide(5,2);
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
		SelectedPhotons_PfIso_RhoCorr_forFit_1_bin06_->Draw();
		c15->cd(10);
		TH2F_SelectedPhotons_PfIso_RhoCorr_forFit_vs_sieie_1_bin06_->Draw();		
	}

	if(plot_16){
		TCanvas *c16 = new TCanvas("c16", "photon Isolation cone 03 for Cic", 10, 10, 700, 700);
		gPad->SetLogy();
		c16->Divide(2,2);
		c16->cd(1);
		SelectedPhotons_PfIsoPhotons03ForCic_1_->Draw();
		c16->cd(2);
		SelectedPhotons_PfIsoNeutrals03ForCic_1_->Draw();
		c16->cd(3);
		SelectedPhotons_PfIsoCharged03ForCicVtx0_1_->Draw();
		c16->cd(4);
		SelectedPhotons_PfIsoCharged03BadForCic_1_->Draw();
	}

	if(plot_17){
		TCanvas *c17 = new TCanvas("c17", "photon Isolation cone 04 for Cic", 10, 10, 700, 700);
		gPad->SetLogy();
		c17->Divide(2,2);
		c17->cd(1);
		SelectedPhotons_PfIsoPhotons04ForCic_1_->Draw();
		c17->cd(2);
		SelectedPhotons_PfIsoNeutrals04ForCic_1_->Draw();
		c17->cd(3);
		SelectedPhotons_PfIsoCharged04ForCicVtx0_1_->Draw();
		c17->cd(4);
		SelectedPhotons_PfIsoCharged04BadForCic_1_->Draw();
	}

	if(plot_18){
		TCanvas *c18 = new TCanvas("c18", "photon ID", 10, 10, 700, 700);
		gPad->SetLogy();
		c18->Divide(4,3);
		c18->cd(1);
		SelectedPhotons_id_sieie_1_->Draw();
		c18->cd(2);
		SelectedPhotons_id_sieip_1_->Draw();
		c18->cd(3);
		SelectedPhotons_id_etawidth_1_->Draw();
		c18->cd(4);
		SelectedPhotons_id_phiwidth_1_->Draw();
		c18->cd(5);
		SelectedPhotons_id_r9_1_->Draw();
		c18->cd(6);
		SelectedPhotons_id_lambdaRatio_1_->Draw();
		c18->cd(7);
		SelectedPhotons_id_s4Ratio_1_->Draw();
		c18->cd(8);
		SelectedPhotons_id_e25_1_->Draw();
		c18->cd(9);
		SelectedPhotons_id_sceta_1_->Draw();
		c18->cd(10);
		SelectedPhotons_id_ESEffSigmaRR_1_->Draw();
		c18->cd(11);
		SelectedPhotons_id_hadronicOverEm_1_->Draw();
		c18->cd(12);
		SelectedPhotons_id_hadronicOverEm2012_1_->Draw();
	}

	if(plot_19){
		TCanvas *c19 = new TCanvas("c19", "photon E_T-p_T cone 04", 10, 10, 700, 700);
		gPad->SetLogy();
		c19->Divide(3,2);
		c19->cd(1);
		SelectedPhotons_hcalTowerSumEtConeDR04_1_->Draw();
		c19->cd(2);
		SelectedPhotons_ecalRecHitSumEtConeDR04_1_->Draw();
		c19->cd(3);
		SelectedPhotons_nTrkSolidConeDR04_1_->Draw();
		c19->cd(4);
		SelectedPhotons_trkSumPtSolidConeDR04_1_->Draw();
		c19->cd(5);
		SelectedPhotons_nTrkHollowConeDR04_1_->Draw();
		c19->cd(6);
		SelectedPhotons_trkSumPtHollowConeDR04_1_->Draw();
	}

	if(plot_20){
		TCanvas *c20 = new TCanvas("c20", "photon Isolation FPR", 10, 10, 700, 700);
		gPad->SetLogy();
		c20->Divide(2,2);
		c20->cd(1);
		SelectedPhotons_IsoFPRCharged_1_->Draw();
		c20->cd(2);
		SelectedPhotons_IsoFPRNeutral_1_->Draw();
		c20->cd(3);
		SelectedPhotons_IsoFPRPhoton_1_->Draw();
		c20->cd(4);
		SelectedPhotons_IsoFPR_1_->Draw();
	}

	if(plot_21){
		TCanvas *c21 = new TCanvas("c21", "jets counting", 10, 10, 700, 700);
		gPad->SetLogy();
		c21->Divide(2,1);
		c21->cd(1);
		SelectedJetsALL_N_->Draw();
		c21->cd(2);
		SelectedJets_N_->Draw();
	}

	if(plot_22){
		TCanvas *c22 = new TCanvas("c22", "Jet 1 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c22->Divide(2,2);
		c22->cd(1);
		SelectedJets_Pt_1_->Draw();
		c22->cd(2);
		SelectedJets_E_1_->Draw();
		c22->cd(3);
		SelectedJets_Eta_1_->Draw();
		c22->cd(4);
		SelectedJets_Phi_1_->Draw();
	}

	if(plot_23){
		TCanvas *c23 = new TCanvas("c23", "H_T", 10, 10, 700, 700);
		gPad->SetLogy();
		c23->cd();
		SelectedJets_HT_->Draw();
	}

	if(plot_24){
		TCanvas *c24 = new TCanvas("c24", "Angular variables (>= 1 jet)", 10, 10, 700, 700);
		gPad->SetLogy();
		c24->Divide(3,1);
		c24->cd(1);
		DeltaR_photon1_jet1_N0_->Draw();
		c24->cd(2);
		DeltaEta_photon1_jet1_N0_->Draw();
		c24->cd(3);
		DeltaPhi_photon1_jet1_N0_->Draw();
	}

	if(plot_25){
		TCanvas *c25 = new TCanvas("c25", "Event shape variables", 10, 10, 700, 700);
		gPad->SetLogy();
		c25->Divide(4,2);
		c25->cd(1);
		thrust_N0_->Draw();
		c25->cd(2);
		broad_N0_->Draw();
		c25->cd(3);
		S3_N0_->Draw();
		c25->cd(4);
		S4_N0_->Draw();
		c25->cd(5);
		ln_thrust_N0_->Draw();
		c25->cd(6);
		ln_broad_N0_->Draw();
		c25->cd(7);
		ln_S3_N0_->Draw();
		c25->cd(8);
		ln_S4_N0_->Draw();
	}

	if(plot_26){
		TCanvas *c26 = new TCanvas("c26", "photon kinematics, 1 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c26->Divide(2,2);
		c26->cd(1);
		SelectedPhotons_Pt_excl1_1_->Draw();
		c26->cd(2);
		SelectedPhotons_E_excl1_1_->Draw();
		c26->cd(3);
		SelectedPhotons_Eta_excl1_1_->Draw();
		c26->cd(4);
		SelectedPhotons_Phi_excl1_1_->Draw();
	}

	if(plot_27){
		TCanvas *c27 = new TCanvas("c27", "Jet 1 kinematics, 1 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c27->Divide(2,2);
		c27->cd(1);
		SelectedJets_Pt_excl1_1_->Draw();
		c27->cd(2);
		SelectedJets_E_excl1_1_->Draw();
		c27->cd(3);
		SelectedJets_Eta_excl1_1_->Draw();
		c27->cd(4);
		SelectedJets_Phi_excl1_1_->Draw();
	}

	if(plot_28){
		TCanvas *c28 = new TCanvas("c28", "photon kinematics, 2 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c28->Divide(2,2);
		c28->cd(1);
		SelectedPhotons_Pt_excl2_1_->Draw();
		c28->cd(2);
		SelectedPhotons_E_excl2_1_->Draw();
		c28->cd(3);
		SelectedPhotons_Eta_excl2_1_->Draw();
		c28->cd(4);
		SelectedPhotons_Phi_excl2_1_->Draw();
	}

	if(plot_29){
		TCanvas *c29 = new TCanvas("c29", "Jet 1 kinematics, 2 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c29->Divide(2,2);
		c29->cd(1);
		SelectedJets_Pt_excl2_1_->Draw();
		c29->cd(2);
		SelectedJets_E_excl2_1_->Draw();
		c29->cd(3);
		SelectedJets_Eta_excl2_1_->Draw();
		c29->cd(4);
		SelectedJets_Phi_excl2_1_->Draw();
	}

	if(plot_30){
		TCanvas *c30 = new TCanvas("c30", "Jet 2 kinematics, 2 jet exclusive", 10, 10, 700, 700);
		gPad->SetLogy();
		c30->Divide(3,2);
		c30->cd(1);
		SelectedJets_Pt_excl2_2_->Draw();
		c30->cd(2);
		SelectedJets_E_excl2_2_->Draw();
		c30->cd(3);
		SelectedJets_Eta_excl2_2_->Draw();
		c30->cd(4);
		SelectedJets_Phi_excl2_2_->Draw();
		c30->cd(5);
		SelectedJets_HT_excl2_->Draw();
	}

	if(plot_31){
		TCanvas *c31 = new TCanvas("c31", "Jet 2 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c31->Divide(2,2);
		c31->cd(1);
		SelectedJets_Pt_2_->Draw();
		c31->cd(2);
		SelectedJets_E_2_->Draw();
		c31->cd(3);
		SelectedJets_Eta_2_->Draw();
		c31->cd(4);
		SelectedJets_Phi_2_->Draw();
	}

	if(plot_32){
		TCanvas *c32 = new TCanvas("c32", "Angular variables (>=2 jets)", 10, 10, 700, 700);
		gPad->SetLogy();
		c32->Divide(3,2);
		c32->cd(1);
		DeltaPhi_photon1_jet1_N1_->Draw();
		c32->cd(2);
		DeltaR_photon1_jet2_N1_->Draw();
		c32->cd(3);
		DeltaR_jet1_jet2_N1_->Draw();
		c32->cd(4);
		DeltaEta_jet1_jet2_N1_->Draw();
		c32->cd(5);
		DeltaPhi_jet1_jet2_N1_->Draw();
	}

	if(plot_33){
		TCanvas *c33 = new TCanvas("c33", "Jet 3 kinematics", 10, 10, 700, 700);
		gPad->SetLogy();
		c33->Divide(2,2);
		c33->cd(1);
		SelectedJets_Pt_3_->Draw();
		c33->cd(2);
		SelectedJets_E_3_->Draw();
		c33->cd(3);
		SelectedJets_Eta_3_->Draw();
		c33->cd(4);
		SelectedJets_Phi_3_->Draw();
	}

	if(plot_34){
		TCanvas *c34 = new TCanvas("c34", "Angular variables (>=3 jets)", 10, 10, 700, 700);
		gPad->SetLogy();
		c34->Divide(4,2);
		c34->cd(1);
		DeltaPhi_photon1_jet1_N2_->Draw();
		c34->cd(2);
		DeltaPhi_photon1_jet2_N2_->Draw();
		c34->cd(3);
		DeltaPhi_photon1_jet3_N2_->Draw();
		c34->cd(4);
		DeltaR_photon1_jet3_N2_->Draw();
		c34->cd(5);
		DeltaPhi_jet1_jet2_N2_->Draw();
		c34->cd(6);
		DeltaPhi_jet1_jet3_N2_->Draw();
		c34->cd(7);
		DeltaPhi_jet2_jet3_N2_->Draw();
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
	text << "nentries (with preselection in the PATZJetsExpress analyzer) = " << nentries_r << endl;
	text << "Number of selected events 0 (Iso at GEN level), unweighted = " << iSelected0 << endl;
	text << "Number of selected events 1 (trigger family 4), unweighted = " << iSelected1 << endl;	
	text << "Number of selected events 2 (ID+Iso+kin Photons: then, on the LEADING one)), unweighted = " << iSelected2 << endl;
	text << "Number of selected events 3 (kin Jets: cleaned vs. LEADING Photon), unweighted = " << iSelected3 << endl;
	text << "Number of selected events 4 (HT), unweighted = " << iSelected4 << endl;
	text << "Number of selected events (all selections), unweighted = " << iSelected4 << endl;
	text << "Number of selected events (all selections), weighted = " << iSelected4*weight_r << endl;
	text.close();
	cout << "...writing text file finished. " << endl;
	}
