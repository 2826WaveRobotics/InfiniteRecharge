#pragma once

//See the docuemtation for more CommandGroup types
// https://docs.wpilib.org/en/latest/docs/software/commandbased/command-groups.html

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>


class DriveForward
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, DriveForward> {
 public:

// Parameters may be added to the Contructor
  DriveForward();
};
