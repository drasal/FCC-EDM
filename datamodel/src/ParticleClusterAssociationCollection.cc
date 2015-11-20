#include "datamodel/ParticleClusterAssociationCollection.h"

namespace fccedm {

ParticleClusterAssociationCollection::ParticleClusterAssociationCollection() : m_collectionID(0), m_data(new ParticleClusterAssociationVector() ){
}

const ParticleClusterAssociationHandle& ParticleClusterAssociationCollection::get(int index) const{
  return m_handles[index];
}

ParticleClusterAssociationHandle ParticleClusterAssociationCollection::create() {
  m_data->emplace_back(ParticleClusterAssociation());
  int index = m_data->size()-1;
  // std::cout<<"creating handle: "<<index<<"/"<<m_collectionID<<std::endl;
  m_handles.emplace_back(ParticleClusterAssociationHandle(index,m_collectionID, m_data));

  return m_handles.back();
}

ParticleClusterAssociationHandle ParticleClusterAssociationCollection::insert(const ParticleClusterAssociationHandle& origin) {
  m_data->emplace_back(origin.read());
  int index = m_data->size()-1;
  m_handles.emplace_back(ParticleClusterAssociationHandle(index,m_collectionID, m_data));

  return m_handles.back();
}  

void ParticleClusterAssociationCollection::clear(){
  m_data->clear();
  m_handles.clear();

}

void ParticleClusterAssociationCollection::prepareForWrite(const albers::Registry* registry){
  for(auto& data : *m_data){
     data.Particle.prepareForWrite(registry);
    data.Cluster.prepareForWrite(registry);
  }
}

void ParticleClusterAssociationCollection::prepareAfterRead(albers::Registry* registry){
  m_handles.clear();
  int index = 0;
  // fix. otherwise, m_collectionID == 0..
  m_collectionID = registry->getIDFromPODAddress( _getBuffer() );
  for (auto& data : *m_data){
    data.Particle.prepareAfterRead(registry);
data.Cluster.prepareAfterRead(registry);

    m_handles.emplace_back(ParticleClusterAssociationHandle(index,m_collectionID, m_data));
    ++index;
  }
}


void ParticleClusterAssociationCollection::setPODsAddress(const void* address){
  m_data = (ParticleClusterAssociationVector*)address;
}


const ParticleClusterAssociationHandle ParticleClusterAssociationCollectionIterator::operator* () const {
  return m_collection->get(m_index);
}

//std::vector<std::pair<std::string,albers::CollectionBase*>>& referenceCollections() {
//}


void ParticleClusterAssociationCollection::print() const {
  std::cout<<"collection "<<m_collectionID
           <<", buf "<<m_data
           <<", nhandles "<<m_handles.size()<<std::endl;
}

} // Namespace
