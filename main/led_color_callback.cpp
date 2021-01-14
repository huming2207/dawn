#include "led_color_callback.hpp"
#include "led_drv_mgr.hpp"

void led_color_callback::onRead(NimBLECharacteristic *character)
{
    auto color = led_drv_mgr::instance().device().get_color();
    character->setValue((const uint8_t *)(&color), sizeof(uint32_t));

    ESP_LOGI(TAG, "Read color requested: 0x%x", color);
}

void led_color_callback::onWrite(NimBLECharacteristic *character)
{
    auto color = character->getValue<uint32_t>();
    auto &device = led_drv_mgr::instance().device();

    device.set_color(color);
    ESP_ERROR_CHECK(device.commit());
    ESP_LOGI(TAG, "New color: 0x%x", color);
}
