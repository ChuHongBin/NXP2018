#include "image.h"
#include "include.h"
#include "camera.h"

static const GUI_LOGPALETTE ImagePal = 
{
	2,  // Number of entries
	0,  // No transparency
	NULL
};

GUI_BITMAP DispImage = 
{
	IMAGE_WIDTH,
	IMAGE_HEIGHT,
	IMAGE_WIDTH / 8,
	1, // BitsPerPixel
	CameraData,  // Pointer to picture data (indices)
	&ImagePal   // Pointer to palette
};



