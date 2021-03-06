#pragma once

//See the docuemtation for more CommandGroup types
// https://docs.wpilib.org/en/latest/docs/software/commandbased/command-groups.html

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "frc2/command/ParallelRaceGroup.h"


class TowerAndDrive
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, TowerAndDrive> {
 public:

// Parameters may be added to the Contructor
  TowerAndDrive();
};
