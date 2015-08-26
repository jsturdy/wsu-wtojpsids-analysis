// -*- C++ -*-
//
// Package:    WSUHadronicW/HadWTrackSelector
// Class:      HadWTrackSelector
//
// Original Author:  Jared Sturdy
//         Created:  Tue, 25 Aug 2015 17:10:31 GMT
//
//


#include "WSUHadronicW/HadWTrackSelector/interface/HadWTrackSelector.h"

#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/OneToOne.h"
#include "DataFormats/Math/interface/deltaR.h"


HadWTrackSelector::HadWTrackSelector(const edm::ParameterSet& pset):
  m_vertexTag(   pset.getParameter<edm::InputTag>("vertexCol")),
  m_jPsiCandsTag(pset.getParameter<edm::InputTag>("jpsiCands")),
  m_tracksTag(   pset.getParameter<edm::InputTag>("tracks"   )),
  m_modes(       pset.getParameter<std::vector<std::string> >("mode")),
  m_minMass( pset.getParameter<double>("minMass"  )),
  m_seedPt ( pset.getParameter<double>("seedPt"   )),
  m_minTrkPt(pset.getParameter<double>("minTrkPt" )),
  m_isoDR(   pset.getParameter<double>("isoDR"    )),
  m_maxDxy(  pset.getParameter<double>("maxTrkDxy")),
  m_maxDz(   pset.getParameter<double>("maxTrkDz" )),
  m_maxD0(   pset.getParameter<double>("maxTrkD0" ))
{
  produces<reco::TrackCollection>("allTracks");
  produces<reco::TrackCollection>("isoTracks");
  produces<reco::TrackCollection>("candTracks");

  produces<edm::OwnVector<reco::Candidate> >();
  produces<reco::CandidateCollection>();
  
  /*
    produces<ExampleData2>();
    //if do put with a label
    produces<ExampleData2>("label");
    //if you want to put into the Run
    produces<ExampleData2,InRun>();
  */
  
}


HadWTrackSelector::~HadWTrackSelector()
{
 
  // do anything here that needs to be done at destruction time
  // (e.g. close files, deallocate resources etc.)

}


void HadWTrackSelector::produce(edm::Event& ev, const edm::EventSetup& es)
{
  // using namespace edm;
  // using namespace reco;

  edm::Handle<reco::VertexCollection> vertices;
  ev.getByLabel(m_vertexTag,vertices);

  edm::Handle<std::vector<reco::CompositeCandidate> > jPsiCands;
  ev.getByLabel(m_jPsiCandsTag,jPsiCands);

  edm::Handle<reco::TrackCollection> allTracks;
  ev.getByLabel(m_tracksTag,allTracks);

  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  es.get<SetupRecord>().get(pSetup);
  */
 
  //what to do if there are multiple J/Psi candidates?  do a loop for each one and create a collection and association map?
  
  reco::TrackCollection allOutTracks;       // all tracks passing the minimum pT cut and vertex matching
  reco::TrackCollection isolatedOutTracks;  // all tracks that are, in addition, well isolated from the J/Psi candidate
  reco::TrackCollection candidateOutTracks; // all tracks that are in a cone around our seed track

  //match the J/Psi to the correct vertex
  reco::Vertex eventPV = findEventPV(*vertices, (*jPsiCands)[0]);

  //do some processing
  for (auto track = allTracks->begin(); track != allTracks->end(); ++track) {
    if (track->pt() > m_minTrkPt) {
      //check the vertex matching
      if (trackToJPsiVertex(*track,eventPV)) {
	allOutTracks.push_back(*track);	
	if (math.deltaR(track->p4(),(*jPsiCands)[0]->p4()) > m_minDR)
	  isolatedOutTracks.push_back(*track);	  
      }
    }
  }

  //isolatedOutTracks.sort(byPt);
  reco::Track seedTrack = isolatedOutTracks.at(0);
  for (auto track = isolatedOutTracks.begin(); track != isolatedOutTracks.end(); ++track) {
    
  }

  
  //put the products into the event
  std::unique_ptr<reco::TrackCollection> allTracksOut1(new reco::TrackCollection(allOutTracks));
  ev.put(std::move(allTracksOut1));

  std::unique_ptr<reco::TrackCollection> isolatedTracksOut1(new reco::TrackCollection(isolatedOutTracks));
  ev.put(std::move(isolatedTracksOut1));

  std::unique_ptr<reco::TrackCollection> candidateTracksOut1(new reco::TrackCollection(candidateOutTracks));
  ev.put(std::move(candidateTracksOut1));


  /*
  //put tracks into a(several) reco::Candidate collection (need a mass hypothesis for each collection...)
  std::unique_ptr<edm::OwnVector<reco::Candidate> > tracksOut2(new edm::OwnVector<reco::Candidate>(*outTracks));
  ev.put(std::move(tracksOut2));

  std::unique_ptr<reco::CandidateCollection> tracksOut3(new reco::CandidateCollection(*outTracks));
  ev.put(std::move(tracksOut3));
  */
}

reco::Vertex HadWTrackSelector::findEventPV(reco::VertexCollection vertices, reco::CompositeCandidate jPsiCand) 
//reco::VertexRef findEventPV(reco::VertexCollection vertices, reco::CompositeCandidate jPsiCand) 
//reco::VertexRefVector findEventPV(reco::VertexCollection vertices, reco::CompositeCandidate jPsiCand) 
{
  reco::Vertex bestMatch;
  //double minDR  = 1000.;
  //double minDxy = 1000.;
  //double minDz  = 1000.;
  //double minD0  = 1000.;
  for (auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
    //jPsiCand.dau1;
    //jPsiCand.dau2;
    //minDR  = 1000.;
    //minDxy = 1000.;
    //minDz  = 1000.;
    //minD0  = 1000.;
    continue;
  }
  return bestMatch;
}

bool HadWTrackSelector::trackToJPsiVertex(reco::Track track, reco::Vertex vertex) 
{
  return false;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void HadWTrackSelector::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void HadWTrackSelector::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
  void HadWTrackSelector::beginRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
  void HadWTrackSelector::endRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
  void HadWTrackSelector::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
  void HadWTrackSelector::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void HadWTrackSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HadWTrackSelector);
