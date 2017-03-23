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
	
	GLfloat* getVerts() override {return this->verts.data();};
	GLubyte* getColors() override {return this->colors.data();};
	GLushort* getIndices() override {return this->indices.data();};
	
	GLushort getNumLayers() {return this->numLayers;};
	GLushort getNumSlices() {return this->numSlices;};
	
	int getIndicesSize() {return this->indices.size();};
	
	bool setColors(GLubyte** colors) override;


};



#endif
