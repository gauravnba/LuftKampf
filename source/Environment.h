#pragma once

#include "baseTypes.h"
#include "GameSprites.h"

#define ENVIRONMENT_WIDTH	1280
#define ENVIRONMENT_HEIGHT	3600

#define BOUNDS_Y_POSITION	1620
#define BOUNDS_HEIGHT		420

#define CLOUDS_WIDTH		3840
#define CLOUDS_HEIGHT		720
#define CLOUDS_Y_POSITION	780
#define CLOUDS_X_POSITION	5760

class Environment
{
public:
	static Environment* CreateInstance();
	static Environment* GetInstance() { return sInstance; };
	~Environment();

	void initBackground();
	void initBounds();
	void update();

private:
	Environment() {};
	GameSprites* mBackgroundSprite;
	GameSprites* mStratosSprite;
	GameSprites* mSeaSprite;
	GameSprites* mCloudSprite;
	GameSprites* mCloudSpriteLeft;
	GameSprites* mCloudSpriteRight;

	static Environment* sInstance;
};