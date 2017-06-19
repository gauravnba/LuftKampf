#pragma once

#include "Projectile.h"
#include "baseTypes.h"
#include <vector>

#define MAX_TRAVERSAL_OFFSET_X 1280
#define MAX_TRAVERSAL_OFFSET_Y 720

class ProjectileManager
{
	friend class CollisionManager;
public:
	static ProjectileManager* CreateInstance();
	static ProjectileManager* GetInstance() { return sInstance; };
	~ProjectileManager() {};

	int32_t	getNumProjectiles() { return mListOfProjectiles.size(); };
	void	createProjectile(float32_t initPosX, float32_t initPosY, float32_t VelX, float32_t VelY, int32_t projectileID);
	//Projectile* getProjectile(int32_t mID);
	void	updateProjectiles(float32_t seconds);
	void	renderProjectiles();

private:
	std::vector<Projectile*> mListOfProjectiles;
	static ProjectileManager* sInstance;
	ProjectileManager() = default;
};