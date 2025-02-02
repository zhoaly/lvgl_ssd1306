#include "LVGL_init_my.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "UART_init_my.h"
#include "lvgl_demo_ui.h"

#include "lvgl.h"
#include "LCD_init.h"

extern esp_lcd_panel_handle_t panel_handle;
extern esp_lcd_panel_io_handle_t io_handle;

extern QueueHandle_t uart_report_cmd_quere;

extern lv_obj_t *btn[5];
TaskHandle_t lvgl_task_Handle;

static const char *TAG = "LVGL_init_my";


static void lvgl_task(){
    uart_report_type uart_output_cmd;
    while (1)
    {
        xQueueReceive(uart_report_cmd_quere,(void *)&uart_output_cmd,(TickType_t)portMAX_DELAY);
        ESP_LOGI(TAG,"reprot is :%d,time is: %ld ",(int)uart_output_cmd.reprot,uart_output_cmd.currenttime-uart_output_cmd.startime);

        static int i= 0;
        i = (int)uart_output_cmd.reprot-'0';
        lv_obj_scroll_to_view(btn[i],LV_ANIM_ON);
        // static int i=0;
        // lv_obj_scroll_to_view(btn[i],LV_ANIM_ON);
        // i++;
        // if (i>=5) i=0;
    }
}


lv_disp_t* LVGL_Init_my(){

    ESP_LOGI(TAG, "Initialize LVGL");
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_port_init(&lvgl_cfg);

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES,
        .double_buffer = true,
        .hres = EXAMPLE_LCD_H_RES,
        .vres = EXAMPLE_LCD_V_RES,
        .monochrome = true,
        .rotation = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false,
        }
    };
    lv_disp_t *disp = NULL;
    disp = lvgl_port_add_disp(&disp_cfg);

    /* Rotation of the screen */
    lv_disp_set_rotation(disp, LV_DISP_ROT_180);

    xTaskCreatePinnedToCore(lvgl_task,"lvgl_task",2048,NULL,2,&lvgl_task_Handle,0);
    return disp;
}