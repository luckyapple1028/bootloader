#ifndef __command_h
#define __command_h

int wait_command(int sec);

int get_command(void);

void boot_kernel(void);

void format_nand(void);

void down_kernel(void);

#endif
