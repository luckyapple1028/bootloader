#include "tiny210.h"
#include "buzzer.h"
#include "stdio.h"
#include "irq.h"

void do_eint16_31_irq(void)
{
	/* 处理中断 */
	if(EXT_INT_2_PEND & 1){
		EXT_INT_2_PEND = 1;

		puts("k1 down\n\r");
	}
	VIC0ADDRESS = 0;
}

extern int time_delay;

void do_eint_rtc_irq(void)
{
	if(INTP & 1){
		INTP = 1;    /* 清中断位 */
		if(buzzer_is_open())
			buzzer_stop();

		if(time_delay > 0){
			time_delay--;
			printf("\b%d", time_delay);
		}		
	}
	VIC0ADDRESS = 0;
}


void irq_init(void)
{
	/* 配置GPH2_0为中断引脚 */
	GPH2CON |= 0xf;    //1111: EXT_INT[16] 
	/* 设置中断为下降沿触发 */
	EXT_INT_2_CON &= ~(0xf);
	EXT_INT_2_CON |= 0x2;    //010 = Falling edge triggered
	/* 使能中断 */
	EXT_INT_2_MASK &= ~(1<<0);    
	
	/* 配置中断控制器使能中断(按键) */
	VIC0INTENABLE |= (1<<16);
	VIC0INTSELECT &= ~(1<<16);

	/* 设置中断向量 */
	VIC0VECTADDR16 = (int)eint16_31_irq;

}

