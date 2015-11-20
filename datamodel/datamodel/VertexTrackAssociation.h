#ifndef VertexTrackAssociation_H 
#define VertexTrackAssociation_H

// Weight of the track in the vertex.
// author: C. Bernet, B. Hegner

#include "datamodel/TrackHandle.h"
#include "datamodel/VertexHandle.h"

namespace fccedm {

class VertexTrackAssociation {
public:
  TrackHandle Track; //The track. 
  VertexHandle Vertex; //The vertex. 
  float Weight; //Weight of the track in the vertex. 

};

} // Namespace
#endif
