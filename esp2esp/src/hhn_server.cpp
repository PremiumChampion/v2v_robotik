#include <hhn_server.h>
#include <hhn_socket.h>

namespace HHN
{

    Server::Server(/* args */)
    {
        this->server = WiFiServer(80);
    }

    Server Server::hhn_server = Server();

    Server *Server::getServer()
    {
        return &Server::hhn_server;
    }

    void Server::run()
    {
        HHN::Socket::cleanSockets();
        WiFiClient socket = server.available();
        
        if (socket)
        {
            HHN::Socket::addSocket(socket);
        }
    }
} // namespace HHN
