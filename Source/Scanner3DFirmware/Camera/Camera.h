#pragma once
#include <raspicam/raspicam.h>

namespace Scanner3DFirmware::Camera
{
    struct CameraConfig
    {
        unsigned short Width;           //multiple of 320
        unsigned short Height;          //multiple of 240
        byte Brightness;                //0 to 100
        byte Sharpness;                 //0 to 100
        byte Contrast;                  //0 to 100
        unsigned short ISO;             //100 to 800
        byte Saturation;                //0 to 100
    };

    class Camera final
    {
    public:
        ~Camera() = default;

        bool Initialize();
        void Finalize();

        std::vector<byte> RetriveGrayScaleImage();

        void ApplyConfig(const CameraConfig& config);
        CameraConfig GetConfig() const;

        static Camera& GetInstance() noexcept;

    private:
        Camera() = default;

    private:
        raspicam::RaspiCam m_camera;
    };
}
