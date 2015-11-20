#ifndef JetParticleAssociation_H 
#define JetParticleAssociation_H

// Reference to the particle
// author: C. Bernet, B. Hegner

#include "datamodel/JetHandle.h"
#include "datamodel/ParticleHandle.h"

namespace fccedm {

class JetParticleAssociation {
public:
  JetHandle Jet; //Reference to the jet 
  ParticleHandle Particle; //Reference to the particle 

};

} // Namespace
#endif
