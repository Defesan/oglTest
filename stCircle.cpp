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
	
	//Basic colors.
	//Okay, so this time, I'm going to iterate through EVERY VERTEX. The first vertex, of course, is going to be black(as the center).
	//After that, though, I want three variables. One for red, one for green, and one for blue.
	//THe red one should increase to 255 over the course of the first third of the circle, and stay that way.
	//(this isn't a color wheel, btw, except in that it is a wheel with colors on it.)
	//With red at 255, the overflow goes into green until it reaches 255.
	//Then the overflow goes into blue until IT reaches 255.
	//So the total I need to reach over numVertices is 765.
	//And the alpha channel for good measure.
	
	GLubyte red = 0;
	GLubyte green = 0;
	GLubyte blue = 0;
	GLubyte alpha = 255;
	
	int delta = 765 / this->numVerts;
	
	if(!delta)
	{
		delta = 1;
	
	}
	
	for(int i = 0; i < this->numVerts; i++)
	{
		int pos = i * 4;
		this->colors[pos] = red;
		pos++;
		this->colors[pos] = green;
		pos++;
		this->colors[pos] = blue;
		pos++;
		this->colors[pos] = alpha;
		
		//If red hasn't been maxed out...
		if(red < 255)
		{
			//and there's room for a full delta...
			if((255 - red) > delta)
			{
				//Add the full delta.
				red += delta;
			}
			else	//There's still room, but not ENOUGH room
			{
				int overflow = delta - (255 - red);
				red = 255;
				green += overflow;
			}
		
		}
		else if(green < 255)
		{
			if((255 - green) > delta)
			{
				green += delta;
			}
			else	
			{
				int overflow = delta - (255 - green);
				green = 255;
				blue += overflow;
			}
		}
		else if(blue < 255)
		{
			if((255 - blue) > delta)
			{
				blue += delta;
			}
			else	
			{
				blue = 255;
			}
		}
		else
		{
			std::cout << "Edge case... But this shouldn't happen. All the colors got filled up." << std::endl;
		}
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
		//BTW, doesn't work. Not for this, at least.
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
