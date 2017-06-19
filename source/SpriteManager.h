#pragma once

#include "GameSprites.h"
#include "baseTypes.h"

#define MAX_NUM_SPRITES 50

class SpriteManager
{
public:
	static SpriteManager *CreateInstance();
	static SpriteManager *GetInstance() { return sInstance; };
	~SpriteManager() {};

	GameSprites*	addSprite(int32_t quadWidth, int32_t quadHeight, char* spriteFileName, int32_t zDepth);
	void			updateSprites(float32_t seconds);
	void			renderSprites();
	void			shutdown();

private:
	static SpriteManager *sInstance;
	const float32_t RAD2DEG = 180.0f/3.14159f;
	uint32_t mSpriteTextureMap;
	GameSprites* spritePointers[MAX_NUM_SPRITES];

	float32_t mLastUpdateTime;
	float32_t mCurrentTime;

	SpriteManager() {};
};