#include "transfer.h"
#include "communication/communication.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

namespace COM
{
    void TransferHandler::run()
    {   
        this->client->run();
        
        if (this->broker->get_has_changes())
        {
            this->client->send(this->broker->get_transmission_data());
        }
        if (SerialCommunication::ArduinoConnection.hasData())
        {
            // this->rcvBroker->rcv_transmission_data(SerialCommunication::ArduinoConnection.recieve());
        }
    }

    void TransferHandler::init()
    {
        // SerialCommunication::ArduinoConnection.init();
    }

    TransferHandler::TransferHandler(HHN_Client::Socket *socket, Broker::Broker<String>* broker)
    {
        this->client = socket;
        this->broker = broker;
    }

    TransferHandler WIFI_TRANSFER_HANDLER = TransferHandler(&externalClient);
} // namespace COM

// socket|var1|var2|m1|m2|m3
// client|0|1|2|3|4|5....

// socket[0]
// socket[2]
