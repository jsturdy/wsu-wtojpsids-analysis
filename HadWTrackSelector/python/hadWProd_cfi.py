import FWCore.ParameterSet.Config as cms

hadWSelector = cms.EDProducer('HadWTrackSelector',
    vertexCol = cms.InputTag("offlinePrimaryVertices"),
    jpsiCands = cms.InputTag("jPsiMuMuCands"),
    tracks    = cms.InputTag("generalTracks"),
    mode      = cms.vstring(""),
    minMass   = cms.double(40.0),
    seedPt    = cms.double(5.0),
    minDR     = cms.double(1.0),
    isoDR     = cms.double(0.3),
    minTrkPt  = cms.double(1.0),
    maxTrkDxy = cms.double(5.),
    maxTrkDz  = cms.double(5.),
    maxTrkD0  = cms.double(5.),
    debug     = cms.bool(False),
)
