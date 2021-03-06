#include "Robot.h"

#include <hal/FRCUsageReporting.h>

//#include <frc/Commands/Scheduler.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include "cameraserver/CameraServer.h"
#include "Commands/FireBalls.h"
#include "frc2/command/WaitCommand.h"
#include <cscore_oo.h>



std::shared_ptr<Feeder> Robot::feeder;
std::shared_ptr<LimeLight> Robot::limeLight;
std::shared_ptr<Turret> Robot::turret;
// std::shared_ptr<ShooterPID> Robot::shooterPID;
std::shared_ptr<ShooterPlain> Robot::shooterPlain;
std::shared_ptr<DrivePID> Robot::drivePID;
std::shared_ptr<ColorWheel> Robot::colorWheel;
std::shared_ptr<Climb> Robot::climb;
std::unique_ptr<OI> Robot::oi;


using namespace frc;
using namespace frc2;

#define LEFT  GenericHID::JoystickHand::kLeftHand
#define RIGHT GenericHID::JoystickHand::kRightHand

static int p_shooterSpeed = 500;
static double p_initialDelay = 0.0;
static double p_autoTracking = true;

// static bool p_servoLock = true;

cs::UsbCamera lifeCam("lifecam", 0);

void Robot::RobotInit() {
	feeder.reset(new Feeder());
	limeLight.reset(new LimeLight());
	turret.reset(new Turret(limeLight.get()));
	// shooterPID.reset(new ShooterPID());
	shooterPlain.reset(new ShooterPlain());
	drivePID.reset(new DrivePID());
	colorWheel.reset(new ColorWheel());
	climb.reset(new Climb());
	oi.reset(new OI());
	
	lifeCam.SetBrightness(50);
	//CameraServer::GetInstance()->StartAutomaticCapture();

	HAL_Report(HALUsageReporting::kResourceType_Framework,
		HALUsageReporting::kFramework_RobotBuilder);
	chooser.SetDefaultOption("FireBalls", new FireBalls());
	// chooser.AddOption("Fire Balls", new FireBalls());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
	frc::SmartDashboard::PutNumber("Initial Delay", 0.0);
}

void Robot::DisabledInit(){
	turret.get()->SetTracking(false);
	turret.get()->SetTurretSpeed(0.0);
	turret.get()->setBrake(false);
	climb.get()->setBrake(true);
	feeder.get()->SetTowerBrakeMode(false);
}

void Robot::DisabledPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::AutonomousInit() {
	p_initialDelay = frc::SmartDashboard::GetNumber("Initial Delay", 0.0);
	std::cout << "Initial Delay: " << p_initialDelay << std::endl;
	turret.get()->setBrake(true);
	if(p_initialDelay > 0.0)
	{
		initialWaitCommand = new WaitCommand((units::second_t)p_initialDelay);
		if(initialWaitCommand != nullptr)
		{
			initialWaitCommand->Schedule();
		}
	}
	autonomousCommand = chooser.GetSelected();
	if ((autonomousCommand != nullptr) && (0.0 == p_initialDelay))
	{
		//Only schedule the Autonomous Command here if there is *no* initial Wait
		autonomousCommand->Schedule();
	}
}

void Robot::AutonomousPeriodic() {
	limeLight.get()->updateLimeLight();
	frc2::CommandScheduler::GetInstance().Run();

	if(p_initialDelay > 0.0)
	{
		//Wait until the InitialWaitCommand is done before scheduling the autonomousCommand
		if(initialWaitCommand->IsFinished() && (autonomousCommand != nullptr))
		{
			autonomousCommand->Schedule();
		}
	}
	//drivePID.get()->ArcadeDrive(0.0, 0.0);
}

void Robot::TeleopInit() {
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
	turret.get()->setBrake(true);
	climb.get()->setBrake(true);

	shooterPlain.get()->setRpm(500);
}

