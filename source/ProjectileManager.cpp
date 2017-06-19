#include <string.h>
#include <algorithm>
#include "ProjectileManager.h"
#include "Player.h"

ProjectileManager* ProjectileManager::sInstance = nullptr;

ProjectileManager* ProjectileManager::CreateInstance()
{
	if (!sInstance)
	{
		sInstance = new ProjectileManager();
	}

	return sInstance;
}

void ProjectileManager::createProjectile(float32_t initPosX,float32_t initPosY, float32_t velX, float32_t velY, int32_t mID)
{
	mListOfProjectiles.push_back(new Projectile(initPosX, initPosY, velX, velY, mID));
}

void ProjectileManager::updateProjectiles(float32_t seconds)
{
	//Partition the projectiles marked for destruction and then remove them.
	uint32_t numProjectiles = mListOfProjectiles.size();
	uint32_t destroyAfterThis = numProjectiles;
	for (uint32_t i = 0; i < destroyAfterThis; ++i)
	{
		if (mListOfProjectiles[i]->isMarkedToDestroy())
		{
			//Get index of the first event from the send that is not expired.
			while ((destroyAfterThis> i) && (mListOfProjectiles[--destroyAfterThis]->isMarkedToDestroy()));
			Projectile* temp = mListOfProjectiles[i];
			mListOfProjectiles[i] = mListOfProjectiles[destroyAfterThis];
			mListOfProjectiles[destroyAfterThis] = temp;
		}
	}

	mListOfProjectiles.erase(mListOfProjectiles.begin() + destroyAfterThis, mListOfProjectiles.end());

	for (uint32_t i = 0; i < mListOfProjectiles.size(); i++)
	{
		float32_t projectilePosX = mListOfProjectiles[i]->getPosX();
		float32_t projectilePosY = mListOfProjectiles[i]->getPosY();

		if (projectilePosX > (Player::GetInstance()->getPosX() + MAX_TRAVERSAL_OFFSET_X) ||
			projectilePosX < (Player::GetInstance()->getPosX() - MAX_TRAVERSAL_OFFSET_X) ||
			projectilePosY > (Player::GetInstance()->getPosY() + MAX_TRAVERSAL_OFFSET_Y) ||
			projectilePosY < (Player::GetInstance()->getPosY() - MAX_TRAVERSAL_OFFSET_Y))
		{
			mListOfProjectiles[i]->markToDestroy();
		}
		else
		{
			mListOfProjectiles[i]->update(seconds);
		}
	}
}

void ProjectileManager::renderProjectiles()
{
	for (uint32_t i = 0; i < mListOfProjectiles.size(); i++)
	{
		mListOfProjectiles[i]->render();
	}
}