CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump
LIBPATH = -lgcc -L /opt/tiny210/toolschain/4.5.1/lib/gcc/arm-none-linux-gnueabi/4.5.1/

CFLAGS 		:= -Wall -O2
CPPFLAGS   	:= -nostdinc -nostdlib -fno-builtin -static

objs := start.o mem_setup.o main.o clock.o nand.o uart.o tag.o buzzer.o irq.o common_irq.o rtc.o

boot.bin: $(objs)	
	${LD} -Tboot.lds -o boot.elf $^ $(LIBPATH)
	${OBJCOPY} -O binary -S boot.elf $@	
	${OBJDUMP} -D -m arm boot.elf > boot.dis	
	../mktiny210spl.exe boot.bin boot-tiny210.bin

%.o:%.c	
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S	
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:	
	rm -f *.o *.bin *.elf *.dis
