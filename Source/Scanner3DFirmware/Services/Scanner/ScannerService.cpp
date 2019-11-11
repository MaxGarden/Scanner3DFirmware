#include "pch.h"
#include "ScannerService.h"
#include "Scanner/Scanner.h"
#include "Camera/Camera.h"

using namespace Scanner3DFirmware::Services;

bool ScannerService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    result &= RegisterRequestHandler('b', [](auto&& payload)
    {
        auto responsePayload = Camera::Capture();
        Scanner::PerformBinarization(responsePayload);
        const auto responseType = responsePayload.empty() ? Response::ResponseType::Fail : Response::ResponseType::Ok;

        return Response{ responseType, std::move(responsePayload) };
    });

    FIRMWARE_ASSERT(result);
    return result;
}