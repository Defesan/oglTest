#include "stCircle.h"

Circle::Circle(GLfloat originX, GLfloat originY, GLfloat radius, GLushort numVerts)
{

	
	this->originX = originX;
	this->originY = originY;
	this->radius = radius;
	this->numVerts = numVerts + 1;
	
	
	this->verts = new GLfloat[3 * this->numVerts];
	this->colors = new GLubyte[4 * this->numVerts];
	
	//How many indices? Well, there's one origin vertex, followed by n verts around the circle. That's n faces, and each one needs three indices.
	
	this->indices = new GLushort[3 * (this->numVerts - 1)];

	this->genVerts();
	
	this->genIndices();
	
	//Color generation. Let's start with black at the center, then increase red, then green, then blue.
	//That means we have four vertices for each color, and the increase needs to go up to, let's say, 252, for clarity's sake. So 63 for the first, 126 for the second, and so on.
	
	int redVerts = numVerts/3;
	int greenVerts = redVerts;
	int blueVerts = redVerts;
	
	switch(numVerts % (redVerts + greenVerts + blueVerts))
	{
		case 0:
			break;
		case 1:
			greenVerts++;
			break;
		case 2:
			redVerts++;
			blueVerts++;
			break;
		default:
			std::cerr << "Something went wrong with the math on determining the number of vertices per color..." << std::endl;
			break;
	}
	
	
	for(int i = 0; i < 4; i++)
	{
		this->colors[i] = 0.0f;
		
		
		int deltaColor[3];
		
		if(redVerts < 254)
		{
			deltaColor[0] = 255 / redVerts;
			deltaColor[1] = 255 / greenVerts;
			deltaColor[2] = 255 / blueVerts;
		}
		else
		{
			deltaColor[0] = 1;
			deltaColor[1] = 1;
			deltaColor[2] = 1;
		}
		
		int pos = (i + 1) * 4;
		this->colors[pos] = (i + 1) * deltaColor[0];
		pos = (i + (redVerts + 1)) * 4;
		this->colors[pos + 1] = (i + 1) * deltaColor[1];
		pos = (i + (redVerts + greenVerts + 1)) * 4;
		this->colors[pos + 2] = (i + 2) * deltaColor[2];
	}

	//And the alpha channel for good measure.
	for(int i = 0; i < this->numVerts; i++)
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
	GLfloat sliceAngle = (2 * PI) / (GLfloat)(this->numVerts - 1); 

	this->verts[0] = this->originX;
	this->verts[1] = this->originY;
	this->verts[2] = 0.0f;
	
	for(int i = 1; i < this->numVerts; i++)
	{
		GLfloat currentAngle = sliceAngle * (i - 1);
		//So the very first vertex works, since that'll be 0.
		this->verts[i * 3] = this->originX + sin(currentAngle) * this->radius;
		this->verts[(i * 3) + 1] = this->originY + cos(currentAngle) * this->radius;
		this->verts[(i * 3) + 2] = 0.0f;
	}
}

void Circle::genIndices()
{
	
	for(int i = 0; i < (this->numVerts - 2); i++)
	{
		int startPos = i * 3;
		this->indices[startPos] = 0;
		this->indices[startPos + 1] = i + 1;
		this->indices[startPos + 2] = i + 2;
	}
	
	int lastVert = (this->numVerts - 2) * 3;
	
	this->indices[lastVert] = 0;
	this->indices[lastVert + 1] = this->numVerts - 1;
	this->indices[lastVert + 2] = 1;
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
