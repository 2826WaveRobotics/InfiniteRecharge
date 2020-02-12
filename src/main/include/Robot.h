#pragma once

#include "frc/TimedRobot.h"
#include <frc2/command/Command.h>
#include "frc/livewindow/LiveWindow.h"
#include "frc/smartdashboard/SendableChooser.h"

#include "Commands/zCommand.h"
#include "Subsystems/ColorWheel.h"
#include "Subsystems/DrivePID.h"
#include "Subsystems/Feeder.h"
#include "Subsystems/ShooterPID.h"
#include "Subsystems/Turret.h"
#include "Subsystems/Climb.h"
#include "Subsystems/LimeLight.h"

#include "OI.h"

class Robot : public frc::TimedRobot {
public:
	frc2::Command* autonomousCommand = nullptr;
	static std::unique_ptr<OI> oi;
	//frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	frc::SendableChooser<frc2::Command*> chooser;

	Feeder *feeder;
	LimeLight *limeLight;
	Turret *turret;
static std::shared_ptr<ShooterPID> shooterPID;
static std::shared_ptr<DrivePID> drivePID;
static std::shared_ptr<ColorWheel> colorWheel;
static std::shared_ptr<Climb> climb;
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
};
