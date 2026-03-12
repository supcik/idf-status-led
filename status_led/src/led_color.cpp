// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#include "led_color.hpp"

#include "status_led.hpp"

LedColor::LedColor(int r, int g, int b) : r_(r), g_(g), b_(b) {}
void LedColor::ApplyBrightness(int brightness) {
    r_ = r_ * brightness / 255;
    g_ = g_ * brightness / 255;
    b_ = b_ * brightness / 255;
}

const LedColor StatusLed::kRed(255, 0, 0);
const LedColor StatusLed::kOrange(255, 32, 0);
const LedColor StatusLed::kGreen(0, 255, 0);
const LedColor StatusLed::kBlue(0, 0, 255);
const LedColor StatusLed::kWhite(255, 255, 255);
const LedColor StatusLed::kDefaultColor = kBlue;
