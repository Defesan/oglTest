#ifndef __ST_RECT_H__
#define __ST_RECT_H__

#include "stShape.h"

class stRect : public Shape
{
private:
	GLfloat origin;
	GLfloat width;
	GLfloat height;
	
public:
	Rect(GLfloat origin, GLfloat width, GLfloat height);
	~Rect();
	
	//No need for special functions. I mean, this is about the most basic shape...
};



#endif
