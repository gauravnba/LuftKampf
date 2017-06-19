#include <windows.h>
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <string.h>
#include "glut.h"
#include "SOIL.h"
#include "Player.h"
#include "Environment.h"
#include "SpriteManager.h"

Environment* Environment::sInstance = nullptr;

Environment* Environment::CreateInstance()
{
	if (!sInstance)
	{
		sInstance = new Environment();
	}

	return sInstance;
}

void Environment::initBackground()
{
	mBackgroundSprite	= SpriteManager::GetInstance()->addSprite(ENVIRONMENT_WIDTH, ENVIRONMENT_HEIGHT, "assets\\Environment.png", 0);
	mCloudSprite		= SpriteManager::GetInstance()->addSprite(CLOUDS_WIDTH, CLOUDS_HEIGHT, "assets\\Clouds.png", 1);
	mCloudSpriteLeft	= SpriteManager::GetInstance()->addSprite(CLOUDS_WIDTH, CLOUDS_HEIGHT, "assets\\Clouds.png", 1);
	mCloudSpriteRight	= SpriteManager::GetInstance()->addSprite(CLOUDS_WIDTH, CLOUDS_HEIGHT, "assets\\Clouds.png", 1);

	mCloudSprite->setPosY(CLOUDS_Y_POSITION);

	mCloudSpriteLeft->setPosY(CLOUDS_Y_POSITION);
	mCloudSpriteRight->setPosY(CLOUDS_Y_POSITION);

	mCloudSpriteLeft->setPosX(-CLOUDS_X_POSITION);
	mCloudSpriteRight->setPosX(CLOUDS_X_POSITION);
}

void Environment::initBounds()
{
	mStratosSprite  = SpriteManager::GetInstance()->addSprite(ENVIRONMENT_WIDTH, BOUNDS_HEIGHT, "assets\\Stratosphere.png", 3);
	mSeaSprite		= SpriteManager::GetInstance()->addSprite(ENVIRONMENT_WIDTH, BOUNDS_HEIGHT, "assets\\Sea.png", 3);

	mStratosSprite->setPosY(BOUNDS_Y_POSITION);
	mSeaSprite->setPosY(-BOUNDS_Y_POSITION);
}

void Environment::update()
{
	mBackgroundSprite->setPosX(Player::GetInstance()->getPosX());
	mStratosSprite->setPosX(Player::GetInstance()->getPosX());
	mSeaSprite->setPosX(Player::GetInstance()->getPosX());
}