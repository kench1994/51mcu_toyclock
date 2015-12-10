#ifndef _DS1302_H_
#define _DS1302_H_

#include "includes.h"

/* ����DS1302���нӿڶ�Ӧ�Ķ˿� */
sbit DS1302_RST = P3^7;    //RST���ţ����°汾��оƬ�ֲ��ж���ΪCE
sbit DS1302_CLK = P3^6;   //CLK���ţ���Ϊ���нӿڵ�ʱ������
sbit DS1302_IO =  P2^1;     //�������ţ��������

/* �������ָ��Ĵ�����ַ */
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


/* ����Ĵ���д��������ָ�� */
#define WP_ON		    0x80
#define WP_OFF          0x00

/* �ӿں������� */
void WriteDS1302(unsigned char Adr, unsigned char WByte);
unsigned char ReadDS1302(unsigned char Adr);


/**********************************************
���ܣ�
    ��ʾʱ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void DisplayTime(void);

/**********************************************
���ܣ�
    ��ʾ����
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void DisplayCalendar(void);


/**********************************************
���ܣ�
    ����ʱ�������
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void SetTimeCalendar(void);

/**********************************************
���ܣ�
    ��ȡʱ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void ReadTime(void);

/**********************************************
���ܣ�
    ��ȡ����
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void ReadCalendar(void);


//void test(void);
#endif