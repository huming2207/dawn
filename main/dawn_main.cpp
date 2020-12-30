#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "esp_log.h"

#include "sk6812rgbw.hpp"

#define TAG "dawn"

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Hello world");
    sk6812rgbw<GPIO_NUM_5, 15, RMT_CHANNEL_7> sk;
    sk.init();
    for (int idx = 0; idx < 15; idx++) {
        switch(idx % 5) {
            case 0: {
                sk.set_color(idx, 0, 0, 0, 255, 255);
                break;
            }
            case 1: {
                sk.set_color(idx, 255, 0, 0, 0, 255);
                break;
            }
            case 2: {
                sk.set_color(idx, 0, 255, 0, 0, 255);
                break;
            }
            case 3: {
                sk.set_color(idx, 0, 0, 255, 0, 255);
                break;
            }
            case 4: {
                sk.set_color(idx, 255, 255, 0, 0, 255);
                break;
            }

            default: {
                sk.set_color(idx, 0, 0, 0, 255, 255);
                break;
            }
        }
    }
    ESP_ERROR_CHECK(sk.commit());

    vTaskDelay(portMAX_DELAY);
}
