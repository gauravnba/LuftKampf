#pragma once

#include "baseTypes.h"

class Enemy
{
	Enemy(float32_t initPosX, float32_t initPosY, float32_t initVelX, float32_t initVelY, int32_t mEnemyID);
	~Enemy() {};

	void update(float32_t seconds);
	void render();
	void checkCollisions();
};