// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/zCommand.h"


OI::OI() {
    // Process operator interface input here.
    op = new frc::XboxController(1);

    driver = new frc::XboxController(0);


    // SmartDashboard Buttons
   //  frc::SmartDashboard::PutData("zCommand", new zCommand());
}


frc::XboxController* OI::getDriver() {
   return driver;
}

frc::XboxController* OI::getOperator() {
   return op;
}

