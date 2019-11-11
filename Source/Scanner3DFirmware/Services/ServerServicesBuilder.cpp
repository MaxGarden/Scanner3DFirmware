#include "pch.h"
#include "ServerServicesBuilder.h"
#include "RemoteServices/Services/ServiceFactory.h"

#include "Config/ConfigService.h"
#include "Camera/CameraService.h"
#include "Scanner/ScannerService.h"

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

    servicesController->RegisterServiceFactory(RemoteServices::ServiceFactory<ConfigService>::CreateFactory("config"));
    servicesController->RegisterServiceFactory(RemoteServices::ServiceFactory<CameraService>::CreateFactory("camera"));
    servicesController->RegisterServiceFactory(RemoteServices::ServiceFactory<ScannerService>::CreateFactory("scanner"));
}