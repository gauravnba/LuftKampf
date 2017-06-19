#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"
#include "randomnumbergenerator.h"
#include "OpenGLDrawing.h"
#include "game.h"
#include "StateManager.h"
#include "InputManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "SpriteManager.h"
#include "Environment.h"
#include "EnemyManager.h"
#include "CollisionManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance = NULL;
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	seedRandomNumberGenerator();
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;
}

void CGame::init()
{
	StateManager::CreateInstance();
	InputManager::CreateInstance();
	Environment::CreateInstance();
	Player::CreateInstance();
	ProjectileManager::CreateInstance();
	SpriteManager::CreateInstance();
	EnemyManager::CreateInstance();
	CollisionManager::CreateInstance();

	StateManager::GetInstance()->setState(StateManager::SPLASH_SCREEN);
	Environment::GetInstance()->initBackground();
	Player::GetInstance()->init();
	Environment::GetInstance()->initBounds();
}
void CGame::UpdateFrame(float32_t seconds)
{
	CollisionManager::GetInstance()->checkCollisions();
	InputManager::GetInstance()->keyProcess();
	Player::GetInstance()->update(seconds);
	Environment::GetInstance()->update();
	SpriteManager::GetInstance()->updateSprites(seconds);
	ProjectileManager::GetInstance()->updateProjectiles(seconds);
	EnemyManager::GetInstance()->updateEnemies(seconds);
}

void CGame::DrawScene(void)										
{
	startOpenGLDrawing();

	float32_t playerPosX = Player::GetInstance()->getPosX();
	float32_t playerPosY = Player::GetInstance()->getPosY();
	gluLookAt(playerPosX, playerPosY,1, playerPosX, playerPosY,-1,0,1,0);

	SpriteManager::GetInstance()->renderSprites();
	ProjectileManager::GetInstance()->renderProjectiles();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	StateManager::GetInstance()->shutdown();
	SpriteManager::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	delete StateManager::GetInstance();
}