#ifndef _NODE_HPP_
#define _NODE_HPP_

#include "Coordinate.hpp"

class Node {
	public:
		Node();
		Node(Coordinate coordinate);
		~Node();

		Coordinate getCoordinate();

	private:
		Coordinate coordinate;
};

#endif
