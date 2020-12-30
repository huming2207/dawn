#pragma once

#include <driver/rmt.h>

template <gpio_num_t PIN, size_t COUNT, rmt_channel_t CHANNEL = RMT_CHANNEL_7>
class sk6812rgbw
{
public:
    sk6812rgbw()
    {
        bit_count = COUNT * 32;
    }

    ~sk6812rgbw()
    {
        rmt_driver_uninstall(CHANNEL);
    }

    esp_err_t init()
    {
        rmt_config_t config{};
        config.rmt_mode = RMT_MODE_TX;
        config.channel = CHANNEL;
        config.gpio_num = PIN;
        config.mem_block_num = 1;
        config.tx_config.loop_en = false;
        config.tx_config.carrier_en = false;
        config.tx_config.idle_output_en = true;
        config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
        config.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;
        config.clk_div = 8; // 80MHx / 8 = 10MHz translates to  0,1 us = 100 ns per count

        auto ret = rmt_config(&config);
        ret = ret ?: rmt_driver_install(config.channel, 0, 0);

        return ret;
    }

    uint32_t bytes_to_color32(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
    {
        uint32_t color32 = 0;

        color32 |= ((uint32_t) g << 24);
        color32 |= ((uint32_t) r << 16);
        color32 |= ((uint32_t) b << 8);
        color32 |= (uint32_t) w;

        return color32;
    }


    uint32_t color32_to_bytes(uint32_t color32, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *w)
    {

        *g = (color32 >> 24) & 0xff;
        *r = (color32 >> 16) & 0xff;
        *b = (color32 >> 8) & 0xff;
        *w = color32 & 0xff;

        return (color32);
    }

    void set_color32(int led, uint32_t kleur, int brightness = -1)
    {
        uint8_t r, g, b, w;

        color32_to_bytes(kleur, &r, &g, &b, &w);
        set_color(led, r, g, b, w, brightness);

    }

    void set_color(int led, uint8_t red, uint8_t green, uint8_t blue, uint8_t white, int brightness = -1)
    {
        uint32_t kleur = 0, bright;
        int i, bit;

        if (led < 0 || led >= get_led_count()) return;

        bright = brightness;
        if (brightness == -1) bright = 100;

        red = bright * red / 100;
        green = bright * green / 100;
        blue = bright * blue / 100;
        white = bright * white / 100;

        kleur |= ((uint32_t) green << 24);
        kleur |= ((uint32_t) red << 16);
        kleur |= ((uint32_t) blue << 8);
        kleur |= (uint32_t) white;

        for (i = (led * 32), bit = 0; bit < 32; bit++) {

            if ((kleur & (1 << (31 - bit)))) {
                rmt_item()[i].level0 = 1;
                rmt_item()[i].duration0 = 6;
                rmt_item()[i].level1 = 0;
                rmt_item()[i].duration1 = 6;
            } else {
                rmt_item()[i].level0 = 1;
                rmt_item()[i].duration0 = 3;
                rmt_item()[i].level1 = 0;
                rmt_item()[i].duration1 = 9;
            }
            //if ( bit == 31 )  _skstrip[i].duration1 += 60;
            ++i;
        }

    }

    esp_err_t commit()
    {
        return rmt_write_items(CHANNEL, rmt_item(), bit_count, true);
    }

    void clear()
    {
        for (int i = 0; i < COUNT; ++i) {
            set_color(i, 0, 0, 0, 0);
        }

        commit();
    }

    int get_led_count() const
    {
        return COUNT;
    }


private:
    int bit_count;
    const char *TAG = "sk6812rgbw";
    static rmt_item32_t *rmt_item()
    {
        static rmt_item32_t item[COUNT * 32];
        return item;
    }
};
