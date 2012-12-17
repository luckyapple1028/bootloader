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
	/* ��ʼ������0 */
	uart_init();
	printf("UART0 initialized\n\r");
	/* ��ʼ��RTC */
	rtc_init();
	printf("RTC initialized\n\r");
	/* �жϳ�ʼ�� */
	irq_init();
		
	buzzer_open();

	/* ��ʼ��NAND������ */
	printf("Init Nand Flash controller\n\r");
	nand_init();

	/* ����ʱ�����ж�����ָ���������Linux�ں� */
	printf("Hit any key to stop autoboot:  ");
	if(wait_command(4) != 0){				
		get_command();			
	}else{
		boot_kernel();
	}
	
	return 0;
}





