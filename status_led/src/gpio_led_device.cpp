// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#include "status_led/gpio_led_device.hpp"

#include "driver/gpio.h"

using namespace status_led;

GpioLed::GpioLed(gpio_num_t pin, bool inverse) : pin_(pin), inverse_(inverse) {
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
