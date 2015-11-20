#ifndef UTILS_JET_H
#define UTILS_JET_H

#include <vector>

namespace fccedm {
  class ParticleHandle;
  class JetHandle;
  class JetParticleAssociationCollection;
}

namespace utils {

  std::vector<fccedm::ParticleHandle> associatedParticles( const fccedm::JetHandle& jet,
						   const fccedm::JetParticleAssociationCollection& associations );
}

#endif
