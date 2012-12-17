#include "xmodem.h"
#include "tiny210.h"
void xmodem_recv(char *addr)
{
	char c;
	int i;
	for (c = '9'; c > '0'; c--)
	{
		uart_putchar(c);
		delay(1);
	}
	
	uart_putchar(NAK);
	while (uart_getchar() != EOT)
	{
		uart_getchar(); 
		uart_getchar();
		for (i = 0; i < 128; i++)
			*addr++ = uart_getchar();
		uart_getchar();
		uart_putchar(ACK);
	}
	uart_putchar(ACK);
}

