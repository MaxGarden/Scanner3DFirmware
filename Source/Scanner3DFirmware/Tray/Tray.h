#pragma once

namespace Scanner3DFirmware::Tray
{
    struct Config
    {
        unsigned short DegreesPerStep; //from 9/160 to 360 (step 9/160)
    };

    bool Initialize();
    void Finalize();

    void StepForward();
    void StepBackward();

    void ApplyConfig(const Config& config);
    Config GetConfig();
}
