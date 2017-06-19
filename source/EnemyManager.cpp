#include <math.h>
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "RandomNumberGenerator.h"
#include "Game.h"
#include "Environment.h"
#include "CollisionManager.h"
#include <time.h>

EnemyManager* EnemyManager::sInstance = nullptr;

EnemyManager* EnemyManager::CreateInstance()
{
	if (!sInstance)
	{
		sInstance = new EnemyManager();
	}

	return sInstance;
}

void EnemyManager::createEnemy()
{
	float32_t playerPosX = Player::GetInstance()->getPosX();
	float32_t playerPosY = Player::GetInstance()->getPosY();

	int32_t	xPosition = getRangedRandom(0, 1);
	int32_t yPosition = getRangedRandom(0, 1);

	float32_t initPosX;
	float32_t initPosY;

	if (xPosition)
	{
		initPosX = getRangedRandom((float32_t)PLAYER_WIDTH, (playerPosX + CGame::mScreenWidth)); // , (playerPosX + (CLOUDS_X_POSITION / 2)));
	}
	else
	{
		initPosX = getRangedRandom((float32_t)-PLAYER_WIDTH, (playerPosX - CGame::mScreenWidth)); // , (playerPosX - (CLOUDS_X_POSITION / 2)));
	}
	
	if (yPosition)
	{
		initPosY = getRangedRandom((float32_t)PLAYER_HEIGHT, (playerPosY + CGame::mScreenHeight)); // , (playerPosY + (ENVIRONMENT_HEIGHT / 2)));
	}
	else
	{
		initPosY = getRangedRandom((float32_t)-PLAYER_HEIGHT, (playerPosY - CGame::mScreenHeight)); // , (playerPosY - (ENVIRONMENT_HEIGHT / 2)));
	}

	float32_t rotationAngle = getRangedRandom(0.0f,FULL_CIRCLE);

	mListofEnemies.push_back(new Enemy(initPosX, initPosY, rotationAngle, mListofEnemies.size()));
}

void EnemyManager::updateEnemies(float32_t deltaTime)
{
	//Partition the Enemies marked for destruction and then remove them.
	uint32_t numEnemies = mListofEnemies.size();
	uint32_t destroyAfterThis = numEnemies;
	for (uint32_t i = 0; i < destroyAfterThis; ++i)
	{
		if (mListofEnemies[i]->isMarkedForDestruction())
		{
			//Get index of the first event from the send that is not expired.
			while ((destroyAfterThis > i) && (mListofEnemies[--destroyAfterThis]->isMarkedForDestruction()));
			Enemy* temp = mListofEnemies[i];
			mListofEnemies[i] = mListofEnemies[destroyAfterThis];
			mListofEnemies[destroyAfterThis] = temp;
		}
	}
	mListofEnemies.erase(mListofEnemies.begin() + destroyAfterThis, mListofEnemies.end());

	if (mListofEnemies.size() == 0)
	{
		mNoEnemiesPresent = true;
	}

	if ((mListofEnemies.size() <= 5) && mNoEnemiesPresent)
	{
		createEnemy();
		if (mListofEnemies.size() == 5)
		{
			mNoEnemiesPresent = false;
		}
	}

	for (uint32_t i = 0; i < mListofEnemies.size(); i++)
	{
		mListofEnemies[i]->update(deltaTime);
	}
}