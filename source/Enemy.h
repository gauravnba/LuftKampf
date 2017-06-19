#pragma once

#include "baseTypes.h"
#include "GameSprites.h"

#define ENEMY_WIDTH				40
#define ENEMY_HEIGHT			40
#define ENEMY_ANGULAR_VELOCITY	0.85f

#define ENEMY_PROJECTILE_ID		1

class Enemy
{
public:
	Enemy(float32_t initPosX, float32_t initPosY, float32_t rotationAngle, int32_t enemyID);
	~Enemy() {};

	void update(float32_t seconds);
	void damageEnemy(int32_t damage);
	float32_t getPosX();
	float32_t getPosY();
	bool_t isMarkedForDestruction() { return mMarkedForDestruction; };

private:
	float32_t const mVelocity = 300.0f;
	float32_t const	mProjectileVelocity = 1000.0f;

	float32_t	mPosX;
	float32_t	mPosY;
	float32_t	mVelocityX;
	float32_t	mVelocityY;
	float32_t	mRotation;
	int32_t		mEnemyID;
	float32_t	mSkipFire = 0.09f;
	float32_t	mEnemyHealth;
	bool_t		mMarkedForDestruction;
	GameSprites* mEnemySprite;
};