#pragma once

#include "frc2/command/Subsystem.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "LimeLight.h"

class Turret: public frc2::Subsystem {
private:	
	rev::CANSparkMax *turretMotor;
    double m_defaultSpeed = 0;
	LimeLight *limeLight;
	bool m_trackingActive;

public:
	Turret(LimeLight *camera);
	
	virtual void Periodic(); //Should be called all of the time from the system Scheduler
	void SetTracking(bool enable);
	void SetTurretSpeed(double speed);
};

