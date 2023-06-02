#include "Utils.hpp"

// Rotation stuff
Rotation::Rotation() {};

Rotation::Rotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	this->angle = angle;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Rotation::rotate() {
	glRotatef(this->angle, this->x, this->y, this->z);
}

void Rotation::setAngle(GLfloat angle) {
	this->angle = angle;
}

// Position stuff
Position::Position() {};

Position::Position(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Position::translate() {
	glTranslatef(this->x, this->y, this->z);
}

void Position::setX(GLfloat x) {
	this->x = x;
}

void Position::setY(GLfloat y) {
	this->y = y;
}

void Position::setZ(GLfloat z) {
	this->z = z;
}

GLfloat Position::getX() {
	return this->x;
}

GLfloat Position::getY() {
	return this->y;
}

GLfloat Position::getZ() {
	return this->z;
}

