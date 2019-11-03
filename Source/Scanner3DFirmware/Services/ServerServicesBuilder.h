#pragma once

#include "RemoteServices/Controllers/ServerControllerListenerBase.h"

namespace Scanner3DFirmware
{
    class ServerServicesBuilder final : public RemoteServices::ServerControllerListenerBase
    {
    public:
        ServerServicesBuilder() = default;
        ~ServerServicesBuilder() override final = default;

        void OnClientConnected(const RemoteServices::IServicesControllerSharedPtr& servicesController) override final;

    private:
        void RegisterServicesFactories(const RemoteServices::IServicesControllerSharedPtr& servicesController);
    };
}