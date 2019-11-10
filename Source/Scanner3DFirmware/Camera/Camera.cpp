#include "pch.h"
#include "Camera.h"

using namespace Scanner3DFirmware::Camera;

#if defined(UNIX)
const raspicam::RASPICAM_FORMAT Camera::s_cameraImageFormat = raspicam::RASPICAM_FORMAT_GRAY;

bool Camera::Initialize()
{
    if(m_camera.isOpened())
        return false;
    
    m_camera.setFormat(s_cameraImageFormat);
    return m_camera.open();
}

void Camera::Finalize()
{
    const auto isCameraOpened = m_camera.isOpened();
    FIRMWARE_ASSERT(isCameraOpened);
    if(!isCameraOpened)
        return;
        
    m_camera.release();
}

std::vector<Scanner3DFirmware::byte> Camera::Capture()
{
    std::vector<byte> result;
    
    if(!m_camera.grab())
        return result;
    
    const auto dataSize = m_camera.getImageTypeSize(s_cameraImageFormat);
    result.resize(dataSize);
    
    m_camera.retrieve(&result[0]);
    return result;
}

void Camera::ApplyConfig(const CameraConfig& config)
{
    m_camera.setWidth(config.Width);
    m_camera.setHeight(config.Height);
    m_camera.setBrightness(config.Brightness);
    m_camera.setSharpness(config.Sharpness);
    m_camera.setContrast(static_cast<int>(config.Contrast));
    m_camera.setISO(config.ISO);
    m_camera.setSaturation(config.Saturation);
}

CameraConfig Camera::GetConfig() const
{
    CameraConfig result;
    
    result.Width = static_cast<unsigned short>(m_camera.getWidth());
    result.Height = static_cast<unsigned short>(m_camera.getHeight());
    result.Brightness = static_cast<unsigned char>(m_camera.getBrightness());
    result.Sharpness = static_cast<char>(m_camera.getSharpness());
    result.Contrast = static_cast<char>(m_camera.getContrast());
    result.ISO = static_cast<unsigned short>(m_camera.getISO());
    result.Saturation = static_cast<char>(m_camera.getSaturation());
    
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

void Camera::ApplyConfig(const CameraConfig& config)
{
}

CameraConfig Camera::GetConfig() const
{
    return {};
}

#endif

Camera& Camera::GetInstance() noexcept
{
    static Camera instance;
    return instance;
}
