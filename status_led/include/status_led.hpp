// SPDX-FileCopyrightText: 2026 Jacques Supcik <jacques@supcik.net>
//
// SPDX-License-Identifier: MIT

#pragma once

/**
 * @brief LedColor class
 * @details This class is used to represent the RGB color of a LED
 */

#include <memory>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "led_color.hpp"
#include "status_led/led_device.hpp"

static const int kDefaultBrightness = 32;

/**
 * @brief StatusLed class
 * @details This class is used to control a RGB Status LED.
 */
class StatusLed {
   public:
    /**
     * @brief Construct a new StatusLed object.
     * @param ledDevice LED device implementation to use for controlling the LED hardware.
     */
    StatusLed(std::unique_ptr<status_led::LedDevice> ledDevice);

    /**
     * @brief Destroy the StatusLed object
     */
    ~StatusLed();

    static const LedColor kRed;
    static const LedColor kOrange;
    static const LedColor kGreen;
    static const LedColor kBlue;
    static const LedColor kWhite;
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
    std::unique_ptr<status_led::LedDevice> ledDevice_;

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
