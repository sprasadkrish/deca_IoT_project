#include <LPC21xx.h>
#include "lcd4bit.h"


void Delay(unsigned long b){ 
  while (--b!=0);	 
  }

void delay_ms(uint16_t j)                    // Function for delay in milliseconds  
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    	for(x=0; x<6000; x++);                // loop to generate 1 millisecond delay with Cclk = 60MHz
	}
}
 void write_command(int cmd) {
  IO1CLR  |= 0x00f00000;                 	/* Clear D4-D7  */
  IO1CLR  |= 0x00040000;	                /* Read/Write = 0 				*/
  IO1CLR  |= 0X00020000;                    /* Register Select = 0,Command */
  IO1SET  |= 0x00f00000 & cmd;  		    /* Set D4-D7    */
  IO1SET  |= 0X00080000;	                /* Enable = 1 					*/  
  Delay(30000);
  IO1CLR  |= 0x00080000;                	 /* set E to low 	  			*/
  }
 
void write_data(int dat) {
  IO1CLR  |= 0x00f00000;                 	/* Clear D4-D7  */
  IO1CLR  |= 0x00040000;		 			/* Read/Write = 0 			*/
  IO1SET  |= 0X00020000;    				/* Register Select = 1,Data */
  IO1SET  |= 0x00f00000 & dat;  			/* Set D4-D7    */
  IO1SET  |= 0X00080000;					/* Enable = 1 				*/
  Delay(30000);          					//delay ~2ms
  IO1CLR  |= 0x00080000; 					/* Set E to low 		  	*/
  }

void lcd_data(char dat){
  write_data(dat << 16);
  write_data(dat << 20);
  }

void lcd_command(char cmd){
  write_command(cmd << 16);
  write_command(cmd << 20);
  }
  
void printlcd(char *CPtr){
  while(*CPtr != '\0') {
	lcd_data(*CPtr);
    CPtr++;
	Delay(20000);
	}
  }



void init_lcd(void) {										  
  IO1DIR 	|= 0x00FE0000;    
  Delay(200000) ;
  write_command(0x30 << 16); 
  Delay(100000);
  write_command(0x30 << 16);
  Delay(100000);
  write_command(0x30 << 16);
  Delay(100000);
  write_command(0x20 << 16);

  lcd_command(0x01);	                         /* clear display */
  lcd_command(0x06);	                         /* auto address inc */
  lcd_command(0x0c);	                         /* cursor off */
  lcd_command(0x80);	                         /* first location */
  }
