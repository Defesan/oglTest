#include "stRect.h"

Rect::Rect(GLfloat origin, GLfloat width, GLfloat height)
{
	//We need four vertices.
	this->verts = new GLfloat[4][3];
	this->colors = new GLubyte[4][4];
	this->indices = new GLshort[6];
	
	this->origin = origin;
	this->width = width;
	this->height = height;
	
	this->genVerts();
	this->genIndices();
	
	for(int i = 0; i < 4; i++)
	{
		this->colors[i] = {50 * i, 50 * i, 50 * i, 255};
	}

}

Rect::~Rect()
{
	delete[] this->verts;
	delete[] this->colors;
	delete[] this->indices;

}

void Rect::genVerts()
{
	this->verts[0] = {

}
