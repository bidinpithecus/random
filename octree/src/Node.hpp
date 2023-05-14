#ifndef _NODE_HPP_
#define _NODE_HPP_

#include "Coordinate.hpp"
#include "helpers.hpp"

class Node {
	public:
		Node();
		Node(Coordinate coordinate, float size);
		Node(Coordinate coordinate, float size, bool highlight);
		~Node();

		Coordinate getCoordinate();
		float getSize();
		bool getHighlight();

		void setCoordinate(Coordinate coordinate);
		void setSize(float size);
		void setHighlight(bool highlight);

		void move();
		bool collidesWith(Node otherNode);

	private:
		Coordinate coordinate;
		float size;
		bool highlight;
};

#endif
