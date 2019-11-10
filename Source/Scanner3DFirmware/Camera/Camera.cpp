#include "pch.h"
#include "Camera.h"

#if !defined(WIN32)
#include <raspicam/raspicam.h>
#endif

using namespace Scanner3DFirmware;

#if !defined(WIN32)
static const raspicam::RASPICAM_FORMAT s_cameraImageFormat = raspicam::RASPICAM_FORMAT_GRAY;
static raspicam::RaspiCam s_camera;

bool Camera::Initialize()
{
    if(s_camera.isOpened())
        return false;
    
    s_camera.setFormat(s_cameraImageFormat);
    return s_camera.open();
}

void Camera::Finalize()
{
    const auto isCameraOpened = s_camera.isOpened();
    FIRMWARE_ASSERT(isCameraOpened);
    if(!isCameraOpened)
        return;
        
    s_camera.release();
}

std::vector<Scanner3DFirmware::byte> Camera::Capture()
{
    std::vector<byte> result;
    
    if(!s_camera.grab())
        return result;
    
    const auto dataSize = s_camera.getImageTypeSize(s_cameraImageFormat);
    result.resize(dataSize);
    
    s_camera.retrieve(&result[0]);
    return result;
}

void Camera::ApplyConfig(const Config& config)
{
    s_camera.setWidth(config.Width);
    s_camera.setHeight(config.Height);
    s_camera.setBrightness(config.Brightness);
    s_camera.setSharpness(config.Sharpness);
    s_camera.setContrast(static_cast<int>(config.Contrast));
    s_camera.setISO(config.ISO);
    s_camera.setSaturation(config.Saturation);
}

Config Camera::GetConfig() const
{
    Config result;
    
    result.Width = static_cast<unsigned short>(s_camera.getWidth());
    result.Height = static_cast<unsigned short>(s_camera.getHeight());
    result.Brightness = static_cast<unsigned char>(s_camera.getBrightness());
    result.Sharpness = static_cast<char>(s_camera.getSharpness());
    result.Contrast = static_cast<char>(s_camera.getContrast());
    result.ISO = static_cast<unsigned short>(s_camera.getISO());
    result.Saturation = static_cast<char>(s_camera.getSaturation());
    
    return result;
}
#else

bool Camera::Initialize()
{
    return true;
}

void Camera::Finalize()
{
}

std::vector<Scanner3DFirmware::byte> Camera::Capture()
{
    return {};
}

void Camera::ApplyConfig(const Config& config)
{
}

Camera::Config Camera::GetConfig()
{
    return {};
}

#endif