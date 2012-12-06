#define GPA0CON  	(*(volatile unsigned int *)0xE0200000) 

#define ULCON0  	(*(volatile unsigned int *)0xE2900000) 
#define UCON0  		(*(volatile unsigned int *)0xE2900004) 
#define UTRSTAT0  	(*(volatile unsigned int *)0xE2900010)
#define UTXH0  		(*(volatile unsigned char *)0xE2900020) 
#define URXH0  		(*(volatile unsigned char *)0xE2900024) 
#define UBRDIV0 	(*(volatile unsigned int *)0xE2900028) 
#define UDIVSLOT0  	(*(volatile unsigned int *)0xE290002C)

void uart_init(void)
{

	// 66Mhz / (115200*16) - 1 = 0x23
	// 66Mhz / (19200*16) - 1 = 0xD5
	//DIV_VAL = UBRDIVn + (num of 1's in UDIVSLOTn)/16 
  	//DIV_VAL = (PCLK / (bps x 16))-1
	GPA0CON &= ~(0xFF<<0);
	GPA0CON |= 0x22;   /*���ö˿�ΪUART_0_TXD��UART_0_RXDģʽ*/

	// set UART SFRs
	ULCON0 = 0x3;      /* ����λ-8bit; ֹͣλ-1bit */
	UCON0 = 0x245;     /* �жϻ���ѯ���䷽ʽ */
	UBRDIV0 = 0x23;    /* PCLK 66Mhz / (115200*16) - 1 = 0x23  */
	UDIVSLOT0 = 0x808;

	return;
}

char uart_getchar(void)
{
	char c;
	// polling receive status: if buffer is full
	//while ((UTRSTAT0 & (1<<0)) == 0)
	while (!(UTRSTAT0 & (1<<0)))
		;

	c = URXH0;

	return c;
}

void uart_putchar(char c)
{
	// polling transmit status: if buffer is empty
	//while ((UTRSTAT0 & (1<<2)) == 0)
	while (!(UTRSTAT0 & (1<<2)))
		;

	UTXH0 = c;

	return;
}

void puts(char *str)
{
	int i = 0;
	while (str[i])
	{
		uart_putchar(str[i]);
		i++;
	}
}


