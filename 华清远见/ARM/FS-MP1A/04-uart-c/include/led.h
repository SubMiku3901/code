#ifndef __LED_H__
#define __LED_H__
#include "gpio.h"

// 2. led灯相关的函数的声明

// LED灯的初始化的函数
void hal_led_init(void);

// led灯闪烁的函数
void hal_led_flash(void);

#endif
