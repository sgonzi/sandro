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
	/* Plots:
	comparestack("Nvtx_", "N^{vtx} ");
Nvtx_->SaveAs("Nvtx_.png");
	comparestack("nPhotons_", "N^{#gamma}");
nPhotons_->SaveAs("nPhotons_.png");
	comparestack("isPhotonlead_", "isPhotonlead");
isPhotonlead_->SaveAs("isPhotonlead_.png");
	comparestack("photonPt_1", "p_{T}^{#gamma1} [GeV/#font[12]{c}]");
photonPt_1->SaveAs("photonPt_1.png");
	comparestack("photonE_1", "E^{#gamma1} [GeV]");
photonE_1->SaveAs("photonE_1.png");
	comparestack("photonEta_1", "#eta^{#gamma1}");
photonEta_1->SaveAs("photonEta_1.png");
	comparestack("photonPhi_1", "#varphi^{#gamma1}");
photonPhi_1->SaveAs("photonPhi_1.png");
	comparestack("photonBit_1", "bit^{#gamma1}");
photonBit_1->SaveAs("photonBit_1.png");
	comparestack("photonPassConversionVeto_1","#gamma1 PassConversionVeto);
photonPassConversionVeto_1->SaveAs("photonPassConversionVeto_1.png");
	comparestack("photonPfIsoChargedHad_1", "#gamma1 PfIsoChargedHad");
photonPfIsoChargedHad_1->SaveAs("photonPfIsoChargedHad_1.png");
	comparestack("photonPfIsoNeutralHad_1", "#gamma1 PfIsoNeutralHad");
photonPfIsoNeutralHad_1->SaveAs("photonPfIsoNeutralHad_1.png");
	comparestack("photonPfIsoPhoton_1", "#gamma1 PfIsoPhoton");
photonPfIsoPhoton_1->SaveAs("photonPfIsoPhoton_1.png");
	comparestack("photonPfIsoPhotons03ForCic_1", "#gamma1 PfIsoPhotons03ForCic");
photonPfIsoPhotons03ForCic_1->SaveAs("photonPfIsoPhotons03ForCic_1.png");
	comparestack("photonPfIsoNeutrals03ForCic_1", "#gamma1 PfIsoNeutrals03ForCic");
photonPfIsoNeutrals03ForCic_1->SaveAs("photonPfIsoNeutrals03ForCic_1.png");
	comparestack("photonPfIsoCharged03ForCicVtx0_1", "#gamma1 PfIsoCharged03ForCicVtx0");
photonPfIsoCharged03ForCicVtx0_1->SaveAs("photonPfIsoCharged03ForCicVtx0_1.png");
	comparestack("photonPfIsoCharged03BadForCic_1", "#gamma1 PfIsoCharged03BadForCic");
photonPfIsoCharged03BadForCic_1->SaveAs("photonPfIsoCharged03BadForCic_1.png");
	comparestack("photonPfIsoPhotons04ForCic_1", "#gamma1 PfIsoPhotons04ForCic");
photonPfIsoPhotons04ForCic_1->SaveAs("photonPfIsoPhotons04ForCic_1.png");
	comparestack("photonPfIsoNeutrals04ForCic_1", "#gamma1 PfIsoNeutrals04ForCic");
photonPfIsoNeutrals04ForCic_1->SaveAs("photonPfIsoNeutrals04ForCic_1.png");
	comparestack("photonPfIsoCharged04ForCicVtx0_1", "#gamma1  PfIsoCharged04ForCicVtx0");
photonPfIsoCharged04ForCicVtx0_1->SaveAs("photonPfIsoCharged04ForCicVtx0_1.png");
	comparestack("photonPfIsoCharged04BadForCic_1", "#gamma1 PfIsoCharged04BadForCic");
photonPfIsoCharged04BadForCic_1->SaveAs("photonPfIsoCharged04BadForCic_1.png");
	comparestack("photonid_sieie_1", "#gamma1 #sigma_{i#etai#eta}");
photonid_sieie_1->SaveAs("photonid_sieie_1.png");
	comparestack("photonid_sieip_1", "#gamma1 #sigma_{i#etai#varphi}");
photonid_sieip_1->SaveAs("photonid_sieip_1.png");
	comparestack("photonid_etawidth_1", "#gamma1 #eta width");
photonid_etawidth_1->SaveAs("photonid_etawidth_1.png");
	comparestack("photonid_phiwidth_1", "#gamma1 #varphi width");
photonid_phiwidth_1->SaveAs("photonid_phiwidth_1.png");
	comparestack("photonid_r9_1", "#gamma1 r9");
photonid_r9_1->SaveAs("photonid_r9_1.png");
	comparestack("photonid_lambdaRatio_1", "#gamma1 #lambda Ratio");
photonid_lambdaRatio_1->SaveAs("photonid_lambdaRatio_1.png");
	comparestack("photonid_s4Ratio_1", "#gamma1 s4 Ratio");
photonid_s4Ratio_1->SaveAs("photonid_s4Ratio_1.png");
	comparestack("photonid_e25_1", "#gamma1 #rho25");
photonid_e25_1->SaveAs("photonid_e25_1.png");
	comparestack("photonid_sceta_1", "#gamma1 SC #eta");
photonid_sceta_1->SaveAs("photonid_sceta_1.png");
	comparestack("photonid_ESEffSigmaRR_1", "#gamma1 ESEffSigmaRR");
photonid_ESEffSigmaRR_1->SaveAs("photonid_ESEffSigmaRR_1.png");
	comparestack("photonid_hadronicOverEm_1", "#gamma1 hadronicOverEm");
photonid_hadronicOverEm_1->SaveAs("photonid_hadronicOverEm_1.png");
	comparestack("photonid_hadronicOverEm2012_1", "#gamma1 hadronicOverEm2012");
photonid_hadronicOverEm2012_1->SaveAs("photonid_hadronicOverEm2012_1.png");
	comparestack("photonhcalTowerSumEtConeDR04_1", "#gamma1 hcalTowerSumEtConeDR04");
photonhcalTowerSumEtConeDR04_1->SaveAs("photonhcalTowerSumEtConeDR04_1.png");
	comparestack("photonecalRecHitSumEtConeDR04_1", "#gamma1 ecalRecHitSumEtConeDR04");
photonecalRecHitSumEtConeDR04_1->SaveAs("photonecalRecHitSumEtConeDR04_1.png");
	comparestack("photonnTrkSolidConeDR04_1", "#gamma1 nTrkSolidConeDR04");
photonnTrkSolidConeDR04_1->SaveAs("photonnTrkSolidConeDR04_1.png");
	comparestack("photontrkSumPtSolidConeDR04_1", "#gamma1 trkSumPtSolidConeDR04");
photontrkSumPtSolidConeDR04_1->SaveAs("photontrkSumPtSolidConeDR04_1.png");
	comparestack("photonnTrkHollowConeDR04_1", "#gamma1 nTrkHollowConeDR04");
photonnTrkHollowConeDR04_1->SaveAs("photonnTrkHollowConeDR04_1.png");
	comparestack("photontrkSumPtHollowConeDR04", "#gamma1 trkSumPtHollowConeDR04");
photontrkSumPtHollowConeDR04->SaveAs("photontrkSumPtHollowConeDR04.png");
	comparestack("photonIsoFPRCharged_1", "#gamma1 IsoFPRCharged");
photonIsoFPRCharged_1->SaveAs("photonIsoFPRCharged_1.png");
	comparestack("photonIsoFPRNeutral_1", "#gamma1 IsoFPRNeutral");
photonIsoFPRNeutral_1->SaveAs("photonIsoFPRNeutral_1.png");
	comparestack("photonIsoFPRPhoton_1", "#gamma1 IsoFPRPhoton");
photonIsoFPRPhoton_1->SaveAs("photonIsoFPRPhoton_1.png");
	comparestack("nJets_", "N^{jets}");
nJets_->SaveAs("nJets_.png");
	comparestack("jetPt_1", "p_{T}^{jet1} [GeV/#font[12]{c}]");
jetPt_1->SaveAs("jetPt_1.png");
	comparestack("jetEta_1", "#eta^{jet1}");
jetEta_1->SaveAs("jetEta_1.png");
	comparestack("jetY_1", "Y^{jet1}"); 
jetY_1->SaveAs("jetY_1.png");
	comparestack("jetPhi_1", "#varphi^{jet1}");
jetPhi_1->SaveAs("jetPhi_1.png");
	comparestack("jetE_1", "E^{jet1}[GeV]");
jetE_1->SaveAs("jetE_1.png");
	comparestack("jetPt_2", "p_{T}^{jet2} [GeV/#font[12]{c}]");
jetPt_2->SaveAs("jetPt_2.png");
	comparestack("jetEta_2", "#eta^{jet2}");
jetEta_2->SaveAs("jetEta_2.png");
	comparestack("jetY_2", "Y^{jet2}"); 
jetY_2->SaveAs("jetY_2.png");
	comparestack("jetPhi_2", "#varphi^{jet2}");
jetPhi_2->SaveAs("jetPhi_2.png");
	comparestack("jetE_2", "E^{jet2} [GeV]");
jetE_2->SaveAs("jetE_2.png");
	comparestack("jetPt_3", "p_{T}^{jet3} [GeV/#font[12]{c}]");
jetPt_3->SaveAs("jetPt_3.png");
	comparestack("jetEta_3", "#eta^{jet3}");
jetEta_3->SaveAs("jetEta_3.png");
	comparestack("jetY_3", "Y^{jet3}"); 
jetY_3>SaveAs("jetY_3.png");
	comparestack("jetPhi_3", "#varphi^{jet3}");
jetPhi_3->SaveAs("jetPhi_3.png");
	comparestack("jetE_3", "E^{jet3} [GeV]");
jetE_3->SaveAs("jetE_3.png");
	comparestack("DeltaR_photon1_jet1_", "#DeltaR #gamma1-jet1");
DeltaR_photon1_jet1_->SaveAs("DeltaR_photon1_jet1_.png");
	comparestack("DeltaR_photon1_jet2_", "#DeltaR #gamma1-jet2");
DeltaR_photon1_jet2_->SaveAs("DeltaR_photon1_jet2_.png");
	comparestack("DeltaR_photon1_jet3_", "#DeltaR #gamma1-jet3");
DeltaR_photon1_jet3_->SaveAs("DeltaR_photon1_jet3_.png");
	*/

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
	Char_t GJets_HT_200To400_name[100];
	Char_t GJets_HT_400ToInf_name[100];
	Char_t QCD_HT_100To250_name[100];
