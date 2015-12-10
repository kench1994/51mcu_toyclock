#include "DS1302.h"

extern unsigned char gDp;

unsigned char gSetTime[]={0x15,0x12,0x09,0x18,0x54,0x00};	//初始时间数组13年01月02日11点14分00秒
struct
{
    unsigned char Seconds;  // 秒
    unsigned char Minutes;  // 分
    unsigned char Hour;     // 时
    unsigned char Date;     // 日
    unsigned char Month;    // 月
    unsigned char Year;     // 年
}gsTimeCalendar;

/**********************************************
功能：
    显示时间
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DisplayTime(void)
{
    DigShowNumber(4,gsTimeCalendar.Hour>>4,0);
    DigShowNumber(3,gsTimeCalendar.Hour&0x0f,0);
    DigShowNumber(2,gsTimeCalendar.Minutes>>4,gDp);
    DigShowNumber(1,gsTimeCalendar.Minutes&0x0f,0);
    //DigShowNumber(3,gsTimeCalendar.Seconds>>4,0);
    //DigShowNumber(2,gsTimeCalendar.Seconds&0x0f,0);
}

/**********************************************
功能：
    显示日期
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DisplayCalendar(void)
{
    DigShowNumber(8,2,0);
    DigShowNumber(7,0,0);
    DigShowNumber(6,gsTimeCalendar.Year>>4,0);
    DigShowNumber(5,gsTimeCalendar.Year&0x0f,1);
    DigShowNumber(4,gsTimeCalendar.Month>>4,0);
    DigShowNumber(3,gsTimeCalendar.Month&0x0f,1);
    DigShowNumber(2,gsTimeCalendar.Date>>4,0);
    DigShowNumber(1,gsTimeCalendar.Date&0x0f,0);
}

/**********************************************
功能：
    设置时间和日期
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void SetTimeCalendar(void)
{
	WriteDS1302(ADR_W_WP,WP_OFF);           //关闭写保护功能，即允许对各寄存器进行写操作
    
	WriteDS1302(ADR_W_YEAR,gSetTime[0]);    //年
	WriteDS1302(ADR_W_MONTH,gSetTime[1]);   //月
	WriteDS1302(ADR_W_DATE,gSetTime[2]);    //日
	WriteDS1302(ADR_W_HOUR,gSetTime[3]);    //时
	WriteDS1302(ADR_W_MINUTES,gSetTime[4]); //分
	WriteDS1302(ADR_W_SECONDS,gSetTime[5]); //秒
    
	WriteDS1302(ADR_W_WP,WP_ON);            //启动写保护功能，即禁止对各寄存器进行写操作
}

/**********************************************
功能：
    读取时间
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void ReadTime(void)
{
    //gsTimeCalendar.Seconds = ReadDS1302(ADR_R_SECONDS);		//读取秒
    gsTimeCalendar.Minutes = ReadDS1302(ADR_R_MINUTES);		//读取分
    gsTimeCalendar.Hour    = ReadDS1302(ADR_R_HOUR);			//读取时
}

/**********************************************
功能：
    读取日期
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void ReadCalendar(void)
{
    gsTimeCalendar.Date  = ReadDS1302(ADR_R_DATE);			//读取日
    gsTimeCalendar.Month = ReadDS1302(ADR_R_MONTH);		//读取月
    gsTimeCalendar.Year  = ReadDS1302(ADR_R_YEAR);			//读取年
}

void test(void){
	gsTimeCalendar.Hour = 0x15;
		DigShowNumber(4,gsTimeCalendar.Hour>>4,0);
		DigShowNumber(3,gsTimeCalendar.Hour&0x0f,1);
		DigShowNumber(2,gsTimeCalendar.Minutes>>4,0);
		DigShowNumber(1,gsTimeCalendar.Minutes&0x0f,1);
}

/**********************************************
功能：
    向DS1302发送一个字节
输入参数：
    TByte:发送的字节
输出参数：
    无
返回值：
**********************************************/
static void TransmitByte(unsigned char TByte)
{
    unsigned char i;
    for(i = 0;i < 8;i++)
    {
		DS1302_CLK = 0;
        if(TByte&0x01)
        {
            DS1302_IO = 1;
        }
        else
        {
            DS1302_IO = 0;
        }
        DS1302_CLK = 1;
        TByte >>= 1;
    }
}

/**********************************************
功能：
    从DS1302接收一个字节
输入参数：
    无
输出参数：
    无
返回值：
    RecByte:从DS1302所接收到的字节
**********************************************/
static unsigned char ReceiveByte(void)
{
    unsigned char i,RecByte;
    for(i = 0;i < 8;i++)
    {
		DS1302_CLK = 0;
        RecByte >>= 1;
        if(DS1302_IO)
        {
            RecByte |= 0x80;
        }
        else
        {
            RecByte &= ~0x80;
        }
        DS1302_CLK = 1;
    }
    return(RecByte);
}

/**********************************************
功能：
    写一字节数据到DS1302某地址
输入参数：
    Adr：寄存器地址
    WByte：要写到对应地址的字节
输出参数：
    无
返回值：
    无
**********************************************/
void WriteDS1302(unsigned char Adr, unsigned char WByte)   //往Adr地址中写入数据WByte
{
	DS1302_RST = 0;  //看时序，RST开始为低电平
	DS1302_CLK = 0;  //CLK开始也为低电平
	DS1302_RST = 1;   //RST在高电平，才可以进行通讯。
 	TransmitByte(Adr);  //先写地址
	TransmitByte(WByte);  //往刚刚的地址中写入数据
	DS1302_RST = 0;    //写完一次数据，RST拉低。
}


/**********************************************
功能：
    从DS1302某地址读一字节数据
输入参数：
    Adr：寄存器地址
输出参数：
    无
返回值：
    从DS1302所读取的字节
**********************************************/
unsigned char ReadDS1302(unsigned char Adr)
{
	unsigned char RByte;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	TransmitByte(Adr);
	RByte = ReceiveByte();
	DS1302_RST = 0;
	return(RByte);
}
