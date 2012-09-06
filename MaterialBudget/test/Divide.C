#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "TH1D.h"
#include "TVectorD.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "THStack.h"
#include "TDirectory.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TPad.h"
//#include "TAttFill.h"

using namespace std;


void Divide(){
        
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);


// For the Pad:
  gStyle->SetPadBorderMode(0);
  // gStyle->SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);

// For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);

//------------------ x_vs_eta

	//Modified
	TFile *Modified_file_x_vs_eta = TFile::Open("Tracker_SubDetectors_x_vs_eta.root");
        
	//Original
	TFile *Original_file_x_vs_eta = TFile::Open("../0_Original_Figures/Tracker_SubDetectors_x_vs_eta.root");
        
	//Output
	string out_x_vs_eta = "Divide_2_PixelBarrelConn1_and_PixelBarrelConn2_x_vs_eta";        
	string outputroot_x_vs_eta = out_x_vs_eta;
	outputroot_x_vs_eta += ".root";
	string outputpdf_x_vs_eta = out_x_vs_eta;
        outputpdf_x_vs_eta += ".pdf";
	//string outputpng_x_vs_eta = out_x_vs_eta;
        //outputpng_x_vs_eta += ".png";
	//string outputC_x_vs_eta = out_x_vs_eta;
        //outputC_x_vs_eta_x_vs_eta += ".C";
	TFile* outplots_x_vs_eta = new TFile(outputroot_x_vs_eta.c_str(), "RECREATE");	
   
        //TCanvas
        TCanvas *Modified_c1_x_vs_eta = (TCanvas*) Modified_file_x_vs_eta->Get("can_SubDetectors");
        TCanvas *Original_c1_x_vs_eta = (TCanvas*) Original_file_x_vs_eta->Get("can_SubDetectors");

        //THStack 
        THStack *Modified_THStack_x_vs_eta = (THStack*) Modified_c1_x_vs_eta->GetPrimitive("stack_x0");
        THStack *Original_THStack_x_vs_eta = (THStack*) Original_c1_x_vs_eta->GetPrimitive("stack_x0");
        
        //Clear the Source Canvas
        Modified_c1_x_vs_eta->Clear();
        Original_c1_x_vs_eta->Clear();

        //Create new Canva
        TCanvas *Divide_c1_x_vs_eta = new TCanvas("Divide_c1", "Divide_c1", 800, 800);
        Divide_c1_x_vs_eta->Range(0,0,25,25);
        Divide_c1_x_vs_eta->SetLeftMargin(0.160);
        Divide_c1_x_vs_eta->Draw();



        //Recall the TH1D (Modified Geometry)
        TH1D *Modified_THStack_5_x_vs_eta = (TH1D*) Modified_THStack_x_vs_eta->GetStack()->At(5);
//        TH1D *Modified_THStack_4_x_vs_eta = (TH1D*) Modified_THStack_x_vs_eta->GetStack()->At(4);
//        TH1D *Modified_THStack_3_x_vs_eta = (TH1D*) Modified_THStack_x_vs_eta->GetStack()->At(3);
//        TH1D *Modified_THStack_2_x_vs_eta = (TH1D*) Modified_THStack_x_vs_eta->GetStack()->At(2);
//        TH1D *Modified_THStack_1_x_vs_eta = (TH1D*) Modified_THStack_x_vs_eta->GetStack()->At(1);
//        TH1D *Modified_THStack_0_x_vs_eta = (TH1D*) Modified_THStack_x_vs_eta->GetStack()->At(0);

        //Recall the TH1D (Original Geometry)
        TH1D *Original_THStack_5_x_vs_eta = (TH1D*) Original_THStack_x_vs_eta->GetStack()->At(5);
//        TH1D *Original_THStack_4_x_vs_eta = (TH1D*) Original_THStack_x_vs_eta->GetStack()->At(4);
//        TH1D *Original_THStack_3_x_vs_eta = (TH1D*) Original_THStack_x_vs_eta->GetStack()->At(3);
//        TH1D *Original_THStack_2_x_vs_eta = (TH1D*) Original_THStack_x_vs_eta->GetStack()->At(2);
//        TH1D *Original_THStack_1_x_vs_eta = (TH1D*) Original_THStack_x_vs_eta->GetStack()->At(1);
//        TH1D *Original_THStack_0_x_vs_eta = (TH1D*) Original_THStack_x_vs_eta->GetStack()->At(0);

        //Divide et impera
        Modified_THStack_5_x_vs_eta->Divide(Original_THStack_5_x_vs_eta);
