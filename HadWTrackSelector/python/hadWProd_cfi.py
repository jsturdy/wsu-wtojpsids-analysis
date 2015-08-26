import FWCore.ParameterSet.Config as cms

hadWSelector = cms.EDProducer('HadWTrackSelector',
    vertexCol = cms.InputTag(),
    jpsiCands = cms.InputTag(),
    tracks    = cms.InputTag(),
    mode      = cms.vstring(""),
    minMass   = cms.double(40.0),
    seedPt    = cms.double(5.0),
    minDR     = cms.double(1.0),
    isoDR     = cms.double(0.5),
    minTrkPt  = cms.double(1.0),
    maxTrkDxy = cms.double(),
    maxTrkDz  = cms.double(),
    maxTrkD0  = cms.double(),
)

## cand view combiner vs cand combiner?, add dR isolation to J/Psi?
jPsiMuMuCands = cms.EDProducer("CandViewCombiner",
    decay = cms.string("muons@+ muons@-"),
    cut = cms.string("3.090 < mass < 3.190 & pt > 15.0"),
    name = cms.string('jPsi'),
    roles = cms.vstring('dau1', 'dau2')
)


jPsiEECands = cms.EDProducer("CandViewCombiner",
    decay = cms.string("electrons@+ electrons@-"),
    cut = cms.string("3.090 < mass < 3.190 & pt > 15.0"),
    name = cms.string('jPsi'),
    roles = cms.vstring('dau1', 'dau2')
)


bestMuons = cms.EDProducer("CandSelector",
    src = cms.InputTag("allMuons"),
    cut = cms.string("pt > 10 & abs( eta ) < 2")
)

piPlusTracks = cms.EDProducer("ConcreteChargedCandidateProducer",
    src = cms.InputTag("ctfWithMaterialTracks"),
    particleType = cms.string("pi+")
)
