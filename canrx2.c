#include <lpc21xx.h>
#include "can.h"
#include "uart1.h"
#include "4bitheader.h"
#define LED 1<<19
void can_init(void);
void can_rx(can_msg *);
void delay(int ms);
int main()
{
int cnt=0;
 can_msg m2;
 IODIR0 |= LED;
 IOSET0 |= LED;
 can_init();
 LCD_INIT();
 uart0_init(115200);
 uart0_tx_string("NODE TESING");
  LCD_STR("RIGHT INDICATOR");
 while(1)
 {
   can_rx(&m2);
  uart0_tx_hex(m2.id);
  if(m2.id ==0x200)
  {
  uart0_tx_string("\r\nLIGHT ON");
  LCD_COMMAND(0X01);
   LCD_STR1("RIGHT INDICATOR ON");
   while(cnt<10)
   {
   IOCLR0 = LED;
   delay_ms(300);
   IOSET0 = LED;
   delay_ms(300);
   cnt++;
	}    
  }
  else
  IOSET0|=LED;
  cnt=0;

  LCD_COMMAND(0X01);
   LCD_STR1("RIGHT INDICATOR OFF");
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
