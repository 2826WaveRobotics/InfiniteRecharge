#include "Robot.h"

#include <hal/FRCUsageReporting.h>

//#include <frc/Commands/Scheduler.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>

#include "Commands/FireBalls.h"
#include "frc2/command/WaitCommand.h"


std::shared_ptr<Feeder> Robot::feeder;
std::shared_ptr<LimeLight> Robot::limeLight;
std::shared_ptr<Turret> Robot::turret;
std::shared_ptr<ShooterPID> Robot::shooterPID;
std::shared_ptr<DrivePID> Robot::drivePID;
std::shared_ptr<ColorWheel> Robot::colorWheel;
std::shared_ptr<Climb> Robot::climb;
std::unique_ptr<OI> Robot::oi;


using namespace frc;
using namespace frc2;

#define LEFT  GenericHID::JoystickHand::kLeftHand
#define RIGHT GenericHID::JoystickHand::kRightHand

static double p_initialDelay = 0.0;
static bool p_servoLock = true;

void Robot::RobotInit() {
	feeder.reset(new Feeder());
	limeLight.reset(new LimeLight());
	turret.reset(new Turret(limeLight.get()));
	shooterPID.reset(new ShooterPID());
	drivePID.reset(new DrivePID());
	colorWheel.reset(new ColorWheel());
	climb.reset(new Climb());
	oi.reset(new OI());

	HAL_Report(HALUsageReporting::kResourceType_Framework,
		HALUsageReporting::kFramework_RobotBuilder);
	chooser.SetDefaultOption("zCommand", new zCommand());
	chooser.AddOption("Fire Balls", new FireBalls());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
	frc::SmartDashboard::PutNumber("Initial Delay", 0.0);
}

void Robot::DisabledInit(){
	turret.get()->SetTracking(false);
	turret.get()->SetTurretSpeed(0.0);
}

void Robot::DisabledPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::AutonomousInit() {
	p_initialDelay = frc::SmartDashboard::GetNumber("Initial Delay", 0.0);
	std::cout << "Initial Delay: " << p_initialDelay << std::endl;
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
	drivePID.get()->ArcadeDrive(0.0, 0.0);
}

void Robot::TeleopInit() {
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	limeLight.get()->updateLimeLight();
	frc2::CommandScheduler::GetInstance().Run();

	////   Drive   ////////////////////////////////////////////////////////////////////

	double driveSpeed = oi->getDriver()->GetY(LEFT);
	double driveRotation = oi->getDriver()->GetX(RIGHT);
	if (fabs(driveSpeed) < 0.1) {
		driveSpeed = 0;
	}
	if (fabs(driveRotation) < 0.1) {
		driveRotation = 0;
	}
	drivePID.get()->ArcadeDrive(driveSpeed, driveRotation);


	////   Feeder & Hopper   /////////////////////////////////////////////////////////

	double feederIn = oi.get()->getOperator()->GetTriggerAxis(LEFT);
	double feederOut = oi.get()->getOperator()->GetTriggerAxis(RIGHT);
	if (fabs(feederIn) >= 0.1) {
		feeder.get()->SetIntakeSpeed(feederIn);
	}
	else if (fabs(feederOut) >= 0.1) {
		feeder.get()->SetIntakeSpeed(-feederOut);
	}
	else {
		feeder.get()->SetIntakeSpeed(0);
	}

	if (oi.get()->getOperator()->GetAButton()) {
		feeder.get()->SetHopperSpeed(0.75);
	}
	else if (oi.get()->getOperator()->GetBButton()) {
		feeder.get()->SetIndividualHopperSpeed(0.75, -0.75);
	}
	else 
		feeder.get()->SetHopperSpeed(0);


	////   Tower & Shooter   //////////////////////////////////////////////////////////	

	double towerSpeed = oi.get()->getOperator()->GetY(LEFT);
	if (fabs(towerSpeed) < 0.1) {
		towerSpeed = 0;
	}
	shooterPID.get()->SetTowerSpeed(towerSpeed);

	 shooterPID.get()->SetShooterSpeed(500);

	std::cout << "Ball Sensor: " << shooterPID.get()->GetBallSensor() << std::endl;


	////   Vision Tracking and Turret   ///////////////////////////////////////////////	

	double turretSpeed = oi.get()->getOperator()->GetX(LEFT);
	if (fabs(turretSpeed) < 0.1) {
		turret.get()->SetTracking(true);
		std::cout<<"set tracking true"<<std::endl;
	}
	else {
		turret.get()->SetTracking(false);
		turret.get()->SetTurretSpeed(turretSpeed);
		std::cout<<"set tracking false"<<std::endl;
	}


	////   Color Wheel   //////////////////////////////////////////////////////////////	

	colorWheel.get()->printClosestColor();


	////  CLimb & Servo   /////////////////////////////////////////////////////////////

	if (oi.get()->getDriver()->GetBackButton()) {
		p_servoLock = !p_servoLock;
	}
	climb.get()->ToggleServoLock(p_servoLock);
	std::cout << "Servo Position: " << climb.get()->GetServoPosition() << std::endl;

	climb.get()->SetClimbSpeed(oi.get()->getDriver()->GetTriggerAxis(RIGHT));
	climb.get()->SetClimbSpeed(-(oi.get()->getDriver()->GetTriggerAxis(LEFT)));

} 
// End TeleopPeriodic

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif