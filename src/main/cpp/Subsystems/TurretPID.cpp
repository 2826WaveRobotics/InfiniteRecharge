#include "Subsystems/TurretPID.h"
#include "frc/SmartDashboard/SmartDashboard.h"
#include "frc/LiveWindow/LiveWindow.h"
#include "Reference.h"
using namespace rev;

TurretPID::TurretPID() : PIDSubsystem(frc2::PIDController( 1.0, 0.0, 0.0)),
    pidController(GetController())
{
    pidController.DisableContinuousInput();
    pidController.SetTolerance(0.2);
        
    turretMotor = new CANSparkMax(TURRET, CANSparkMaxLowLevel::MotorType::kBrushless);

    // Use these to get going:
    // SetSetpoint() -  Sets where the PID controller should move the system
    //                  to
    // Enable() - Enables the PID controller.
}

double TurretPID::GetMeasurement() {
    // Return your input value for the PID loop
    // e.g. a sensor, like a potentiometer:
    // yourPot->SetAverageVoltage() / kYourMaxVoltage;

    //Need to read the limelight values to know if we need to turn
    return 0;
}

void TurretPID::UseOutput(double output, double setpoint) {
    // Use output to drive your system, like a motor
    // e.g. yourMotor->Set(output);

    turretMotor->PIDWrite(output);
}




