#include "Projectile.h"

#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "Player.h"

void Projectile::drawProjectile(float32_t radius, float32_t x, float32_t y, int32_t r, int32_t g, int32_t b)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SMOOTH);
	glColor4ub(r, g, b, 0xFF);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(radius / 2.0f);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

Projectile::Projectile(float32_t initPosX, float32_t initPosY, float32_t initVelX, float32_t initVelY, int32_t ID)
{
	mPosX = initPosX;
	mPosY = initPosY;
	mVelX = initVelX;
	mVelY = initVelY;
	mProjectileID = ID;
	mMarkedToDestroy = false;
}

void Projectile::update(float32_t deltaTime)
{
	mPosX += (mVelX * deltaTime);
	mPosY += (mVelY * deltaTime);
}

void Projectile::render()
{
	switch (mProjectileID)
	{
	case 0:
		drawProjectile(PLAYER_PROJECTILE_RADIUS + 5,
			mPosX, mPosY, 216, 132, 39);					//Color value = dull orange

		drawProjectile(PLAYER_PROJECTILE_RADIUS,
			mPosX, mPosY, 255, 255, 255);					//Color value = white
		break;

	case 1:
		drawProjectile(ENEMY_PROJECTILE_RADIUS,
			mPosX, mPosY, 136, 0, 21);						//Color value = brick red
		break;
	}
}

void Projectile::markToDestroy()
{
	mMarkedToDestroy = true;
}