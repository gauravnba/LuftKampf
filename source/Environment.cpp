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
	if (sInstance == nullptr)
	{
		sInstance = new Environment();
	}

	return sInstance;
}

void Environment::initBackground()
{
	mBackgroundSprite	= SpriteManager::GetInstance()->addSprite(ENVIRONMENT_WIDTH, ENVIRONMENT_HEIGHT, "assets\\Environment.png");
	//mCloudSprite		=
}

void Environment::initBounds()
{
	mStratosSprite  = SpriteManager::GetInstance()->addSprite(ENVIRONMENT_WIDTH, BOUNDS_HEIGHT, "assets\\Stratosphere.png");
	mSeaSprite		= SpriteManager::GetInstance()->addSprite(ENVIRONMENT_WIDTH, BOUNDS_HEIGHT, "assets\\Sea.png");

	mStratosSprite->setPosY(BOUNDS_Y_POSITION);
	mSeaSprite->setPosY(-BOUNDS_Y_POSITION);
}

void Environment::update(float32_t deltaTime)
{
	mBackgroundSprite->setPosX(Player::GetInstance()->getPosX());
	mStratosSprite->setPosX(Player::GetInstance()->getPosX());
	mSeaSprite->setPosX(Player::GetInstance()->getPosX());
}