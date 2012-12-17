
#ifndef __uart_h
#define __uart_h


#define GPA0CON  	(*(volatile unsigned int *)0xE0200000) 

#define ULCON0  	(*(volatile unsigned int *)0xE2900000) 
#define UCON0  		(*(volatile unsigned int *)0xE2900004) 
#define UTRSTAT0  	(*(volatile unsigned int *)0xE2900010)
#define UTXH0  		(*(volatile unsigned char *)0xE2900020) 
#define URXH0  		(*(volatile unsigned char *)0xE2900024) 
#define UBRDIV0 	(*(volatile unsigned int *)0xE2900028) 
#define UDIVSLOT0  	(*(volatile unsigned int *)0xE290002C)


void uart_init(void);

char uart_getchar(void);

void uart_putchar(char c);

int uart_getchar_timeout(char *c, unsigned int time);


#endif
