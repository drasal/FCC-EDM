#ifndef GenVertex_H 
#define GenVertex_H

// Not sure how it's defined.
// author: C. Bernet, B. Hegner

#include "datamodel/Point.h"

namespace fccedm {

class GenVertex {
public:
  Point Position; //Vertex position in cm 
  float Ctau; //Not sure how it's defined. 

};

} // Namespace
#endif
