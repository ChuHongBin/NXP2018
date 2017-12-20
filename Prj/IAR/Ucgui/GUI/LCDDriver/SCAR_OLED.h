


#ifndef __SCAR_OLED_H__
#define __SCAR_OLED_H__


#include "common.h"             //山外K60 平台常用类型声明和宏定义
//定义OLED使用的数据标准


//定义OLED使用的接口标准
//数据线拉高
#define OLED_CLK_H      gpio_set (PTD1, 1);
#define OLED_MISO_H     gpio_set (PTD3, 1);
#define OLED_RST_H      gpio_set (PTD4, 1);
#define OLED_DC_H       gpio_set (PTD2, 1);
//数据线拉低
#define OLED_CLK_L      gpio_set (PTD1, 0);
#define OLED_MISO_L     gpio_set (PTD3, 0);
#define OLED_RST_L      gpio_set (PTD4, 0);
#define OLED_DC_L       gpio_set (PTD2, 0);

/*****************************************************************************
 #### Hardware_Interface ####
		
	OLED屏接线------------------------------------------------------------------
               GND  电源地
               VCC  接5V或3.3v电源
               D0   PTD1 宏为 OLED_CLK
               D1   PTD3 宏为 OLED_MISO
               RST  PTD4 宏为 OLED_RST
               DC   PTD2 宏为 OLED_DC 
               CS   已接地，不用接
               -----------------------------------------------------------------
               注意:如您的接口与本程序不一样，修改时请不要遗漏了各模块初始化部分
                  --中对管脚输入/输出的配置
 *****************************************************************************/

void OLED_Clear(void);
void SCAR_OLED_Init(void);
void OLED_DrawPoint(int8_t x,int8_t y,int8_t t);
void OLED_Updata(void);


/////  



#endif  //__SCAR_OLED_H__
