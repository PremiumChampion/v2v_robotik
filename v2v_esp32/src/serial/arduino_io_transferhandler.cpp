#include "broker/broker.h"
#include "arduino_io_transferhandler.h"
#include "arduino2esp.h"
#include "sensors/sensors.h"
#include "actors/actors.h"

namespace SerialCommunication
{
    template <class rcv, class snd>
    Arduino_IO_TransferHandler<rcv, snd>::Arduino_IO_TransferHandler(
        Broker::Broker<rcv> *rcvBroker,
        Broker::Broker<snd> *sndBroker)
    {
        this->rcvBroker = rcvBroker;
        this->sndBroker = sndBroker;
    }
    template <class rcv, class snd>
    void Arduino_IO_TransferHandler<rcv, snd>::run()
    {
        SerialCommunication::ArduinoConnection.run();
        if (this->sndBroker->get_has_changes())
        {
            SerialCommunication::ArduinoConnection.send(this->sndBroker->get_transmission_data());
        }
        if (SerialCommunication::ArduinoConnection.hasData())
        {
            this->rcvBroker->rcv_transmission_data(SerialCommunication::ArduinoConnection.receive());
        }
    }
    template <class rcv, class snd>
    void Arduino_IO_TransferHandler<rcv, snd>::init()
    {
        SerialCommunication::ArduinoConnection.init();
    }

    Arduino_IO_TransferHandler<int, int> SENSOR_ACTOR_TRANSFER_HANDLER(&Sensors::MESSAGE_BROKER, &Actors::MESSAGE_BROKER);
} // namespace SerialCommunication
