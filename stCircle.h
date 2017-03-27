#ifndef __ST_CIRCLE_H__
#define __ST_CIRCLE_H__

#include "stShape.h"



class Circle : public Shape
{
private:
	GLfloat originX;
	GLfloat originY;
	GLfloat radius;
	GLushort numSlices;
public:
	
	Circle(GLfloat originX, GLfloat originY, GLfloat radius, GLushort numVerts);
	Circle(GLfloat originX, GLfloat originY, GLfloat radius) : Circle(originX, originY, radius, 12) {};
	~Circle() override;
	
	GLfloat* getVerts() override {return this->verts.data();};
	GLubyte* getColors() override {return this->colors.data();};
	GLushort* getIndices() override {return this->indices.data();};
	
	void genVerts() override;
	void genIndices() override;
	bool setColors(GLubyte** colors) override;
	void render();
};


#endif
