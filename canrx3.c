#include <lpc21xx.h>
#include "can.h"
#include "uart1.h"
#include "4bitheader.h"
#define IP1 1<<17
#define IP2 1<<18
void can_init(void);
void can_rx(can_msg *);
void delay(int ms);
int main()
{
 can_msg m2;
 IODIR0 |= IP1|IP2;
 IOSET0 |= IP1|IP2;
 can_init();
 LCD_INIT();
 uart0_init(115200);
 uart0_tx_string("NODE TESING");
 LCD_STR("WIPER"); .
 while(1)
 {
   can_rx(&m2);
  uart0_tx_hex(m2.id);
  if(m2.id ==0x300)
  {
  uart0_tx_string("\r\nWIPER ON");
  	
  	LCD_COMMAND(0X01);
  LCD_STR("WIPER ON");
   while(1)
   {
   IOSET0 |= IP1;
   IOCLR0 |= IP2;

    can_rx(&m2);
	 uart0_tx_hex(m2.id);
     if(m2.id==0x400)
     {
        IOCLR0|=IP1;
		IOCLR0|=IP2;
		LCD_COMMAND(0X01);
    	LCD_STR("WIPER OFF");
        break;
     }
   }
  }
  else if(m2.id==0x400)
  {
   IOCLR0|=IP1;
    IOCLR0|=IP2;
   	LCD_COMMAND(0X01);
	LCD_STR("WIPER OFF");
  }
}
   }
void can_rx(can_msg *m2)
{
 while((C2GSR&0x1)==0);
 m2->id=C2RID;
 m2->dlc=(C2RFS>>16)&0xF;
 m2->rtr=(C2RFS>>30)&0x1;
 if(m2->rtr==0)
 { 
  m2->byteA=C2RDA;
  m2->byteB=C2RDB;
 }
 C2CMR=(1<<2);
}
