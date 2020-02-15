#include "Subsystems/LimeLight.h"
#include "networktables/NetworkTableInstance.h"

static std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

enum
{
    Led_Maitain = 0,
    Led_Off,
    Led_Blink,
    Led_On
};

LimeLight::LimeLight()
{
    validTarget = table->GetNumber("tv",0);
    horizontalOffset = table->GetNumber("tx",0);
    verticalOffset = table->GetNumber("ty",0);
    targetArea = table->GetNumber("ta",0);
    targetSkew = table->GetNumber("ts",0);
}

void LimeLight::updateLimeLight()
{
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	nt::NetworkTableEntry tx = table.get()->GetEntry("tx");
    horizontalOffset = tx.GetDouble(0);
    
    validTarget = table.get()->GetNumber("tv",0.0);
    // horizontalOffset = table->GetNumber("tx",0.0);
    verticalOffset = table.get()->GetNumber("ty",0.0);
    targetArea = table.get()->GetNumber("ta",0.0);
    targetSkew = table.get()->GetNumber("ts",0.0);
}

bool LimeLight::getValidTarget()
{
    // Returns true or false depending on if the camera sees any targets
    return validTarget;
}

double LimeLight::getHorizontalOffset()
{
    // Returns the horizontal offset of the target
    return horizontalOffset;
}

double LimeLight::getVerticalOffset()
{
    // Returns the vertical offset of the target
    return verticalOffset;
}

double LimeLight::getTargetArea()
{
    // Returns the area of the target from 0 to 100 percent
    return targetArea;
}

double LimeLight::getTargetSkew()
{
    // Returns the rotation of the target from -90 to 0 degrees
    return targetSkew;
}

void LimeLight::setLED(bool on)
{
    if (on) 
    {
        table->PutNumber("ledMode", Led_On);
    }
    else
    {
        table->PutNumber("ledMode", Led_Off);
    }
    
}

void LimeLight::setPipeline(int num){
    table->PutNumber("pipeline", num); //check that "pipeline" is the right word
}

int LimeLight::getPipeline()
{
    return table->GetNumber("getpipe", 0);
}

void LimeLight::activateVisionProcessing(bool vision)
{
    table->PutNumber("camMode", !vision); ///Vision Mode is 0, Driver Camera is 1
}

double LimeLight::getDistance(int cameraAngle, double cameraHeight, double targetHeight)
{
    double yOffset = getVerticalOffset();
	return (targetHeight - cameraHeight) / atan(cameraAngle + yOffset);
}