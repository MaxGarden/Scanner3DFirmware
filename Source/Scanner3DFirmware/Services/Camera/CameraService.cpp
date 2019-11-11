#include "pch.h"
#include "CameraService.h"
#include "Camera/Camera.h"

using namespace Scanner3DFirmware::Services;

bool CameraService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    result &= RegisterRequestHandler('c', [](auto&& payload)
    {
        auto responsePayload = Camera::Capture();
        const auto responseType = responsePayload.empty() ? Response::ResponseType::Fail : Response::ResponseType::Ok;
        return Response{ responseType, std::move(responsePayload) };
    });

    FIRMWARE_ASSERT(result);
    return result;
}