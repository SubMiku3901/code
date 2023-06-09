#include "gpio.h"
/*
    功能：GPIO初始化的函数
    参数：
        @ gpios : 初始化的那个组的gpio引脚 GPIOx(x=A-F)
        @ gpioInit : gpio初始化的结构体
*/

void hal_gpio_init(gpio_t *gpios, gpio_init_t *gpioInit)
{
    int pinNum;
    for (pinNum = 0; pinNum < 16; pinNum++)
    {
        // 如果为真，则pinNum对应的引脚的编号
        if (gpioInit->pins & (0x1 << pinNum))
        {
            gpios->MODER &= ~(0x3 << (pinNum * 2));
            gpios->MODER |= (gpioInit->mode << (pinNum * 2));

            gpios->OTYPER &= ~(0x1 << pinNum);
            gpios->OTYPER |= (gpioInit->type << pinNum);

            gpios->OSPEEDR &= ~(0x3 << (pinNum * 2));
            gpios->OSPEEDR |= (gpioInit->speed << (pinNum * 2));

            gpios->PUPDR &= ~(0x3 << (pinNum * 2));
            gpios->PUPDR |= (gpioInit->pupd << (pinNum * 2));
        }
    }
}

/*
    功能：GPIO引脚输出的函数
    参数：
        @ gpios : 初始化的那个组的gpio引脚 GPIOx(x=A-F)
        @ pin:那个引脚
        @ statu:引脚的状态
*/
void hal_gpio_write(gpio_t *gpios, unsigned int pins, gpio_statu_t statu)
{
    if (statu != GPIO_RESET)
    {
        gpios->ODR |= pins;
    }
    else
    {
        gpios->ODR &= ~(pins);
    }
}

/*
    功能：GPIO引脚输入的函数
    参数：
        @ gpios : 初始化的那个组的gpio引脚 GPIOx(x=A-F)
        @ pin:那个引脚
    返回值：
        @ statu:引脚的状态
*/
gpio_statu_t hal_gpio_read(gpio_t *gpios, unsigned int pins)
{
    if (gpios->IDR & pins)
    {
        return GPIO_SET;
    }
    else
    {
        return GPIO_RESET;
    }
}
