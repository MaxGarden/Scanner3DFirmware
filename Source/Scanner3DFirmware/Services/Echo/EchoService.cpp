#include "pch.h"
#include "EchoService.h"
#include <iostream>

using namespace Scanner3DFirmware::Services;

void EchoService::SendMessage(const std::string& message)
{
    m_sentMessages.emplace_back(message);
    Send(RemoteServices::ServicePayload{ message.cbegin(), message.cend() });
}

void EchoService::OnReceived(const RemoteServices::ServicePayload& payload)
{
    std::string message{ payload.cbegin(), payload.cend() };

    const auto iterator = std::find(m_sentMessages.cbegin(), m_sentMessages.cend(), message);
    if (iterator == m_sentMessages.cend())
        Send(RemoteServices::ServicePayload{ payload });
    else
    {
        std::cout << "Received echo: " << message << std::endl;
        m_sentMessages.erase(iterator);
    }
}