#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H

class TLorentzVector;

namespace fccedm {
  class LorentzVector;
}

namespace utils {

  /// Converts a LorentzVector POD to a TLorentzVector
  TLorentzVector lvFromPOD(const fccedm::LorentzVector& lv);

  /// Converts a TLorentzVector to a LorentzVector POD
  fccedm::LorentzVector lvToPOD(const TLorentzVector& tlv);

  /// difference eta1-eta2
  float deltaEta(const fccedm::LorentzVector& lv1, const fccedm::LorentzVector& lv2);

  /// difference phi1-phi2
  float deltaEta(const fccedm::LorentzVector& lv1, const fccedm::LorentzVector& lv2);

  /// dR2.
  ///
  /// Faster than deltaR because no call to sqrt
  float deltaR2(const fccedm::LorentzVector& lv1, const fccedm::LorentzVector& lv2);

  /// dR
  float deltaR(const fccedm::LorentzVector& lv1, const fccedm::LorentzVector& lv2);
}

#endif
