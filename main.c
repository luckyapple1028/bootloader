#include "tiny210.h"


void delay(int num)
{
	int i = 1;

	while(num--){
		for(i = 1; i < 0x8000000; i++);
		puts(" ");
	};
}

int mymain(void)
{
	void (*theKernel)(int zero, int arch, unsigned int params);

	/* ��ʼ������0 */
	uart_init();
	puts("UART0 initialized\n\r");

	buzzer_open();
	delay(1000);
	buzzer_stop();

	/* ��ʼ��NAND������ */
	puts("Init Nand Flash controller\n\r");
	nand_init();

	/* ��Linux�ں˶�ȡ��DDR�� */
	puts("Read kernel from Nand Flash\n\r");
	nand_read(0x21000000, 0x400000, 0x800000);
	/* ������������ */
	
	puts("Set boot params\n\r");
	init_taglist();
	/* ��תִ��*/
	puts("Boot kernel...\n\r");
	theKernel = (void (*)(int, int, unsigned int))0x21000040;/* Linux �ں���ڵ�ַ */
	theKernel(0, 3466, 0x22000000); /* ��һ��������0���ڶ��������ǻ����룬����������������������ַ */

	return 0;
}





