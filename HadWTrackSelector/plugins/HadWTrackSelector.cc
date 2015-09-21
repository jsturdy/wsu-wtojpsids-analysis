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
  m_vertexTag(   consumes<std::vector<reco::Vertex> > (pset.getParameter<edm::InputTag>("vertexCol"))),
  m_jPsiCandsTag(consumes<std::vector<reco::CompositeCandidate> > (pset.getParameter<edm::InputTag>("jpsiCands"))),
  m_tracksTag(   consumes<std::vector<reco::Track> > (pset.getParameter<edm::InputTag>("tracks"   ))),
  m_modes(       pset.getParameter<std::vector<std::string> >("mode")),
  m_minMass( pset.getParameter<double>("minMass"  )),
  m_seedPt ( pset.getParameter<double>("seedPt"   )),
  m_minTrkPt(pset.getParameter<double>("minTrkPt" )),
  m_minDR(   pset.getParameter<double>("minDR"    )),
  m_isoDR(   pset.getParameter<double>("isoDR"    )),
  m_maxDxy(  pset.getParameter<double>("maxTrkDxy")),
  m_maxDz(   pset.getParameter<double>("maxTrkDz" )),
  m_maxD0(   pset.getParameter<double>("maxTrkD0" )),
  m_debug(   pset.getParameter<bool>("debug" ))
{
  produces<reco::TrackCollection>("allTracks");
  produces<reco::TrackCollection>("isoTracks");
  produces<reco::TrackCollection>("candTracks");

  //produces<edm::OwnVector<reco::Candidate> >();
  //produces<reco::CandidateCollection>();
  
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
  ev.getByToken(m_vertexTag,vertices);

  edm::Handle<std::vector<reco::CompositeCandidate> > jPsiCands;
  ev.getByToken(m_jPsiCandsTag,jPsiCands);

  edm::Handle<reco::TrackCollection> allTracks;
  ev.getByToken(m_tracksTag,allTracks);

  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  es.get<SetupRecord>().get(pSetup);
  */
  
  if (!(jPsiCands.isValid() && vertices.isValid() && allTracks.isValid())) {
    if (m_debug)
      std::cout << "vertices.isValid() "  << vertices.isValid()  << std::endl
		<< "jPsiCands.isValid() " << jPsiCands.isValid() << std::endl
		<< "allTracks.isValid() " << allTracks.isValid() << std::endl
		<< "found an invalid handle, not completing processing" << std::endl;
    
    //put the products into the event
    std::unique_ptr<reco::TrackCollection> allTracksOut1(new reco::TrackCollection());
    ev.put(std::move(allTracksOut1),"allTracks");

    std::unique_ptr<reco::TrackCollection> isolatedTracksOut1(new reco::TrackCollection());
    ev.put(std::move(isolatedTracksOut1),"isoTracks");

    std::unique_ptr<reco::TrackCollection> candidateTracksOut1(new reco::TrackCollection());
    ev.put(std::move(candidateTracksOut1),"candTracks");

    return;
  }

  if ((!jPsiCands->size()) || (!vertices->size()) || (!allTracks->size())) {
    if (m_debug)
      std::cout << "vertices->size() "  << vertices->size()  << std::endl
		<< "jPsiCands->size() " << jPsiCands->size() << std::endl
		<< "allTracks->size() " << allTracks->size() << std::endl
		<< "found an empty collection, not completing processing" << std::endl;
    
    //put the products into the event
    std::unique_ptr<reco::TrackCollection> allTracksOut1(new reco::TrackCollection());
    ev.put(std::move(allTracksOut1),"allTracks");

    std::unique_ptr<reco::TrackCollection> isolatedTracksOut1(new reco::TrackCollection());
    ev.put(std::move(isolatedTracksOut1),"isoTracks");

    std::unique_ptr<reco::TrackCollection> candidateTracksOut1(new reco::TrackCollection());
    ev.put(std::move(candidateTracksOut1),"candTracks");

    return;
  }

  //what to do if there are multiple J/Psi candidates?  do a loop for each one and create a collection and association map?
  
  reco::TrackCollection allOutTracks;       // all tracks passing the minimum pT cut and vertex matching
  reco::TrackCollection isolatedOutTracks;  // all tracks that are, in addition, well isolated from the J/Psi candidate
  reco::TrackCollection candidateOutTracks; // all tracks that are in a cone around our seed track

  std::cout << "vertices->size() "  << vertices->size()  << std::endl
	    << "jPsiCands->size() " << jPsiCands->size() << std::endl
	    << "allTracks->size() " << allTracks->size() << std::endl
	    << std::endl;
  
  //match the J/Psi to the correct vertex
  reco::Vertex eventPV = findEventPV(*vertices, (*jPsiCands)[0]);
  std::cout << "found the eventPV" << std::endl;

  //do some processing
  for (auto track = allTracks->begin(); track != allTracks->end(); ++track) {
    if (track->pt() > m_minTrkPt) {
      //check the vertex matching
      if (trackToJPsiVertex(*track,eventPV)) {
	allOutTracks.push_back(*track);	
	if (reco::deltaR(*track,(*jPsiCands)[0]) > m_minDR)
	  isolatedOutTracks.push_back(*track);	  
      }
    }
  }
  std::cout << "Looped through the tracks" << std::endl;

  //isolatedOutTracks.sort(byPt);
  if (isolatedOutTracks.size()) {
    auto track = isolatedOutTracks.begin();
    reco::Track seedTrack = *track;
    ++track;
    for (; track != isolatedOutTracks.end(); ++track) {
      
    }
  }
  std::cout << "Looped through the isolated tracks" << std::endl;

  std::cout << "allOutTracks.size() "       << allOutTracks.size()       << std::endl
	    << "isolatedOutTracks.size() "  << isolatedOutTracks.size()  << std::endl
	    << "candidateOutTracks.size() " << candidateOutTracks.size() << std::endl
	    << std::endl;
  
  //put the products into the event
  std::unique_ptr<reco::TrackCollection> allTracksOut1(new reco::TrackCollection(allOutTracks));
  ev.put(std::move(allTracksOut1),"allTracks");
  std::cout << "put the selected tracks" << std::endl;

  std::unique_ptr<reco::TrackCollection> isolatedTracksOut1(new reco::TrackCollection(isolatedOutTracks));
  ev.put(std::move(isolatedTracksOut1),"isoTracks");
  std::cout << "put the isolated tracks" << std::endl;

  std::unique_ptr<reco::TrackCollection> candidateTracksOut1(new reco::TrackCollection(candidateOutTracks));
  ev.put(std::move(candidateTracksOut1),"candTracks");
  std::cout << "put the candidate tracks" << std::endl;


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
  //bool betterMatch = false;
  //double minDR  = 1000.;
  double minDxy = m_maxDxy;
  double minDz  = m_maxDz;
  //double minD0  = m_maxD0;

  for (auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
    //jPsiCand.dau1;
    //jPsiCand.dau2;
    /*
      //maybe instead use:
      //virtual const Point & vertex() const  = 0;
      ///// x coordinate of vertex position
      //virtual double vx() const  = 0;
      ///// y coordinate of vertex position
      //virtual double vy() const  = 0;
      ///// z coordinate of vertex position
      //virtual double vz() const  = 0;
      
      double tmp_minDxy = std::abs(jPsiCand.bestTrack()->dxy(vertex->position()));
      double tmp_minDz  = std::abs(jPsiCand.bestTrack()->dz(vertex->position()));
      double tmp_minD0  = std::abs(jPsiCand.bestTrack()->d0(vertex->position()));
    */
    double tmp1_minDxy = std::abs(jPsiCand.daughter(0)->bestTrack()->dxy(vertex->position()));
    double tmp1_minDz  = std::abs(jPsiCand.daughter(0)->bestTrack()->dz(vertex->position()));
    //double tmp1_minD0  = std::abs(jPsiCand.daughter(0)->bestTrack()->d0(vertex->position()));

    /*      
    double tmp2_minDxy = std::abs(jPsiCand.daughter(1)->bestTrack()->dxy(vertex->position()));
    double tmp2_minDz  = std::abs(jPsiCand.daughter(1)->bestTrack()->dz(vertex->position()));
    double tmp2_minD0  = std::abs(jPsiCand.daughter(1)->bestTrack()->d0(vertex->position()));
    */
    if ((tmp1_minDxy < minDxy) && 
	//(tmp1_minD0 < minD0) &&
	(tmp1_minDz < minDz)) {
      //betterMatch = true;
      bestMatch = *vertex;
      //minDR  = 1000.;
      minDxy = tmp1_minDxy;
      //minD0  = tmp1_minD0;
      minDz  = tmp1_minDz;
    }
    //continue;
  }
  return bestMatch;
}

bool HadWTrackSelector::trackToJPsiVertex(const reco::Track& track, const reco::Vertex& vertex) 
{
  //compute
  if ((std::abs(track.dxy(vertex.position())) < m_maxDxy) &&
      //(std::abs(track.d0(vertex.position()))  < m_maxD0 ) &&
      (std::abs(track.dz(vertex.position()))  < m_maxDz))
    return true;

  //were unable to match track to the supplied vertex, within parameters
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
