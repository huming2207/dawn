#pragma once

#include <NimBLEDevice.h>

class led_serv_mgr
{
public:
    static led_serv_mgr& get_instance()
    {
        static led_serv_mgr instance;
        return instance;
    }

    esp_err_t init();

    NimBLECharacteristic *tx_characteristic = nullptr;
    NimBLEServer *server = nullptr;

private:
    led_serv_mgr() = default;
    static void ble_conn_task(void *ctx);
    bool device_connected = false;
    bool old_dev_connected = false;

public:
    led_serv_mgr (led_serv_mgr const &) = delete;
    void operator=(led_serv_mgr const &) = delete;
};



