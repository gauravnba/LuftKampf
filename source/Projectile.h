#pragma once

#include "baseTypes.h"

#define PLAYER_PROJECTILE_RADIUS	50
#define ENEMY_PROJECTILE_RADIUS		30

class Projectile
{
public:
	Projectile(float32_t initPosX, float32_t initPosY, float32_t initVelX, float32_t initVelY, int32_t mProjectileID);
	~Projectile() {};

	void drawProjectile(float32_t radius, float32_t x, float32_t y, int32_t r, int32_t g, int32_t b);
	void update(float32_t seconds);
	void render();
	int32_t projectileID() { return mProjectileID; };

	void markToDestroy();

	float32_t getPosX() { return mPosX; };
	float32_t getPosY() { return mPosY; };
	bool isMarkedToDestroy() { return mMarkedToDestroy; };

private:
	float32_t mPosX, mPosY, mVelX, mVelY;
	int32_t mProjectileID; //0 is player projectile, 1 is enemy projectile
	bool mMarkedToDestroy;
};