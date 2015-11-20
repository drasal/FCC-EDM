// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/Particle.h"
#include "datamodel/ParticleCollection.h"
#include "datamodel/JetCollection.h"
#include "datamodel/JetParticleAssociationCollection.h"
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


void processEvent(unsigned iEvent, albers::EventStore& store, albers::Writer& writer, DummyGenerator& generator) {
  if(iEvent % 1000 == 0)
    std::cout<<"processing event "<<iEvent<<std::endl;

  generator.generate();

  // fill event information
  fccedm::EventInfoCollection* evinfocoll = nullptr;
  store.get("EventInfo", evinfocoll);
  if(evinfocoll==nullptr) {
    std::cerr<<"collection EventInfo does not exist!"<<std::endl;
    return;
  }
  fccedm::EventInfoHandle evinfo = evinfocoll->create();
  evinfo.mod().Number = iEvent;

  // and now for the writing
  // TODO: do that at a different time w/o coll pointer
  // COLIN: calling writeEvent should not be left up to the user.
  writer.writeEvent();
  store.next();

  return;
}


int main(){
  std::cout<<"start processing"<<std::endl;

  albers::Registry   registry;
  albers::EventStore store(&registry);
  albers::Writer     writer("example.root", &registry);

  DummyGenerator generator(10, store);
  generator.setNPrint(10);

  unsigned nevents=10000;

  fccedm::EventInfoCollection& evinfocoll = store.create<fccedm::EventInfoCollection>("EventInfo");

  writer.registerForWrite<fccedm::EventInfoCollection>("EventInfo");

  // collections from the dummy generator
  writer.registerForWrite<fccedm::ParticleCollection>("GenParticle");
  writer.registerForWrite<fccedm::JetCollection>("GenJet");
  writer.registerForWrite<fccedm::JetParticleAssociationCollection>("GenJetParticle");

  for(unsigned i=0; i<nevents; ++i) {
    processEvent(i, store, writer, generator);
  }

  writer.finish();
}
