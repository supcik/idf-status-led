/**
 ******************************************************************************
 * @file        : status_led.cpp
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

#include "status_led.hpp"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "status_led/led_device.hpp"

const char* StatusLed::kTag = "StatusLed";
const int StatusLed::kTimeUnitMs = 10;
const int StatusLed::kThreadStackSize = 2800;
const int StatusLed::kQueueSize = 4;

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

StatusLed::StatusLed(status_led::LedDevice* ledDevice) : ledDevice_(ledDevice) {
    queue_ = xQueueCreate(kQueueSize, sizeof(LedCommand));

    // create a task with the "Thread" method
    xTaskCreate([](void* param) { static_cast<StatusLed*>(param)->Task(); },
                "LedTask",
                kThreadStackSize,
                this,
                uxTaskPriorityGet(nullptr),
                &task_);
}

StatusLed::~StatusLed() {
    vTaskDelete(task_);
    vQueueDelete(queue_);
}

void StatusLed::Off() {
    ESP_LOGD(kTag, "Switching LED Off");
    LedCommand cmd = {
        .cmd = kOff,
        .color = 0,
        .timeOnMs = 0,
        .timeOffMs = 0,
        .flashCount = 0,
    };
    xQueueSend(queue_, &cmd, 0);
}

void StatusLed::On(LedColor color, int brightness) {
    ESP_LOGD(kTag, "Switching LED On");
    color.ApplyBrightness(brightness);
    LedCommand cmd = {
        .cmd = kOn,
        .color = color.Value(),
        .timeOnMs = 0,
        .timeOffMs = 0,
        .flashCount = 0,
    };
    xQueueSend(queue_, &cmd, 0);
}

void StatusLed::Blink(int timeOnMs, int timeOffMs, LedColor color, int brightness) {
    ESP_LOGD(kTag, "Blinking LED");
    color.ApplyBrightness(brightness);
    LedCommand cmd = {
        .cmd = kBlink,
        .color = color.Value(),
        .timeOnMs = timeOnMs,
        .timeOffMs = timeOffMs,
        .flashCount = 0,
    };
    xQueueSend(queue_, &cmd, 0);
}

void StatusLed::Flash(int timeOnMs, int timeOffMs, int count, LedColor color, int brightness) {
    ESP_LOGD(kTag, "Blinking LED");
    color.ApplyBrightness(brightness);
    LedCommand cmd = {
        .cmd = kFlash,
        .color = color.Value(),
        .timeOnMs = timeOnMs,
        .timeOffMs = timeOffMs,
        .flashCount = count,
    };
    xQueueSend(queue_, &cmd, 0);
}

// StatusLed Task. The main purpose of this task is to make the status LED
// blink, stay off, or stay on.
void StatusLed::Task() {
    ESP_LOGI(kTag, "Starting LED Task");
    LedCommand cmd, restoreCmd;
    TickType_t delay = portMAX_DELAY;
    bool is_on = false;

    while (true) {
        LedCommand prevCmd;
        if (cmd.cmd != kFlash) {  // Don't save flash commands
            prevCmd = cmd;
        }
        BaseType_t res = xQueueReceive(queue_, &cmd, delay);
        bool newMessage = res == pdTRUE;
        if (newMessage) {
            ESP_LOGD(kTag, "Received command %d", cmd.cmd);
        }
        switch (cmd.cmd) {
            case kOff:
                ESP_LOGD(kTag, "Switching LED Off");
                ledDevice_->Off();
                delay = portMAX_DELAY;
                break;
            case kOn:
                ESP_LOGD(kTag, "Switching LED On");
                ledDevice_->On(cmd.color >> 16 & 0xff, cmd.color >> 8 & 0xff, cmd.color & 0xff);
                delay = portMAX_DELAY;
                break;
            case kFlash:
                ESP_LOGD(kTag, "Flashing LED : flashCount=%d", cmd.flashCount);
                if (newMessage) {
                    restoreCmd = prevCmd;
                    if (cmd.flashCount < 1) {
                        cmd.flashCount = 1;
                    }
                    is_on = false;
                }
                if (is_on) {
                    ledDevice_->Off();
                    is_on = false;
                    cmd.flashCount--;
                    delay = pdMS_TO_TICKS(cmd.timeOffMs);
                } else {
                    if (cmd.flashCount <= 0) {
                        cmd = restoreCmd;
                        cmd.flashCount = 0;
                        delay = 0;
                    } else {
                        ledDevice_->On(
                            (cmd.color >> 16) & 0xff, (cmd.color >> 8) & 0xff, cmd.color & 0xff);
                        is_on = true;
                        delay = pdMS_TO_TICKS(cmd.timeOnMs);
                    }
                }
                break;
            case kBlink:
                ESP_LOGD(kTag, "Blinking LED");
                if (newMessage) {
                    is_on = false;
                }
                if (is_on) {
                    ledDevice_->Off();
                    is_on = false;
                    delay = pdMS_TO_TICKS(cmd.timeOffMs);
                } else {
                    ledDevice_->On(
                        (cmd.color >> 16) & 0xff, (cmd.color >> 8) & 0xff, cmd.color & 0xff);
                    is_on = true;
                    delay = pdMS_TO_TICKS(cmd.timeOnMs);
                }
                break;
            default:
                ESP_LOGW(kTag, "Unknown command");
                break;
        }
    }
}
