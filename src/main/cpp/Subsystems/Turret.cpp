#include "Subsystems/Turret.h"
#include "frc/SmartDashboard/SmartDashboard.h"
#include "frc/LiveWindow/LiveWindow.h"
#include "Reference.h"
#include "Subsystems/LimeLight.h"

using namespace rev;


Turret::Turret()  {
    turretMotor = new CANSparkMax(TURRET, CANSparkMaxLowLevel::MotorType::kBrushless);
}

// Gets values from LimeLight for vision tracking
void Turret::RunTurretTracking(LimeLight *limeLight)
{
    double offset = limeLight->getTarget();
    SetTurretSpeed(offset);
}

// Sets turret speed for manual override
void Turret::SetTurretSpeed(double speed)
{
	turretMotor->Set(speed);
}





