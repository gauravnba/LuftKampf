#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <string.h>
#include "glut.h"
#include "SOIL.h"
#include "baseTypes.h"
#include "SpriteManager.h"
#include "openglframework.h"

SpriteManager *SpriteManager::sInstance = nullptr;

SpriteManager *SpriteManager::CreateInstance()
{
	if (!sInstance)
	{
		sInstance = new SpriteManager();
		memset(sInstance->spritePointers, NULL, sizeof(sInstance->spritePointers));
	}

	return sInstance;
}

GameSprites* SpriteManager::addSprite(int32_t width, int32_t height, char* spriteFileName, int32_t zDepth)
{
	for (int32_t i = 0; i < MAX_NUM_SPRITES; i++)
	{
		if (spritePointers[i] == nullptr)
		{
			/* load an image file directly as a new OpenGL texture */
			mSpriteTextureMap = SOIL_load_OGL_texture(spriteFileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
			spritePointers[i] = new GameSprites(width, height, mSpriteTextureMap, zDepth);

			return spritePointers[i];
		}
	}
	return nullptr;
}

void SpriteManager::updateSprites(float32_t seconds)
{
	mCurrentTime += seconds;
}

void SpriteManager::renderSprites()
{
	glEnable(GL_TEXTURE_2D);

	for (int32_t i = 0; i < MAX_NUM_SPRITES; i++)
	{
		if (spritePointers[i] != nullptr)
		{
			if (spritePointers[i]->getDraw())
			{
				int32_t spriteID = spritePointers[i]->getSpriteID();
				glBindTexture(GL_TEXTURE_2D, spriteID);

				int32_t lWidth = spritePointers[i]->getWidth();
				int32_t lHeight = spritePointers[i]->getHeight();
				int32_t zIndex = spritePointers[i]->getZIndex();

				float32_t posX = spritePointers[i]->getPosX();
				float32_t posY = spritePointers[i]->getposY();

				float32_t xPositionLeft = posX - lWidth / 2;
				float32_t xPositionRight = posX + lWidth / 2;

				float32_t yPositionTop = posY - lHeight / 2;
				float32_t yPositionBottom = posY + lHeight / 2;

				float32_t xTextureCoord = 0;
				float32_t yTextureCoord = 0;

				glPushMatrix();

				float32_t spriteRotationAngle = spritePointers[i]->getRotation() * RAD2DEG;

				glTranslatef(posX, posY, zIndex);
				glRotatef(spriteRotationAngle, 0, 0, 1.0f);
				glTranslatef(-posX, -posY, -zIndex);

				glBegin(GL_QUADS);

				glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
				glTexCoord2f(xTextureCoord, yTextureCoord);
				glVertex3f(xPositionLeft, yPositionTop, zIndex);
				glTexCoord2f(xTextureCoord + 1, yTextureCoord);
				glVertex3f(xPositionRight, yPositionTop, zIndex);
				glTexCoord2f(xTextureCoord + 1, yTextureCoord + 1);
				glVertex3f(xPositionRight, yPositionBottom, zIndex);
				glTexCoord2f(xTextureCoord, yTextureCoord + 1);
				glVertex3f(xPositionLeft, yPositionBottom, zIndex);

				glEnd();

				glPopMatrix();
			}
		}
		else
			break;
	}
}

void SpriteManager::shutdown()
{
	return;
}