#ifndef _DS1302_H_
#define _DS1302_H_

#include "includes.h"

/* 定义DS1302串行接口对应的端口 */
sbit DS1302_RST = P3^7;    //RST引脚，在新版本的芯片手册中定义为CE
sbit DS1302_CLK = P3^6;   //CLK引脚，作为串行接口的时钟引脚
sbit DS1302_IO =  P2^1;     //数据引脚，输入输出

/* 定义控制指令集寄存器地址 */
#define ADR_R_SECONDS   0x81
#define ADR_R_MINUTES	0x83
#define ADR_R_HOUR    	0x85
#define ADR_R_DATE		0x87
#define ADR_R_MONTH	    0x89
#define ADR_R_DAY		0x8B
#define ADR_R_YEAR		0x8D
#define ADR_R_WP		0x8F

#define ADR_W_SECONDS   0x80
#define ADR_W_MINUTES	0x82
#define ADR_W_HOUR    	0x84
#define ADR_W_DATE		0x86
#define ADR_W_MONTH	    0x88
#define ADR_W_DAY		0x8A
#define ADR_W_YEAR		0x8C
#define ADR_W_WP		0x8E


/* 定义寄存器写保护开关指令 */
#define WP_ON		    0x80
#define WP_OFF          0x00

/* 接口函数定义 */
void WriteDS1302(unsigned char Adr, unsigned char WByte);
unsigned char ReadDS1302(unsigned char Adr);


/**********************************************
功能：
    显示时间
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DisplayTime(void);

/**********************************************
功能：
    显示日期
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DisplayCalendar(void);


/**********************************************
功能：
    设置时间和日期
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void SetTimeCalendar(void);

/**********************************************
功能：
    读取时间
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void ReadTime(void);

/**********************************************
功能：
    读取日期
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void ReadCalendar(void);


//void test(void);
#endif