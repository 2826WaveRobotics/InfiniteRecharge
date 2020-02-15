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
	frc::SendableChooser<frc2::Command*> chooser;

	
	static std::shared_ptr<Feeder> feeder;
	static std::shared_ptr<LimeLight> limeLight;
	static std::shared_ptr<Turret> turret;
	static std::shared_ptr<ShooterPID> shooterPID;
	static std::shared_ptr<DrivePID> drivePID;
	static std::shared_ptr<ColorWheel> colorWheel;
	static std::shared_ptr<Climb> climb;
	static std::unique_ptr<OI> oi;
	
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
};
