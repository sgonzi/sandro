// put definitions here

#include <TH1F.h>
#include <vector>
// histograms
/*
TH1F *ptPhotonGEN_, *ptPhotonREC_; 
TH1F *DeltaRGENREC_;

TH1F *Nvtx_;
TH1F *nPhotons_;
TH1F *nJets_;
TH1F *ptPhoton_, *etaPhoton_, *phiPhoton_, photonPassConversionVeto_, ;
TH1F *ptjet1_, *etajet1_, *phijet1_;
*/

TH1F  *ptPhotonGEN_, *ptPhotonREC_, *DeltaRGENREC_, 
			*Nvtx_, 
			*nPhotons_,
			*isPhotonlead_,
			*photonPt_1_,
			*photonE_1_,
			*photonEta_1_, 
			*photonPhi_1_, 
			*photonBit_1_,
			*photonPassConversionVeto_1_, 
			*photonPfIsoChargedHad_1_, 
			*photonPfIsoNeutralHad_1_, 
			*photonPfIsoPhoton_1_, 
			*photonPfIsoPhotons03ForCic_1_, 
			*photonPfIsoNeutrals03ForCic_1_, 
			*photonPfIsoCharged03ForCicVtx0_1_,
			*photonPfIsoCharged03BadForCic_1_, 
			*photonPfIsoPhotons04ForCic_1_, 
			*photonPfIsoNeutrals04ForCic_1_,
			*photonPfIsoCharged04ForCicVtx0_1_, 
			*photonPfIsoCharged04BadForCic_1_,
			*photonid_sieie_1_,  
			*photonid_sieip_1_, 
			*photonid_etawidth_1_, 
			*photonid_phiwidth_1_, 
			*photonid_r9_1_, 
			*photonid_lambdaRatio_1_, 
			*photonid_s4Ratio_1_,
			*photonid_e25_1_, 
			*photonid_sceta_1_, 
			*photonid_ESEffSigmaRR_1_, 
			*photonid_hadronicOverEm_1_, 
			*photonid_hadronicOverEm2012_1_,
			*photonhcalTowerSumEtConeDR04_1_, 
			*photonecalRecHitSumEtConeDR04_1_, 
			*photonnTrkSolidConeDR04_1_,
			*photontrkSumPtSolidConeDR04_1_, 
			*photonnTrkHollowConeDR04_1_, 
			*photontrkSumPtHollowConeDR04_1_, 
			//PhotonIso_1_,
			*photonIsoFPRCharged_1_, 
			*photonIsoFPRNeutral_1_, 
			*photonIsoFPRPhoton_1_, /**jetPhotonDPhi_,*/ 
			*nJets_, 
			*jetPt_1_, 
			*jetEta_1_, 
			*jetY_1_,
			*jetPhi_1_, 
			*jetE_1_,
			*jetPt_2_, 
			*jetEta_2_, 
			*jetY_2_,
			*jetPhi_2_, 
			*jetE_2_,
			*jetPt_3_, 
			*jetEta_3_, 
			*jetY_3_,
			*jetPhi_3_, 
			*jetE_3_,
			*DeltaR_photon1_jet1_,
			*DeltaPhi_photon1_jet1_,
			*DeltaR_photon1_jet2_,
			*DeltaEta_jet1_jet2_,
			*DeltaPhi_jet1_jet2_,				
			*DeltaR_photon1_jet3_,
			*HT_;
			
//  ptPhoton_->Sumw2();
//  etaPhoton_->Sumw2();
//  phiPhoton_->Sumw2();

void Book_Histos();
void Plot_Histos();
void Zero_Variables();
void Text_File();
float deltaEta(float, float);
float deltaPhi(float, float);
float deltaR(float, float, float, float);

