#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include "Utils.hpp"
#include "Color.hpp"

class Cylinder {
	public:
		Cylinder();
		Cylinder(GLUquadric* pObj, GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, Rotation rotation, Position position, Color color);

		void draw();
		void setSize(GLfloat base, GLfloat top, GLfloat height);
		void setRotation(Rotation rotation);
		void setPosition(Position position);
		void setColor(Color color);
		void setBase(GLfloat base);
		void setTop(GLfloat top);
		void setHeight(GLfloat height);
		GLfloat getBase();
		GLfloat getTop();
		GLfloat getHeight();

	private:
		GLUquadric* pObj;
		GLfloat base;
		GLfloat top;
		GLfloat height;
		GLint slices;
		GLint stacks;
		Rotation rotation;
		Position position;
		Color color;
};

class Disk {
	public:
		Disk();
		Disk(GLUquadric* pObj, GLfloat inner, GLfloat outer, GLint slices, GLint loops, Rotation rotation, Position position, Color color);

		void draw();
		void setSize(GLfloat inner, GLfloat outer);
		void setRotation(Rotation rotation);
		void setPosition(Position position);
		void setColor(Color color);

		void setInner(GLfloat inner);
		void setOuter(GLfloat outer);
		GLfloat getInner();
		GLfloat getOuter();

	private:
		GLUquadric* pObj;
		GLfloat inner;
		GLfloat outer;
		GLint slices;
		GLint loops;
		Rotation rotation;
		Position position;
		Color color;
};

class Sphere {
	public:
		Sphere();
		Sphere(GLUquadric* pObj, GLfloat radius, GLint slices, GLint stacks, Rotation rotation, Position position, Color color);

		void draw();
		void setSize(GLfloat radius);
		void setRotation(Rotation rotation);
		void setPosition(Position position);
		void setColor(Color color);

		GLfloat getSize();

	private:
		GLUquadric* pObj;
		GLfloat radius;
		GLint slices;
		GLint stacks;
		Rotation rotation;
		Position position;
		Color color;
};

class Cube {
	public:
		Cube();
		Cube(GLfloat side, Rotation rotation, Position position, Position scale, Color color);

		void draw();
		void setSize(GLfloat side);
		void setRotation(Rotation rotation);
		void setPosition(Position position);
		void setScale(Position scale);
		void setColor(Color color);

	private:
		GLfloat side;
		Rotation rotation;
		Position position;
		Position scale;
		Color color;
};

#endif
