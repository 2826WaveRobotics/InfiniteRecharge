#pragma once

#include "frc2/command/Subsystem.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "frc/DigitalInput.h"
#include "frc/PowerDistributionPanel.h"

class Feeder: public frc2::Subsystem {
private:
	frc::PowerDistributionPanel *pDBoard;
	frc::DigitalInput *photoEye;

	rev::CANSparkMax *hopperLeft;
	rev::CANSparkMax *hopperRight;
	rev::CANSparkMax *intake;

public:
	Feeder();

	void SetIntakeSpeed(double speed);
	void SetHopperSpeed(double speed);
	void SetIndividualHopperSpeed(double leftSpeed, double rightSpeed);
};

