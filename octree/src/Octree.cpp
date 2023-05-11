#include "Octree.hpp"

using namespace std;

Octree::Octree() {}

Octree::Octree(Cube boundary, int capacity) : boundary(boundary), capacity(capacity) { isDivided = false; }

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
	// Node is outside of the boundary
	if (!this->boundary.contains(node)) { return false; }
	// If octree is available, add the node in the list of nodes of this octree
	// If not, subdivide it, try to insert it again and reset the nodes of the octree
	if (this->nodes.size() < this->capacity && !this->isDivided) {
		this->nodes.push_back(node);
		return true;
	} else {
		if (!this->isDivided) {
			vector<Node> emptyVec;
			this->subdivide();

			for (auto node : this->nodes) {
				this->insert(node);
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
	Cube cubeX0Y0Z0 = Cube();
	Cube cubeX0Y0Z1 = Cube();
	Cube cubeX0Y1Z0 = Cube();
	Cube cubeX0Y1Z1 = Cube();
	Cube cubeX1Y0Z0 = Cube();
	Cube cubeX1Y0Z1 = Cube();
	Cube cubeX1Y1Z0 = Cube();
	Cube cubeX1Y1Z1 = Cube();

	x0y0z0 = new Octree(cubeX0Y0Z0, this->capacity);
	x0y0z1 = new Octree(cubeX0Y0Z1, this->capacity);
	x0y1z0 = new Octree(cubeX0Y1Z0, this->capacity);
	x0y1z1 = new Octree(cubeX0Y1Z1, this->capacity);
	x1y0z0 = new Octree(cubeX1Y0Z0, this->capacity);
	x1y0z1 = new Octree(cubeX1Y0Z1, this->capacity);
	x1y1z0 = new Octree(cubeX1Y1Z0, this->capacity);
	x1y1z1 = new Octree(cubeX1Y1Z1, this->capacity);
}
