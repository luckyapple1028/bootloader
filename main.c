#include "tiny210.h"


void delay(int num)
{
	int i = 1;

	while(num--){
		for(i = 1; i < 0x8000000; i++);
	};
}

int mymain(void)
{
	void (*theKernel)(int zero, int arch, unsigned int params);

	/* 初始化串口0 */
	uart_init();
	puts("UART0 initialized\n\r");
	/* 初始化RTC */
	rtc_init();
	puts("RTC initialized\n\r");
	/* 中断初始化 */
	irq_init();
	puts("IRQ initialized\n\r");
	
	buzzer_open();

	/* 初始化NAND控制器 */
	puts("Init Nand Flash controller\n\r");
	nand_init();

	while(1);

	/* 将Linux内核读取到DDR中 */
	puts("Read kernel from Nand Flash\n\r");
	nand_read(0x21000000, 0x400000, 0x800000);
	/* 设置启动参数 */
	
	puts("Set boot params\n\r");
	init_taglist();
	/* 跳转执行*/
	puts("Boot kernel...\n\r");

	
	theKernel = (void (*)(int, int, unsigned int))0x21000040;/* Linux 内核入口地址 */
	theKernel(0, 3466, 0x22000000); /* 第一个参数是0，第二个参数是机器码，第三个参数是启动参数地址 */

	return 0;
}





