#include "pch.h"
#include "Networking/Server/WebSocketServer.h"

int main()
{
    const auto server = Networking::IWebSocketServer::CreateWebby(50485, 1);

    server->SetOnClientConnectedCallback([](const auto& connection)
    {
        return true;
    });

    server->Initialize();

    while (true)
        server->Update();

    server->Finalize();
    return 0;
}