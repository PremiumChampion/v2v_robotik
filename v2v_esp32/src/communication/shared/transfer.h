#include "communication/client/socket.h"
#include "broker/broker.h"

#pragma once
namespace COM
{
    class TransferHandler
    {
    private:
        HHN_Client::Socket* client;
        Broker::Broker<String>* rcv_broker;
        Broker::Broker<String>* snd_broker;

    public:
        TransferHandler(HHN_Client::Socket* socket, Broker::Broker<String>* rcv_broker, Broker::Broker<String>* snd_broker);
        void run();
        void init();
    };

    extern TransferHandler WIFI_TRANSFER_HANDLER;

} // namespace COM
