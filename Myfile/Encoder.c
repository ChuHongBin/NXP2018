#include "Encoder.h"



int16_t Right_val;            //右编码器采样值
int16_t Left_val;             //左编码器采样值
int16_t tms =5;          //编码器采样时间(s)
int16_t count = 0;
void PIT0_IRQHandler(void);
//编码器初始化
void encoder_Init(void)
{
//    ftm_quad_init(FTM1);                                    //左边编码器
//    ftm_quad_init(FTM2);                                    //右边编码器
    pit_init_ms(PIT0, tms);                      //初始化PIT0，定时时间为： ts*1000(ms)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //编码器
    enable_irq (PIT0_IRQn);                                 //使能PIT0中断
}

//编码器脉冲计数
void PIT0_IRQHandler(void)
{
//   count =- ftm_quad_get(FTM1);    //获取FTM 正交解码 的脉冲数(负数表示反方向)
//   count = ftm_quad_get(FTM2);    //获取FTM 正交解码 的脉冲数(负数表示反方向)

    
//    ftm_quad_clean(FTM1);              //清除计数
//    ftm_quad_clean(FTM2);              //清除计数
    
        
    
    PIT_Flag_Clear(PIT0);              //清中断标志位

}
