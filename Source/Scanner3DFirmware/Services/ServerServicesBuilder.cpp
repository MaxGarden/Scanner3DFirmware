#include "pch.h"
#include "ServerServicesBuilder.h"
#include "RemoteServices/Services/ServiceFactory.h"

#include "Echo/EchoService.h"

using namespace Scanner3DFirmware;
using namespace Scanner3DFirmware::Services;

void ServerServicesBuilder::OnClientConnected(const RemoteServices::IServicesControllerSharedPtr& servicesController)
{
    RegisterServicesFactories(servicesController);
}

void ServerServicesBuilder::RegisterServicesFactories(const RemoteServices::IServicesControllerSharedPtr& servicesController)
{
    if (!servicesController)
        return;

    servicesController->RegisterServiceFactory(RemoteServices::ServiceFactory<EchoService>::CreateFactory("echo"));
}