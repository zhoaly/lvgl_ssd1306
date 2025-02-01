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


static const char *TAG = "example";





void app_main(void)
{
    LCD_Init();

    lv_disp_t* disp=LVGL_Init_my();

    lvgl_port_lock(0);
    example_lvgl_demo_ui(disp);
    lvgl_port_unlock();

    /////////////////////////////////////////
    const uart_port_t uart_num = UART_NUM_0;
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
};
// Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, \
                                        uart_buffer_size, 10, &uart_queue, 0));

                                            
    char* test_str = "This is a test string.\n";

    uint8_t data[128]={0};
    int length = 0;
    

    while (1)
    {
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
        uart_read_bytes(uart_num, data, length, 100);
        uart_write_bytes(uart_num, (const char*)data, length);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}
