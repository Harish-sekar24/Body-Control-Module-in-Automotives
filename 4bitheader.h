#include <LPC21XX.H>
#include "delayheader.h"
#define LCD_D 0X0f<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19
void LCD_INIT(void);
void LCD_COMMAND(unsigned char );
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);
void LCD_STR(unsigned char *);
void LCD_FLOAT(float );
void LCD_INIT(void)
{
	IODIR1=LCD_D|RS|E|RW;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);	
	LCD_COMMAND(0X28);
    LCD_COMMAND(0X80);
}
void LCD_COMMAND(unsigned char cmd)
{
	IOCLR1=LCD_D;
	IOSET1=(cmd&0xf0)<<16;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=(cmd&0x0f)<<20;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void LCD_DATA(unsigned char d)
{
	IOCLR1=LCD_D;
	IOSET1=(d&0xf0)<<16;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=(d&0x0f)<<20;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void LCD_STR1(unsigned char *s)
{
int c=0;
while(*s)
{
c++;
if(c==16)
LCD_COMMAND(0xc0);
LCD_DATA(*s++);
}
}
void LCD_STR(unsigned char *s)
{
 while(*s)
 LCD_DATA(*s++);
}
void LCD_INTEGER(int n)
{
 	int a[5],i=0;
	if(n==0)
	LCD_DATA('0');
	else
	{
		if(n<0)
		{
			LCD_DATA('-');
			n=-n;
			}
		while(n>0)
		{
		  a[i++]=n%10;
		  n=n/10;
		  }
		  for(--i;i>=0;i--)
		  LCD_DATA(a[i]+48);
		  }

}
void LCD_FLOAT(float f)
{
	int temp;
	temp=f;
	LCD_INTEGER(temp);
	LCD_DATA('.');
	temp=(f-temp)*100;
	LCD_INTEGER(temp);
	}
void LCD_SCROLL(char *p)
{
        unsigned char i,c,sh=0;
    char *s;
 
  while(1)
		{
            s=p,c=sh;
		       	LCD_COMMAND(0X80);  
       			for(i=sh;i!=0;i++)
			      LCD_COMMAND(' ');
				      
			  if(sh==16)
				{
            LCD_COMMAND(0x80);				
                 sh=0;
}
                 
								while(*s)
									{
										 if(c==16)						
								  LCD_COMMAND(0X80);
                  LCD_DATA(*s++);
						      c++;
	  
					}
					sh++;
					delay_second(1);
					LCD_COMMAND(0X01);
}
}
