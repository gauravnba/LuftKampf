#include "GameSprites.h"

GameSprites::GameSprites(int32_t width, int32_t height, int32_t ID, int32_t index)
{
	mWidth = width;
	mHeight = height;
	mId = ID;
	zIndex = index;
}