#include "Node.hpp"
#include "Coordinate.hpp"

Node::Node() : coordinate(Coordinate(0)) {}
Node::Node(Coordinate coordinate, float size) : coordinate(coordinate), size(size) {}
Node::~Node() {}

Coordinate Node::getCoordinate() { return this->coordinate; }
float Node::getSize() { return this->size; }

void Node::setCoordinate(Coordinate coordinate) { this->coordinate = coordinate; }
void Node::setSize(float size) { this->size = size; }
