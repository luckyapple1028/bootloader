
extern void buzzer_set_freq(unsigned long freq);

extern void buzzer_stop(void);

extern void buzzer_open(void);

extern void nand_init(void);

extern void nand_read(int sdram_addr, int nand_addr, int size);

extern void uart_init(void);

extern char uart_getchar(void);

extern void uart_putchar(char c);

extern void puts(char *str);

extern void init_taglist(void);

extern void irq_init(void);

extern void eint16_31_irq(void);

extern void rtc_init(void);

extern void eint_rtc_irq(void);


