#include "Debug.h"
#include "SCAR_OLED.h"
#include "myKey.h"
#include "Image.h"



bool menu_State_1 =false;
bool menu_State_2 =false;
bool menu_1 =false;
bool menu_2 =false;
// 6*8
//显示
//使用拨码开关控制主菜单
void Debug(void)
{ 
  //拨码开关赋值
  menu_State_1 = key_Switch_1;
  menu_State_2 = key_Switch_2;
  //初始化
  //
  if(menu_1 && !menu_State_1)
  { 
    OLED_Clear();
    menu_1 = false;
  }
  if(menu_2 && !menu_State_2)
  {
    OLED_Clear();
    menu_2 = false;
  }
  //菜单 1
  //显示图片及相关
  if(!menu_1 && menu_State_1 && !menu_State_2)
  { 
    menu_1 = true;    
    //设置坐标
    GUI_GotoXY(80,60);
    //显示帧率
    GUI_DispString("FPS:");
    //设置坐标
    GUI_GotoXY(80,60);
    //显示文本
    GUI_DispString("");   
  }  
  //菜单 2
  //显示PID
  if(!menu_2 && menu_State_2 && !menu_State_1)
  { 
    menu_2 = true;
    //设置坐标
    GUI_GotoXY(0,0);
    //显示文本
    GUI_DispString("P:");
    //设置坐标
    GUI_GotoXY(0,8);
    //显示文本
    GUI_DispString("I:");
    //设置坐标
    GUI_GotoXY(0,16);
    //显示文本
    GUI_DispString("D:");    
  }
  //数据在这里
  //动态显示
  if(menu_1 && menu_State_1 && !menu_State_2)
  {
    //显示图像
    GUI_DrawBitmap(&DispImage,0,0);
    //更新
    OLED_Updata();
  }
  if(menu_2 && menu_State_2 && !menu_State_1)
  { 
    //更新
    OLED_Updata();
  }
}