//        Modified_THStack_4_x_vs_eta->Divide(Original_THStack_4_x_vs_eta);
//        Modified_THStack_3_x_vs_eta->Divide(Original_THStack_3_x_vs_eta);
//        Modified_THStack_2_x_vs_eta->Divide(Original_THStack_2_x_vs_eta);
//        Modified_THStack_1_x_vs_eta->Divide(Original_THStack_1_x_vs_eta);
//        Modified_THStack_0_x_vs_eta->Divide(Original_THStack_0_x_vs_eta);

        //SetFillColor 0
        Modified_THStack_5_x_vs_eta->SetFillColor(0);
//        Modified_THStack_4_x_vs_eta->SetFillColor(0);
//        Modified_THStack_3_x_vs_eta->SetFillColor(0);
//        Modified_THStack_2_x_vs_eta->SetFillColor(0);
//        Modified_THStack_1_x_vs_eta->SetFillColor(0);
//        Modified_THStack_0_x_vs_eta->SetFillColor(0);

        //Colors
//        int k5 = kGray;
//        int k4 = kOrange-2;
//        int k3 = kOrange+10;
//        int k2 = kMagenta-2;
//        int k1 = kAzure-5;
//        int k0 = kGray+2;

        //SetLineColor 
//        Modified_THStack_5->SetLineColor(k5);
//        Modified_THStack_4->SetLineColor(k4);
//        Modified_THStack_3->SetLineColor(k3);
//        Modified_THStack_2->SetLineColor(k2);
//        Modified_THStack_1->SetLineColor(k1);
//        Modified_THStack_0->SetLineColor(k0);

        //SetLineWidth 2 
        Modified_THStack_5_x_vs_eta->SetLineWidth(2);
//        Modified_THStack_4_x_vs_eta->SetLineWidth(2);
//        Modified_THStack_3_x_vs_eta->SetLineWidth(2);
//        Modified_THStack_2_x_vs_eta->SetLineWidth(2);
//        Modified_THStack_1_x_vs_eta->SetLineWidth(2);
//        Modified_THStack_0_x_vs_eta->SetLineWidth(2);

//        Modified_THStack_0_x_vs_eta->Draw("histo");
//        Modified_THStack_1_x_vs_eta->Draw("histo same");
//        Modified_THStack_2_x_vs_eta->Draw("histo same");
//        Modified_THStack_3_x_vs_eta->Draw("histo same");
//        Modified_THStack_4_x_vs_eta->Draw("histo same");
        Modified_THStack_5_x_vs_eta->Draw("histo");

        Modified_THStack_5_x_vs_eta->SetTitle("t/X_{0} vs. #eta: Modified/Original geometry");
        Modified_THStack_5_x_vs_eta->SetYTitle("ratio");
        Modified_THStack_5_x_vs_eta->GetYaxis()->SetTitleOffset(2.1);
        Modified_THStack_5_x_vs_eta->GetXaxis()->SetRangeUser(-4, 4);
//      Modified_THStack_5_x_vs_eta.GetYaxis()->SetRangeUser(0.999, 1.008);

        // Legenda
//       TLegend *theLegend_Divide = new TLegend(0.18,0.8,0.98,0.92); //$$ per inserire la TLegend al posto giusto
//       theLegend_Divide->SetNColumns(3); //$$
//       theLegend_Divide->SetFillColor(0); //$$
//       theLegend_Divide->SetFillStyle(0); //$$
//       theLegend_Divide->SetBorderSize(0); //$$
//       theLegend_Divide->AddEntry(Modified_THStack_5,  "Support Tube",  "f");
//       theLegend_Divide->AddEntry(Modified_THStack_3,      "TOB",      "f");
//       theLegend_Divide->AddEntry(Modified_THStack_1,    "Pixel",    "f");
//       theLegend_Divide->AddEntry(Modified_THStack_4,      "TEC",      "f");
//       theLegend_Divide->AddEntry(Modified_THStack_2,       "TIB and TID",  "f");
//       theLegend_Divide->AddEntry(Modified_THStack_0, "Beam Pipe","f");
//       theLegend_Divide->Draw();
  //
         Divide_c1_x_vs_eta->SaveAs((outputpdf_x_vs_eta.c_str()));
         // Divide_c1_x_vs_eta->SaveAs((outputpng_x_vs_eta.c_str()));
         Divide_c1_x_vs_eta->SaveAs((outputroot_x_vs_eta.c_str()));
         // Divide_c1_x_vs_eta->SaveAs((outputC_x_vs_eta.c_str()));

  outplots_x_vs_eta->cd();
  outplots_x_vs_eta->Write();
  outplots_x_vs_eta->Close();

