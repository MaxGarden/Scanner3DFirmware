#include "pch.h"
#include "TrayService.h"
#include "Tray/Tray.h"

using namespace Scanner3DFirmware::Services;

bool TrayService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    result &= RegisterRequestHandler('f', [](auto&& payload)
    {
        const auto responseType = Tray::StepForward() ? Response::ResponseType::Ok : Response::ResponseType::Fail;
        return Response{ responseType, {} };
    });

    result &= RegisterRequestHandler('b', [](auto&& payload)
    {
        const auto responseType = Tray::StepBackward() ? Response::ResponseType::Ok : Response::ResponseType::Fail;
        return Response{ responseType, {} };
    });

    FIRMWARE_ASSERT(result);
    return result;
}