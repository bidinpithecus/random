#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(Position direction, Position position, Position up, Position rotation, GLfloat speed, GLfloat zoom) {
	this->direction = direction;
	this->position = position;
	this->up = up;
	this->rotation = rotation;
	this->speed = speed;
	this->zoom = zoom;
}

void Camera::setDirection(Position direction) {
	this->direction = direction;
}

void Camera::setPosition(Position position) {
	this->position = position;
}

void Camera::setUp(Position up) {
	this->up = up;
}

void Camera::setSpeed(GLfloat speed) {
	this->speed = speed;
}

void Camera::setZoom(GLfloat zoom) {
	this->zoom = zoom;
}

void Camera::setRotation(Position rotation) {
	this->rotation = rotation;
}

Position Camera::getDirection() {
	return this->direction;
}

Position Camera::getPosition() {
	return this->position;
}

Position Camera::getUp() {
	return this->up;
}

Position Camera::getRotation() {
	return this->rotation;
}

GLfloat Camera::getSpeed() {
	return this->speed;
}

GLfloat Camera::getZoom() {
	return this->zoom;
}

