#ifndef __ST_CIRCLE_H__
#define __ST_CIRCLE_H__

#include "stShape.h"



class Circle : public Shape
{
private:
	GLfloat originX;
	GLfloat originY;
	GLfloat radius;
	GLushort numVerts;
public:
	
	Circle(GLfloat originX, GLfloat originY, GLfloat radius, GLushort numVerts);
	Circle(GLfloat originX, GLfloat originY, GLfloat radius) : Circle(originX, originY, radius, 12) {};
	~Circle() override;
	
	GLfloat* getVerts() override {return this->verts;};
	GLubyte* getColors() override {return this->colors;};
	GLushort* getIndices() override {return this->indices;};
	
	void genVerts() override;
	void genIndices() override;
	bool setColors(GLubyte** colors) override;
};


#endif
