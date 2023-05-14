#include "Node.hpp"

Node::Node() : coordinate(Coordinate(0)) {}
Node::Node(Coordinate coordinate, float size) : coordinate(coordinate), size(size) { highlight = false; }
Node::Node(Coordinate coordinate, float size, bool highlight) : coordinate(coordinate), size(size), highlight(highlight) {}
Node::~Node() {}

Coordinate Node::getCoordinate() { return this->coordinate; }
float Node::getSize() { return this->size; }
bool Node::getHighlight() { return this->highlight; }

void Node::setCoordinate(Coordinate coordinate) { this->coordinate = coordinate; }
void Node::setSize(float size) { this->size = size; }
void Node ::setHighlight(bool highlight) { this->highlight = highlight; }

void Node::move() {
	int factor = 1;
	float newX = randomInt(-factor, factor);
	float newY = randomInt(-factor, factor);
	float newZ = randomInt(-factor, factor);
	Coordinate newCoord(newX, newY, newZ);
	this->coordinate += newCoord;
}

bool Node::collidesWith(Node otherNode) {
	float minimumDistance = (this->getSize() + otherNode.getSize()) / 2.0;

	return this->coordinate.squaredDistance(otherNode.getCoordinate()) < minimumDistance;
}
