
#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

// NOT CALLED IN SEQUENTIAL MODE i.e. ONLY FOR MT:
// - ONLY FOR creating RunAction for the Master thread
void ActionInitialization::BuildForMaster() const {}

// Create all User Actions here:
// - for sequential mode (will be invoked immediately by G4RunManager
//   when the ActionInitialization object is registered in the main)
// - for worker threads (will be invoked later by all worker RunManagers)
void ActionInitialization::Build() const {
  // Set UserPrimaryGeneratorAction
  PrimaryGeneratorAction* primaryAction = new PrimaryGeneratorAction();
  SetUserAction(primaryAction);
}
