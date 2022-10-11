#include "communication/client/socket.h"
#include "broker/broker.h"

#pragma once
namespace COM
{
    class TransferHandler
    {
    private:
        HHN_Client::Socket* client;
        Broker::Broker<String>* broker;

    public:
        TransferHandler(HHN_Client::Socket* socket, Broker::Broker<String>* rcv_broker);
        void run();
        void init();
    };

    extern TransferHandler WIFI_TRANSFER_HANDLER;

} // namespace COM
