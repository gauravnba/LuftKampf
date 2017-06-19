#pragma once

#include "baseTypes.h"

class GameSprites 
{
public:
	GameSprites() {};
	GameSprites(int32_t width, int32_t height, int32_t ID, int32_t zIndex);
	~GameSprites() {};
	int32_t	getWidth() { return mWidth; };
	int32_t	getHeight() { return mHeight; };
	int32_t getSpriteID() { return mId; };
	int32_t getZIndex() { return zIndex; };

	void setPosX(float32_t posX) { mPosX = posX; };
	void setPosY(float32_t posY) { mPosY = posY; };
	float32_t getPosX() { return mPosX; };
	float32_t getposY() { return mPosY; };

	void GameSprites::setRotation(float32_t rotateAngle) { mRotation = rotateAngle; };
	float32_t getRotation() { return mRotation; };

	void setDraw(bool_t draw) { mToDraw = draw; };
	bool_t getDraw() { return mToDraw; };

private:
	int32_t mWidth;
	int32_t mHeight;
	int32_t zIndex;
	float32_t mRotation = 0.0f;
	float32_t mPosX		= 0.0f;
	float32_t mPosY		= 0.0f;
	int32_t mId;
	bool_t	mToDraw		= true;
};