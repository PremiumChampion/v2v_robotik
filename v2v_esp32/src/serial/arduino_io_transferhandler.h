#include "broker/broker.h"

namespace SerialCommunication
{
    template <class rcv, class snd>
    class Arduino_IO_TransferHandler
    {
    private:
        Broker::Broker<rcv> *rcvBroker;
        Broker::Broker<snd> *sndBroker;
        unsigned long last_full_sync_time;

    public:
        Arduino_IO_TransferHandler(
            Broker::Broker<rcv> *rcvBroker,
            Broker::Broker<snd> *sndBroker);
        void run();
        void init();
    };

    template class Arduino_IO_TransferHandler<int, int>;

    extern Arduino_IO_TransferHandler<int, int> SENSOR_ACTOR_TRANSFER_HANDLER;
} // namespace SerialCommunication