//------------------ l_vs_eta

	//Modified
	TFile *Modified_file_l_vs_eta = TFile::Open("Tracker_SubDetectors_l_vs_eta.root");
        
	//Original
	TFile *Original_file_l_vs_eta = TFile::Open("../0_Original_Figures/Tracker_SubDetectors_l_vs_eta.root");
        
	//Output
	string out_l_vs_eta = "Divide_2_PixelBarrelConn1_and_PixelBarrelConn2_l_vs_eta";        
	string outputroot_l_vs_eta = out_l_vs_eta;
	outputroot_l_vs_eta += ".root";
	string outputpdf_l_vs_eta = out_l_vs_eta;
        outputpdf_l_vs_eta += ".pdf";
	//string outputpng_l_vs_eta = out_l_vs_eta;
        //outputpng_l_vs_eta += ".png";
	//string outputC_l_vs_eta = out_l_vs_eta;
        //outputC_l_vs_eta_l_vs_eta += ".C";
	TFile* outplots_l_vs_eta = new TFile(outputroot_l_vs_eta.c_str(), "RECREATE");	
   
        //TCanvas
        TCanvas *Modified_c1_l_vs_eta = (TCanvas*) Modified_file_l_vs_eta->Get("can_SubDetectors");
        TCanvas *Original_c1_l_vs_eta = (TCanvas*) Original_file_l_vs_eta->Get("can_SubDetectors");

        //THStack 
        THStack *Modified_THStack_l_vs_eta = (THStack*) Modified_c1_l_vs_eta->GetPrimitive("stack_x0");
        THStack *Original_THStack_l_vs_eta = (THStack*) Original_c1_l_vs_eta->GetPrimitive("stack_x0");
        
        //Clear the Source Canvas
        Modified_c1_l_vs_eta->Clear();
        Original_c1_l_vs_eta->Clear();

        //Create new Canva
        TCanvas *Divide_c1_l_vs_eta = new TCanvas("Divide_c1", "Divide_c1", 800, 800);
        Divide_c1_l_vs_eta->Range(0,0,25,25);
        Divide_c1_l_vs_eta->SetLeftMargin(0.160);
        Divide_c1_l_vs_eta->Draw();



        //Recall the TH1D (Modified Geometry)
        TH1D *Modified_THStack_5_l_vs_eta = (TH1D*) Modified_THStack_l_vs_eta->GetStack()->At(5);
//        TH1D *Modified_THStack_4_l_vs_eta = (TH1D*) Modified_THStack_l_vs_eta->GetStack()->At(4);
//        TH1D *Modified_THStack_3_l_vs_eta = (TH1D*) Modified_THStack_l_vs_eta->GetStack()->At(3);
//        TH1D *Modified_THStack_2_l_vs_eta = (TH1D*) Modified_THStack_l_vs_eta->GetStack()->At(2);
//        TH1D *Modified_THStack_1_l_vs_eta = (TH1D*) Modified_THStack_l_vs_eta->GetStack()->At(1);
//        TH1D *Modified_THStack_0_l_vs_eta = (TH1D*) Modified_THStack_l_vs_eta->GetStack()->At(0);

        //Recall the TH1D (Original Geometry)
        TH1D *Original_THStack_5_l_vs_eta = (TH1D*) Original_THStack_l_vs_eta->GetStack()->At(5);
//        TH1D *Original_THStack_4_l_vs_eta = (TH1D*) Original_THStack_l_vs_eta->GetStack()->At(4);
//        TH1D *Original_THStack_3_l_vs_eta = (TH1D*) Original_THStack_l_vs_eta->GetStack()->At(3);
//        TH1D *Original_THStack_2_l_vs_eta = (TH1D*) Original_THStack_l_vs_eta->GetStack()->At(2);
//        TH1D *Original_THStack_1_l_vs_eta = (TH1D*) Original_THStack_l_vs_eta->GetStack()->At(1);
//        TH1D *Original_THStack_0_l_vs_eta = (TH1D*) Original_THStack_l_vs_eta->GetStack()->At(0);

        //Divide et impera
        Modified_THStack_5_l_vs_eta->Divide(Original_THStack_5_l_vs_eta);
