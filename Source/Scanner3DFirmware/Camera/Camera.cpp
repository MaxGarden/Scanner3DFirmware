#include "pch.h"
#include "Camera.h"

using namespace Scanner3DFirmware::Camera;

void Camera::ApplyConfig(CameraConfig&& config)
{
    m_cameraConfig = std::move(config);
}

CameraConfig Camera::GetConfig() const
{
    return m_cameraConfig;
}

Camera& Camera::GetInstance() noexcept
{
    static Camera instance;
    return instance;
}