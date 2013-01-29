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


void comparestack(char* titleh, char* namevariable){

  // Usage is: .L comparestack.C+
  //       ie: comparestack("ptPhoton_","P_{T}^{#gamma} [GeV]")

	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadBorderSize(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetOptTitle(0);   // eliminates the title
	gStyle->SetDrawOption(0);
	gStyle->SetOptStat(0);

	Char_t dataname[100];
	Char_t Gname1[100];
	Char_t Gname2[100];
//	Char_t QCDname1[100];
//	Char_t QCDname2[100];
	Char_t QCDname3[100];
//	Char_t QCDname4[100];

	Int_t itype = 0; //dummy


	sprintf(dataname,"data_all_photons_gammahistos_%d.root",itype);
	cout << "data file is_ " << dataname << endl;
	sprintf(Gname1,"mc_GJets_HT-200To400_gammahistos_%d.root",itype);
	cout << "GJets file 1 is: " << Gname1 << endl;
	sprintf(Gname2,"mc_GJets_HT-400ToInf_gammahistos_%d.root",itype);
	cout << "GJets file 2 is: " << Gname2 << endl;
//	sprintf(QCDname1,"mc_QCD_HT-100To250_gammahistos_%d.root",itype);
//	cout << "QCD file 1 is: " << QCDname1 << endl;
//	sprintf(QCDname2,"mc_QCD_HT-250To500_gammahistos_%d.root",itype);
//	cout << "QCD file 2 is: " << QCDname2 << endl;
	sprintf(QCDname3,"mc_QCD_HT-500To1000_gammahistos_%d.root",itype);
	cout << "QCD file 3 is: " << QCDname3 << endl;
//	sprintf(QCDname4,"mc_QCD_HT-1000ToInf_gammahistos_%d.root",itype);
//	cout << "QCD file 4 is: " << QCDname4 << endl;


	TFile *datafile=new TFile(dataname);  
	TFile *Gfile1  =new TFile(Gname1);
	TFile *Gfile2  =new TFile(Gname2); 
//	TFile *QCDfile1  =new TFile(QCDname1);  
//	TFile *QCDfile2  =new TFile(QCDname2);   
	TFile *QCDfile3  =new TFile(QCDname3); 
//	TFile *QCDfile4  =new TFile(QCDname4); 

	Char_t titlehisto[100],titlecanvas[100];

	strcpy(titlehisto,titleh);
	cout << "Analyzing Histogram " << titlehisto << endl;


	TH1F *Datahisto=(TH1F*)datafile->Get(titlehisto);
	cout << "Data entries " << Datahisto->Integral() << endl;  

	TH1F *Ghisto1=(TH1F*)Gfile1->Get(titlehisto);
	cout << "GJets file 1 entries " << Ghisto1->Integral() << endl;
	Ghisto1->SetLineColor(1);
	Ghisto1->SetFillColor(5);  //for colors comment out Sumw2 in code

	TH1F *Ghisto2=(TH1F*)Gfile2->Get(titlehisto);
	cout << "GJets file 2 entries " << Ghisto2->Integral() << endl;
	Ghisto1->Add(Ghisto2);  

/*	TH1F *QCDhisto1=(TH1F*)QCDfile1->Get(titlehisto);
	cout << "QCD file 1 entries " << QCDhisto1->Integral() << endl;  
	QCDhisto1->SetLineColor(1);
	QCDhisto1->SetFillColor(kMagenta+2);

	TH1F *QCDhisto2=(TH1F*)QCDfile2->Get(titlehisto);
	cout << "QCD file 2 entries " << QCDhisto2->Integral() << endl;  
*/
	TH1F *QCDhisto3=(TH1F*)QCDfile3->Get(titlehisto);
	cout << "QCD file 3 entries " << QCDhisto3->Integral() << endl;
/*
	TH1F *QCDhisto4=(TH1F*)QCDfile4->Get(titlehisto);
	cout << "QCD file 4 entries " << QCDhisto4->Integral() << endl;

	QCDhisto1->Add(QCDhisto2);
	QCDhisto1->Add(QCDhisto3);  
	QCDhisto1->Add(QCDhisto4;  
*/
	QCDhisto3->SetLineColor(1);
	QCDhisto3->SetFillColor(kMagenta+2);

	cout << "GJets total entries " << Ghisto1->Integral() << endl;  
//	cout << "QCD total entries " << QCDhisto1->Integral() << endl;  
	cout << "QCD total entries " << QCDhisto3->Integral() << endl;  

  TCanvas *c1=new TCanvas(titlehisto,titlehisto,200,10,700,700);  
  // c1->Divide(1,2);

   
   // c1->cd(1);
   // Ghisto1->Draw();
   // gPad->SetLogy();
   // c1->cd(2);
   // QCDhisto1->Draw();
   // gPad->SetLogy();

	THStack *MCtotal= new THStack();
/*
	MCtotal->Add(QCDhisto1);
	MCtotal->Add(Ghisto1);
*/
	MCtotal->Add(QCDhisto3);
	MCtotal->Add(Ghisto1);


// c1->cd(3);
// MCtotal->Draw("");
// gPad->SetLogy();

	c1->cd(1);
	Datahisto->SetMarkerStyle(20);
	Datahisto->SetMinimum(0.1);
	Datahisto->Draw("E");
	MCtotal->Draw("SAME");
	Datahisto->Draw("ESAME");
	gPad->SetLogy();
	Datahisto->GetXaxis()->SetTitle(namevariable);
	Datahisto->GetXaxis()->SetTitleSize(0.05);
	Datahisto->GetYaxis()->SetTitle("Events");
	Datahisto->GetYaxis()->SetTitleOffset(0.8);
	Datahisto->GetYaxis()->SetTitleSize(0.05);
	Datahisto->GetYaxis()->SetLabelSize(0.03);

	TLegend *leg =new TLegend(0.6,0.6,0.8,0.8);
	leg->AddEntry(Datahisto,"Data 510.274 pb^{1-}","pL");
	leg->AddEntry(Ghisto1,"#gamma + jets","f");
//	leg->AddEntry(QCDhisto1,"QCD","f");
	leg->AddEntry(QCDhisto3,"QCD","f");
	leg->SetFillColor(10);
	leg->SetLineColor(10);
	leg->Draw();

   //gStyle->SetOptStat(0);
  

}
