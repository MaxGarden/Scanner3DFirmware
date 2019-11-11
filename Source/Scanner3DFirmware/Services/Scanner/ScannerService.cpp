#include "pch.h"
#include "ScannerService.h"
#include "Scanner/Scanner.h"
#include "Camera/Camera.h"

using namespace Scanner3DFirmware::Services;

bool ScannerService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    static const auto binarizedData = []()
    {
        auto result = Camera::Capture();
        Scanner::PerformBinarization(result);

        return result;
    };

    result &= RegisterRequestHandler('b', [](auto&& payload)
    {
        auto responsePayload = binarizedData();
        const auto responseType = responsePayload.empty() ? Response::ResponseType::Fail : Response::ResponseType::Ok;

        return Response{ responseType, std::move(responsePayload) };
    });

    result &= RegisterRequestHandler('a', [](auto&& payload)
    {
        const auto cameraConfig = Camera::GetConfig();
        const auto averagePoints = Scanner::CalculateAveragePoints(binarizedData(), cameraConfig.Width);

        RemoteServices::ServicePayload responsePayload;

        const auto beginIterator = reinterpret_cast<const byte*>(averagePoints.data());
        const auto endIterator = beginIterator + averagePoints.size() * sizeof(decltype(averagePoints)::value_type);

        return Response{ Response::ResponseType::Ok, RemoteServices::ServicePayload{ beginIterator, endIterator } };
    });

    FIRMWARE_ASSERT(result);
    return result;
}