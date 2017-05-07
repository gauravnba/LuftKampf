#pragma once

#include "GameSprites.h"

//#define PERPENDICULAR	1.57079f

#define PLAYER_WIDTH	50
#define PLAYER_HEIGHT	50

#define GRAVITY			10

#define INPUT_THRUST	0
#define INPUT_LEFT		1
#define INPUT_RIGHT		2
#define INPUT_FIRE		3

#define ROTATE					4.5f
#define ROTATE_UNDER_THRUST		3.0f
#define PLAYER_PROJECTILE_ID	0

class Player
{
public:
	static Player* CreateInstance();
	static Player* GetInstance() { return sInstance; };
	~Player() {};

	void init();
	void update(float32_t deltaSeconds);
	void render();
	void checkCollisions();
	void reduceVelocity();
	void updatePosition(float32_t deltaSeconds);
	void shutdown();

	float32_t getRotation() { return mPlayerRotation; };
	float32_t getPosX() { return mPosX; };
	float32_t getPosY() { return mPosY; };
	float32_t getVelX() { return mPlayerVelocityX; };
	float32_t getVelY() { return mPlayerVelocityY; };

private:
	static Player* sInstance;
	GameSprites* mPlayerSprite;

	const float32_t	mGravity		= 100.0f;
	const float32_t mDrag			= 50.0f;
	const float32_t mAcceleration	= 800.0f;
	const float32_t mMaxVelocity	= 500.0f;
	const float32_t mProjectileVel	= 1200.0f;

	float32_t	mPosX = 0;
	float32_t	mPosY = 0;

	float32_t	mPlayerRotation		= 1.57079f;
	float32_t	mPlayerVelocityX	= 0;
	float32_t	mPlayerVelocityY	= 0;
	float32_t	mSkipFire			= 0.09f;
	bool_t		mIsThrusting = false;
};