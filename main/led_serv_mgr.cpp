#include "ble_server_cb.hpp"
#include "led_serv_mgr.hpp"

#define SERVICE_UUID            "1ac91080-1067-478c-b72c-34a8a317da08"
#define COLOR_UUID              "effd29b9-fa9b-4d61-84f5-24e397c59962"
#define BRIGHTNESS_UUID         "dca811c8-f101-4ed5-a7db-b6729a90eb39"

void led_serv_mgr::ble_conn_task(void *ctx)
{

}

esp_err_t led_serv_mgr::init()
{
    server = NimBLEDevice::createServer();
    server->setCallbacks(new ble_server_cb());

    NimBLEService *service = server->createService(SERVICE_UUID);
    auto *color_character = service->createCharacteristic(COLOR_UUID);
    auto *bright_character = service->createCharacteristic(BRIGHTNESS_UUID);

    return ESP_OK;
}
