#include "broker/broker.h"

namespace SerialCommunication
{
    template <class rcv, class snd>
    class Ardunio_IO_TransferHandler
    {
    private:
        Broker::Broker<rcv> *rcvBroker;
        Broker::Broker<snd> *sndBroker;

    public:
        Ardunio_IO_TransferHandler(
            Broker::Broker<rcv> *rcvBroker,
            Broker::Broker<snd> *sndBroker);
        void run();
        void init();
    };

    template class Ardunio_IO_TransferHandler<int, int>;

    extern Ardunio_IO_TransferHandler<int, int> SENSOR_ACTOR_TRANSFER_HANDLER;
} // namespace SerialCommunication
