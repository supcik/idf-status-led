/**
 ******************************************************************************
 * @file        : led_device.hpp
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

#pragma once

#include <stdint.h>

#include "led_strip.h"

namespace status_led {

class LedDevice {
   public:
    LedDevice(int pin) : pin_(pin) {}
    virtual ~LedDevice() = default;
    virtual void On(uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void Off() = 0;

   protected:
    int pin_;
};

class GpioLed : public LedDevice {
   public:
    GpioLed(int pin, bool inverse = false);
    void On(uint8_t r, uint8_t g, uint8_t b) override;
    void Off() override;

   private:
    bool inverse_;
};

class Ws2812Led : public LedDevice {
   public:
    Ws2812Led(int pin, led_color_component_format_t color_component_format);
    ~Ws2812Led() override;
    void On(uint8_t r, uint8_t g, uint8_t b) override;
    void Off() override;

   private:
    static const int kRmtResolution;
    led_strip_handle_t ledStrip_;
};

}  // namespace status_led
