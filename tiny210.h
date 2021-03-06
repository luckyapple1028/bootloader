
extern void buzzer_set_freq(unsigned long freq);

extern void buzzer_stop(void);

extern void buzzer_open(void);

extern void nand_init(void);

extern void nand_read(int sdram_addr, int nand_addr, int size);

extern void uart_init(void);

extern char uart_getchar(void);

extern void uart_putchar(char c);

extern void init_taglist(void);

extern void irq_init(void);

extern void eint16_31_irq(void);

extern void rtc_init(void);

extern void eint_rtc_irq(void);

extern int wait_command(int sec);

extern int get_command(void);

extern void delay(int num);

extern void boot_kernel(void);

extern int ymodem_recv(char *addr);

extern int uart_getchar_timeout(char *c, unsigned int time);



