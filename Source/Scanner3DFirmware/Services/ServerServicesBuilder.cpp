#include "pch.h"
#include "ServerServicesBuilder.h"

using namespace Scanner3DFirmware;

void ServerServicesBuilder::OnClientConnected(const RemoteServices::IServicesControllerSharedPtr& servicesController)
{
    RegisterServicesFactories(servicesController);
}

void ServerServicesBuilder::RegisterServicesFactories(const RemoteServices::IServicesControllerSharedPtr& servicesController)
{
    //TODO
}