#include "pch.h"
#include "Networking/Server/WebSocketServer.h"
#include <iostream>

int main()
{
    Networking::Initialize();

    const auto server = Networking::IWebSocketServer::CreateWebby(50485, 1);

    server->SetOnClientConnectedCallback([](const auto& connection)
    {
        std::cout << "Someone is connected";
    });

    server->Initialize();

    while (true)
        server->Update();

    server->Finalize();
    Networking::Finalize();

    return 0;
}