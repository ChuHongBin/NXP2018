#include "Debug.h"
#include "SCAR_OLED.h"
#include "myKey.h"
#include "Image.h"



bool menu_State_1 =false;
bool menu_State_2 =false;
bool menu_1 =false;
bool menu_2 =false;
// 6*8
//��ʾ
//ʹ�ò��뿪�ؿ������˵�
void Debug(void)
{ 
  //���뿪�ظ�ֵ
  menu_State_1 = key_Switch_1;
  menu_State_2 = key_Switch_2;
  //��ʼ��
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
  //�˵� 1
  //��ʾͼƬ�����
  if(!menu_1 && menu_State_1 && !menu_State_2)
  { 
    menu_1 = true;    
    //��������
    GUI_GotoXY(80,60);
    //��ʾ֡��
    GUI_DispString("FPS:");
    //��������
    GUI_GotoXY(80,60);
    //��ʾ�ı�
    GUI_DispString("");   
  }  
  //�˵� 2
  //��ʾPID
  if(!menu_2 && menu_State_2 && !menu_State_1)
  { 
    menu_2 = true;
    //��������
    GUI_GotoXY(0,0);
    //��ʾ�ı�
    GUI_DispString("P:");
    //��������
    GUI_GotoXY(0,8);
    //��ʾ�ı�
    GUI_DispString("I:");
    //��������
    GUI_GotoXY(0,16);
    //��ʾ�ı�
    GUI_DispString("D:");    
  }
  //����������
  //��̬��ʾ
  if(menu_1 && menu_State_1 && !menu_State_2)
  {
    //��ʾͼ��
    GUI_DrawBitmap(&DispImage,0,0);
    //����
    OLED_Updata();
  }
  if(menu_2 && menu_State_2 && !menu_State_1)
  { 
    //����
    OLED_Updata();
  }
}

