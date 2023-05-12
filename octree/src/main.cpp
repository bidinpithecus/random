#include <GL/gl.h>
#include <GL/glut.h>
#include "Octree.hpp"

using namespace std;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float pointSize = 2;
int randomInt(int min, int max);
Cube bigBoundary(800); // Increased the size of the cube
Octree octree = Octree(bigBoundary, 8);
vector<Node> nodes;

void drawTree(Octree* tree) {
    Cube boundary = tree->getBoundary();

    // Draw the cube
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_LINE_LOOP);
		// Bottom face
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMinZ());
		// Top face
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMaxY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMaxY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMinZ());
		// Front face
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMaxY(), boundary.getMinZ());
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMinZ());
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMinZ());
		// Back face
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMaxZ());
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMaxZ());
		glVertex3f(boundary.getMaxX(), boundary.getMaxY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMaxZ());
		// Left face
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMinZ());
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMinZ());
		glVertex3f(boundary.getMinX(), boundary.getMaxY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMaxZ());
		glVertex3f(boundary.getMinX(), boundary.getMinY(), boundary.getMinZ());
		// Right face
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMaxY(), boundary.getMinZ());
		glVertex3f(boundary.getMaxX(), boundary.getMaxY(), boundary.getMaxZ());
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMaxZ());
		glVertex3f(boundary.getMaxX(), boundary.getMinY(), boundary.getMinZ());
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POINTS);
	for (auto node : tree->getNodes()) {
		glPointSize(node.getSize());
		glVertex3f(node.getCoordinate().getX(), node.getCoordinate().getY(), node.getCoordinate().getZ());
	}
	glEnd();

    if (tree->isItDivided()) {
        drawTree(tree->getX0Y0Z0());
        drawTree(tree->getX0Y0Z1());
        drawTree(tree->getX0Y1Z0());
        drawTree(tree->getX0Y1Z1());
        drawTree(tree->getX1Y0Z0());
        drawTree(tree->getX1Y0Z1());
        drawTree(tree->getX1Y1Z0());
        drawTree(tree->getX1Y1Z1());
    }
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10000.0); // Increased the far clipping plane distance

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 2000.0,   // Camera position (moved away from the cube)
        0.0, 0.0, 0.0,      // Look at position (center of the cube)
        0.0, 1.0, 0.0      // Up vector
    );

    glTranslatef(-WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, -WINDOW_WIDTH / 2.0);

    glPointSize(pointSize);

    drawTree(&octree);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    for (int i = 0; i < 50; i++) {
		int randomX = randomInt(-octree.getBoundary().getSideSize() / 2, octree.getBoundary().getSideSize() / 2);
		int randomY = randomInt(-octree.getBoundary().getSideSize() / 2, octree.getBoundary().getSideSize() / 2);
		int randomZ = randomInt(-octree.getBoundary().getSideSize() / 2, octree.getBoundary().getSideSize() / 2);

		Node node(Coordinate(randomX, randomY, randomZ), pointSize);
        octree.insert(node);
    }

	octree.print();

	string graphData = octree.generateGraph();

	ofstream file("data/octree.dot");
	file << graphData;
	file.close();

	string command = "dot -Tsvg data/octree.dot -o data/octree.svg";
	system(command.c_str());

    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Octree");

    // Set the display callback function
    glutDisplayFunc(display);

    // Enter the main loop
    glutMainLoop();

    return 0;
}
