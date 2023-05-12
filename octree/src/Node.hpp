#ifndef _NODE_HPP_
#define _NODE_HPP_

#include "Coordinate.hpp"

class Node {
	public:
		Node();
		Node(Coordinate coordinate, float size);
		~Node();

		Coordinate getCoordinate();
		float getSize();
		void setCoordinate(Coordinate coordinate);
		void setSize(float size);

	private:
		Coordinate coordinate;
		float size;
};

#endif
