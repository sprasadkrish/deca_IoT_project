

#include <LPC213x.H>                     /* LPC21xx definitions               */
#include "serial.h" 
#include <stdint.h>



void init_serial (void)  {		         /* Initialize Serial Interface       */
  PINSEL0 |= 0X00000005;                 /* Enable RxD0 and TxD0              */
  U0LCR    = 0X83;	                    /*8 bits, no Parity, 1 Stop bit      */
  U0DLL    = 0XC3;	
  U0DLM = 0X00;							 /* 115.2k Baud Rate @10MHz VPB Clock */
  U0LCR = 0X03;					         /* DLAB = 0                          */
  }



int sendchar (int SDat)  {                 /* Write character to Serial Port    */
  while (!(U0LSR & 0x20));
  return (U0THR = SDat);
  }


int getchar (void)  {                    /* Read character from Serial Port   */
  while (!(U0LSR & 0x01)); 
    return (U0RBR);
  }

void UART0_SendString(char* str) //A function to send string on UART0
{
	uint8_t i = 0;
	while( str[i] != '\0' )
	{
		sendchar(str[i]);
		i++;
	}
}
