#define GJetsClass_cxx
#include "GJetsClass.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <Riostream.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "GJetsDefs.h"
#ifdef __MAKECINT__
#pragma link C++ class vector<float>+;
#endif


void GJetsClass::Loop(Int_t isample)
{
//   In a ROOT session, you can do:
//      Root > .L GJetsClass.C
//      Root > GJetsClass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch


  Float_t weight, weight_withPU;
  Int_t itype=0;   // dummy for the moment 

  // choose the sample:
  // isample==0 -> data
  // isample==1 -> GJets 40<HT<100
  // isample==2 -> Gjets 100<HT<200
  // isample==3 -> GJtes 200<HT<inf
  // isample==4 -> QCD   250<HT<500
  // isample==5 -> QCD   500<HT<1000
  // isample==6 -> QCD   1000<HT<inf

   double Lumi_t=5000.;  


  if(isample==0){
    sprintf(outputname,"Data_gammahistos_%d.root",itype);
   weight=1.;
   cout << "Running on data " << endl;
   cout<<"Integrated luminosity is "<<Lumi_t<<endl;
 }

  else if(isample==1){  // this sample irrelevant
    sprintf(outputname,"GJetsHT40-100_gammahistos_%d.root",itype);   //xsec=25690 pb * k-factor 1.23?
    // weight=1.;                                                       // temporary weight=1 for eff. calculation    
   weight=Lumi_t /(12730970./(25690*1.23));
   cout << "Running on GJets HT40-100 " << endl;

 }

  else if(isample==2){
    sprintf(outputname,"GJetsHT100-200_gammahistos_%d.root",itype);   //xsec=5213 pb *1.23?
    // weight=1.;                                             
   weight=Lumi_t /(1536287./(5213.*1.23));
   cout << "Running on GJets HT100-200 " << endl;
   cout << "weight is " << weight << endl;

 }

  else if(isample==3){
    sprintf(outputname,"GJetsHT200-inf_gammahistos_%d.root",itype);   //xsec=798.3 pb *1.23?
    // weight=1.;
    weight=Lumi_t /(9377170./(798.3*1.23));
   cout << "Running on GJets HT200-inf " << endl;

 }


  else if(isample==4){
    sprintf(outputname,"QCDHT250-500_gammahistos_%d.root",itype);   //xsec=198500
    // weight=1.;
    weight=Lumi_t /(20674220./(198500));
   cout << "Running on QCD HT250-500 " << endl;

 }
  else if(isample==5){
    sprintf(outputname,"QCDHT500-1000_gammahistos_%d.root",itype);   //xsec=5856
    // weight=1.;
    weight=Lumi_t /(14437470./(5856.));
   cout << "Running on QCD HT500-1000 " << endl;

 }
  else if(isample==6){
    sprintf(outputname,"QCDHT1000_gammahistos_%d.root",itype);   //xsec=198500
    // weight=1.;
    weight=Lumi_t /(6294851./(122.6));
   cout << "Running on QCD HT1000 " << endl;

 }



   if (fChain == 0) return;

   // ================ initialize and book histograms

TFile *fhistos= new TFile(outputname,"RECREATE");
Book_Histos();
iSelected=0;
iSelectedWithWeights=0;

   Long64_t nentries = fChain->GetEntriesFast();
   cout << "nentries " << nentries << endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

     if(jentry%100000==0)cout << jentry << endl;
     Zero_Variables();



     // ============ selection for photon at GEN level
     // if (selGEN && nPhotonsGEN>0 && photonPtGEN>150. && TMath::Abs(photonEtaGEN)<1.4442 && nJetsGEN>0) {

     // take request of jet, as done by Jessica
     if (selGEN && nPhotonsGEN>0 && photonPtGEN>150. && TMath::Abs(photonEtaGEN)<1.4442 ) {
          
       ptGENjet1=jetPtGEN->at(0);
       etaGENjet1=jetEtaGEN->at(0);

       // if(ptGENjet1>50. && TMath::Abs(etaGENjet1)<2.5){
       Bool_t DummyTrue=kTRUE;
       if(DummyTrue){
        ptPhotonGEN150_->Fill(photonPtGEN,1.);
        ptPhotonGEN200_->Fill(photonPtGEN,1.);


       // ======= now look here for reconstructed photon, do not require trigger and reconstructed jets at this point
          Int_t gammaID=photonID;
          if(nPhotons>0 && (gammaID&8) && (TMath::Abs(photonEta)<1.4442) && photonPt>150. ){
	    // Float_t DeltaR_GENREC=photonRECODRGEN;   // recompute it

            Float_t deta = photonEtaGEN - photonEta;
            Float_t dphi = deltaPhi(photonPhi, photonPhiGEN);
            Float_t drsquared= deta*deta + dphi*dphi;
            Float_t DeltaR_GENREC= TMath::Sqrt(drsquared);
            // if(jentry<10) cout << "deta " << deta << endl;
            // if(jentry<10) cout << "dphi " << deta << endl;
            // if(jentry<10) cout << "DeltaR_GENREC " << DeltaR_GENREC << endl;
            DeltaRGENREC_->Fill(DeltaR_GENREC,1.); // why such a small number?
            if(DeltaR_GENREC<0.1) {
              
             ptPhotonREC150_->Fill(photonPtGEN,1.);
             ptPhotonREC200_->Fill(photonPtGEN,1.);


	    }  // end if DeltaR matching GEN-REC cut
	  }  // end RECO cuts on photons

       } // end GEN cuts n jets  
     }  // end GEN cuts

     // ============ selection for photons at RECO level for control plots

      if(selRECO && nPhotons>0 && nJets>0 && (8 & isTriggered) ){//

	

     // =========== add stricter selection here
     // at least one jet with pt>50 GeV, VgammaID cuts (photonID |= isVgamma2011 << 3;)
     // and that the photon is in the barrel (photonBit |= (it->isEB()          << 0)
     // and has a pt greater than 150.;

       // jet1
       ptjet1=jetPt->at(0);
       etajet1=jetEta->at(0);
       phijet1=jetPhi->at(0);           
       Int_t gammaID=photonID;
       // if (ptjet1>50. && TMath::Abs(etajet1)<2.5 && (gammaID&8) && (photonBit&1) ){
       if (ptjet1>50. && TMath::Abs(etajet1)<2.5 && (gammaID&8) && (TMath::Abs(photonEta)<1.4442) && photonPt>150. ){


 // ======= weight
        if(isample==0){  //data
          weight_withPU=1.;
       }
        else{   // MC         
          weight_withPU=PUWeight*Lumi_t/1000.;
	  // this weight includes pileup, as calculated by Andrea, and the 1.23 k-factor for the Gamma samples
	}


        iSelected++;
        iSelectedWithWeights=iSelectedWithWeights+weight_withPU;

        ptPhoton_->Fill(photonPt,weight_withPU);
        etaPhoton_->Fill(photonEta,weight_withPU);
        Nvtx_->Fill(nVtx,weight_withPU);
       }  // end if selection with 1 jet

      // if (Cut(ientry) < 0) continue;
      } // end if preselection

   }   // end loop on entries

 // ====================================terminate and plot
 cout << "Number of selected events, unweighted " << iSelected << endl;
 cout << "Number of selected events Only one type and ptjet1>50, weighted " << iSelected*weight << endl;
 cout << "weighted for PU " << iSelectedWithWeights << endl;
 

   fhistos->Write();
   Plot_Histos();  
 

}




