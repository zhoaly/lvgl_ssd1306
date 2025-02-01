#ifndef UART_INIT_MY
#define UART_INIT_MY

#include "driver/uart.h"

#define uart_num UART_NUM_0
#define uart_buffer_size (1024 * 2)
#define uart_baud_rate 115200
void uart_init_my();
#endif