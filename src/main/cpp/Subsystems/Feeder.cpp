#include "Subsystems/Feeder.h"
#include "Reference.h"
using namespace rev;

Feeder::Feeder() {
    hopperLeft = new CANSparkMax(HOPPER_LEFT, CANSparkMaxLowLevel::MotorType::kBrushless);
    hopperRight = new CANSparkMax(HOPPER_RIGHT, CANSparkMaxLowLevel::MotorType::kBrushless);
    intake = new CANSparkMax(INTAKE, CANSparkMaxLowLevel::MotorType::kBrushless);

    pDBoard = new frc::PowerDistributionPanel(0);
    //AddChild("PDBoard", pDBoard);

    photoEye = new frc::DigitalInput(6);
    //AddChild("PhotoEye", photoEye);
}

// Sets intake speed
void Feeder::SetIntakeSpeed(double speed)
{
    intake->Set(speed);
}

// Sets hopper speed for both sides
void Feeder::SetHopperSpeed(double speed)
{
    hopperLeft->Set(speed);
    hopperRight->Set(-speed);
}

// Sets hopper speed for just left side
void Feeder::SetHopperLeft(double speed)
{
    hopperLeft->Set(speed);
}

// Sets hopper speed for just right side
void Feeder::SetHopperRight(double speed)
{
    hopperRight->Set(-speed);
}
