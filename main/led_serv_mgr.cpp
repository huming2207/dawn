#include "ble_server_cb.hpp"
#include "led_serv_mgr.hpp"
#include "led_drv_mgr.hpp"
#include "led_color_callback.hpp"

#define SERVICE_UUID            "fbe1b71b-42a1-4c3a-9f00-85c6d996af53"
#define COLOR_UUID              "fbe1b71b-42a1-4c3a-9f00-85c6d996af56"

esp_err_t led_serv_mgr::init()
{
    auto ret = led_drv_mgr::instance().device().init();
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "LED Device init error: 0x%x", ret);
        return ret;
    }

    server = NimBLEDevice::createServer();
    server->setCallbacks(new ble_server_cb());

    NimBLEService *service = server->createService(SERVICE_UUID);

    auto *color_character = service->createCharacteristic(COLOR_UUID, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC);
    color_character->setCallbacks(new led_color_callback());

    if (!service->start()) {
        ESP_LOGE(TAG, "Failed to start BLE LED service");
        return ESP_FAIL;
    }

    if (!server->getAdvertising()->start()) {
        ESP_LOGE(TAG, "Failed to start BLE Server");
        return ESP_FAIL;
    }


    return ESP_OK;
}
