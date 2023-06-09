#include "led.h"
void delay_ms(unsigned int ms);
// LED灯的初始化的函数
void hal_led_init(void)
{
    RCC_MP_AHB4ENSETR |= (0x1 << 4) | (0x1 << 5);
    gpio_init_t gpioInit = {
        .pins = GPIO_PIN_10,
        .mode = GPIO_OUTPUT,
        .type = GPIO_PP,
        .speed = GPIO_LOW_LEVEL,
        .pupd = GPIO_NOPUPD,
    };

    hal_gpio_init(GPIOE, &gpioInit);

    gpioInit.pins = GPIO_PIN_8;
    hal_gpio_init(GPIOE, &gpioInit);

    gpioInit.pins = GPIO_PIN_10;
    hal_gpio_init(GPIOF, &gpioInit);
}

// led灯闪烁的函数
void hal_led_flash(void)
{
    hal_gpio_write(GPIOE, GPIO_PIN_10 | GPIO_PIN_8, GPIO_SET);
    hal_gpio_write(GPIOF, GPIO_PIN_10, GPIO_SET);
    delay_ms(500);
    hal_gpio_write(GPIOE, GPIO_PIN_10 | GPIO_PIN_8, GPIO_RESET);
    hal_gpio_write(GPIOF, GPIO_PIN_10, GPIO_RESET);
    delay_ms(500);
}
