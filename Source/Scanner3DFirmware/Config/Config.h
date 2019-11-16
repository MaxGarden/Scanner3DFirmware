#pragma once

#include "Camera/Camera.h"
#include "Scanner/Scanner.h"
#include "Tray/Tray.h"

namespace Scanner3DFirmware::Config
{
    struct Config
    {
        Camera::Config CameraConfig;
        Scanner::Config ScannerConfig;
        Tray::Config TrayConfig;
    };

    bool Initialize();
    void Finalize();

    void ApplyConfig(Config&& config);
    Config GetConfig();
}