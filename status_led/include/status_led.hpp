// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

/**
 * @brief LedColor class
 * @details This class is used to represent the RGB color of a LED
 */

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "status_led/led_device.hpp"

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

    /** @brief Red component. */
    uint8_t r_;
    /** @brief Green component. */
    uint8_t g_;
    /** @brief Blue component. */
    uint8_t b_;
};

static const int kDefaultBrightness = 32;

/**
 * @brief StatusLed class
 * @details This class is used to control a RGB Status LED.
 */
class StatusLed {
   public:
    /**
     * @brief Construct a new StatusLed object.
     * @param ledDevice LED device implementation.
     */
    StatusLed(status_led::LedDevice& ledDevice);

    /**
     * @brief Construct a new StatusLed object.
     * @param ledDevice Pointer to LED device implementation.
     */
    StatusLed(status_led::LedDevice* ledDevice);

    /**
     * @brief Destroy the StatusLed object
     */
    ~StatusLed();

    /** @brief Predefined red color constant. */
    static const LedColor kRed;
    /** @brief Predefined orange color constant. */
    static const LedColor kOrange;
    /** @brief Predefined green color constant. */
    static const LedColor kGreen;
    /** @brief Predefined blue color constant. */
    static const LedColor kBlue;
    /** @brief Predefined white color constant. */
    static const LedColor kWhite;

    /** @brief Default color constant. */
    static const LedColor kDefaultColor;

    /**
     * @brief Turn the LED off.
     */
    void Off();

    /**
     * @brief Turn the LED on with a fixed color.
     * @param color Base color to display.
     * @param brightness Brightness factor in range [0, 255].
     */
    void On(LedColor color = kDefaultColor, int brightness = kDefaultBrightness);

    /**
     * @brief Blink continuously with on/off timings.
     * @param timeOnMs On duration in milliseconds.
     * @param timeOffMs Off duration in milliseconds.
     * @param color Base color to display.
     * @param brightness Brightness factor in range [0, 255].
     */
    void Blink(int timeOnMs,
               int timeOffMs,
               LedColor color = kDefaultColor,
               int brightness = kDefaultBrightness);

    /**
     * @brief Flash a finite number of times.
     * @param timeOnMs On duration in milliseconds.
     * @param timeOffMs Off duration in milliseconds.
     * @param count Number of flashes.
     * @param color Base color to display.
     * @param brightness Brightness factor in range [0, 255].
     */
    void Flash(int timeOnMs,
               int timeOffMs,
               int count = 1,
               LedColor color = kDefaultColor,
               int brightness = kDefaultBrightness);

    /** @brief Underlying LED device implementation. */
    status_led::LedDevice& ledDevice_;

   private:
    enum ledCmd { kOff, kOn, kFlash, kBlink };

    struct LedCommand {
        enum ledCmd cmd;
        uint32_t color;
        int timeOnMs;
        int timeOffMs;
        int flashCount;
    };

    static const char* kTag;
    static const int kTimeUnitMs;
    static const int kThreadStackSize;
    static const int kQueueSize;

    void Task();
    uint32_t ColorValue(LedColor color, int brightness);

    QueueHandle_t queue_;
    TaskHandle_t task_;
};
