idf_component_register(SRCS "dawn_main.cpp"
                    "ble_server_cb.cpp" "includes/ble_server_cb.hpp"
                    "led_serv_mgr.cpp" "includes/led_serv_mgr.hpp"
                    "led_color_callback.cpp" "includes/led_color_callback.hpp"
                    "hal/includes/sk6812rgbw.hpp"
                    "includes/led_drv_mgr.hpp"
                    "includes/common_defs.hpp"
                    INCLUDE_DIRS "" "includes" "hal/includes")
