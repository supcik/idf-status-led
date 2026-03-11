// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

/**
 * @brief Abstract LED device interface.
 */

#include <stdint.h>

#include "led_strip.h"

namespace status_led {

class LedDevice {
   public:
    /**
     * @brief Construct a new LED device bound to a GPIO pin.
     * @param pin GPIO pin used by the underlying LED hardware.
     */
    LedDevice(int pin) : pin_(pin) {}

    virtual ~LedDevice() = default;

    /*!
     * @brief Turn LED on with a color.
     */
    virtual void On(uint8_t r, uint8_t g, uint8_t b) = 0;

    /**
     * @brief Turn LED off.
     */
    virtual void Off() = 0;

   protected:
    int pin_;
};

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
    GpioLed(int pin, bool inverse = false);

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
    bool inverse_;
};

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
    Ws2812Led(int pin, led_color_component_format_t color_component_format);

    ~Ws2812Led() override;

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
    static const int kRmtResolution;
    led_strip_handle_t ledStrip_;
};

}  // namespace status_led
