#include <string.h>
#include "ProjectileManager.h"
#include "Player.h"

ProjectileManager* ProjectileManager::sInstance = nullptr;
int32_t ProjectileManager::mNumProjectiles = 0;

ProjectileManager* ProjectileManager::CreateInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new ProjectileManager();
	}

	return sInstance;
}

void ProjectileManager::createProjectile(float32_t initPosX,float32_t initPosY, float32_t velX, float32_t velY, int32_t mID)
{
	mListOfProjectiles.push_back(new Projectile(initPosX, initPosY, velX, velY, mID)); 
	mNumProjectiles++;
}

void ProjectileManager::updateProjectiles(float32_t seconds)
{
	for (int i = 0; i < mNumProjectiles; i++)
	{
		float32_t projectilePosX = mListOfProjectiles[i]->getPosX();
		float32_t projectilePosY = mListOfProjectiles[i]->getPosY();
		float32_t playerPosOffsetX = Player::GetInstance()->getPosX() + MAX_TRAVERSAL_OFFSET_X;
		float32_t playerPosOffsetY = Player::GetInstance()->getPosY() + MAX_TRAVERSAL_OFFSET_Y;

		if (projectilePosX > (Player::GetInstance()->getPosX() + MAX_TRAVERSAL_OFFSET_X) ||
			projectilePosX < (Player::GetInstance()->getPosX() - MAX_TRAVERSAL_OFFSET_X) ||
			projectilePosY > (Player::GetInstance()->getPosY() + MAX_TRAVERSAL_OFFSET_Y) ||
			projectilePosY < (Player::GetInstance()->getPosY() - MAX_TRAVERSAL_OFFSET_Y))
		{
			mListOfProjectiles.erase(mListOfProjectiles.begin() + i);
			mNumProjectiles--;
		}
		else
			mListOfProjectiles[i]->update(seconds);
	}
}

void ProjectileManager::renderProjectiles()
{
	for (int i = 0; i < mNumProjectiles; i++)
	{
		mListOfProjectiles[i]->render();
	}
}