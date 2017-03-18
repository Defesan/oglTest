#ifndef __ST_RECT_H__
#define __ST_RECT_H__

#include "stShape.h"

class Rect : public Shape
{
private:
	GLfloat originX;
	GLfloat originY;
	GLfloat width;
	GLfloat height;
	
public:
	Rect(GLfloat originX, GLfloat originY, GLfloat width, GLfloat height);
	//Rect(GLfloat originX, GLfloat originY, GLfloat edge);
	~Rect() override;
	GLfloat** getVerts() override {return this->verts;};
	GLubyte** getColors() override {return this->colors;};
	GLushort* getIndices() override {return this->indices;};
	//No need for special functions. I mean, this is about the most basic shape... but I still need to override all of the base class' methods.
	//I guess that makes sense.
	
	void genVerts() override;
	void genIndices() override;
	bool setColors(GLubyte** colors) override;
};



#endif
