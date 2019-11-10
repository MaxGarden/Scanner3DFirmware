#include "pch.h"
#include "Networking/Server/WebSocketServer.h"
#include "RemoteServices/DataModels/Services.h"
#include "RemoteServices/DataModels/Server.h"
#include "RemoteServices/Controllers/ServerController.h"
#include "Services/ServerServicesBuilder.h"
#include "Camera/Camera.h"
#include <iostream>

using namespace Scanner3DFirmware;

int main()
{
    const auto fail = [](const auto returnCode, const auto& message)
    {
        std::cerr << message;
        return returnCode;
    };

    if (!Networking::Initialize())
        return fail(-1, "Cannot initialize networking.");

    auto websocketServer = Networking::IWebSocketServer::CreateWebby(50485, 1);
    if (!websocketServer)
        return fail(-2, "Cannot create web socket server.");

    const auto server = RemoteServices::IServerSharedPtr{ RemoteServices::IServer::Create(std::move(websocketServer)) };
    if (!server)
        return fail(-3, "Cannot create server data model.");

    const auto serverController = RemoteServices::IServerController::Create();
    if (!serverController)
        return fail(-4, "Cannot create server controller.");

    if (!serverController->SetDataModel(server))
        return fail(-5, "Server controller has not accepters server data model.");

    auto servicesBuilder = std::make_unique<ServerServicesBuilder>();
    if (!serverController->RegisterListener(std::move(servicesBuilder)))
        return fail(-6, "Cannot register services builder.");

    if(!Camera::Initialize())
        return fail(-7, "Cannot initialize camera.");
    
    if (!server->Initialize())
        return fail(-8, "Cannot initialize server data model.");

    std::cout << "Server started successfully." << std::endl;

    while (true)
        server->Update();

    Camera::Finalize();
    server->Finalize();
    Networking::Finalize();

    return 0;
}
