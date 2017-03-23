#include "stRect.h"

Rect::Rect(GLfloat originX, GLfloat originY, GLfloat width, GLfloat height)
{
	//We need four vertices.
	//this->verts = new GLfloat[12];
	//this->colors = new GLubyte[12];
	//this->indices = new GLushort[6];
	
	//Let's just make sure there's no need for reallocation.
	this->verts.reserve(12);
	this->colors.reserve(16);
	this->indices.reserve(6);
	
	
	
	this->originX = originX;
	this->originY = originY;
	this->width = width;
	this->height = height;
	
	this->genVerts();
	this->genIndices();
	
	for(int i = 0; i < 4; i++)
	{
		int arrOffset = i * 4;
		this->colors[arrOffset] = 20 * i;
		this->colors[arrOffset + 1] = 30 * i;
		this->colors[arrOffset + 2] = 50 * i;
		this->colors[arrOffset + 3] = 255;
	}

}

Rect::~Rect()
{
	//delete[] this->verts;
	//delete[] this->colors;
	//delete[] this->indices;
	//Vector handles all of this! Yay!
}

void Rect::genVerts()
{
	GLfloat offsetX = this->width / 2;
	GLfloat offsetY = this->height / 2; 
	this->verts[0] = this->originX - offsetX;
	this->verts[1] = this->originY + offsetY;
	this->verts[2] = 0.0f;
	this->verts[3] = this->originX + offsetX;
	this->verts[4] = this->originY + offsetY;
	this->verts[5] = 0.0f;
	this->verts[6] = this->originX - offsetX;
	this->verts[7] = this->originY - offsetY;
	this->verts[8] = 0.0f;
	this->verts[9] = this->originX + offsetX;
	this->verts[10] = this->originY - offsetY;
	this->verts[11] = 0.0f;
	
	
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
		//Yes, I know. Not good code. I need to pull in both the number of vertices and the size of the color array, but for now...
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				this->colors[(i * 4) + j] = colors[i][j];
			}
		}
		return true;
	}
	return false;
}
