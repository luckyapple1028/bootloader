
#ifndef __irq_h
#define __irq_h

#define GPH2CON		        (*(volatile unsigned int *)0xE0200C40)
#define EXT_INT_2_PEND		(*(volatile unsigned int *)0xE0200F48)
#define EXT_INT_2_CON		(*(volatile unsigned int *)0xE0200E08)
#define EXT_INT_2_MASK		(*(volatile unsigned int *)0xE0200F08)
#define INTP                (*(volatile unsigned int *)0xE2800030)


#define VIC0INTENABLE		(*(volatile unsigned int *)0xF2000010)
#define VIC0INTSELECT		(*(volatile unsigned int *)0xF200000C)
#define VIC0VECTADDR16		(*(volatile unsigned int *)0xF2000140)
#define VIC0VECTADDR29		(*(volatile unsigned int *)0xF2000174)

  
#define VIC0ADDRESS		    (*(volatile unsigned int *)0xF2000F00)

#define buzzer_is_open()    (GPD0CON & 0x02)   


void irq_init(void);

void do_eint16_31_irq(void);

#endif
