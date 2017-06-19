//for debug
#include <windows.h>

#include "baseTypes.h"
#include "CollisionManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "Projectile.h"

CollisionManager* CollisionManager::sInstance = nullptr;

CollisionManager* CollisionManager::CreateInstance()
{
	if (!sInstance)
	{
		sInstance = new CollisionManager();
	}

	return sInstance;
}

void CollisionManager::checkCollisions()
{
	//Check collisions for Player and Enemies
	for (uint32_t i = 0; i < EnemyManager::GetInstance()->mListofEnemies.size(); i++)
	{
		float32_t deltaX = (Player::GetInstance()->getPosX()) - (EnemyManager::GetInstance()->mListofEnemies[i]->getPosX());
		float32_t deltaY = (Player::GetInstance()->getPosY()) - (EnemyManager::GetInstance()->mListofEnemies[i]->getPosY());
		float32_t distanceSquared = (deltaX * deltaX) + (deltaY * deltaY);

		if (distanceSquared < ((PLAYER_WIDTH/2) * (ENEMY_WIDTH/2)) + ((PLAYER_WIDTH/2) * (ENEMY_WIDTH/2)))
		{
			PlaySound("assets\\Audio\\Player_Hit.wav",NULL,SND_ASYNC);
			Player::GetInstance()->damagePlayer(ENEMY_COLLIDE_DAMAGE);
			EnemyManager::GetInstance()->mListofEnemies[i]->damageEnemy(PLAYER_COLLIDE_DAMAGE);
		}
	}

	//Check collisions for Player and Enemy Projectiles
	for (uint32_t i = 0; i < ProjectileManager::GetInstance()->mListOfProjectiles.size(); i++)
	{
		if (ProjectileManager::GetInstance()->mListOfProjectiles[i]->projectileID() == 1)//Check if the projectile is an enemy projectile
		{
			float32_t deltaX = (Player::GetInstance()->getPosX()) - (ProjectileManager::GetInstance()->mListOfProjectiles[i]->getPosX());
			float32_t deltaY = (Player::GetInstance()->getPosY()) - (ProjectileManager::GetInstance()->mListOfProjectiles[i]->getPosY());
			float32_t distanceSquared = (deltaX * deltaX) + (deltaY * deltaY);

			if (distanceSquared < (((PLAYER_WIDTH / 2)*(ENEMY_PROJECTILE_RADIUS))+((PLAYER_WIDTH / 2)*(ENEMY_PROJECTILE_RADIUS))))
			{
				ProjectileManager::GetInstance()->mListOfProjectiles[i]->markToDestroy();
				PlaySound("assets\\Audio\\Player_Hit_Projectile.wav", NULL, SND_ASYNC);
				Player::GetInstance()->damagePlayer(ENEMY_PROJECTILE_DAMAGE);
			}
		}
	}

	//Check collisions for Enemy and Player Projectiles
	for (uint32_t i = 0; i < ProjectileManager::GetInstance()->mListOfProjectiles.size(); i++)
	{
		if (ProjectileManager::GetInstance()->mListOfProjectiles[i]->projectileID() == 0)//Check if the projectile is a player projectile.
		{
			for (uint32_t j = 0; j < EnemyManager::GetInstance()->mListofEnemies.size(); j++)
			{
				float32_t deltaX = (EnemyManager::GetInstance()->mListofEnemies[j]->getPosX())
									- (ProjectileManager::GetInstance()->mListOfProjectiles[i]->getPosX());
				float32_t deltaY = (EnemyManager::GetInstance()->mListofEnemies[j]->getPosY())
									- (ProjectileManager::GetInstance()->mListOfProjectiles[i]->getPosY());
				float32_t distanceSquared = (deltaX * deltaX) + (deltaY * deltaY);

				if (distanceSquared < (((ENEMY_WIDTH / 2)*(PLAYER_PROJECTILE_RADIUS))+((ENEMY_WIDTH / 2)*(PLAYER_PROJECTILE_RADIUS))))
				{
					ProjectileManager::GetInstance()->mListOfProjectiles[i]->markToDestroy();
					PlaySound("assets\\Audio\\Enemy_Hit.wav", NULL, SND_ASYNC);
					EnemyManager::GetInstance()->mListofEnemies[j]->damageEnemy(PLAYER_PROJECTILE_DAMAGE);
				}
			}
		}
	}
}