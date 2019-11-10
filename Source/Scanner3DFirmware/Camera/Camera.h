#pragma once

namespace Scanner3DFirmware::Camera
{
    struct CameraConfig
    {
        unsigned short Width;           //multiple of 320
        unsigned short Height;          //multiple of 240
        unsigned char Brightness;       //0 to 100
        char Sharpness;                 //-100 to 100
        char Contrast;                  //-100 to 100
        unsigned short Iso;             //100 to 800
        char Saturation;                //-100 to 100
    };

    class Camera final
    {
    public:
        ~Camera() = default;

        void ApplyConfig(CameraConfig&& config);
        CameraConfig GetConfig() const;

        static Camera& GetInstance() noexcept;

    private:
        Camera() = default;

    private:
        CameraConfig m_cameraConfig;
    };
}