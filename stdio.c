
#include "stdio.h"
#include "uart.h"


int putchar(int c)
{
	if (c == '\n')
		uart_putchar('\r');
	
	if (c == '\b')
	{
		uart_putchar('\b');
		uart_putchar(' ');	
	}
			
	uart_putchar((char)c);
	
	return c;	
}

int getchar(void)
{
	int c;
	
	c = (int)uart_getchar();

	if (c == '\r')
		return '\n';
	
	return c;
}

int puts(const char * s)
{
	while (*s)
		putchar(*s++);
		
	putchar('\n');

	return 0;
}

char * gets(char * s)
{
	char * p = s;
	
	while ((*p = getchar()) != '\n')
	{
		if (*p != '\b')
			putchar(*p++);
		else	
			if (p > s)
				putchar(*p--);	
	}
	
	*p = '\0';
	putchar('\n');
		
	return s;
}


int strcmp(const char * s1, const char * s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return 0;	
		s1++;
		s2++;				
	}
	
	return *s1 - *s2;
}

void *memcpy(void *dest, const void *src, unsigned int count)
{
	char *tmp = dest;
	const char *s = src;
	while (count--)
		*tmp++ = *s++ ;
	return dest;
}

