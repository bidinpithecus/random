#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include <vector>
#include "Coordinate.hpp"

class Particle {
	public:
		Particle();
		Particle(Coordinate acceleration, Coordinate position, Coordinate velocity, int viewDistance, int numOfMicroEyes);
		Coordinate getAcceleration();
		Coordinate getPosition();
		Coordinate getVelocity();
		std::vector<Coordinate> getFov();
		int getViewDistance();
		int getNumOfMicroEyes();
		void setAcceleration(Coordinate acceleration);
		void setPosition(Coordinate position);
		void setVelocity(Coordinate velocity);
		void setFov(std::vector<Coordinate> fov);
		void setViewDistance(int viewDistance);
		void setNumOfMicroEyes(int numOfMicroEyes);

		void update();
		void show();

	private:
		Coordinate acceleration;
		Coordinate position;
		Coordinate velocity;
		std::vector<Coordinate> fov;
		int viewDistance;
		int numOfMicroEyes;
};

#endif
