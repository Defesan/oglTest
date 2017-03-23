#include "stSphere.h"

Sphere::Sphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLushort numLayers, GLushort numSlices)
{
	this->originX = originX;
	this->originY = originY;
	this->originZ = originZ;
	this->radius = radius;
	this->numLayers = numLayers;
	this->numSlices = numSlices;
	
	int numVerts = (numLayers * numSlices) + 2;
	//int vertArraySize = numVerts * 3;
	//std::cout << "Vert Array Size: " << vertArraySize << std::endl;
	//this->verts = new GLfloat[vertArraySize];
	//this->colors = new GLubyte[numVerts * 4];
	
	//Once again, we ask:how many triangles?
	//There will be a triangle for every slice on the top and bottom, and two between each layer.
	//From stCircle, we learned that there is one face for every vertex around a circle. So if there are N slices, there are 2 * N faces making up the top and bottom.
	//There is one quad for every slice BETWEEN each adjacent pair of layers, which means two faces. We'll cross the 'how to index that' bridge when we come to it.
	//But if there are M layers, there are 2 * (M - 1) triangles.
	
	//this->indices = new GLushort[(2 * numSlices) + (2 * (numLayers - 1))];
	
	this->genVerts();
	//std::cout << "Generated vertices." << std::endl;
	
	this->genIndices();
	
	GLubyte red = 0;
	GLubyte green = 0;
	GLubyte blue = 0;
	GLubyte alpha = 0;
	
	for(int i = 0; i < numVerts; i++)
	{
		//For every vertex in the color array, let's just increment all of the values by one, and eat the overflow if it happens.
		int startPos = 4 * i;
		this->colors[startPos] = red;
		this->colors[startPos + 1] = green;
		this->colors[startPos + 2] = blue;
		this->colors[startPos + 3] = alpha;
		
		red += 20;
		green += 20;
		blue += 20;
		
	}
	
}

Sphere::~Sphere()
{
	//delete[] this->verts;
	//delete[] this->colors;
	//delete[] this->indices;

}

void Sphere::genVerts()
{
	//Oh, joy. Spherical trig. I've been looking forward to this all week.
	//int numVerts = (this->numLayers * this->numSlices) + 2;
	//We'll take this from the top.
	GLfloat currentYPos = this->originY + this->radius;
	int vertIndex = 0;
	int startPos = 0;
	this->verts[startPos] = this->originX;
	this->verts[startPos + 1] = currentYPos;
	this->verts[startPos + 2] = this->originZ;
	
	std::cout << vertIndex << ": " << this->verts[startPos] << "X, " << this->verts[startPos + 1] << "Y, " << this->verts[startPos + 2] << "Z, " << std::endl;
	vertIndex++;
	//Now, the circles are going to go "back" and "forward" along the Z-axis.
	//We can think of the layers as points on a half-circle, so the difference in angle between the layers would be PI / numLayers + 1.
	//The layers only count the 'inner' layers, not the poles, but there's one less 'slice' than there are points, so it's just +1.
	
	GLfloat layerAngle = PI/(this->numLayers + 1);
	GLfloat sliceAngle = (2 * PI)/this->numSlices;
	
	
	
	
	for(int i = 0; i < this->numLayers; i++)
	{
		GLfloat currentSliceAngle;
		GLfloat currentLayerAngle = layerAngle * (i + 1);
		GLfloat layerRadius = this->originX + (sin(currentLayerAngle) * this->radius);
		currentYPos = this->originY + (cos(currentLayerAngle) * this->radius);	//This will be the same for all the generated vertices in this layer.
		for(int j = 0; j < this->numSlices; j++)
		{
			startPos = vertIndex * 3;
			currentSliceAngle = j * sliceAngle;
			this->verts[startPos] = this->originX + (sin(currentSliceAngle) * layerRadius);//x position
			this->verts[startPos + 1] = currentYPos;
			this->verts[startPos + 2] = this->originZ + (cos(currentSliceAngle) * layerRadius); //z position
			std::cout << vertIndex << ": " << this->verts[startPos] << "X, " << this->verts[startPos + 1] << "Y, " << this->verts[startPos + 2] << "Z, " << std::endl;
			vertIndex++;	
		}
		//That's it, I think?
		//Let's examine what we're doing.
		//First we figure out the 'height' and 'radius' of the current ring. On a circle, those are basically the y and x coordinates.
		//To get the y coord, we take the cosine of the angle and multiply it by the radius.
		//To get the x coord, we take the sine of the angle and multiply it by the radius.
		//Then we construct the ring, just like a circle in 2D, except it's the X and Z axes, not the X and Y axes. Here, Z is Y and X is...X.
		//Finally, we increment the 'global', or at least non-local vertIndex variable every time we finish a vertex.
		//I think that works.	
	}
	// Now that we're here, vertIndex should be at the last vertex.
	
	startPos = vertIndex * 3;
	currentYPos = this->originY - this->radius;
	this->verts[startPos] = this->originX;
	this->verts[startPos + 1] = currentYPos;
	this->verts[startPos + 2] = this->originZ;
	std::cout << vertIndex << ": " << this->verts[startPos] << "X, " << this->verts[startPos + 1] << "Y, " << this->verts[startPos + 2] << "Z, " << std::endl;
	//And that's the last vertex. Now we just have to make them make SENSE.

}

