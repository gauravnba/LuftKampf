//for debug
#include <windows.h>
#include "SpriteManager.h"
#include "InputManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include <math.h>
#include "EnemyManager.h"
#include "ProjectileManager.h"

Player* Player::sInstance = nullptr;

Player* Player::CreateInstance()
{
	if (!sInstance)
		sInstance = new Player;

	return sInstance;
}

void Player::init()
{
	mPlayerSprite = SpriteManager::GetInstance()->addSprite(PLAYER_WIDTH, PLAYER_HEIGHT, "assets\\Airplane.png", 2);
	mThrusterSprite = SpriteManager::GetInstance()->addSprite(THRUST_SPRITE_SIZE, THRUST_SPRITE_SIZE, "assets\\Thrust.png", 2);
	mThrusterSprite->setDraw(false);
}

void Player::update(float32_t deltaTime)
{
	bool* lPlayerInputs = InputManager::GetInstance()->getInputs();

	if (lPlayerInputs[INPUT_THRUST])
	{
		mIsThrusting = true;
		mThrusterSprite->setDraw(true);
		mThrusterSprite->setRotation(mPlayerRotation);
		mThrusterSprite->setPosX(mPosX - (((PLAYER_WIDTH + THRUST_SPRITE_SIZE)/2)*cos(mPlayerRotation)));
		mThrusterSprite->setPosY(mPosY - (((PLAYER_HEIGHT+ THRUST_SPRITE_SIZE)/2)*sin(mPlayerRotation)));
	}
	else
	{
		mThrusterSprite->setDraw(false);
		mIsThrusting = false;
	}

	if (lPlayerInputs[INPUT_LEFT])
	{
		if (lPlayerInputs[INPUT_THRUST])
		{
			mPlayerRotation += ROTATE_UNDER_THRUST * deltaTime;
		}
		else
		{
			mPlayerRotation += ROTATE * deltaTime;
		}

		//Clamp rotation to 360 degrees.
		if (mPlayerRotation >= 6.28318f)
			mPlayerRotation -= 6.28318f;
		else if (mPlayerRotation <= -6.28318f)
			mPlayerRotation += 6.28318f;
	}

	if (lPlayerInputs[INPUT_RIGHT])
	{
		if (lPlayerInputs[INPUT_THRUST])
			mPlayerRotation -= ROTATE_UNDER_THRUST  * deltaTime;
		else
			mPlayerRotation -= ROTATE * deltaTime;

		//Clamp rotation to 360 degrees.
		if (mPlayerRotation >= 6.28318f)
			mPlayerRotation -= 6.28318f;
		else if (mPlayerRotation <= -6.28318f)
			mPlayerRotation += 6.28318f;
	}

	if (lPlayerInputs[INPUT_FIRE])
	{

		if (mSkipFire > 0.09f)
		{
			float32_t mProjectileVelocityX = (mPlayerVelocityX + (mProjectileVel*cos(mPlayerRotation)));
			float32_t mProjectileVelocityY = (mPlayerVelocityY + (mProjectileVel*sin(mPlayerRotation)));

			ProjectileManager::GetInstance()->createProjectile(	mPosX + ((PLAYER_WIDTH/2)*cos(mPlayerRotation)),
																mPosY + ((PLAYER_HEIGHT/2)*sin(mPlayerRotation)),
																mProjectileVelocityX,
																mProjectileVelocityY,
																PLAYER_PROJECTILE_ID);
			
			mSkipFire = 0;
		}
		else
		{
			mSkipFire += deltaTime;
		}
	}

	updatePosition(deltaTime);
}

void Player::updatePosition(float32_t deltaTime)
{
	//Clamp player to the bounds of the environment.
	if (mPosY <= -1440)
	{
		mPosY = -1440;
		mPlayerVelocityY = 0;
	}
	if (mPosY >= 1440)
	{
		mPosY = 1440;
		mPlayerVelocityY = 0;
	}

	//apply Gravity
	mPlayerVelocityY -= (mGravity * deltaTime);

	//Apply drag to player
	if (mPlayerVelocityX > 0)
	{
		mPlayerVelocityX -= (mDrag * deltaTime);
	}

	if (mPlayerVelocityX < 0)
	{
		mPlayerVelocityX += (mDrag * deltaTime);
	}

	//Use thrusters
	if (mIsThrusting && (mPlayerVelocityX <= mMaxVelocity) && (mPlayerVelocityY <= mMaxVelocity))
	{
		mPlayerVelocityX += (mAcceleration * cos(mPlayerRotation)) * deltaTime;
		mPlayerVelocityY += (mAcceleration * sin(mPlayerRotation)) * deltaTime;
	}

	//Set position in frame
	mPosX += mPlayerVelocityX * deltaTime;
	mPosY += mPlayerVelocityY * deltaTime;

	//Set Sprite position.
	mPlayerSprite->setPosX(mPosX);
	mPlayerSprite->setPosY(mPosY);
	mPlayerSprite->setRotation(mPlayerRotation);
}

void Player::shutdown()
{
	delete sInstance;
}

void Player::damagePlayer(int32_t damage)
{
	mPlayerHealth -= damage;
}
