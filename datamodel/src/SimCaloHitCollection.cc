#include "datamodel/SimCaloHitCollection.h"

namespace fccedm {

SimCaloHitCollection::SimCaloHitCollection() : m_collectionID(0), m_data(new SimCaloHitVector() ){
}

const SimCaloHitHandle& SimCaloHitCollection::get(int index) const{
  return m_handles[index];
}

SimCaloHitHandle SimCaloHitCollection::create() {
  m_data->emplace_back(SimCaloHit());
  int index = m_data->size()-1;
  // std::cout<<"creating handle: "<<index<<"/"<<m_collectionID<<std::endl;
  m_handles.emplace_back(SimCaloHitHandle(index,m_collectionID, m_data));

  return m_handles.back();
}

SimCaloHitHandle SimCaloHitCollection::insert(const SimCaloHitHandle& origin) {
  m_data->emplace_back(origin.read());
  int index = m_data->size()-1;
  m_handles.emplace_back(SimCaloHitHandle(index,m_collectionID, m_data));

  return m_handles.back();
}  

void SimCaloHitCollection::clear(){
  m_data->clear();
  m_handles.clear();

}

void SimCaloHitCollection::prepareForWrite(const albers::Registry* registry){

}

void SimCaloHitCollection::prepareAfterRead(albers::Registry* registry){
  m_handles.clear();
  int index = 0;
  // fix. otherwise, m_collectionID == 0..
  m_collectionID = registry->getIDFromPODAddress( _getBuffer() );
  for (auto& data : *m_data){
    
    m_handles.emplace_back(SimCaloHitHandle(index,m_collectionID, m_data));
    ++index;
  }
}


void SimCaloHitCollection::setPODsAddress(const void* address){
  m_data = (SimCaloHitVector*)address;
}


const SimCaloHitHandle SimCaloHitCollectionIterator::operator* () const {
  return m_collection->get(m_index);
}

//std::vector<std::pair<std::string,albers::CollectionBase*>>& referenceCollections() {
//}


void SimCaloHitCollection::print() const {
  std::cout<<"collection "<<m_collectionID
           <<", buf "<<m_data
           <<", nhandles "<<m_handles.size()<<std::endl;
}

} // Namespace
