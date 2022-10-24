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
        // resync after 500ms
        if (this->last_full_sync_time + 500 < millis())
        {
            this->last_full_sync_time = millis();
            this->sndBroker->reset_pushed_message_indicator();
        }
        
        SerialCommunication::ArduinoConnection.run();
        if (this->sndBroker->get_has_changes())
        {
            String data = this->sndBroker->get_transmission_data();
            SerialCommunication::ArduinoConnection.send(data);
        }
        if (SerialCommunication::ArduinoConnection.hasData())
        {
            String data = SerialCommunication::ArduinoConnection.receive();
            this->rcvBroker->rcv_transmission_data(data);
        }
    }
    template <class rcv, class snd>
    void Arduino_IO_TransferHandler<rcv, snd>::init()
    {
        SerialCommunication::ArduinoConnection.init();
    }

    Arduino_IO_TransferHandler<int, int> SENSOR_ACTOR_TRANSFER_HANDLER(&Sensors::MESSAGE_BROKER, &Actors::MESSAGE_BROKER);
} // namespace SerialCommunication
