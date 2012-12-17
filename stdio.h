
#ifndef __stdio_h
#define __stdio_h


int putchar(int c);

int getchar(void);

int puts(const char * s);

char * gets(char * s);

int printf(const char * format, ...);

int strcmp(const char * s1, const char * s2);

void *memcpy(void *dest, const void *src, unsigned int count);


#endif
