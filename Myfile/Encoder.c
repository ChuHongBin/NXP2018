#include "Encoder.h"



int16_t Right_val;            //�ұ���������ֵ
int16_t Left_val;             //�����������ֵ
int16_t tms =5;          //����������ʱ��(s)
int16_t count = 0;
void PIT0_IRQHandler(void);
//��������ʼ��
void encoder_Init(void)
{
//    ftm_quad_init(FTM1);                                    //��߱�����
//    ftm_quad_init(FTM2);                                    //�ұ߱�����
    pit_init_ms(PIT0, tms);                      //��ʼ��PIT0����ʱʱ��Ϊ�� ts*1000(ms)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //������
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�
}

//�������������
void PIT0_IRQHandler(void)
{
//   count =- ftm_quad_get(FTM1);    //��ȡFTM �������� ��������(������ʾ������)
//   count = ftm_quad_get(FTM2);    //��ȡFTM �������� ��������(������ʾ������)

    
//    ftm_quad_clean(FTM1);              //�������
//    ftm_quad_clean(FTM2);              //�������
    
        
    
    PIT_Flag_Clear(PIT0);              //���жϱ�־λ

}
