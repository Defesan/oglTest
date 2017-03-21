#ifndef __ST_SPHERE_H__
#define __ST_SPHERE_H__

#include "stShape.h"


class Sphere : public Shape
{
private:
	GLfloat originX;
	GLfloat originY;
	GLfloat originZ;
	GLfloat radius;
	
	GLushort numLayers;
	GLushort numSlices;
	
	void genVerts() override;
	void genIndices() override;
public:
	Sphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius, GLushort numLayers, GLushort numSlices);
	Sphere(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat radius) : Sphere(originX, originY, originZ, radius, 6, 12) {};
	~Sphere() override;
	
	GLfloat* getVerts() override {return this->verts;};
	GLubyte* getColors() override {return this->colors;};
	GLushort* getIndices() override {return this->indices;};
	
	bool setColors(GLubyte** colors) override;


};



#endif