//	Char_t QCD_HT_250To500_name[100];
	Char_t QCD_HT_500To1000_name[100];
	Char_t QCD_HT_1000ToInf_name[100];

	Int_t itype = 0; //dummy

	sprintf(dataname,"data_all_photons_gammahistos_%d.root",itype);
//	sprintf(dataname,"data_Run2012B_13Jul2012_gammahistos_%d.root",itype);
	cout << "data file is_ " << dataname << endl;
	sprintf(GJets_HT_200To400_name,"mc_GJets_HT-200To400_gammahistos_%d.root",itype);
	cout << "GJets file 1 is: " << GJets_HT_200To400_name << endl;
	sprintf(GJets_HT_400ToInf_name,"mc_GJets_HT-400ToInf_gammahistos_%d.root",itype);
	cout << "GJets file 2 is: " << GJets_HT_400ToInf_name << endl;
	sprintf(QCD_HT_100To250_name,"mc_QCD_HT-100To250_gammahistos_%d.root",itype);
	cout << "QCD file 1 is: " << QCD_HT_100To250_name << endl;
//	sprintf(QCD_HT_250To500_name,"mc_QCD_HT-250To500_gammahistos_%d.root",itype);
//	cout << "QCD file 2 is: " << QCD_HT_250To500_name << endl;
	sprintf(QCD_HT_500To1000_name,"mc_QCD_HT-500To1000_gammahistos_%d.root",itype);
	cout << "QCD file 3 is: " << QCD_HT_500To1000_name << endl;
	sprintf(QCD_HT_1000ToInf_name,"mc_QCD_HT-1000ToInf_gammahistos_%d.root",itype);
	cout << "QCD file 4 is: " << QCD_HT_1000ToInf_name << endl;


	TFile *datafile=new TFile(dataname);  
	TFile *GJets_HT_200To400_file  =new TFile(GJets_HT_200To400_name);
	TFile *GJets_HT_400ToInf_file  =new TFile(GJets_HT_400ToInf_name); 
	TFile *QCD_HT_100To250_file  =new TFile(QCD_HT_100To250_name);  
