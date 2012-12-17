#include "stdio.h"
#include "uart.h"
#include "command.h"
#include "tiny210.h"
int time_delay = 0;

int wait_command(int sec)
{
	char c;
	time_delay = sec;

	while((uart_getchar_timeout(&c, 100) != 0) && (time_delay > 0));
	
	if(time_delay > 0){
		time_delay = 0;
		return -1;
	}else 
		return 0;
}

int get_command(void)
{
	char command[10];

	while(1){
		printf("\n\rPlease select a command(input number)\n\r");
		printf("1: boot linux kernel\n\r"); 
		printf("2: format nand flash\n\r"); 
		printf("3: download linux kernel\n\r"); 

		gets(command);

		if(strcmp(command, "1") == 0){		
			boot_kernel();
		}
		if(strcmp(command, "2") == 0){
			format_nand();
		}
		if(strcmp(command, "3") == 0){
			down_kernel();
		}
	}
	return 0;
}


void boot_kernel(void)
{
	void (*theKernel)(int zero, int arch, unsigned int params);

	/* ��Linux�ں˶�ȡ��DDR�� */
	printf("\n\rRead kernel from Nand Flash\n\r");
	nand_read(0x21000000, 0x400000, 0x800000);
	/* ������������ */

	printf("Set boot params\n\r");
	init_taglist();
	/* ��תִ��*/
	printf("Boot kernel...\n\r");

	theKernel = (void (*)(int, int, unsigned int))0x21000040;/* Linux �ں���ڵ�ַ */
	theKernel(0, 3466, 0x22000000); /* ��һ��������0���ڶ��������ǻ����룬����������������������ַ */
}

void format_nand(void)
{
	printf("format nand flash\n\r");
}

void down_kernel(void)
{
	void (*theKernel)(int zero, int arch, unsigned int params);

	printf("download linux kernel through ymodem\n\r");

	char *addr = (char *)0x21000000;

	ymodem_recv(addr);

	/* ������������ */
	printf("Set boot params\n\r");
	init_taglist();
	/* ��תִ��*/
	printf("Boot kernel...\n\r");

	theKernel = (void (*)(int, int, unsigned int))0x21000040;/* Linux �ں���ڵ�ַ */
	theKernel(0, 3466, 0x22000000); /* ��һ��������0���ڶ��������ǻ����룬����������������������ַ */
		
}

