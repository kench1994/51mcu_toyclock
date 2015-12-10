#include "digitron.h"

code unsigned char Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  // ���ֶ��룬Segment[0]~Segment[9]�ֱ��Ӧ����0~9�Ķ���
code unsigned char Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};  // λѡ��Select[0]Ϊȫѡ��Select[1]~Select[8]�ֱ��Ӧ��1λ�����Ҳࣩ~��8λ������ࣩ

/**********************************************
���ܣ�
    ���λѡ�ֽںͶ����ֽڵ�74HC595
���������
    SelectByte:  λѡ�ֽ�
    SegmentByte: �����ֽ�
���������
    ��
����ֵ��
**********************************************/
void DigOutput(unsigned char SelectByte, unsigned char SegmentByte)
{
    unsigned char i;
    
	DIG_SHCP = 0;   // 74HC595����λ������������͵�ƽ
	DIG_STCP = 0;   // 74HC595������������������͵�ƽ
    
    /* �������ֽڣ���8λ����λ��ǰ������74HC595оƬ */
	for(i=0; i<8; i++)
	{
        /* �ж����ݵ����λ��������λ��1��������������ߵ�ƽ�������0������͵�ƽ */
	    if(SegmentByte&0x80)
        {
	        DIG_DATA = 1;
        }
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
        /* ���74HC595оƬ��������λ���壬ÿ���һ����λ���壬74HC595�ڲ��������ƶ�һλ */
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
        /* Ҫ�������������һλ����Ϊ��һλ���ݵ������׼�� */
		SegmentByte <<= 1;
	}
    /* ��λѡ�ֽڣ���8λ����λ��ǰ������74HC595оƬ */
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
    /* ���74HC595оƬ�������������壬����74HC595оƬ���յ����������������оƬ�������������� */
	DIG_STCP = 1;
	_nop_();
	DIG_STCP = 0;
	_nop_();
}


/**********************************************
���ܣ�
    ��ĳλ��ʾ�Զ������
���������
    DigSelect: �����λѡ��1����8�������ҵ�����
    CustomSeg: �Զ������ֵ
���������
    ��
����ֵ��
**********************************************/
void DigShowCustom(unsigned char DigSelect, unsigned char CustomSeg)
{
    if(0<DigSelect<9)
    {
        DigOutput(Select[DigSelect],CustomSeg);
    }
}

/**********************************************
���ܣ�
    ��ĳλ��ʾ����
���������
    DigSelect: �����λѡ��1����8�������ҵ�����
    Number:    ���֣�0����9��
    Dp:        С���㣨1:��ʾ��0:����ʾ��
���������
    ��
����ֵ��
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
���ܣ�
    ��ʼ������ܣ�ʹ�����ȫ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void DigInit(void)
{
    DIG_DATA = 0;
	  DIG_SHCP = 0;
	  DIG_STCP = 0;
    DigOutput(0x00,0xff);
}