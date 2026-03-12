// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <driver/gpio.h>
#include <stdint.h>

#include "status_led/led_device.hpp"

namespace status_led {

/**
 * @brief RGB LED implementation backed by discrete GPIO channels.
 */
class GpioLed : public LedDevice {
   public:
    /**
     * @brief Construct a GPIO LED device.
     * @param pin Base GPIO pin used by the device implementation.
     * @param inverse True when output logic is inverted.
     */
    GpioLed(gpio_num_t pin, bool inverse = false);

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
    bool inverse_;
};

}  // namespace status_led
