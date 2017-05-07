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
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "field.h"
#include "randomnumbergenerator.h"
#include "OpenGLDrawing.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "SpriteManager.h"
#include "Environment.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;
}

void CGame::init()
{
	//BallManagerC::CreateInstance();
	StateManager::CreateInstance();
	//FieldManagerC::CreateInstance();
	InputManager::CreateInstance();
	Environment::CreateInstance();
	Player::CreateInstance();
	ProjectileManager::CreateInstance();
	//SpriteDemoManagerC::CreateInstance();
	SpriteManager::CreateInstance();

	//InputManagerC::GetInstance()->init();
	//BallManagerC::GetInstance()->init();
	StateManager::GetInstance()->setState(StateManager::SPLASH_SCREEN);
	//FieldManagerC::GetInstance()->init();
	//SpriteManager::GetInstance()->addSprite(1024, 768, "assets\\Background.png");
	Environment::GetInstance()->initBackground();
	Player::GetInstance()->init();
	Environment::GetInstance()->initBounds();
}
void CGame::UpdateFrame(float32_t seconds)
{
	InputManager::GetInstance()->keyProcess();
	Player::GetInstance()->update(seconds);
	Environment::GetInstance()->update(seconds);
	SpriteManager::GetInstance()->updateSprites(seconds);
	ProjectileManager::GetInstance()->updateProjectiles(seconds);
	//BallManagerC::GetInstance()->updateBalls(milliseconds);
//	InputManagerC::GetInstance()->update(milliseconds);
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	gluLookAt(Player::GetInstance()->getPosX(), Player::GetInstance()->getPosY(),1, Player::GetInstance()->getPosX(), Player::GetInstance()->getPosY(),-1,0,1,0);
	SpriteManager::GetInstance()->renderSprites();
	ProjectileManager::GetInstance()->renderProjectiles();
	//BallManagerC::GetInstance()->renderBalls();
	//FieldManagerC::GetInstance()->renderField();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	//BallManagerC::GetInstance()->shutdown();
	StateManager::GetInstance()->shutdown();
	//FieldManagerC::GetInstance()->shutdown();
	SpriteManager::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	//delete BallManagerC::GetInstance();
	delete StateManager::GetInstance();
	//delete FieldManagerC::GetInstance();
}