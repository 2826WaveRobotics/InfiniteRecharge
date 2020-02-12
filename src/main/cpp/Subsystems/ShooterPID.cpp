#include "Subsystems/ShooterPID.h"
#include "Reference.h"

using namespace rev;

ShooterPID::ShooterPID() : PIDSubsystem(frc2::PIDController( 1.0, 0.0, 0.0)),
    pidController(GetController())
{
    pidController.DisableContinuousInput();
    pidController.SetTolerance(0.2);
    
    shooter1 = new WPI_TalonFX(SHOOTER_1);
    shooter2 = new WPI_TalonFX(SHOOTER_2);
    shooterGroup = new frc::SpeedControllerGroup(*shooter1, *shooter2);
    tower1 = new CANSparkMax(TOWER_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    tower2 = new CANSparkMax(TOWER_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    towerGroup = new frc::SpeedControllerGroup(*tower1, *tower2);

    m_rpm = 0;
    
    // Use these to get going:
    // SetSetpoint() -  Sets where the PID controller should move the system
    //                  to
    // Enable() - Enables the PID controller.

}

double ShooterPID::GetMeasurement() {
    // Return your input value for the PID loop
    // e.g. a sensor, like a potentiometer:
    // yourPot->SetAverageVoltage() / kYourMaxVoltage;
    
    //Need to get raw speed. Will probably have to reference the CTRE software
    return shooter1->GetSensorCollection().GetIntegratedSensorVelocity();  
}

void ShooterPID::UseOutput(double output, double setpoint) {
    // Use output to drive your system, like a motor
    // e.g. yourMotor->Set(output);

    // In this function, floor the "output" value to zero before passing it to the motor group.
    if (output < 0)
    {
        output = 0;
    }
    shooterGroup->PIDWrite(output);
}

// Sets the shooter speed
void ShooterPID::SetShooterSpeed(double rpm)
{
    m_rpm = rpm;
    SetSetpoint(rpm);
}

// Turns the shooter on or off
void ShooterPID::ToggleShooter(bool on)
{
    if (on) {
        // Remembers the last speed the shooter was set to when turned on
        SetShooterSpeed(m_rpm);
    }
    else
    {
        SetShooterSpeed(0);
    }
}


