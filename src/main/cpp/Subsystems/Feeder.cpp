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


