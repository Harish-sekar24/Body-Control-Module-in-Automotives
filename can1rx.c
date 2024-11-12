#include <lpc21xx.h>
#include "can.h"
#include "4bitheader.h"
#include "uart1.h"
#define LED 1<<17
void can_init(void);
void can_rx(can_msg *);
void delay(int ms);
int main()
{
 int cnt=0;
 can_msg m1;
 IODIR0 |= LED;
 IOSET0 |= LED;
 can_init();
 LCD_INIT();
 uart0_init(115200);
 uart0_tx_string("NODE TESING");
 LCD_STR("LEFT INDICATOR");
 while(1)
 {
  
   can_rx(&m1);
  uart0_tx_hex(m1.id);
  if(m1.id ==0x100)
  {
  uart0_tx_string("\r\nLIGHT ON");
  	LCD_COMMAND(0X01);
   LCD_STR1("LEFT INDICATOR ON");
   while(cnt<10)
   {
   IOCLR0 = LED;
   delay_ms(500);
   IOSET0 = LED;
   delay_ms(500);
   cnt++;
	}
   }
   else
   {
   IOSET0|=LED;
   }
   cnt=0;
   LCD_COMMAND(0X01);
   LCD_STR1("LEFT INDICATOR OFF");
  
}
}
void can_rx(can_msg *m1)
{
 while((C2GSR&0x1)==0);
 m1->id=C2RID;
 m1->dlc=(C2RFS>>16)&0xF;
 m1->rtr=(C2RFS>>30)&0x1;
 if(m1->rtr==0)
 { 
  m1->byteA=C2RDA;
  m1->byteB=C2RDB;
 }
 C2CMR=(1<<2);
}
