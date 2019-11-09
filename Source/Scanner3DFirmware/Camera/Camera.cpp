#include "pch.h"
#include "Camera.h"

using namespace Scanner3DFirmware::Camera;

void Camera::ApplyConfig(const CameraConfig& config)
{
    //TODO
}

CameraConfig Camera::GetConfig() const
{
    //TODO
    return CameraConfig{};
}

Camera& Camera::GetInstance() noexcept
{
    static Camera instance;
    return instance;
}