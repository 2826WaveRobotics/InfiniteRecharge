#include "Subsystems/Feeder.h"
#include "Reference.h"
using namespace rev;

Feeder::Feeder() {
    hopperLeft = new CANSparkMax(HOPPER_LEFT, CANSparkMaxLowLevel::MotorType::kBrushless);
    hopperRight = new CANSparkMax(HOPPER_RIGHT, CANSparkMaxLowLevel::MotorType::kBrushless);
    intake = new CANSparkMax(INTAKE, CANSparkMax::MotorType::kBrushless);

    hopperLeft->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    hopperRight->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    intake->SetIdleMode(CANSparkMax::IdleMode::kCoast);

    tower1 = new CANSparkMax(TOWER_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    tower2 = new CANSparkMax(TOWER_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    tower1->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    tower2->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    tower2->SetInverted(true);
    tower1->SetOpenLoopRampRate(2);
    tower2->SetOpenLoopRampRate(2);
    towerGroup = new frc::SpeedControllerGroup(*tower1, *tower2);

    lowerSensor = new frc::DigitalInput(LOWER_SENSOR);
    upperSensor = new frc::DigitalInput(UPPER_SENSOR);

    m_autoFeed = true;

    //pDBoard = new frc::PowerDistributionPanel(0);
    // AddChild("PDBoard", pDBoard);
}

// Sets intake speed
void Feeder::SetIntakeSpeed(double speed)
{
    intake->Set(speed);
}

// Sets hopper speeds
void Feeder::SetHopperSpeed(double leftSpeed, double rightSpeed)
{
    hopperLeft->Set(-leftSpeed);
    hopperRight->Set(-rightSpeed);
}

// Sets the tower speed
void Feeder::SetTowerSpeed(double speed)
{
    towerGroup->Set(speed);
    
    //std::cout << "Tower Speed: " << speed << std::endl;
}

// Sets the speed for both the hopper and the tower 
void Feeder::SetFeederSystem(double speed)
{
    SetTowerSpeed(speed);
    
    speed = speed * 0.5;
    SetHopperSpeed(speed, speed * 0.25);

   // std::cout << "Feeder System: " << speed << std::endl;
}

bool Feeder::GetLowerSensor()
{
    return lowerSensor->Get();
}

bool Feeder::GetUpperSensor()
{
    return upperSensor->Get();
}

void Feeder::Periodic() 
{
    static int s_stageCounter = 0;

    if (m_autoFeed) {
        if (GetUpperSensor()) {
            SetFeederSystem(0);
        }
        else {
            // Starts feeder system
            if ((GetLowerSensor()) && (0 == s_stageCounter)) {
                s_stageCounter = 10;
            }
            // Runs feeder system
            if (s_stageCounter > 0) {
                SetFeederSystem(0.75);
                s_stageCounter--;
            }
            // Turns off feeder system
            else {
                SetFeederSystem(0);
            }
        }
    } // if (m_autoFeed)
} // Periodic

// Turns on and off automatic feeding
void Feeder::SetAutoFeed(bool enable)
{
    m_autoFeed = enable;
}

void Feeder::SetTowerBrakeMode(bool brake) 
{
    if (brake) 
    {
        tower1->SetIdleMode(CANSparkMax::IdleMode::kBrake);
        tower2->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    }
    else 
    {
        tower1->SetIdleMode(CANSparkMax::IdleMode::kCoast);
        tower2->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    }
}