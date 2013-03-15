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
#include <TPaveText.h>
#include <TPad.h>
#include <TBox.h>

void setMYStyle() {

  TStyle *myStyle = new TStyle("MYStyle","My Style");

// For the canvas:
  myStyle->SetCanvasBorderMode(0);
  myStyle->SetCanvasColor(kWhite);
  myStyle->SetCanvasDefH(600); //Height of canvas
  myStyle->SetCanvasDefW(600); //Width of canvas
  myStyle->SetCanvasDefX(0);   //POsition on screen
  myStyle->SetCanvasDefY(0);

// For the Pad:
  myStyle->SetPadBorderMode(0);
  myStyle->SetPadColor(kWhite);
  myStyle->SetPadGridX(false);
  myStyle->SetPadGridY(false);
  myStyle->SetGridColor(0);
  myStyle->SetGridStyle(3);
  myStyle->SetGridWidth(1);

// For the frame:
  myStyle->SetFrameBorderMode(0);
  myStyle->SetFrameBorderSize(1);
  myStyle->SetFrameFillColor(0);
  myStyle->SetFrameFillStyle(0);
  myStyle->SetFrameLineColor(1);
  myStyle->SetFrameLineStyle(1);
  myStyle->SetFrameLineWidth(1);

// For the histo:
  myStyle->SetHistLineColor(1);
  myStyle->SetHistLineStyle(0);
  myStyle->SetHistLineWidth(1);
  myStyle->SetEndErrorSize(2);
  myStyle->SetErrorX(0.);
  myStyle->SetMarkerStyle(20);

//For the fit/function:
  myStyle->SetOptFit(1);
  myStyle->SetFitFormat("5.4g");
  myStyle->SetFuncColor(2);
  myStyle->SetFuncStyle(1);
  myStyle->SetFuncWidth(1);

//For the date:
  myStyle->SetOptDate(0);

// For the statistics box:
  myStyle->SetOptFile(0);
  myStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  myStyle->SetStatColor(kWhite);
  myStyle->SetStatFont(42);
  myStyle->SetStatFontSize(0.025);
  myStyle->SetStatTextColor(1);
  myStyle->SetStatFormat("6.4g");
  myStyle->SetStatBorderSize(1);
  myStyle->SetStatH(0.1);
  myStyle->SetStatW(0.15);

// Margins:
  myStyle->SetPadTopMargin(0.07);
  myStyle->SetPadBottomMargin(0.13);
  myStyle->SetPadLeftMargin(0.13);
  myStyle->SetPadRightMargin(0.13);

// For the Global title:
  myStyle->SetOptTitle(0);
  myStyle->SetTitleFont(42);
  myStyle->SetTitleColor(1);
  myStyle->SetTitleTextColor(1);
  myStyle->SetTitleFillColor(10);
  myStyle->SetTitleFontSize(0.05);

// For the axis titles:
  myStyle->SetTitleColor(1, "XYZ");
  myStyle->SetTitleFont(42, "XYZ");
  myStyle->SetTitleSize(0.06, "XYZ");
  myStyle->SetTitleXOffset(0.9);
  myStyle->SetTitleYOffset(1.);

// For the axis labels:
  myStyle->SetLabelColor(1, "XYZ");
  myStyle->SetLabelFont(42, "XYZ");
  myStyle->SetLabelOffset(0.007, "XYZ");
  myStyle->SetLabelSize(0.045, "XYZ");

// For the axis:
  myStyle->SetAxisColor(1, "XYZ");
  myStyle->SetStripDecimals(kTRUE);
  myStyle->SetTickLength(0.03, "XYZ");
  myStyle->SetNdivisions(510, "XYZ");
  myStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  myStyle->SetPadTickY(1);

// Change for log plots:
  myStyle->SetOptLogx(0);
  myStyle->SetOptLogy(0);
  myStyle->SetOptLogz(0);

// Postscript options:
  myStyle->SetPaperSize(20.,20.);

  myStyle->cd();
}


