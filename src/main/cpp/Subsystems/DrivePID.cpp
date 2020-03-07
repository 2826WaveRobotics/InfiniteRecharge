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
    left1->SetOpenLoopRampRate(0.2);
    left2->SetOpenLoopRampRate(0.2);
    left3->SetOpenLoopRampRate(0.2);
    leftSide = new frc::SpeedControllerGroup(*left1, *left2, *left3);

    right1 = new CANSparkMax(DRIVE_RIGHT_1, CANSparkMaxLowLevel::MotorType::kBrushless);
    right2 = new CANSparkMax(DRIVE_RIGHT_2, CANSparkMaxLowLevel::MotorType::kBrushless);
    right3 = new CANSparkMax(DRIVE_RIGHT_3, CANSparkMaxLowLevel::MotorType::kBrushless);
    right1->SetOpenLoopRampRate(0.2);
    right2->SetOpenLoopRampRate(0.2);
    right3->SetOpenLoopRampRate(0.2);
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
    diffDrive->ArcadeDrive(-speed, rotation, true);
    //std::cout << "Arcade Drive Speed: " << -speed << " Rotation: " << rotation << std::endl;
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


// //Set heading setpoint for gyro and turning
// void DrivePID::SetDirection(double heading) {
// 	if(pidController.GetSetpoint() != heading)
// 	{
// 		Disable();
// 		pidController.Reset();

// 		pidController.SetSetpoint(heading); //we are now facing the same way the entire time
// 		Enable();
// 	}
// }

// //Drive straight, manually applying correction
// void DrivePID::DriveStraight(double power, double heading) {

// 	double yaw = gyro->GetYaw();
// 	SetDirection(heading);
// 	double correction = fabs(pidController.());
// 	bool direction;

// 	if(yaw > 0){
// 		if((heading < yaw)&& (heading > (-180 + yaw))){
// 			direction = 1; //Left
// 		}
// 		else{
// 			direction = 0;
// 		}
// 	}
// 	else if(yaw < 0){
// 		if((heading > yaw)&& (heading < (180 + yaw))){
// 			direction = 0; //Right
// 		}
// 		else{
// 			direction = 1;
// 		}
// 	}

// 	if((correction > 0.01) && (correction < 0.2)){
// 		correction = 0.2;
// 	}
// 	else if((correction > -0.2) && (correction < -0.01)){
// 		correction = -0.2;
// 	}

// 	std::cout << "Correction: " << correction << std::endl;

// 	if((power < 0) && (direction == 1)){
// 		diffDrive->TankDrive(power+correction, power, false);
// 	}
// 	else if((power < 0) && (direction == 0)){
// 		diffDrive->TankDrive(power, power+correction, false);
// 	}
// 	else if((power > 0) && (direction == 1)){
// 		diffDrive->TankDrive(power+correction, power, false);
// 	}
// 	else if((power > 0) && (direction == 0)){
// 		diffDrive->TankDrive(power, power+correction, false);
// 	}
// 	else{
// 		diffDrive->TankDrive(power, power);
// 	}

// }

// //Accelerate until stopping distance
// void DrivePID::DriveAccelerate(double distance, double power, double heading){
// 	//SetSidePower(power, power);
// 	DriveStraight(power, heading+1);
// 	double distanceDiff = fabs(fabs(GetDistance())-(fabs(distance)));

// 	double velocity = fabs(GetVelocity());
// 	double stoppingDist = velocity*1.35;

// 	std::cout << "Velocity: " << velocity << "   Distance Difference:  " << distanceDiff
// 			<< "  Stopping Distance:  " << stoppingDist << std::endl;

// 	if(distanceDiff <= stoppingDist){
// 		driveState = c_deaccelerate;
// 		std::cout << "  Change to Deaccelerate  " << std::endl;
// 	}
// }

// //Deaccelerate by coasting
// void DrivePID::DriveDeaccelerate(double distance, double power){
// 	std::cout << "   Drive Deaccelerate   " << std::endl;
// 	SetSidePower(0, 0);
// 	double velocity = fabs(GetVelocity());
// 	if(velocity < (10)){
// 		std::cout << "   Change to Drive Stop    " << std::endl;
// 		driveState = c_stop;
// 	}
// }

// //Drive a distance within two inches
// void DrivePID::DriveDistance(double distance, double power, double heading){
// 	//double yaw = GetYaw();
// 	SetDirection(heading+1);

// 	if(driveState == c_accelerate){
// 		DriveAccelerate(distance, power, heading);
// 	}
// 	else if(driveState == c_deaccelerate){
// 		DriveDeaccelerate(distance, power);
// 	}
// 	else{
// 		DriveStop(power);
// 	}
// }

// //Apply power inverse to velocity to stop
// void DrivePID::DriveStop(double distance){
// 	double velocity = GetVelocity();
// 	double inverseVelocity = 1/(GetVelocity()/2);
// 	std::cout << "   Drive Stop   " << " Inverse Velocity:  " << inverseVelocity << std::endl;

// 	if(velocity > 2){
// 		SetSidePower(-inverseVelocity, -inverseVelocity);
// 	}
// 	else if(velocity < -2){
// 		SetSidePower(-inverseVelocity, -inverseVelocity);
// 	}
// 	else{
// 		SetSidePower(0, 0);
// 	}
// }

// //Return distance traveled based on encoder values
// double DrivePID::GetDistance(){
// 	double rightDist = GetRightEncoder()*(-1);
// 	double leftDist = GetLeftEncoder();
// 	double m_distanceTraveled;

// 	if(rightDist < 0 ){
// 		m_distanceTraveled =  (rightDist+leftDist)/2;
// 	}
// 	else if (rightDist > 0){
// 		m_distanceTraveled = ((rightDist+leftDist)/2)*(-1);
// 	}
// 	else{
// 		m_distanceTraveled = 0;
// 	}

// 	return m_distanceTraveled;
// }


// //Zero drive encoders
// void DrivePID::ZeroEncoders(){
// 	//Use this if the encoders are plugged into the Roborio
// 	rightEncoder->Reset();
// 	leftEncoder->Reset();

// 	//Use this if the encoders are plugged into the talons
// //	right1->GetSensorCollection().SetQuadraturePosition(0, 50);
// //	left1->GetSensorCollection().SetQuadraturePosition(0, 50);
// }

// //Return yaw from gyro
// float DrivePID::GetYaw(){
// 	return gyro->GetYaw();
// }

// //Zero gyro yaw
// void DrivePID::ZeroYaw(){
// 	gyro->ZeroYaw();
// }
