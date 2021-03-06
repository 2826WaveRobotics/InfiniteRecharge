#include "Commands/FireBalls.h"
#include "Commands/SetShooterSpeedCommand.h"
#include "Commands/ArcadeDriveCommand.h"
#include "Commands/RaiseTowerCommand.h"
#include "Commands/WaveWaitCommand.h"
#include "Commands/TowerAndDrive.h"

using namespace frc2;

FireBalls::FireBalls() {
  AddCommands
  (
      // Add commands in the sequence you want them to run.
      // When one finishes, the next will start.

      // Add commands comma separated. No comma after the last one
      
      SetShooterSpeedCommand(2600),
      TowerAndDrive()
  );
}
