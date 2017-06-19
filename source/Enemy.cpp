#include <windows.h>
#include <math.h>
#include "Enemy.h"
#include "SpriteManager.h"
#include "Player.h"
#include "ProjectileManager.h"

Enemy::Enemy(float32_t initPosX, float32_t initPosY, float32_t rotationAngle, int32_t enemyID)
{
	mPosX = initPosX;
	mPosY = initPosY;
	mRotation = rotationAngle;
	mEnemyID = enemyID;

	mEnemySprite = SpriteManager::GetInstance()->addSprite(ENEMY_WIDTH, ENEMY_HEIGHT, "assets\\Enemy.png", 2);

	mEnemyHealth = 100;
	mEnemySprite->setPosX(mPosX);
	mEnemySprite->setPosY(mPosY);
	mEnemySprite->setRotation(mRotation);
	mMarkedForDestruction = false;
}

void Enemy::update(float32_t deltaTime)
{
	mVelocityX = (mVelocity * cos(mRotation)) * deltaTime;
	mVelocityY = (mVelocity * sin(mRotation)) * deltaTime;

	mPosX += mVelocityX;
	mPosY += mVelocityY;

	float32_t vectorToPlayerX = Player::GetInstance()->getPosX() - mPosX;
	float32_t vectorToPlayerY = Player::GetInstance()->getPosY() - mPosY;

	float32_t playerDirection = atan2f(vectorToPlayerY, vectorToPlayerX);

	//Fire at Player
	float32_t angleToPlayer = playerDirection - mRotation;

	if (angleToPlayer < 0.08727f && angleToPlayer > -0.08727f)
	{
		if (mSkipFire > 0.09f)
		{
			float32_t mProjectileVelocityX = mVelocityX + (mProjectileVelocity * cos(mRotation));
			float32_t mProjectileVelocityY = mVelocityY + (mProjectileVelocity * sin(mRotation));

			ProjectileManager::GetInstance()->createProjectile(mPosX + ((ENEMY_WIDTH / 2)*cos(mRotation)),
				mPosY + ((ENEMY_HEIGHT / 2)*sin(mRotation)),
				mProjectileVelocityX,
				mProjectileVelocityY,
				ENEMY_PROJECTILE_ID);

			mSkipFire = 0;
		}
		else
		{
			mSkipFire += deltaTime;
		}
	}

	mRotation += angleToPlayer * (ENEMY_ANGULAR_VELOCITY * deltaTime);

	//Clamp rotation to 360 degrees.
	if (mRotation >= 6.28318f)
		mRotation -= 6.28318f;
	else if (mRotation <= -6.28318f)
		mRotation += 6.28318f;

	mEnemySprite->setPosX(mPosX);
	mEnemySprite->setPosY(mPosY);
	mEnemySprite->setRotation(mRotation);
}

void Enemy::damageEnemy(int32_t damage)
{
	if (mEnemyHealth > 0)
	{
		mEnemyHealth -= damage;
	}
	else
	{
		mMarkedForDestruction = true;
	}
}

float32_t Enemy::getPosX()
{
	return mPosX;
}

float32_t Enemy::getPosY()
{
	return mPosY;
}