import FWCore.ParameterSet.Config as cms

hadWSelector = cms.EDProducer('HadWTrackSelector',
    vertexCol = cms.InputTag(),
    jpsiCands = cms.InputTag(),
    tracks    = cms.InputTag(),
    mode      = cms.vstring(),
    minMass   = cms.double(),
    seedPt    = cms.double(),
    isoDR     = cms.double(),
    minTrkPt  = cms.double(),
    maxTrkDxy = cms.double(),
    maxTrkDz  = cms.double(),
    maxTrkD0  = cms.double(),
)

## cand view combiner vs cand combiner?
jPsiCands = cms.EDProducer("CandViewCombiner",
    decay = cms.string("muons@+ muons@-"),
    cut = cms.string("86.0 < mass < 96.0"),
    name = cms.string('jPsi'),
    roles = cms.vstring('muon1', 'muon2')
)


jPsiCands = cms.EDProducer("CandViewCombiner",
    decay = cms.string("electrons@+ electrons@-"),
    cut = cms.string("86.0 < mass < 96.0"),
    name = cms.string('jPsi'),
    roles = cms.vstring('electron1', 'electron2')
)


bestMuons = cms.EDProducer("CandSelector",
    src = cms.InputTag("allMuons"),
    cut = cms.string("pt > 10 & abs( eta ) < 2")
)

piPlusTracks = cms.EDProducer("ConcreteChargedCandidateProducer",
    src = cms.InputTag("ctfWithMaterialTracks"),
    particleType = cms.string("pi+")
)
