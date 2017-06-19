#pragma once

#define ENEMY_COLLIDE_DAMAGE		20
#define ENEMY_PROJECTILE_DAMAGE		10
#define PLAYER_PROJECTILE_DAMAGE	34
#define PLAYER_COLLIDE_DAMAGE		100

class CollisionManager
{
public:
	static CollisionManager* CreateInstance();
	static CollisionManager* GetInstance() { return sInstance; };
	~CollisionManager() = default;

	void checkCollisions();

private:
	CollisionManager() {};
	static CollisionManager* sInstance;
};