#include "includes.h"

extern code unsigned char Segment[];
extern code unsigned char Select[];

unsigned char gDp = 1,gCounter = 0;

void delay1s(void)
{
	unsigned char h,i,j,k;
	for(h=5;h>0;h--)
	for(i=4;i>0;i--)
	for(j=116;j>0;j--)
	for(k=214;k>0;k--);
}

void InitTimer0() //???0 ???
{TMOD= 0x01; //?????0 ?????1
	TH0= 0x3C; // ???
	TL0 = 0x0B0;
	EA= 1; // ????
	ET0 = 1; //???? 0 ??
	TR0 = 1; // ?????0 
}

void Timer0Interrupt(void) interrupt 1 // ???0 ?????
{
	gCounter++;
	if(gCounter == 10){
	TH0= 0x3C; // ????, ?????????
	TL0 = 0x0B0;
	if(gDp == 1)
		gDp = 0;
			else 
		gDp = 1;
	gCounter = 0;
	}
}
void main(void)
{
	unsigned short i;
	DigInit();
  //��ʼ��ʱ����������֮ǰ�����ã����δ˺�������
	SetTimeCalendar();				//����DS1302�е�ʱ�������Ϊ��ʼֵ
	InitTimer0();
	//while(1)	test();
	while(1)
	{
		ReadTime();             //��ȡʱ��
		DisplayTime();      //��ʾʱ��
	}
}