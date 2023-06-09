#ifndef __GPIO_H__
#define __GPIO_H__

// 1.封装GPIOE，GPIOF,RCC外设对应的寄存器
#define RCC_MP_AHB4ENSETR *(volatile unsigned int *)0x50000A28
#define RCC_MP_APB1ENSETR *(volatile unsigned int *)0x50000A00

typedef struct
{
    volatile unsigned int MODER;
    volatile unsigned int OTYPER;
    volatile unsigned int OSPEEDR;
    volatile unsigned int PUPDR;
    volatile unsigned int IDR;
    volatile unsigned int ODR;
} gpio_t;

#define GPIOA ((gpio_t *)0x50002000)
#define GPIOB ((gpio_t *)0x50003000)
#define GPIOC ((gpio_t *)0x50004000)
#define GPIOD ((gpio_t *)0x50005000)
#define GPIOE ((gpio_t *)0x50006000)
#define GPIOF ((gpio_t *)0x50007000)
#define GPIOG ((gpio_t *)0x50008000)

// 通过判断16位的数，哪位为1，就可以得到引脚对应的编号
#define GPIO_PIN_0 0x0001U
#define GPIO_PIN_1 0x0002U
#define GPIO_PIN_2 0x0004U
#define GPIO_PIN_3 0x0008U
#define GPIO_PIN_4 0x0010U
#define GPIO_PIN_5 0x0020U
#define GPIO_PIN_6 0x0040U
#define GPIO_PIN_7 0x0080U
#define GPIO_PIN_8 0x0100U
#define GPIO_PIN_9 0x0200U
#define GPIO_PIN_10 0x0400U
#define GPIO_PIN_11 0x0800U
#define GPIO_PIN_12 0x1000U
#define GPIO_PIN_13 0x2000U
#define GPIO_PIN_14 0x4000U
#define GPIO_PIN_15 0x8000U

typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT,
    GPIO_AF,
    GPIO_ANALOG
} gpio_moder_t;

typedef enum
{
    GPIO_PP = 0,
    GPIO_OD
} gpio_otyper_t;

typedef enum
{
    GPIO_LOW_LEVEL = 0,
    GPIO_MEDIUM_LEVEL,
    GPIO_HIGH_LEVEL,
    GPIO_VERY_HIGH_LEVEL
} gpio_ospeedr_t;

typedef enum
{
    GPIO_NOPUPD = 0,
    GPIO_PU,
    GPIO_PD,
} gpio_pupdr_t;

typedef enum
{
    GPIO_RESET = 0,
    GPIO_SET,
} gpio_statu_t;

// gpio初始化的结构体
typedef struct
{
    unsigned int pins;    // 引脚的编号
    gpio_moder_t mode;    // GPIO引脚的模式
    gpio_otyper_t type;   // gpio引脚的类型
    gpio_ospeedr_t speed; // GPIO引脚的输出的速度
    gpio_pupdr_t pupd;    // gpio引脚上拉下拉电阻的选择
} gpio_init_t;

/*
    功能：GPIO初始化的函数
    参数：
        @ gpios : 初始化的那个组的gpio引脚 GPIOx(x=A-F)
        @ gpioInit : gpio初始化的结构体
*/

void hal_gpio_init(gpio_t *gpios, gpio_init_t *gpioInit);

/*
    功能：GPIO引脚输出的函数
    参数：
        @ gpios : 初始化的那个组的gpio引脚 GPIOx(x=A-F)
        @ pin:那个引脚
        @ statu:引脚的状态
*/
void hal_gpio_write(gpio_t *gpios, unsigned int pins, gpio_statu_t statu);

/*
    功能：GPIO引脚输入的函数
    参数：
        @ gpios : 初始化的那个组的gpio引脚 GPIOx(x=A-F)
        @ pin:那个引脚
    返回值：
        @ statu:引脚的状态
*/
gpio_statu_t hal_gpio_read(gpio_t *gpios, unsigned int pins);

#endif
