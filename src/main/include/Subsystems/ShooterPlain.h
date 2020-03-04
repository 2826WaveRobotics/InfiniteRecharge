#pragma once

#include "frc/commands/Subsystem.h"
#include "rev/CANSparkMax.h"

class ShooterPlain: public frc::Subsystem {
private:
  rev::CANSparkMax *shooter1;
  rev::CANSparkMax *shooter2;
  //rev::CANEncoder m_encoder;
  //rev::CANPIDController m_pidController;

public:
  ShooterPlain();
  void setSpeed(double speed);
  void setRpm(double rpm);
};

