#include "stRect.h"

Rect::Rect(GLfloat originX, GLfloat originY, GLfloat width, GLfloat height)
{
	//We need four vertices.
	this->verts = new GLfloat*[4];
	this->colors = new GLubyte*[4];
	
	for(int i = 0; i < 4; i++)
	{
		this->verts[i] = new GLfloat[3];
	    this->colors[i] = new GLubyte[4];
	}
	this->indices = new GLushort[6];
	
	this->originX = originX;
	this->originY = originY;
	this->width = width;
	this->height = height;
	
	this->genVerts();
	this->genIndices();
	
	for(int i = 0; i < 4; i++)
	{
		this->colors[i][0] = 20 * i;
		this->colors[i][1] = 30 * i;
		this->colors[i][2] = 50 * i;
		this->colors[i][3] = 255;
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
	GLfloat offsetX = this->width / 2;
	GLfloat offsetY = this->height / 2; 
	this->verts[0][0] = this->originX - offsetX;
	this->verts[0][1] = this->originY + offsetY;
	this->verts[0][2] = 0.0f;
	this->verts[1][0] = this->originX + offsetX;
	this->verts[1][1] = this->originY + offsetY;
	this->verts[1][2] = 0.0f;
	this->verts[2][0] = this->originX - offsetX;
	this->verts[2][1] = this->originY - offsetY;
	this->verts[2][2] = 0.0f;
	this->verts[3][0] = this->originX + offsetX;
	this->verts[3][1] = this->originY - offsetY;
	this->verts[3][2] = 0.0f;
	
	
}

void Rect::genIndices()
{
	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 2;
	this->indices[3] = 2;
	this->indices[4] = 1;
	this->indices[5] = 3;
	
}

bool Rect::setColors(GLubyte** colors)
{
	if(colors)
	{
		this->colors = colors;
		return true;
	}
	return false;
}
