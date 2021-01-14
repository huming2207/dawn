#include "led_color_callback.hpp"
#include "led_manager.hpp"

void led_color_callback::onRead(NimBLECharacteristic *character)
{
    auto color = led_manager::instance().device().get_color();
    character->setValue((const uint8_t *)(&color), sizeof(uint32_t));
}

void led_color_callback::onWrite(NimBLECharacteristic *character)
{
    led_manager::instance().device().set_color()
    auto color = character->getValue<uint32_t>();

}