void comparestack(char* titleh, char* namevariable){

  // Usage is: .L comparestack.C+
  //       ie: comparestack("ptPhoton_","P_{T}^{#gamma} [GeV]")
	/* Plots:
	comparestack("Nvtx_", "N^{vtx} ");
Nvtx_->SaveAs("Nvtx_.png");
	comparestack("nPhotons_", "N^{#gamma}");
nPhotons_->SaveAs("nPhotons_.png");
	comparestack("photonPt_1_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]");
photonPt_1_->SaveAs("photonPt_1_.png");
	comparestack("photonE_1_", "E^{#gamma1} [GeV]");
photonE_1_->SaveAs("photonE_1_.png");
	comparestack("photonEta_1_", "#eta^{#gamma1}");
photonEta_1_->SaveAs("photonEta_1-.png");
	comparestack("photonPhi_1_", "#varphi^{#gamma1}");
photonPhi_1_->SaveAs("photonPhi_1-.png");
	comparestack("photonBit_1_", "bit^{#gamma1}");
photonBit_1_->SaveAs("photonBit_1_.png");

	comparestack("photonPfIsoChargedHad_1_", "#gamma1 PfIsoChargedHad");
photonPfIsoChargedHad_1_->SaveAs("photonPfIsoChargedHad_1_.png");
	comparestack("photonPfIsoNeutralHad_1_", "#gamma1 PfIsoNeutralHad");
photonPfIsoNeutralHad_1_->SaveAs("photonPfIsoNeutralHad_1_.png");
	comparestack("photonPfIsoPhoton_1_", "#gamma1 PfIsoPhoton");
photonPfIsoPhoton_1_->SaveAs("photonPfIsoPhoton_1_.png");
	comparestack("photonPfIsoPhotons03ForCic_1_", "#gamma1 PfIsoPhotons03ForCic");
photonPfIsoPhotons03ForCic_1_->SaveAs("photonPfIsoPhotons03ForCic_1_.png");
	comparestack("photonPfIsoNeutrals03ForCic_1_", "#gamma1 PfIsoNeutrals03ForCic");
photonPfIsoNeutrals03ForCic_1_->SaveAs("photonPfIsoNeutrals03ForCic_1_.png");
	comparestack("photonPfIsoCharged03ForCicVtx0_1_", "#gamma1 PfIsoCharged03ForCicVtx0");
photonPfIsoCharged03ForCicVtx0_1_->SaveAs("photonPfIsoCharged03ForCicVtx0_1_.png");
	comparestack("photonPfIsoCharged03BadForCic_1_", "#gamma1 PfIsoCharged03BadForCic");
photonPfIsoCharged03BadForCic_1_->SaveAs("photonPfIsoCharged03BadForCic_1_.png");
	comparestack("photonPfIsoPhotons04ForCic_1_", "#gamma1 PfIsoPhotons04ForCic");
photonPfIsoPhotons04ForCic_1_->SaveAs("photonPfIsoPhotons04ForCic_1_.png");
	comparestack("photonPfIsoNeutrals04ForCic_1_", "#gamma1 PfIsoNeutrals04ForCic");
photonPfIsoNeutrals04ForCic_1_->SaveAs("photonPfIsoNeutrals04ForCic_1_.png");
	comparestack("photonPfIsoCharged04ForCicVtx0_1_", "#gamma1  PfIsoCharged04ForCicVtx0");
photonPfIsoCharged04ForCicVtx0_1_->SaveAs("photonPfIsoCharged04ForCicVtx0_1_.png");
	comparestack("photonPfIsoCharged04BadForCic_1_", "#gamma1 PfIsoCharged04BadForCic");
photonPfIsoCharged04BadForCic_1_->SaveAs("photonPfIsoCharged04BadForCic_1_.png");

	comparestack("photonid_sieie_1_", "#gamma1 #sigma_{i#etai#eta}");
photonid_sieie_1_->SaveAs("photonid_sieie_1_.png");
	comparestack("photonid_sieip_1_", "#gamma1 #sigma_{i#etai#varphi}");
photonid_sieip_1_->SaveAs("photonid_sieip_1_.png");
	comparestack("photonid_etawidth_1_", "#gamma1 #eta width");
photonid_etawidth_1_->SaveAs("photonid_etawidth_1_.png");
	comparestack("photonid_phiwidth_1_", "#gamma1 #varphi width");
photonid_phiwidth_1_->SaveAs("photonid_phiwidth_1_.png");
	comparestack("photonid_r9_1_", "#gamma1 r9");
photonid_r9_1_->SaveAs("photonid_r9_1_.png");
	comparestack("photonid_lambdaRatio_1_", "#gamma1 #lambda Ratio");
photonid_lambdaRatio_1_->SaveAs("photonid_lambdaRatio_1_.png");
	comparestack("photonid_s4Ratio_1_", "#gamma1 s4 Ratio");
photonid_s4Ratio_1_->SaveAs("photonid_s4Ratio_1_.png");
	comparestack("photonid_e25_1_", "#gamma1 #rho25");
photonid_e25_1_->SaveAs("photonid_e25_1_.png");
	comparestack("photonid_sceta_1_", "#gamma1 SC #eta");
photonid_sceta_1_->SaveAs("photonid_sceta_1_.png");

	comparestack("photonid_ESEffSigmaRR_1_", "#gamma1 ESEffSigmaRR");
photonid_ESEffSigmaRR_1_->SaveAs("photonid_ESEffSigmaRR_1_.png");
	comparestack("photonid_hadronicOverEm_1_", "#gamma1 hadronicOverEm");
photonid_hadronicOverEm_1_->SaveAs("photonid_hadronicOverEm_1_.png");
	comparestack("photonid_hadronicOverEm2012_1_", "#gamma1 hadronicOverEm2012");
photonid_hadronicOverEm2012_1_->SaveAs("photonid_hadronicOverEm2012_1_.png");
	comparestack("photonhcalTowerSumEtConeDR04_1_", "#gamma1 hcalTowerSumEtConeDR04");
photonhcalTowerSumEtConeDR04_1_->SaveAs("photonhcalTowerSumEtConeDR04_1_.png");
	comparestack("photonecalRecHitSumEtConeDR04_1_", "#gamma1 ecalRecHitSumEtConeDR04");
photonecalRecHitSumEtConeDR04_1_->SaveAs("photonecalRecHitSumEtConeDR04_1_.png");
	comparestack("photonnTrkSolidConeDR04_1_", "#gamma1 nTrkSolidConeDR04");
photonnTrkSolidConeDR04_1_->SaveAs("photonnTrkSolidConeDR04_1_.png");
	comparestack("photontrkSumPtSolidConeDR04_1_", "#gamma1 trkSumPtSolidConeDR04");
photontrkSumPtSolidConeDR04_1_->SaveAs("photontrkSumPtSolidConeDR04_1_.png");
	comparestack("photonnTrkHollowConeDR04_1_", "#gamma1 nTrkHollowConeDR04");
photonnTrkHollowConeDR04_1_->SaveAs("photonnTrkHollowConeDR04_1_.png");
	comparestack("photontrkSumPtHollowConeDR04_", "#gamma1 trkSumPtHollowConeDR04");
photontrkSumPtHollowConeDR04_1_->SaveAs("photontrkSumPtHollowConeDR04_1_.png");
	comparestack("photonIsoFPRCharged_1_", "#gamma1 IsoFPRCharged");
photonIsoFPRCharged_1_->SaveAs("photonIsoFPRCharged_1_.png");
	comparestack("photonIsoFPRNeutral_1_", "#gamma1 IsoFPRNeutral");
photonIsoFPRNeutral_1_->SaveAs("photonIsoFPRNeutral_1_.png");
	comparestack("photonIsoFPRPhoton_1_", "#gamma1 IsoFPRPhoton");
photonIsoFPRPhoton_1_->SaveAs("photonIsoFPRPhoton_1_.png");

	comparestack("nJets_", "N^{jets}");
nJets_->SaveAs("nJets_.png");
	comparestack("jetPt_1_", "p_{T}^{jet1} [GeV/#font[12]{c}]");
jetPt_1_->SaveAs("jetPt_1_.png");
	comparestack("jetEta_1_", "#eta^{jet1}");
jetEta_1_->SaveAs("jetEta_1_.png");
	comparestack("jetPhi_1_", "#varphi^{jet1}");
jetPhi_1_->SaveAs("jetPhi_1_.png");
	comparestack("jetE_1_", "E^{jet1}[GeV]");
jetE_1_->SaveAs("jetE_1_.png");
	comparestack("jetPt_2_", "p_{T}^{jet2} [GeV/#font[12]{c}]");
jetPt_2_->SaveAs("jetPt_2_.png");
	comparestack("jetEta_2_", "#eta^{jet2}");
jetEta_2_->SaveAs("jetEta_2_.png");

	comparestack("jetPhi_2_", "#varphi^{jet2}");
jetPhi_2_->SaveAs("jetPhi_2_.png");
	comparestack("jetE_2_", "E^{jet2} [GeV]");
jetE_2_->SaveAs("jetE_2_.png");
	comparestack("jetPt_3_", "p_{T}^{jet3} [GeV/#font[12]{c}]");
jetPt_3_->SaveAs("jetPt_3_.png");
	comparestack("jetEta_3_", "#eta^{jet3}");
jetEta_3_->SaveAs("jetEta_3_.png");

	comparestack("jetPhi_3_", "#varphi^{jet3}");
jetPhi_3_->SaveAs("jetPhi_3_.png");
	comparestack("jetE_3_", "E^{jet3} [GeV]");
jetE_3_->SaveAs("jetE_3_.png");
	comparestack("DeltaR_photon1_jet1_", "#DeltaR #gamma1-jet1");
DeltaR_photon1_jet1_->SaveAs("DeltaR_photon1_jet1_.png");
	comparestack("DeltaR_photon1_jet2_", "#DeltaR #gamma1-jet2");
DeltaR_photon1_jet2_->SaveAs("DeltaR_photon1_jet2_.png");
	comparestack("DeltaR_photon1_jet3_", "#DeltaR #gamma1-jet3");
DeltaR_photon1_jet3_->SaveAs("DeltaR_photon1_jet3_.png");

	comparestack("DeltaPhi_photon1_jet1_","#Delta#varphi photon1-jet1");
DeltaPhi_photon1_jet1_->SaveAs("DeltaPhi_photon1_jet1_.png");
	comparestack("DeltaEta_jet1_jet2_","#Delta#eta jet1-jet2");
DeltaEta_jet1_jet2_->SaveAs("DeltaEta_jet1_jet2_.png");
	comparestack("DeltaPhi_jet1_jet2_","#Delta#varphi jet1-jet2");
DeltaPhi_jet1_jet2_->SaveAs("DeltaPhi_jet1_jet2_.png");
	comparestack("HT_","H_{T}");
HT_->SaveAs("HT_.png");

-------------

	comparestack("Nvtx_cl_", "N^{vtx} ");
Nvtx_cl_->SaveAs("Nvtx_cl_.png");
	comparestack("nPhotons_cl_", "N^{#gamma}");
nPhotons_cl_->SaveAs("nPhotons_cl_.png");
	comparestack("photonPt_1_cl_", "p_{T}^{#gamma1} [GeV/#font[12]{c}]");
photonPt_1_cl_->SaveAs("photonPt_1_cl_.png");
	comparestack("photonE_1_cl_", "E^{#gamma1} [GeV]");
photonE_1_cl_->SaveAs("photonE_1_cl_.png");
	comparestack("photonEta_1_cl_", "#eta^{#gamma1}");
photonEta_1_cl_->SaveAs("photonEta_1-.png");
	comparestack("photonPhi_1_cl_", "#varphi^{#gamma1}");
photonPhi_1_cl_->SaveAs("photonPhi_1-.png");
	comparestack("photonBit_1_cl_", "bit^{#gamma1}");
photonBit_1_cl_->SaveAs("photonBit_1_cl_.png");

	comparestack("photonPfIsoChargedHad_1_cl_", "#gamma1 PfIsoChargedHad");
photonPfIsoChargedHad_1_cl_->SaveAs("photonPfIsoChargedHad_1_cl_.png");
	comparestack("photonPfIsoNeutralHad_1_cl_", "#gamma1 PfIsoNeutralHad");
photonPfIsoNeutralHad_1_cl_->SaveAs("photonPfIsoNeutralHad_1_cl_.png");
	comparestack("photonPfIsoPhoton_1_cl_", "#gamma1 PfIsoPhoton");
photonPfIsoPhoton_1_cl_->SaveAs("photonPfIsoPhoton_1_cl_.png");
	comparestack("photonPfIsoPhotons03ForCic_1_cl_", "#gamma1 PfIsoPhotons03ForCic");
photonPfIsoPhotons03ForCic_1_cl_->SaveAs("photonPfIsoPhotons03ForCic_1_cl_.png");
	comparestack("photonPfIsoNeutrals03ForCic_1_cl_", "#gamma1 PfIsoNeutrals03ForCic");
photonPfIsoNeutrals03ForCic_1_cl_->SaveAs("photonPfIsoNeutrals03ForCic_1_cl_.png");
	comparestack("photonPfIsoCharged03ForCicVtx0_1_cl_", "#gamma1 PfIsoCharged03ForCicVtx0");
photonPfIsoCharged03ForCicVtx0_1_cl_->SaveAs("photonPfIsoCharged03ForCicVtx0_1_cl_.png");
	comparestack("photonPfIsoCharged03BadForCic_1_cl_", "#gamma1 PfIsoCharged03BadForCic");
photonPfIsoCharged03BadForCic_1_cl_->SaveAs("photonPfIsoCharged03BadForCic_1_cl_.png");
	comparestack("photonPfIsoPhotons04ForCic_1_cl_", "#gamma1 PfIsoPhotons04ForCic");
photonPfIsoPhotons04ForCic_1_cl_->SaveAs("photonPfIsoPhotons04ForCic_1_cl_.png");
	comparestack("photonPfIsoNeutrals04ForCic_1_cl_", "#gamma1 PfIsoNeutrals04ForCic");
photonPfIsoNeutrals04ForCic_1_cl_->SaveAs("photonPfIsoNeutrals04ForCic_1_cl_.png");
	comparestack("photonPfIsoCharged04ForCicVtx0_1_cl_", "#gamma1  PfIsoCharged04ForCicVtx0");
photonPfIsoCharged04ForCicVtx0_1_cl_->SaveAs("photonPfIsoCharged04ForCicVtx0_1_cl_.png");
	comparestack("photonPfIsoCharged04BadForCic_1_cl_", "#gamma1 PfIsoCharged04BadForCic");
photonPfIsoCharged04BadForCic_1_cl_->SaveAs("photonPfIsoCharged04BadForCic_1_cl_.png");

	comparestack("photonid_sieie_1_cl_", "#gamma1 #sigma_{i#etai#eta}");
photonid_sieie_1_cl_->SaveAs("photonid_sieie_1_cl_.png");
	comparestack("photonid_sieip_1_cl_", "#gamma1 #sigma_{i#etai#varphi}");
photonid_sieip_1_cl_->SaveAs("photonid_sieip_1_cl_.png");
	comparestack("photonid_etawidth_1_cl_", "#gamma1 #eta width");
photonid_etawidth_1_cl_->SaveAs("photonid_etawidth_1_cl_.png");
	comparestack("photonid_phiwidth_1_cl_", "#gamma1 #varphi width");
photonid_phiwidth_1_cl_->SaveAs("photonid_phiwidth_1_cl_.png");
	comparestack("photonid_r9_1_cl_", "#gamma1 r9");
photonid_r9_1_cl_->SaveAs("photonid_r9_1_cl_.png");
	comparestack("photonid_lambdaRatio_1_cl_", "#gamma1 #lambda Ratio");
photonid_lambdaRatio_1_cl_->SaveAs("photonid_lambdaRatio_1_cl_.png");
	comparestack("photonid_s4Ratio_1_cl_", "#gamma1 s4 Ratio");
photonid_s4Ratio_1_cl_->SaveAs("photonid_s4Ratio_1_cl_.png");
	comparestack("photonid_e25_1_cl_", "#gamma1 #rho25");
photonid_e25_1_cl_->SaveAs("photonid_e25_1_cl_.png");
	comparestack("photonid_sceta_1_cl_", "#gamma1 SC #eta");
photonid_sceta_1_cl_->SaveAs("photonid_sceta_1_cl_.png");

	comparestack("photonid_ESEffSigmaRR_1_cl_", "#gamma1 ESEffSigmaRR");
photonid_ESEffSigmaRR_1_cl_->SaveAs("photonid_ESEffSigmaRR_1_cl_.png");
	comparestack("photonid_hadronicOverEm_1_cl_", "#gamma1 hadronicOverEm");
photonid_hadronicOverEm_1_cl_->SaveAs("photonid_hadronicOverEm_1_cl_.png");
	comparestack("photonid_hadronicOverEm2012_1_cl_", "#gamma1 hadronicOverEm2012");
photonid_hadronicOverEm2012_1_cl_->SaveAs("photonid_hadronicOverEm2012_1_cl_.png");
	comparestack("photonhcalTowerSumEtConeDR04_1_cl_", "#gamma1 hcalTowerSumEtConeDR04");
photonhcalTowerSumEtConeDR04_1_cl_->SaveAs("photonhcalTowerSumEtConeDR04_1_cl_.png");
	comparestack("photonecalRecHitSumEtConeDR04_1_cl_", "#gamma1 ecalRecHitSumEtConeDR04");
photonecalRecHitSumEtConeDR04_1_cl_->SaveAs("photonecalRecHitSumEtConeDR04_1_cl_.png");
	comparestack("photonnTrkSolidConeDR04_1_cl_", "#gamma1 nTrkSolidConeDR04");
photonnTrkSolidConeDR04_1_cl_->SaveAs("photonnTrkSolidConeDR04_1_cl_.png");
	comparestack("photontrkSumPtSolidConeDR04_1_cl_", "#gamma1 trkSumPtSolidConeDR04");
photontrkSumPtSolidConeDR04_1_cl_->SaveAs("photontrkSumPtSolidConeDR04_1_cl_.png");
	comparestack("photonnTrkHollowConeDR04_1_cl_", "#gamma1 nTrkHollowConeDR04");
photonnTrkHollowConeDR04_1_cl_->SaveAs("photonnTrkHollowConeDR04_1_cl_.png");
	comparestack("photontrkSumPtHollowConeDR04_", "#gamma1 trkSumPtHollowConeDR04");
photontrkSumPtHollowConeDR04_1_cl_->SaveAs("photontrkSumPtHollowConeDR04_1_cl_.png");
	comparestack("photonIsoFPRCharged_1_cl_", "#gamma1 IsoFPRCharged");
photonIsoFPRCharged_1_cl_->SaveAs("photonIsoFPRCharged_1_cl_.png");
	comparestack("photonIsoFPRNeutral_1_cl_", "#gamma1 IsoFPRNeutral");
photonIsoFPRNeutral_1_cl_->SaveAs("photonIsoFPRNeutral_1_cl_.png");
	comparestack("photonIsoFPRPhoton_1_cl_", "#gamma1 IsoFPRPhoton");
photonIsoFPRPhoton_1_cl_->SaveAs("photonIsoFPRPhoton_1_cl_.png");

	comparestack("nJets_cl_", "N^{jets}");
nJets_cl_->SaveAs("nJets_cl_.png");
	comparestack("jetPt_1_cl_", "p_{T}^{jet1} [GeV/#font[12]{c}]");
jetPt_1_cl_->SaveAs("jetPt_1_cl_.png");
	comparestack("jetEta_1_cl_", "#eta^{jet1}");
jetEta_1_cl_->SaveAs("jetEta_1_cl_.png");
	comparestack("jetPhi_1_cl_", "#varphi^{jet1}");
jetPhi_1_cl_->SaveAs("jetPhi_1_cl_.png");
	comparestack("jetE_1_cl_", "E^{jet1}[GeV]");
jetE_1_cl_->SaveAs("jetE_1_cl_.png");
	comparestack("jetPt_2_cl_", "p_{T}^{jet2} [GeV/#font[12]{c}]");
jetPt_2_cl_->SaveAs("jetPt_2_cl_.png");
	comparestack("jetEta_2_cl_", "#eta^{jet2}");
jetEta_2_cl_->SaveAs("jetEta_2_cl_.png");

	comparestack("jetPhi_2_cl_", "#varphi^{jet2}");
jetPhi_2_cl_->SaveAs("jetPhi_2_cl_.png");
	comparestack("jetE_2_cl_", "E^{jet2} [GeV]");
jetE_2_cl_->SaveAs("jetE_2_cl_.png");
	comparestack("jetPt_3_cl_", "p_{T}^{jet3} [GeV/#font[12]{c}]");
jetPt_3_cl_->SaveAs("jetPt_3_cl_.png");
	comparestack("jetEta_3_cl_", "#eta^{jet3}");
jetEta_3_cl_->SaveAs("jetEta_3_cl_.png");

	comparestack("jetPhi_3_cl_", "#varphi^{jet3}");
jetPhi_3_cl_->SaveAs("jetPhi_3_cl_.png");
	comparestack("jetE_3_cl_", "E^{jet3} [GeV]");
jetE_3_cl_->SaveAs("jetE_3_cl_.png");
	comparestack("DeltaR_photon1_jet1_cl_", "#DeltaR #gamma1-jet1");
DeltaR_photon1_jet1_cl_->SaveAs("DeltaR_photon1_jet1_cl_.png");
	comparestack("DeltaR_photon1_jet2_cl_", "#DeltaR #gamma1-jet2");
DeltaR_photon1_jet2_cl_->SaveAs("DeltaR_photon1_jet2_cl_.png");
	comparestack("DeltaR_photon1_jet3_cl_", "#DeltaR #gamma1-jet3");
DeltaR_photon1_jet3_cl_->SaveAs("DeltaR_photon1_jet3_cl_.png");

	comparestack("DeltaPhi_photon1_jet1_cl_","#Delta#varphi photon1-jet1");
DeltaPhi_photon1_jet1_cl_->SaveAs("DeltaPhi_photon1_jet1_cl_.png");
	comparestack("DeltaEta_jet1_jet2_cl_","#Delta#eta jet1-jet2");
DeltaEta_jet1_jet2_cl_->SaveAs("DeltaEta_jet1_jet2_cl_.png");
	comparestack("DeltaPhi_jet1_jet2_cl_","#Delta#varphi jet1-jet2");
DeltaPhi_jet1_jet2_cl_->SaveAs("DeltaPhi_jet1_jet2_cl_.png");
	comparestack("HT_cl_","H_{T}");
HT_cl_->SaveAs("HT_cl_.png");

*/


/*
	comparestack("photonPassConversionVeto_1","#gamma1 PassConversionVeto);
photonPassConversionVeto_1->SaveAs("photonPassConversionVeto_1.png");
	comparestack("isPhotonlead_", "isPhotonlead");
isPhotonlead_->SaveAs("isPhotonlead_.png");
	comparestack("jetY_1", "Y^{jet1}"); 
jetY_1->SaveAs("jetY_1.png");
	comparestack("jetY_2", "Y^{jet2}"); 
jetY_2->SaveAs("jetY_2.png");
	comparestack("jetY_3", "Y^{jet3}"); 
jetY_3>SaveAs("jetY_3.png");
	*/
	setMYStyle();
	
	Char_t DATA_Run2012A_13Jul2012_name[100];
	Char_t DATA_Run2012A_recover_06Aug2012_name[100];
	Char_t DATA_Run2012B_13Jul2012_name[100];
	Char_t DATA_Run2012C_24Aug2012_name[100];
	Char_t DATA_Run2012C_EcalRecover_11Dec2012_name[100];
	Char_t DATA_Run2012C_PromptReco_name[100];
	Char_t DATA_Run2012D_PromptReco_name[100];
							
	Char_t GJets_HT_200To400_name[100];
	Char_t GJets_HT_400ToInf_name[100];
	
	Char_t QCD_Pt_20_30_EMEnriched_name[100];
	Char_t QCD_Pt_30_80_EMEnriched_name[100];
	Char_t QCD_Pt_80_170_EMEnriched_name[100];
	Char_t QCD_Pt_170_250_EMEnriched_name[100];
	Char_t QCD_Pt_250_350_EMEnriched_name[100];
	Char_t QCD_Pt_350_EMEnriched_name[100];

	Char_t QCD_Pt_20_30_BCtoE_name[100];
	Char_t QCD_Pt_30_80_BCtoE_name[100];
	Char_t QCD_Pt_80_170_BCtoE_name[100];
	Char_t QCD_Pt_170_250_BCtoE_name[100];
	Char_t QCD_Pt_250_350_BCtoE_name[100];
	Char_t QCD_Pt_350_BCtoE_name[100];
	
/*
	Char_t QCD_HT_100To250_name[100];
	Char_t QCD_HT_250To500_name[100];
	Char_t QCD_HT_500To1000_name[100];
	Char_t QCD_HT_1000ToInf_name[100];
*/

	Int_t itype = 2; // identifica histo con analisi diverse
	string png_folder = "png_plots/";
	string png_string = ".png";
	string root_folder = "root_plots/";
	string root_string = ".root";

	sprintf(DATA_Run2012A_13Jul2012_name,"DATA_Run2012A-13Jul2012_histos_%d.root",itype);
	cout << "data file 1 is " << DATA_Run2012A_13Jul2012_name << endl;
	sprintf(DATA_Run2012A_recover_06Aug2012_name,"DATA_Run2012A-recover-06Aug2012_histos_%d.root",itype);
	cout << "data file 2 is " << DATA_Run2012A_recover_06Aug2012_name << endl;
	sprintf(DATA_Run2012B_13Jul2012_name,"DATA_Run2012B-13Jul2012_histos_%d.root",itype);
	cout << "data file 3 is " << DATA_Run2012B_13Jul2012_name << endl;
	sprintf(DATA_Run2012C_24Aug2012_name,"DATA_Run2012C-24Aug2012_histos_%d.root",itype);
	cout << "data file 4 is " << DATA_Run2012C_24Aug2012_name << endl;
	sprintf(DATA_Run2012C_EcalRecover_11Dec2012_name,"DATA_Run2012C-EcalRecover_11Dec2012_histos_%d.root",itype);
	cout << "data file 5 is " << DATA_Run2012C_EcalRecover_11Dec2012_name << endl;
	sprintf(DATA_Run2012C_PromptReco_name,"DATA_Run2012C-PromptReco_histos_%d.root",itype);
	cout << "data file 6 is " << DATA_Run2012C_PromptReco_name << endl;
	sprintf(DATA_Run2012D_PromptReco_name,"DATA_Run2012D-PromptReco_histos_%d.root",itype);
	cout << "data file 7 is " << DATA_Run2012D_PromptReco_name << endl;

	sprintf(GJets_HT_200To400_name,"MC_GJets_HT-200To400_histos_%d.root",itype);
	cout << "GJets file 11 is: " << GJets_HT_200To400_name << endl;
	sprintf(GJets_HT_400ToInf_name,"MC_GJets_HT-400ToInf_histos_%d.root",itype);
	cout << "GJets file 12 is: " << GJets_HT_400ToInf_name << endl;

	sprintf(QCD_Pt_20_30_EMEnriched_name,"MC_QCD_Pt_20_30_EMEnriched_histos_%d.root",itype);
	cout << "QCD file 21 is: " << QCD_Pt_20_30_EMEnriched_name << endl;
	sprintf(QCD_Pt_30_80_EMEnriched_name,"MC_QCD_Pt_30_80_EMEnriched_histos_%d.root",itype);
	cout << "QCD file 22 is: " << QCD_Pt_30_80_EMEnriched_name << endl;
	sprintf(QCD_Pt_80_170_EMEnriched_name,"MC_QCD_Pt_80_170_EMEnriched_histos_%d.root",itype);
	cout << "QCD file 23 is: " << QCD_Pt_80_170_EMEnriched_name << endl;
	sprintf(QCD_Pt_170_250_EMEnriched_name,"MC_QCD_Pt_170_250_EMEnriched_histos_%d.root",itype);
	cout << "QCD file 24 is: " << QCD_Pt_170_250_EMEnriched_name << endl;
	sprintf(QCD_Pt_250_350_EMEnriched_name,"MC_QCD_Pt_250_350_EMEnriched_histos_%d.root",itype);
	cout << "QCD file 25 is: " << QCD_Pt_250_350_EMEnriched_name << endl;
	sprintf(QCD_Pt_350_EMEnriched_name,"MC_QCD_Pt_350_EMEnriched_histos_%d.root",itype);
	cout << "QCD file 26 is: " << QCD_Pt_350_EMEnriched_name << endl;

	sprintf(QCD_Pt_20_30_BCtoE_name,"MC_QCD_Pt_20_30_BCtoE_histos_%d.root",itype);
	cout << "QCD file 31 is: " << QCD_Pt_20_30_BCtoE_name << endl;
	sprintf(QCD_Pt_30_80_BCtoE_name,"MC_QCD_Pt_30_80_BCtoE_histos_%d.root",itype);
	cout << "QCD file 32 is: " << QCD_Pt_30_80_BCtoE_name << endl;
	sprintf(QCD_Pt_80_170_BCtoE_name,"MC_QCD_Pt_80_170_BCtoE_histos_%d.root",itype);
	cout << "QCD file 33 is: " << QCD_Pt_80_170_BCtoE_name << endl;
	sprintf(QCD_Pt_170_250_BCtoE_name,"MC_QCD_Pt_170_250_BCtoE_histos_%d.root",itype);
	cout << "QCD file 34 is: " << QCD_Pt_170_250_BCtoE_name << endl;
	sprintf(QCD_Pt_250_350_BCtoE_name,"MC_QCD_Pt_250_350_BCtoE_histos_%d.root",itype);
	cout << "QCD file 35 is: " << QCD_Pt_250_350_BCtoE_name << endl;
	sprintf(QCD_Pt_350_BCtoE_name,"MC_QCD_Pt_350_BCtoE_histos_%d.root",itype);
	cout << "QCD file 36S is: " << QCD_Pt_350_BCtoE_name << endl;	
	
/*
	sprintf(QCD_HT_100To250_name,"mc_QCD_HT-100To250_histos_%d.root",itype);
	cout << "QCD file 1b is: " << QCD_HT_100To250_name << endl;
	sprintf(QCD_HT_250To500_name,"mc_QCD_HT-250To500_histos_%d.root",itype);
	cout << "QCD file 2b is: " << QCD_HT_250To500_name << endl;
	sprintf(QCD_HT_500To1000_name,"mc_QCD_HT-500To1000_histos_%d.root",itype);
	cout << "QCD file 3b is: " << QCD_HT_500To1000_name << endl;
	sprintf(QCD_HT_1000ToInf_name,"mc_QCD_HT-1000ToInf_histos_%d.root",itype);
	cout << "QCD file 4b is: " << QCD_HT_1000ToInf_name << endl;
*/


	TFile *DATA_Run2012A_13Jul2012_file = new TFile(DATA_Run2012A_13Jul2012_name);
	TFile *DATA_Run2012A_recover_06Aug2012_file = new TFile(DATA_Run2012A_recover_06Aug2012_name);
	TFile *DATA_Run2012B_13Jul2012_file = new TFile(DATA_Run2012B_13Jul2012_name);
	TFile *DATA_Run2012C_24Aug2012_file = new TFile(DATA_Run2012C_24Aug2012_name);
	TFile *DATA_Run2012C_EcalRecover_11Dec2012_file = new TFile(DATA_Run2012C_EcalRecover_11Dec2012_name);
	TFile *DATA_Run2012C_PromptReco_file = new TFile(DATA_Run2012C_PromptReco_name);
	TFile *DATA_Run2012D_PromptReco_file = new TFile(DATA_Run2012D_PromptReco_name);
	
	TFile *GJets_HT_200To400_file = new TFile(GJets_HT_200To400_name);
	TFile *GJets_HT_400ToInf_file = new TFile(GJets_HT_400ToInf_name); 
	TFile *QCD_Pt_20_30_EMEnriched_file = new TFile(QCD_Pt_20_30_EMEnriched_name); 
	TFile *QCD_Pt_30_80_EMEnriched_file = new TFile(QCD_Pt_30_80_EMEnriched_name);
	TFile *QCD_Pt_80_170_EMEnriched_file = new TFile(QCD_Pt_80_170_EMEnriched_name);
	TFile *QCD_Pt_170_250_EMEnriched_file = new TFile(QCD_Pt_170_250_EMEnriched_name);
	TFile *QCD_Pt_250_350_EMEnriched_file = new TFile(QCD_Pt_250_350_EMEnriched_name);
	TFile *QCD_Pt_350_EMEnriched_file = new TFile(QCD_Pt_350_EMEnriched_name);

	TFile *QCD_Pt_20_30_BCtoE_file = new TFile(QCD_Pt_20_30_BCtoE_name); 
	TFile *QCD_Pt_30_80_BCtoE_file = new TFile(QCD_Pt_30_80_BCtoE_name);
	TFile *QCD_Pt_80_170_BCtoE_file = new TFile(QCD_Pt_80_170_BCtoE_name);
	TFile *QCD_Pt_170_250_BCtoE_file = new TFile(QCD_Pt_170_250_BCtoE_name);
	TFile *QCD_Pt_250_350_BCtoE_file = new TFile(QCD_Pt_250_350_BCtoE_name);
	TFile *QCD_Pt_350_BCtoE_file = new TFile(QCD_Pt_350_BCtoE_name);

/*
	TFile *QCD_HT_100To250_file = new TFile(QCD_HT_100To250_name);  
	TFile *QCD_HT_250To500_file = new TFile(QCD_HT_250To500_name);   
	TFile *QCD_HT_500To1000_file = new TFile(QCD_HT_500To1000_name); 
	TFile *QCD_HT_1000ToInf_file = new TFile(QCD_HT_1000ToInf_name); 
*/


	Char_t titlehisto[100],titlecanvas[100];

	strcpy(titlehisto,titleh);
	cout << "Analyzing Histogram " << titlehisto << endl;


//--- data -----------------------------------------------------------------
	TH1F *DATA_Run2012A_13Jul2012_histo=(TH1F*)DATA_Run2012A_13Jul2012_file->Get(titlehisto);
	cout << "DATA_Run2012A_13Jul2012 entries = " << DATA_Run2012A_13Jul2012_histo->Integral() << endl;  
	TH1F *DATA_Run2012A_recover_06Aug2012_histo=(TH1F*)DATA_Run2012A_recover_06Aug2012_file->Get(titlehisto);
	cout << "DATA_Run2012A_recover_06Aug2012 entries = " << DATA_Run2012A_recover_06Aug2012_histo->Integral() << endl;  
	TH1F *DATA_Run2012B_13Jul2012_histo=(TH1F*)DATA_Run2012B_13Jul2012_file->Get(titlehisto);
	cout << "DATA_Run2012B_13Jul2012 entries = " << DATA_Run2012B_13Jul2012_histo->Integral() << endl;  
	TH1F *DATA_Run2012C_24Aug2012_histo=(TH1F*)DATA_Run2012C_24Aug2012_file->Get(titlehisto);
	cout << "DATA_Run2012C_24Aug2012 entries = " << DATA_Run2012C_24Aug2012_histo->Integral() << endl;  
	TH1F *DATA_Run2012C_EcalRecover_11Dec2012_histo=(TH1F*)DATA_Run2012C_EcalRecover_11Dec2012_file->Get(titlehisto);
	cout << "DATA_Run2012C_EcalRecover_11Dec2012 entries = " << DATA_Run2012C_EcalRecover_11Dec2012_histo->Integral() << endl;  
	TH1F *DATA_Run2012C_PromptReco_histo=(TH1F*)DATA_Run2012C_PromptReco_file->Get(titlehisto);
	cout << "DATA_Run2012C_PromptReco entries = " << DATA_Run2012C_PromptReco_histo->Integral() << endl;  
	TH1F *DATA_Run2012D_PromptReco_histo=(TH1F*)DATA_Run2012D_PromptReco_file->Get(titlehisto);
	cout << "DATA_Run2012D_PromptReco entries = " << DATA_Run2012D_PromptReco_histo->Integral() << endl;  

	TH1F *DATA_total_histo = (TH1F*) DATA_Run2012A_13Jul2012_histo->Clone("DATA_total_histo");
	DATA_total_histo->Add(DATA_Run2012A_recover_06Aug2012_histo);
	DATA_total_histo->Add(DATA_Run2012B_13Jul2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_24Aug2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_EcalRecover_11Dec2012_histo);
	DATA_total_histo->Add(DATA_Run2012C_PromptReco_histo);
	DATA_total_histo->Add(DATA_Run2012D_PromptReco_histo);
				
//--- MC signal GJets_HT-xToy ----------------------------------------------
	TH1F *GJets_HT_200To400_histo=(TH1F*)GJets_HT_200To400_file->Get(titlehisto);
	cout << "GJets_HT_200To400 entries = " << GJets_HT_200To400_histo->Integral() << endl;

	TH1F *GJets_HT_400ToInf_histo=(TH1F*)GJets_HT_400ToInf_file->Get(titlehisto);
	cout << "GJets_HT_400ToInf entries = " << GJets_HT_400ToInf_histo->Integral() << endl;

	TH1F *GJets_HT_xToy_total_histo = (TH1F*) GJets_HT_200To400_histo->Clone("GJets_HT_xToy_total_histo");
//--- GJets_HT_xToy_total_histo->Sumw2();
	GJets_HT_xToy_total_histo->Add(GJets_HT_400ToInf_histo);  
	GJets_HT_xToy_total_histo->SetLineColor(1);
	GJets_HT_xToy_total_histo->SetFillColor(5);  //for colors comment out Sumw2 in code

//--- MC background QCD_Pt_x_y EMEnriched ----------------------------------
	TH1F *QCD_Pt_20_30_EMEnriched_histo=(TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto);
	cout << "CD_Pt_20_30_EMEnriched entries = " << QCD_Pt_20_30_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_30_80_EMEnriched_histo=(TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto);
	cout << "QCD_Pt_30_80_EMEnriched entries = " << QCD_Pt_30_80_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_80_170_EMEnriched_histo=(TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto);
	cout << "QCD_Pt_80_170_EMEnriched entries = " << QCD_Pt_80_170_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_170_250_EMEnriched_histo=(TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto);
	cout << "QCD_Pt_170_250_EMEnriched entries = " << QCD_Pt_170_250_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_250_350_EMEnriched_histo=(TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto);
	cout << "QCD_Pt_250_350_EMEnriched entries = " << QCD_Pt_250_350_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_350_EMEnriched_histo=(TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto);
	cout << "QCD_Pt_350_EMEnriched entries = " << QCD_Pt_350_EMEnriched_histo->Integral() << endl;

	TH1F *QCD_Pt_x_y_EMEnriched_total_histo = (TH1F*) QCD_Pt_20_30_EMEnriched_histo->Clone("QCD_Pt_x_y_EMEnriched_total_histo");
//	QCD_Pt_x_y_EMEnriched_total_histo->Sumw2();
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_30_80_EMEnriched_histo);
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_80_170_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_170_250_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_250_350_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->Add(QCD_Pt_350_EMEnriched_histo);  
	QCD_Pt_x_y_EMEnriched_total_histo->SetLineColor(1);
	QCD_Pt_x_y_EMEnriched_total_histo->SetFillColor(kMagenta+2);