void Robot::TeleopPeriodic() {
	limeLight.get()->updateLimeLight();
	frc2::CommandScheduler::GetInstance().Run();
	//turret.get()->SetTracking(true); //aDDED THIS

	////   Drive    /////////////////////////////////////////////////////
	
	double rightSide = oi->getDriver()->GetY(RIGHT);
	double leftSide = oi->getDriver()->GetX(LEFT);
	rightSide=rightSide*-1;
	drivePID.get()->ArcadeDrive(rightSide*.5, leftSide*.5);


	////   Feeder & Hopper   ////////////////////////////////////////////
	if(oi->getDriver()->GetAButton())
	{
		feeder.get()->SetHopperSpeed(0.5);
	}
	else
	{
		feeder.get()->SetHopperSpeed(0.0);
	}
	


	////   Feeder   ////////////////////////////////////////////////////////////////////

	feeder.get()->SetAutoFeed(false);
	double feederIn = oi.get()->getOperator()->GetTriggerAxis(LEFT);
	bool feederOut = oi.get()->getOperator()->GetBumper(LEFT);
	if (fabs(feederIn) >= 0.1) {
		feeder.get()->SetIntakeSpeed(feederIn * 0.8);
	}
	else if (feederOut) {
		feeder.get()->SetIntakeSpeed(-0.75);
	}
	else {
		feeder.get()->SetIntakeSpeed(0.0);
	}


	////   Tower & Hopper   ////////////////////////////////////////////////////////////	
	
	double towerUp = oi.get()->getOperator()->GetTriggerAxis(RIGHT);
	bool towerDown = oi.get()->getOperator()->GetBumper(RIGHT);
	if (fabs(towerUp) >= 0.1) {
		feeder.get()->SetAutoFeed(false);
		feeder.get()->SetFeederSystem(towerUp * -0.75);
		// std::cout << "Manual Ball Feeding" << std::endl;
	}
	else if (towerDown) {
		feeder.get()->SetAutoFeed(false);
		feeder.get()->SetFeederSystem(0.75);
		// std::cout << "Manual Ball Feeding" << std::endl;
	}
	else {
		feeder.get()->SetAutoFeed(true);
		// std::cout << "Auto Ball Feeding" << std::endl;
	}


	////   Color Wheel     ///////////////////////////////////////////////
	//colorWheel.get()->printClosestColor();
//SHOOTER 
	if(oi.get()->getOperator()->GetAButtonPressed()) {
		p_shooterSpeed = 2700;
	    shooterPlain.get()->setRpm(2700);
	}
	else if(oi.get()->getOperator()->GetXButtonPressed()) {
		p_shooterSpeed = 3050;
	    shooterPlain.get()->setRpm(3050);
	}
	else if(oi.get()->getOperator()->GetBButtonPressed()) {
		p_shooterSpeed = 500;
        shooterPlain.get()->setRpm(500);
	}
	//shooterPlain.get()->setRpm(p_shooterSpeed);

	// IF the shooter is within 10 rpm of the desired speed 
	// controller will vibrate
	if ((fabs(shooterPlain.get()->GetVelocity()) >= p_shooterSpeed - 10) && (fabs(shooterPlain.get()->GetVelocity()) <= p_shooterSpeed + 10)){
		
		oi.get()->getDriver()->SetRumble(GenericHID::RumbleType::kLeftRumble, 1);
		oi.get()->getDriver()->SetRumble(GenericHID::RumbleType::kRightRumble, 1);

	}
	else
	{
		oi.get()->getDriver()->SetRumble(GenericHID::RumbleType::kLeftRumble, 0);
		oi.get()->getDriver()->SetRumble(GenericHID::RumbleType::kRightRumble, 0);
	}
	
	////   Vision Tracking and Turret   ///////////////////////////////////////////////	

	double turretSpeed = oi.get()->getOperator()->GetX(LEFT);
	if (fabs(turretSpeed) >= 0.1) {
		turret.get()->SetTracking(false);
		turret.get()->SetTurretSpeed(-turretSpeed);
		// std::cout << "Manual Turret Targeting" << std::endl;
	}
	else {
		turret.get()->SetTracking(p_autoTracking);
		if (!p_autoTracking) {
			turret.get()->SetTurretSpeed(0);
		}
	}

	if (oi.get()->getOperator()->GetStartButtonPressed()) {
		p_autoTracking = true;
	}
	if (oi.get()->getOperator()->GetBackButtonPressed()) {
		p_autoTracking = false;
	}

	// std::cout << " Rotation Count: " << turret.get()->getHexRotationCount() << std::endl;


	////   Color Wheel   //////////////////////////////////////////////////////////////	

	// colorWheel.get()->printClosestColor();


	////  CLimb & Servo   /////////////////////////////////////////////////////////////
	
	// if (oi.get()->getDriver()->GetBackButton()) {
	// 	p_servoLock = !p_servoLock;
	// }
	// climb.get()->ToggleServoLock(p_servoLock);
	//std::cout << "Servo Position: " << climb.get()->GetServoPosition() << std::endl;

	double climbspeed = oi.get()->getDriver()->GetTriggerAxis(RIGHT);
	double negativeclimbspeed = oi.get()->getDriver()->GetTriggerAxis(LEFT);

	bool operatorClimb = oi.get()->getOperator()->GetYButton();

	if (climbspeed >= 0.1) {
		climb.get()->SetClimbSpeed(climbspeed);
	}
	else if (negativeclimbspeed >= 0.1) {
		climb.get()->SetClimbSpeed(-negativeclimbspeed);
	}
	else if (operatorClimb) {
		climb.get()->SetClimbSpeed(0.35);
	}
	else {
		climb.get()->SetClimbSpeed(0);
	}
	climb.get()->SetServoPosition(p_servoPosition);
	//std::cout << "Servo Position: " << p_servoPosition << std::endl;

} 
// End TeleopPeriodic

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif