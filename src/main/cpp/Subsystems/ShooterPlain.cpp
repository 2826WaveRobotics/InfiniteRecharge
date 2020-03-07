#include "Subsystems/ShooterPlain.h"
#include "Reference.h"

using namespace rev;


ShooterPlain::ShooterPlain() : frc::Subsystem("ShooterPlain")
{
    shooter1 = new CANSparkMax(SHOOTER_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    shooter2 = new CANSparkMax(SHOOTER_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    shooter1->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    shooter2->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    shooter1->SetOpenLoopRampRate(1);
    shooter2->SetOpenLoopRampRate(1);
    shooter1->SetClosedLoopRampRate(1);
    shooter2->SetClosedLoopRampRate(1);
    shooter2->Follow(*shooter1, true);


}


void ShooterPlain::setSpeed(double speed)
{
    shooter1->Set(speed);
   // shooter2->Set(speed);
    std::cout << "Shooter Speed: " << shooter1->GetEncoder().GetVelocity() << std::endl; 
}

void ShooterPlain::setRpm(double rpm)
{
    static CANPIDController m_pidController = shooter1->GetPIDController();
    double kP = 0.0003; // 0.0003
    double kI = 0.0000005;
    double kD = 0;
    double kIz = 0;
    //double kFF = 0.00015; // 0.000015
    double kMaxOutput = 0.0;
    double kMinOutput = -1.0;
    static bool paramsHaveBeenSet = false;

    if(!paramsHaveBeenSet)
    {
        m_pidController.SetP(kP);
        m_pidController.SetI(kI);
        m_pidController.SetD(kD);
        m_pidController.SetIZone(kIz);
        //m_pidController.SetFF(kFF);
        m_pidController.SetOutputRange(kMinOutput, kMaxOutput);
        paramsHaveBeenSet = true;
    }

    m_pidController.SetReference(-rpm, rev::ControlType::kVelocity);

    // std::cout << "Speed: " << shooter1->GetEncoder().GetVelocity() << std::endl;
}

double ShooterPlain::GetVelocity()
{
    return shooter1->GetEncoder().GetVelocity();
}
