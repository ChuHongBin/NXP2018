#ifndef _CAMERA_H__
#define _CAMERA_H__

#include "common.h"
#include "include.h"


//һ������
extern uint8_t CameraBuff[];
//��������
extern uint8_t CameraData[];
//��ѹ���ͼ��
extern uint8_t ImageData[];

//��ʼ������ͷ
uint8_t Camera_Init(void);
//��ȡͼ��
void Camera_Get_Image(void);


#endif








