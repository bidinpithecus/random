#include "Particle.hpp"
#include "Helpers.hpp"

Particle::Particle() { this->fov.assign(fibonacciPoints.size(), Coordinate(0)); }
Particle::Particle(Coordinate acceleration, Coordinate position, Coordinate velocity, int viewDistance, int size): acceleration(acceleration), position(position), velocity(velocity), viewDistance(viewDistance), size(size) { this->fov.assign(fibonacciPoints.size(), Coordinate(0)); }

Coordinate Particle::getAcceleration() { return acceleration; }
Coordinate Particle::getPosition() { return position; }
Coordinate Particle::getVelocity() { return velocity; }
std::vector<Coordinate> Particle::getFov() { return fov; }
float Particle::getViewDistance() { return viewDistance; }
float Particle::getSpeed() { return speed; }
float Particle::getSize() { return size; }

void Particle::setAcceleration(Coordinate acceleration) { this->acceleration = acceleration; }
void Particle::setPosition(Coordinate position) { this->position = position; }
void Particle::setVelocity(Coordinate velocity) { this->velocity = velocity; }
void Particle::setViewDistance(float viewDistance) { this->viewDistance = viewDistance; }
void Particle::setSpeed(float speed) { this->speed = speed; }
void Particle::setSize(float size) { this->size = size; }

void Particle::setFov() {
	for (long unsigned int i = 0; i < fibonacciPoints.size(); i++) {
		this->fov[i] = (fibonacciPoints[i] * this->size) + this->position;
	}
}

void Particle::update() {
	this->setFov();

	Coordinate desiredCoordinate = this->fov.at(fibonacciPoints.size() - 1) * this->speed;
	this->position = desiredCoordinate - this->position;
	// this->velocity = (desiredDirection * this->speed) - this->position;
}

void Particle::show(GLUquadricObj *pObj) {
	glPushMatrix();
		glTranslatef(this->position.getX(), this->position.getY(), this->position.getZ());
		glColor3f(0.1, 0.1, 0.1);
		gluSphere(pObj, this->size, 10, 5);
	glPopMatrix();

	for (auto coord : fov) {
		glColor3f(0, 0.75, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3f(coord.getX(), coord.getY(), coord.getZ());
			coord = this->position + ((coord - this->position) / Coordinate(coord - this->position).magnitude()) * this->viewDistance * this->size;
			glVertex3f(coord.getX(), coord.getY(), coord.getZ());
		glEnd();
	}
}
