#pragma once

namespace Scanner3DFirmware::Tray
{
    struct Config
    {
        float MotorStepAngleInDegrees; //readonly
        unsigned short MotorStepsPerTrayStep = 1; //from 1 to 200
        unsigned short MotorStepDelayInMiliseconds = 100;
    };

    bool Initialize();
    void Finalize();

    bool StepForward();
    bool StepBackward();

    void ApplyConfig(Config&& config);
    Config GetConfig();
}
