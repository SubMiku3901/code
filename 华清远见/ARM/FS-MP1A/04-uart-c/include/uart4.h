#ifndef __UART4_H__
#define __UART4_H__

#include "../common/include/stm32mp1xx_uart.h"
#include "../include/gpio.h"

// 串口初始化函数
void hal_uart4_init(void);

// 发送一个字符
void hal_put_char(const char ch);

// 发送一个字符串
void hal_put_string(const char *str);

// 接收一个字符
char hal_get_char(void);

// 接收一个字符串
char* hal_get_string(void);

#endif
