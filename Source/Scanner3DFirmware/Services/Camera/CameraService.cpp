#include "pch.h"
#include "CameraService.h"
#include "Camera/Camera.h"

#include <iostream>

using namespace Scanner3DFirmware::Services;

bool CameraService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    result &= RegisterRequestHandler('g', [this](auto&& payload)
    {
        return CreateConfigResponse();
    });

    result &= RegisterRequestHandler('a', [this](auto&& payload)
    {
        if (payload.size() == sizeof(Camera::CameraConfig))
        {
            const auto config = reinterpret_cast<const Camera::CameraConfig*>(payload.data());
            Camera::Camera::GetInstance().ApplyConfig(Camera::CameraConfig{ *config });
        }

        return CreateConfigResponse();
    });

    result &= RegisterRequestHandler('c', [this](auto&& payload)
    {
        //TODO
        return Response{ Response::ResponseType::Fail, {} };
    });

    FIRMWARE_ASSERT(result);
    return result;
}

CameraService::Response CameraService::CreateConfigResponse()
{
    const auto config = Camera::Camera::GetInstance().GetConfig();
    const auto beginIterator = reinterpret_cast<const RemoteServices::byte*>(&config);
    const auto endIterator = beginIterator + sizeof(Camera::CameraConfig);

    return Response{ Response::ResponseType::Ok, RemoteServices::ServicePayload{ beginIterator, endIterator } };
}