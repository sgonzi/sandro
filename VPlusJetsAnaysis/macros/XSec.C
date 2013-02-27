// 
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


void XSec(){

  // Usage is: .L comparestack.C+
  //       ie: comparestack("ptPhoton_","P_{T}^{#gamma} [GeV]")

	Char_t name_GJets_HT_200To400[100];
	Char_t name_GJets_HT_400ToInf[100];
//	Char_t name_QCD_HT_100To250[100];
//	Char_t name_QCD_HT_250To500[100];
//	Char_t name_QCD_HT_500To1000[100];
//	Char_t name_QCD_HT_1000ToInf[100];
	Char_t name_QCD_Pt_20_30_EMEnriched[100];
	Char_t name_QCD_Pt_30_80_EMEnriched[100];
	Char_t name_QCD_Pt_80_170_EMEnriched[100];
	Char_t name_QCD_Pt_170_250_EMEnriched[100];
	Char_t name_QCD_Pt_250_350_EMEnriched[100];
	Char_t name_QCD_Pt_350_EMEnriched[100];
 
  Char_t titlehisto[100] = "accepted/XSec";


	sprintf(name_GJets_HT_200To400,"MC_GJets_HT-200To400_Summer12.root");
	sprintf(name_GJets_HT_400ToInf,"MC_GJets_HT-400ToInf_Summer12.root");
//	sprintf(name_QCD_HT_100To250,"MC_QCD_HT-100To250_Summer12.root");
//	sprintf(name_QCD_HT_250To500,"MC_QCD_HT-250To500_Summer12.root");
//	sprintf(name_QCD_HT_500To1000,"MC_QCD_HT-500To1000_Summer12.root");
//	sprintf(name_QCD_HT_1000ToInf,"MC_QCD_HT-1000ToInf_Summer12.root");
	sprintf(name_QCD_Pt_20_30_EMEnriched,"MC_QCD_Pt_20_30_EMEnriched_Summer12.root");
	sprintf(name_QCD_Pt_30_80_EMEnriched,"MC_QCD_Pt_30_80_EMEnriched_Summer12.root");	
	sprintf(name_QCD_Pt_80_170_EMEnriched,"MC_QCD_Pt_80_170_EMEnriched_Summer12.root");
	sprintf(name_QCD_Pt_170_250_EMEnriched,"MC_QCD_Pt_170_250_EMEnriched_Summer12.root");
	sprintf(name_QCD_Pt_250_350_EMEnriched,"MC_QCD_Pt_250_350_EMEnriched_Summer12.root");
	sprintf(name_QCD_Pt_350_EMEnriched,"MC_QCD_Pt_350_EMEnriched_Summer12.root");	
	

	TFile *file_GJets_HT_200To400 = new TFile(name_GJets_HT_200To400);
	TFile *file_GJets_HT_400ToInf = new TFile(name_GJets_HT_400ToInf); 
//	TFile *file_QCD_HT_100To250   = new TFile(name_QCD_HT_100To250);  
//	TFile *file_QCD_HT_250To500   = new TFile(name_QCD_HT_250To500);   
//	TFile *file_QCD_HT_500To1000  = new TFile(name_QCD_HT_500To1000); 
//	TFile *file_QCD_HT_1000ToInf  = new TFile(name_QCD_HT_1000ToInf); 
	TFile *file_QCD_Pt_20_30_EMEnriched  = new TFile(name_QCD_Pt_20_30_EMEnriched); 
	TFile *file_QCD_Pt_30_80_EMEnriched  = new TFile(name_QCD_Pt_30_80_EMEnriched); 
	TFile *file_QCD_Pt_80_170_EMEnriched  = new TFile(name_QCD_Pt_80_170_EMEnriched); 
	TFile *file_QCD_Pt_170_250_EMEnriched  = new TFile(name_QCD_Pt_170_250_EMEnriched); 
	TFile *file_QCD_Pt_250_350_EMEnriched  = new TFile(name_QCD_Pt_250_350_EMEnriched); 
	TFile *file_QCD_Pt_350_EMEnriched  = new TFile(name_QCD_Pt_350_EMEnriched); 

	TH1F *histo_GJets_HT_200To400 = (TH1F*)file_GJets_HT_200To400->Get(titlehisto);
	TH1F *histo_GJets_HT_400ToInf = (TH1F*)file_GJets_HT_400ToInf->Get(titlehisto);
//	TH1F *histo_QCD_HT_100To250   = (TH1F*)file_QCD_HT_100To250->Get(titlehisto);
//	TH1F *histo_QCD_HT_250To500   = (TH1F*)file_QCD_HT_250To500->Get(titlehisto);
//	TH1F *histo_QCD_HT_500To1000  = (TH1F*)file_QCD_HT_500To1000->Get(titlehisto);
//	TH1F *histo_QCD_HT_1000ToInf  = (TH1F*)file_QCD_HT_1000ToInf->Get(titlehisto);
	TH1F *histo_QCD_Pt_20_30_EMEnriched    = (TH1F*)file_QCD_Pt_20_30_EMEnriched->Get(titlehisto);
	TH1F *histo_QCD_Pt_30_80_EMEnriched    = (TH1F*)file_QCD_Pt_30_80_EMEnriched->Get(titlehisto);
	TH1F *histo_QCD_Pt_80_170_EMEnriched   = (TH1F*)file_QCD_Pt_80_170_EMEnriched->Get(titlehisto);
	TH1F *histo_QCD_Pt_170_250_EMEnriched  = (TH1F*)file_QCD_Pt_170_250_EMEnriched->Get(titlehisto);
	TH1F *histo_QCD_Pt_250_350_EMEnriched  = (TH1F*)file_QCD_Pt_250_350_EMEnriched->Get(titlehisto);
	TH1F *histo_QCD_Pt_350_EMEnriched      = (TH1F*)file_QCD_Pt_350_EMEnriched->Get(titlehisto);
	

  double XSec_GJets_HT_200To400, XSec_GJets_HT_400ToInf, /* XSec_QCD_HT_100To250, XSec_QCD_HT_250To500, XSec_QCD_HT_500To1000, XSec_QCD_HT_1000ToInf,*/ XSec_QCD_Pt_20_30_EMEnriched, XSec_QCD_Pt_30_80_EMEnriched, XSec_QCD_Pt_80_170_EMEnriched, XSec_QCD_Pt_170_250_EMEnriched, XSec_QCD_Pt_250_350_EMEnriched, XSec_QCD_Pt_350_EMEnriched;
  
//  XSec_GJets_HT_200To400 = Ghisto1->GetBinContent(1);
  XSec_GJets_HT_200To400 = histo_GJets_HT_200To400->GetBinContent(1)/histo_GJets_HT_200To400->GetBinContent(2);
  XSec_GJets_HT_400ToInf = histo_GJets_HT_400ToInf->GetBinContent(1)/histo_GJets_HT_400ToInf->GetBinContent(2);  
//  XSec_QCD_HT_100To250   = histo_QCD_HT_100To250->GetBinContent(1)/histo_QCD_HT_100To250->GetBinContent(2);
//  XSec_QCD_HT_250To500  = histo_QCD_HT_250To500->GetBinContent(1)/histo_QCD_HT_250To500->GetBinContent(2);
//  XSec_QCD_HT_500To1000  = histo_QCD_HT_500To1000->GetBinContent(1)/histo_QCD_HT_500To1000->GetBinContent(2);
//  XSec_QCD_HT_1000ToInf  = histo_QCD_HT_1000ToInf->GetBinContent(1)/histo_QCD_HT_1000ToInf->GetBinContent(2);
  XSec_QCD_Pt_20_30_EMEnriched  = histo_QCD_Pt_20_30_EMEnriched->GetBinContent(1)/histo_QCD_Pt_20_30_EMEnriched->GetBinContent(2);
  XSec_QCD_Pt_30_80_EMEnriched  = histo_QCD_Pt_30_80_EMEnriched->GetBinContent(1)/histo_QCD_Pt_30_80_EMEnriched->GetBinContent(2);
  XSec_QCD_Pt_80_170_EMEnriched  = histo_QCD_Pt_80_170_EMEnriched->GetBinContent(1)/histo_QCD_Pt_80_170_EMEnriched->GetBinContent(2);
  XSec_QCD_Pt_170_250_EMEnriched  = histo_QCD_Pt_170_250_EMEnriched->GetBinContent(1)/histo_QCD_Pt_170_250_EMEnriched->GetBinContent(2);
  XSec_QCD_Pt_250_350_EMEnriched  = histo_QCD_Pt_250_350_EMEnriched->GetBinContent(1)/histo_QCD_Pt_250_350_EMEnriched->GetBinContent(2);
  XSec_QCD_Pt_350_EMEnriched  = histo_QCD_Pt_350_EMEnriched->GetBinContent(1)/histo_QCD_Pt_350_EMEnriched->GetBinContent(2);

    
	cout << "XSec GJets_HT-200To400 = " << XSec_GJets_HT_200To400 << " /pb" << endl;  
	cout << "XSec GJets_HT-400ToInf = " << XSec_GJets_HT_400ToInf << " /pb" << endl;  
//	cout << "XSec QCD_HT-100To250 = " << XSec_QCD_HT_100To250 << " /pb" << endl;  
//	cout << "XSec QCD_HT-250To500 = " << XSec_QCD_HT_250To500 << " /pb" << endl;  	
//	cout << "XSec QCD_HT-500To1000 = " << XSec_QCD_HT_500To1000 << " /pb" << endl;  
//	cout << "XSec QCD_HT-1000ToInf = " << XSec_QCD_HT_1000ToInf << " /pb" << endl;  
	cout << "XSec QCD_Pt_20_30_EMEnriched = " << XSec_QCD_Pt_20_30_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_30_80_EMEnriched = " << XSec_QCD_Pt_30_80_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_80_170_EMEnriched = " << XSec_QCD_Pt_80_170_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_170_250_EMEnriched = " << XSec_QCD_Pt_170_250_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_250_350_EMEnriched = " << XSec_QCD_Pt_250_350_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_350_EMEnriched = " << XSec_QCD_Pt_350_EMEnriched << " /pb" << endl;  				

}
