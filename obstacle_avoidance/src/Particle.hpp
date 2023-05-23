#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include <vector>
#include "Coordinate.hpp"
#include "Helpers.hpp"

class Particle {
	public:
		Particle();
		Particle(Coordinate acceleration, Coordinate position, Coordinate velocity, int viewDistance, int numOfMicroEyes);
		Coordinate getAcceleration();
		Coordinate getPosition();
		Coordinate getVelocity();
		std::vector<Coordinate> getFov();
		float getViewDistance();
		float getSpeed();
		float getSize();
		void setAcceleration(Coordinate acceleration);
		void setPosition(Coordinate position);
		void setVelocity(Coordinate velocity);
		void setViewDistance(float viewDistance);
		void setSpeed(float speed);
		void setSize(float size);

		void setFov();
		void update();
		void show(GLUquadricObj *pObj);

	private:
		Coordinate acceleration;
		Coordinate position;
		Coordinate velocity;
		std::vector<Coordinate> fov;
		float viewDistance;
		float speed;
		float size;
};

#endif
