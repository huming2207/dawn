#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "esp_log.h"

#include "sk6812rgbw.hpp"
#include <NimBLEDevice.h>
#include "led_serv_mgr.hpp"

#define TAG "dawn"

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Hello world");

    NimBLEDevice::init("Bluart");

    ESP_ERROR_CHECK(led_serv_mgr::instance().init());

    vTaskDelay(portMAX_DELAY);
}
