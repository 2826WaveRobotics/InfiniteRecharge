#pragma once

#include "frc2/command/Subsystem.h"
#include "rev/CANSparkMax.h"
#include "frc/Encoder.h"
#include "LimeLight.h"

class Turret: public frc2::Subsystem {
private:	
	rev::CANSparkMax *turretMotor;
	
public:
	Turret();

	void RunTurretTracking(LimeLight *limeLight);
	void SetTurretSpeed(double speed);
};

