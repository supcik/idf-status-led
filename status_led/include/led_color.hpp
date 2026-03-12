// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>

/**
 * @brief LedColor class
 * @details This class is used to represent the RGB color of a LED
 */

class LedColor {
   public:
    /**
     * @brief  Construct a new LedColor object
     * @param r Red component (0..255)
     * @param g Green component (0..255)
     * @param b Blue component (0..255)
     */
    LedColor(int r, int g, int b);

    /**
     * @brief Apply brightness scaling to the color.
     * @param brightness Brightness factor in range [0, 255].
     */
    void ApplyBrightness(int brightness);

    /**
     * @brief Get packed RGB value.
     * @return Packed 24-bit value formatted as 0xRRGGBB.
     */
    uint32_t Value() const { return (r_ << 16) | (g_ << 8) | b_; }

   private:
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};
