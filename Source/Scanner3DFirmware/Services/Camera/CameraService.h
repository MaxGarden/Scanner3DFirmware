#pragma once

#include "RemoteServices/Services/RequestResponseServiceBase.h"

namespace Scanner3DFirmware::Services
{
    class CameraService final : public RemoteServices::RequestResponseServiceBase
    {
    public:
        CameraService() = default;
        virtual ~CameraService() override final = default;

    protected:
        virtual void OnRegisterRequestsHandlers() override final;

    private:
        Response CreateConfigResponse();
    };
}