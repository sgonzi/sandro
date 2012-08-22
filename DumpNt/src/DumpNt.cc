// -*- C++ -*-
//
// Package:    DumpNt
// Class:      DumpNt
// 
/**\class DumpNt DumpNt.cc DumpNt/DumpNt/src/DumpNt.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Mauro Donega (ETH) [donega]
//         Created:  Wed Jun 13 18:08:53 CEST 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

//#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
//#include "Geometry/Records/interface/CaloGeometryRecord.h"
//#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
//#include "Geometry/CaloTopology/interface/CaloTopology.h"
//#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
//#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
//#include "RecoEcal/EgammaCoreTools/interface/PositionCalc.h"

#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//ParticleFlowReco/interface/PFCluster.h
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "RecoParticleFlow/PFClusterTools/interface/ClusterClusterMapping.h"
#include "CommonTools/ParticleFlow/plugins/PFPileUp.h"
#include "DataFormats/ParticleFlowCandidate/interface/PileUpPFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PileUpPFCandidateFwd.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
//#include "applyScCorrections_PHOTON.C"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterFunctionBaseClass.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterFunctionFactory.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"

//#include "fLocalCorr.h"

#include "CondFormats/EcalObjects/interface/EcalClusterLocalContCorrParameters.h"
#include "CondFormats/DataRecord/interface/EcalClusterLocalContCorrParametersRcd.h"
#include "CondFormats/EcalObjects/interface/EcalClusterCrackCorrParameters.h"
#include "CondFormats/DataRecord/interface/EcalClusterCrackCorrParametersRcd.h"

//#include "RecoEcal/EgammaCoreTools/plugins/EcalClusterEnergyCorrectionObjectSpecificBaseClass.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/Common/interface/AssociationVector.h"

//inizio
#include "RecoVertex/PrimaryVertexProducer/interface/VertexHigherPtSquared.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexSorter.h"
//#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
//#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
//#include "/raid/sandro/Geometria/Tracker_ECAL/CMSSW_5_2_5/src/Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "RecoEgamma/EgammaTools/interface/EGEnergyCorrector.h"
//#include "DataFormats/Common/interface/Ref.h"
//#include "DataFormats/Common/interface/RefProd.h"
//#include "DataFormats/Common/interface/RefVector.h"
//fine


#include <Math/VectorUtil.h>

#include "TLorentzVector.h"
#include "TVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

using namespace ROOT::Math::VectorUtil;
typedef math::XYZTLorentzVector LorentzVector;
//typedef math::XYZPoint Point;
typedef math::XYZVectorF Vector;

using std::cout; using std::endl;

//
// class declaration
//

class DumpNt : public edm::EDAnalyzer {
public:
  explicit DumpNt(const edm::ParameterSet&);
  ~DumpNt();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  edm::InputTag genParticlesProducer_;
  bool doMC_;
  bool doElectrons_;
  edm::InputTag electronsProducer_;
  edm::InputTag reducedBarrelEcalRecHitCollection_;
  edm::InputTag reducedEndcapEcalRecHitCollection_;
//inizio
  edm::InputTag PVTag_;
  edm::InputTag recHitCollection_EB_;
  edm::InputTag recHitCollection_EE_;
  edm::InputTag PVTagWithBS_;
//fine
  std::string OutputFile_;
  
  double deltaRmax_ ;

  TFile* fOutput;
  TTree* myTree_;

  int iEvent_        ;
  int countElectrons ;

  int event_number;

  float GenEnergy;
  float GenET;
  float GenEta;
  float GenPhi;
//inizio
  float Genpt;
  float ptOverGenpt;
//fine

  float            el_scEnergy;
  float            el_scRawEnergy;
  //  math::XYZPoint   el_caloPosition; 
  //  P4Kind 	   el_candidateP4Kind; 
  float 	   el_convDcot; 
  float 	   el_convDist; 
  int 	           el_convFlags; 
  float 	   el_convRadius;   
//   float 	   el_correctedEcalEnergy; 
//   float 	   el_correctedEcalEnergyError; 
  float 	   el_deltaEtaEleClusterTrackAtCalo; 
  float 	   el_deltaEtaSeedClusterTrackAtCalo; 
  float 	   el_deltaEtaSuperClusterTrackAtVtx; 
  float 	   el_deltaPhiEleClusterTrackAtCalo; 
  float 	   el_deltaPhiSeedClusterTrackAtCalo; 
  float 	   el_deltaPhiSuperClusterTrackAtVtx; 
  float 	   el_e1x5; 
  float 	   el_e2x5Max; 
  float 	   el_e5x5; 
  bool 	           el_ecalDriven; 
  bool 	           el_ecalDrivenSeed; 
  float 	   el_ecalEnergy; // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)  
  float 	   el_ecalEnergyError; 
  float 	   el_eEleClusterOverPout; 
  float 	   el_eSeedClusterOverP; 
  float 	   el_eSeedClusterOverPout; 
  float 	   el_eSuperClusterOverP; 
  float 	   el_fbrem; 
  float 	   el_hadronicOverEm; 
  float 	   el_hadronicOverEm1; 
  float 	   el_hadronicOverEm2; 
  float 	   el_hcalOverEcal; 
  bool 	           el_isEB; 
  bool 	           el_isEBEEGap; 
  bool 	           el_isEBEtaGap; 
  bool 	           el_isEBGap; 
  bool 	           el_isEBPhiGap; 
  bool 	           el_isEcalEnergyCorrected; 
  bool 	           el_isEE; 
  bool 	           el_isEEDeeGap; 
  bool 	           el_isEEGap; 
  bool 	           el_isEERingGap; 
  bool 	           el_isGap; 
  int 	           el_numberOfBrems; 
  bool 	           el_passingCutBasedPreselection; 
  bool 	           el_passingMvaPreselection; 
  //  bool 	   el_passingPflowPreselection; 
  //  float 	   el_pfSuperClusterFbrem; 
  float 	   el_r9; 
  float 	   el_scE1x5; 
  float 	   el_scE2x5Max; 
  float 	   el_scE5x5; 
  int 	           el_scPixCharge; 
  float 	   el_scSigmaEtaEta; 
  float 	   el_scSigmaIEtaIEta; 
  float 	   el_sigmaEtaEta; 
  float 	   el_sigmaIetaIeta; 
  //  float 	   el_sigmaIphiIphi; 
  //  float 	   el_superClusterFbrem; 
  //  math::XYZPoint   el_superClusterPosition; 
  bool 	           el_trackerDrivenSeed; 
  //  float 	   el_trackFbrem; 
  //  math::XYZVectorF el_trackMomentumAtCalo; 
  //  math::XYZVectorF el_trackMomentumAtEleClus; 
  //  math::XYZVectorF el_trackMomentumAtVtx; 
  //  math::XYZVectorF el_trackMomentumAtVtxWithraint; 
  float 	   el_trackMomentumError;                                    
  //  math::XYZVectorF el_trackMomentumOut; 
  //  math::XYZPointF  el_trackPositionAtCalo; 
  //  math::XYZPointF  el_TrackPositionAtCalo; 
  //  math::XYZPointF  el_TrackPositionAtVtx; 
  //  math::XYZPointF  el_trackPositionAtVtx; 
  
  float            el_trkp         ;
  float            el_trkpT        ;
  float            el_trketa       ;
  float            el_trkphi       ;
  	           
  float	           el_trkAtCalop        ; 
  float	           el_trkAtCalopT       ; 
  float	           el_trkAtCaloeta      ; 
  float	           el_trkAtCalophi      ; 
	           
  float	           el_trkAtEleClusp     ; 
  float	           el_trkAtEleCluspT    ; 
  float	           el_trkAtEleCluseta   ; 
  float	           el_trkAtEleClusphi   ; 
	           
  float	           el_trkAtVtxp     ; 
  float	           el_trkAtVtxpT    ; 
  float	           el_trkAtVtxeta   ; 
  float	           el_trkAtVtxphi   ; 
	           
  float	           el_trkOutp       ; 
  float	           el_trkOutpT      ; 
  float	           el_trkOuteta     ; 
  float	           el_trkOutphi     ; 

//inizio 
  float            el_PV_z;
  float            el_scEta;
  float            el_scPhi;
  //float            el_EOverP;
  float            el_e3x3;
  float            el_scE;
  double           scE_regression;
  int	           el_seedIeta;
  int	           el_seedIphi;
  int	           el_seedIx;
  int	           el_seedIy;
  int	           el_seedZside;
  float	           el_pt;
 //fine

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  double DeltaR(double phi1, double phi2, double eta1, double eta2);
  double DeltaPhi(double phi1, double phi2);

  bool isInPhiCracks(double phi, double eta);
  bool isInEtaCracks(double eta);


  // ----------member data ---------------------------

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DumpNt::DumpNt(const edm::ParameterSet& iConfig)

{
  genParticlesProducer_ = iConfig.getParameter<edm::InputTag>("genParticlesProducer");
  electronsProducer_    = iConfig.getParameter<edm::InputTag>("electronsProducer");
  doMC_                 = iConfig.getParameter<bool>("doMC");
  doElectrons_          = iConfig.getParameter<bool>("doElectrons");
  reducedBarrelEcalRecHitCollection_ = iConfig.getParameter<edm::InputTag>("reducedBarrelEcalRecHitCollection");
  reducedEndcapEcalRecHitCollection_ = iConfig.getParameter<edm::InputTag>("reducedEndcapEcalRecHitCollection");  
  deltaRmax_            = iConfig.getParameter<double>("deltaRmax");
//inizio
  PVTag_               = iConfig.getParameter<edm::InputTag>("PVTag");
  recHitCollection_EB_ = iConfig.getParameter<edm::InputTag>("recHitCollection_EB");
  recHitCollection_EE_ = iConfig.getParameter<edm::InputTag>("recHitCollection_EE");
  PVTagWithBS_         = iConfig.getParameter<edm::InputTag>("PVTagWithBS");  
//fine
  
  OutputFile_           = iConfig.getParameter<std::string>("OutputFile");
  cout << "Creating "<<OutputFile_.c_str()<<endl;
  fOutput = new TFile(OutputFile_.c_str(),"RECREATE");

  myTree_ = new TTree("Tree","PileUp info");

  myTree_->Branch("event_number",&event_number,"event_number/I");

  myTree_->Branch("GenEnergy",&GenEnergy,"GenEnergy/F");
  myTree_->Branch("GenET",&GenET,"GenET/F");
  myTree_->Branch("GenEta",&GenEta,"GenEta/F");
  myTree_->Branch("GenPhi",&GenPhi,"GenPhi/F");
//inizio
  myTree_->Branch("Genpt",&Genpt,"Genpt/F");
  myTree_->Branch("ptOverGenpt",&ptOverGenpt,"ptOverGenpt/F");
//fine

  myTree_->Branch("el_scEnergy"                               ,  &el_scEnergy                       , "el_scEnergy/F"                                 );  
  myTree_->Branch("el_scRawEnergy"                            ,  &el_scRawEnergy                    , "el_scRawEnergy/F"                                 );  
  //  myTree_->Branch("el_caloPosition"                           ,  &el_caloPosition                   , "el_caloPosition"                               );
  //  myTree_->Branch("el_candidateP4Kind"                        ,  &el_candidateP4Kind                , "el_candidateP4Kind"                            );	
  myTree_->Branch("el_convDcot"                               ,  &el_convDcot                       , "el_convDcot/F"                                   );  
  myTree_->Branch("el_convDist"                               ,  &el_convDist                       , "el_convDist/F"                                   );  
  myTree_->Branch("el_convFlags"                              ,  &el_convFlags                      , "el_convFlags/I"                                  );     
  myTree_->Branch("el_convRadius"                             ,  &el_convRadius                     , "el_convRadius/F"                                 );  
//   myTree_->Branch("el_correctedEcalEnergy"                    ,  &el_correctedEcalEnergy            , "el_correctedEcalEnergy/F"                        );  
//   myTree_->Branch("el_correctedEcalEnergyError"               ,  &el_correctedEcalEnergyError       , "el_correctedEcalEnergyError/F"                   );  
  myTree_->Branch("el_deltaEtaEleClusterTrackAtCalo"          ,  &el_deltaEtaEleClusterTrackAtCalo  , "el_deltaEtaEleClusterTrackAtCalo/F"              );  
  myTree_->Branch("el_deltaEtaSeedClusterTrackAtCalo"         ,  &el_deltaEtaSeedClusterTrackAtCalo , "el_deltaEtaSeedClusterTrackAtCalo/F"             );  
  myTree_->Branch("el_deltaEtaSuperClusterTrackAtVtx"         ,  &el_deltaEtaSuperClusterTrackAtVtx , "el_deltaEtaSuperClusterTrackAtVtx/F"             );  
  myTree_->Branch("el_deltaPhiEleClusterTrackAtCalo"          ,  &el_deltaPhiEleClusterTrackAtCalo  , "el_deltaPhiEleClusterTrackAtCalo/F"              );  
  myTree_->Branch("el_deltaPhiSeedClusterTrackAtCalo"         ,  &el_deltaPhiSeedClusterTrackAtCalo , "el_deltaPhiSeedClusterTrackAtCalo/F"             );  
  myTree_->Branch("el_deltaPhiSuperClusterTrackAtVtx"         ,  &el_deltaPhiSuperClusterTrackAtVtx , "el_deltaPhiSuperClusterTrackAtVtx/F"             );  
  myTree_->Branch("el_e1x5"                                   ,  &el_e1x5                           , "el_e1x5/F"                                       );  
  myTree_->Branch("el_e2x5Max"                                ,  &el_e2x5Max                        , "el_e2x5Max/F"                                    );  
  myTree_->Branch("el_e5x5"                                   ,  &el_e5x5                           , "el_e5x5/F"                                       );  
  myTree_->Branch("el_ecalDriven"                             ,  &el_ecalDriven                     , "el_ecalDriven/B"                                 );     
  myTree_->Branch("el_ecalDrivenSeed"                         ,  &el_ecalDrivenSeed                 , "el_ecalDrivenSeed/B"                             );     
  myTree_->Branch("el_ecalEnergy"                             ,  &el_ecalEnergy                     , "el_ecalEnergy/F"                                 );  
  myTree_->Branch("el_ecalEnergyError"                        ,  &el_ecalEnergyError                , "el_ecalEnergyError/F"                            );  
  myTree_->Branch("el_eEleClusterOverPout"                    ,  &el_eEleClusterOverPout            , "el_eEleClusterOverPout/F"                        );  
  myTree_->Branch("el_eSeedClusterOverP"                      ,  &el_eSeedClusterOverP              , "el_eSeedClusterOverP/F"                          );  
  myTree_->Branch("el_eSeedClusterOverPout"                   ,  &el_eSeedClusterOverPout           , "el_eSeedClusterOverPout/F"                       );  
  myTree_->Branch("el_eSuperClusterOverP"                     ,  &el_eSuperClusterOverP             , "el_eSuperClusterOverP/F"                         );  
  myTree_->Branch("el_fbrem"                                  ,  &el_fbrem                          , "el_fbrem/F"                                      );  
  myTree_->Branch("el_hadronicOverEm"                         ,  &el_hadronicOverEm                 , "el_hadronicOverEm/F"                             );  
  myTree_->Branch("el_hadronicOverEm1"                        ,  &el_hadronicOverEm1                , "el_hadronicOverEm1/F"                            );  
  myTree_->Branch("el_hadronicOverEm2"                        ,  &el_hadronicOverEm2                , "el_hadronicOverEm2/F"                            );  
  myTree_->Branch("el_hcalOverEcal"                           ,  &el_hcalOverEcal                   , "el_hcalOverEcal/F"                               );  
  myTree_->Branch("el_isEB"                                   ,  &el_isEB                           , "el_isEB/B"                                       );     
  myTree_->Branch("el_isEBEEGap"                              ,  &el_isEBEEGap                      , "el_isEBEEGap/B"                                  );     
  myTree_->Branch("el_isEBEtaGap"                             ,  &el_isEBEtaGap                     , "el_isEBEtaGap/B"                                 );     
  myTree_->Branch("el_isEBGap"                                ,  &el_isEBGap                        , "el_isEBGap/B"                                    );     
  myTree_->Branch("el_isEBPhiGap"                             ,  &el_isEBPhiGap                     , "el_isEBPhiGap/B"                                 );     
  myTree_->Branch("el_isEcalEnergyCorrected"                  ,  &el_isEcalEnergyCorrected          , "el_isEcalEnergyCorrected/B"                      );     
  myTree_->Branch("el_isEE"                                   ,  &el_isEE                           , "el_isEE/B"                                       );     
  myTree_->Branch("el_isEEDeeGap"                             ,  &el_isEEDeeGap                     , "el_isEEDeeGap/B"                                 );     
  myTree_->Branch("el_isEEGap"                                ,  &el_isEEGap                        , "el_isEEGap/B"                                    );     
  myTree_->Branch("el_isEERingGap"                            ,  &el_isEERingGap                    , "el_isEERingGap/B"                                );     
  myTree_->Branch("el_isGap"                                  ,  &el_isGap                          , "el_isGap/B"                                      );     
  myTree_->Branch("el_numberOfBrems"                          ,  &el_numberOfBrems                  , "el_numberOfBrems/I"                              );     
  myTree_->Branch("el_passingCutBasedPreselection"            ,  &el_passingCutBasedPreselection    , "el_passingCutBasedPreselection/B"                );     
  myTree_->Branch("el_passingMvaPreselection"                 ,  &el_passingMvaPreselection         , "el_passingMvaPreselection/B"                     );     
  //  myTree_->Branch("el_passingPflowPreselection"               ,  &el_passingPflowPreselection       , "el_passingPflowPreselection/B"                   );     
  //  myTree_->Branch("el_pfSuperClusterFbrem"                    ,  &el_pfSuperClusterFbrem            , "el_pfSuperClusterFbrem/F"                        );  
  myTree_->Branch("el_r9"                                     ,  &el_r9                             , "el_r9/F"                                         );  
  myTree_->Branch("el_scE1x5"                                 ,  &el_scE1x5                         , "el_scE1x5/F"                                     );  
  myTree_->Branch("el_scE2x5Max"                              ,  &el_scE2x5Max                      , "el_scE2x5Max/F"                                  );  
  myTree_->Branch("el_scE5x5"                                 ,  &el_scE5x5                         , "el_scE5x5/F"                                     );  
  myTree_->Branch("el_scPixCharge"                            ,  &el_scPixCharge                    , "el_scPixCharge/I"                                );     
  myTree_->Branch("el_scSigmaEtaEta"                          ,  &el_scSigmaEtaEta                  , "el_scSigmaEtaEta/F"                              );  
  myTree_->Branch("el_scSigmaIEtaIEta"                        ,  &el_scSigmaIEtaIEta                , "el_scSigmaIEtaIEta/F"                            );  
  myTree_->Branch("el_sigmaEtaEta"                            ,  &el_sigmaEtaEta                    , "el_sigmaEtaEta/F"                                );  
  myTree_->Branch("el_sigmaIetaIeta"                          ,  &el_sigmaIetaIeta                  , "el_sigmaIetaIeta/F"                              );  
  //  myTree_->Branch("el_sigmaIphiIphi"                          ,  &el_sigmaIphiIphi                  , "el_sigmaIphiIphi/F"                              );  
  //  myTree_->Branch("el_superClusterFbrem"                      ,  &el_superClusterFbrem              , "el_superClusterFbrem/F"                          );  
  //  myTree_->Branch("el_superClusterPosition"                   ,  &el_superClusterPosition           , "el_superClusterPosition"                       );
  myTree_->Branch("el_trackerDrivenSeed"                      ,  &el_trackerDrivenSeed              , "el_trackerDrivenSeed/B"                          );    
  //  myTree_->Branch("el_trackFbrem"                             ,  &el_trackFbrem                     , "el_trackFbrem/F"                                 );  
  //  myTree_->Branch("el_trackMomentumAtCalo"                    ,  &el_trackMomentumAtCalo            , "el_trackMomentumAtCalo"                        );
  //  myTree_->Branch("el_trackMomentumAtEleClus"                 ,  &el_trackMomentumAtEleClus         , "el_trackMomentumAtEleClus"                     );
  //  myTree_->Branch("el_trackMomentumAtVtx"                     ,  &el_trackMomentumAtVtx             , "el_trackMomentumAtVtx"                         );
  //  myTree_->Branch("el_trackMomentumAtVtxWithraint"            ,  &el_trackMomentumAtVtxWithraint    , "el_trackMomentumAtVtxWithraint"                );
  myTree_->Branch("el_trackMomentumError"                     ,  &el_trackMomentumError             , "el_trackMomentumError/F"                         );  
  //  myTree_->Branch("el_trackMomentumOut"                       ,  &el_trackMomentumOut               , "el_trackMomentumOut"                           );
  //  myTree_->Branch("el_trackPositionAtCalo"                    ,  &el_trackPositionAtCalo            , "el_trackPositionAtCalo"                        );
  //  myTree_->Branch("el_TrackPositionAtCalo"                    ,  &el_TrackPositionAtCalo            , "el_TrackPositionAtCalo"                        );
  //  myTree_->Branch("el_TrackPositionAtVtx"                     ,  &el_TrackPositionAtVtx             , "el_TrackPositionAtVtx"                         );
  //  myTree_->Branch("el_trackPositionAtVtx"                     ,  &el_trackPositionAtVtx             , "el_trackPositionAtVtx"                         );
  
  myTree_->Branch("el_trkp"       , &el_trkp                   ,"el_trkp/F"       );
  myTree_->Branch("el_trkpT"      , &el_trkpT     	       ,"el_trkpT/F"      );
  myTree_->Branch("el_trketa"     , &el_trketa    	       ,"el_trketa/F"     );
  myTree_->Branch("el_trkphi"     , &el_trkphi    	       ,"el_trkphi/F"     );
  
  myTree_->Branch("el_trkAtCalop"      , &el_trkAtCalop     	       ,"el_trkAtCalop/F"      );
  myTree_->Branch("el_trkAtCalopT"     , &el_trkAtCalopT    	       ,"el_trkAtCalopT/F"     );
  myTree_->Branch("el_trkAtCaloeta"    , &el_trkAtCaloeta   	       ,"el_trkAtCaloeta/F"    );
  myTree_->Branch("el_trkAtCalophi"    , &el_trkAtCalophi   	       ,"el_trkAtCalophi/F"    );
  
  myTree_->Branch("el_trkAtEleClusp"   , &el_trkAtEleClusp  	       ,"el_trkAtEleClusp/F"   );
  myTree_->Branch("el_trkAtEleCluspT"  , &el_trkAtEleCluspT 	       ,"el_trkAtEleCluspT/F"  );
  myTree_->Branch("el_trkAtEleCluseta" , &el_trkAtEleCluseta	       ,"el_trkAtEleCluseta/F" );
  myTree_->Branch("el_trkAtEleClusphi" , &el_trkAtEleClusphi	       ,"el_trkAtEleClusphi/F" );
  
  myTree_->Branch("el_trkAtVtxp"   , &el_trkAtVtxp  	       ,"el_trkAtVtxp/F"   );
  myTree_->Branch("el_trkAtVtxpT"  , &el_trkAtVtxpT 	       ,"el_trkAtVtxpT/F"  );
  myTree_->Branch("el_trkAtVtxeta" , &el_trkAtVtxeta	       ,"el_trkAtVtxeta/F" );
  myTree_->Branch("el_trkAtVtxphi" , &el_trkAtVtxphi	       ,"el_trkAtVtxphi/F" );
  
  myTree_->Branch("el_trkOutp"     , &el_trkOutp    	       ,"el_trkOutp/F"     );
  myTree_->Branch("el_trkOutpT"    , &el_trkOutpT   	       ,"el_trkOutpT/F"    );
  myTree_->Branch("el_trkOuteta"   , &el_trkOuteta  	       ,"el_trkOuteta/F"   );
  myTree_->Branch("el_trkOutphi"   , &el_trkOutphi  	       ,"el_trkOutphi/F"   );

//inizio
  myTree_->Branch("el_PV_z"        , &el_PV_z                  ,"el_PV_z/F");
  myTree_->Branch("el_scEta"       , &el_scEta                 ,"el_scEta/F");
  myTree_->Branch("el_scPhi"       , &el_scPhi                 ,"el_scPhi/F");
  //myTree_->Branch("el_EOverP"      , &el_EOverP                ,"el_EOverP/F");
  myTree_->Branch("el_e3x3"        , &el_e3x3                  ,"el_e3x3/F");
  myTree_->Branch("el_scE"         , &el_scE                   ,"el_scE/F");
  myTree_->Branch("scE_regression" , &scE_regression           ,"scE_regression/D");
  myTree_->Branch("el_seedIeta"    , &el_seedIeta              ,"el_seedIeta/I");
  myTree_->Branch("el_seedIphi"    , &el_seedIphi              ,"el_seedIphi/I");
  myTree_->Branch("el_seedIx"      , &el_seedIx                ,"el_seedIx/I");
  myTree_->Branch("el_seedIy"      , &el_seedIy                ,"el_seedIy/I");
  myTree_->Branch("el_seedZside"   , &el_seedZside             ,"el_seedZside/I");
  myTree_->Branch("el_pt"          , &el_pt                    ,"el_pt/F");
//fine

  iEvent_        = 0;
  countElectrons = 0;

}


DumpNt::~DumpNt()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
  fOutput->Write();
  fOutput->Close();
}


//
// member functions
//

// ------------ method called for each event  ------------
void
DumpNt::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  //MC truth
  edm::Handle <reco::GenParticleCollection> genParticles;
  if (doMC_){
    iEvent.getByLabel( genParticlesProducer_, genParticles );
    //     cout << "nGenParticles="<<genParticles->size()<<std::endl;
  }
  
  //Electron collection
  edm::Handle<reco::GsfElectronCollection> electronHandle;
  if (doElectrons_){
    iEvent.getByLabel(electronsProducer_,electronHandle);
    //     cout << "nElectrons=" << electronHandle->size() << std::endl;
    countElectrons += electronHandle->size();
    
  }

  // Get the lazy tools
  edm::Handle<EcalRecHitCollection> EBRecHits_;
  edm::Handle<EcalRecHitCollection> EERecHits_;
  iEvent.getByLabel(reducedBarrelEcalRecHitCollection_, EBRecHits_);
  iEvent.getByLabel(reducedEndcapEcalRecHitCollection_, EERecHits_);
  EcalClusterLazyTools* lazyTools = 0;
  lazyTools = new EcalClusterLazyTools( iEvent, iSetup, reducedBarrelEcalRecHitCollection_, reducedEndcapEcalRecHitCollection_ );  


//inizio
  // vertexes collection
  edm::Handle<reco::VertexCollection> vertexes; 
  iEvent.getByLabel(PVTag_, vertexes);

  // beam spot
  edm::Handle<reco::BeamSpot> BSHandle;
  iEvent.getByType(BSHandle);

  // calo topology
  edm::ESHandle<CaloTopology> pTopology;
  iSetup.get<CaloTopologyRecord>().get(pTopology);
  const CaloTopology *topology = pTopology.product();

  // EB rec Hits
  edm::Handle<EcalRecHitCollection> recHitsEB;
  iEvent.getByLabel(recHitCollection_EB_, recHitsEB);
  const EcalRecHitCollection* theBarrelEcalRecHits = recHitsEB.product();
  if ( ! recHitsEB.isValid() ) {
    std::cerr << "SimpleNtupleEoverP::analyze --> recHitsEB not found" << std::endl; 
  }
  
  // EE rec Hits
  edm::Handle<EcalRecHitCollection> recHitsEE;
  iEvent.getByLabel(recHitCollection_EE_, recHitsEE);
  const EcalRecHitCollection* theEndcapEcalRecHits = recHitsEE.product();
 if ( ! recHitsEE.isValid() ) {
    std::cerr << "SimpleNtupleEoverP::analyze --> recHitsEE not found" << std::endl; 
  }

  // vertex collection with beam spot
  edm::Handle<reco::VertexCollection> hVertexProduct;
  iEvent.getByLabel(PVTagWithBS_,hVertexProduct);

  // EnergyCorrecto tools
  EGEnergyCorrector ecorr_;
  if ( !ecorr_.IsInitialized() ){
     ecorr_.Initialize(iSetup, "/raid/sandro/Geometria/Tracker_ECAL/CMSSW_5_2_5/src/DumpNt/DumpNt/test/gbrv3ele_52x.root"); //from UserCode/HiggsAnalysis/HiggsTo2photons/data/
  }
//  EcalClusterLazyTools lazyTools_1(iEvent, iSetup, reducedBarrelEcalRecHitCollection_, reducedEndcapEcalRecHitCollection_);
//fine


  // Dump Electron quantities

  if (doElectrons_) {
    
    if (electronHandle->size()==2) {

      for( reco::GsfElectronCollection::const_iterator eleIter = electronHandle->begin();
	   eleIter != electronHandle->end(); ++eleIter ){
	
	const reco::CaloClusterPtr eleSeed = eleIter->superCluster()->seed();

//inizio
        reco::SuperClusterRef scRef = eleIter->superCluster();
        //const edm::Ptr<reco::CaloCluster>& seedCluster = scRef->seed();
//fine

	el_scEnergy                              = eleIter->energy();
	el_scRawEnergy                           = eleIter->superCluster()->rawEnergy();

	el_convDcot                              = eleIter->convDcot();                              		   
	el_convDist 				 = eleIter->convDist(); 					     	  	     
	el_convFlags 				 = eleIter->convFlags(); 					     	  	     
	el_convRadius   			 = eleIter->convRadius();   					  		     
// 	el_correctedEcalEnergy 		         = eleIter->correctedEcalEnergy(); 				  		     
// 	el_correctedEcalEnergyError 		 = eleIter->correctedEcalEnergyError(); 			     	  	     
	el_deltaEtaEleClusterTrackAtCalo 	 = eleIter->deltaEtaEleClusterTrackAtCalo(); 			  		     
	el_deltaEtaSeedClusterTrackAtCalo 	 = eleIter->deltaEtaSeedClusterTrackAtCalo(); 			  		     
	el_deltaEtaSuperClusterTrackAtVtx 	 = eleIter->deltaEtaSuperClusterTrackAtVtx(); 			  		     
	el_deltaPhiEleClusterTrackAtCalo 	 = eleIter->deltaPhiEleClusterTrackAtCalo(); 			  		     
	el_deltaPhiSeedClusterTrackAtCalo 	 = eleIter->deltaPhiSeedClusterTrackAtCalo(); 			  		     
	el_deltaPhiSuperClusterTrackAtVtx 	 = eleIter->deltaPhiSuperClusterTrackAtVtx(); 			  		     
	el_e1x5 				 = eleIter->e1x5(); 						  		     
	el_e2x5Max 				 = eleIter->e2x5Max(); 						  		     
	el_e5x5 				 = eleIter->e5x5(); 						  		     
	el_ecalDriven 				 = eleIter->ecalDriven(); 					     	  	     
	el_ecalDrivenSeed 			 = eleIter->ecalDrivenSeed(); 					  		     
	el_ecalEnergy 				 = eleIter->ecalEnergy(); 					     	  	     
	el_ecalEnergyError 			 = eleIter->ecalEnergyError(); 					  		     
	el_eEleClusterOverPout 		         = eleIter->eEleClusterOverPout(); 				  		     
	el_eSeedClusterOverP 			 = eleIter->eSeedClusterOverP(); 				     	  	     
	el_eSeedClusterOverPout 		 = eleIter->eSeedClusterOverPout(); 				  		     
	el_eSuperClusterOverP 			 = eleIter->eSuperClusterOverP(); 				     	  	     
	el_fbrem 				 = eleIter->fbrem(); 						  		     
	el_hadronicOverEm 			 = eleIter->hadronicOverEm(); 					  		     
	el_hadronicOverEm1 			 = eleIter->hadronicOverEm1(); 					  		     
	el_hadronicOverEm2 			 = eleIter->hadronicOverEm2(); 					  		     
	el_hcalOverEcal 			 = eleIter->hcalOverEcal(); 					  		     
	el_isEB 				 = eleIter->isEB(); 						  		     
	el_isEBEEGap 				 = eleIter->isEBEEGap(); 					     	  	     
	el_isEBEtaGap 				 = eleIter->isEBEtaGap(); 					     	  	     
	el_isEBGap 				 = eleIter->isEBGap(); 						  		     
	el_isEBPhiGap 				 = eleIter->isEBPhiGap(); 					     	  	     
	el_isEcalEnergyCorrected 		 = eleIter->isEcalEnergyCorrected(); 				  		     
	el_isEE 				 = eleIter->isEE(); 						  		     
	el_isEEDeeGap 				 = eleIter->isEEDeeGap(); 					     	  	     
	el_isEEGap 				 = eleIter->isEEGap(); 						  		     
	el_isEERingGap 			         = eleIter->isEERingGap(); 					  		     
	el_isGap 				 = eleIter->isGap(); 						  		     
	el_numberOfBrems 			 = eleIter->numberOfBrems(); 					  		     
	el_passingCutBasedPreselection 	         = eleIter->passingCutBasedPreselection(); 			  		     
	el_passingMvaPreselection 		 = eleIter->passingMvaPreselection(); 				  		     
//	el_passingPflowPreselection 		 = eleIter->passingPflowPreselection(); 			     	  	     
//	el_pfSuperClusterFbrem 		         = eleIter->pfSuperClusterFbrem(); 				  		     
	//	el_r9 					 = eleIter->r9(); 
	el_r9                                    =  -9 ;
	if (el_scRawEnergy != 0) el_r9 =  lazyTools->e3x3(*eleSeed)/el_scRawEnergy; 

	el_scE1x5 				 = eleIter->scE1x5(); 						  		     
	el_scE2x5Max 				 = eleIter->scE2x5Max(); 					     	  	     
	el_scE5x5 				 = eleIter->scE5x5(); 						  		     
	el_scPixCharge 			         = eleIter->scPixCharge(); 					  		     
	el_scSigmaEtaEta 			 = eleIter->scSigmaEtaEta(); 					  		     
	el_scSigmaIEtaIEta 			 = eleIter->scSigmaIEtaIEta(); 					  		     
	el_sigmaEtaEta 			         = eleIter->sigmaEtaEta(); 					  		     
	el_sigmaIetaIeta 			 = eleIter->sigmaIetaIeta(); 					  		     
	//	el_sigmaIphiIphi 			 = eleIter->sigmaIphiIphi(); 					  		     
	//	el_superClusterFbrem 			 = eleIter->superClusterFbrem(); 				     	  	     

	el_trackerDrivenSeed 			 = eleIter->trackerDrivenSeed(); 				     	  	     
	//	el_trackFbrem 				 = eleIter->trackFbrem(); 					     	  	     


	el_trackMomentumError                   = eleIter->trackMomentumError();                                                     
	

	const LorentzVector & el_p4 = eleIter->p4();

  	el_trkp                           = el_p4.P(); 
  	el_trkpT                          = el_p4.Pt(); 
  	el_trketa                         = el_p4.Eta(); 
  	el_trkphi                         = el_p4.Phi(); 

 	const  Vector el_trackMomentumAtCalo 	  =  eleIter->trackMomentumAtCalo ()    ;

  	el_trkAtCalop                           = el_trackMomentumAtCalo.rho();   
  	el_trkAtCaloeta                         = el_trackMomentumAtCalo.Eta(); 
  	el_trkAtCalophi                         = el_trackMomentumAtCalo.Phi(); 
  	el_trkAtCalopT                          = -999;
	if (cosh(el_trkAtCaloeta) != 0)         el_trkAtCalopT = el_trkAtCalop / cosh(el_trkAtCaloeta);

 	const  Vector el_trackMomentumAtEleClus   =  eleIter->trackMomentumAtEleClus () ;

  	el_trkAtEleClusp                        = el_trackMomentumAtEleClus.rho();   
  	el_trkAtEleCluseta                      = el_trackMomentumAtEleClus.Eta(); 
  	el_trkAtEleClusphi                      = el_trackMomentumAtEleClus.Phi(); 
  	el_trkAtEleCluspT                          = -999;
	if (cosh(el_trkAtEleCluseta) != 0)         el_trkAtEleCluspT = el_trkAtEleClusp / cosh(el_trkAtEleCluseta);

 	const  Vector el_trackMomentumAtVtx  	  =  eleIter->trackMomentumAtVtx ()     ;

  	el_trkAtVtxp                        = el_trackMomentumAtVtx.rho();   
  	el_trkAtVtxeta                      = el_trackMomentumAtVtx.Eta(); 
  	el_trkAtVtxphi                      = el_trackMomentumAtVtx.Phi(); 
  	el_trkAtVtxpT                          = -999;
	if (cosh(el_trkAtVtxeta) != 0)         el_trkAtVtxpT = el_trkAtVtxp / cosh(el_trkAtVtxeta);

 	const  Vector el_trackMomentumOut  	  =  eleIter->trackMomentumOut ()       ;

  	el_trkOutp                          = el_trackMomentumOut.rho();   
  	el_trkOuteta                        = el_trackMomentumOut.Eta(); 
  	el_trkOutphi                        = el_trackMomentumOut.Phi(); 
  	el_trkOutpT                         = -999;
	if (cosh(el_trkOuteta) != 0)         el_trkOutpT = el_trkOutp / cosh(el_trkOuteta);
	
//inizio
        // select the BS
        math::XYZPoint BSPoint_;
        const reco::BeamSpot BS = *BSHandle;
        math::XYZPoint BSPoint(BS.position().x(), BS.position().y(), BS.position().z());
        BSPoint_ = BSPoint;

        // select the primary vertex
        reco::Vertex PV;
        bool PVfound = (vertexes -> size() != 0);

        if(PVfound)
        {
        	//VertexHigherPtSquared vertexTool;
    		// sort the primary vertices according to sum of (pt)^2 of tracks (first one -> highest sum of (pt)^2 )
    		PrimaryVertexSorter PVSorter;
    		std::vector<reco::Vertex> sortedVertices = PVSorter.sortedList(*(vertexes.product()));
    		for( unsigned int u = 0 ; u < sortedVertices.size(); u++ )
    		{
      			PV = sortedVertices[u];
			el_PV_z = PV.z();
		}
    
    		PV = sortedVertices[0];
  	}
  
  	else
  	{
    		//creating a dummy PV
    		reco::Vertex::Point p(BSPoint_.x(),BSPoint_.y(),BSPoint_.z());
    		reco::Vertex::Error e;
    		e(0,0) = 0.0015*0.0015;
    		e(1,1) = 0.0015*0.0015;
    		e(2,2) = 15.*15.;
    		PV = reco::Vertex(p, e, 1, 1, 1);
    
        	el_PV_z=-999.;
        }

        el_scEta                            = scRef->eta();
        el_scPhi                            = scRef->phi();
        //el_EOverP                           = eleIter->eSuperClusterOverP();

        float E3x3 = 0;
        if(el_isEB) {
        	E3x3 = EcalClusterTools::e3x3( *scRef, theBarrelEcalRecHits, topology);
        }
        if(el_isEE){
       		E3x3 = EcalClusterTools::e3x3( *scRef, theEndcapEcalRecHits, topology);
        }
        el_e3x3                             = E3x3;     

        el_scE                              = scRef->energy();

        reco::GsfElectron ele = *eleIter;
        std::pair<double,double> cor = ecorr_.CorrectedEnergyWithError(ele, *hVertexProduct, *lazyTools, iSetup);
        scE_regression                      = cor.first;

        int ieta = 0;
        int iphi = 0;
        int ix = 0;
        int iy = 0;
        int zside = 0;

        if(el_isEB)
        {
          std::pair<DetId, float> id = EcalClusterTools::getMaximum(eleSeed->hitsAndFractions(), theBarrelEcalRecHits);
     
          // flag
          EcalRecHitCollection::const_iterator it = theBarrelEcalRecHits->find(id.first);
     
          if( it != theBarrelEcalRecHits->end() )
          {
            ieta = (EBDetId(id.first)).ieta();
            iphi = (EBDetId(id.first)).iphi();
            ix = -999;
            iy = -999;
            zside = 0;
          }
     
        }
   
        else
        {
          std::pair<DetId, float> id = EcalClusterTools::getMaximum(eleSeed->hitsAndFractions(), theEndcapEcalRecHits);
     
          // flag - OutOfTime
          EcalRecHitCollection::const_iterator it = theEndcapEcalRecHits->find(id.first);
     
          if( it != theEndcapEcalRecHits->end() )
          {
            ix = (EEDetId(id.first)).ix();
            iy = (EEDetId(id.first)).iy();
            ieta = -999;
            iphi = -999;
            zside = (EEDetId(id.first)).zside();
          }

        }

        el_seedIeta                         = ieta;
        el_seedIphi                         = iphi;
        el_seedIx                           = ix;
        el_seedIy                           = iy;
        el_seedZside                        = zside;

        el_pt                               = eleIter->pt();

//fine

	// Dump Truth quantities
  
	//genparticle matching  
	GenEnergy       = -9;
	GenET           = -9;
	GenEta          = -9;
	GenPhi          = -9;
	Genpt           = -9;
	ptOverGenpt     = -9;
  
	// simple truth matching
	if (doMC_){
	  int pdg_to_match;
	  if (doElectrons_) pdg_to_match = 11; // electron
	  else pdg_to_match = 22;              // photon
	  //	  int igpsl=-1;
	  for(unsigned int j=0; j<genParticles->size(); ++j ){
	    const reco::GenParticle & p = (*genParticles)[j];
	    if (fabs(p.pdgId()) == pdg_to_match){
	      if (DeltaR(eleIter->phi(), p.phi(), eleIter->eta(), p.eta()) < deltaRmax_){
		GenEnergy   = p.energy();
		GenET       = p.et();
		GenEta      = p.eta();
		GenPhi      = p.phi();
		Genpt       = p.pt();
                ptOverGenpt = el_pt/Genpt;
	      }
	    }
	  }
	}

	myTree_->Fill();
	
      }
    }  
  }

  iEvent_++;

}


// ------------ method called once each job just before starting event loop  ------------
void 
DumpNt::beginJob()
{

  // Initializa counters
  iEvent_        = 0 ;
  countElectrons = 0 ;  

  // Job configuration
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << "--- Job configuration " << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
  cout << " genParticlesProducer " << genParticlesProducer_ << endl;
  cout << " electronsProducer    " << electronsProducer_    << endl;
  cout << " doMC                 " << doMC_                 << endl;
  cout << " doElectrons          " << doElectrons_          << endl;
  cout << " deltaRmax            " << deltaRmax_            << endl;
  cout << " OutputFile           " << OutputFile_           << endl;
  cout << "--------------------------------------------------------------------------------" << endl;
 
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DumpNt::endJob() 
{
  cout << "Number of events = " << iEvent_ << endl;
}

// ------------ method called when starting to processes a run  ------------
void 
DumpNt::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
DumpNt::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
DumpNt::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
DumpNt::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DumpNt::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ------------ my Utils ------------
double 
DumpNt::DeltaR(double phi1, double phi2, double eta1, double eta2){
  
  double dphi=phi2-phi1;
  if (dphi>TMath::Pi()) dphi=2*TMath::Pi()-dphi;
  if (dphi<-TMath::Pi()) dphi=-2*TMath::Pi()-dphi;
  double dR=sqrt(dphi*dphi+(eta2-eta1)*(eta2-eta1));

  return dR;
}

double 
DumpNt::DeltaPhi(double phi1, double phi2){

  double dphi=phi1-phi2;
  if (dphi>TMath::Pi()) dphi=2*TMath::Pi()-dphi;
  if (dphi<-TMath::Pi()) dphi=-2*TMath::Pi()-dphi;

  return dphi;
}

bool 
DumpNt::isInPhiCracks(double phi, double eta){
  // tranform radiants [-pi,pi] in degrees [0,360]
  phi = (phi+TMath::Pi()) *180/TMath::Pi();

  // each supermodule is 20 degrees wide
  Double_t moduleWidth = 20;

  // the first module is centered at phi=0, so the first cracks are +10 and -10
  Double_t phi0 = 10.;

  // set a fiducial cut around the crack of +2-2 degrees
  Double_t fiducialCut = 2.;

  bool OK = false;
  if (fabs(eta)<1.44){
    for (Int_t i = 0 ; i < 18; ++i){
      if ((phi0 + moduleWidth*i -fiducialCut) <= phi && phi <= (phi0 + moduleWidth*i + fiducialCut)) OK = true;
      //        cout << " PHI " << (phi0 + moduleWidth*i -fiducialCut) << " " << phi << " " <<  (phi0 + moduleWidth*i + fiducialCut)  << " " << OK << endl ;
    }
  }

  //  cout << "is in phi crack ? " << OK << endl;
  return OK;
}

bool 
DumpNt::isInEtaCracks(double eta){
  
  /*
    Yuri Maravin eta cracks def :
    double emAbsEta = fabs(phoSC_GeomEta);
    pho_isInCrack = 0;
    if ( emAbsEta < 0.018 ||
    (emAbsEta > 0.423 && emAbsEta < 0.461) || 
    (emAbsEta > 0.770 && emAbsEta < 0.806) || 
    (emAbsEta > 1.127 && emAbsEta < 1.163) || 
    (emAbsEta > 1.460 && emAbsEta < 1.558) )
    pho_isInCrack = 1;
  */
  
  const Int_t nBinsEta = 5;
  Double_t leftEta [nBinsEta]       = {0.00, 0.42, 0.77, 1.13, 1.46};
  Double_t rightEta[nBinsEta]       = {0.02, 0.46, 0.81, 1.16, 9999.};
  
  bool OK = false;
  if (TMath::Abs(eta)<1.44) {
    for (Int_t i = 0; i< nBinsEta; ++i){
      if (leftEta[i] < TMath::Abs(eta) && TMath::Abs(eta) < rightEta[i] ) OK = true;
    }
  }
  else if (TMath::Abs(eta)>1.44 && TMath::Abs(eta)<1.56) OK = true;
  else if (TMath::Abs(eta)>1.56) OK = false;
  //    cout << leftEta[i] << " " << TMath::Abs(eta) << " " << rightEta[i] <<  " " << OK << endl;
  
  //  cout << "IS IN CRACK ? " << OK << endl;
  return OK;
}



//define this as a plug-in
DEFINE_FWK_MODULE(DumpNt);
