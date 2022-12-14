#include "transfer.h"
#include "communication/communication.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

namespace COM
{ // Uncomment and replace external client with correct pointer and insert the right pointer to the broker
    TransferHandler WIFI_TRANSFER_HANDLER = TransferHandler(&COM::externalClient, &COM::broker);

    void TransferHandler::run()
    {
        this->client->run();

        if (this->broker->get_has_changes())
        {
            String transmissionData = this->broker->get_transmission_data();
            // Serial.println("WIFI-SEND:" + transmissionData);
            this->client->send(transmissionData);
        }

        if (this->client->hasClientData())
        {
            String rcvData = this->client->receive();
            // Serial.println("WIFI-RCV:" + rcvData);
            this->broker->rcv_transmission_data(rcvData);
        }
    }

    void TransferHandler::init()
    {
        COM::setup();
        this->run();
    }

    TransferHandler::TransferHandler(HHN_Client::Socket *socket, Broker::Broker<int> *broker)
    {
        this->client = socket;
        this->broker = broker;
        // this->last_sync_time = 0;
    }

} // namespace COM

// socket|var1|var2|m1|m2|m3
// client|0|1|2|3|4|5....

// socket[0]
// socket[2]
