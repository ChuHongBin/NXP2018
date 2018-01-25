#include "myKey.h"

#define down  0
#define up    1

void         myKey_init         (void);

void         key_get_status     (void);

int16_t      key_win            (int16_t key);

int16_t      key_check_status   (int16_t key);

void         KEY_IRQHandler     (void);

//引脚号              
PTXn_e key_gpio[8] = {PTA15, PTA17, PTA8, PTA16, PTA9, 
                      PTC7, PTC8, PTC9};
                     //上  ，下  ， 左 ，右  ，中  ，
                     //1, 2, 3

int16_t gpio_MAX = 8;
int16_t key_status[12];

void myKey_init(void)
{   
    int key =0;
    for(key=0;key<gpio_MAX;key++)
    {
        gpio_init(key_gpio[key], GPI, 0);
    //    port_init_NoALT(key_gpio[key], PULLUP);         //保持复用不变，仅仅改变配置选项
    }  
    /*
    pit_init_ms(PIT1, 10);
    //开中断
    set_vector_handler(PIT1_VECTORn ,KEY_IRQHandler);      //
    enable_irq (PIT1_IRQn);                                 //使能PIT1中断
    */
}
//获取全部按键状态
void key_get_status(void)
{
  int16_t key=0;
   
  //状态位初始化化  
  for(key=0; key<gpio_MAX; key++)
  {
    key_status[key]=0;
  }
  //按键
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
//获取key状态（不带延时消抖）
int16_t key_win(int16_t key)
{
    if(gpio_get(key_gpio[key]) == down)
    {
        return 1;
    }
    return 0;
}
//检测key状态（带延时消抖）
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
//按键中断
void KEY_IRQHandler(void)
{


}


