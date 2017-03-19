#include "stCircle.h"

Circle::Circle(GLfloat originX, GLfloat originY, GLfloat radius)
{
	//Unlike Rect, I don't need a 'base case' constructor. I mean, that base case was a square.
	//I guess I could make an ellipse class, and make circle a base case?
	//I probably will, eventually, but let's start with what we're starting with.
	
	this->originX = originX;
	this->originY = originY;
	this->radius = radius;
	
	
	int numVertices = 13; //I should probably make this a parameter, later.
	
	this->verts = new GLfloat[3 * numVertices];
	this->colors = new GLubyte[4 * numVertices];
	
	//How many indices? Well, there's one origin vertex, followed by twelve verts around the circle. That's twelve faces, and each one needs three indices.
	
	this->indices = new GLushort[3 * (numVertices - 1)];

	this->genVerts();
	
	this->genIndices();
	
	//Color generation. Let's start with black at the center, then increase red, then green, then blue.
	//That means we have four vertices for each color, and the increase needs to go up to, let's say, 252, for clarity's sake. So 63 for the first, 126 for the second, and so on.
	
	for(int i = 0; i < 4; i++)
	{
		this->colors[i] = 0.0f;
		
		int pos = (i + 1) * 4;
		this->colors[pos] = (i + 1) * 63;
		pos = (i + 5) * 4;
		this->colors[pos + 1] = (i + 1) * 63;
		pos = (i + 9) * 4;
		this->colors[pos + 2] = (i + 2) * 63;
	}

	//And the alpha channel for good measure.
	for(int i = 0; i < 13; i++)
	{
		//I want to change the fourth member of each quad.
		int pos = (i * 4) + 3;
		this->colors[pos] = 255;
	}

	//Okay, I think THAT should work.
}

Circle::~Circle()
{
	delete[] this->verts;
	delete[] this->colors;
	delete[] this->indices;

}

void Circle::genVerts()
{
	GLfloat sliceAngle = (2 * PI) / 12.0f; //Yeah, definitely have to make that a parameter.

	this->verts[0] = this->originX;
	this->verts[1] = this->originY;
	this->verts[2] = 0.0f;
	
	for(int i = 0; i < 12; i++)
	{
		GLfloat currentAngle = sliceAngle * i;
		//So the very first vertex works, since that'll be 0.
		this->verts[i * 3] = sin(currentAngle) * this->radius;
		this->verts[(i * 3) + 1] = cos(currentAngle) * this->radius;
		this->verts[(i * 3) + 2] = 0.0f;
	}
}

void Circle::genIndices()
{

	//So the indices should be as follows
	//0 1 2
	//0 2 3
	//0 3 4
	//0 4 5
	//0 5 6
	//0 6 7
	//0 7 8
	//0 8 9
	//0 9 10
	//0 10 11
	//0 11 12
	//0 12 1
	for(int i = 0; i < 11; i++)
	{
		int startPos = i * 3;
		this->indices[startPos] = 0;
		this->indices[startPos + 1] = i + 1;
		this->indices[startPos + 2] = i + 2;
	}
	this->indices[33] = 0;
	this->indices[34] = 12;
	this->indices[35] = 1;
}

bool Circle::setColors(GLubyte** colors)
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
