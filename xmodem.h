#ifndef __xmodem_h
#define __xmodem_h

#define NAK 0x15
#define EOT 0x04
#define ACK 0x06

void xmodem_recv(char *addr);

#endif
