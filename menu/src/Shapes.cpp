#include "Shapes.hpp"

// Cylinder stuff
Cylinder::Cylinder() {};

Cylinder::Cylinder(GLUquadric* pObj, GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, Rotation rotation, Position position, Color color) {
	this->pObj = pObj;
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
	this->rotation = rotation;
	this->position = position;
	this->color = color;
};

void Cylinder::draw() {
	// save transform matrix state
	glPushMatrix();
	color.paint();
	// setting position in screen
	position.translate();
	// setting rotation in screen
	rotation.rotate();
	// setting the disk itself
	gluCylinder(this->pObj, this->base, this->top, this->height, this->slices, this->stacks);
	// restore transform matrix state
	glPopMatrix();
}

void Cylinder::setSize(GLfloat base, GLfloat top, GLfloat height) {
	this->base = base;
	this->top = top;
	this-> height = height;
}

void Cylinder::setRotation(Rotation rotation) {
	this->rotation = rotation;
}

void Cylinder::setPosition(Position position) {
	this->position = position;
}

void Cylinder::setColor(Color color) {
	this->color = color;
}

void Cylinder::setBase(GLfloat base) {
	this->base = base;
}

void Cylinder::setTop(GLfloat top) {
	this->top = top;
}

void Cylinder::setHeight(GLfloat height) {
	this->height = height;
}
GLfloat Cylinder::getBase() {
	return this->base;
}

GLfloat Cylinder::getTop() {
	return this->top;
}

GLfloat Cylinder::getHeight() {
	return this->height;
}

// Disk stuff
Disk::Disk() {};

Disk::Disk(GLUquadric* pObj, GLfloat inner, GLfloat outer, GLint slices, GLint loops, Rotation rotation, Position position, Color color) {
	this->pObj = pObj;
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
	this->rotation = rotation;
	this->position = position;
	this->color = color;
};

void Disk::draw() {
	// save transform matrix state
	glPushMatrix();
	color.paint();
	// setting position in screen
	position.translate();
	// setting rotation in screen
	rotation.rotate();
	// setting the disk itself
	gluDisk(this->pObj, this->inner, this->outer, this->slices, this->loops);
	// restore transform matrix state
	glPopMatrix();
}

void Disk::setSize(GLfloat inner, GLfloat outer) {
	this->inner = inner;
	this->outer = outer;
}

void Disk::setRotation(Rotation rotation) {
	this->rotation = rotation;
}

void Disk::setPosition(Position position) {
	this->position = position;
}

void Disk::setColor(Color color) {
	this->color = color;
}

void Disk::setInner(GLfloat inner) {
	this->inner = inner;
}

void Disk::setOuter(GLfloat outer) {
	this->outer = outer;
}
GLfloat Disk::getOuter() {
	return this->outer;
}

GLfloat Disk::getInner() {
	return this->inner;
}
// Sphere stuff
Sphere::Sphere() {};

Sphere::Sphere(GLUquadric* pObj, GLfloat radius, GLint slices, GLint stacks, Rotation rotation, Position position, Color color) {
	this->pObj = pObj;
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
	this->rotation = rotation;
	this->position = position;
	this->color = color;
};

void Sphere::draw() {
	// save transform matrix state
	glPushMatrix();
	// setting the color that goes [0, 1]
	color.paint();
	// setting position in screen
	position.translate();
	// setting the sphere itself
	gluSphere(this->pObj, this->radius, this->slices, this->stacks);
	// restore transform matrix state
	glPopMatrix();
}

void Sphere::setSize(GLfloat radius) {
	this->radius = radius;
}

void Sphere::setRotation(Rotation rotation) {
	this->rotation = rotation;
}

void Sphere::setPosition(Position position) {
	this->position = position;
}

void Sphere::setColor(Color color) {
	this->color = color;
}

GLfloat Sphere::getSize() {
	return this->radius;
}
