#pragma once

#include <NimBLEDevice.h>

class ble_server_cb : public NimBLEServerCallbacks
{
public:
    void onConnect(NimBLEServer *server) override;
    void onDisconnect(NimBLEServer* server) override;
    uint32_t onPassKeyRequest() override;
    bool onConfirmPIN(uint32_t pass_key) override;
    void onAuthenticationComplete(ble_gap_conn_desc *desc) override;

private:
    static constexpr const char *TAG = "ble_server";
};



