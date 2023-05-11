#include "QuadTree.hpp"

QuadTree::QuadTree() {}

QuadTree::QuadTree(Rectangle boundary, int capacity) : boundary(boundary), capacity(capacity) {
	this->isDivided = false;
};

bool QuadTree::isItDivided() {
	return isDivided;
}

Rectangle QuadTree::getBoundary() {
	return boundary;
}

std::vector<Point> QuadTree::getPoints() {
	return points;
}

QuadTree* QuadTree::getNorthWest() {
	return northWest;
}

QuadTree* QuadTree::getNorthEast() {
	return northEast;
}

QuadTree* QuadTree::getSouthWest() {
	return southWest;
}

QuadTree* QuadTree::getSouthEast() {
	return southEast;
}

bool QuadTree::insert(Point point) {
	if (!this->boundary.contains(point)) {
		return false;
	}
	if (this->points.size() < this->capacity && !this->isDivided) {
		this->points.push_back(point);
		return true;
	} else {
		if (!this->isDivided) {
			std::vector<Point> emptyVec;
			this->subdivide();
			for (auto point : this->points) {
				this->insert(point);
			}
			this->points = emptyVec;
		}

		return this->northWest->insert(point) || this->northEast->insert(point) || this->southWest->insert(point) || this->southEast->insert(point);
	}
}

void QuadTree::subdivide() {
	Rectangle nw(boundary.topLeft, boundary.center);
	Rectangle ne(Point(boundary.center.x, boundary.topLeft.y), Point(boundary.bottomRight.x, boundary.center.y));
	Rectangle sw(Point(boundary.topLeft.x, boundary.center.y), Point(boundary.center.x, boundary.bottomRight.y));
	Rectangle se(boundary.center, boundary.bottomRight);
	isDivided = true;

	this->northWest = new QuadTree(nw, this->capacity);
	this->northEast = new QuadTree(ne, this->capacity);
	this->southWest = new QuadTree(sw, this->capacity);
	this->southEast = new QuadTree(se, this->capacity);
}

void QuadTree::query(Rectangle range, std::vector<Point>& found) {
    if (!boundary.intersects(range)) {
        return;
    } else {
        for (const auto& point : points) {
            if (range.contains(point)) {
                found.push_back(point);
            }
        }
        if (isDivided) {
            northWest->query(range, found);
            northEast->query(range, found);
            southWest->query(range, found);
            southEast->query(range, found);
        }
    }
}


void QuadTree::print() {
    if (this->isDivided) {
        this->northWest->print();
        this->northEast->print();
        this->southWest->print();
        this->southEast->print();
    } else {
        std::cout << "Points in node (" << this->boundary.topLeft.x << ", " << this->boundary.topLeft.y << ") - (" << this->boundary.bottomRight.x << ", " << this->boundary.bottomRight.y << "): ";
        for (const auto& point : this->points) {
            std::cout << "(" << point.x << ", " << point.y << ") ";
        }
        std::cout << std::endl;
    }
}
