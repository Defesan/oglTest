#ifndef __ST_RECT_H__
#define __ST_RECT_H__

#include "stShape.h"

class stRect : public Shape
{
private:
	GLfloat originX;
	GLfloat originY;
	GLfloat width;
	GLfloat height;
	
public:
	Rect(GLfloat originX, GLfloat originY, GLfloat width, GLfloat height);
	~Rect();
	GLfloat** getVerts() {return this->verts;};
	GLubyte** getColors() {return this->colors;};
	GLushort* getIndices() {return this->indices;};
	//No need for special functions. I mean, this is about the most basic shape...
};



#endif