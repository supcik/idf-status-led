/**
 ******************************************************************************
 * @file        : main.cpp
 * @brief       : Simple test for Status Led
 * @author      : Jacques Supcik <jacques@supcik.net>
 * @date        : 11 March 2024
 ******************************************************************************
 * @copyright   : Copyright (c) 2024 Jacques Supcik
 * @attention   : SPDX-License-Identifier: MIT or Apache-2.0
 ******************************************************************************
 * @details
 *
 ******************************************************************************
 */

#include <inttypes.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "status_led.hpp"

extern "C" {
void app_main(void);
}

const char* kTag = "main";

void PrintStat() {
    UBaseType_t nOfTasks = uxTaskGetNumberOfTasks();
    TaskStatus_t* data = new TaskStatus_t[nOfTasks];
    UBaseType_t res = uxTaskGetSystemState(data, nOfTasks, nullptr);
    if (res == pdFALSE) {
        ESP_LOGE(kTag, "Failed to get task status");
        delete[] data;
        return;
    }
    ESP_LOGI(kTag, "Number of tasks: %d", nOfTasks);
    for (UBaseType_t i = 0; i < nOfTasks; i++) {
        ESP_LOGI(
            kTag, "Task %d: %s, SHW=%" PRIu32, i, data[i].pcTaskName, data[i].usStackHighWaterMark);
    }
    delete[] data;
}

void app_main(void) {
    ESP_LOGI(kTag, "Starting StatusLed test");
    StatusLed led;
    while (true) {
        led.On(kGreen, 8);
        vTaskDelay(pdMS_TO_TICKS(2000));
        led.Blink(50, 450, kBlue, 32);
        vTaskDelay(pdMS_TO_TICKS(2000));
        led.On(kOrange, 8);
        vTaskDelay(pdMS_TO_TICKS(1000));
        led.Flash(50, 200, 3, kWhite, 32);
        vTaskDelay(pdMS_TO_TICKS(3000));
        led.Blink(50, 50, kWhite, 32);
        vTaskDelay(pdMS_TO_TICKS(1000));
        led.Flash(50, 200, 3, kRed, 32);
        vTaskDelay(pdMS_TO_TICKS(3000));
        PrintStat();
    }
}