//--- MC background QCD_Pt_x_y BCtoE ----------------------------------
	TH1F *QCD_Pt_20_30_BCtoE_histo=(TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto);
	cout << "QCD_Pt_20_30_BCtoE entries = " << QCD_Pt_20_30_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_30_80_BCtoE_histo=(TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto);
	cout << "QCD_Pt_30_80_BCtoE entries = " << QCD_Pt_30_80_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_80_170_BCtoE_histo=(TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto);
	cout << "QCD_Pt_80_170_BCtoE entries = " << QCD_Pt_80_170_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_170_250_BCtoE_histo=(TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto);
	cout << "QCD_Pt_170_250_BCtoE entries = " << QCD_Pt_170_250_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_250_350_BCtoE_histo=(TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto);
	cout << "QCD_Pt_250_350_BCtoE entries = " << QCD_Pt_250_350_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_350_BCtoE_histo=(TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto);
	cout << "QCD_Pt_350_BCtoE entries = " << QCD_Pt_350_BCtoE_histo->Integral() << endl;

	TH1F *QCD_Pt_x_y_BCtoE_total_histo = (TH1F*) QCD_Pt_20_30_BCtoE_histo->Clone("QCD_Pt_x_y_BCtoE_total_histo");
//	QCD_Pt_x_y_BCtoE_total_histo->Sumw2();
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_30_80_BCtoE_histo);
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_80_170_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_170_250_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_250_350_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->Add(QCD_Pt_350_BCtoE_histo);  
	QCD_Pt_x_y_BCtoE_total_histo->SetLineColor(1);
	QCD_Pt_x_y_BCtoE_total_histo->SetFillColor(kBlue+2);

