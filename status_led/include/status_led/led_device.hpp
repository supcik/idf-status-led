// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

/**
 * @brief Abstract LED device interface.
 */

#include "led_strip.h"

namespace status_led {

class LedDevice {
   public:
    /*!
     * @brief Turn LED on with a color.
     */
    virtual void On(uint8_t r, uint8_t g, uint8_t b) = 0;

    /**
     * @brief Turn LED off.
     */
    virtual void Off() = 0;
};

}  // namespace status_led
