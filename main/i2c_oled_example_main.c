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
#include "driver/uart.h"

#include "LCD_init.h"
#include "LVGL_init_my.h"
#include "lvgl_demo_ui.h"
#include "UART_init_my.h"

static const char *TAG = "example";


extern uint8_t data[128];


void app_main(void)
{
    LCD_Init();
    uart_init_my();
    lv_disp_t* disp=LVGL_Init_my();

    lvgl_port_lock(0);
    example_lvgl_demo_ui(disp);
    lvgl_port_unlock();

    while (1)
    {   
        int length=0;
        
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));//读取缓冲区内长度
        uart_read_bytes(uart_num, data, length, 100);
        uart_write_bytes(uart_num, (const char*)data, length);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}
