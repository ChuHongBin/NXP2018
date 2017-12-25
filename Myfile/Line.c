#include "Line.h"
#include "camera.h"
#include "main.h"

void                  Handle_Image                  (void);
void                  turnImage                     (void);
inline ImageColor     GetPiexl                      (int16_t x, int16_t y);
void                  SetPixel                      (int16_t x, int16_t y, ImageColor col);


ALIGN4      uint8_t tImage[CAMER_SIZE];
            uint8_t *pImage;
          
ALIGN4	    int16_t LeftLine	[IMAGE_HEIGHT];
ALIGN4	    int16_t RightLine	[IMAGE_HEIGHT];
ALIGN4	    int16_t MiddleLine	[IMAGE_HEIGHT];
int16_t		LeftLineCnt			= 0;
int16_t		RightLineCnt		= 0;
int16_t		MiddleLineCnt		= 0;

//ͼ����
void Handle_Image(void)
{
    pImage = ImageData;
    //ͼ��ת
    turnImage();
}

//ȡ�� 
inline ImageColor GetPiexl(int16_t x, int16_t y)
{
        ImageColor ret = Image_ColorRode; 
        if ((tImage[y * IMAGE_WIDTH / 8 + x / 8] & (0x80 >> (x % 8))) == 0)
        {
            ret = Image_ColorRode;
        }
        else
        {
            ret = Image_ColorSide;
        }

        return ret;
}
//д��
void SetPixel(int16_t x, int16_t y, ImageColor col)
{
	if (col == Image_ColorRode)
	{
		tImage[y * IMAGE_WIDTH / 8 + x / 8] &= (uint8_t)(~(0x80 >> (x % 8)));
	}
	else
	{
		tImage[y * IMAGE_WIDTH / 8 + x / 8] |= (uint8_t)(0x80 >> (x % 8));
	}
}
//ͼ��ת
void turnImage(void)
{
    for(int16_t n = 0; n < IMAGE_HEIGHT; n++)
	{
		arm_copy_q7((q7_t*)((pImage + (n * (IMAGE_WIDTH  / 8)))), 
				(q7_t*)(tImage + (((IMAGE_HEIGHT - 1) - n) * (IMAGE_WIDTH  / 8))), 
				IMAGE_WIDTH / 8);
	}

}




