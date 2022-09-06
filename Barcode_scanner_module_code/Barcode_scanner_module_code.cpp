#include "BarcodeCode.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  //Rx=2, Tx=3
int i, j = 0;
static unsigned char Command[9];
//unsigned char CRC;
void Write(unsigned char Length) {
  for (i = 0; i < Length; i++)
  {
    mySerial.write(Command[i]);
  }
}
void Common_Setting(void){
  Command[0] = Command_Heard;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = (Addr_Functions >> 8) & 0xFF;
  Command[5] = (Addr_Functions << 8) & 0xFF;
  Command[6] = LED_Indicator_En + Buz_Indicator_En + Focus_Com + Light_Com + Command_Mode;
  //Serial.println(Command[6], HEX);
  Command[7] = 0xAB;
  Command[8] = 0xCD;
  Write(9);
}
void Set_Interface(void){
  Command[0] = Command_Heard;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = (Addr_OutputMode >> 8) & 0xFF;
  Command[5] = ((Addr_OutputMode << 8) >> 8) & 0xFF;
  Command[6] = UART_Output;
  Command[7] = 0xAB;
  Command[8] = 0xCD;
  Write(9);
}
void Scan_Command(){
  Command[0] = Command_Heard;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = 0x00;
  Command[5] = 0x02;
  Command[6] = 0x01;
  Command[7] = 0xAB;
  Command[8] = 0xCD;
  Write(9);
}
void Scan_Interval_Setting()
{
  Command[0] = Command_Heard;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = 0x00;
  Command[5] = 0x05;
  Command[6] = 0xFA;//Max:25.5s, FA=25s., 64=10s
  Command[7] = 0xAB;
  Command[8] = 0xCD;
  Write(9);
  }
void setup() {
  // put your setup code here, to run once:

  mySerial.begin(9600);
  Serial.begin(19200);
  Serial.println("************This is test of Barcode************");
  Common_Setting();
  //Scan_Interval_Setting();
  delay(1000);
  Set_Interface();
  // serialInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0 && Serial.read()== '1'){
      Serial.println("Begin Scanning....");
      Scan_Command();
   }
  if (mySerial.available()) {
    String Scan_Result;
    Scan_Result = mySerial.readString();
    Serial.println(Scan_Result);  
  }
}
