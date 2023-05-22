#include "App.hpp"
#include "Shapes.hpp"
#include "Coordinate.hpp"
#include "Helpers.hpp"
#include <GL/freeglut_std.h>
#include <ctime>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;

Cylinder cylinder;
Disk disk;
Sphere sphere;
Position position;
Rotation rotation;
GLUquadricObj *pObj;

vector<pair<Coordinate, float>> spheres;

vector<Coordinate> fibPoints;
float howFarOneSees = 2;

void drawParticle(Coordinate sphereCenter, float sphereRadius, int numOfPoints) {
	auto fibPoints = fibonacciSphere(sphereCenter, sphereRadius, numOfPoints);
	glPushMatrix();
		glTranslatef(sphereCenter.getX(), sphereCenter.getY(), sphereCenter.getZ());
		glColor3f(0.1, 0.1, 0.1);
		gluSphere(pObj, sphereRadius, 10, 5);
	glPopMatrix();


	for (auto coord : fibPoints) {
		glColor3f(0, 0.75, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3f(coord.getX(), coord.getY(), coord.getZ());
			coord = sphereCenter + ((coord - sphereCenter) / Coordinate(coord - sphereCenter).magnitude()) * howFarOneSees * sphereRadius;
			glVertex3f(coord.getX(), coord.getY(), coord.getZ());
		glEnd();
	}
}

void drawScene(void) {
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	for (auto& particle : spheres) {
		particle.first.setZ(particle.first.getZ() + 0.01);
		drawParticle(particle.first, particle.second, 450);
	}
}

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));

	for (int i = 0; i < 500; i++) {
		int x = randomNum(-40, 40);
		int y = randomNum(-40, 40);
		int z = randomNum(-10, 10);
		float size = 0.5;
		spheres.push_back(make_pair(Coordinate(x, y, z), size));
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Obstacle Avoidance");
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	setupRC();
	glutMainLoop();

	return 0;
}