//	TFile *QCD_HT_250To500_file  =new TFile(QCD_HT_250To500_name);   
	TFile *QCD_HT_500To1000_file  =new TFile(QCD_HT_500To1000_name); 
	TFile *QCD_HT_1000ToInf_file  =new TFile(QCD_HT_1000ToInf_name); 

	Char_t titlehisto[100],titlecanvas[100];

	strcpy(titlehisto,titleh);
	cout << "Analyzing Histogram " << titlehisto << endl;


	TH1F *Datahisto=(TH1F*)datafile->Get(titlehisto);
	cout << "Data entries " << Datahisto->Integral() << endl;  

	TH1F *GJets_HT_200To400_histo=(TH1F*)GJets_HT_200To400_file->Get(titlehisto);
//	GJets_HT_200To400_histo->Scale(185.798/510.274);
	cout << "GJets file 1 entries " << GJets_HT_200To400_histo->Integral() << endl;
	GJets_HT_200To400_histo->SetLineColor(1);
	GJets_HT_200To400_histo->SetFillColor(5);  //for colors comment out Sumw2 in code

	TH1F *GJets_HT_400ToInf_histo=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto);
//	GJets_HT_400ToInf_histo->Scale(185.798/510.274);
	cout << "GJets file 2 entries " << GJets_HT_400ToInf_histo->Integral() << endl;
	GJets_HT_200To400_histo->Add(GJets_HT_400ToInf_histo);  

	TH1F *QCD_HT_100To250_histo=(TH1F*)QCD_HT_100To250_file->Get(titlehisto);
