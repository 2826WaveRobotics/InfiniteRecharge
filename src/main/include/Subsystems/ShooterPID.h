#pragma once

#include "frc2/command/PIDSubsystem.h"
#include "frc/controller/PIDController.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "frc/SpeedControllerGroup.h"
#include "frc/DigitalInput.h"

class ShooterPID: public frc2::PIDSubsystem {
	//TalonFX is the Falcon motor controller
	rev::CANSparkMax *shooter1;
	rev::CANSparkMax *shooter2;
	frc::SpeedControllerGroup *shooterGroup;
	frc2::PIDController& pidController;

	double m_defaultSpeed;
public:
	ShooterPID();
	double GetMeasurement() override;
	void UseOutput(double output, double setpoint) override;
	
	void PrintCurrent();
	void SetShooterSpeed(double speed);
};

