// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#include "status_led/ws2812_led_device.hpp"

#include "driver/gpio.h"
#include "led_strip.h"

using namespace status_led;

const int kRmtResolution = 10 * 1000 * 1000;  // 10MHz

Ws2812Led::Ws2812Led(gpio_num_t pin, led_color_component_format_t color_component_format)
    : pin_(pin) {
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t stripConfig = {};
    stripConfig.strip_gpio_num = pin;
    stripConfig.max_leds = 1;  // The number of LEDs in the strip,
    stripConfig.color_component_format = color_component_format;
    stripConfig.led_model = LED_MODEL_WS2812;  // LED strip model

    led_strip_rmt_config_t rmtConfig = {};

    rmtConfig.clk_src = RMT_CLK_SRC_DEFAULT;
    rmtConfig.resolution_hz = kRmtResolution;

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&stripConfig, &rmtConfig, &ledStrip_));
}

Ws2812Led::~Ws2812Led() {
    led_strip_clear(ledStrip_);
    led_strip_refresh(ledStrip_);
    led_strip_del(ledStrip_);
}

void Ws2812Led::On(uint8_t r, uint8_t g, uint8_t b) {
    led_strip_set_pixel(ledStrip_, 0, r, g, b);
    led_strip_refresh(ledStrip_);
}

void Ws2812Led::Off() {
    led_strip_clear(ledStrip_);
    led_strip_refresh(ledStrip_);
}
