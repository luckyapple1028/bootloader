
#ifndef __buzzer_h
#define __buzzer_h


#define GPD0CON		 (*(volatile unsigned int *)0xE02000A0)
#define GPD0DAT		 (*(volatile unsigned int *)0xE02000A4)

#define TCON		 (*(volatile unsigned long *)0xE2500008)     
#define TCNTB0       (*(volatile unsigned long *)0xE250000C)
#define TCMPB0       (*(volatile unsigned long *)0xE2500010)
#define TCFG0        (*(volatile unsigned long *)0xE2500000)
#define TCFG1        (*(volatile unsigned long *)0xE2500004)


void buzzer_set_freq(unsigned long freq);

void buzzer_stop(void);

void buzzer_open(void);

#endif