/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "esp_lcd_panel_vendor.h"


#include "LCD_init.h"
#include "LVGL_init_my.h"
#include "lvgl_demo_ui.h"


static const char *TAG = "example";




void app_main(void)
{
    LCD_Init();

    lv_disp_t* disp=LVGL_Init_my();



    ESP_LOGI(TAG, "Display LVGL Scroll Text");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (lvgl_port_lock(0)) {
        example_lvgl_demo_ui(disp);
        // Release the mutex
        lvgl_port_unlock();
    }
}
