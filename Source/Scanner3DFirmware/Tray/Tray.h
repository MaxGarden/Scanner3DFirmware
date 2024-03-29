#pragma once

namespace Scanner3DFirmware::Tray
{
    struct Config
    {
        float MotorStepAngleInDegrees; //readonly
        unsigned short MotorStepsPerTrayStep = 1; //from 1 to 6400
        unsigned short MotorStepDelayInMiliseconds = 100;
    };

    bool Initialize();
    void Finalize();

    void Update();

    bool StepForward();
    bool StepBackward();

    void ApplyConfig(Config&& config);
    Config GetConfig();
}
