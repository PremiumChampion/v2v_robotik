#include "transfer.h"
#include "communication/communication.h"
#include "communication/client/socket.h"
#include "broker/broker.h"

namespace COM
{
    // run method is called periodically
    void TransferHandler::run()
    {   
        this->client->run(); // What should the client run method do? Or what is the run method doing. 
 
    /*
        Check, if new data to be sent is available
        Read from broker buffer and send via wifi
    */
        if (this->broker->get_has_changes())
        {
            this->client->send(this->broker->get_transmission_data());
        }
    /*
        Check, if new data is available in buffer to be read.
        Read data and send to broker. 
    */

        if (SerialCommunication::ArduinoConnection.hasData())
        {
            // this->rcvBroker->rcv_transmission_data(SerialCommunication::ArduinoConnection.receive());
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
