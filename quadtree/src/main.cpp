#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "QuadTree.hpp"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float pointSize = 1.0;
int randomInt(int min, int max);
Rectangle boundary(Point(1, 1), Point(WINDOW_WIDTH, WINDOW_HEIGHT));
QuadTree quadtree = QuadTree(boundary, 4);

std::vector<Point> points;

void drawQuadTree(QuadTree* tree) {
    // Draw the boundary of the current QuadTree node
    const Rectangle& boundary = tree->getBoundary();
	glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_LINE_LOOP);
		glVertex2f(boundary.topLeft.x, boundary.topLeft.y);
		glVertex2f(boundary.bottomRight.x, boundary.topLeft.y);
		glVertex2f(boundary.bottomRight.x, boundary.bottomRight.y);
		glVertex2f(boundary.topLeft.x, boundary.bottomRight.y);
    glEnd();

    // Recursively draw the QuadTree subdivisions if it is divided
    if (tree->isItDivided()) {
        drawQuadTree(tree->getNorthWest());
        drawQuadTree(tree->getNorthEast());
        drawQuadTree(tree->getSouthWest());
        drawQuadTree(tree->getSouthEast());
    }
}

void showPoints() {
	QuadTree qTree = QuadTree(boundary, 4);
    glPointSize(pointSize);
    glBegin(GL_POINTS);
	for (auto& point : points) {
		point.x += randomInt(-1, 1);
		point.y += randomInt(-1, 1);
		if (point.highlight) {
			glColor3f(1, 1, 1);
		} else {
		    glColor3f(0.5, 0.5, 0.5); // Set the color to white
		}
		point.highlight = false;
		qTree.insert(point);
        glVertex2f(point.x, point.y);
	}
    glEnd();

	for (auto& point : points) {
		std::vector<Point> wanted;
		Rectangle range = Rectangle(Point(point.x - (pointSize * 2), point.y - (pointSize * 2)), Point(point.x + (pointSize * 2), point.y + (pointSize * 2)));
		qTree.query(range, wanted);
		for (auto& otherPoint : wanted) {
			if (((point.x != otherPoint.x) || (point.y != otherPoint.y)) && point.dist(otherPoint) < pointSize * 2) {
				point.highlight = true;
				otherPoint.highlight = true;
			}
		}
	}
	drawQuadTree(&qTree);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);

	showPoints();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int randomInt(int min, int max) {
    unsigned int randomValue;
	FILE* fptr;
	fptr = fopen("/dev/random", "r");
	fread(&randomValue, sizeof(randomValue), 1, fptr);
	fclose(fptr);

	randomValue %= (max - min) + 1;
	randomValue += min;

    return randomValue;
}

int main(int argc, char** argv) {
    for (int i = 0; i < 1000; i++) {
		Point point = Point(randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT));
		points.push_back(point);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("QuadTree Visualization");

    glutDisplayFunc(display);
	glutIdleFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
