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

//	Char_t GJets_HT_40To100_name[100];
	Char_t GJets_HT_100To200_name[100];							
	Char_t GJets_HT_200To400_name[100];
	Char_t GJets_HT_400ToInf_name[100];
	
	Char_t G_Pt_15to30_name[100];
	Char_t G_Pt_30to50_name[100];
	Char_t G_Pt_50to80_name[100];
	Char_t G_Pt_80to120_name[100];	
	Char_t G_Pt_120to170_name[100];
	Char_t G_Pt_170to300_name[100];	
	Char_t G_Pt_300to470_name[100];
	Char_t G_Pt_470to800_name[100];
	Char_t G_Pt_800to1400_name[100];
	Char_t G_Pt_1400to1800_name[100];
	Char_t G_Pt_1800_name[100];

	Char_t DiPhotonJets_name[100];

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
	
	Char_t QCD_HT_100To250_name[100];
	Char_t QCD_HT_250To500_name[100];
	Char_t QCD_HT_500To1000_name[100];
	Char_t QCD_HT_1000ToInf_name[100];

 
  Char_t titlehisto[100] = "accepted/XSec";


//	sprintf(GJets_HT_40To100_name,"samples/GJets_HT-40To100_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V19-v1.root");
	sprintf(GJets_HT_100To200_name,"samples/GJets_HT-100To200_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V19-v1.root");
	sprintf(GJets_HT_200To400_name,"samples/GJets_HT-200To400_8TeV-madgraph_v2_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(GJets_HT_400ToInf_name,"samples/GJets_HT-400ToInf_8TeV-madgraph_v3_Summer12_DR53X-PU_S10_START53_V7C-v1.root");
	sprintf(G_Pt_15to30_name,"samples/G_Pt-15to30_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_30to50_name,"samples/G_Pt-30to50_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_50to80_name,"samples/G_Pt-50to80_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_80to120_name,"samples/G_Pt-80to120_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_120to170_name,"samples/G_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");	
	sprintf(G_Pt_170to300_name,"samples/G_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_300to470_name,"samples/G_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");	
	sprintf(G_Pt_470to800_name,"samples/G_Pt-470to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_800to1400_name,"samples/G_Pt-800to1400_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_1400to1800_name,"samples/G_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(G_Pt_1800_name,"samples/G_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(DiPhotonJets_name,"samples/DiPhotonJets_8TeV-madgraph-tarball-v2_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_20_30_EMEnriched_name,"samples/QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_30_80_EMEnriched_name,"samples/QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");	
	sprintf(QCD_Pt_80_170_EMEnriched_name,"samples/QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_170_250_EMEnriched_name,"samples/QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_250_350_EMEnriched_name,"samples/QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_350_EMEnriched_name,"samples/QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");	
	sprintf(QCD_Pt_20_30_BCtoE_name,"samples/QCD_Pt_20_30_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_30_80_BCtoE_name,"samples/QCD_Pt_30_80_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");	
	sprintf(QCD_Pt_80_170_BCtoE_name,"samples/QCD_Pt_80_170_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_170_250_BCtoE_name,"samples/QCD_Pt_170_250_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_250_350_BCtoE_name,"samples/QCD_Pt_250_350_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_Pt_350_BCtoE_name,"samples/QCD_Pt_350_BCtoE_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2.root");	
	sprintf(QCD_HT_100To250_name,"samples/QCD_HT-100To250_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_HT_250To500_name,"samples/QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_HT_500To1000_name,"samples/QCD_HT-500To1000_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
	sprintf(QCD_HT_1000ToInf_name,"samples/QCD_HT-1000ToInf_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");


//	TFile *GJets_HT_40To100_file = new TFile(GJets_HT_40To100_name);
	TFile *GJets_HT_100To200_file = new TFile(GJets_HT_100To200_name);
	TFile *GJets_HT_200To400_file = new TFile(GJets_HT_200To400_name);
	TFile *GJets_HT_400ToInf_file = new TFile(GJets_HT_400ToInf_name); 
	TFile *G_Pt_15to30_file = new TFile(G_Pt_15to30_name);
	TFile *G_Pt_30to50_file = new TFile(G_Pt_30to50_name);
	TFile *G_Pt_50to80_file = new TFile(G_Pt_50to80_name);
	TFile *G_Pt_80to120_file = new TFile(G_Pt_80to120_name);
	TFile *G_Pt_120to170_file = new TFile(G_Pt_120to170_name);
	TFile *G_Pt_170to300_file = new TFile(G_Pt_170to300_name);
	TFile *G_Pt_300to470_file = new TFile(G_Pt_300to470_name);
	TFile *G_Pt_470to800_file = new TFile(G_Pt_470to800_name);
	TFile *G_Pt_800to1400_file = new TFile(G_Pt_800to1400_name);
	TFile *G_Pt_1400to1800_file = new TFile(G_Pt_1400to1800_name);
	TFile *G_Pt_1800_file = new TFile(G_Pt_1800_name);
	TFile *DiPhotonJets_file = new TFile(DiPhotonJets_name);
	TFile *QCD_Pt_20_30_EMEnriched_file  = new TFile(QCD_Pt_20_30_EMEnriched_name); 
	TFile *QCD_Pt_30_80_EMEnriched_file  = new TFile(QCD_Pt_30_80_EMEnriched_name); 
	TFile *QCD_Pt_80_170_EMEnriched_file  = new TFile(QCD_Pt_80_170_EMEnriched_name); 
	TFile *QCD_Pt_170_250_EMEnriched_file  = new TFile(QCD_Pt_170_250_EMEnriched_name); 
	TFile *QCD_Pt_250_350_EMEnriched_file  = new TFile(QCD_Pt_250_350_EMEnriched_name); 
	TFile *QCD_Pt_350_EMEnriched_file  = new TFile(QCD_Pt_350_EMEnriched_name); 
	TFile *QCD_Pt_20_30_BCtoE_file  = new TFile(QCD_Pt_20_30_BCtoE_name); 
	TFile *QCD_Pt_30_80_BCtoE_file  = new TFile(QCD_Pt_30_80_BCtoE_name); 
	TFile *QCD_Pt_80_170_BCtoE_file  = new TFile(QCD_Pt_80_170_BCtoE_name); 
	TFile *QCD_Pt_170_250_BCtoE_file  = new TFile(QCD_Pt_170_250_BCtoE_name); 
	TFile *QCD_Pt_250_350_BCtoE_file  = new TFile(QCD_Pt_250_350_BCtoE_name); 
	TFile *QCD_Pt_350_BCtoE_file  = new TFile(QCD_Pt_350_BCtoE_name); 
	TFile *QCD_HT_100To250_file   = new TFile(QCD_HT_100To250_name);  
	TFile *QCD_HT_250To500_file   = new TFile(QCD_HT_250To500_name);   
	TFile *QCD_HT_500To1000_file  = new TFile(QCD_HT_500To1000_name); 
	TFile *QCD_HT_1000ToInf_file  = new TFile(QCD_HT_1000ToInf_name); 


//	TH1F *GJets_HT_40To100_histo = (TH1F*)GJets_HT_40To100_file->Get(titlehisto);
	TH1F *GJets_HT_100To200_histo = (TH1F*)GJets_HT_100To200_file->Get(titlehisto);
	TH1F *GJets_HT_200To400_histo = (TH1F*)GJets_HT_200To400_file->Get(titlehisto);
	TH1F *GJets_HT_400ToInf_histo = (TH1F*)GJets_HT_400ToInf_file->Get(titlehisto);
	TH1F *G_Pt_15to30_histo  = (TH1F*)G_Pt_15to30_file->Get(titlehisto);
	TH1F *G_Pt_30to50_histo  = (TH1F*)G_Pt_30to50_file->Get(titlehisto);
	TH1F *G_Pt_50to80_histo  = (TH1F*)G_Pt_50to80_file->Get(titlehisto);
	TH1F *G_Pt_80to120_histo  = (TH1F*)G_Pt_80to120_file->Get(titlehisto);
	TH1F *G_Pt_120to170_histo  = (TH1F*)G_Pt_120to170_file->Get(titlehisto);
	TH1F *G_Pt_170to300_histo  = (TH1F*)G_Pt_170to300_file->Get(titlehisto);
	TH1F *G_Pt_300to470_histo  = (TH1F*)G_Pt_300to470_file->Get(titlehisto);
	TH1F *G_Pt_470to800_histo  = (TH1F*)G_Pt_470to800_file->Get(titlehisto);	
	TH1F *G_Pt_800to1400_histo  = (TH1F*)G_Pt_800to1400_file->Get(titlehisto);		
	TH1F *G_Pt_1400to1800_histo  = (TH1F*)G_Pt_1400to1800_file->Get(titlehisto);	
	TH1F *G_Pt_1800_histo  = (TH1F*)G_Pt_1800_file->Get(titlehisto);				
	TH1F *DiPhotonJets_histo = (TH1F*)DiPhotonJets_file->Get(titlehisto);	
	TH1F *QCD_Pt_20_30_EMEnriched_histo    = (TH1F*)QCD_Pt_20_30_EMEnriched_file->Get(titlehisto);
	TH1F *QCD_Pt_30_80_EMEnriched_histo    = (TH1F*)QCD_Pt_30_80_EMEnriched_file->Get(titlehisto);
	TH1F *QCD_Pt_80_170_EMEnriched_histo   = (TH1F*)QCD_Pt_80_170_EMEnriched_file->Get(titlehisto);
	TH1F *QCD_Pt_170_250_EMEnriched_histo  = (TH1F*)QCD_Pt_170_250_EMEnriched_file->Get(titlehisto);
	TH1F *QCD_Pt_250_350_EMEnriched_histo  = (TH1F*)QCD_Pt_250_350_EMEnriched_file->Get(titlehisto);
	TH1F *QCD_Pt_350_EMEnriched_histo      = (TH1F*)QCD_Pt_350_EMEnriched_file->Get(titlehisto);
	TH1F *QCD_Pt_20_30_BCtoE_histo    = (TH1F*)QCD_Pt_20_30_BCtoE_file->Get(titlehisto);
	TH1F *QCD_Pt_30_80_BCtoE_histo    = (TH1F*)QCD_Pt_30_80_BCtoE_file->Get(titlehisto);
	TH1F *QCD_Pt_80_170_BCtoE_histo   = (TH1F*)QCD_Pt_80_170_BCtoE_file->Get(titlehisto);
	TH1F *QCD_Pt_170_250_BCtoE_histo  = (TH1F*)QCD_Pt_170_250_BCtoE_file->Get(titlehisto);
	TH1F *QCD_Pt_250_350_BCtoE_histo  = (TH1F*)QCD_Pt_250_350_BCtoE_file->Get(titlehisto);
	TH1F *QCD_Pt_350_BCtoE_histo      = (TH1F*)QCD_Pt_350_BCtoE_file->Get(titlehisto);
	TH1F *QCD_HT_100To250_histo   = (TH1F*)QCD_HT_100To250_file->Get(titlehisto);
	TH1F *QCD_HT_250To500_histo   = (TH1F*)QCD_HT_250To500_file->Get(titlehisto);
	TH1F *QCD_HT_500To1000_histo  = (TH1F*)QCD_HT_500To1000_file->Get(titlehisto);
	TH1F *QCD_HT_1000ToInf_histo  = (TH1F*)QCD_HT_1000ToInf_file->Get(titlehisto);

  double /*XSec_GJets_HT_40To100,*/ XSec_GJets_HT_100To200, XSec_GJets_HT_200To400, XSec_GJets_HT_400ToInf, 
         XSec_G_Pt_15to30, XSec_G_Pt_30to50, XSec_G_Pt_50to80, XSec_G_Pt_80to120, XSec_G_Pt_120to170, XSec_G_Pt_170to300,
         XSec_G_Pt_300to470, XSec_G_Pt_470to800, XSec_G_Pt_800to1400, XSec_G_Pt_1400to1800, XSec_G_Pt_1800,
         XSec_DiPhotonJets,
         XSec_QCD_Pt_20_30_EMEnriched, XSec_QCD_Pt_30_80_EMEnriched, XSec_QCD_Pt_80_170_EMEnriched,
         XSec_QCD_Pt_170_250_EMEnriched, XSec_QCD_Pt_250_350_EMEnriched, XSec_QCD_Pt_350_EMEnriched, 
         XSec_QCD_Pt_20_30_BCtoE, XSec_QCD_Pt_30_80_BCtoE, XSec_QCD_Pt_80_170_BCtoE, XSec_QCD_Pt_170_250_BCtoE,
         XSec_QCD_Pt_250_350_BCtoE, XSec_QCD_Pt_350_BCtoE,
         XSec_QCD_HT_100To250, XSec_QCD_HT_250To500, XSec_QCD_HT_500To1000, XSec_QCD_HT_1000ToInf;  

//  XSec_GJets_HT_40To100 = GJets_HT_40To100_histo->GetBinContent(1)/GJets_HT_40To100_histo->GetBinContent(2);
  XSec_GJets_HT_100To200 = GJets_HT_100To200_histo->GetBinContent(1)/GJets_HT_100To200_histo->GetBinContent(2);
  XSec_GJets_HT_200To400 = GJets_HT_200To400_histo->GetBinContent(1)/GJets_HT_200To400_histo->GetBinContent(2);
  XSec_GJets_HT_400ToInf = GJets_HT_400ToInf_histo->GetBinContent(1)/GJets_HT_400ToInf_histo->GetBinContent(2); 
	XSec_G_Pt_15to30 = G_Pt_15to30_histo->GetBinContent(1)/G_Pt_15to30_histo->GetBinContent(2);
 	XSec_G_Pt_30to50 = G_Pt_30to50_histo->GetBinContent(1)/G_Pt_30to50_histo->GetBinContent(2);  
	XSec_G_Pt_50to80 = G_Pt_50to80_histo->GetBinContent(1)/G_Pt_50to80_histo->GetBinContent(2);
	XSec_G_Pt_80to120 = G_Pt_80to120_histo->GetBinContent(1)/G_Pt_80to120_histo->GetBinContent(2);
	XSec_G_Pt_120to170 = G_Pt_120to170_histo->GetBinContent(1)/G_Pt_120to170_histo->GetBinContent(2);
	XSec_G_Pt_170to300 = G_Pt_170to300_histo->GetBinContent(1)/G_Pt_170to300_histo->GetBinContent(2);
	XSec_G_Pt_300to470 = G_Pt_300to470_histo->GetBinContent(1)/G_Pt_300to470_histo->GetBinContent(2);
	XSec_G_Pt_470to800 = G_Pt_470to800_histo->GetBinContent(1)/G_Pt_470to800_histo->GetBinContent(2);
	XSec_G_Pt_800to1400 = G_Pt_800to1400_histo->GetBinContent(1)/G_Pt_800to1400_histo->GetBinContent(2);
	XSec_G_Pt_1400to1800 = G_Pt_1400to1800_histo->GetBinContent(1)/G_Pt_1400to1800_histo->GetBinContent(2);
	XSec_G_Pt_1800 = G_Pt_1800_histo->GetBinContent(1)/G_Pt_1800_histo->GetBinContent(2);
	XSec_DiPhotonJets = DiPhotonJets_histo->GetBinContent(1)/DiPhotonJets_histo->GetBinContent(2);
  XSec_QCD_Pt_20_30_EMEnriched = QCD_Pt_20_30_EMEnriched_histo->GetBinContent(1)/QCD_Pt_20_30_EMEnriched_histo->GetBinContent(2);
  XSec_QCD_Pt_30_80_EMEnriched = QCD_Pt_30_80_EMEnriched_histo->GetBinContent(1)/QCD_Pt_30_80_EMEnriched_histo->GetBinContent(2);
  XSec_QCD_Pt_80_170_EMEnriched = QCD_Pt_80_170_EMEnriched_histo->GetBinContent(1)/QCD_Pt_80_170_EMEnriched_histo->GetBinContent(2);
  XSec_QCD_Pt_170_250_EMEnriched = QCD_Pt_170_250_EMEnriched_histo->GetBinContent(1)/QCD_Pt_170_250_EMEnriched_histo->GetBinContent(2);
  XSec_QCD_Pt_250_350_EMEnriched = QCD_Pt_250_350_EMEnriched_histo->GetBinContent(1)/QCD_Pt_250_350_EMEnriched_histo->GetBinContent(2);
  XSec_QCD_Pt_350_EMEnriched = QCD_Pt_350_EMEnriched_histo->GetBinContent(1)/QCD_Pt_350_EMEnriched_histo->GetBinContent(2);
  XSec_QCD_Pt_20_30_BCtoE = QCD_Pt_20_30_BCtoE_histo->GetBinContent(1)/QCD_Pt_20_30_BCtoE_histo->GetBinContent(2);
  XSec_QCD_Pt_30_80_BCtoE = QCD_Pt_30_80_BCtoE_histo->GetBinContent(1)/QCD_Pt_30_80_BCtoE_histo->GetBinContent(2);
  XSec_QCD_Pt_80_170_BCtoE = QCD_Pt_80_170_BCtoE_histo->GetBinContent(1)/QCD_Pt_80_170_BCtoE_histo->GetBinContent(2);
  XSec_QCD_Pt_170_250_BCtoE = QCD_Pt_170_250_BCtoE_histo->GetBinContent(1)/QCD_Pt_170_250_BCtoE_histo->GetBinContent(2);
  XSec_QCD_Pt_250_350_BCtoE = QCD_Pt_250_350_BCtoE_histo->GetBinContent(1)/QCD_Pt_250_350_BCtoE_histo->GetBinContent(2);
  XSec_QCD_Pt_350_BCtoE = QCD_Pt_350_BCtoE_histo->GetBinContent(1)/QCD_Pt_350_BCtoE_histo->GetBinContent(2);
  XSec_QCD_HT_100To250 = QCD_HT_100To250_histo->GetBinContent(1)/QCD_HT_100To250_histo->GetBinContent(2);
  XSec_QCD_HT_250To500 = QCD_HT_250To500_histo->GetBinContent(1)/QCD_HT_250To500_histo->GetBinContent(2);
  XSec_QCD_HT_500To1000 = QCD_HT_500To1000_histo->GetBinContent(1)/QCD_HT_500To1000_histo->GetBinContent(2);
  XSec_QCD_HT_1000ToInf = QCD_HT_1000ToInf_histo->GetBinContent(1)/QCD_HT_1000ToInf_histo->GetBinContent(2);

	cout << endl;		
//	cout << "XSec GJets_HT-40To100 = " << XSec_GJets_HT_40To100 << " /pb" << endl;  
	cout << "XSec GJets_HT-100To200 = " << XSec_GJets_HT_100To200 << " /pb" << endl;
	cout << "XSec GJets_HT-200To400 = " << XSec_GJets_HT_200To400 << " /pb" << endl;  
	cout << "XSec GJets_HT-400ToInf = " << XSec_GJets_HT_400ToInf << " /pb" << endl;
	cout << endl;
	cout << "XSec G_Pt_15to30 = " << XSec_G_Pt_15to30 << " /pb" << endl;  
	cout << "XSec G_Pt_30to50 = " << XSec_G_Pt_30to50 << " /pb" << endl;  
	cout << "XSec G_Pt_50to80 = " << XSec_G_Pt_50to80 << " /pb" << endl;  
	cout << "XSec G_Pt_80to120 = " << XSec_G_Pt_80to120 << " /pb" << endl;  
	cout << "XSec G_Pt_120to170 = " << XSec_G_Pt_120to170 << " /pb" << endl;  
	cout << "XSec G_Pt_170to300 = " << XSec_G_Pt_170to300 << " /pb" << endl;  
	cout << "XSec G_Pt_300to470 = " << XSec_G_Pt_300to470 << " /pb" << endl;  
	cout << "XSec G_Pt_470to800 = " << XSec_G_Pt_470to800 << " /pb" << endl;  
	cout << "XSec G_Pt_800to1400 = " << XSec_G_Pt_800to1400 << " /pb" << endl;  
	cout << "XSec G_Pt_1400to1800 = " << XSec_G_Pt_1400to1800 << " /pb" << endl;  	
	cout << "XSec G_Pt_1800 = " << XSec_G_Pt_1800 << " /pb" << endl;
	cout << endl;
	cout << "XSec DiPhotonJets = " << XSec_DiPhotonJets << " /pb" << endl;
	cout << endl;
	cout << "XSec QCD_Pt_20_30_EMEnriched = " << XSec_QCD_Pt_20_30_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_30_80_EMEnriched = " << XSec_QCD_Pt_30_80_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_80_170_EMEnriched = " << XSec_QCD_Pt_80_170_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_170_250_EMEnriched = " << XSec_QCD_Pt_170_250_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_250_350_EMEnriched = " << XSec_QCD_Pt_250_350_EMEnriched << " /pb" << endl;  
	cout << "XSec QCD_Pt_350_EMEnriched = " << XSec_QCD_Pt_350_EMEnriched << " /pb" << endl;  				
	cout << endl;
	cout << "XSec QCD_Pt_20_30_BCtoE = " << XSec_QCD_Pt_20_30_BCtoE << " /pb" << endl;  
	cout << "XSec QCD_Pt_30_80_BCtoE = " << XSec_QCD_Pt_30_80_BCtoE << " /pb" << endl;  
	cout << "XSec QCD_Pt_80_170_BCtoE = " << XSec_QCD_Pt_80_170_BCtoE << " /pb" << endl;  
	cout << "XSec QCD_Pt_170_250_BCtoE = " << XSec_QCD_Pt_170_250_BCtoE << " /pb" << endl;  
	cout << "XSec QCD_Pt_250_350_BCtoE = " << XSec_QCD_Pt_250_350_BCtoE << " /pb" << endl;  
	cout << "XSec QCD_Pt_350_BCtoE = " << XSec_QCD_Pt_350_BCtoE << " /pb" << endl;  				
	cout << endl;
	cout << "XSec QCD_HT-100To250 = " << XSec_QCD_HT_100To250 << " /pb" << endl;  
	cout << "XSec QCD_HT-250To500 = " << XSec_QCD_HT_250To500 << " /pb" << endl;  	
	cout << "XSec QCD_HT-500To1000 = " << XSec_QCD_HT_500To1000 << " /pb" << endl;  
	cout << "XSec QCD_HT-1000ToInf = " << XSec_QCD_HT_1000ToInf << " /pb" << endl;  
	cout << endl;
}
