#include "pch.h"
#include "ScannerService.h"
#include "Scanner/Scanner.h"
#include "Camera/Camera.h"

using namespace Scanner3DFirmware::Services;

bool ScannerService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    static const auto calculateBinarizedData = []()
    {
        auto result = Camera::Capture();
        Scanner::PerformBinarization(result);

        return result;
    };

    static const auto calculateAveragePoints = []()
    {
        const auto cameraConfig = Camera::GetConfig();
        return Scanner::CalculateAveragePoints(calculateBinarizedData(), cameraConfig.Width);
    };

    static const auto calculate3DPoints = [](auto trayAngle)
    {
        const auto averagePoints = calculateAveragePoints();
        return Scanner::Calculate3DPoints(averagePoints, trayAngle);
    };

    static const auto vectorResponse = [](const auto& data)
    {
        const auto beginIterator = reinterpret_cast<const byte*>(data.data());
        const auto endIterator = beginIterator + data.size() * sizeof(typename std::remove_reference<decltype(data)>::type::value_type);

        return Response{ Response::ResponseType::Ok, RemoteServices::ServicePayload{ beginIterator, endIterator } };
    };

    result &= RegisterRequestHandler('b', [](auto&& payload)
    {
        auto responsePayload = calculateBinarizedData();
        const auto responseType = responsePayload.empty() ? Response::ResponseType::Fail : Response::ResponseType::Ok;

        return Response{ responseType, std::move(responsePayload) };
    });

    result &= RegisterRequestHandler('a', [](auto&& payload)
    {
        return vectorResponse(calculateAveragePoints());
    });

    result &= RegisterRequestHandler('r', [](auto&& payload)
    {
        const auto trayAngle = *reinterpret_cast<float*>(payload.data());
        return vectorResponse(calculate3DPoints(trayAngle));
    });

    FIRMWARE_ASSERT(result);
    return result;
}