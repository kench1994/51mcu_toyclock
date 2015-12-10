#ifndef _DIGITRON_H_
#define _DIGITRON_H_

#include "includes.h"

sbit DIG_DATA = P0^2;   // 74HC595的数据输入引脚
sbit DIG_SHCP = P0^4;   // 74HC595的移位脉冲引脚
sbit DIG_STCP = P2^3;   // 74HC595的锁存脉冲引脚


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
void DigOutput(unsigned char SelectByte, unsigned char SegmentByte);


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
void DigShowCustom(unsigned char DigSelect, unsigned char CustomSeg);

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
void DigShowNumber(unsigned char DigSelect, unsigned char Number, bit Dp);

/**********************************************
功能：
    初始化数码管，使数码管全灭
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DigInit(void);
#endif
