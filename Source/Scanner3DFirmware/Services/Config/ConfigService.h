#pragma once

#include "RemoteServices/Services/RequestResponseServiceBase.h"

namespace Scanner3DFirmware::Services
{
    class ConfigService final : public RemoteServices::RequestResponseServiceBase
    {
    public:
        ConfigService() = default;
        virtual ~ConfigService() override final = default;

        virtual bool Initialize() override final;

    private:
        Response CreateConfigResponse();
    };
}