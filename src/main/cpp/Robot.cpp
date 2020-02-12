#include "Robot.h"

#include <hal/FRCUsageReporting.h>

#include <frc/Commands/Scheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Feeder Robot::feeder;
// LimeLight Robot::limeLight;
// Turret Robot::turret;
std::shared_ptr<ShooterPID> Robot::shooterPID;
std::shared_ptr<DrivePID> Robot::drivePID;
std::shared_ptr<ColorWheel> Robot::colorWheel;
std::shared_ptr<Climb> Robot::climb;
std::unique_ptr<OI> Robot::oi;

double p_servoPosition = 0.35;

void Robot::RobotInit() {
	feeder = new Feeder();
	limeLight = new LimeLight();
	turret = new Turret();
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
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	colorWheel.get()->printClosestColor();

	if ((oi.get()->getOperator().get()->GetAButtonPressed()) && (p_servoPosition < 1))
	{
		p_servoPosition = 0.15;
	}
	else if ((oi.get()->getOperator().get()->GetBButtonPressed()) && (p_servoPosition > 0))
	{
		p_servoPosition = 0.325;
	}
	climb.get()->SetServoPosition(p_servoPosition);
	std::cout << "Servo Position: " << p_servoPosition << std::endl;

	turret->RunTurretTracking(limeLight);

}//TeleopPeriodic

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif