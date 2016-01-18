// standard includes
#include <stdexcept>


#include "MissingEnergyCollection.h"



MissingEnergyCollection::MissingEnergyCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new MissingEnergyDataContainer() ) {
  
}

const MissingEnergy MissingEnergyCollection::operator[](unsigned int index) const {
  return MissingEnergy(m_entries[index]);
}

const MissingEnergy MissingEnergyCollection::at(unsigned int index) const {
  return MissingEnergy(m_entries.at(index));
}

int  MissingEnergyCollection::size() const {
  return m_entries.size();
}

MissingEnergy MissingEnergyCollection::create(){
  auto obj = new MissingEnergyObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return MissingEnergy(obj);
}

void MissingEnergyCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void MissingEnergyCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }
  
}

void MissingEnergyCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new MissingEnergyObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool MissingEnergyCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void MissingEnergyCollection::push_back(ConstMissingEnergy object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void MissingEnergyCollection::setBuffer(void* address){
  m_data = static_cast<MissingEnergyDataContainer*>(address);
}


const MissingEnergy MissingEnergyCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const MissingEnergy* MissingEnergyCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const MissingEnergyCollectionIterator& MissingEnergyCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


