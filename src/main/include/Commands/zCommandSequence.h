#pragma once

//See the docuemtation for more CommandGroup types
// https://docs.wpilib.org/en/latest/docs/software/commandbased/command-groups.html

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>


class zCommandSequence
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, zCommandSequence> {
 public:

// Parameters may be added to the Contructor
  zCommandSequence();
};