/*
// MC background QCD HT-xToy --------------------------------------------
	TH1F *QCD_HT_100To250_histo=(TH1F*)QCD_HT_100To250_file->Get(titlehisto);
	cout << "QCD file 1b entries " << QCD_HT_100To250_histo->Integral() << endl;  

	TH1F *QCD_HT_250To500_histo=(TH1F*)QCD_HT_250To500_file->Get(titlehisto);
	cout << "QCD file 2b entries " << QCD_HT_250To500_histo->Integral() << endl;  

	TH1F *QCD_HT_500To1000_histo=(TH1F*)QCD_HT_500To1000_file->Get(titlehisto);
	cout << "QCD file 3b entries " << QCD_HT_500To1000_histo->Integral() << endl;

	TH1F *QCD_HT_1000ToInf_histo=(TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto);
	cout << "QCD file 4b entries " << QCD_HT_1000ToInf_histo->Integral() << endl;

	QCD_HT_100To250_histo->SetLineColor(1);
	QCD_HT_100To250_histo->SetFillColor(kRed+2);
	QCD_HT_100To250_histo->Add(QCD_HT_250To500_histo);
	QCD_HT_100To250_histo->Add(QCD_HT_500To1000_histo);  
	QCD_HT_100To250_histo->Add(QCD_HT_1000ToInf_histo);  
*/

	cout << "GJets total entries = " << GJets_HT_xToy_total_histo->Integral() << endl;  
	cout << "QCD EMEnriched total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() << endl;  
	cout << "QCD BCtoE total entries = " << QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;
	cout << "QCD total entries = " << QCD_Pt_x_y_EMEnriched_total_histo->Integral() + QCD_Pt_x_y_BCtoE_total_histo->Integral() << endl;	 
