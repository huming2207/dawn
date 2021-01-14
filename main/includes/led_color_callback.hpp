#pragma once

#include <NimBLEDevice.h>

class led_color_callback : public NimBLECharacteristicCallbacks
{
public:
    void onRead(NimBLECharacteristic* pCharacteristic) override;
    void onWrite(NimBLECharacteristic* pCharacteristic) override;

};



