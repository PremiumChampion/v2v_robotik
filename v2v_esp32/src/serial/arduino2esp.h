#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#define SOFTWARE_SERIAL 0x0
#define HARDWARE_SERIAL 0x1

#define SERIAL_INTERFACE SOFTWARE_SERIAL

namespace SerialCommunication
{
	enum SerialMode
	{
		IDLE,
		SENDING,
		RECIEVING,
	};

	class Arduino2esp
	{
	private:
#if SERIAL_INTERFACE == SOFTWARE_SERIAL
		SoftwareSerial *serial;
#elif SERIAL_INTERFACE == HARDWARE_SERIAL
		HardwareSerial *serial;
#endif

		// buffers serial input until a whole fragment is ready
		String rcvBuffer;
		// the time the serial communication Received some data (millis)
		unsigned long lastReceiveTime;
		// buffers serial output until it is ready to be sent
		String sndBuffer;

		// SoftwareSerial can not receive and send data at the same time
		SerialMode mode;
		// method for sending serial data
		void snd_data();
		// method for recieving serial data
		void rcv_data();

	public:
#if SERIAL_INTERFACE == SOFTWARE_SERIAL
		Arduino2esp(SoftwareSerial *serialConnection);
#elif SERIAL_INTERFACE == HARDWARE_SERIAL
		Arduino2esp(HardwareSerial *serialConnection);
#endif
		void init();
		void run();
		// receive serial data
		// strips newlines
		String receive();
		// send serial data
		void send(String data);
		bool hasData();
	};

	extern Arduino2esp ArduinoConnection;

} // namespace SerialCommunication
