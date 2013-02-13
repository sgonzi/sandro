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


	Char_t Gname1[100];
	Char_t Gname2[100];
	Char_t QCDname1[100];
//	Char_t QCDname2[100];
	Char_t QCDname3[100];
	Char_t QCDname4[100];

  Char_t titlehisto[100] = "accepted/XSec";


	sprintf(Gname1,"MC_GJets_HT-200To400_Summer12.root");
	sprintf(Gname2,"MC_GJets_HT-400ToInf_Summer12.root");
	sprintf(QCDname1,"MC_QCD_HT-100To250_Summer12.root");
//	sprintf(QCDname2,"MC_QCD_HT-250To500_Summer12.root");
	sprintf(QCDname3,"MC_QCD_HT-500To1000_Summer12.root");
	sprintf(QCDname4,"MC_QCD_HT-1000ToInf_Summer12.root");


	TFile *Gfile1  =new TFile(Gname1);
	TFile *Gfile2  =new TFile(Gname2); 
	TFile *QCDfile1  =new TFile(QCDname1);  
//	TFile *QCDfile2  =new TFile(QCDname2);   
	TFile *QCDfile3  =new TFile(QCDname3); 
	TFile *QCDfile4  =new TFile(QCDname4); 

	TH1F *Ghisto1=(TH1F*)Gfile1->Get(titlehisto);
	TH1F *Ghisto2=(TH1F*)Gfile2->Get(titlehisto);
	TH1F *QCDhisto1=(TH1F*)QCDfile1->Get(titlehisto);
//	TH1F *QCDhisto2=(TH1F*)QCDfile2->Get(titlehisto);
	TH1F *QCDhisto3=(TH1F*)QCDfile3->Get(titlehisto);
	TH1F *QCDhisto4=(TH1F*)QCDfile4->Get(titlehisto);

  double XSec_GJets_HT_200To400, XSec_GJets_HT_400ToInf, XSec_QCD_HT_100To250, /*XSec_QCD_HT_250To500,*/ XSec_QCD_HT_500To1000, XSec_QCD_HT_1000ToInf;
//  XSec_GJets_HT_200To400 = Ghisto1->GetBinContent(1);
  XSec_GJets_HT_200To400 = Ghisto1->GetBinContent(1)/Ghisto1->GetBinContent(2);
  XSec_GJets_HT_400ToInf = Ghisto2->GetBinContent(1)/Ghisto2->GetBinContent(2);  
  XSec_QCD_HT_100To250  = QCDhisto1->GetBinContent(1)/QCDhisto1->GetBinContent(2);
//  XSec_QCD_HT_250To500  = QCDhisto2->GetBinContent(1)/QCDhisto3->GetBinContent(2);
  XSec_QCD_HT_500To1000 = QCDhisto3->GetBinContent(1)/QCDhisto3->GetBinContent(2);
  XSec_QCD_HT_1000ToInf = QCDhisto4->GetBinContent(1)/QCDhisto4->GetBinContent(2);
  
	cout << "XSec GJets_HT-200To400 = " << XSec_GJets_HT_200To400 << " /pb" << endl;  
	cout << "XSec GJets_HT-400ToInf = " << XSec_GJets_HT_400ToInf << " /pb" << endl;  
	cout << "XSec QCD_HT-100To250 = " << XSec_QCD_HT_100To250 << " /pb" << endl;  
//	cout << "XSec QCD_HT-250To500 = " << XSec_QCD_HT_250To500 << " /pb" << endl;  	
	cout << "XSec QCD_HT-500To1000 = " << XSec_QCD_HT_500To1000 << " /pb" << endl;  
	cout << "XSec QCD_HT-1000ToInf = " << XSec_QCD_HT_1000ToInf << " /pb" << endl;  

}
