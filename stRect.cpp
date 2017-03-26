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
		this->colors.push_back(20 * i);
		this->colors.push_back(30 * i);
		this->colors.push_back(50 * i);
		this->colors.push_back(255);
	}

}

Rect::~Rect()
{

}

void Rect::genVerts()
{
	GLfloat offsetX = this->width / 2;
	GLfloat offsetY = this->height / 2; 
	this->verts.push_back(this->originX - offsetX);
	this->verts.push_back(this->originY + offsetY);
	this->verts.push_back(0.0f);
	this->verts.push_back(this->originX + offsetX);
	this->verts.push_back(this->originY + offsetY);
	this->verts.push_back(0.0f);
	this->verts.push_back(this->originX - offsetX);
	this->verts.push_back(this->originY - offsetY);
	this->verts.push_back(0.0f);
	this->verts.push_back(this->originX + offsetX);
	this->verts.push_back(this->originY - offsetY);
	this->verts.push_back(0.0f);
	
	
}

void Rect::genIndices()
{
	this->indices.push_back(0);
	this->indices.push_back(1);
	this->indices.push_back(2);
	this->indices.push_back(2);
	this->indices.push_back(1);
	this->indices.push_back(3);
	
}

bool Rect::setColors(GLubyte** colors)
{
	if(colors)
	{
		this->colors.clear();
		//Yes, I know. Not good code. I need to pull in both the number of vertices and the size of the color array, but for now...
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				this->colors.push_back(colors[i][j]);
			}
		}
		return true;
	}
	return false;
}

void Rect::setColorToGLColor()
{
	//These colors are typically floats, which presents a problem....
	GLfloat colors[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	GLubyte ubColors[4] = {0, 0, 0, 0};
	glGetFloatv(GL_CURRENT_COLOR, colors);
	
	//Convert from float to ubyte
	for(int i = 0; i < 4; i++)
	{
		ubColors[i] = (GLubyte)(colors[i] * 255);		//should work?
	}
	this->colors.clear();
	for(int i = 0; i < 16; i++)
	{
		this->colors.push_back(ubColors[i % 4]);
	}
	
}

void Rect::render()
{
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, this->colors.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, this->verts.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, this->indices.data());
}
