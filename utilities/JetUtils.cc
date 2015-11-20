#include "JetUtils.h"

#include "datamodel/ParticleHandle.h"
#include "datamodel/JetHandle.h"
#include "datamodel/JetParticleAssociationCollection.h"
#include <iostream>

namespace utils {

  std::vector<fccedm::ParticleHandle> associatedParticles( const fccedm::JetHandle& jet,
						   const fccedm::JetParticleAssociationCollection& associations ) {

    std::vector<fccedm::ParticleHandle> result;
    if(not jet.isAvailable()) {
      std::cerr<<"Jet handle is not available"<<std::endl;
      return result;
      // COLIN should throw an exception
    }
    for(const auto& assoch : associations){
      const fccedm::JetParticleAssociation& assoc = assoch.read();
      if( assoc.Jet == jet ) {
	result.emplace_back(assoc.Particle);
      }
    }
    return result;
  }

} // namespace
