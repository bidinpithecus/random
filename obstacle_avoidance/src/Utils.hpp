#ifndef _utils_h_
#define _utils_h_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define X 0
#define Y 1
#define Z 2

class Position {
	public:
		Position();
		Position(GLfloat x, GLfloat y, GLfloat z);

		void translate();
		void setX(GLfloat x);
		void setY(GLfloat y);
		void setZ(GLfloat z);

		GLfloat getX();
		GLfloat getY();
		GLfloat getZ();

	private:
		GLfloat x;
		GLfloat y;
		GLfloat z;
};

class Rotation {
	public:
		Rotation();
		Rotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

		void rotate();
		void setAngle(GLfloat angle);

	private:
		GLfloat angle;
		GLfloat x;
		GLfloat y;
		GLfloat z;
};

#endif
