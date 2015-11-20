#ifndef BareJet_H 
#define BareJet_H

#include "datamodel/LorentzVector.h"

namespace fccedm {

class BareJet {
public:
  unsigned Bits;
  LorentzVector P4;
  float Area;

};

} // Namespace
#endif
