/**
 ******************************************************************************
 * @file        : status_led.hpp
 * @brief       : Status Led Driver
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

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "status_led/led_device.hpp"

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
    void ApplyBrightness(int brightness);
    uint32_t Value() const { return (r_ << 16) | (g_ << 8) | b_; }

    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};

const LedColor kRed(255, 0, 0);
const LedColor kOrange(255, 32, 0);
const LedColor kGreen(0, 255, 0);
const LedColor kBlue(0, 0, 255);
const LedColor kWhite(255, 255, 255);

const LedColor kDefaultColor = kBlue;
const int kDefaultBrightness = 32;

/**
 * @brief StatusLed class
 * @details This class is used to control a RGB Status LED.
 */
class StatusLed {
   public:
    /**
     * brief Construct a new StatusLed object
     */
    StatusLed(status_led::LedDevice* ledDevice);

    /**
     * @brief Destroy the StatusLed object
     */
    ~StatusLed();

    void Off();
    void On(LedColor color = kDefaultColor, int brightness = kDefaultBrightness);
    void Blink(int timeOnMs,
               int timeOffMs,
               LedColor color = kDefaultColor,
               int brightness = kDefaultBrightness);
    void Flash(int timeOnMs,
               int timeOffMs,
               int count = 1,
               LedColor color = kDefaultColor,
               int brightness = kDefaultBrightness);

    // Context
    status_led::LedDevice* ledDevice_;

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
