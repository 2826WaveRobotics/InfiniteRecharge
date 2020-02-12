#pragma once

#include "frc/Servo.h"
#include "frc2/command/Subsystem.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "frc/DigitalInput.h"
#include "frc/PowerDistributionPanel.h"

class Climb: public frc2::Subsystem {
private:
    rev::CANSparkMax *climbMotor;
    frc::Servo *ratchetServo;
  
public:
    Climb();

    double GetServoPosition();
    void SetServoPosition(double position);
    void ToggleServoLock(bool lock);
    void SetClimbSpeed(double speed);
};