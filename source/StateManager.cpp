#define STATE_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"
#include "stateManager.h"

StateManager* StateManager::sInstance = nullptr;

StateManager *StateManager::CreateInstance()
{
	if(sInstance == nullptr)
		sInstance = new StateManager();

	return sInstance;
}
int32_t StateManager::getState()
{
	return mCurrentState;
}
void StateManager::setState(int32_t state)
{
	mCurrentState = state;
}
void StateManager::shutdown()
{
}