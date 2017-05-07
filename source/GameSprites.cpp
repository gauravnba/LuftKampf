#include "GameSprites.h"

GameSprites::GameSprites(int width, int height, int ID, int index)
{
	mWidth = width;
	mHeight = height;
	mId = ID;
	zIndex = index;
}

void GameSprites::setRotation(float32_t rotateAngle)
{
	mRotation = rotateAngle;
}