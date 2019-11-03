#include "pch.h"
#include "Networking/Server/WebSocketServer.h"
#include "RemoteServices/DataModels/Services.h"
#include "RemoteServices/DataModels/Server.h"
#include <iostream>

int main()
{
    Networking::Initialize();

    auto webbyServer = Networking::IWebSocketServer::CreateWebby(50485, 1);
    const auto server = RemoteServices::IServer::Create(std::move(webbyServer));

    server->Initialize();

    while (true)
        server->Update();

    server->Finalize();
    Networking::Finalize();

    return 0;
}