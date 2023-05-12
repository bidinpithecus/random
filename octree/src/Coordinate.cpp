#include "Coordinate.hpp"
#include <cmath>

Coordinate::Coordinate() : x(0), y(0), z(0) {}
Coordinate::Coordinate(float same) : x(same), y(same), z(same) {}
Coordinate::Coordinate(float x, float y, float z) : x(x), y(y), z(z) {}
Coordinate::~Coordinate() {}

float Coordinate::getX() { return this->x; }
float Coordinate::getY() { return this->y; }
float Coordinate::getZ() { return this->z; }

void Coordinate::setX(float x) { this->x = x; }
void Coordinate::setY(float y) { this->y = y; }
void Coordinate::setZ(float z) { this->z = z; }

bool Coordinate::operator==(Coordinate coordinate) {
	bool sameX = this->x == coordinate.x;
	bool sameY = this->y == coordinate.y;
	bool sameZ = this->z == coordinate.z;
	return sameX && sameY && sameZ;
}

bool Coordinate::operator!=(Coordinate coordinate) {
	bool diffX = this->x != coordinate.x;
	bool diffY = this->y != coordinate.y;
	bool diffZ = this->z != coordinate.z;
	return diffX || diffY || diffZ;
}

Coordinate Coordinate::operator+(Coordinate coordinate) {
	return Coordinate(this->x + coordinate.x, this->y + coordinate.y, this->z + coordinate.z);
}

Coordinate Coordinate::operator-(Coordinate coordinate) {
	return Coordinate(this->x - coordinate.x, this->y - coordinate.y, this->z - coordinate.z);
}

Coordinate Coordinate::operator*(float num) {
	return Coordinate(this->x * num, this->y * num, this->z * num);
}

Coordinate Coordinate::operator/(float num) {
	if (!num) { num = 1; }
	return Coordinate(this->x / num, this->y / num, this->z / num);
}

void Coordinate::operator+=(Coordinate coordinate) {
	*this = *this + coordinate;
}

void Coordinate::operator-=(Coordinate coordinate) {
	*this = *this - coordinate;
}

void Coordinate::operator*=(float num) {
	*this = *this * num;
}

void Coordinate::operator/=(float num) {
	*this = *this / num;
}

float Coordinate::squaredDistance(Coordinate coordinate) {
	return sqrt(
		pow(this->x - coordinate.x, 2) +
		pow(this->y - coordinate.y, 2) +
		pow(this->z - coordinate.z, 2));
}
