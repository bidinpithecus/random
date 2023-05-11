#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include "Coordinate.hpp"

/*
	This class will hold the central point and the side size of the cube
*/
class Cube {
	public:
		Cube();
		Cube(float sideSize);
		Cube(Coordinate center, float sideSize);
		~Cube();

		Coordinate getCenter();
		float getSideSize();

		void setCenter(Coordinate center);
		void setSideSize(float sideSize);

		bool contains(Coordinate coord);
		bool intersects(Cube cube);

		float getMinX();
		float getMaxX();
		float getMinY();
		float getMaxY();
		float getMinZ();
		float getMaxZ();

	private:
		Coordinate center;
		float sideSize;
};

#endif
