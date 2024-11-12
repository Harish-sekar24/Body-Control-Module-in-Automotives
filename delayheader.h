void delay_microsecond(unsigned int t)
{
  T0PR=15-1;
	T0TCR=0X01;
	while(T0TC<t);
	T0TCR=0X03;														  
	T0TCR=0x00;
}
void delay_millisecond(unsigned int t)
{
  T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<t);
	T0TCR=0X03;
	T0TCR=0x00;
}
void delay_second(unsigned int t)
{
  T0PR=15000000-1;
	T0TCR=0X01;
	while(T0TC<t);
	T0TCR=0X03;
	T0TCR=0x00;
}
void delay_ms(int ms)
{
	T0PR = 60000-1;
	T0TCR = 0X01;
	while(T0TC < ms);
	T0TCR = 0X03;
	T0TCR = 0X00;	
}
