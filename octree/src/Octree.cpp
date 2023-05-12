#include "Octree.hpp"

using namespace std;

Octree::Octree() {}
Octree::Octree(Cube boundary, int capacity) : boundary(boundary), capacity(capacity) { isDivided = false; }
Octree::~Octree() {}

bool Octree::isItDivided() { return isDivided; }
Cube Octree::getBoundary() { return boundary; }
vector<Node> Octree::getNodes() { return nodes; }
Octree* Octree::getX0Y0Z0() { return x0y0z0; }
Octree* Octree::getX0Y0Z1() { return x0y0z1; }
Octree* Octree::getX0Y1Z0() { return x0y1z0; }
Octree* Octree::getX0Y1Z1() { return x0y1z1; }
Octree* Octree::getX1Y0Z0() { return x1y0z0; }
Octree* Octree::getX1Y0Z1() { return x1y0z1; }
Octree* Octree::getX1Y1Z0() { return x1y1z0; }
Octree* Octree::getX1Y1Z1() { return x1y1z1; }

/*
	this method returns true if node was inserted succesfully,
	or false if it wasn't able to do so.
*/
bool Octree::insert(Node node) {
    // Node is outside of the boundary, unable to insert
    if (!this->boundary.contains(node.getCoordinate())) {
        return false;
    }

    // If octree is available, add the node in the list of nodes of this octree
    // If not, subdivide it, try to insert it again, and reset the nodes of the octree
    if (this->nodes.size() < this->capacity && !this->isDivided) {
        this->nodes.push_back(node);
        return true;
    } else {
        if (!this->isDivided) {
            vector<Node> emptyVec;
            this->subdivide();

            for (auto& n : this->nodes) {
                this->insert(n);
            }
            this->nodes = emptyVec;
        }

        return
            this->x0y0z0->insert(node) || this->x0y0z1->insert(node) ||
            this->x0y1z0->insert(node) || this->x0y1z1->insert(node) ||
            this->x1y0z0->insert(node) || this->x1y0z1->insert(node) ||
            this->x1y1z0->insert(node) || this->x1y1z1->insert(node);
    }
}

/*
	this method subdivide the octree into its 8 sub-octrees
*/
void Octree::subdivide() {
    float newSize = this->boundary.getSideSize() / 2.0f;

    Coordinate center = this->boundary.getCenter();

    float offset = newSize / 2.0f;

    Coordinate centerX0Y0Z0(center.getX() - offset, center.getY() - offset, center.getZ() - offset);
    Coordinate centerX0Y0Z1(center.getX() - offset, center.getY() - offset, center.getZ() + offset);
    Coordinate centerX0Y1Z0(center.getX() - offset, center.getY() + offset, center.getZ() - offset);
    Coordinate centerX0Y1Z1(center.getX() - offset, center.getY() + offset, center.getZ() + offset);
    Coordinate centerX1Y0Z0(center.getX() + offset, center.getY() - offset, center.getZ() - offset);
    Coordinate centerX1Y0Z1(center.getX() + offset, center.getY() - offset, center.getZ() + offset);
    Coordinate centerX1Y1Z0(center.getX() + offset, center.getY() + offset, center.getZ() - offset);
    Coordinate centerX1Y1Z1(center.getX() + offset, center.getY() + offset, center.getZ() + offset);

    Cube cubeX0Y0Z0(centerX0Y0Z0, newSize);
    Cube cubeX0Y0Z1(centerX0Y0Z1, newSize);
    Cube cubeX0Y1Z0(centerX0Y1Z0, newSize);
    Cube cubeX0Y1Z1(centerX0Y1Z1, newSize);
    Cube cubeX1Y0Z0(centerX1Y0Z0, newSize);
    Cube cubeX1Y0Z1(centerX1Y0Z1, newSize);
    Cube cubeX1Y1Z0(centerX1Y1Z0, newSize);
    Cube cubeX1Y1Z1(centerX1Y1Z1, newSize);

    this->x0y0z0 = new Octree(cubeX0Y0Z0, this->capacity);
    this->x0y0z1 = new Octree(cubeX0Y0Z1, this->capacity);
	this->x0y1z0 = new Octree(cubeX0Y1Z0, this->capacity);
	this->x0y1z1 = new Octree(cubeX0Y1Z1, this->capacity);
	this->x1y0z0 = new Octree(cubeX1Y0Z0, this->capacity);
	this->x1y0z1 = new Octree(cubeX1Y0Z1, this->capacity);
	this->x1y1z0 = new Octree(cubeX1Y1Z0, this->capacity);
	this->x1y1z1 = new Octree(cubeX1Y1Z1, this->capacity);
	this->isDivided = true;
}
void Octree::query(Cube range, vector<Node> &nodesFound) {
	if (!boundary.intersects(range)) {
		return;
	} else {
		for (auto& node : nodesFound) {
			if (range.contains(node.getCoordinate())) {
				nodesFound.push_back(node);
			}
		}
		if (this->isDivided) {
			this->x0y0z0->query(range, nodesFound);
			this->x0y0z1->query(range, nodesFound);
			this->x0y1z0->query(range, nodesFound);
			this->x0y1z1->query(range, nodesFound);
			this->x1y0z0->query(range, nodesFound);
			this->x1y0z1->query(range, nodesFound);
			this->x1y1z0->query(range, nodesFound);
			this->x1y1z1->query(range, nodesFound);
		}
	}
}

void Octree::print() {
    cout << "Points in boundaries ((" << this->boundary.getMinX() << " - " << this->boundary.getMaxX() << "), (" << this->boundary.getMinY() << " - " << this->boundary.getMaxY() << "), (" << this->boundary.getMinZ() << " - " << this->boundary.getMaxZ() << ")): ";

    if (this->isDivided) {
        cout << endl;
        this->getX0Y0Z0()->print();
        this->getX0Y0Z1()->print();
        this->getX0Y1Z0()->print();
        this->getX0Y1Z1()->print();
        this->getX1Y0Z0()->print();
        this->getX1Y0Z1()->print();
        this->getX1Y1Z0()->print();
        this->getX1Y1Z1()->print();
    } else {
        for (auto& node : this->getNodes()) {
            cout << "(" << node.getCoordinate().getX() << ", " << node.getCoordinate().getY() << ", " << node.getCoordinate().getZ() << ") ";
        }
        cout << endl;
    }
}

string Octree::generateGraph() {
	std::stringstream ss;
	ss << "digraph Octree {\n";
	// ss << "splines = false" << endl;
	generateGraphRecursive(ss);
	ss << "}\n";
	return ss.str();
}

void Octree::generateGraphRecursive(std::stringstream& ss) {
	ss << "\"" << this << "\" [label=\"" << this->boundary.getCenter().getX() << ", " <<this->boundary.getCenter().getY() << ", " << this->boundary.getCenter().getZ() << "\"shape=circle];\n";
	if (isDivided) {
		ss << "\"" << this << "\" -> \"" << x0y0z0 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x0y0z1 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x0y1z0 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x0y1z1 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x1y0z0 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x1y0z1 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x1y1z0 << "\";\n";
		ss << "\"" << this << "\" -> \"" << x1y1z1 << "\";\n";
		x0y0z0->generateGraphRecursive(ss);
		x0y0z1->generateGraphRecursive(ss);
		x0y1z0->generateGraphRecursive(ss);
		x0y1z1->generateGraphRecursive(ss);
		x1y0z0->generateGraphRecursive(ss);
		x1y0z1->generateGraphRecursive(ss);
		x1y1z0->generateGraphRecursive(ss);
		x1y1z1->generateGraphRecursive(ss);
	}
}
