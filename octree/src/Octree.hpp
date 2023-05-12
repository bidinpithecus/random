#ifndef _OCTREE_HPP_
#define _OCTREE_HPP_

#include <vector>
#include "Cube.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

class Octree {
	public:
		Octree();
		~Octree();
		Octree(Cube boundary, int capacity);
		bool isItDivided();
		Cube getBoundary();
		std::vector<Node> getNodes();
		Octree* getX0Y0Z0();
		Octree* getX0Y0Z1();
		Octree* getX0Y1Z0();
		Octree* getX0Y1Z1();
		Octree* getX1Y0Z0();
		Octree* getX1Y0Z1();
		Octree* getX1Y1Z0();
		Octree* getX1Y1Z1();

		bool insert(Node node);
		void subdivide();
		void query(Cube range, std::vector<Node>& nodesFound);
		std::string generateGraph();
		void print();

	private:
		Cube boundary;
		long unsigned int capacity;
		std::vector<Node> nodes;
		bool isDivided;

		Octree* x0y0z0;
		Octree* x0y0z1;
		Octree* x0y1z0;
		Octree* x0y1z1;
		Octree* x1y0z0;
		Octree* x1y0z1;
		Octree* x1y1z0;
		Octree* x1y1z1;

		void generateGraphRecursive(std::stringstream& ss);
};

#endif
