
#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

// forward declarations
class G4ParticleGun;
class G4Event;
class G4String;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
 public:  // Method declarations
  // Constructor & Destructor
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  // (Pure) virtual method to generata primary events
  virtual void GeneratePrimaries(G4Event*);

 private:  // Data member declarations
  G4ParticleGun* fParticleGun = nullptr;

  void SetDefaultKinematic();
};

#endif
