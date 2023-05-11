#ifndef _QUADTREE_HPP_
#define _QUADTREE_HPP_

#include <vector>
#include <iostream>
#include <cmath>

struct Point {
    float x;
    float y;
	float highlight;
    Point(float x, float y) : x(x), y(y) { highlight = false; };
    Point() : x(0), y(0) {};
	float dist(Point other) {
		return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
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
        return !(this->topLeft.x > rectangle.bottomRight.x || this->bottomRight.x < rectangle.topLeft.x ||
        this->bottomRight.y < rectangle.topLeft.y || this->topLeft.y > rectangle.bottomRight.y);
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

    private:
        Rectangle boundary;
        int capacity;
        std::vector<Point> points;
        bool isDivided;

        QuadTree* northWest;
        QuadTree* northEast;
        QuadTree* southWest;
        QuadTree* southEast;
};

#endif
