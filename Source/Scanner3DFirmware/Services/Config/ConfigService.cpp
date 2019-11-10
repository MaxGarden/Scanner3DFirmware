#include "pch.h"
#include "ConfigService.h"
#include "Config/Config.h"

using namespace Scanner3DFirmware::Services;

bool ConfigService::Initialize()
{
    auto result = RequestResponseServiceBase::Initialize();

    result &= RegisterRequestHandler('g', [this](auto&& payload)
    {
        return CreateConfigResponse();
    });

    result &= RegisterRequestHandler('a', [this](auto&& payload)
    {
        if (payload.size() == sizeof(Config::Config))
        {
            const auto config = reinterpret_cast<const Config::Config*>(payload.data());
            Config::ApplyConfig(Config::Config{ *config });
        }

        return CreateConfigResponse();
    });

    FIRMWARE_ASSERT(result);
    return result;
}

ConfigService::Response ConfigService::CreateConfigResponse()
{
    const auto config = Config::GetConfig();
    const auto beginIterator = reinterpret_cast<const RemoteServices::byte*>(&config);
    const auto endIterator = beginIterator + sizeof(Camera::Config);

    return Response{ Response::ResponseType::Ok, RemoteServices::ServicePayload{ beginIterator, endIterator } };
}