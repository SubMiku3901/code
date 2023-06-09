#include "../include/uart4.h"

void hal_uart4_init(void) {
  // RCC 章节
  // 1. 使能 GPIOB 组控制器 `RCC_MP_AHB4ENSETR[1]`
  // 2. 使能 GPIOG 组控制器 `RCC_MP_AHB4ENSETR[6]`
  RCC_MP_AHB4ENSETR |= (0x1 << 1) | (0x1 << 6);
  // 3. 使能 UART4 组控制器 `RCC_MP_APB1ENSETR[16]`
  RCC_MP_APB1ENSETR |= (0x1 << 16);
  
  // GPIO 章节
  // 复用功能模式
  // 复用功能位串口接收/发送

  // PG11 寄存器初始化
  gpio_init_t gpioInit = {
    .pins = GPIO_PIN_11,
    .mode = GPIO_AF,
  };
  hal_gpio_init(GPIOG, &gpioInit);
  // 结构体没有定义 AFR 寄存器，需要单独设置
  (*(volatile unsigned int *)0x50003024) |= (0x8 << 12);

  // PB2 寄存器初始化
  gpioInit.pins = GPIO_PIN_2;
  hal_gpio_init(GPIOB, &gpioInit);
  (*(volatile unsigned int *)0x50008020) |= (0x8 << 8);

  // UART4 章节
  // USART_CR1 寄存器 0x40010000
  // 1. 通过 M1 和 M2 设置起始位和位宽度
  // 设置为 8N1，USART_CR1[28] = 0, USART_CR1[12] = 0
  (*(volatile unsigned int*)0x40010000) &= ~(0x1 << 28);
  (*(volatile unsigned int*)0x40010000) &= ~(0x1 << 12);
  // 2. 通过 OVER8 设置波特率
  // 设置为 16，USART_CR1[15] = 0
  (*(volatile unsigned int*)0x40010000) &= ~(0x1 << 15);
  // 3. 通过 PCE 设置校验位
  // 设置为 0，USART_CR1[10] = 0
  (*(volatile unsigned int*)0x40010000) &= ~(0x1 << 10);
  // 4. 通过 TE 和 RE 使能发送和接收
  // 设置为 1，USART_CR1[3] = 1, USART_CR1[2] = 1
  (*(volatile unsigned int*)0x40010000) |= (0x1 << 3);
  (*(volatile unsigned int*)0x40010000) |= (0x1 << 2);
  // 5. 通过 UE 使能串口
  // 设置为 1，USART_CR1[0] = 1
  (*(volatile unsigned int*)0x40010000) |= (0x1 << 0);

  // USART_CR2 寄存器 0x40010004
  // 1. 通过 STOP 设置停止位
  // 设置为 0，USART_CR2[13:12] = 0b00
  (*(volatile unsigned int*)0x40010004) &= ~(0x3 << 12);

  // USRT_BRR 寄存器 0x4001000C
  // 1. 通过 DIV_Fraction 和 DIV_Mantissa 设置波特率
  // 波特率 = 115200
  // BRR = 64000000 / 115200 = 555d = 0x22B
  (*(volatile unsigned int*)0x4001000C) &= ~(0xFFFF << 0);
  (*(volatile unsigned int*)0x4001000C) |= 0x22B;
}

// 发送一个字符
void hal_put_char(const char ch) {
  // 判断发送数据寄存器是否为空 TEX位 ISR[7]
  // 读0: 发送寄存器满，需要等待
  // 读1: 发送寄存器空，可以发送下一个字节
  while(!(USART4->ISR & (0x1 << 7)));
  // 发送数据寄存器 = ch
  USART4->TDR = ch;
  // 判断发送数据是否完成 TC位 ISR[6]，等待发送完成
  // 读0: 发送未完成
  // 读1: 发送完成
  while(!(USART4->ISR & (0x1 << 6)));
}

// 发送一个字符串
void hal_put_string(const char *str) {
  // 判断是否为 0
  // 一个一个字符发送
}

// 接收一个字符
char hal_get_char(void) {
  // 定义一个变量，用来接收数据
  char ch;
  // 判断接收数据寄存器是否有数据可读 RXNE位 ISR[5]
  // 读0: 接收寄存器空，没有数据可读
  // 读1: 接收寄存器有数据，可以读取
  while(!(USART4->ISR & (0x1 << 5)));
  // 读取接收数据寄存器
  // ch = 接收数据寄存器
  // RDR 寄存器地址 0x40010024
  ch = (*(volatile unsigned int*)0x40010024);
  return ch;
}

// 接收一个字符串
char* hal_get_string(void) {
  // for 循环
  // 判断键盘回车键是否按下 '\r'
  return "";
}

