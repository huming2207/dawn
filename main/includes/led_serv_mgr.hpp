#pragma once

#include <NimBLEDevice.h>

class led_serv_mgr
{
public:
    static led_serv_mgr& instance()
    {
        static led_serv_mgr instance;
        return instance;
    }

    esp_err_t init();
    NimBLEServer *server = nullptr;

private:
    led_serv_mgr() = default;
    static constexpr const char *TAG = "ble_led_serv";

public:
    led_serv_mgr (led_serv_mgr const &) = delete;
    void operator=(led_serv_mgr const &) = delete;
};



