#include "Subsystems/Turret.h"
#include "frc/SmartDashboard/SmartDashboard.h"
#include "frc/LiveWindow/LiveWindow.h"
#include "Reference.h"
#include "Subsystems/LimeLight.h"

using namespace rev;

Turret::Turret(LimeLight *camera)  {
    turretMotor = new CANSparkMax(TURRET, CANSparkMaxLowLevel::MotorType::kBrushless);
    turretMotor->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    m_defaultSpeed = 0;
    limeLight = camera;
    m_trackingActive = false;
}

// Gets values from LimeLight for vision tracking
void Turret::Periodic()
{
    if(m_trackingActive)
    {
        double speed = 0;

        if (limeLight->getValidTarget()) {
            double xOffset = limeLight->getHorizontalOffset();

            // Remembers which direction the target is in case the target is lost
            m_defaultSpeed = 0;
            if (xOffset < -1.5) {
                m_defaultSpeed = 1;
            }
            if (xOffset > 1.5) {
                m_defaultSpeed = -1;
            }

            // Sets the turret speed based on the target offset
            if (fabs(xOffset) < 1.5) {
                speed = -0.15 * xOffset;
            }
            else if (fabs(xOffset) < 5) {
                speed = -0.25 * xOffset;
            }
            else if (fabs(xOffset) < 10) {
                speed = -0.35 * xOffset;
            }
            else {
                speed = -0.45 * xOffset;
            }
        }

        // Will run the turret to find the missing target
        else {
            speed = m_defaultSpeed;
        }

        // Sets the turret speed
        SetTurretSpeed(speed);
    }
}//Periodic

// Sets turret speed for manual override
void Turret::SetTurretSpeed(double speed)
{
	turretMotor->Set(speed);
}

void Turret::SetTracking(bool enable)
{
    m_trackingActive = enable;
}



