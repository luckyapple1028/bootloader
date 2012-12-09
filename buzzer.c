#include "buzzer.h"
       
void buzzer_set_freq(unsigned long freq)
{
	unsigned long tcnt;

	/*prescaler value = 50*/
	TCFG0 &= ~(255<< 0);
	TCFG0 |= ((50-1)<< 0);
	

	/*mux = 16*/
	TCFG1 &= ~(0xf << 0);
	TCFG1 |= (0x4<< 0);

	tcnt = (66*1024*1024/50/16)/freq;

	TCNTB0 = tcnt;
	TCMPB0 = tcnt/2;

	TCON &= ~0x1f;
	TCON |= 0x0b;
	TCON &= ~2;
}


void buzzer_stop(void)
{
	GPD0CON &= ~(0xf << 0);
	GPD0CON |= (0x1 << 0);

	GPD0DAT &= ~(1 << 0);
}


void buzzer_open(void)
{
	GPD0CON &= ~(0xf << 0);
	GPD0CON |= (0x2 << 0);

	buzzer_set_freq(9000);
}


int raise (int signum)
{
	return 0;
}

