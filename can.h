typedef struct can
{
 	int id;
	int dlc;
	int rtr;
	int byteA;
	int byteB;
	int flag;
}can_msg;
void can_init(void);
void can_init(void)
{
 	PINSEL1|=0x00014000;
	VPBDIV=1;
	C2MOD=0x01;
	AFMR=0x02;
	C2BTR=0x001c001d;
	C2MOD&=~(1<<0);
}