//        Modified_THStack_4_l_vs_eta->Divide(Original_THStack_4_l_vs_eta);
//        Modified_THStack_3_l_vs_eta->Divide(Original_THStack_3_l_vs_eta);
//        Modified_THStack_2_l_vs_eta->Divide(Original_THStack_2_l_vs_eta);
//        Modified_THStack_1_l_vs_eta->Divide(Original_THStack_1_l_vs_eta);
//        Modified_THStack_0_l_vs_eta->Divide(Original_THStack_0_l_vs_eta);

        //SetFillColor 0
        Modified_THStack_5_l_vs_eta->SetFillColor(0);
//        Modified_THStack_4_l_vs_eta->SetFillColor(0);
//        Modified_THStack_3_l_vs_eta->SetFillColor(0);
//        Modified_THStack_2_l_vs_eta->SetFillColor(0);
//        Modified_THStack_1_l_vs_eta->SetFillColor(0);
//        Modified_THStack_0_l_vs_eta->SetFillColor(0);

        //Colors
//        int k5 = kGray;
//        int k4 = kOrange-2;
//        int k3 = kOrange+10;
//        int k2 = kMagenta-2;
//        int k1 = kAzure-5;
//        int k0 = kGray+2;

        //SetLineColor 
//        Modified_THStack_5->SetLineColor(k5);
//        Modified_THStack_4->SetLineColor(k4);
//        Modified_THStack_3->SetLineColor(k3);
//        Modified_THStack_2->SetLineColor(k2);
//        Modified_THStack_1->SetLineColor(k1);
//        Modified_THStack_0->SetLineColor(k0);

        //SetLineWidth 2 
        Modified_THStack_5_l_vs_eta->SetLineWidth(2);
//        Modified_THStack_4_l_vs_eta->SetLineWidth(2);
//        Modified_THStack_3_l_vs_eta->SetLineWidth(2);
//        Modified_THStack_2_l_vs_eta->SetLineWidth(2);
//        Modified_THStack_1_l_vs_eta->SetLineWidth(2);
//        Modified_THStack_0_l_vs_eta->SetLineWidth(2);

//        Modified_THStack_0_l_vs_eta->Draw("histo");
//        Modified_THStack_1_l_vs_eta->Draw("histo same");
//        Modified_THStack_2_l_vs_eta->Draw("histo same");
//        Modified_THStack_3_l_vs_eta->Draw("histo same");
//        Modified_THStack_4_l_vs_eta->Draw("histo same");
        Modified_THStack_5_l_vs_eta->Draw("histo");

        Modified_THStack_5_l_vs_eta->SetTitle("t/#lambda_{I} vs. #eta: Modified/Original geometry");
        Modified_THStack_5_l_vs_eta->SetYTitle("ratio");
        Modified_THStack_5_l_vs_eta->GetYaxis()->SetTitleOffset(2.1);
        Modified_THStack_5_l_vs_eta->GetXaxis()->SetRangeUser(-4, 4);
//      Modified_THStack_5_l_vs_eta.GetYaxis()->SetRangeUser(0.999, 1.008);

        // Legenda
//       TLegend *theLegend_Divide = new TLegend(0.18,0.8,0.98,0.92); //$$ per inserire la TLegend al posto giusto
//       theLegend_Divide->SetNColumns(3); //$$
//       theLegend_Divide->SetFillColor(0); //$$
//       theLegend_Divide->SetFillStyle(0); //$$
//       theLegend_Divide->SetBorderSize(0); //$$
//       theLegend_Divide->AddEntry(Modified_THStack_5,  "Support Tube",  "f");
//       theLegend_Divide->AddEntry(Modified_THStack_3,      "TOB",      "f");
//       theLegend_Divide->AddEntry(Modified_THStack_1,    "Pixel",    "f");
//       theLegend_Divide->AddEntry(Modified_THStack_4,      "TEC",      "f");
//       theLegend_Divide->AddEntry(Modified_THStack_2,       "TIB and TID",  "f");
//       theLegend_Divide->AddEntry(Modified_THStack_0, "Beam Pipe","f");
//       theLegend_Divide->Draw();
  //
         Divide_c1_l_vs_eta->SaveAs((outputpdf_l_vs_eta.c_str()));
         // Divide_c1_l_vs_eta->SaveAs((outputpng_l_vs_eta.c_str()));
         Divide_c1_l_vs_eta->SaveAs((outputroot_l_vs_eta.c_str()));
         // Divide_c1_l_vs_eta->SaveAs((outputC_l_vs_eta.c_str()));

  outplots_l_vs_eta->cd();
  outplots_l_vs_eta->Write();
  outplots_l_vs_eta->Close();

}

