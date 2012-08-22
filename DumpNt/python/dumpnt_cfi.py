import FWCore.ParameterSet.Config as cms

ntuple = cms.EDAnalyzer("DumpNt",
                              genParticlesProducer = cms.InputTag("genParticles"),
                              doMC                 = cms.bool(True),
                              doElectrons          = cms.bool(True),
                              electronsProducer    = cms.InputTag("gsfElectrons"),
                              deltaRmax            = cms.double(1.0),
                              reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
                              reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
                              PVTag                = cms.InputTag("offlinePrimaryVertices"),
                              recHitCollection_EB  = cms.InputTag("reducedEcalRecHitsEB"),
                              recHitCollection_EE  = cms.InputTag("reducedEcalRecHitsEE"),
                              PVTagWithBS          = cms.InputTag("offlinePrimaryVerticesWithBS"),
                              OutputFile           = cms.string("outputfile.root")
                              )
