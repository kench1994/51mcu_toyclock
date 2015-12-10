#ifndef _DIGITRON_H_
#define _DIGITRON_H_

#include "includes.h"

sbit DIG_DATA = P0^2;   // 74HC595��������������
sbit DIG_SHCP = P0^4;   // 74HC595����λ��������
sbit DIG_STCP = P2^3;   // 74HC595��������������


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
void DigOutput(unsigned char SelectByte, unsigned char SegmentByte);


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
void DigShowCustom(unsigned char DigSelect, unsigned char CustomSeg);

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
void DigShowNumber(unsigned char DigSelect, unsigned char Number, bit Dp);

/**********************************************
���ܣ�
    ��ʼ������ܣ�ʹ�����ȫ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void DigInit(void);
#endif
