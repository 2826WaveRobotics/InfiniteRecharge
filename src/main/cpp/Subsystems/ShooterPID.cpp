#include "Subsystems/ShooterPID.h"
#include "Reference.h"

using namespace rev;
//static double s_lastSetSpeed = 0;
ShooterPID::ShooterPID() : PIDSubsystem(frc2::PIDController( 1.0, 0.0, 0.0)),
    pidController(GetController())
{
    pidController.DisableContinuousInput();
    pidController.SetTolerance(5);
    
    shooter1 = new CANSparkMax(SHOOTER_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    shooter2 = new CANSparkMax(SHOOTER_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    shooter1->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    shooter2->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    shooter2->SetInverted(true);
    shooterGroup = new frc::SpeedControllerGroup(*shooter1, *shooter2);
    
    m_defaultSpeed = 0;

}

double ShooterPID::GetMeasurement() {
    // Return your input value for the PID loop
    // e.g. a sensor, like a potentiometer:
    // yourPot->SetAverageVoltage() / kYourMaxVoltage;
    
    // Need to get raw speed. Will probably have to reference the CTRE software
    // return shooter1->GetSensorCollection().GetIntegratedSensorVelocity();  
    
    return shooter1->GetEncoder().GetVelocity();
}

void ShooterPID::UseOutput(double output, double setpoint) {
    // Use output to drive your system, like a motor
    // e.g. yourMotor->Set(output);

    // In this function, floor the "output" value to zero before passing it to the motor group.

//shooterGroup->PIDWrite(output);
}

// Prints the current draw of the two motors
void ShooterPID::PrintCurrent()
{
    std::cout << "Shooter Currents: " << shooter1->Get() << " & " << shooter2->GetOutputCurrent() << std::endl;
}

// Sets the motor speed
void ShooterPID::SetShooterSpeed(double speed)
{
    Disable();
    shooter1->Set(speed);
    shooter2->Set(-speed);
    
    // SetSetpoint(speed);
    // Enable();
}




// Chris sucks, this is the old code below

/*
// Sets the shooter speed
//static double s_lastSetSpeed = 0;
void ShooterPID::SetShooterSpeed(double speed)
{
        // what is the purpose of the comparison if the last set speed is always zero?
        static double s_lastSetSpeed = 0;
        
		 std::cout << "Rpm" << rpm  << std::endl;
         
		 std::cout << "last Set speed" << s_lastSetSpeed << std::endl;
        
    if(rpm != s_lastSetSpeed)
    {
         std::cout << "BI sucks" << std::endl;
        if (rpm > 0)
        {
            SetSetpoint(rpm);
            Enable();
            
            std::cout << "Enable" << std:: endl;
            std::cout << rpm << std:: endl;
        }
        else
        {
            std::cout << "Disable" << std:: endl;
            Disable();
        }
    }
    s_lastSetSpeed = rpm;    
    

}
*/