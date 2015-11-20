#ifndef TrackStateAssociation_H 
#define TrackStateAssociation_H

// The track state.
// author: C. Bernet, B. Hegner

#include "datamodel/TrackHandle.h"
#include "datamodel/TrackStateHandle.h"

namespace fccedm {

class TrackStateAssociation {
public:
  TrackHandle Track; //The track. 
  TrackStateHandle State; //The track state. 

};

} // Namespace
#endif
