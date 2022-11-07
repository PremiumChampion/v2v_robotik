#include "communication/client/socket.h"
#include "broker/broker.h"

#pragma once
namespace COM
{
    class TransferHandler
    {
    private:
        HHN_Client::Socket* client;
        Broker::Broker<int>* broker;

    public:
        TransferHandler(HHN_Client::Socket* socket, Broker::Broker<int>* rcv_broker);
        void run();
        void init();
    };

    extern TransferHandler WIFI_TRANSFER_HANDLER;

} // namespace COM
