#include "DS1302.h"

extern unsigned char gDp;

unsigned char gSetTime[]={0x15,0x12,0x09,0x18,0x54,0x00};	//��ʼʱ������13��01��02��11��14��00��
struct
{
    unsigned char Seconds;  // ��
    unsigned char Minutes;  // ��
    unsigned char Hour;     // ʱ
    unsigned char Date;     // ��
    unsigned char Month;    // ��
    unsigned char Year;     // ��
}gsTimeCalendar;

/**********************************************
���ܣ�
    ��ʾʱ��
���������
    ��
���������
    ��
����ֵ��
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
���ܣ�
    ��ʾ����
���������
    ��
���������
    ��
����ֵ��
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
���ܣ�
    ����ʱ�������
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void SetTimeCalendar(void)
{
	WriteDS1302(ADR_W_WP,WP_OFF);           //�ر�д�������ܣ�������Ը��Ĵ�������д����
    
	WriteDS1302(ADR_W_YEAR,gSetTime[0]);    //��
	WriteDS1302(ADR_W_MONTH,gSetTime[1]);   //��
	WriteDS1302(ADR_W_DATE,gSetTime[2]);    //��
	WriteDS1302(ADR_W_HOUR,gSetTime[3]);    //ʱ
	WriteDS1302(ADR_W_MINUTES,gSetTime[4]); //��
	WriteDS1302(ADR_W_SECONDS,gSetTime[5]); //��
    
	WriteDS1302(ADR_W_WP,WP_ON);            //����д�������ܣ�����ֹ�Ը��Ĵ�������д����
}

/**********************************************
���ܣ�
    ��ȡʱ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void ReadTime(void)
{
    //gsTimeCalendar.Seconds = ReadDS1302(ADR_R_SECONDS);		//��ȡ��
    gsTimeCalendar.Minutes = ReadDS1302(ADR_R_MINUTES);		//��ȡ��
    gsTimeCalendar.Hour    = ReadDS1302(ADR_R_HOUR);			//��ȡʱ
}

/**********************************************
���ܣ�
    ��ȡ����
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void ReadCalendar(void)
{
    gsTimeCalendar.Date  = ReadDS1302(ADR_R_DATE);			//��ȡ��
    gsTimeCalendar.Month = ReadDS1302(ADR_R_MONTH);		//��ȡ��
    gsTimeCalendar.Year  = ReadDS1302(ADR_R_YEAR);			//��ȡ��
}

void test(void){
	gsTimeCalendar.Hour = 0x15;
		DigShowNumber(4,gsTimeCalendar.Hour>>4,0);
		DigShowNumber(3,gsTimeCalendar.Hour&0x0f,1);
		DigShowNumber(2,gsTimeCalendar.Minutes>>4,0);
		DigShowNumber(1,gsTimeCalendar.Minutes&0x0f,1);
}

/**********************************************
���ܣ�
    ��DS1302����һ���ֽ�
���������
    TByte:���͵��ֽ�
���������
    ��
����ֵ��
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
���ܣ�
    ��DS1302����һ���ֽ�
���������
    ��
���������
    ��
����ֵ��
    RecByte:��DS1302�����յ����ֽ�
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
���ܣ�
    дһ�ֽ����ݵ�DS1302ĳ��ַ
���������
    Adr���Ĵ�����ַ
    WByte��Ҫд����Ӧ��ַ���ֽ�
���������
    ��
����ֵ��
    ��
**********************************************/
void WriteDS1302(unsigned char Adr, unsigned char WByte)   //��Adr��ַ��д������WByte
{
	DS1302_RST = 0;  //��ʱ��RST��ʼΪ�͵�ƽ
	DS1302_CLK = 0;  //CLK��ʼҲΪ�͵�ƽ
	DS1302_RST = 1;   //RST�ڸߵ�ƽ���ſ��Խ���ͨѶ��
 	TransmitByte(Adr);  //��д��ַ
	TransmitByte(WByte);  //���ոյĵ�ַ��д������
	DS1302_RST = 0;    //д��һ�����ݣ�RST���͡�
}


/**********************************************
���ܣ�
    ��DS1302ĳ��ַ��һ�ֽ�����
���������
    Adr���Ĵ�����ַ
���������
    ��
����ֵ��
    ��DS1302����ȡ���ֽ�
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