void Sphere::genIndices()
{
	//Well, that trig was fun enough. Especially compared to this...
	
	
	//Again, we're starting from the top. There are three phases here, and the first is the easiest.
	
	int startPos = 0;
	
	//By the way, anyone noticed how much I like for loops?
	std::cout << "Generating upper cap." << std::endl;
	for(int i = 0; i < this->numSlices; i++)
	{
		this->indices[startPos] = 0;	//All of these tris start at the center point.
		this->indices[startPos + 1] = i + 1;
		if(i != (this->numSlices - 1))
		{
			this->indices[startPos + 2] = i + 2;
		}
		else
		{
			this->indices[startPos + 2] = 1;
		}
		std::cout << this->indices[startPos] << " " << this->indices[startPos + 1] << " " << this->indices[startPos + 2] << std::endl;
		startPos += 3;
	}
	
	//That was the easy part.
	//Okay, so say N = 12. It doesn't matter what M is, since this is just between layers.
	//Around the first ring you have 1, 2, 3, ..., 12. The next vertex, 13, should be in the next ring, directly below 1.
	//So, with rings starting at 0 and going to (numLayers - 1), we'll make two tris per vertex.
	//The first one is simple enough: (N * i) + 1, (N * (i + 1)) + 1, (N * (i + 1)) + 2.
	//The second isn't much worse: (N * i) + 1, (N * i) + 2, (N * (i + 1)) + 2.
	//Adding an inner loop, with j going from 0 to N...
	//Tri 1: (N * i) + j + 1, (N * (i + 1)) + j + 1, (N * (i + 1)) + j + 2
	//Tri 2: (N * i) + j + 1, (N * i) + j + 2, (N * (i + 1)) + j + 2
	std::cout << "Generating strips." << std::endl;
	for(int i = 0; i < (this->numLayers - 1); i++)
	{
		std::cout << "Generating strip " << i << "." << std::endl;
		int firstVert = (this->numSlices * i) + 1;	//Important for closing the strips
		int belowFirst = (this->numSlices * (i + 1)) + 1; //Also important.
		
		for(int j = 0; j < this->numSlices; j++)
		{
			//There are a few safe assumptions, regardless of index, but they're out of order.
			this->indices[startPos] = firstVert + j;
			this->indices[startPos + 1] = belowFirst + j;
			this->indices[startPos + 3] = firstVert + j;
			
			if(j != (this->numSlices - 1))
			{
				this->indices[startPos + 2] = belowFirst + (j + 1);
				this->indices[startPos + 4] = firstVert + (j + 1);
				this->indices[startPos + 5] = belowFirst + (j + 1);
			}
			else
			{
				this->indices[startPos + 2] = belowFirst;
				this->indices[startPos + 4] = firstVert;
				this->indices[startPos + 5] = belowFirst;
			}
			std::cout << this->indices[startPos] << " " << this->indices[startPos + 1] << " " << this->indices[startPos + 2] << std::endl;
			std::cout << this->indices[startPos + 3] << " " << this->indices[startPos + 4] << " " << this->indices[startPos + 5] << std::endl;
			startPos += 6;
		}
		//That's it, I think?
	
	}
	
	//And now for the slightly less easy than the first part -- but probably nowhere near as tricky as the second part -- third part.
	
	int numVerts = this->numSlices * this->numLayers + 2;
	int lastVert = numVerts - 1;
	int startOfLastRing = lastVert - this->numSlices;
	
	//StartPos should be current.
	std::cout << "Generating bottom cap." << std::endl;
	for(int i = 0; i < this->numSlices; i++)
	{
		this->indices[startPos] = lastVert;	//All of these tris start at the center point.
		this->indices[startPos + 1] = i + startOfLastRing;
		if(i != (this->numSlices - 1))
		{
			this->indices[startPos + 2] = i + (startOfLastRing + 1);
		}
		else
		{
			this->indices[startPos + 2] = startOfLastRing;
		}
		std::cout << this->indices[startPos] << " " << this->indices[startPos + 1] << " " << this->indices[startPos + 2] << std::endl;
		startPos += 3;
	}
	//Good God, I hope that's at least going to compile, so I can commit it.
}


bool Sphere::setColors(GLubyte** colors)
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
