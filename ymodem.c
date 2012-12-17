#include "ymodem.h"
#include "tiny210.h"
#include "stdio.h"

unsigned char file_name[FILE_NAME_LENGTH];

unsigned int Str2Int(unsigned char *inputstr, unsigned int *intnum)
{
	unsigned int i = 0, res = 0;
	unsigned int val = 0;

	if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
	{
		if (inputstr[2] == '\0')
		{
    		return 0;
    	}
    	for (i = 2; i < 11; i++)
    	{
      		if (inputstr[i] == '\0')
      		{
        		*intnum = val;
        		/* return 1; */
        		res = 1;
        		break;
      		}
      		if (ISVALIDHEX(inputstr[i]))
      		{
       			val = (val << 4) + CONVERTHEX(inputstr[i]);
      		}
      		else
      		{
        		/* return 0, Invalid input */
        		res = 0;
       			break;
      		}
    	}
    	/* over 8 digit hex --invalid */
    	if (i >= 11)
    	{
      		res = 0;
    	}
  	}
  	else /* max 10-digit decimal input */
  	{
    	for (i = 0;i < 11;i++)
    	{
      		if (inputstr[i] == '\0')
      		{
        		*intnum = val;
        		/* return 1 */
        		res = 1;
        		break;
      		}
      		else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
      		{
        		val = val << 10;
        		*intnum = val;
        		res = 1;
        		break;
      		}
      		else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
      		{
        		val = val << 20;
        		*intnum = val;
        		res = 1;
        		break;
      		}
      		else if (ISVALIDDEC(inputstr[i]))
      		{
        		val = val * 10 + CONVERTDEC(inputstr[i]);
      		}
      		else
      		{
        		/* return 0, Invalid input */
        		res = 0;
        		break;
      		}
    	}
    	/* Over 10 digit decimal --invalid */
    	if (i >= 11)
    	{
      		res = 0;
    	}
  	}
  	return res;
}


int Receive_Packet (unsigned char *data, unsigned int *length, unsigned int timeout)
{
	unsigned int i, packet_size;
	unsigned char c;
	*length = 0;
	if (uart_getchar_timeout((char *)&c, timeout) != 0)
	{
		return -1;
	}
	switch (c)
	{
		case SOH:
			packet_size = PACKET_SIZE;
			break;
		case STX:
			packet_size = PACKET_1K_SIZE;
			break;
		case EOT:
			return 0;
		case CA:
			if ((uart_getchar_timeout((char *)&c, timeout) == 0) && (c == CA))
			{
		    	*length = -1;
		        return 0;
			}
			else
			{
		        return -1;
			}
		case ABORT1:
		case ABORT2:
			return 1;
		default:
			return -1;
	}
	*data = c;
	for (i = 1; i < (packet_size + PACKET_OVERHEAD); i ++)
	{
		if (uart_getchar_timeout((char *)(data + i), timeout) != 0)
	    {
			return -1;
	    }
	}
	if (data[PACKET_SEQNO_INDEX] != ((data[PACKET_SEQNO_COMP_INDEX] ^ 0xff) & 0xff))
	{
		return -1;
	}
	*length = packet_size;
	return 0;
}


int ymodem_recv(char *addr)
{
	unsigned char packet_data[PACKET_1K_SIZE + PACKET_OVERHEAD], file_size[FILE_SIZE_LENGTH], *file_ptr, *buf_ptr;
	unsigned int i, packet_length, session_done, file_done, packets_received, errors, session_begin, size = 0;
	
	for (session_done = 0, errors = 0, session_begin = 0; ;)
	{
		for (packets_received = 0, file_done = 0, buf_ptr = (unsigned char *)addr; ;)
		{
			switch (Receive_Packet(packet_data, &packet_length, NAK_TIMEOUT))
			{
		  		case 0:
				errors = 0;
				switch (packet_length)
				{
			 		/* Abort by sender */
			  		case - 1:
						uart_putchar(ACK);
						return 0;
			  		/* End of transmission */
			  		case 0:
						uart_putchar(ACK);
						file_done = 1;
						break;
			  		/* Normal packet */
			  		default:
						if ((packet_data[PACKET_SEQNO_INDEX] & 0xff) != (packets_received & 0xff))
						{
							uart_putchar(NAK);
						}
						else
						{
							if (packets_received == 0)
				  			{
								/* Filename packet */
								if (packet_data[PACKET_HEADER] != 0)
								{
					  				/* Filename packet has valid data */
					  				for (i = 0, file_ptr = packet_data + PACKET_HEADER; (*file_ptr != 0) && (i < FILE_NAME_LENGTH);)
					  				{
										file_name[i++] = *file_ptr++;
					  				}
					 				file_name[i++] = '\0';
					  				for (i = 0, file_ptr ++; (*file_ptr != ' ') && (i < FILE_SIZE_LENGTH);)
					  				{
										file_size[i++] = *file_ptr++;
					  				}
					  				file_size[i++] = '\0';
					  				Str2Int(file_size, &size);
	
					  				/* Test the size of the image to be sent */
					  				/* Image size is greater than Flash size */
					  				if (size > (IMAGE_MAX_SIZE - 1))
					  				{
										/* End session */
										uart_putchar(CA);
										uart_putchar(CA);
										return -1;
					  				}
					  				uart_putchar(ACK);
					  				uart_putchar(CRC16);
								}
								/* Filename packet is empty, end session */
								else
								{
					  				uart_putchar(ACK);
					  				file_done = 1;
					  				session_done = 1;
					  				break;
								}
				  			}
				  			/* Data packet */
				  			else
				  			{
								memcpy(buf_ptr, packet_data + PACKET_HEADER, packet_length);
					
								buf_ptr += packet_length;
								uart_putchar(ACK);
				  			}
				  			packets_received ++;
				  			session_begin = 1;
						}
				}
				break;
		  		case 1:
					uart_putchar(CA);
					uart_putchar(CA);
					return -3;
		  		default:
					if (session_begin > 0)
					{
			  			errors ++;
					}
					if (errors > MAX_ERRORS)
					{
			  			uart_putchar(CA);
			 			uart_putchar(CA);
			  			return 0;
					}
					uart_putchar(CRC16);
					break;
			}
			if (file_done != 0)
			{
		  		break;
			}
	  	}
	  	if (session_done != 0)
	  	{
			break;
	  	}
	}
	return (int)size;
}