// variables
Float_t weight_r, weight_withPU_r;
string  sample_r;
Long64_t nentries_r;
Char_t  outputname[100];
Char_t  textname[100];
Int_t		isPhotonlead, photonBit_1;
Float_t //GENjet1, etaGENjet1,
				//PhotonGEN_, *ptPhotonREC_, *DeltaRGENREC_, 
				Nvtx, 
				nPhotons,
				photonPt_1,
				photonE_1,
				photonEta_1, 
				photonPhi_1, 
				photonPassConversionVeto_1, 
				photonPfIsoChargedHad_1, 
				photonPfIsoNeutralHad_1, 
				photonPfIsoPhoton_1, 
				photonPfIsoPhotons03ForCic_1, 
				photonPfIsoNeutrals03ForCic_1, 
				photonPfIsoCharged03ForCicVtx0_1,
				photonPfIsoCharged03BadForCic_1, 
				photonPfIsoPhotons04ForCic_1, 
				photonPfIsoNeutrals04ForCic_1,
				photonPfIsoCharged04ForCicVtx0_1, 
				photonPfIsoCharged04BadForCic_1,
				photonid_sieie_1,  
				photonid_sieip_1, 
				photonid_etawidth_1, 
				photonid_phiwidth_1, 
				photonid_r9_1, 
				photonid_lambdaRatio_1, 
				photonid_s4Ratio_1,
				photonid_e25_1, 
				photonid_sceta_1, 
				photonid_ESEffSigmaRR_1, 
				photonid_hadronicOverEm_1, 
				photonid_hadronicOverEm2012_1,
				photonhcalTowerSumEtConeDR04_1, 
				photonecalRecHitSumEtConeDR04_1, 
				photonnTrkSolidConeDR04_1,
				photontrkSumPtSolidConeDR04_1, 
				photonnTrkHollowConeDR04_1, 
				photontrkSumPtHollowConeDR04_1, 
				//PhotonIso_1,
				photonIsoFPRCharged_1, 
				photonIsoFPRNeutral_1, 
				photonIsoFPRPhoton_1,
				/**jetPhotonDPhi_,*/ 
				nJets, 
				jetPt_1, 
				jetEta_1, 
				jetY_1,
				jetPhi_1, 
				jetE_1,
				jetPt_2, 
				jetEta_2, 
				jetY_2,
				jetPhi_2, 
				jetE_2,
				jetPt_3, 
				jetEta_3, 
				jetY_3,
				jetPhi_3, 
				jetE_3,				
				DeltaR_photon1_jet1,
				DeltaPhi_photon1_jet1,
				DeltaR_photon1_jet2,
				DeltaEta_jet1_jet2,
				DeltaPhi_jet1_jet2,				
				DeltaR_photon1_jet3,
				HT;
				
//counters
Int_t  iSelected0, iSelected1, iSelected2, iSelected3, iSelected4, iSelected5, iSelected6, iSelected7; 
Int_t  iSelectedWithWeights0, iSelectedWithWeights1, iSelectedWithWeights2, iSelectedWithWeights3, iSelectedWithWeights4, iSelectedWithWeights5, iSelectedWithWeights6, iSelectedWithWeights7;
//clean
//unsigned int jetN, iJetar, iJetcl, conta, conta1;

vector<float>	jetPt_cl,
							jetEta_cl, 
							jetPhi_cl,
							jetE_cl; 

