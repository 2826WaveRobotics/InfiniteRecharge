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
    shooter1->SetNeutralMode(phoenix::motorcontrol::Coast);
    shooter2->SetNeutralMode(phoenix::motorcontrol::Coast);
    shooterGroup = new frc::SpeedControllerGroup(*shooter1, *shooter2);
    tower1 = new CANSparkMax(TOWER_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    tower2 = new CANSparkMax(TOWER_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    tower1->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    tower2->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    towerGroup = new frc::SpeedControllerGroup(*tower1, *tower2);
    
    m_defaultSpeed = 0;

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
    static double s_lastSetSpeed = 0;
    if(rpm != s_lastSetSpeed)
    {
        if(rpm > 0)
        {
            SetSetpoint(rpm);
            Enable();
        }
        else
        {
            Disable();
        }
    }
    s_lastSetSpeed = rpm;    
}

void ShooterPID::SetTowerSpeed(double speed)
{
    towerGroup->Set(speed);
}

