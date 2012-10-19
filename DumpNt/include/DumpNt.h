#ifndef DumpNt_h
#define DumpNt_h

#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "TFile.h"
#include "TTree.h"
#include "TList.h"

#include <string>

class DumpNt : public edm::EDAnalyzer{
//class DumpNt {

	public:
		explicit DumpNt(const edm::ParameterSet&);

		virtual ~DumpNt();

		static void fillDescriptions(edm::ConfigurationDescriptions&);

		edm::InputTag genParticlesProducer_;

		bool doMC_, doElectrons_;

		edm::InputTag electronsProducer_;

		double deltaRmax_;

		edm::InputTag reducedBarrelEcalRecHitCollection_;
		edm::InputTag reducedEndcapEcalRecHitCollection_;
		edm::InputTag PVTag_;
		edm::InputTag recHitCollection_EB_;
		edm::InputTag recHitCollection_EE_;
		edm::InputTag PVTagWithBS_;

		std::string OutputFile_;

		TFile* fOutput;
		TTree* myTree_;

		int event_number;

		float GenEnergy, GenET, GenEta, GenPhi, Genpt;

		float pt_Over_Genpt, CtfTrackpt_Over_Genpt, ClosestTrackpt_Over_Genpt, gsfTrackpt_Over_Genpt, 
		Energy_Over_GenEnergy, scEnergy_Over_GenEnergy, scRawEnergy_Over_GenEnergy;

		float el_Energy, el_scEnergy, el_scRawEnergy, el_convDcot, el_convDist, el_convRadius;

		int el_convFlags;

		// math::XYZPoint el_caloPosition;
		// P4Kind el_candidateP4Kind;

		// float el_correctedEcalEnergy;
		// float el_correctedEcalEnergyError;

		float el_deltaEtaEleClusterTrackAtCalo, el_deltaEtaSeedClusterTrackAtCalo,
		el_deltaEtaSuperClusterTrackAtVtx, el_deltaPhiEleClusterTrackAtCalo, el_deltaPhiSeedClusterTrackAtCalo,
		el_deltaPhiSuperClusterTrackAtVtx;

		float el_e1x5, el_e2x5Max, el_e5x5;

		bool el_ecalDriven, el_ecalDrivenSeed;

		float el_ecalEnergy, // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
		el_ecalEnergyError, el_eEleClusterOverPout, el_eSeedClusterOverP, el_eSeedClusterOverPout,
		el_eSuperClusterOverP, el_fbrem, el_hadronicOverEm, el_hadronicOverEm1, el_hadronicOverEm2,
		el_hcalOverEcal;

		bool el_isEB,el_isEBEEGap, el_isEBEtaGap, el_isEBGap, el_isEBPhiGap, el_isEcalEnergyCorrected, el_isEE,
		el_isEEDeeGap, el_isEEGap, el_isEERingGap, el_isGap;

		int el_numberOfBrems;

		bool el_passingCutBasedPreselection, el_passingMvaPreselection;

		// bool el_passingPflowPreselection;
		// float el_pfSuperClusterFbrem;

		float el_r9, el_scE1x5, el_scE2x5Max, el_scE5x5;

		int el_scPixCharge;

		float el_scSigmaEtaEta, el_scSigmaIEtaIEta, el_sigmaEtaEta, el_sigmaIetaIeta;

		// float el_sigmaIphiIphi;
		// float el_superClusterFbrem;
		// math::XYZPoint el_superClusterPosition;

		bool el_trackerDrivenSeed;

		// float el_trackFbrem;
		// math::XYZVectorF el_trackMomentumAtCalo;
		// math::XYZVectorF el_trackMomentumAtEleClus;
		// math::XYZVectorF el_trackMomentumAtVtx;
		// math::XYZVectorF el_trackMomentumAtVtxWithraint;

		float el_trackMomentumError;

		// math::XYZVectorF el_trackMomentumOut;
		// math::XYZPointF el_trackPositionAtCalo;
		// math::XYZPointF el_TrackPositionAtCalo;
		// math::XYZPointF el_TrackPositionAtVtx;
		// math::XYZPointF el_trackPositionAtVtx;

		float el_trkp, el_trkpT, el_trketa, el_trkphi;
		 
		float el_trkAtCalop, el_trkAtCaloeta, el_trkAtCalophi, el_trkAtCalopT,;
 
		float el_trkAtEleClusp, el_trkAtEleCluseta, el_trkAtEleClusphi, el_trkAtEleCluspT,;
 
		float el_trkAtVtxp, el_trkAtVtxeta, el_trkAtVtxphi, el_trkAtVtxpT;
 
		float el_trkOutp, el_trkOuteta, el_trkOutphi, el_trkOutpT;

		// float el_EOverP;

		float el_PV_z, el_scEta, el_scPhi;

		float el_e3x3, el_scE;

		double scE_regression;

		int el_seedIeta, el_seedIphi, el_seedIx, el_seedIy, el_seedZside;

		float el_pt, el_CtfTrack_pt, el_ClosestTrack_pt, el_gsfTrack_pt;

		int iEvent_, countElectrons;

	private:
		virtual void beginJob();
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob();

		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

		double DeltaR(double phi1, double phi2, double eta1, double eta2);
		double DeltaPhi(double phi1, double phi2);

		bool isInPhiCracks(double phi, double eta);
		bool isInEtaCracks(double eta);
};

#endif
