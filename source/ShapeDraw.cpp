#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <math.h>
#include <stdio.h>

const float32_t DEG2RAD = 3.14159f/180.0f;


void DrawCircle(float32_t radius, float32_t x, float32_t y, char8_t r, char8_t g, char8_t b, bool filled)
{
	
	glEnable(GL_POINT_SMOOTH);
	if(!filled)
	{
		glDisable(GL_TEXTURE_2D);
		glColor4ub(r, g, b,0x20);
		// Set the point size
		glPointSize(1.0);
		glBegin(GL_POINTS);
		float32_t radiusMax = radius + 2.0f;
		float32_t radiusMin = radius - 2.0f;
		for (int i=0; i < 360; i+=3)
		{
			float32_t degInRad = i*DEG2RAD;
			glVertex2f(x + (cos(degInRad)*radius),y + (sin(degInRad)*radius));
			glVertex2f(x + (cos(degInRad)*radiusMax),y + (sin(degInRad)*radiusMax));
			glVertex2f(x + (cos(degInRad)*radiusMin),y + (sin(degInRad)*radiusMin));
		}
		glEnd();
	}
	else
	{
	    glColor4ub(r, g, b,0xFF);
		glEnable(GL_BLEND); 
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glPointSize(radius/2.0f);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}

void DrawLine(float32_t startX, float32_t startY, float32_t endX, float32_t endY, char8_t r, char8_t g, char8_t b)
{
	glColor3ub(r, g, b);
	// Draw filtered lines
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINE_STRIP);
		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
	glEnd();

}
