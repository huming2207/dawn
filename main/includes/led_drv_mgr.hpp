#pragma once

#include <sk6812rgbw.hpp>

using sk6812 = sk6812rgbw<GPIO_NUM_5, 15, RMT_CHANNEL_7>;

class led_drv_mgr
{
public:
    static led_drv_mgr& instance()
    {
        static led_drv_mgr instance;
        return instance;
    }


    led_drv_mgr (led_drv_mgr const &) = delete;
    void operator=(led_drv_mgr const &) = delete;

public:
    sk6812 &device()
    {
        return sk;
    }

private:
    led_drv_mgr() = default;
    sk6812 sk{};
};