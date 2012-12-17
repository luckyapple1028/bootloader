#include "tiny210.h"
#include "stdio.h"

void delay(int num)
{
	int i = 1;

	while(num--){
		for(i = 1; i < 0x8000000; i++);
	};
}

int mymain(void)
{
	/* 初始化串口0 */
	uart_init();
	printf("UART0 initialized\n\r");
	/* 初始化RTC */
	rtc_init();
	printf("RTC initialized\n\r");
	/* 中断初始化 */
	irq_init();
		
	buzzer_open();

	/* 初始化NAND控制器 */
	printf("Init Nand Flash controller\n\r");
	nand_init();

	/* 倒计时，有中断则处理指令，否则启动Linux内核 */
	printf("Hit any key to stop autoboot:  ");
	if(wait_command(4) != 0){				
		get_command();			
	}else{
		boot_kernel();
	}
	
	return 0;
}





