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
    right1->GetEncoder().SetPositionConversionFactor(0.25);

    diffDrive = new frc::DifferentialDrive(*leftSide, *rightSide);
    diffDrive->SetRightSideInverted(true);
    gyro = new AHRS(frc::SPI::Port::kMXP, 100);
 
}

double DrivePID::GetMeasurement() {
    // Return your input value for the PID loop
    return gyro->GetYaw();
}


void DrivePID::UseOutput(double output, double setpoint) {
    // Use output to drive your system, like a motor
    // e.g. yourMotor->Set(output);
    leftSide->PIDWrite(output);
    rightSide->PIDWrite(output);
}

// Arcade drive
void DrivePID::ArcadeDrive(double speed, double rotation)
{
    diffDrive->ArcadeDrive(-speed, -rotation, true);
}

// Tank drive
void DrivePID::TankDrive(double leftSpeed, double rightSpeed)
{
    diffDrive->TankDrive(-leftSpeed, -rightSpeed);
}

// Resets the encoders
void DrivePID::ResetDriveEncoders()
{
    left1->GetEncoder().SetPosition(0);
    right1->GetEncoder().SetPosition(0);
}

// Gets position from encoders
double DrivePID::GetDriveEncoder() 
{
    return left1->GetEncoder().GetPosition();
}

void DrivePID::SetMotorsToBrake()
{
    left1->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    left2->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    left3->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    right1->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    right2->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    right3->SetIdleMode(CANSparkMax::IdleMode::kBrake);
}

void DrivePID::SetMotorsToCoast()
{
    left1->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    left2->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    left3->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    right1->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    right2->SetIdleMode(CANSparkMax::IdleMode::kCoast);
    right3->SetIdleMode(CANSparkMax::IdleMode::kCoast);
}
