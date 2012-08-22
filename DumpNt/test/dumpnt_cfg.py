import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

## load parameters
process.load("DumpNt.DumpNt.dumpnt_cfi")
process.ntuple.doMC = cms.bool(True)

#################
## Customization 
isMC = process.ntuple.doMC

import FWCore.Utilities.FileUtils as FileUtils
nameSourceMC = FileUtils.loadListFromFile ('../data/0_Original_DATA.txt')
nameSourceDATA = FileUtils.loadListFromFile ('../data/1_PixelBarrelConnToST_MC.txt')
#nameSourceMC = cms.untracked.vstring('file:/raid/sandro/Geometria/Tracker_ECAL/CMSSW_5_2_5/src/DumpNt/DumpNt/test/SingleElectronPt35_cfi_py_RAW2DIGI_RECO.root')
#nameSourceDATA = cms.untracked.vstring('/store/data/Run2012B/DoubleElectron/AOD/08Jun2012-v1/0000/F68EAAC5-92B2-E111-B9BF-003048FFD736.root')

numEventsToRun = 1000

GloTagMC = cms.string('START52_V11C::All')
GloTagDATA = cms.string('GR_R_52_V9D::All')

nameOutputMC = cms.string("outfile_0_Original_MC.root")
nameOutputDATA = cms.string("outfile_0_Original_DATA.root")
#################

## MessageLogger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

## Source
if isMC == True:
	nameSource = nameSourceMC
else:
	nameSource = nameSourceDATA

readFiles = cms.untracked.vstring( *nameSource)

process.source = cms.Source("PoolSource",
	                    fileNames = readFiles
                           )

## Max Number of Events
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(numEventsToRun)
                                      )

## Standard Sequences 
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

## GlobalTag
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
if isMC == True:
	process.GlobalTag.globaltag = GloTagMC 
else: 
	process.GlobalTag.globaltag = GloTagDATA

## Output
if isMC == True:
	nameOutput = nameOutputMC
else:
	nameOutput = nameOutputDATA
process.ntuple.OutputFile = nameOutput

process.p = cms.Path(process.ntuple)
