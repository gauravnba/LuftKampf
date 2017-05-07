#pragma once

#include "baseTypes.h"
#include "Enemy.h"
#include <vector>

class EnemyManager
{
public:
	static EnemyManager* CreateInstance();
	static EnemyManager* GetInstance() { return sInstance; };
	~EnemyManager() {};

	void	init();
	int32_t	getNumEnemies() { return mNumEnemies; };
	void	spawnEnemy();
	void	updateEnemies(float32_t seconds);
	void	renderEnemies();
	void	fireGuns();

private:
	std::vector <Enemy*> mListofEnemies;
	static EnemyManager* sInstance;
	static int32_t mNumEnemies;
	EnemyManager() {};
};