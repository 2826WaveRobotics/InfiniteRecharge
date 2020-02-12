#include "Subsystems/Climb.h"
#include "Reference.h"

using namespace rev;

Climb::Climb() {
    climbMotor = new CANSparkMax(CLIMB, CANSparkMaxLowLevel::MotorType::kBrushless);
    ratchetServo = new frc::Servo(0);
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

// Sets climb speed
void Climb::SetClimbSpeed(double speed)
{
    climbMotor->Set(speed);
}