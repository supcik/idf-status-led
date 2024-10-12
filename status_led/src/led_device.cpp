/**
 ******************************************************************************
 * @file        : led_device.cpp
 * @brief       : Led device for status LED
 * @author      : Jacques Supcik <jacques@supcik.net>
 * @date        : 2 October 2024
 ******************************************************************************
 * @copyright   : Copyright (c) 2024 Jacques Supcik
 * @attention   : SPDX-License-Identifier: MIT or Apache-2.0
 ******************************************************************************
 * @details
 *
 ******************************************************************************
 */

#include "status_led/led_device.hpp"

#include "driver/gpio.h"
#include "led_strip.h"

using namespace status_led;

const int Ws2812Led::kRmtResolution = 10 * 1000 * 1000;  // 10MHz

GpioLed::GpioLed(int pin, bool inverse) : LedDevice(pin), inverse_(inverse) {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = 1ULL << pin;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
}

void GpioLed::On(uint8_t r, uint8_t g, uint8_t b) {
    if (r == 0 && g == 0 && b == 0) {
        Off();
        return;
    }
    if (inverse_) {
        gpio_set_level(static_cast<gpio_num_t>(pin_), 0);
    } else {
        gpio_set_level(static_cast<gpio_num_t>(pin_), 1);
    }
}

void GpioLed::Off() {
    if (inverse_) {
        gpio_set_level(static_cast<gpio_num_t>(pin_), 1);
    } else {
        gpio_set_level(static_cast<gpio_num_t>(pin_), 0);
    }
}

Ws2812Led::Ws2812Led(int pin, bool swap_red_green)
    : LedDevice(pin), swap_red_green_(swap_red_green) {
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t stripConfig = {};
    stripConfig.strip_gpio_num = pin;
    stripConfig.max_leds = 1;                             // The number of LEDs in the strip,
    stripConfig.led_pixel_format = LED_PIXEL_FORMAT_GRB;  // Pixel format of your LED strip
    stripConfig.led_model = LED_MODEL_WS2812;             // LED strip model

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
    if (swap_red_green_) {
        led_strip_set_pixel(ledStrip_, 0, g, r, b);
    } else {
        led_strip_set_pixel(ledStrip_, 0, r, g, b);
    }
    led_strip_refresh(ledStrip_);
}

void Ws2812Led::Off() {
    led_strip_clear(ledStrip_);
    led_strip_refresh(ledStrip_);
}
