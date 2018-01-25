#include "camera.h"
#include "stdio.h"
#include "include.h"



//直接缓存
ALIGN4 uint8_t CameraBuff[CAMERA_SIZE] = { 0x00 };
//二级缓存
ALIGN4 uint8_t CameraData[CAMERA_SIZE] = { 0x00 };
//解压图像
ALIGN4 uint8_t ImageData[CAMERA_SIZE] = { 0x00 };

bool ImageStatus = false;
 
//声明中断函数
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void DMA1_IRQHandler();
void DMA_Init(DMA_CHn CHn, uint8_t *SADDR, uint8_t *DADDR);


///初始化摄像头
//返回【0】正确 
uint8_t Camera_Init(void)
{ 
    if(!camera_init(CameraBuff))
    {
     //传输函数
     DMA_Init(DMA_CH1, CameraBuff, CameraData);
     //配置摄像头中断服务函数
     set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //设置PORTA的中断服务函数为 PORTA_IRQHandler
     set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //设置DMA0的中断服务函数为 DMA0_IRQHandler
     //传输中断
     set_vector_handler(DMA1_VECTORn ,DMA1_IRQHandler);      //设置DMA1的中断服务函数为 DMA1_IRQHandler    
     //优先级
     NVIC_SetPriorityGrouping((uint32)0x4);           
     NVIC_SetPriority(PORTA_IRQn,0);         //配置优先级
     NVIC_SetPriority(DMA0_IRQn,1);          //配置优先级
     NVIC_SetPriority(DMA1_IRQn,2);          //配置优先级
     NVIC_SetPriority(PIT0_VECTORn,3);       //配置优先级
     //开始采集图像
     camera_get_img();
     return 0;
  }
  return 1;  
}
//判断是否完成采集图像
void Camera_Get_Image(void){
    
    //等待采集成功
    while(!ImageStatus);
    
    ImageStatus = false;
    //开始采集图像
    camera_get_img();   
    //复制
    arm_copy_q7((q7_t*)CameraData, (q7_t*)ImageData, CAMERA_SIZE);    
}
///DMA传输
// DMA_CHn    通道号（DMA_CH0 ~ DMA_CH15）
// SADDR      源地址
// DADDR      目的地址
void DMA_Init(DMA_CHn CHn, uint8_t *SADDR, uint8_t *DADDR)
{
    // DMA_BYTEn  每次DMA传输1个字节数
    DMA_BYTEn byten = DMA_BYTE1;
    uint16_t BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //计算传输字节数
    uint32_t count = 600/BYTEs;   
    // cfg        DMA传输配置，从DMA_cfg里选择
    uint32_t cfg =  DADDR_RECOVER;  //恢复目标地址
    //DMA 寄存器 配置
   
    /* 开启时钟 */
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //打开DMA模块时钟
#if defined(MK60DZ10)
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //打开DMA多路复用器时钟
#elif defined(MK60F15)
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX0_MASK;                    //打开DMA多路复用器时钟
#endif
    /* 配置 DMA 通道 的 传输控制块 TCD ( Transfer Control Descriptor ) */
    DMA_SADDR(CHn) =    (uint32_t)SADDR;                      // 设置  源地址
    DMA_DADDR(CHn) =    (uint32_t)DADDR;                      // 设置目的地址
    DMA_SOFF(CHn)  =    BYTEs;                              // 设置源地址偏移 
    DMA_DOFF(CHn)  =    BYTEs;                              // 每次传输后，目的地址加 byten
    DMA_ATTR(CHn)  =    (0
                         | DMA_ATTR_SMOD(0x0)               // 源地址模数禁止  Source address modulo feature is disabled
                         | DMA_ATTR_SSIZE(byten)            // 源数据位宽 ：DMA_BYTEn  。    SSIZE = 0 -> 8-bit ，SSIZE = 1 -> 16-bit ，SSIZE = 2 -> 32-bit ，SSIZE = 4 -> 16-byte
                         | DMA_ATTR_DMOD(0x0)               // 目标地址模数禁止
                         | DMA_ATTR_DSIZE(byten)            // 目标数据位宽 ：DMA_BYTEn  。  设置参考  SSIZE
                        );
    DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(1);   //当前主循环次数
    DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKNO_BITER(1);   //起始主循环次数
                                
    DMA_CR &= ~DMA_CR_EMLM_MASK;                                // CR[EMLM] = 0

    //当CR[EMLM] = 0 时: 副循环
    DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(count); // 通道字节

    /* 配置 DMA 传输结束后的操作 */
    DMA_SLAST(CHn)      =   DMA_SLAST_SLAST(-600);                              //调整  源地址的附加值,主循环结束后恢复  源地址
    DMA_DLAST_SGA(CHn)  =   (uint32)( (cfg & DADDR_KEEPON ) == 0 ? (-count)  : 0 ); //调整目的地址的附加值,主循环结束后恢复目的地址或者保持地址
    DMA_CSR(CHn)        =   (0
                             | DMA_CSR_BWC(3)               //带宽控制,每读一次，eDMA 引擎停止 8 个周期（0不停止；1保留；2停止4周期；3停止8周期）                           
                             | DMA_CSR_DREQ_MASK                          
                             | DMA_CSR_INTMAJOR_MASK        //主循环结束后产生中断
                            );
    
    /* 配置 DMA 触发源 */
    DMAMUX_CHCFG_REG(DMAMUX0_BASE_PTR, CHn) = (DMAMUX_CHCFG_SOURCE(DMA_Always_EN1)); //触发通道 
    DMAMUX_CHCFG_REG(DMAMUX0_BASE_PTR, CHn)  &= ~DMAMUX_CHCFG_TRIG_MASK;
    DMAMUX_CHCFG_REG(DMAMUX0_BASE_PTR, CHn) |= DMAMUX_CHCFG_ENBL_MASK;  // Enable routing of DMA request 
    DMA_IRQ_EN(CHn);        //允许DMA通道传输
}



//PORTA中断服务函数
//场中断
void PORTA_IRQHandler()
{
    uint8_t  n = 29;    //引脚号
    uint32_t flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                          //清中断标志位
    n = 29;                                      //场中断
    if(flag & (1 << n))  camera_vsync();        //PTA29触发中断
    
}
//DMA0中断服务函数
//判断
//【开始】 图像采集  
//【结束】 图像采集
void DMA0_IRQHandler()
{
   camera_dma(); 
   //打开DMA1传输 
   DMA_EN(DMA_CH1);
}
//DMA1中断服务函数
//传输结束
void DMA1_IRQHandler()
{   
    //清除通道传输中断标志位
    DMA_IRQ_CLEAN(DMA_CH1);
    //完成标志
    ImageStatus = true;    
}









