#include "ble_server_cb.hpp"

void ble_server_cb::onConnect(NimBLEServer *server)
{
    ESP_LOGW(TAG, "On connect");
}

void ble_server_cb::onDisconnect(NimBLEServer *server)
{
    ESP_LOGW(TAG, "On disconnect");
}

bool ble_server_cb::onConfirmPIN(uint32_t pass_key)
{
    ESP_LOGW(TAG, "Got PIN: %u", pass_key);

    return pass_key == 123456;
}

uint32_t ble_server_cb::onPassKeyRequest()
{
    ESP_LOGW(TAG, "On pass key request");
    return 123456;
}

void ble_server_cb::onAuthenticationComplete(ble_gap_conn_desc *desc)
{
    ESP_LOGW(TAG, "Auth complete");
}
