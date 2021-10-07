
#include "DetectorConstruction.hh"

// for geometry definitions
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// for material definitions
#include "G4Material.hh"
#include "G4NistManager.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

// Constructor
//
DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

// Destructor
//
DetectorConstruction::~DetectorConstruction() {}

// The detector is a simple slab with a thickness along the x-direction.
//
G4VPhysicalVolume* DetectorConstruction::Construct() {
  // I. CREATE MATERIALS:
  // 1. Material for the world: low density hydrogen defined by "hand"
  G4double zet = 1.0;
  G4double amass = 1.01 * g / mole;
  G4double density = universe_mean_density;
  G4double pressure = 3.e-18 * pascal;
  G4double tempture = 2.73 * kelvin;
  G4Material* materialWorld = new G4Material("Galactic", zet, amass, density,
                                             kStateGas, tempture, pressure);

  // 2. Material for the target: set to be gold
  G4Material* targetMaterial =
      G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");

  // II. CREATE GEOMETRY:

  // a. Create the world (a box), defining first its size:
  G4double worldXSize = 4. * cm;
  G4double worldYZSize = 1. * worldXSize;
  G4Box* worldSolid = new G4Box("worldSolid",       // name
                                0.5 * worldXSize,    // half x-size
                                0.5 * worldYZSize,   // half y-size
                                0.5 * worldYZSize);  // half z-size
  G4LogicalVolume* worldLogical =
      new G4LogicalVolume(worldSolid,      // solid
                          materialWorld,   // material
                          "worldLogical");  // name
  G4VPhysicalVolume* worldPhysical =
      new G4PVPlacement(nullptr,                    // (no) rotation
                        G4ThreeVector(0., 0., 0.),  // translation
                        worldLogical,               // its logical volume
                        "World",                    // its name
                        nullptr,                    // its mother volume
                        false,                      // not used
                        0);                         // copy number

  // b. Add the foil target
  G4double targetThickness = 100 * um;
  G4double targetSize = 2 * cm;
  G4Box* targetSolid = new G4Box("targetSolid", 0.5 * targetThickness,
                                 0.5 * targetSize, 0.5 * targetSize);
  G4LogicalVolume* targetLogical =
      new G4LogicalVolume(targetSolid, targetMaterial, "targetLogical");
  fTargetPhysical = new G4PVPlacement(nullptr,  // (no) rotation
                                      G4ThreeVector(0., 0., 0.),  // translation
                                      targetLogical,  // its logical volume
                                      "Target",       // its name
                                      worldLogical,   // its mother volume
                                      false,          // not used
                                      0);             // copy number

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // III. RETURN THE World PHYSICAL-VOLUME POINTER:
  return worldPhysical;
}