//	QCD_HT_100To250_histo->Scale(185.798/510.274);
	cout << "QCD file 1 entries " << QCD_HT_100To250_histo->Integral() << endl;  
	QCD_HT_100To250_histo->SetLineColor(1);
	QCD_HT_100To250_histo->SetFillColor(kMagenta+2);
/*
	TH1F *QCD_HT_250To500_histo=(TH1F*)QCD_HT_250To500_file->Get(titlehisto);
	cout << "QCD file 2 entries " << QCD_HT_250To500_histo->Integral() << endl;  
*/
	TH1F *QCD_HT_500To1000_histo=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto);
//  QCD_HT_500To1000_histo->Scale(185.798/510.274);
	cout << "QCD file 3 entries " << QCD_HT_500To1000_histo->Integral() << endl;

	TH1F *QCD_HT_1000ToInf_histo=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto);
//	QCD_HT_1000ToInf_histo->Scale(185.798/510.274);
	cout << "QCD file 4 entries " << QCD_HT_1000ToInf_histo->Integral() << endl;

//	QCD_HT_100To250_histo->Add(QCD_HT_250To500_histo);
	QCD_HT_100To250_histo->Add(QCD_HT_500To1000_histo);  
	QCD_HT_100To250_histo->Add(QCD_HT_1000ToInf_histo);  

//	QCD_HT_500To1000_histo->SetLineColor(1);
//	QCD_HT_500To1000_histo->SetFillColor(kMagenta+2);

	cout << "GJets total entries " << GJets_HT_200To400_histo->Integral() << endl;  
	cout << "QCD total entries " << QCD_HT_100To250_histo->Integral() << endl;  
//	cout << "QCD total entries " << QCD_HT_500To1000_histo->Integral() << endl;  

  TCanvas *c1=new TCanvas(titlehisto,titlehisto,200,10,700,700);  
  // c1->Divide(1,2);

   
   // c1->cd(1);
   // GJets_HT_200To400_histo->Draw();
   // gPad->SetLogy();
   // c1->cd(2);
   // QCD_HT_100To250_histo->Draw();
   // gPad->SetLogy();

	THStack *MCtotal= new THStack();

	MCtotal->Add(QCD_HT_100To250_histo);
	MCtotal->Add(GJets_HT_200To400_histo);
/*
	MCtotal->Add(QCD_HT_500To1000_histo);
	MCtotal->Add(GJets_HT_200To400_histo);
*/

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
	leg->AddEntry(Datahisto,"Data 510.274 pb^{-1}","pL");
	leg->AddEntry(GJets_HT_200To400_histo,"#gamma + jets","f");
	leg->AddEntry(QCD_HT_100To250_histo,"QCD","f");
//	leg->AddEntry(QCD_HT_500To1000_histo,"QCD","f");
	leg->SetFillColor(10);
	leg->SetLineColor(10);
	leg->Draw();

   //gStyle->SetOptStat(0);
  

}