//	cout << "QCD total entries = " << QCD_HT_100To250_histo->Integral() << endl;  


  TCanvas *Canva = new TCanvas(titlehisto,titlehisto);  
	TPad* upperPad = new TPad("upperPad", "upperPad",.005, .25, .995, .995);
  TPad* lowerPad = new TPad("lowerPad", "lowerPad",.005, .005, .995, .2475);
  upperPad->Draw(); 			       
  lowerPad->Draw(); 
  upperPad->cd();   
   // Canva->cd(1);
   // GJets_HT_200To400_histo->Draw();
   // gPad->SetLogy();
   // Canva->cd(2);
   // QCD_HT_100To250_histo->Draw();
   // gPad->SetLogy();

	THStack *MC_stack= new THStack();
//	MC_stack->Add(QCD_HT_100To250_histo);
	MC_stack->Add(QCD_Pt_x_y_BCtoE_total_histo);
	MC_stack->Add(QCD_Pt_x_y_EMEnriched_total_histo);
	MC_stack->Add(GJets_HT_xToy_total_histo);

	TH1F *ratio_histo_NUM = (TH1F*) DATA_total_histo->Clone("ratio_histo_NUM");
	ratio_histo_NUM->Sumw2();

	TH1F *ratio_histo_DEN = (TH1F*) GJets_HT_xToy_total_histo->Clone("ratio_histo_DEN");
	ratio_histo_DEN->Add(QCD_Pt_x_y_BCtoE_total_histo);	
	ratio_histo_DEN->Add(QCD_Pt_x_y_EMEnriched_total_histo);
	ratio_histo_DEN->Sumw2();
	
	TH1F *ratio_histo = (TH1F*) ratio_histo_NUM->Clone("ratio_histo");
	ratio_histo->Sumw2();
	ratio_histo->Divide(ratio_histo_DEN);

