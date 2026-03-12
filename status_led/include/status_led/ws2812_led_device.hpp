// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

/**
 * @brief Abstract LED device interface.
 */

#include <driver/gpio.h>
#include <stdint.h>

#include "led_strip.h"
#include "status_led/led_device.hpp"

namespace status_led {

/**
 * @brief WS2812/NeoPixel LED implementation.
 */
class Ws2812Led : public LedDevice {
   public:
    /**
     * @brief Construct a WS2812 LED device.
     * @param pin GPIO pin connected to the WS2812 data line.
     * @param color_component_format Color byte order expected by the LED.
     */
    Ws2812Led(gpio_num_t pin, led_color_component_format_t color_component_format);

    ~Ws2812Led();

    /**
     * @brief Turn LED on with a color.
     * @param r Red component in range [0, 255].
     * @param g Green component in range [0, 255].
     * @param b Blue component in range [0, 255].
     */
    void On(uint8_t r, uint8_t g, uint8_t b) override;

    /**
     * @brief Turn LED off.
     */
    void Off() override;

   private:
    gpio_num_t pin_;
    led_strip_handle_t ledStrip_;
};

}  // namespace status_led
