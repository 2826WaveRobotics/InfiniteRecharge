#include "Subsystems/Turret.h"
#include "frc/SmartDashboard/SmartDashboard.h"
#include "frc/LiveWindow/LiveWindow.h"
#include "Reference.h"
#include "Subsystems/LimeLight.h"

using namespace rev;

//These are the max Hex Rotation Counts that the turrent is allowed to move
const double c_clockwiseMax = -262;
const double c_counterClockwiseMax = 147;

Turret::Turret(LimeLight *camera)  {
    turretMotor = new CANSparkMax(TURRET, CANSparkMaxLowLevel::MotorType::kBrushless);
    turretMotor->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    limeLight = camera;

    m_trackingActive = true;
    m_countsRemaining = 0;

    turretMotor->GetEncoder().SetPosition(0.0); //Reset the encoder
}

// Gets values from LimeLight for vision tracking
void Turret::Periodic()
{
    if(m_trackingActive)
    {
        double speed = 0;

        if (limeLight->getValidTarget()) {
            double xOffset = limeLight->getHorizontalOffset();

            // Sets the turret speed based on the target offset
            if (fabs(xOffset) < 5) {
                speed = -0.005 * xOffset;
            }
            else if (fabs(xOffset) < 8) {
                speed = -0.025 * xOffset;
            }
            else if (fabs(xOffset) < 15) {
                speed = -0.050 * xOffset;
            }
            else {
                speed = -0.200 * xOffset;
            }
        }

        SetTurretSpeed(speed);

    } // if tracking active
} // Periodic

// Sets turret speed for manual override
// Clockwise is negative motor
// Counterclockwise is positive motor
void Turret::SetTurretSpeed(double speed)
{
    if (m_countsRemaining > 0) {
        speed = 1.0;
        m_countsRemaining = m_countsRemaining - 1;
    }
    else if (m_countsRemaining < 0) {
        speed = -1.0;
        m_countsRemaining = m_countsRemaining + 1;
    }

    if (clockwiseLimitReached() && speed < 0) {
        // Once you go this far clockwise, can only have negative motor values
        speed = 0;
    }
    else if (counterClockwiseLimitReached() && speed > 0) {
        // Once you go this far counterclockwise, can only have positive motor values
        speed = 0;
    }

	turretMotor->Set(speed);
    // m_defaultSpeed = speed;
}

void Turret::SetTracking(bool enable)
{
    m_trackingActive = enable;
}

bool Turret::IsTracking() 
{
    return m_trackingActive;
}

double Turret::getHexRotationCount()
{
    double rawPosition = turretMotor->GetEncoder().GetPosition();

    return rawPosition; //45:1 gearing
}

bool Turret::clockwiseLimitReached()
{
    if (getHexRotationCount() <= c_clockwiseMax) {
        //Once you go this far clockwise, can only have negative motor values
        m_countsRemaining = 60;
        return true;
    }
    else {
        return false;
    }
    
}

bool Turret::counterClockwiseLimitReached()
{
    if (getHexRotationCount() >= c_counterClockwiseMax) {
        m_countsRemaining = -60;
        return true;
    }
    else {
        return false;
    }
}

void Turret::setBrake(bool brake) 
{
    if (brake) {
        turretMotor->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    }
    else {
        turretMotor->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    }
}


