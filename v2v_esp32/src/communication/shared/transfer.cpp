#include "transfer.h"
#include "communication/communication.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

namespace COM
{ // Uncomment and replace external client with correct pointer and insert the right pointer to the broker
    TransferHandler WIFI_TRANSFER_HANDLER = TransferHandler(&COM::externalClient, &COM::RCV_BROKER, &COM::SND_BROKER);

    void TransferHandler::run()
    {
        this->client->run();

        if (this->snd_broker->get_has_changes())
        {
            this->client->send(this->snd_broker->get_transmission_data());
        }

        if (this->client->hasClientData())
        {
            this->rcv_broker->rcv_transmission_data(this->client->receive());
        }
    }

    
    void TransferHandler::init()
    {
        COM::setup();
    }

    TransferHandler::TransferHandler(HHN_Client::Socket *socket, Broker::Broker<String> *rcv_broker, Broker::Broker<String> *snd_broker)
    {
        this->client = socket;
        this->rcv_broker = rcv_broker;
        this->snd_broker = snd_broker;
    }

} // namespace COM

// socket|var1|var2|m1|m2|m3
// client|0|1|2|3|4|5....

// socket[0]
// socket[2]
