#include <LPC21XX.H>	 
#include "uart1.h"
#include "can.h"
#include "4bitheader.h"
#include <stdarg.h>
int flag=0;

#define SW1 1<<14
#define SW2 1<<15
#define SW3 1<<16
void can_tx(can_msg );
int main()
{
 
   can_msg m1,m2,m3,m4;
   can_init();
   LCD_INIT();
 uart0_init(115200);
 uart0_tx_string("NODE IS SENDING");
 
    m1.id=0x100;
    m1.dlc=1;
    m1.rtr=0;
    m1.byteA=0xAA;
    m1.byteB=0;

    m2.id=0x200;
    m2.dlc=1;
    m2.rtr=0;
    m2.byteA=0xBB;
    m2.byteB=0;
  
    m3.id=0x300;
    m3.dlc=1;
    m3.rtr=0;
    m3.byteA=0xBB;
    m3.byteB=0;
      
	  
	 m4.id=0x400;
    m4.dlc=1;
    m4.rtr=0;
    m4.byteA=0xBB;
    m4.byteB=0;
       
	  LCD_COMMAND(0X82);
  	 LCD_STR("BODY CONTROL");
	 LCD_COMMAND(0XC5);
  	 LCD_STR("MODULE");
   

    while(1)
    {
	
    if((IOPIN0&SW1)==0)
    {  
   delay_ms(200);
   while((IOPIN0&SW1)==0);
	LCD_COMMAND(0X0C);
	LCD_STR("LEFT INDICATOR ON");
   uart0_tx_string("Node_A transmit the message to Node_B");
  uart0_tx_string("\r\n");
    
    can_tx(m1);
    uart0_tx_hex(m1.id);
    }
    
    
    if((IOPIN0&SW2)==0)
    {
       delay_ms(200);
       while((IOPIN0&SW2)==0);
    uart0_tx_string("Node_A transmit the message to Node_C");
    uart0_tx_string("\r\n");
		can_tx(m2);
    
    }
    if((IOPIN0&SW3)==0)
    {
      flag=!flag;
   delay_ms(250);
   while((IOPIN0&SW3)==0);
   uart0_tx_string("Node_A transmit the message to Node_B");
  uart0_tx_string("\r\n");

	if(flag==1)
	{
    can_tx(m3);
	uart0_tx_hex(m3.id);
	}
    else
	{
	can_tx(m4);
	uart0_tx_hex(m4.id);
    }
	}
	 LCD_COMMAND(0X82);
  	 LCD_STR("BODY CONTROL");
	 LCD_COMMAND(0XC5);
  	 LCD_STR("MODULE");
  
}
}
void can_tx(can_msg m1)
 {
   C2TID1=m1.id;
   C2TFI1=(m1.dlc<<16);
   if(m1.rtr==0)
   {
      C2TFI1&=~(1<<30);
   C2TDA1=m1.byteA;
   C2TDB1=m1.byteB;
   }
   else
   C2TFI1|=1<<30;
   C2CMR=(1<<0)|(1<<5);
   while(((C2GSR>>3)&1)==0);
 }
