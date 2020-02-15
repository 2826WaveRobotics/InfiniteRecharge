#pragma once

#include "frc/commands/Subsystem.h"
#include "rev/CANSparkMax.h"
#include "ctre/Phoenix.h"
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

class ColorWheel: public frc::Subsystem {
private:
  rev::CANSparkMax *colorMotor;

  static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    
  rev::ColorSensorV3 m_colorSensor{i2cPort};
  rev::ColorMatch m_colorMatcher;

  //Color values are R,G,B valid ranges are 0.0 - 1.0.  Need to take RGB value and divide by 255 (RGB is in 0 - 255)
  const frc::Color kBlueTarget = frc::Color(0.0, 1.0, 1.0);   //CMYK = 100, 0, 0, 0
  const frc::Color kGreenTarget = frc::Color(0.0, 1.0, 0.0);  //CMYK = 100, 0, 100, 0
  const frc::Color kRedTarget = frc::Color(1.0, 0.0, 0.0);    //CMYK = 0, 100, 100, 0
  const frc::Color kYellowTarget = frc::Color(1.0, 1.0, 0.0); //CMYK = 0, 0, 100, 0

  //Information on how to access the required color from FMS can be found here:
  //https://frc-docs.readthedocs.io/en/latest/docs/software/wpilib-overview/2020-Game-Data.html

public:
  ColorWheel();
  //void InitDefaultCommand() override;
  //void Periodic() override;
  void printClosestColor();
};

