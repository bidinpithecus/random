#include "Cube.hpp"

Cube::Cube() {}
Cube::Cube(float sideSize) : center(Coordinate(0)), sideSize(sideSize) {}
Cube::Cube(Coordinate center, float sideSize) : center(center), sideSize(sideSize) {}
Cube::~Cube() {}

Coordinate Cube::getCenter() { return this->center; }
float Cube::getSideSize() { return this->sideSize; }

void Cube::setCenter(Coordinate center) { this->center = center; }
void Cube::setSideSize(float sideSize) { this->sideSize = sideSize; }

float Cube::getMinX() {
	return this->center.getX() - (this->sideSize / 2.0);
}
float Cube::getMaxX() {
	return this->center.getX() + (this->sideSize / 2.0);
}

float Cube::getMinY() {
	return this->center.getY() - (this->sideSize / 2.0);
}
float Cube::getMaxY() {
	return this->center.getY() + (this->sideSize / 2.0);
}

float Cube::getMinZ() {
	return this->center.getZ() - (this->sideSize / 2.0);
}
float Cube::getMaxZ() {
	return this->center.getZ() + (this->sideSize / 2.0);
}

bool Cube::contains(Coordinate coord) {
	bool xContained = (coord.getX() <= this->getMaxX()) && (coord.getX() >= this->getMinX());
	bool yContained = (coord.getY() <= this->getMaxY()) && (coord.getY() >= this->getMinY());
	bool zContained = (coord.getZ() <= this->getMaxZ()) && (coord.getZ() >= this->getMinZ());

	return xContained && yContained && zContained;
}

bool Cube::intersects(Cube cube) {
	bool intersectX = (cube.getMinX() <= this->getMaxX()) && (cube.getMaxX() >= this->getMinX());
	bool intersectY = (cube.getMinY() <= this->getMaxY()) && (cube.getMaxY() >= this->getMinY());
	bool intersectZ = (cube.getMinZ() <= this->getMaxZ()) && (cube.getMaxZ() >= this->getMinZ());

	return (intersectX && intersectY && intersectZ);
}
