#pragma once

#include "frc2/command/SubsystemBase.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "LimeLight.h"

class Turret: public frc2::SubsystemBase {
private:	
	rev::CANSparkMax *turretMotor;
	LimeLight *limeLight;

	bool m_trackingActive;
	int m_countsRemaining;

public:
	Turret(LimeLight *camera);
	
    void Periodic() override; //Should be called all of the time from the system Scheduler
	void SetTracking(bool enable);
	bool IsTracking();
	void SetTurretSpeed(double speed);
	double getHexRotationCount();
	bool clockwiseLimitReached();
	bool counterClockwiseLimitReached();
	void setBrake(bool brake);
};

