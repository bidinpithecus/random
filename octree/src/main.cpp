#include <GL/gl.h>
#include <GL/glut.h>
#include "Octree.hpp"

using namespace std;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float pointSize = 2;
Cube bigBoundary(200);
Octree octree = Octree(bigBoundary, 8);
vector<Node> nodes;

void showPoints();
void drawTree(Octree* tree);
void turnNodesOn();
void printCube(Cube cube);

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

void printCube(Cube cube) {
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 1, 1);
		// Bottom face
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMinZ());
		// Top face
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMaxY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMaxY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMinZ());
		// Front face
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMaxY(), cube.getMinZ());
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMinZ());
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMinZ());
		// Back face
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMaxZ());
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMaxZ());
		glVertex3f(cube.getMaxX(), cube.getMaxY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMaxZ());
		// Left face
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMinZ());
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMinZ());
		glVertex3f(cube.getMinX(), cube.getMaxY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMaxZ());
		glVertex3f(cube.getMinX(), cube.getMinY(), cube.getMinZ());
		// Right face
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMaxY(), cube.getMinZ());
		glVertex3f(cube.getMaxX(), cube.getMaxY(), cube.getMaxZ());
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMaxZ());
		glVertex3f(cube.getMaxX(), cube.getMinY(), cube.getMinZ());
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 2000.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glTranslatef(0, 0, -WINDOW_WIDTH / 2.0);

    // drawTree(&octree);
	showPoints();

    glutSwapBuffers();
}

void showPoints() {
	turnNodesOn();
	octree = Octree(bigBoundary, 8);
	for (auto& node : nodes) {
		glPointSize(node.getSize());
		glBegin(GL_POINTS);
		node.move();
		octree.insert(node);
		if (node.getHighlight()) {
			glColor4f(1.0, 0, 0, 1.0);
		} else {
			glColor4f(0.5, 0.5, 0.5, 0.4);
		}
		glVertex3f(node.getCoordinate().getX(), node.getCoordinate().getY(), node.getCoordinate().getZ());
		node.setHighlight(false);
		glEnd();
	}
}

void turnNodesOn() {
	for (auto& node : nodes) {
		vector<Node> collisions;
		Cube range(node.getCoordinate(), node.getSize());
		octree.query(range, collisions);
		if (collisions.size() > 1) {
			for (auto& otherNode : collisions) {
				otherNode.setHighlight(true);
				node.setHighlight(otherNode.getHighlight());
			}
		}
	}
}

int main(int argc, char** argv) {
    for (int i = 0; i < 2000; i++) {
		Node node = Node();
		node.setSize(pointSize);

		int randomX = randomInt(-octree.getBoundary().getSideSize() / 2 + node.getSize(), octree.getBoundary().getSideSize() / 2 - node.getSize());
		int randomY = randomInt(-octree.getBoundary().getSideSize() / 2 + node.getSize(), octree.getBoundary().getSideSize() / 2 - node.getSize());
		int randomZ = randomInt(-octree.getBoundary().getSideSize() / 2 + node.getSize(), octree.getBoundary().getSideSize() / 2 - node.getSize());

		node.setCoordinate(Coordinate(randomX, randomY, randomZ));
		nodes.push_back(node);
        octree.insert(node);
    }

	octree.print();

	string graphData = octree.generateGraph();

	ofstream file("data/octree.dot");
	file << graphData;
	file.close();

	string command = "dot -Tsvg data/octree.dot -o data/octree.svg";
	system(command.c_str());

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Octree");

    glutDisplayFunc(display);

	glutIdleFunc(display);

    glutMainLoop();

    return 0;
}
