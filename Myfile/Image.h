#ifndef __IMAGE_H
#define __IMAGE_H


#include "gui.h"


#define IMAGE_WIDTH		80
#define IMAGE_HEIGHT	60
#define IMAGE_ARIA		(IMAGE_WIDTH * IMAGE_HEIGHT)
#define IMAGE_SIZE		(IMAGE_ARIA / 8)


extern GUI_BITMAP DispImage;

#endif