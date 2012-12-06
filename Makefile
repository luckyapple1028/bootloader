CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

CFLAGS 		:= -Wall -O2
CPPFLAGS   	:= -nostdinc -nostdlib -fno-builtin

objs := start.o mem_setup.o main.o clock.o nand.o uart.o tag.o

boot.bin: $(objs)	
	${LD} -Ttext 0x20000010 -o boot.elf $^	
	${OBJCOPY} -O binary -S boot.elf $@	
	${OBJDUMP} -D -m arm boot.elf > boot.dis	
	../mktiny210spl.exe boot.bin boot-sd.bin

%.o:%.c	
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S	
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:	
	rm -f *.o *.bin *.elf *.dis
