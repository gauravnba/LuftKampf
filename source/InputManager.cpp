#include <windows.h>
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <gl/glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "OpenGLFramework.h"
#include "InputManager.h"

InputManager* InputManager::sInstance = nullptr;

const char InputManager::mPlayerInput[NUM_INPUTS] = { VK_UP, VK_LEFT, VK_RIGHT, FIRE_KEY };

InputManager *InputManager::CreateInstance()
{
	if(sInstance == nullptr)
		sInstance = new InputManager();

	return sInstance;
}

void InputManager::keyProcess()
{
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		TerminateApplication(g_window);						// Terminate The Program
	}

	if (g_keys->keyDown[VK_F1])									// Is F1 Being Pressed?
	{
		ToggleFullscreen(g_window);							// Toggle Fullscreen Mode
	}

	InputManager::playerInput();
}

void InputManager::playerInput()
{
	for (int i = 0; i < NUM_INPUTS; i++)
	{
		if (g_keys->keyDown[mPlayerInput[i]])
		{
			mPlayerInputStates[i] = true;
		}
		else if (!(g_keys->keyDown[mPlayerInput[i]]))
		{
			mPlayerInputStates[i] = false;
		}
	}
}