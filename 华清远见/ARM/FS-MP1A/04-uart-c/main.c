#include "include/uart4.h"

extern void printf(const char *fmt, ...);
void delay_ms(unsigned int ms)
{
	int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 1800; j++)
			;
}

int main()
{
  hal_uart4_init();
  while(1) {
    hal_put_char(hal_get_char() + 1);
  }
	return 0;
}

