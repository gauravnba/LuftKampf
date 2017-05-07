#pragma once

#include "baseTypes.h"

#define PLAYER_PROJECTILE_RADIUS 50

class Projectile
{
public:
	Projectile(float32_t initPosX, float32_t initPosY, float32_t initVelX, float32_t initVelY, int32_t mProjectileID);
	~Projectile() {};

	void drawProjectile(float32_t radius, float32_t x, float32_t y, char8_t r, char8_t g, char8_t b);
	void update(float32_t seconds);
	void render();
	void checkCollisions();
	float32_t getPosX() { return mPosX; };
	float32_t getPosY() { return mPosY; };

private:
	float32_t mPosX, mPosY, mVelX, mVelY;
	int32_t mProjectileID; //0 is player projectile, 1 is enemy projectile
};