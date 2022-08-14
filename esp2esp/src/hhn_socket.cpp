#include <WiFi.h>
#include <hhn_socket.h>
#include <hhn_messagebroker.h>

namespace HHN
{
#pragma region static

    int Socket::ACTIVE_SOCKET_COUNT = 0;
    int Socket::NEXT_SOCKET_CLEAN_MS = 0;
    Socket Socket::sockets[MAX_SOCKETS];

    void Socket::addSocket(WiFiClient client)
    {
        boolean add_client = true;
        for (int i = 0; i < ACTIVE_SOCKET_COUNT; i++)
        {
            String remoteIP = Socket::sockets[i].remoteIP();
            if (remoteIP.equals(client.remoteIP().toString()))
            {
                add_client = false;
            }
        }
        // do not add the client and close the connection
        //  if the max num of clients is exceded and a new client wants to connect
        if (MAX_SOCKETS > Socket::ACTIVE_SOCKET_COUNT && add_client)
        {
            client.stop();
            add_client = false;
        }

        if (add_client)
        {
            Socket socket = Socket(client);

            Socket::sockets[ACTIVE_SOCKET_COUNT] = socket;
            ACTIVE_SOCKET_COUNT++;
        }
    }

    void Socket::cleanSockets()
    {
        if (NEXT_SOCKET_CLEAN_MS < millis())
        {
            NEXT_SOCKET_CLEAN_MS = millis() + 100;
            for (int i = 0; i < ACTIVE_SOCKET_COUNT; i++)
            {
                if (!Socket::sockets[i].isConnected())
                {
                    for (int j = i + 1; j < ACTIVE_SOCKET_COUNT; j++)
                    {
                        Socket::sockets[j - 1] = Socket::sockets[j];
                    }
                    ACTIVE_SOCKET_COUNT--;
                }
            }
        }
    }

    void Socket::run_sockets()
    {
        for (int i = 0; i < ACTIVE_SOCKET_COUNT; i++)
        {
            Socket::sockets[i].run();
        }
    }

#pragma endregion

    Socket::Socket()
    {
        this->payload = String("");
        this->client = WiFiClient();
    }
    Socket::Socket(WiFiClient client)
    {
        this->payload = String("");
        this->client = client;
    }

    boolean Socket::isConnected()
    {
        return this->client.connected();
    }

    void Socket::run()
    {
        while (this->client.available())
        {
            char c = client.read();

            if (c != '\n')
            {
                this->payload += c;
            }

            if (c == '\n')
            {
                // handle the message
                MessageBroker::message(this);
                // reset payloads
                this->payload = String("");
            }
        }
    }

    void Socket::send(String data)
    {
        this->client.print(data);
    }

    void Socket::sendln(String data)
    {
        this->client.println(data);
    }

    String Socket::getPayload()
    {
        return this->payload;
    }
    String Socket::remoteIP()
    {
        return this->client.remoteIP().toString();
    }
    void Socket::close()
    {
        this->client.stop();
    }

} // namespace HHNServer
