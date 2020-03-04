#pragma once

#include "frc2/command/SubsystemBase.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "frc/DigitalInput.h"
#include "frc/PowerDistributionPanel.h"
#include "frc/SpeedControllerGroup.h"

class Feeder: public frc2::SubsystemBase {
private:
	//frc::PowerDistributionPanel *pDBoard;

	rev::CANSparkMax *hopperLeft;
	rev::CANSparkMax *hopperRight;
	rev::CANSparkMax *intake;

	rev::CANSparkMax *tower1;
	rev::CANSparkMax *tower2;
	frc::SpeedControllerGroup *towerGroup;

	frc::DigitalInput *lowerSensor;
	frc::DigitalInput *upperSensor;

	bool m_autoFeed;

public:
	Feeder();
	
	void Periodic() override; //Should be called all of the time from the system Scheduler

	void SetIntakeSpeed(double speed);
	void SetAutoFeed(bool enable);

	void SetTowerSpeed(double speed);
	void SetHopperSpeed(double leftSpeed, double rightSpeed);
	void SetFeederSystem(double speed);

	bool GetLowerSensor();
	bool GetUpperSensor();
};

