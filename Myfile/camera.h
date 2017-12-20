#ifndef _CAMERA_H__
#define _CAMERA_H__

#include "common.h"
#include "include.h"


//一级缓存
extern uint8_t CameraBuff[];
//二级缓存
extern uint8_t CameraData[];
//解压后的图像
extern uint8_t ImageData[];

//初始化摄像头
uint8_t Camera_Init(void);
//获取图像
void Camera_Get_Image(void);


#endif








