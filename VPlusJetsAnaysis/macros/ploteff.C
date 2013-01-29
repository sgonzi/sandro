// 

#include <TROOT.h>
#include <TFile.h>
#include <string>
#include <stdio.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>


void ploteff(){


gStyle->SetFrameBorderMode(0);
gStyle->SetCanvasBorderMode(0);
gStyle->SetPadBorderMode(0);
gStyle->SetPadBorderSize(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetStatColor(0);
gStyle->SetOptTitle(0);   // eliminates the title
gStyle->SetDrawOption(0);



   TFile *file150=new TFile("GJetsHT100-200_gammahistos_0.root");                            
   TH1F *pt150gen=(TH1F*)file150->Get("ptPhotonGEN150_");
   TH1F *pt150rec=(TH1F*)file150->Get("ptPhotonREC150_");
   TH1F *ptphoton150=(TH1F*)file150->Get("ptPhoton_");
   cout << "MC selected events for HT 100-200 " << ptphoton150->Integral() << endl;  

   TH1F *efficiency150 = (TH1F*) pt150rec->Clone();
   efficiency150->Divide(pt150gen);


   TFile *file200=new TFile("GJetsHT200-inf_gammahistos_0.root");                            
   TH1F *pt200gen=(TH1F*)file200->Get("ptPhotonGEN200_");
   TH1F *pt200rec=(TH1F*)file200->Get("ptPhotonREC200_");
   TH1F *ptphoton200=(TH1F*)file200->Get("ptPhoton_");
   cout << "MC selected events for HT 200-inf " << ptphoton200->Integral() << endl;  

   TH1F *efficiency200 = (TH1F*) pt200rec->Clone();
   efficiency200->Divide(pt200gen);





   
   TCanvas *s1=new TCanvas("s1","  ",200,10,700,300);  
   s1->Divide(2,1);
   s1->cd(1);
   efficiency150->Draw();
   efficiency150->GetYaxis()->SetTitle(" Efficiency");
   efficiency150->GetXaxis()->SetTitle("p_{T}^{#gamma} (GeV)");
   efficiency150->SetMinimum(0.5);
   efficiency150->SetMaximum(1.0);
   TLegend *leg =new TLegend(0.1,0.1,0.6,0.3);
   TLegend *leg =new TLegend(0.2,0.2,0.8,0.4);
   leg->SetHeader("#gamma Efficiency for HT 100-200");
   leg->SetFillColor(10);
   leg->SetLineColor(10);
   leg->Draw();
   s1->cd(2);
   efficiency200->Draw();
   efficiency200->GetYaxis()->SetTitle(" Efficiency");
   efficiency200->GetXaxis()->SetTitle("p_{T}^{#gamma} (GeV)");
   efficiency200->SetMinimum(0.5);
   efficiency200->SetMaximum(1.0);
   TLegend *leg =new TLegend(0.2,0.2,0.8,0.4);
   leg->SetHeader("#gamma Efficiency for HT 200-inf");
   leg->SetFillColor(10);
   leg->SetLineColor(10);
   leg->Draw();


   gStyle->SetOptStat(0);
  


}
