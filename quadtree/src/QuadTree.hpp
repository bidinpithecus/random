#ifndef _QUADTREE_HPP_
#define _QUADTREE_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

struct Point {
    float x;
    float y;
	float highlight;
    Point(float x, float y) : x(x), y(y) { highlight = false; };
    Point() : x(0), y(0) {};
	float squaredDist(Point other) {
		return pow(this->x - other.x, 2) + pow(this->y - other.y, 2);
	};
};

struct Rectangle {
    Point topLeft;
    Point bottomRight;
    Point center;
    Rectangle() {};
    Rectangle(Point topLeft, Point bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {
        center.x = (topLeft.x + bottomRight.x) / 2.0;
        center.y = (topLeft.y + bottomRight.y) / 2.0;
    };
    bool contains(Point point) {
       return (point.x >= topLeft.x && point.x <= bottomRight.x) && (point.y >= topLeft.y && point.y <= bottomRight.y);
    }
    bool intersects(Rectangle rectangle) {
		bool intersectX = (rectangle.topLeft.x <= this->bottomRight.x) && (rectangle.bottomRight.x >= this->topLeft.x);
		bool intersectY = (rectangle.topLeft.y <= this->bottomRight.y) && (rectangle.bottomRight.y >= this->topLeft.y);
        return intersectX && intersectY;
    }
};

class QuadTree {
    public:
        QuadTree();
        QuadTree(Rectangle boundary, int capacity);
        bool isItDivided();
        Rectangle getBoundary();
        std::vector<Point> getPoints();
        QuadTree* getNorthWest();
        QuadTree* getNorthEast();
        QuadTree* getSouthWest();
        QuadTree* getSouthEast();

        bool insert(Point point);
        void subdivide();
        void query(Rectangle range, std::vector<Point>& found);
        void print();
		std::string generateGraphviz();

    private:
        Rectangle boundary;
        long unsigned int capacity;
        std::vector<Point> points;
        bool isDivided;

        QuadTree* northWest;
        QuadTree* northEast;
        QuadTree* southWest;
        QuadTree* southEast;

		void generateGraphvizRecursive(std::stringstream& ss);
};

#endif