// Canva->cd(3);
// MC_stack->Draw("");
// gPad->SetLogy();
//	Canva->Divide(1,2,0.01,0.0001);
	
//	Canva->cd(1);
	DATA_total_histo->SetMarkerStyle(20);
	DATA_total_histo->SetMinimum(0.1);
	DATA_total_histo->Draw("E");
	MC_stack->Draw("SAME");
	DATA_total_histo->Draw("ESAME");
	gPad->SetLogy();
	DATA_total_histo->Draw("AXIS X+ Y+ SAME");
	DATA_total_histo->Draw("AXIS SAME");
	DATA_total_histo->GetXaxis()->SetTitle(namevariable);
	DATA_total_histo->GetXaxis()->SetTitleSize(0.05);
	DATA_total_histo->GetYaxis()->SetTitle("Events");
	//DATA_total_histo->GetYaxis()->SetTitleOffset(0.8);
	//DATA_total_histo->GetYaxis()->SetTitleSize(0.05);
	//DATA_total_histo->GetYaxis()->SetLabelSize(0.03);

	TLegend *leg =new TLegend(0.6068,0.5478,0.8188,0.7480);
	leg->SetFillColor(0); 
  leg->SetFillStyle(0); 
  leg->SetBorderSize(0);
	leg->AddEntry(DATA_total_histo,"Data","pL");
	leg->AddEntry(GJets_HT_xToy_total_histo,"#gamma + jets","f");
	leg->AddEntry(QCD_Pt_x_y_EMEnriched_total_histo,"QCD EMEnriched","f");
	leg->AddEntry(QCD_Pt_x_y_BCtoE_total_histo,"QCD BCtoE","f");
