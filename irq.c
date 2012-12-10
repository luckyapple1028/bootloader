#include "tiny210.h"
#include "buzzer.h"


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


void do_eint16_31_irq(void)
{
	/* �����ж� */
	if(EXT_INT_2_PEND & 1){
		EXT_INT_2_PEND = 1;

		puts("k1 down\n\r");
	}
	VIC0ADDRESS = 0;
}

void do_eint_rtc_irq(void)
{
	if(INTP & 1){
		INTP = 1;
		if(buzzer_is_open())
			buzzer_stop();
		puts("RTC\n\r");
	}
	VIC0ADDRESS = 0;
}


void irq_init(void)
{
	/* ����GPH2_0Ϊ�ж����� */
	GPH2CON |= 0xf;    //1111: EXT_INT[16] 
	/* �����ж�Ϊ�½��ش��� */
	EXT_INT_2_CON &= ~(0xf);
	EXT_INT_2_CON |= 0x2;    //010 = Falling edge triggered
	/* ʹ���ж� */
	EXT_INT_2_MASK &= ~(1<<0);    
	
	/* �����жϿ�����ʹ���ж��(����) */
	VIC0INTENABLE |= (1<<16);
	VIC0INTSELECT &= ~(1<<16);
	/* �����жϿ�����ʹ���ж��(RTC) */
	VIC0INTENABLE |= (1<<29);
	VIC0INTSELECT &= ~(1<<29);	
	/* �����ж����� */
	VIC0VECTADDR16 = (int)eint16_31_irq;
	VIC0VECTADDR29 = (int)eint_rtc_irq;
}

