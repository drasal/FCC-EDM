// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/MCParticle.h"
#include "datamodel/MCParticleCollection.h"
#include "datamodel/LorentzVector.h"

// Utility functions
#include "utilities/VectorUtils.h"

// ROOT
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"

// STL
#include <iostream>
#include <vector>

// albers specific includes
#include "albers/EventStore.h"
#include "albers/Registry.h"
#include "albers/Writer.h"

// testing tools
#include "utilities/DummyGenerator.h"



int main(){
  std::cout<<"start processing"<<std::endl;

  albers::Registry   registry;
  albers::EventStore store(&registry);
  albers::Writer     writer("simpleexample.root", &registry);

  unsigned nevents=10000;

  fccedm::EventInfoCollection& evinfocoll = store.create<fccedm::EventInfoCollection>("EventInfo");
  fccedm::MCParticleCollection& pcoll = store.create<fccedm::MCParticleCollection>("MCParticle");

  writer.registerForWrite<fccedm::EventInfoCollection>("EventInfo");

  // collections from the dummy generator
  writer.registerForWrite<fccedm::MCParticleCollection>("MCParticle");

  for(unsigned iev=0; iev<nevents; ++iev) {
    // fill event information
    fccedm::EventInfoCollection* evinfocoll = nullptr;
    // here, asking the store for the collection.
    // could also just reuse the reference obtained at the time of the creation
    // of the collection
    store.get("EventInfo", evinfocoll);
    if(evinfocoll==nullptr) {
      std::cerr<<"collection EventInfo does not exist!"<<std::endl;
      return 1;
    }
    fccedm::EventInfoHandle evinfo = evinfocoll->create();
    evinfo.mod().Number = iev;

    fccedm::MCParticleHandle ptc = pcoll.create();
    ptc.mod().Core.Type = 25;
    auto& p4 = ptc.mod().Core.P4;
    p4.Px = static_cast<float>(iev);
    p4.Py = 0.;
    p4.Pz = 0.;
    p4.Mass = 126.;

    writer.writeEvent();
    store.next();
  }

  writer.finish();

  return 0;
}
