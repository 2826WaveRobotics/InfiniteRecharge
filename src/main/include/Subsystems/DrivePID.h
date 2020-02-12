#pragma once

#include "AHRS.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc2/command/PIDSubsystem.h"
#include "frc/controller/PIDController.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "frc/SpeedControllerGroup.h"

class DrivePID: public frc2::PIDSubsystem {
	rev::CANSparkMax *left1;
	rev::CANSparkMax *left2;
	rev::CANSparkMax *left3;
	frc::SpeedControllerGroup *leftSide;
	rev::CANSparkMax *right1;
	rev::CANSparkMax *right2;
	rev::CANSparkMax *right3;
	frc::SpeedControllerGroup *rightSide;

 	frc2::PIDController& pidController;
	frc::DifferentialDrive *diffDrive;
	AHRS *gyro;
	
public:
	DrivePID();
	double GetMeasurement() override;
	void UseOutput(double output, double setpoint) override;
	
	void ArcadeDrive(double speed, double rotation);
	void TankDrive(double leftSpeed, double rightSpeed);
	void ResetEncoders();
	double GetEncoderDistance();
};

