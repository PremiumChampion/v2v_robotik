#include "BarcodeCode.h"
#include "barcodescannermodule.h"
#include <SoftwareSerial.h>
#include "sensors/sensors.h"

namespace QR
{

  BarcodeScannerModule::BarcodeScannerModule(SoftwareSerial *serialScannerConnection)
  {
    Serial.begin(9600);

    this->scannerSerial = serialScannerConnection;
    this->i = 0;
    this->j = 0;
    this->lastReadingTime = millis();

    this->scannerSerial->begin(9600);
    Serial.println("Common_Setting");
    this->Common_Setting();
    Serial.println("Set_Interface");
    this->Set_Interface();
    Serial.println("Scan_Interval_Setting");
    this->Scan_Interval_Setting(0);
    // this->Scan_Command();
  }

  BarcodeScannerModule::~BarcodeScannerModule()
  {
  }

  void BarcodeScannerModule::getValue()
  {
  }

  // static unsigned char Command[9];
  // unsigned char CRC;
  void BarcodeScannerModule::Write(unsigned char Length)
  {
    for (i = 0; i < Length; i++)
    {
      this->scannerSerial->write(this->Command[i]);
    }
  }
  void BarcodeScannerModule::Common_Setting(void)
  {
    this->Command[0] = Command_Heard;
    this->Command[1] = 0x00;
    this->Command[2] = Command_Write;
    this->Command[3] = 0x01;
    this->Command[4] = (Addr_Functions >> 8) & 0xFF;
    this->Command[5] = (Addr_Functions << 8) & 0xFF;
    this->Command[6] = LED_Indicator_En + Buz_Indicator_En + Focus_Com + Light_Com + Continous_Mode;
    // Serial.println(Command[6], HEX);
    this->Command[7] = 0xAB;
    this->Command[8] = 0xCD;
    this->Write(9);
  }
  void BarcodeScannerModule::Set_Interface(void)
  {
    this->Command[0] = Command_Heard;
    this->Command[1] = 0x00;
    this->Command[2] = Command_Write;
    this->Command[3] = 0x01;
    this->Command[4] = (Addr_OutputMode >> 8) & 0xFF;
    this->Command[5] = ((Addr_OutputMode << 8) >> 8) & 0xFF;
    this->Command[6] = UART_Output;
    this->Command[7] = 0xAB;
    this->Command[8] = 0xCD;
    this->Write(9);
  }
  void BarcodeScannerModule::Scan_Command()
  {
    this->Command[0] = Command_Heard;
    this->Command[1] = 0x00;
    this->Command[2] = Command_Write;
    this->Command[3] = 0x01;
    this->Command[4] = 0x00;
    this->Command[5] = 0x02;
    this->Command[6] = 0x01;
    this->Command[7] = 0xAB;
    this->Command[8] = 0xCD;
    this->Write(9);
  }
  void BarcodeScannerModule::Scan_Interval_Setting(int interval)
  {
    interval = interval % 256;
    this->Command[0] = Command_Heard;
    this->Command[1] = 0x00;
    this->Command[2] = Command_Write;
    this->Command[3] = 0x01;
    this->Command[4] = 0x00;
    this->Command[5] = 0x05;
    this->Command[6] = interval; // Max:25.5s, FA=25s., 64=10s (min)0-255(max)
    this->Command[7] = 0xAB;
    this->Command[8] = 0xCD;
    this->Write(9);
  }

  void BarcodeScannerModule::run()
  {
    if (this->scannerSerial->available())
    {
      do
      {
        char nextChar = (char)this->scannerSerial->read();
        // Serial.println(nextChar);
        this->buffer += nextChar;
        // Serial.println(Scan_Result);
      } while (this->scannerSerial->available());

      lastReadingTime = millis();
    }

    if (lastReadingTime + 70 < millis() && this->buffer.length() > 0)
    {
      this->currentValue = buffer;
      this->buffer = "";
      Sensors::MESSAGE_BROKER.set(Sensors::QR_CODE, currentValue.toInt());
    }
  }

} // namespace QR
