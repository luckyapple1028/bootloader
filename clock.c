#define APLL_CON  	(*(volatile unsigned int *)0xe0100100) 
#define CLK_SRC0  	(*(volatile unsigned int *)0xe0100200) 
#define CLK_DIV0  	(*(volatile unsigned int *)0xe0100300) 
#define MPLL_CON  	(*(volatile unsigned int *)0xe0100108)  

void clock_init(void)
{
	// clock init
	APLL_CON = 0xa07d0301;   /* APLL P:3 M:125 S:1 FOUT 1000.0MHZ */
	CLK_SRC0 = 0x10001111;   /* —°‘Ò ±÷”‘¥ */
	CLK_DIV0 = 0x14131440;   /* ARMCLK=1000M HCLK_MSYS=200M PCLK_MSYS=100M HCLK_DSYS=166M PCLK_DSYS=83M HCLK_PSYS=133M PCLK_PSYS=66MHZ*/
	MPLL_CON = 0xa29b0c01;   /* MPLL P:12 M:667 S:1 FOUT 667.0MHZ */

	return;
}


