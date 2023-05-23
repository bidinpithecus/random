#include "App.hpp"
#include "Shapes.hpp"
#include "Coordinate.hpp"
#include "Particle.hpp"
#include "Helpers.hpp"
#include <ctime>
#include <vector>

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;

Sphere sphere;
GLUquadricObj *pObj;

vector<Particle> particles;

void drawScene(void) {
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	for (auto& particle : particles) {
		particle.update();
		particle.show(pObj);
	}
}

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));
	for (int i = 0; i < 500; i++) {
		Particle particle;
		int x = randomNum(-40, 40);
		int y = randomNum(-40, 40);
		int z = randomNum(-10, 10);
		particle.setSize(0.5);
		particle.setViewDistance(2.0);
		particle.setSpeed(0.001);
		particle.setPosition(Coordinate(x, y, z));
		particle.setVelocity(Coordinate(0));
		particle.setAcceleration(Coordinate(0));
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
	glutIdleFunc(renderScene);
	setupRC();
	glutMainLoop();

	return 0;
}
