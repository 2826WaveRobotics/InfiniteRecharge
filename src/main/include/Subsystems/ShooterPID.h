#pragma once

#include "frc2/command/PIDSubsystem.h"
#include "frc/controller/PIDController.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "frc/Encoder.h"
#include "frc/SpeedControllerGroup.h"
#include "frc/DigitalInput.h"

class ShooterPID: public frc2::PIDSubsystem {
	//TalonFX is the Falcon motor controller
	rev::CANSparkMax *shooter1;
	rev::CANSparkMax *shooter2;
	frc::SpeedControllerGroup *shooterGroup;
	frc2::PIDController& pidController;

    rev::CANSparkMax *tower1;
	rev::CANSparkMax *tower2;
	frc::SpeedControllerGroup *towerGroup;

	frc::DigitalInput *ballSensor;

	double m_defaultSpeed;
public:
	ShooterPID();
	double GetMeasurement() override;
	void UseOutput(double output, double setpoint) override;
	
	void SetShooterSpeed(double rpm);
	void SetTowerSpeed(double speed);
	bool GetBallSensor();
};

