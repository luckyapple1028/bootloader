#include "irq.h"
#include "tiny210.h"

#define RTCCON     (*(volatile unsigned int *)0xE2800040)
#define TICCNT     (*(volatile unsigned int *)0xE2800044)

void rtc_init(void)
{
	RTCCON |= (1 << 8)|(1 << 0);

	TICCNT = 32768-1;       //32768/32768 = 1s;	

	/* RTC irq init */
	/* �����жϿ�����ʹ���ж�(RTC) */
	VIC0INTENABLE |= (1<<29);
	VIC0INTSELECT &= ~(1<<29);	

	/* �����ж����� */
	VIC0VECTADDR29 = (int)eint_rtc_irq;	
}
