#ifndef LIMELIGHT
#define LIMELIGHT

#include "frc/smartdashboard/Smartdashboard.h"

class LimeLight
{
public:
    LimeLight();

    void updateLimeLight();
    bool getValidTarget();
    double getHorizontalOffset();
    double getVerticalOffset();
    double getTargetArea();
    double getTargetSkew();
    void setLED(bool on);
    void setPipeline(int num);
    int getPipeline();
    void activateVisionProcessing(bool vision);
    double getDistance(int cameraAngle, double cameraHeight, double targetHeight);

    bool validTarget;
    double horizontalOffset;
    double verticalOffset;
    double targetArea;
    double targetSkew;
};

#endif