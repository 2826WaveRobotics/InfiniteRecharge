#pragma once

#include "frc2/command/PIDSubsystem.h"
#include "frc/controller/PIDController.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"

class TurretPID: public frc2::PIDSubsystem {
	frc2::PIDController& pidController;
	
	rev::CANSparkMax *turretMotor;
public:
	TurretPID();
	double GetMeasurement() override;
	void UseOutput(double output, double setpoint) override;
};

