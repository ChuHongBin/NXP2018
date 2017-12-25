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


void  main(void)
{  
    InitOK_t Init = {true, true};
    //初始化按键
    //初始化舵机
    //初始化电机
    //初始化OLED
    GUI_Init();          
    //初始化摄像头
    if(Camera_Init()){
       Init.CameraInit =false; 
       GUI_DispString("CameraInit false"); 
       OLED_Updata();
    }
    //初始化SD卡
    while(1){
        //开始采集图像
        Camera_Get_Image();      
    }   
}

