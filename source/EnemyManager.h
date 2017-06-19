#pragma once

#include "baseTypes.h"
#include "Enemy.h"
#include <vector>

#define FULL_CIRCLE 6.28318f

class EnemyManager
{
	friend class CollisionManager;
public:
	static EnemyManager* CreateInstance();
	static EnemyManager* GetInstance() { return sInstance; };
	~EnemyManager() {};

	void	createEnemy();
	int32_t	getNumEnemies() { return mListofEnemies.size(); };
	void	updateEnemies(float32_t deltaTime);

private:
	static EnemyManager* sInstance;

	std::vector <Enemy*> mListofEnemies;
	bool_t		mNoEnemiesPresent	= true;

	EnemyManager() {};
};