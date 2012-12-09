
#define	NFCONF  (*(volatile unsigned int *)0xB0E00000) 
#define	NFCONT  (*(volatile unsigned int *)0xB0E00004) 	
#define	NFCMMD  (*(volatile unsigned char *)0xB0E00008) 
#define	NFADDR  (*(volatile unsigned char *)0xB0E0000C)
#define	NFDATA  (*(volatile unsigned char *)0xB0E00010)
#define	NFSTAT  (*(volatile unsigned int *)0xB0E00028)

#define	MP0_3CON  (*(volatile unsigned int *)0xE0200320)

#define PAGE_SIZE	2048


void nand_init(void);

void nand_read(int sdram_addr, int nand_addr, int size);

