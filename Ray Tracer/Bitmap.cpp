#include "StdAfx.h"
#include "Bitmap.h"
#include "FreeImage.h"


CBitmap::CBitmap(void)
{
}


CBitmap::~CBitmap(void)
{
}

bool CBitmap::init(int width, int hight)
{
	mBitmap = FreeImage_AllocateT(FIT_BITMAP, width, hight, 32);
	return true;
}

bool CBitmap::save(std::string fname)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fname.c_str());
	FreeImage_Save(FIF_BMP, mBitmap, fname.c_str());
	return true;
}

bool CBitmap::setPixel(int x, int y, glm::vec3 color)
{
	RGBQUAD quad;
	quad.rgbRed = color.x * 255;
	quad.rgbGreen = color.y * 255;
	quad.rgbBlue = color.z * 255;

	FreeImage_SetPixelColor(mBitmap, x, y, &quad);
	return true;
}
