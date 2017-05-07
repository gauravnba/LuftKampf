#pragma once

#include "baseTypes.h"
#include "GameSprites.h"

#define ENVIRONMENT_WIDTH	1280
#define ENVIRONMENT_HEIGHT	3600
#define BOUNDS_HEIGHT		420
#define BOUNDS_Y_POSITION	1620

class Environment
{
public:
	static Environment* CreateInstance();
	static Environment* GetInstance() { return sInstance; };
	~Environment();

	void initBackground();
	void initBounds();
	void update(float32_t deltaTime);
	void render();

private:
	Environment() {};
	GameSprites* mBackgroundSprite;
	GameSprites* mStratosSprite;
	GameSprites* mSeaSprite;

	static Environment* sInstance;
};