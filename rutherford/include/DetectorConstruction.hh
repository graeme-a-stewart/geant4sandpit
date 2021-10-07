#ifndef DETECTORCONTRUCTION_HH
#define DETECTORCONTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

// forward declarations
//
class G4VPhysicalVolume;

// This class is mandatory: description of the detector

class DetectorConstruction : public G4VUserDetectorConstruction {
 public:                            // Method declarations
  DetectorConstruction();           // Constructor
  virtual ~DetectorConstruction();  // Destructor

  // The base class has the (only one) pure virtual method Construct() which
  // is invoked by the G4RunManager when it's Initialize() method is invoked.
  // The Construct() method must return the G4VPhysicalVolume pointer which
  // represents the world volume.
  // Your detector description must be implemented here in this method.
  virtual G4VPhysicalVolume* Construct();

 private:  // Data members
  // The pointer to the target physical volume
  G4VPhysicalVolume* fTargetPhysical = nullptr;
};

#endif
