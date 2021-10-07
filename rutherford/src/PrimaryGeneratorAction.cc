
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction() {
  // create the particle-gun object
  G4int nParticle = 1;
  fParticleGun = new G4ParticleGun(nParticle);
  SetDefaultKinematic();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
  fParticleGun->GeneratePrimaryVertex(evt);
}

void PrimaryGeneratorAction::SetDefaultKinematic() {
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  const G4String& particleName = "alpha";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(4.267 * MeV);  // alpha emission from U238

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
  fParticleGun->SetParticlePosition(G4ThreeVector(-2. * cm, 0., 0.));
  fParticleGun->SetParticleEnergy(100 * MeV);
}
