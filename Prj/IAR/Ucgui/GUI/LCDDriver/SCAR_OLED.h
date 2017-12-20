


#ifndef __SCAR_OLED_H__
#define __SCAR_OLED_H__


#include "common.h"             //ɽ��K60 ƽ̨�������������ͺ궨��
//����OLEDʹ�õ����ݱ�׼


//����OLEDʹ�õĽӿڱ�׼
//����������
#define OLED_CLK_H      gpio_set (PTD1, 1);
#define OLED_MISO_H     gpio_set (PTD3, 1);
#define OLED_RST_H      gpio_set (PTD4, 1);
#define OLED_DC_H       gpio_set (PTD2, 1);
//����������
#define OLED_CLK_L      gpio_set (PTD1, 0);
#define OLED_MISO_L     gpio_set (PTD3, 0);
#define OLED_RST_L      gpio_set (PTD4, 0);
#define OLED_DC_L       gpio_set (PTD2, 0);

/*****************************************************************************
 #### Hardware_Interface ####
		
	OLED������------------------------------------------------------------------
               GND  ��Դ��
               VCC  ��5V��3.3v��Դ
               D0   PTD1 ��Ϊ OLED_CLK
               D1   PTD3 ��Ϊ OLED_MISO
               RST  PTD4 ��Ϊ OLED_RST
               DC   PTD2 ��Ϊ OLED_DC 
               CS   �ѽӵأ����ý�
               -----------------------------------------------------------------
               ע��:�����Ľӿ��뱾����һ�����޸�ʱ�벻Ҫ��©�˸�ģ���ʼ������
                  --�жԹܽ�����/���������
 *****************************************************************************/

void OLED_Clear(void);
void SCAR_OLED_Init(void);
void OLED_DrawPoint(int8_t x,int8_t y,int8_t t);
void OLED_Updata(void);


/////  



#endif  //__SCAR_OLED_H__
