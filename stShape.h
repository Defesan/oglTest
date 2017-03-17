#ifndef __ST_SHAPE_H__
#define __ST_SHAPE_H__

#include <cmath>

#if defined(__IPHONEOS__) || defined(__ANDROID__)
#define USING_OPENGLES
#endif

#ifdef USING_OPENGLES
#include "SDL_opengles.h"
#else
#include "SDL2/SDL_opengl.h"
#endif

//Ah, the prototypical abstract class. But... I am making shapes here, so I need one.
class Shape
{
	//These shapes are going to be defined in terms of vertices, triangles, and colors. So...each one has to have all three. Doesn't matter what it is.
private:
	GLfloat** verts;
	GLubyte** colors;
	GLushort* indices;
	
	//This is going to be VERY simple at first.
		
	//Generate the vertices of the object.
	virtual void genVerts() = 0;
	
	//Take the vertices and try and piece them together in such a way that it generates a shape.
	virtual void genIndices() = 0;
	
public:
	//Putting the constructor aside, what will we always need to do?
	
	//This class can't really come up with a color scheme on its own yet, so we still have to send that in.
	virtual bool setColors(GLFloat** colors) = 0;
	
	//We need the getters so that we can actually display the shape. Maybe make this class able to display itself in the future?
	virtual GLFLoat** getColors() = 0;
	virtual GLFLoat** getVerts() = 0;
	virtual GLushort* getIndices() = 0;

	//Finally, the destructor.
	virtual ~Shape();
};


#endif
