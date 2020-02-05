#include "Subsystems/DrivePID.h"
#include "Reference.h"

using namespace rev;

DrivePID::DrivePID() : PIDSubsystem(frc2::PIDController( 1.0, 0.0, 0.0)),
    pidController(GetController())
 {
    pidController.DisableContinuousInput();
    pidController.SetTolerance(0.2);

    left1 = new CANSparkMax(DRIVE_LEFT_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    left2 = new CANSparkMax(DRIVE_LEFT_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    left3 = new CANSparkMax(DRIVE_LEFT_3, CANSparkMaxLowLevel::MotorType::kBrushless);
    leftSide = new frc::SpeedControllerGroup(*left1, *left2, *left3);

    right1 = new CANSparkMax(DRIVE_RIGHT_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    right2 = new CANSparkMax(DRIVE_RIGHT_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    right3 = new CANSparkMax(DRIVE_RIGHT_3, CANSparkMaxLowLevel::MotorType::kBrushless);
    rightSide = new frc::SpeedControllerGroup(*right1, *right2, *right3);

    // The conversion factor will be a combo of the gear ratio and wheel circumference.
    // This will be multiplied by the number of motor rotations so that calling GetPosition()
    // Returns a distance rather than a raw number of turns.  
    left1->GetEncoder().SetPositionConversionFactor(0.25);
 
        // Use these to get going:
        // SetSetpoint() -  Sets where the PID controller should move the system
        //                  to
        // Enable() - Enables the PID controller.
}

double DrivePID::GetMeasurement() {
    // Return your input value for the PID loop
    return left1->GetEncoder().GetPosition();
}

void DrivePID::UseOutput(double output, double setpoint) {
    // Use output to drive your system, like a motor
    // e.g. yourMotor->Set(output);
    leftSide->PIDWrite(output);
}




