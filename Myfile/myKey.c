#include "myKey.h"

#define down  0
#define up    1

void         myKey_init         (void);

void         key_get_status     (void);

int16_t      key_win            (int16_t key);

int16_t      key_check_status   (int16_t key);

void         KEY_IRQHandler     (void);

//���ź�              
PTXn_e key_gpio[8] = {PTA15, PTA17, PTA8, PTA16, PTA9, 
                      PTC7, PTC8, PTC9};
                     //��  ����  �� �� ����  ����  ��
                     //1, 2, 3

int16_t gpio_MAX = 8;
int16_t key_status[12];

void myKey_init(void)
{   
    int key =0;
    for(key=0;key<gpio_MAX;key++)
    {
        gpio_init(key_gpio[key], GPI, 0);
    //    port_init_NoALT(key_gpio[key], PULLUP);         //���ָ��ò��䣬�����ı�����ѡ��
    }  
    /*
    pit_init_ms(PIT1, 10);
    //���ж�
    set_vector_handler(PIT1_VECTORn ,KEY_IRQHandler);      //
    enable_irq (PIT1_IRQn);                                 //ʹ��PIT1�ж�
    */
}
//��ȡȫ������״̬
void key_get_status(void)
{
  int16_t key=0;
   
  //״̬λ��ʼ����  
  for(key=0; key<gpio_MAX; key++)
  {
    key_status[key]=0;
  }
  //����
  for(key=0; key<5; key++)
  {
    key_status[key]=key_check_status(key);   
  }
  //DIP
  for(key=5; key<gpio_MAX; key++)
  {
    key_status[key]=key_win(key);
  }
}
//��ȡkey״̬��������ʱ������
int16_t key_win(int16_t key)
{
    if(gpio_get(key_gpio[key]) == down)
    {
        return 1;
    }
    return 0;
}
//���key״̬������ʱ������
int16_t key_check_status(int16_t key)
{
    if(key_win(key) == 1)
    {
        DELAY_MS(120);
        if( key_win(key) == 1)
        {
            return 1;
        }
    }
    return 0;
}
//�����ж�
void KEY_IRQHandler(void)
{


}


