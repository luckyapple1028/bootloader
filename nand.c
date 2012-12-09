#include "nand.h"

void nand_init(void)
{
	// [15:12] TACLS = 1 -> (1) 	1/133Mhz = 7.5ns
	// [11:8] TWRPH0 = 1 -> (1+1)	7.5ns * 2 = 15ns
	// [7:4] TWRPH1 = 1 -> (1+1)	7.5ns * 2 = 15ns
	NFCONF |= 2<<12 | 2<<8 | 1<<4;    

	// AddrCycle  [1] 	1 = 5 address cycle 
	NFCONF |= 1<<1; 

	// MODE  [0]  NAND Flash controller operating mode 
	//	0 = Disable NAND Flash Controller 
	//	*1 = Enable NAND Flash Controller
	NFCONT |= 1<<0; 

	// Reg_nCE0  [1]  NAND Flash Memory nRCS[0] signal control 
	//	*0 = Force nRCS[0] to low (Enable chip select) 
	//	1 = Force nRCS[0] to High (Disable chip select) 
	NFCONT &= ~(1<<1);

	// GPIO functional mux setting
	// 		0010 = NF_xxx 
	MP0_3CON = 0x22222222;

	return;
}

void nand_select(void)
{
	NFCONT &= ~(1<<1);	
}

void nand_deselect(void)
{
	NFCONT |= (1<<1);	
}

void nand_read_page(int addr, char buf[])
{
	int i;
	char tmp;

	// write read_page cmd 00h
	NFCMMD = 0x00;
	
	// write 5 address
	NFADDR = (addr>>0) & 0xFF;
	NFADDR = (addr>>8) & 0x7;
	NFADDR = (addr>>11) & 0xFF;
	NFADDR = (addr>>19) & 0xFF;
	NFADDR = (addr>>27) & 0x1;

	// write read_page cmd 30h
	NFCMMD = 0x30;

	// wait for R/nB -> Ready	
	while ((NFSTAT & (1<<0)) == 0)
		;

	// read data 2048 bytes
	for (i = 0; i < PAGE_SIZE; i++)
		buf[i] = NFDATA;

	for (i = 0; i < 64; i++)
		tmp = NFDATA;

	return;
}

void nand_read(int sdram_addr, int nand_addr, int size)
{
	int pages = (size - 1)/PAGE_SIZE + 1;
	int i;
	
	nand_select();

	for (i = 0; i < pages; i++)
		nand_read_page(nand_addr + i*PAGE_SIZE, (char *)(sdram_addr + i*PAGE_SIZE));

	nand_deselect();
	
	return;
}

void clear_bss(void)
{
	extern int __bss_start, __bss_end;
	int *p = &__bss_start;
	
	for (; p < &__bss_end; p++)
		*p = 0;
}