TH1F  *ptPhotonGEN_cl_, *ptPhotonREC_cl_, *DeltaRGENREC_cl_, 
			*Nvtx_cl_, 
			*nPhotons_cl_,
			*isPhotonlead_cl_,
			*photonPt_1_cl_,
			*photonE_1_cl_,
			*photonEta_1_cl_, 
			*photonPhi_1_cl_, 
			*photonBit_1_cl_,
			*photonPassConversionVeto_1_cl_, 
			*photonPfIsoChargedHad_1_cl_, 
			*photonPfIsoNeutralHad_1_cl_, 
			*photonPfIsoPhoton_1_cl_, 
			*photonPfIsoPhotons03ForCic_1_cl_, 
			*photonPfIsoNeutrals03ForCic_1_cl_, 
			*photonPfIsoCharged03ForCicVtx0_1_cl_,
			*photonPfIsoCharged03BadForCic_1_cl_, 
			*photonPfIsoPhotons04ForCic_1_cl_, 
			*photonPfIsoNeutrals04ForCic_1_cl_,
			*photonPfIsoCharged04ForCicVtx0_1_cl_, 
			*photonPfIsoCharged04BadForCic_1_cl_,
			*photonid_sieie_1_cl_,  
			*photonid_sieip_1_cl_, 
			*photonid_etawidth_1_cl_, 
			*photonid_phiwidth_1_cl_, 
			*photonid_r9_1_cl_, 
			*photonid_lambdaRatio_1_cl_, 
			*photonid_s4Ratio_1_cl_,
			*photonid_e25_1_cl_, 
			*photonid_sceta_1_cl_, 
			*photonid_ESEffSigmaRR_1_cl_, 
			*photonid_hadronicOverEm_1_cl_, 
			*photonid_hadronicOverEm2012_1_cl_,
			*photonhcalTowerSumEtConeDR04_1_cl_, 
			*photonecalRecHitSumEtConeDR04_1_cl_, 
			*photonnTrkSolidConeDR04_1_cl_,
			*photontrkSumPtSolidConeDR04_1_cl_, 
			*photonnTrkHollowConeDR04_1_cl_, 
			*photontrkSumPtHollowConeDR04_1_cl_, 
			//PhotonIso_1_cl_,
			*photonIsoFPRCharged_1_cl_, 
			*photonIsoFPRNeutral_1_cl_, 
			*photonIsoFPRPhoton_1_cl_, /**jetPhotonDPhi_,*/ 
			*nJets_cl_, 
			*jetPt_1_cl_, 
			*jetEta_1_cl_, 
			*jetY_1_cl_,
			*jetPhi_1_cl_, 
			*jetE_1_cl_,
			*jetPt_2_cl_, 
			*jetEta_2_cl_, 
			*jetY_2_cl_,
			*jetPhi_2_cl_, 
			*jetE_2_cl_,
			*jetPt_3_cl_, 
			*jetEta_3_cl_, 
			*jetY_3_cl_,
			*jetPhi_3_cl_, 
			*jetE_3_cl_,
			*DeltaR_photon1_jet1_cl_,
			*DeltaPhi_photon1_jet1_cl_,
			*DeltaR_photon1_jet2_cl_,
			*DeltaEta_jet1_jet2_cl_,
			*DeltaPhi_jet1_jet2_cl_,				
			*DeltaR_photon1_jet3_cl_,
			*HT_cl_;

Int_t nJets_cl;
Float_t jetPt_1_cl,
				jetEta_1_cl,
				jetY_1_cl,
				jetPhi_1_cl,
				jetE_1_cl,
				jetPt_2_cl,
				jetEta_2_cl,
				jetY_2_cl,
				jetPhi_2_cl,
				jetE_2_cl,
				jetPt_3_cl,
				jetEta_3_cl,
				jetY_3_cl,
				jetPhi_3_cl,
				jetE_3_cl,
				DeltaR_photon1_jet1_cl,
				DeltaPhi_photon1_jet1_cl, 
				DeltaR_photon1_jet2_cl, 
				DeltaEta_jet1_jet2_cl, 
				DeltaPhi_jet1_jet2_cl, 
				DeltaR_photon1_jet3_cl, 
				HT_cl;

Int_t  iSelected0_cl, iSelected1_cl, iSelected2_cl, iSelected3_cl, iSelected4_cl, iSelected5_cl, iSelected6_cl, iSelected7_cl; 
Int_t  iSelectedWithWeights0_cl, iSelectedWithWeights1_cl, iSelectedWithWeights2_cl, iSelectedWithWeights3_cl, iSelectedWithWeights4_cl, iSelectedWithWeights5_cl, iSelectedWithWeights6_cl, iSelectedWithWeights7_cl;