//	leg->AddEntry(QCD_HT_100To250_histo,"QCD","f");
	leg->Draw();

  TPaveText* text = new TPaveText(0.6068,0.7722,0.8188,0.8571,"NDC");
  text->SetFillColor(0);
  text->SetBorderSize(0);
  text->AddText("CMS Preliminary");
  text->AddText("#sqrt{s} = 8 TeV, L = 19.03 fb^{-1}");
  text->SetTextAlign(11);
  text->Draw();

	lowerPad-> cd();
//	Canva->cd(2);

	int xmin,xmax;
	xmin = ratio_histo->GetXaxis()->GetXmin();
	xmax = ratio_histo->GetXaxis()->GetXmax();

	ratio_histo->Draw("");
	TBox *box_1 = new TBox(xmin,0.9,xmax,1.1);
	box_1->SetFillColor(22);
	box_1->Draw();

	TBox *box_2 = new TBox(xmin,0.95,xmax,1.05);
	box_2->SetFillColor(14);
	box_2->Draw();


	ratio_histo->Draw("P E0 SAME");
	ratio_histo->Draw("AXIS X+ Y+ SAME");
	ratio_histo->Draw("AXIS SAME");
  ratio_histo->GetXaxis()->SetTitle("");
	ratio_histo->GetYaxis()->SetTitle("Ratio (Data/MC RECO)");
	ratio_histo->GetYaxis()->SetTitleSize(0.08);
	ratio_histo->GetYaxis()->SetTitleOffset(0.6);
	ratio_histo->GetYaxis()->SetLabelSize(0.1);
	ratio_histo->GetXaxis()->SetLabelSize(0.1);
	ratio_histo->GetYaxis()->SetRangeUser(0.75,1.25);
	ratio_histo->GetYaxis()->SetNdivisions(505, "kTRUE");
	ratio_histo->SetMarkerStyle(20);
	ratio_histo->SetMarkerColor(kBlue);
	ratio_histo->SetMarkerSize(0.7);
	ratio_histo->SetLineColor(kBlue);

  Canva->SaveAs((png_folder + titleh + png_string).c_str());
  Canva->SaveAs((root_folder + titleh + root_string).c_str());
	Canva->Close();

	//lowerPad->SetGridy(2);
}