void Book_Histos(){

  cout << "Booking histograms .. " << endl;
  // book the histograms

 Nvtx_= new TH1F("Nvtx_","Number of vertices ",50,0,50);
 ptPhoton_= new TH1F("ptPhoton_","P_t of the photon ",100,0.,1000.);
 etaPhoton_= new TH1F("etaPhoton_","#eta of the photon ",100,-5.,5.);

 DeltaRGENREC_=new TH1F("DeltaRGENREC_","DeltaR Gen-REC photon",50,0.,0.01);
 ptPhotonGEN150_= new TH1F("ptPhotonGEN150_","P_t of the generated photon ",2,150.,200.);
 ptPhotonREC150_= new TH1F("ptPhotonREC150_","P_t of the generated&reconstructed photon ",2,150.,200.);
 ptPhotonGEN200_= new TH1F("ptPhotonGEN200_","P_t of the generated photon ",4,200.,1000.);
 ptPhotonREC200_= new TH1F("ptPhotonREC200_","P_t of the generated&reconstructed photon ",4,200.,1000.);


 // ptPhoton_->Sumw2();
 // etaPhoton_->Sumw2();

}

void Plot_Histos(){

  // plot few histograms at the end, for check


cout << "Plot, quick check " << endl;

 
gStyle->SetOptStat(1111111);
TCanvas *c111=new TCanvas("c111","General",10,10,700,700);
c111->Divide(2,3);
c111->cd(1);
ptPhoton_->Draw();
gPad->SetLogy();
c111->cd(3);
etaPhoton_->Draw();
c111->cd(4);
Nvtx_->Draw();
c111->cd(5);
DeltaRGENREC_->Draw();



TCanvas *c222=new TCanvas("c222","Efficiencies",10,10,700,700);
c222->Divide(2,3);
c222->cd(1);
ptPhotonREC150_->Draw();
gPad->SetLogy();
c222->cd(2);
ptPhotonREC200_->Draw();
gPad->SetLogy();
c222->cd(3);
ptPhotonGEN150_->Draw();
gPad->SetLogy();
c222->cd(4);
ptPhotonGEN200_->Draw();
gPad->SetLogy();
c222->cd(5);
TH1F *efficiency150 = (TH1F*) ptPhotonREC150_->Clone();
efficiency150->Divide(ptPhotonGEN150_);
efficiency150->Draw();
c222->cd(6);
TH1F *efficiency200 = (TH1F*) ptPhotonREC200_->Clone();
efficiency200->Divide(ptPhotonGEN200_);
efficiency200->Draw();

}






 float deltaPhi(float phi1, float phi2) { 
     float result = phi1 - phi2;
     while (result > TMath::Pi()) result -= float(2.*TMath::Pi());
     while (result <= -TMath::Pi()) result += float(2.*TMath::Pi());
     float absresult=TMath::Abs(result);
     return absresult;
   }



void Zero_Variables(){


}
