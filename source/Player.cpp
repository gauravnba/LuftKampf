//for debug
#include <windows.h>
#include "SpriteManager.h"
#include "InputManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include <math.h>

Player* Player::sInstance = nullptr;

Player* Player::CreateInstance()
{
	if (sInstance == nullptr)
		sInstance = new Player;

	return sInstance;
}

void Player::init()
{
	mPlayerSprite = SpriteManager::GetInstance()->addSprite(PLAYER_WIDTH, PLAYER_HEIGHT, "assets\\Airplane.png");
}

void Player::update(float32_t deltaTime)
{
	bool* lPlayerInputs = InputManager::GetInstance()->getInputs();

	if (lPlayerInputs[INPUT_THRUST])
	{
		mIsThrusting = true;
	}
	else
	{
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
			mSkipFire += deltaTime;
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


	if (mPlayerVelocityX > 0)
	{
		mPlayerVelocityX -= (mDrag * deltaTime);
	}

	if (mPlayerVelocityX < 0)
	{
		mPlayerVelocityX += (mDrag * deltaTime);
	}

	if (mIsThrusting && (mPlayerVelocityX <= mMaxVelocity) && (mPlayerVelocityY <= mMaxVelocity))
	{
		mPlayerVelocityX += (mAcceleration * cos(mPlayerRotation)) * deltaTime;
		mPlayerVelocityY += (mAcceleration * sin(mPlayerRotation)) * deltaTime;

		char debug[256];
		sprintf(debug, "\nplayerVelX: %f\nplayerVelY: %f\n", mPlayerVelocityX, mPlayerVelocityY);

		OutputDebugString(debug);
	}

	mPosX += mPlayerVelocityX * deltaTime;
	mPosY += mPlayerVelocityY * deltaTime;

	mPlayerSprite->setPosX(mPosX);
	mPlayerSprite->setPosY(mPosY);
	mPlayerSprite->setRotation(mPlayerRotation);
}

void Player::shutdown()
{
	delete sInstance;
}