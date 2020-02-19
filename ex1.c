#include <LPC21xx.H>                   /* LPC21xx definitions			*/             
#include "lcd4bit.h"
 #include <stdint.h>

#include <stdio.h>
#include <string.h>

void init_adc()
{
  PINSEL1 |= 0X01000000;
  ADCR = 0X00200602;
}

 
int read_adc(void)
{
  int val;	  
  ADCR |= 0x01000000;                 /* Start A/D Conversion           */
  do 
  {
  	val = ADDR;                        /* Read A/D Data Register         */
  } while (!(val & 0x80000000));     /* Wait for end of A/D Conversion */
  ADCR &= ~0x01000000;                 /* Stop A/D Conversion            */
  val >>=6;
  val= val & 0x3FF;
  return(val);
}
 
 



int main(void)
{
	int dat,i=0;
	 
	char buf[5];
	init_adc();
	init_lcd();
	init_serial();
 
	sprintf (buf,"%2.2f", read_adc()*1.0);
	delay_ms(5000);   
	UART0_SendString("AT\r"); 
	delay_ms(3000);  
	UART0_SendString("AT+CWMODE=2\r"); 
	delay_ms(3000);
//	UART0_SendString("AT+CIFSR\r");
//	delay_ms(3000);
	UART0_SendString("AT+CIPMUX=1\r"); 
	delay_ms(5000);  
	UART0_SendString("AT+CIPSERVER=1,80\r"); 
	delay_ms(15000);  
	UART0_SendString("AT+CIPSEND=0,5\r");
	delay_ms(15000); 
			UART0_SendString(buf);
//	UART0_SendString("98.00");
		//	UART0_SendString("\r\n");
			delay_ms(15000);  
//	UART0_SendString(buf);
//	UART0_SendString("\r");
	delay_ms(15000);  
	UART0_SendString("AT+CIPCLOSE=0\r");
	delay_ms(3000);  
 


	while(1)
	{
 	  
	  		sprintf (buf,"%2.2f", read_adc()*1.0);
		//	delay_ms(5000);   
			UART0_SendString("AT+CIPSERVER=1,80\r"); 
			delay_ms(15000);  
			UART0_SendString("AT+CIPSEND=0,5\r");
			delay_ms(15000); 
			UART0_SendString(buf);
	 		delay_ms(15000);  
			UART0_SendString("AT+CIPCLOSE=0\r");
			delay_ms(3000); 
 
	 	while(dat>0)
	 	{
		   	buf[i]=dat%10;
	 		dat=dat/10;
	 		i++;
	 	}
	 	while(--i >= 0)
		{
			lcd_data(buf[i]+'0');
		}

		lcd_data(' ');
		lcd_data(' ');
		lcd_data(' ');
		lcd_data(' ');
		lcd_data(' ');	
 	
	}
	
	 
}
 

