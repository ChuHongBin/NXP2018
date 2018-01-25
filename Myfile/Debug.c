#include "Debug.h"
#include "SCAR_OLED.h"
#include "myKey.h"
#include "Image.h"

struct MENU 
{
    int16_t menu_e; //�˵���
    int16_t labal;  //���
    int16_t var;

}menu={0, 0, 0};

int16_t *key_state;
int16_t key_state_MAX=8;
int16_t MENU_MAX=3;
//�˵�1
void UI_menu_1(void);
//�˵�2
void UI_menu_2(void);
//�˵�3
void UI_menu_3(void);


void Debug(void)
{  
   //��ȡ����
   key_get_status();
   //��ȡ����״̬
   key_state =key_status;

   //�ı���
   menu.labal +=key_state[0];//��
   if(menu.labal>key_state_MAX)
     menu.labal =key_state_MAX;
   menu.labal -=key_state[1];//��
   if(menu.labal< 0)
     menu.labal =0;
   //���
   GUI_GotoXY(36,0);
   GUI_DispDec(menu.labal, 2);
   //�Ӽ�
   menu.var=0;
   menu.var -=key_state[2];//��
   menu.var +=key_state[3];//��
   //�˵��仯
   if(menu.labal==0||menu.labal==1)
   {    
      //��һ���˵�
      if(key_state[4]==1&&menu.labal==0)
      {
        menu.menu_e--;
        if(menu.menu_e <0)
          menu.menu_e=0;
        else
          OLED_Clear();
      }
      //��һ���˵�
      if(key_state[4]==1&&menu.labal==1)
      {
        menu.menu_e++;
        if(menu.menu_e >MENU_MAX)
          menu.menu_e=MENU_MAX;
        else
          OLED_Clear();
      }
   }
   //�˵�
   if(menu.menu_e==0)
   {
      UI_menu_1();
   }
   else if(menu.menu_e==1)
   {
      UI_menu_2();
   }
   else 
   {
      UI_menu_3();
   }
 
   //
   OLED_Updata();  
}  



void UI_menu_1(void)
{  
   int16_t labal[8];
   for(int16_t n=0; n<8; n++)
   {
        labal[n] =0;
   }
   labal[menu.labal] =menu.var;
   //����
   GUI_GotoXY(0,0);
   GUI_DispString("MENU1-"); 
   //��
   GUI_GotoXY(96,8*7);
   GUI_DispString("1NEXT");
   //����
   GUI_GotoXY(2,8*2);
   GUI_DispString("2 ");
   GUI_DispDecShift(2+labal[2], 4, 1);
   
   GUI_GotoXY(2,8*3);
   GUI_DispString("3 ");
   GUI_DispDecShift(2+labal[3], 4, 1);
   
   GUI_GotoXY(2,8*4);
   GUI_DispString("4 ");
   GUI_DispDecShift(2+labal[4], 4, 1);
   
   GUI_GotoXY(66,8*2);
   GUI_DispString("5 ");
   GUI_DispDecShift(2+labal[5], 4, 1);
   
   GUI_GotoXY(66,8*3);
   GUI_DispString("6 ");
   GUI_DispDecShift(2+labal[6], 4, 1);
   
   GUI_GotoXY(66,8*4);
   GUI_DispString("7 ");
   GUI_DispDecShift(2+labal[7], 4, 1);
}
void UI_menu_2(void)
{    
   int16_t labal[8];
   for(int16_t n=0; n<8; n++)
   {
        labal[n] =0;
   }
   labal[menu.labal] =menu.var;
   //����
   GUI_GotoXY(0,0);
   GUI_DispString("MENU2-");
   //��
   GUI_GotoXY(0,8*7);
   GUI_DispString("0LAST");
   //��
   GUI_GotoXY(96,8*7);
   GUI_DispString("1NEXT");
   //����
   GUI_GotoXY(2,8*2);
   GUI_DispString("2 ");
   GUI_DispDecShift(2+labal[2], 4, 1);
   
   GUI_GotoXY(2,8*3);
   GUI_DispString("3 ");
   GUI_DispDecShift(2+labal[3], 4, 1);
   
   GUI_GotoXY(2,8*4);
   GUI_DispString("4 ");
   GUI_DispDecShift(2+labal[4], 4, 1);
   
   GUI_GotoXY(66,8*2);
   GUI_DispString("5 ");
   GUI_DispDecShift(2+labal[5], 4, 1);
   
   GUI_GotoXY(66,8*3);
   GUI_DispString("6 ");
   GUI_DispDecShift(2+labal[6], 4, 1);
   
   GUI_GotoXY(66,8*4);
   GUI_DispString("7 ");
   GUI_DispDecShift(2+labal[7], 4, 1);
   
}
void UI_menu_3(void)
{  
   int16_t labal[8];
   for(int16_t n=0; n<8; n++)
   {
        labal[n] =0;
   }
   labal[menu.labal] =menu.var;
   //����
   GUI_GotoXY(0,0);
   GUI_DispString("MENU3-");
   //��
   GUI_GotoXY(0,8*7);
   GUI_DispString("0LAST");
   //����
   GUI_GotoXY(2,8*2);
   GUI_DispString("2 ");
   GUI_DispDecShift(2+labal[2], 4, 1);
   
   GUI_GotoXY(2,8*3);
   GUI_DispString("3 ");
   GUI_DispDecShift(2+labal[3], 4, 1);
   
   GUI_GotoXY(2,8*4);
   GUI_DispString("4 ");
   GUI_DispDecShift(2+labal[4], 4, 1);
   
   GUI_GotoXY(66,8*2);
   GUI_DispString("5 ");
   GUI_DispDecShift(2+labal[5], 4, 1);
   
   GUI_GotoXY(66,8*3);
   GUI_DispString("6 ");
   GUI_DispDecShift(2+labal[6], 4, 1);
   
   GUI_GotoXY(66,8*4);
   GUI_DispString("7 ");
   GUI_DispDecShift(2+labal[7], 4, 1);  
}

   





