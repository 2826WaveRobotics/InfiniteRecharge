#include "Commands/DriveForward.h"
#include "Commands/ArcadeDriveCommand.h"
#include "Commands/WaveWaitCommand.h"

using namespace frc2;

DriveForward::DriveForward() {
  AddCommands
  (
      // Add commands in the sequence you want them to run.
      // When one finishes, the next will start.

      // Add commands comma separated. No comma after the last one

    ArcadeDriveCommand(0.25, 0 , 3.0)
  );
}
