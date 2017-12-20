
 /*!
  * @file       SCAR_OLED.c
  * @brief      SCAR_OLED驱动函数实现
  * @author     
  * @version    v1.0
  * @date       2017-02-02
  * @remarks
				-----
				

  */

#include "common.h"		//山外K60 平台常用类型声明和宏定义
#include "MK60_port.h"		//PORT
#include "MK60_gpio.h"		//IO口操作
#include "SCAR_OLED.h"		//OLED

#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 		


#define X_WIDTH  128
int8_t OLED_GRAM[128][8];
//==============================================================
//函数名：      void OLED_PutPixel(int8_t x,int8_t y)
//功能描述：    OLED_写 1Bit 数据
//参数：        写入的数据
//返回：        无
//调用：        内部调用
//==============================================================
void OLED_WriteData(int8_t data)
{
  int16_t i=8;
  OLED_DC_H;
  OLED_CLK_L;
  
 for(i=8;i>0;i--)
  {
    if(data&0x80)
	{
	  OLED_MISO_H;
	}
    else
	{
	  OLED_MISO_L;
	}
	
    OLED_CLK_H;      
    OLED_CLK_L;
	
    data<<=1;    
  }

}



//==============================================================
//函数名：      void OLED_WriteCmd(int8_t cmd)
//功能描述：    OLED_写 1Bit 命令
//参数：        写入的命令
//返回：        无
//调用：        内部调用
//==============================================================
void OLED_WriteCmd(int8_t cmd)
{
  int16_t i=8;
  OLED_DC_L;
  OLED_CLK_L;;

  for(i=8;i>0;i--)
  {
    if(cmd&0x80)
	{
	  OLED_MISO_H;	 
	}
    else
	{
	  OLED_MISO_L;	 
	}
    OLED_CLK_H;	
    OLED_CLK_L;   
    cmd<<=1;   
  } 	

}


//==============================================================
//函数名：      void OLED_Set_Pos(int8_t x, int8_t y)
//功能描述：    设置起始点
//参数：        坐标
//返回：        无
//调用：        内部调用
//==============================================================
void OLED_Set_Pos(int8_t x, int8_t y)
{ 
  OLED_WriteCmd(0xb0+y);
  OLED_WriteCmd(((x&0xf0)>>4)|0x10);
  OLED_WriteCmd((x&0x0f)|0x01); 
} 

//==============================================================
//函数名：      void OLED_DLY_ms(int16_t ms)
//功能描述：    OLED_延时(精确)
//参数：        ms
//返回：        无
//调用：        内部调用
//==============================================================
void OLED_DLY_ms(int16_t ms)
{                         
	DELAY_MS(ms);

}

//==============================================================
//函数名：      void SCAR_OLED_Init(void)   
//功能描述：    OLED_初始化
//参数：        无
//返回：        无
//调用：        外部调用
//==============================================================
void SCAR_OLED_Init(void)        
{
    gpio_init (PTD2, GPO,0);            //DC
    gpio_init (PTD4, GPO,0);            //RST
    gpio_init (PTD3, GPO,0);            //D1
    gpio_init (PTD1, GPO,0);            //D0
	
	OLED_CLK_H;			//预制SLK和SS为高电平 
	OLED_RST_L;
	OLED_DLY_ms(50);      
	OLED_RST_H;         //复位OLED

	OLED_WriteCmd(0xae);//--turn off oled panel
	OLED_WriteCmd(0x00);//---set low column address
	OLED_WriteCmd(0x10);//---set high column address
	OLED_WriteCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteCmd(0x81);//--set contrast control register
	OLED_WriteCmd(0xcf);// Set SEG Output Current Brightness
	OLED_WriteCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WriteCmd(0xc0);/////Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WriteCmd(0xa6);//--set normal display
	OLED_WriteCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WriteCmd(0x3f);//--1/64 duty
	OLED_WriteCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteCmd(0x00);//-not offset
	OLED_WriteCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WriteCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteCmd(0xd9);//--set pre-charge period
	OLED_WriteCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteCmd(0xda);//--set com pins hardware configuration
	OLED_WriteCmd(0x12);
	OLED_WriteCmd(0xdb);//--set vcomh
	OLED_WriteCmd(0x40);//Set VCOM Deselect Level
	OLED_WriteCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteCmd(0x02);//
	OLED_WriteCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WriteCmd(0x14);//--set(0x10) disable	OLED_WriteCmd(0x10);//--set(0x10) disable
	OLED_WriteCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WriteCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WriteCmd(0xaf);//--turn on oled panel
    
    //清屏
    OLED_Clear();

}


//画点	
//t:1 填充 0,清空
void OLED_DrawPoint(int8_t x,int8_t y,int8_t t)
{
	int16_t pos,bx,temp=0;
//	if(x>127||y>63)return;
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
//开启OLED显示  
void OLED_Display_On(void)
{
	OLED_WriteCmd(0X8D);  
	OLED_WriteCmd(0X14);  
	OLED_WriteCmd(0XAF); 
}
//关闭OLED显示    
void OLED_Display_Off(void)
{
	OLED_WriteCmd(0X8D);  
	OLED_WriteCmd(0X10); 
	OLED_WriteCmd(0XAE); 
}		
//更新显存到LCD		 
void OLED_Updata(void)
{
	int16_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WriteCmd (0xb0+i);    
		OLED_WriteCmd (0x00);      
		OLED_WriteCmd (0x10);       
		for(n=0;n<128;n++)OLED_WriteData(OLED_GRAM[n][i]); 
	}   
}
//清屏
void OLED_Clear(void)
{
	int16_t i=0,n=0;  
	for(i=0;i<8;i++)
      for(n=0;n<128;n++)
        OLED_GRAM[n][i]=0x00;  
	OLED_Updata();
}
/*
Oled_FillImage(uint8_t *Image)
{
    uint8_t x, y;
    
    for()
}

*/


void LCD_Index2Color_233(){}

void LCD_Index2Index_233(){}

void LCD_Color2Index_233(){}



