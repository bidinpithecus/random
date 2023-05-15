#include "Camera.hpp"
#include "snowman.h"
#include "Color.hpp"
#include "Shapes.hpp"
#include "Helpers.hpp"
#include "Coordinate.hpp"
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;

Color color;
Cylinder cylinder;
Disk disk;
Sphere sphere;
Position position;
Rotation rotation;
GLUquadricObj *pObj;

vector<Coordinate> fibPoints;

float phi = M_PI * (sqrt(5.0) - 1.0);

vector<Coordinate> fibonacciSphere(float scalar, int numOfPoints) {
	vector<Coordinate> points;
	float theta;
	float radius;
	float x, y, z;
	Coordinate coord;
	for (int i = 0; i < numOfPoints; i++) {
		theta = phi * i;
		y = 1 - (i / (float) (numOfPoints - 1)) * 2;
		radius = sqrt(1 - y * y);
		x = cos(theta) * radius;
		z = sin(theta) * radius;

		points.push_back(Coordinate(x, y, z) * scalar);
	}
	return points;
}

void drawScene(void) {
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		gluSphere(pObj, 1, 26, 13);
	glPopMatrix();

	for (auto coord : fibPoints) {
	glPushMatrix();
		glTranslatef(coord.getX(), coord.getY(), coord.getZ());
		glColor3f(0, 1.0, 0.0);
		gluSphere(pObj, 0.01, 26, 13);
	glPopMatrix();
	}
}

int main(int argc, char *argv[]) {
	fibPoints = fibonacciSphere(1, 1000);
    // Seed the random number generator with the current time
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
