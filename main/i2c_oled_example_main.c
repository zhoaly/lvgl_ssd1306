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
extern QueueHandle_t uart_report_cmd_quere;//uart输入队列句柄

void app_main(void)
{
    LCD_Init();
    uart_init_my();
    lv_disp_t* disp=LVGL_Init_my();





    lvgl_port_lock(0);
    example_lvgl_demo_ui(disp);
    lvgl_port_unlock();


    uart_report_type  pvBuffer[10]={0};
    while (1)
    {
        xQueueReceive(uart_report_cmd_quere,(void *)&pvBuffer, (TickType_t)portMAX_DELAY);
        ESP_LOGI(TAG,"reprot is :%c,time is: %ld ",pvBuffer[0].reprot,pvBuffer[0].currenttime-pvBuffer[0].startime);
    }
    

    
}
