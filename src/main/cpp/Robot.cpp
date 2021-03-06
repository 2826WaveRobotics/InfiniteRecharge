#include "Robot.h"

#include <hal/FRCUsageReporting.h>

#include <frc/Commands/Scheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>


std::shared_ptr<Feeder> Robot::feeder;
std::shared_ptr<LimeLight> Robot::limeLight;
std::shared_ptr<Turret> Robot::turret;
std::shared_ptr<ShooterPID> Robot::shooterPID;
std::shared_ptr<DrivePID> Robot::drivePID;
std::shared_ptr<ColorWheel> Robot::colorWheel;
std::shared_ptr<Climb> Robot::climb;
std::unique_ptr<OI> Robot::oi;


using namespace frc;
#define LEFT  GenericHID::JoystickHand::kLeftHand
#define RIGHT GenericHID::JoystickHand::kRightHand

double p_servoPosition = 0.35;

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
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Schedule();
}

void Robot::AutonomousPeriodic() {
	limeLight.get()->updateLimeLight();
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	limeLight.get()->updateLimeLight();
	frc::Scheduler::GetInstance()->Run();

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
	


	////    Tower & Shooter   ///////////////////////////////////////////



	////   Vision Tracking and Turret  /////////////////////////////////
	turret.get()->SetTracking(true);


	////   Color Wheel     ///////////////////////////////////////////////
	//colorWheel.get()->printClosestColor();


	////  CLimb & Servo    //////////////////////////////////////////////////////////////
	if ((oi.get()->getOperator()->GetAButtonPressed()) && (p_servoPosition < 1))
	{
		p_servoPosition = 0.15;
	}
	else if ((oi.get()->getOperator()->GetBButtonPressed()) && (p_servoPosition > 0))
	{
		p_servoPosition = 0.325;
	}
	climb.get()->SetServoPosition(p_servoPosition);
	//std::cout << "Servo Position: " << p_servoPosition << std::endl;

}//TeleopPeriodic

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif