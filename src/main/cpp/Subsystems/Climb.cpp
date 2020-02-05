#include "Subsystems/Climb.h"
#include "Reference.h"

using namespace rev;

Climb::Climb() {
    climbMotor = new CANSparkMax(CLIMB, CANSparkMaxLowLevel::MotorType::kBrushless);
}