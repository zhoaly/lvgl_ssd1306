#include "UART_init_my.h"


static const char *TAG = "uart_init_my";


uint8_t data[128]={0};

QueueHandle_t uart_queue;
//const uart_port_t uart_num = UART_NUM_0;


void uart_init_my(){

    uart_config_t uart_config = {
    .baud_rate = uart_baud_rate,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE,\
                                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));


    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, \
                                        uart_buffer_size, 10, &uart_queue, 0));


}