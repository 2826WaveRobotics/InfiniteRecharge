#include "Commands/TowerAndDrive.h"
#include "Commands/SetShooterSpeedCommand.h"
#include "Commands/ArcadeDriveCommand.h"
#include "Commands/RaiseTowerCommand.h"
#include "Commands/WaveWaitCommand.h"

using namespace frc2;

TowerAndDrive::TowerAndDrive() {
  AddCommands
  (
      // Add commands in the sequence you want them to run.
      // When one finishes, the next will start.

      // Add commands comma separated. No comma after the last one
      
      //SetShooterSpeedCommand(2300),
      WaveWaitCommand(4.0), 
      RaiseTowerCommand(0.5),
      WaveWaitCommand(5.0),
      RaiseTowerCommand(0.0),
      ArcadeDriveCommand(0.25, 0 , 3.0)
  );
}
