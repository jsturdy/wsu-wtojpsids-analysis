// -*- C++ -*-
//
// Package:    WSUHadronicW/HadWTrackSelector
// Class:      HadWTrackSelector
// 
/**\class HadWTrackSelector HadWTrackSelector.h WSUHadronicW/HadWTrackSelector/interface/HadWTrackSelector.h

   Description: Used to select tracks coming from potential hadronic W decays, where the resulting particles
                are a J/Psi and some c sbar (+ u ubar/d dbar) states, e.g., Ds, D0, K, pi Lambda

   Implementation:
   * The J/Psi candidates will be constructed using the PAT CandCombiner module
   * Isolation sums can be computed using the PAT tools
   * Subset of the tracks will be stored:
     - Tracks matched back to the J/Psi (the e/mu tracks)
     - Charged tracks matched back to the J/Psi vertex within a reasonable impact parameter window
     - Neutral tracks?

   * Byproducts should be isolated as they will not be colour connected to the J/Psi
   * 

*/
//
// Original Author:  Jared Sturdy
//         Created:  Tue, 25 Aug 2015 17:10:31 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"


//
// class declaration
//

class HadWTrackSelector : public edm::stream::EDProducer<> {
  public:
    explicit HadWTrackSelector(const edm::ParameterSet&);
    ~HadWTrackSelector();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
    virtual void beginStream(edm::StreamID) override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endStream() override;
    
    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    
    // ----------member data ---------------------------
    edm::InputTag m_vertexTag;    // input tag for vertex collection
    edm::InputTag m_jpsiCandsTag; // input tag for J/Psi candidates collection
    edm::InputTag m_tracksTag;    // input tag for track collection
    
    std::vector<std::string> m_modes; // decay modes to consider
    
    double m_minMass;   // minimum invariant mass for consideration
    double m_seedPt;    // minimum pT for a seed track to be considered
    double m_minTrkPt;  // minimum pT for a track to be saved
    double m_isoDR_;    // cone size for isolation requirement
    double m_maxDxy_;   // maximum Dxy impact parameter between tracks and selected PV
    double m_maxDz_;    // maximum Dz impact parameter between tracks and selected PV
    double m_maxD0_;    // maximum D0 impact parameter between tracks and selected PV
};
