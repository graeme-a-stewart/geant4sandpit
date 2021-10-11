// Simple Geant4 Application that sets up a Rutherford scattering experiment
//
// https://en.wikipedia.org/wiki/Rutherford_scattering
//
// Particle gun setup to fire alpha particles against a gold foil

// Include global-definitions
#include "globals.hh"

// Simple RunManager
#include "G4RunManager.hh"

// Your detector construction
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

// To be able to use and combine the reference physics lists
#include "G4PhysListFactory.hh"

// For the UI manager (to execute the G4 macro input file)
#include "G4UImanager.hh"

// For VIS and/or UI-session
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

// For scoring
#include "G4ScoringManager.hh"

int main(int argc, char** argv) {
  // Setup for interactive session only
  //
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  // Construct a run manager (Sequential)
  //
  G4RunManager* runManager = new G4RunManager();

  // Set (MANDATORY) User initialization classes:
  //  = 1. G4VUserDetectorConstruction
  //  = 2. G4VUserPhysicsList
  //  = 3. G4VUserActionInitialization (that contains
  //  G4VUserPrimaryGeneratorAction)
  //
  // 1. DetectorConstruction = DetectorConstruction <-
  // G4VUserDetectorConstruction
  G4VUserDetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  // 2. PhysicsList = G4VModularPhysicsList <- G4VUserPhysicsList
  //    (use reference physics list through the G4PhysListFactory)
  const G4String plName = "FTFP_BERT_EMZ";
  G4PhysListFactory plFactory;
  G4VModularPhysicsList* pl = plFactory.GetReferencePhysList(plName);
  runManager->SetUserInitialization(pl);
  //
  // 3. ActionInitialization = ActionInitialization <-
  // G4VUserActionInitialization
  //    (and ActionInitialization contains PrimaryGeneratorAction which
  //    is
  //     <- G4VUserPrimaryGeneratorActions)
  //    Note, that:
  //     - all other UserActions (Run, Event, Stepping, Tracking, Stacking) are
  //     optional !
  //     - the DetectorConstruction pointer is propagated down to the
  //     UserActions
  //       because some actions (e.g. PrimaryGenerator) needs information from
  //       the detector.
  runManager->SetUserInitialization(new ActionInitialization());

  // Add scoring
  // - this allows scoring commands be used in the UI
  G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();

  // Add visualization:
  // - create a G4VisExecutive object as the Visualization Manager
  // - initialize the Visualization Manager (will handle all vis components)
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  // - interactive mode: create ui-session
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  UImanager->ApplyCommand("/control/execute vis.mac");
  ui->SessionStart();

  // Here we are after the ui-session termination!
  delete ui;

  // Delete the Visualization Manager
  delete visManager;

  // At the end, delete the Run Manager
  delete runManager;

  return 0;
}
