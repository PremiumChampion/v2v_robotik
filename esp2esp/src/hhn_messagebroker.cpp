#include <hhn_messagebroker.h>
#include <hhn_socket.h>
#include <Arduino.h>

namespace HHN
{
    void MessageBroker::message(Socket *socket)
    {
        Serial.print(socket->getPayload());
        socket->sendln(socket->getPayload());
    }
} // namespace HHN
