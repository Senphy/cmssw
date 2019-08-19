#ifndef RecoHGCal_TICL_TracksterMomentumPluginBase_H__
#define RecoHGCal_TICL_TracksterMomentumPluginBase_H__

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/HGCalReco/interface/Trackster.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/PluginManager/interface/PluginFactory.h"

namespace ticl {
  class TracksterMomentumPluginBase {
  public:
    TracksterMomentumPluginBase(const edm::ParameterSet&, edm::ConsumesCollector&& iC) {}
    typedef reco::Candidate::LorentzVector LorentzVector;
    virtual ~TracksterMomentumPluginBase() {}
    virtual LorentzVector calcP4(const ticl::Trackster& trackster) const = 0;

    // Allow access to event so data products can be read once at beginning of event but four-vector calculation can 
    // be run on single tracksters
    edm::Event& evt() { return *evt_; }
    
    // Needs to be called by CMSSW plugins using this plugin before being able to use other methods
    void beginEvent(edm::Event& evt) {
       evt_ = &evt;
       this->beginEvt();
     }
  private:
    virtual void beginEvt() = 0;
    edm::Event* evt_;
  };
} // namespace

typedef edmplugin::PluginFactory<ticl::TracksterMomentumPluginBase*(const edm::ParameterSet&, edm::ConsumesCollector&& iC)> TracksterMomentumPluginFactory;

#endif
