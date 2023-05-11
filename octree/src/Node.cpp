#include "Node.hpp"
#include "Coordinate.hpp"

Node::Node() : coordinate(Coordinate(0)) {}
Node::Node(Coordinate coordinate) : coordinate(coordinate) {}

Coordinate Node::getCoordinate() { return this->coordinate; }
