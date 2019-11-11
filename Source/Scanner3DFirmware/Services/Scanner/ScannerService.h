#pragma once

#include "RemoteServices/Services/RequestResponseServiceBase.h"

namespace Scanner3DFirmware::Services
{
    class ScannerService final : public RemoteServices::RequestResponseServiceBase
    {
    public:
        ScannerService() = default;
        virtual ~ScannerService() override final = default;

        virtual bool Initialize() override final;
    };
}