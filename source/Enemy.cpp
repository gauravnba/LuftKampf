#include <math.h>
#include "Enemy.h"
#include "SpriteManager.h"
#include "Player.h"
#include "ProjectileManager.h"

Enemy::Enemy(float32_t initPosX, float32_t initPosY, float32_t rotationAngle, int32_t enemyID)
{
	mPosX		= initPosX;
	mPosY		= initPosY;
	mRotation	= rotationAngle;
	mEnemyID	= enemyID;

	mEnemySprite = SpriteManager::GetInstance()->addSprite(ENEMY_WIDTH, ENEMY_HEIGHT, "assets\\Enemy.png");

	mEnemySprite->setPosX(mPosX);
	mEnemySprite->setPosY(mPosY);
	mEnemySprite->setRotation(mRotation);
}

void Enemy::update(float32_t deltaTime)
{
	mVelocityX = (mVelocity * cos(mRotation)) * deltaTime;
	mVelocityY = (mVelocity * sin(mRotation)) * deltaTime;

	mPosX -= mVelocityX;
	mPosY -= mVelocityY;
	
	float32_t vectorToPlayerX = Player::GetInstance()->getPosX() - mPosX;
	float32_t vectorToPlayerY = Player::GetInstance()->getPosY() - mPosY;
	float32_t playerDirection = atan2f(vectorToPlayerY, vectorToPlayerX);

	//Rotate towards player
	if (playerDirection > 0.08727f)
	{
		mRotation += ENEMY_ROTATION_ANGLE * deltaTime;
	}
	else if (playerDirection < -0.08727f)
	{
		mRotation -= ENEMY_ROTATION_ANGLE * deltaTime;
	}

	//Fire at Player
	if (playerDirection < 0.08727f && playerDirection > -0.08727f)
	{
		float32_t mProjectileVelocityX = mVelocityX + (mProjectileVelocity * cos(mRotation));
		float32_t mProjectileVelocityY = mVelocityY + (mProjectileVelocity * sin(mRotation));

		ProjectileManager::GetInstance()->createProjectile(	mPosX + ((ENEMY_WIDTH / 2)*cos(mRotation)),
															mPosY + ((ENEMY_HEIGHT / 2)*sin(mRotation)),
															mProjectileVelocityX,
															mProjectileVelocityY,
															PLAYER_PROJECTILE_ID);
	}

	mEnemySprite->setPosX(mPosX);
	mEnemySprite->setPosY(mPosY);
	mEnemySprite->setRotation(mRotation);
}