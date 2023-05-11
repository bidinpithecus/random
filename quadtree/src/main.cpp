#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "QuadTree.hpp"

QuadTree quadtree;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

void drawQuadTree(QuadTree* tree) {
    // Draw the boundary of the current QuadTree node
    const Rectangle& boundary = tree->getBoundary();
    glBegin(GL_LINE_LOOP);
    glVertex2f(boundary.topLeft.x, boundary.topLeft.y);
    glVertex2f(boundary.bottomRight.x, boundary.topLeft.y);
    glVertex2f(boundary.bottomRight.x, boundary.bottomRight.y);
    glVertex2f(boundary.topLeft.x, boundary.bottomRight.y);
    glEnd();

    // Draw the points inside the current QuadTree node
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (const auto& point : tree->getPoints()) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    // Recursively draw the QuadTree subdivisions if it is divided
    if (tree->isItDivided()) {
        drawQuadTree(tree->getNorthWest());
        drawQuadTree(tree->getNorthEast());
        drawQuadTree(tree->getSouthWest());
        drawQuadTree(tree->getSouthEast());
    }
}

void drawRange(const Rectangle& range) {
    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0); // Set the color to red

    glBegin(GL_LINE_LOOP);
    glVertex2f(range.topLeft.x, range.topLeft.y);
    glVertex2f(range.bottomRight.x, range.topLeft.y);
    glVertex2f(range.bottomRight.x, range.bottomRight.y);
    glVertex2f(range.topLeft.x, range.bottomRight.y);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Set the color to blue

    glPointSize(3.0);
    glBegin(GL_POINTS);

    std::vector<Point> foundPoints;
    quadtree.query(range, foundPoints);
    for (const auto& point : foundPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0); // Set the color to white

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    // Draw the QuadTree
    drawQuadTree(&quadtree);

    // Define the range to query
    Rectangle range(Point(200, 200), Point(400, 400));

    // Draw the queried range and colorize the points within the range
    drawRange(range);

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
    Rectangle boundary(Point(1, 1), Point(WINDOW_WIDTH, WINDOW_HEIGHT));
    quadtree = QuadTree(boundary, 4);

    for (int i = 0; i < 5; i++) {
        quadtree.insert(Point(randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT)));
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("QuadTree Visualization");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
