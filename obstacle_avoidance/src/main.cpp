#include "App.hpp"
#include "Shapes.hpp"
#include "Coordinate.hpp"
#include "Helpers.hpp"
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

Coordinate sphereCenter(1, 1, 1);
float sphereRadius = 1;

vector<Coordinate> fibPoints;
float howFarOneSees = 5;

void drawParticle() {

}

void drawScene(void) {
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	glPushMatrix();
		glTranslatef(sphereCenter.getX(), sphereCenter.getY(), sphereCenter.getZ());
		glColor3f(0.1, 0.1, 0.1);
		gluSphere(pObj, sphereRadius, 26, 13);
	glPopMatrix();

	for (auto coord : fibPoints) {
		glPushMatrix();
			glTranslatef(coord.getX(), coord.getY(), coord.getZ());
			glColor3f(0, 0.25, 0.0);
			gluSphere(pObj, sphereRadius * 0.02, 4, 4);
		glPopMatrix();

		glColor3f(0, 0.75, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3f(coord.getX(), coord.getY(), coord.getZ());
			coord = sphereCenter + ((coord - sphereCenter) / Coordinate(coord - sphereCenter).magnitude()) * howFarOneSees;
			glVertex3f(coord.getX(), coord.getY(), coord.getZ());

		glEnd();
	}
}

int main(int argc, char *argv[]) {
	fibPoints = fibonacciSphere(sphereCenter, sphereRadius, 450);
    srand((unsigned int)time(NULL));
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
