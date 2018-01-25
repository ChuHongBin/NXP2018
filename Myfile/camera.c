#include "camera.h"
#include "stdio.h"
#include "include.h"



//ֱ�ӻ���
ALIGN4 uint8_t CameraBuff[CAMERA_SIZE] = { 0x00 };
//��������
ALIGN4 uint8_t CameraData[CAMERA_SIZE] = { 0x00 };
//��ѹͼ��
ALIGN4 uint8_t ImageData[CAMERA_SIZE] = { 0x00 };

bool ImageStatus = false;
 
//�����жϺ���
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void DMA1_IRQHandler();
void DMA_Init(DMA_CHn CHn, uint8_t *SADDR, uint8_t *DADDR);


///��ʼ������ͷ
//���ء�0����ȷ 
uint8_t Camera_Init(void)
{ 
    if(!camera_init(CameraBuff))
    {
     //���亯��
     DMA_Init(DMA_CH1, CameraBuff, CameraData);
     //��������ͷ�жϷ�����
     set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //����PORTA���жϷ�����Ϊ PORTA_IRQHandler
     set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //����DMA0���жϷ�����Ϊ DMA0_IRQHandler
     //�����ж�
     set_vector_handler(DMA1_VECTORn ,DMA1_IRQHandler);      //����DMA1���жϷ�����Ϊ DMA1_IRQHandler    
     //���ȼ�
     NVIC_SetPriorityGrouping((uint32)0x4);           
     NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�
     NVIC_SetPriority(DMA0_IRQn,1);          //�������ȼ�
     NVIC_SetPriority(DMA1_IRQn,2);          //�������ȼ�
     NVIC_SetPriority(PIT0_VECTORn,3);       //�������ȼ�
     //��ʼ�ɼ�ͼ��
     camera_get_img();
     return 0;
  }
  return 1;  
}
//�ж��Ƿ���ɲɼ�ͼ��
void Camera_Get_Image(void){
    
    //�ȴ��ɼ��ɹ�
    while(!ImageStatus);
    
    ImageStatus = false;
    //��ʼ�ɼ�ͼ��
    camera_get_img();   
    //����
    arm_copy_q7((q7_t*)CameraData, (q7_t*)ImageData, CAMERA_SIZE);    
}
///DMA����
// DMA_CHn    ͨ���ţ�DMA_CH0 ~ DMA_CH15��
// SADDR      Դ��ַ
// DADDR      Ŀ�ĵ�ַ
void DMA_Init(DMA_CHn CHn, uint8_t *SADDR, uint8_t *DADDR)
{
    // DMA_BYTEn  ÿ��DMA����1���ֽ���
    DMA_BYTEn byten = DMA_BYTE1;
    uint16_t BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //���㴫���ֽ���
    uint32_t count = 600/BYTEs;   
    // cfg        DMA�������ã���DMA_cfg��ѡ��
    uint32_t cfg =  DADDR_RECOVER;  //�ָ�Ŀ���ַ
    //DMA �Ĵ��� ����
   
    /* ����ʱ�� */
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
#if defined(MK60DZ10)
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //��DMA��·������ʱ��
#elif defined(MK60F15)
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX0_MASK;                    //��DMA��·������ʱ��
#endif
    /* ���� DMA ͨ�� �� ������ƿ� TCD ( Transfer Control Descriptor ) */
    DMA_SADDR(CHn) =    (uint32_t)SADDR;                      // ����  Դ��ַ
    DMA_DADDR(CHn) =    (uint32_t)DADDR;                      // ����Ŀ�ĵ�ַ
    DMA_SOFF(CHn)  =    BYTEs;                              // ����Դ��ַƫ�� 
    DMA_DOFF(CHn)  =    BYTEs;                              // ÿ�δ����Ŀ�ĵ�ַ�� byten
    DMA_ATTR(CHn)  =    (0
                         | DMA_ATTR_SMOD(0x0)               // Դ��ַģ����ֹ  Source address modulo feature is disabled
                         | DMA_ATTR_SSIZE(byten)            // Դ����λ�� ��DMA_BYTEn  ��    SSIZE = 0 -> 8-bit ��SSIZE = 1 -> 16-bit ��SSIZE = 2 -> 32-bit ��SSIZE = 4 -> 16-byte
                         | DMA_ATTR_DMOD(0x0)               // Ŀ���ַģ����ֹ
                         | DMA_ATTR_DSIZE(byten)            // Ŀ������λ�� ��DMA_BYTEn  ��  ���òο�  SSIZE
                        );
    DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(1);   //��ǰ��ѭ������
    DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKNO_BITER(1);   //��ʼ��ѭ������
                                
    DMA_CR &= ~DMA_CR_EMLM_MASK;                                // CR[EMLM] = 0

    //��CR[EMLM] = 0 ʱ: ��ѭ��
    DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(count); // ͨ���ֽ�

    /* ���� DMA ���������Ĳ��� */
    DMA_SLAST(CHn)      =   DMA_SLAST_SLAST(-600);                              //����  Դ��ַ�ĸ���ֵ,��ѭ��������ָ�  Դ��ַ
    DMA_DLAST_SGA(CHn)  =   (uint32)( (cfg & DADDR_KEEPON ) == 0 ? (-count)  : 0 ); //����Ŀ�ĵ�ַ�ĸ���ֵ,��ѭ��������ָ�Ŀ�ĵ�ַ���߱��ֵ�ַ
    DMA_CSR(CHn)        =   (0
                             | DMA_CSR_BWC(3)               //�������,ÿ��һ�Σ�eDMA ����ֹͣ 8 �����ڣ�0��ֹͣ��1������2ֹͣ4���ڣ�3ֹͣ8���ڣ�                           
                             | DMA_CSR_DREQ_MASK                          
                             | DMA_CSR_INTMAJOR_MASK        //��ѭ������������ж�
                            );
    
    /* ���� DMA ����Դ */
    DMAMUX_CHCFG_REG(DMAMUX0_BASE_PTR, CHn) = (DMAMUX_CHCFG_SOURCE(DMA_Always_EN1)); //����ͨ�� 
    DMAMUX_CHCFG_REG(DMAMUX0_BASE_PTR, CHn)  &= ~DMAMUX_CHCFG_TRIG_MASK;
    DMAMUX_CHCFG_REG(DMAMUX0_BASE_PTR, CHn) |= DMAMUX_CHCFG_ENBL_MASK;  // Enable routing of DMA request 
    DMA_IRQ_EN(CHn);        //����DMAͨ������
}



//PORTA�жϷ�����
//���ж�
void PORTA_IRQHandler()
{
    uint8_t  n = 29;    //���ź�
    uint32_t flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                          //���жϱ�־λ
    n = 29;                                      //���ж�
    if(flag & (1 << n))  camera_vsync();        //PTA29�����ж�
    
}
//DMA0�жϷ�����
//�ж�
//����ʼ�� ͼ��ɼ�  
//�������� ͼ��ɼ�
void DMA0_IRQHandler()
{
   camera_dma(); 
   //��DMA1���� 
   DMA_EN(DMA_CH1);
}
//DMA1�жϷ�����
//�������
void DMA1_IRQHandler()
{   
    //���ͨ�������жϱ�־λ
    DMA_IRQ_CLEAN(DMA_CH1);
    //��ɱ�־
    ImageStatus = true;    
}









