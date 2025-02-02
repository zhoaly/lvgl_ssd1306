#include "lvgl.h"
#include "esp_log.h"



// 全局变量声明
lv_timer_t *timer;
lv_obj_t *scr;
lv_obj_t *panel;
lv_style_t style_panel;
lv_obj_t *btn[5];
lv_obj_t *label[5];



static const char *TAG = "LVGL_UI";

void  my_time_cb(lv_timer_t * parm){
    uint32_t * user_data = timer->user_data;
    //ESP_LOGI(TAG,"timer call back");
    // static int i=0;
    // lv_obj_scroll_to_view(btn[i],LV_ANIM_ON);
    // i++;
    // if (i>=5) i=0;
    //lv_obj_scroll_to_view(btn[0],LV_ANIM_ON);
    //ESP_LOGI(TAG,"obj x pos is:%d",lv_obj_get_scroll_x(panel));
    //lv_obj_scroll_by();
}


void example_lvgl_demo_ui(lv_disp_t *disp)
{
    static uint32_t user_data = 10;
    lv_timer_enable(true);
    timer = lv_timer_create(my_time_cb, 1000, &user_data); // 创建定时器

    scr = lv_disp_get_scr_act(disp); // 获取当前屏幕

    /* 创建容器面板 */
    panel = lv_obj_create(scr);
    lv_obj_set_size(panel, 128, 64);
    lv_obj_align(panel, LV_ALIGN_CENTER, 0, 0);

    /* 样式设置 */
    lv_style_init(&style_panel);
    lv_style_set_bg_color(&style_panel, lv_color_white());
    lv_style_set_text_color(&style_panel, lv_color_black());
    lv_style_set_border_width(&style_panel, 1);
    lv_style_set_border_color(&style_panel, lv_color_black());
    lv_style_set_radius(&style_panel, 3);
    lv_style_set_pad_column(&style_panel, 5);

    lv_obj_add_style(panel, &style_panel, 0);

    /* 配置面板的滚动属性与布局 */
    lv_obj_set_scroll_snap_x(panel, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    /* 向面板中添加多个页面 */
    for (uint32_t i = 0; i < 5; i++) {
        btn[i] = lv_btn_create(panel);
        lv_obj_set_size(btn[i], 100, 40);
        lv_obj_add_style(btn[i], &style_panel, 0);

        label[i] = lv_label_create(btn[i]);
        lv_label_set_text_fmt(label[i], "Page %ld", i + 1);
        lv_obj_center(label[i]);
    }
}
