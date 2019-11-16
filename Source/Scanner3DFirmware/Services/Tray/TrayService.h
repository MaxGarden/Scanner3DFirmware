#pragma once

#include "RemoteServices/Services/RequestResponseServiceBase.h"

namespace Scanner3DFirmware::Services
{
    class TrayService final : public RemoteServices::RequestResponseServiceBase
    {
    public:
        TrayService() = default;
        virtual ~TrayService() override final = default;

        virtual bool Initialize() override final;
    };
}