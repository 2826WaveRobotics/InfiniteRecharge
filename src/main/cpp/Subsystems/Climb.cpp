#include "Subsystems/Climb.h"
#include "Reference.h"

using namespace rev;
const double motorlimit = 0;
Climb::Climb() {
    climbMotor = new CANSparkMax(CLIMB, CANSparkMaxLowLevel::MotorType::kBrushless);
    ratchetServo = new frc::Servo(RATCHET_SERVO);
}

// Reads servo position
double Climb::GetServoPosition()
{
    return ratchetServo->Get();
}

// Sets servo position from 0 (Full left) to 1 (Full right)
void Climb::SetServoPosition(double position)
{
    ratchetServo->Set(position);
}

// Toggles the lock
void Climb::ToggleServoLock(bool lock)
{
    if (lock)
	{
		SetServoPosition(0.15);
	}
	else if (!lock)
	{
		SetServoPosition(0.325);
	}
}

double Climb::GetClimbRotationCount()
{
    double rawPosition = climbMotor->GetEncoder().GetPosition();

    return rawPosition; 
}

bool Climb::ClimbLimitReached()
{
    if(GetClimbRotationCount() <= motorlimit)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// Sets climb speed
void Climb::SetClimbSpeed(double speed)
{
    climbMotor->Set(speed);
}

void Climb::setBrake(bool brake){

    if (brake) {
        climbMotor->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    }
    else {
        climbMotor->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    }
}