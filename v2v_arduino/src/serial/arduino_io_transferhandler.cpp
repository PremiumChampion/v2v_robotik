#include "broker/broker.h"
#include "arduino_io_transferhandler.h"
#include "arduino2esp.h"
#include "sensors/sensors.h"
#include "actors/actors.h"

namespace SerialCommunication
{
    template <class rcv, class snd>
    Ardunio_IO_TransferHandler<rcv, snd>::Ardunio_IO_TransferHandler(
        Broker::Broker<rcv> *rcvBroker,
        Broker::Broker<snd> *sndBroker)
    {
        this->rcvBroker = rcvBroker;
        this->sndBroker = sndBroker;
    }
    template <class rcv, class snd>
    void Ardunio_IO_TransferHandler<rcv, snd>::run()
    {
        SerialCommunication::EspConnection.run();
        if (this->sndBroker->get_has_changes())
        {
            SerialCommunication::EspConnection.send(this->sndBroker->get_transmission_data());
        }
        if (SerialCommunication::EspConnection.hasData())
        {
            this->rcvBroker->rcv_transmission_data(SerialCommunication::EspConnection.recieve());
        }
    }
    template <class rcv, class snd>
    void Ardunio_IO_TransferHandler<rcv, snd>::init()
    {
        SerialCommunication::EspConnection.init();
    }

    Ardunio_IO_TransferHandler<int, int> SENSOR_ACTOR_TRANSFER_HANDLER(&Sensors::MESSAGE_BROKER, &Actors::MESSAGE_BROKER);
} // namespace SerialCommunication
