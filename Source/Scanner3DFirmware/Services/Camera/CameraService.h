#pragma once

#include "RemoteServices/Services/RequestResponseServiceBase.h"

namespace Scanner3DFirmware::Services
{
    class CameraService final : public RemoteServices::RequestResponseServiceBase
    {
    public:
        CameraService() = default;
        virtual ~CameraService() override final = default;

        virtual bool Initialize() override final;
    };
}