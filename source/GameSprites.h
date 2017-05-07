#pragma once

#include "baseTypes.h"

class GameSprites 
{
public:
	GameSprites() {};
	GameSprites(int width, int height, int ID, int zIndex);
	~GameSprites() {};
	int32_t	getWidth() { return mWidth; };
	int32_t	getHeight() { return mHeight; };
	int32_t getSpriteID() { return mId; };
	int32_t getZIndex() { return zIndex; };

	void setPosX(float32_t posX) { mPosX = posX; };
	void setPosY(float32_t posY) { mPosY = posY; };
	int32_t getPosX() { return mPosX; };
	int32_t getposY() { return mPosY; };

	void setRotation(float32_t rotationAngle);
	float32_t getRotation() { return mRotation; };

private:
	int32_t mWidth;
	int32_t mHeight;
	int32_t zIndex;
	float32_t mRotation = 0.0f;
	float32_t mPosX		= 0.0f;
	float32_t mPosY		= 0.0f;
	int32_t mId;
};