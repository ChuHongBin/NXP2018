#include "common.h"
#include "include.h"
#include "MK60_dma.h"
#include "SCAR_OLED.h"		
#include "camera.h"
#include "main.h"
#include "Motor.h"
#include "Debug.h"
#include "Encoder.h"
#include "Route.h"
#include "myKey.h"


int Camera_init = 0;


void  main(void)
{  
    InitOK_t Init = {true, true};
    //��ʼ������
    myKey_init();
    //��ʼ�����
    //��ʼ�����
    //��ʼ��OLED
    GUI_Init(); 
#if Camera_init
    //��ʼ������ͷ
    if(Camera_Init()){
       Init.CameraInit =false; 
       GUI_DispString("CameraInit false"); 
       OLED_Updata();
    }
    //��ʼ��SD��
    while(1){
        //��ʼ�ɼ�ͼ��
        Camera_Get_Image();      
    }
#else
    while(1){
     Debug(); 
    }
#endif    
}

