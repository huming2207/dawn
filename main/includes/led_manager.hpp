#pragma once

#include <sk6812rgbw.hpp>

using sk6812 = sk6812rgbw<GPIO_NUM_5, 15, RMT_CHANNEL_7>;

class led_manager
{
public:
    static led_manager& instance()
    {
        static led_manager instance;
        return instance;
    }


    led_manager (led_manager const &) = delete;
    void operator=(led_manager const &) = delete;

public:
    sk6812 &device()
    {
        return sk;
    }

private:
    led_manager() = default;
    sk6812 sk{};
};