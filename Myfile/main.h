#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"

//摄像头定义

#define IMAGE_BLACK		(uint8_t)0
#define IMAGE_WHITE		(uint8_t)0xff

#define IMAGE_HEIGHT    60
#define IMAGE_WIDTH     80
#define CAMER_SIZE      IMAGE_HEIGHT*IMAGE_WIDTH/8 

#define IMAGE_HEIGHT_BAND		(IMAGE_HEIGHT-1)
#define IMAGE_WIDTH_BAND		(IMAGE_WIDTH-1)



//定义全局的变量

typedef struct
{
	bool CameraInit;
	bool SDInit;
}InitOK_t;



#endif



