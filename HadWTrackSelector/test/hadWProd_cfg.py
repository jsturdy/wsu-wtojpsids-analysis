import FWCore.ParameterSet.Config as cms

process = cms.Process("HADWPROD")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        "file:WJPsiDsTomumu_8TeV_Pythia8_TuneCUETP8S1.root"
        #"file:WJPsiDsTomumu_13TeV_Pythia8_TuneCUETP8S1.root"
        #"file:/afs/cern.ch/work/s/sturdy/WSUAnalysis/HadronicW/CMSSW_7_5_2/src/WSUHadronicW/HadWTrackSelector/W2JeeDs_TuneZ2star_8TeV535_pythia6_HLT8E33_AODSIM.root"
    )
)


## cand view combiner vs cand combiner?, add dR isolation to J/Psi?
process.jPsiMuMuCands = cms.EDProducer("CandViewCombiner",
    decay = cms.string("muons@+ muons@-"),
    cut   = cms.string("3.090 < mass < 3.190 & pt > 15.0"),
    name  = cms.string('jPsi'),
    roles = cms.vstring('dau1', 'dau2')
)


process.jPsiEECands = cms.EDProducer("CandViewCombiner",
    decay = cms.string("gsfElectrons@+ gsfElectrons@-"),
    cut = cms.string("3.090 < mass < 3.190 & pt > 15.0"),
    name = cms.string('jPsi'),
    roles = cms.vstring('dau1', 'dau2')
)

process.bestMuons = cms.EDProducer("CandSelector",
    src = cms.InputTag("allMuons"),
    cut = cms.string("pt > 10 & fabs( eta ) < 2.4")
)

process.piPlusTracks = cms.EDProducer("ConcreteChargedCandidateProducer",
    src = cms.InputTag("ctfWithMaterialTracks"),
    particleType = cms.string("pi+")
)
  
process.piMinusTracks = cms.EDProducer("ConcreteChargedCandidateProducer",
    src = cms.InputTag("ctfWithMaterialTracks"),
    particleType = cms.string("pi-")
)
  
#process.load("WSUHadronicW.HadWTrackSelector.hadWProd_cfi")
from WSUHadronicW.HadWTrackSelector.hadWProd_cfi import *
process.hadWSelector = hadWSelector.clone()
process.hadWSelector.jpsiCands = cms.InputTag("jPsiMuMuCands")

process.p = cms.Path(
    process.jPsiMuMuCands
    #process.jPsiEECands
    #*process.piPlusTracks
    #*process.piMinusTracks
    *process.hadWSelector
    )

process.out = cms.OutputModule("PoolOutputModule",
    fileName       = cms.untracked.string('myOutputFile.root'),
    outputCommands = cms.untracked.vstring(
        #"drop *",
        "keep *",
    ),
    SelectEvents   = cms.untracked.PSet(
        SelectEvents = cms.vstring("p")
    )
)

process.e = cms.EndPath(process.out)

###-- Dump config ------------------------------------------------------------
file = open('debugging_dump.py','w')
file.write(str(process.dumpPython()))
file.close()
