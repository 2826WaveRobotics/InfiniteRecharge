#pragma once

#include "frc2/command/Subsystem.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "frc/DigitalInput.h"
#include "frc/PowerDistributionPanel.h"

class Climb: public frc2::Subsystem {
private:
    rev::CANSparkMax *climbMotor;
  
public:
    Climb();
};