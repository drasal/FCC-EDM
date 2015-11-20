#ifndef MissingEnergyHANDLE_H
#define MissingEnergyHANDLE_H
#include "datamodel/MissingEnergy.h"

#include <vector>

// 
// author: C. Bernet, B. Hegner

namespace albers {
  class Registry;
}

namespace fccedm {

//forward declaration of MissingEnergy container
class MissingEnergyCollection;

class MissingEnergyHandle {

  friend class MissingEnergyCollection;

public:

  MissingEnergyHandle() :
  		      m_index(-1),
		      m_containerID(0),
		      m_container(0),
		      m_registry(0)
		      {}	

  MissingEnergyHandle(const MissingEnergyHandle& other) :
  		      m_index(other.m_index),
		      m_containerID(other.m_containerID),
		      m_container(other.m_container),
		      m_registry(other.m_registry)
		      {}	

//TODO: Proper syntax to use, but ROOT doesn't handle it:  MissingEnergyHandle() = default;



  // precheck whether the pointee actually exists
  bool isAvailable() const;

  // returns a const (read-only) reference to the object pointed by the Handle.
  const MissingEnergy& read() const {return m_container->at(m_index);}

  // returns a non-const (writeable) reference to the object pointed by the Handle 
  MissingEnergy& mod() {return m_container->at(m_index);}
  
  void prepareForWrite(const albers::Registry*);  // use m_container to set m_containerID properly
  
  void prepareAfterRead(albers::Registry*);   // use m_containerID to set m_container properly

  int index() const {return m_index;}

  int containerID() const {return m_containerID;}

  /// equality operator (true if both the index and the container ID are equal)
  bool operator==(const MissingEnergyHandle& other) const {
       return (m_index==other.m_index) && (other.m_containerID==other.m_containerID);
  }

  /// less comparison operator, so that Handles can be e.g. stored in sets.
  friend bool operator< (const MissingEnergyHandle& p1,
			 const MissingEnergyHandle& p2 );

private:
  MissingEnergyHandle(int index, unsigned containerID,  std::vector<MissingEnergy>* container);
  int m_index;
  unsigned m_containerID;
  mutable std::vector<MissingEnergy>* m_container; //! transient
  albers::Registry* m_registry; //! transient
  //  bool _retrieveData();
  // members to support 1-to-N relations
  

};

} // Namespace
#endif
