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


#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/Common/interface/OneToOne.h"
#include "DataFormats/Math/interface/deltaR.h"


HadWTrackSelector::HadWTrackSelector(const edm::ParameterSet& pset):
  m_vertexTag(   pset.getParameter<edm::InputTag>("vertexCol")),
  m_jpsiCandsTag(pset.getParameter<edm::InputTag>("jpsiCands")),
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

  produces<reco::TrackCollection>();
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


void
HadWTrackSelector::produce(edm::Event& ev, const edm::EventSetup& es)
{
  using namespace edm;
  using namespace reco;

  edm::Handle<> pIn;
  ev.getByLabel("example",pIn);
  /* This is an event example
  edm::Handle<ExampleData> pIn;
  ev.getByLabel("example",pIn);

  //Use the ExampleData to create an ExampleData2 which 
  // is put into the Event
  std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
  ev.put(std::move(pOut));
  */

  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  es.get<SetupRecord>().get(pSetup);
  */
 
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
HadWTrackSelector::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
HadWTrackSelector::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
  void
  HadWTrackSelector::beginRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
  void
  HadWTrackSelector::endRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
  void
  HadWTrackSelector::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
  void
  HadWTrackSelector::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HadWTrackSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HadWTrackSelector);
