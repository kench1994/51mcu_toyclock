#include "digitron.h"

code unsigned char Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  // 数字段码，Segment[0]~Segment[9]分别对应数字0~9的段码
code unsigned char Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};  // 位选，Select[0]为全选，Select[1]~Select[8]分别对应第1位（最右侧）~第8位（最左侧）

/**********************************************
功能：
    输出位选字节和段码字节到74HC595
输入参数：
    SelectByte:  位选字节
    SegmentByte: 段码字节
输出参数：
    无
返回值：
**********************************************/
void DigOutput(unsigned char SelectByte, unsigned char SegmentByte)
{
    unsigned char i;
    
	DIG_SHCP = 0;   // 74HC595的移位脉冲引脚输出低电平
	DIG_STCP = 0;   // 74HC595的锁存脉冲引脚输出低电平
    
    /* 将段码字节（共8位，高位在前）移入74HC595芯片 */
	for(i=0; i<8; i++)
	{
        /* 判断数据的最高位，如果最高位是1，数据引脚输出高电平；如果是0，输出低电平 */
	    if(SegmentByte&0x80)
        {
	        DIG_DATA = 1;
        }
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
        /* 输出74HC595芯片的数据移位脉冲，每输出一个移位脉冲，74HC595内部的数据移动一位 */
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
        /* 要输出的数据左移一位，即为下一位数据的输出作准备 */
		SegmentByte <<= 1;
	}
    /* 将位选字节（共8位，高位在前）移入74HC595芯片 */
	for(i=0; i<8; i++)
	{
	    if(SelectByte&0x80)
        {
	        DIG_DATA = 1;
        }    
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
		SelectByte <<= 1;
	}
    /* 输出74HC595芯片的数据锁存脉冲，即将74HC595芯片接收到的最新数据输出到芯片的所有数据引脚 */
	DIG_STCP = 1;
	_nop_();
	DIG_STCP = 0;
	_nop_();
}


/**********************************************
功能：
    在某位显示自定义段码
输入参数：
    DigSelect: 数码管位选择（1——8，即最右到最左）
    CustomSeg: 自定义段码值
输出参数：
    无
返回值：
**********************************************/
void DigShowCustom(unsigned char DigSelect, unsigned char CustomSeg)
{
    if(0<DigSelect<9)
    {
        DigOutput(Select[DigSelect],CustomSeg);
    }
}

/**********************************************
功能：
    在某位显示数字
输入参数：
    DigSelect: 数码管位选择（1——8，即最右到最左）
    Number:    数字（0——9）
    Dp:        小数点（1:显示；0:不显示）
输出参数：
    无
返回值：
**********************************************/
void DigShowNumber(unsigned char DigSelect, unsigned char Number, bit Dp)
{
    if((0<DigSelect<9)&&(Number<10))
    {
        if(Dp)
    	{
            DigOutput(Select[DigSelect],(Segment[Number]&~0x80));
    	}
    	else
    	{
            DigOutput(Select[DigSelect],(Segment[Number]|0x80));
    	}
    }
}


/**********************************************
功能：
    初始化数码管，使数码管全灭
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DigInit(void)
{
    DIG_DATA = 0;
	  DIG_SHCP = 0;
	  DIG_STCP = 0;
    DigOutput(0x00,0xff);
}