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
	this->indices = new GLshort[6];
	
	this->originX = originX;
	this->originY = originY;
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
	this->verts[0] = {this->originX - (this->width / 2), this->originY + (this->height / 2), 0.0f};
    this->verts[1] = {this->originX + (this->width / 2), this->originY + (this->height / 2), 0.0f};
	this->verts[2] = {this->originX + (this->width / 2), this->originY - (this->height / 2), 0.0f};    
	this->verts[3] = {this->originX - (this->width / 2), this->originY - (this->height / 2), 0.0f};
}

void Rect::genIndices()
{
	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 3;
	this->indices[3] = 2;
	this->indices[4] = 1;
	this->indices[5] = 3;
	
}

bool setColors(GLubyte** colors)
{
	if(colors)
	{
		this->colors = colors;
		return true;
	}
	return false;
}