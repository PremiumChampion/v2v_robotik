#include "BarcodeCode.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
#pragma once

namespace QR
{
    class BarcodeScannerModule
    {
    private:
        String currentValue;
        SoftwareSerial *scannerSerial;
        int i, j = 0;
        unsigned char Command[9];
        String buffer;
        unsigned long lastReadingTime;

        void Write(unsigned char Length);
        void Common_Setting(void);
        void Set_Interface(void);
        void Scan_Command();
        void Scan_Interval_Setting(int);
        
    public:
        BarcodeScannerModule(SoftwareSerial *serialScannerConnection);
        ~BarcodeScannerModule();
        void run();
        void getValue();
    };
} // namespace QR
