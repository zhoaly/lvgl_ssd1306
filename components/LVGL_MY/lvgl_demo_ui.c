#include "lvgl.h"

void example_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    /*------------------------------------------------------------------------------
     * 创建容器面板：该面板用于承载多个页面（例如：功能页面），
     * 尺寸设置为OLED的实际尺寸：128x64
     *------------------------------------------------------------------------------*/
    lv_obj_t * panel = lv_obj_create(scr);
    lv_obj_set_size(panel, 128, 64);
    // 屏幕较小，所以将面板居中显示
    lv_obj_align(panel, LV_ALIGN_CENTER, 0, 0);

    /*------------------------------------------------------------------------------
     * 样式设置：
     * 对于黑白OLED屏幕，设置背景色为白色（代表熄灭），
     * 文字及边框颜色设置为黑色（代表亮起）
     *------------------------------------------------------------------------------*/
    static lv_style_t style_panel;
    lv_style_init(&style_panel);
    lv_style_set_bg_color(&style_panel, lv_color_white());
    lv_style_set_text_color(&style_panel, lv_color_black());
    // 设置边框宽度为1像素，并指定边框颜色
    lv_style_set_border_width(&style_panel, 1);
    lv_style_set_border_color(&style_panel, lv_color_black());
    lv_style_set_radius(&style_panel,5); //设置圆角
    lv_style_set_pad_column(&style_panel,10);//设置间距

    // 将样式应用到面板上
    lv_obj_add_style(panel, &style_panel, 0);

    /*------------------------------------------------------------------------------
     * 配置面板的滚动属性与布局：
     * 1. 开启水平滚动捕捉至中心
     * 2. 使用 Flex 布局，设置为行方向排列（水平排列子控件）
     * 3. 关闭滚动条显示
     * 4. 使部件居中
     *------------------------------------------------------------------------------*/
    lv_obj_set_scroll_snap_x(panel, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);

    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_flex_align(panel,LV_FLEX_ALIGN_CENTER,LV_FLEX_ALIGN_CENTER,LV_FLEX_ALIGN_CENTER);
    //lv_obj_set_scroll_loop(panel, true);

    /*------------------------------------------------------------------------------
     * 向面板中添加多个页面：
     * 由于OLED尺寸较小，这里创建3个页面，每个页面均使用一个按钮模拟，
     * 按钮尺寸设置为与屏幕相同，保证页面内容全屏显示
     *------------------------------------------------------------------------------*/
    for(uint32_t i = 0; i < 3; i++) {
        // 创建一个按钮作为单个页面的容器
        lv_obj_t * btn = lv_btn_create(panel);
        lv_obj_set_size(btn, 100, 40);
        // 为按钮添加同一套样式（背景、边框、文字颜色等）
        lv_obj_add_style(btn, &style_panel, 0);

        // 在按钮上创建标签，并显示当前页面编号
        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Page %ld", i + 1);
        // 使标签在按钮中居中显示
        lv_obj_center(label);
}
}
