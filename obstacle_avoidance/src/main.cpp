#include "App.hpp"
#include "Shapes.hpp"
#include "Coordinate.hpp"
#include "Particle.hpp"
#include "Helpers.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
float fps = 0.0;

GLUquadricObj *pObj;
vector<Particle> particles;

void getFps() {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - previousTime;
	frameCount++;

	if (deltaTime > 100) {
		fps = frameCount / (deltaTime / 1000.0);

		frameCount = 0;
		previousTime = currentTime;
	}
}

void overlayScene(void) {
	char fpsStr[16];
	sprintf(fpsStr, "FPS: %.2f", fps);
    int strHeight = 12;
	int strWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)fpsStr);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2i(width - strWidth, height - strHeight);

	for (int i = 0; fpsStr[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, fpsStr[i]);
	}

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
	getFps();
	glutPostRedisplay();
}

void drawScene() {
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	for (auto& particle : particles) {
		particle.show(pObj);
	}
}

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));
	for (int i = 0; i < 500; i++) {
		int x = randomNum(-40, 40);
		int y = randomNum(-40, 40);
		int z = randomNum(-10, 10);
		float size = 0.5;
		float viewDistance = 2.0;
		float speed = 0.001;
		auto position = Coordinate(x, y, z);
		auto velocity = Coordinate(0);
		auto acceleration = Coordinate(0);
		Particle particle(acceleration, position, velocity, viewDistance, size, speed);
		particles.push_back(particle);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Obstacle Avoidance");
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	setupRC();
	glutMainLoop();

	return 0;
}
