#include "Subsystems/ColorWheel.h"
#include "Reference.h"

using namespace rev;

ColorWheel::ColorWheel() : frc::Subsystem("ColorWheel") {
    colorMotor = new CANSparkMax(COLOR_WHEEL, CANSparkMaxLowLevel::MotorType::kBrushless);

    // Needs to register all of the colors
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
}

// void ColorWheel::InitDefaultCommand() {
//     // Set the default command for a subsystem here.
//     // SetDefaultCommand(new MySpecialCommand());

// }

// void ColorWheel::Periodic() {
//     // Put code here to be run every loop

// }

void ColorWheel::printClosestColor()
{
    std::cout << "Color: ";

    frc::Color SensedColor = m_colorSensor.GetColor();
    //comment this out or in to see values.
    //std::cout << "red: " << SensedColor.red << ", Blue: " << SensedColor.blue << ", Green: " << SensedColor.green << std::endl;

    if (SensedColor.red > SensedColor.green && SensedColor.blue < SensedColor.red  && SensedColor.green > SensedColor.blue) {
        std::cout << "Red ";
    }
    if (SensedColor.blue > SensedColor.green) {
        std::cout << "Blue ";
    }
        
    if (SensedColor.green > SensedColor.blue && SensedColor.blue > SensedColor.red) {
        std::cout << "Green ";
    }
    if (SensedColor.green > SensedColor.blue && SensedColor.blue < SensedColor.red && SensedColor.red < SensedColor.green ) {
        std::cout << "Yellow ";
    }

    // bool foundColor = false;
    // double confidenceFactor = 0.95;
    // if(kBlueTarget == m_colorMatcher.MatchColor(kBlueTarget, confidenceFactor))
    // {
    //     std::cout << "Found Blue";
    //     foundColor = true;
    // }
    // if(kGreenTarget == m_colorMatcher.MatchColor(kGreenTarget, confidenceFactor))
    // {
    //     std::cout << "Found Green";
    //     foundColor = true;
    // }
    // if(kYellowTarget == m_colorMatcher.MatchColor(kYellowTarget, confidenceFactor))
    // {
    //     std::cout << "Found Yellow";
    //     foundColor = true;
    // }
    // if(kRedTarget == m_colorMatcher.MatchColor(kRedTarget, confidenceFactor))
    // {
    //     std::cout << "Found Red";
    //     foundColor = true;
    // }

    // if(!foundColor)
    // {
    //     std::cout << "Did Not Match Color";
    // }

    // std::cout << std::endl;
}
