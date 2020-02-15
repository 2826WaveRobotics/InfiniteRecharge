#include "Commands/FireBalls.h"
#include "Commands/SetShooterSpeedCommand.h"
#include "Commands/RaiseTower.h"

#include "frc2/command/WaitCommand.h"
using namespace frc2;

FireBalls::FireBalls() {
  AddCommands
  (
      //Add commands in the sequence you want them to run.
      //When one finishes, the next will start.
      //
      //Add commands comma separated. No comma after the last one
      SetShooterSpeedCommand(2000),
      WaitCommand((units::second_t)5.0), //Seconds to wait beofre we start shooting
      RaiseTower(0.5),
      WaitCommand((units::second_t)5.0), 
      RaiseTower(0.0),
      SetShooterSpeedCommand(0)
  );
}
