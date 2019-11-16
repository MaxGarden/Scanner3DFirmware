#pragma once

namespace Scanner3DFirmware::Camera
{
    struct Config
    {
        unsigned short Width;           //multiple of 320
        unsigned short Height;          //multiple of 240
        byte Brightness;                //0 to 100
        byte Sharpness;                 //0 to 100
        byte Contrast;                  //0 to 100
        unsigned short ISO;             //100 to 800
        byte Saturation;                //0 to 100
        unsigned short Rotation = 270;  //0 to 359
    };

    bool Initialize();
    void Finalize();

    std::vector<byte> Capture();

    void ApplyConfig(const Config& config);
    Config GetConfig();
}
