#include "App.hpp"
#include "Camera.hpp"
#include "Color.hpp"

#define UNUSED __attribute__((unused))

Camera camera = Camera(Position(0, 0, -1), Position(0.0f, -0.75f, 5.0f), Position(0.0f, 1.0f, 0.0f), Position(0, 0, 0), 0.05f, -4.0f);

// Change viewing volume and viewport.  Called when window is resized
void resize(int width, int height) {
	GLfloat fAspect;

	// Prevent a divide by zero
	if (height == 0) {
		height = 1;
	}

	// Set Viewport to window dimensions
	glViewport(0, 0, width, height);
	fAspect = (GLfloat)width / (GLfloat)height;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Produce the perspective projection
	gluPerspective(45.0f, fAspect, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Respond to some other keys (move camera and zoom)
void normalKeyPressed(unsigned char key, UNUSED int x, UNUSED int y) {
    switch(key) {
        // Move the camera forward when the "W" key is pressed
        case 'w':
        case 'W':
			camera.setPosition(Position(camera.getPosition().getX(), camera.getPosition().getY() + camera.getSpeed(), camera.getPosition().getZ()));
            break;

        // Move the camera backward when the "S" key is pressed
        case 's':
        case 'S':
			camera.setPosition(Position(camera.getPosition().getX(), camera.getPosition().getY() - camera.getSpeed(), camera.getPosition().getZ()));
            break;

        // Move the camera to the left when the "A" key is pressed
        case 'a':
        case 'A':
			camera.setPosition(Position(camera.getPosition().getX() - camera.getSpeed(), camera.getPosition().getY(), camera.getPosition().getZ()));
            break;

        // Move the camera to the right when the "D" key is pressed
        case 'D':
        case 'd':
			camera.setPosition(Position(camera.getPosition().getX() + camera.getSpeed(), camera.getPosition().getY(), camera.getPosition().getZ()));
            break;

		// Zoom out when the "z" key is pressed
		case 'z':
			camera.setZoom(camera.getZoom() - (camera.getSpeed() * 2));
			break;

		// Zoom in when the "z" key is pressed
		case 'Z':
			camera.setZoom(camera.getZoom() + (camera.getSpeed() * 2));
			break;

        // Exit the program when the "ESC" key is pressed
        case 27:
            exit(0);
            break;
    }

    // Redraw the scene
    glutPostRedisplay();
}

void initScene() {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.getPosition().getX(), camera.getPosition().getY(), camera.getPosition().getZ(), camera.getPosition().getX() + camera.getDirection().getX(), camera.getPosition().getY() + camera.getDirection().getY(), camera.getPosition().getZ() + camera.getDirection().getZ(), camera.getUp().getX(), camera.getUp().getY(), camera.getUp().getZ());

	// Save the matrix state and do the rotations
	glPushMatrix();

	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, camera.getZoom());
	glRotatef(camera.getRotation().getY(), 1.0f, 0.0f, 0.0f);
	glRotatef(camera.getRotation().getX(), 0.0f, 1.0f, 0.0f);
}

void finishScene() {
	glPopMatrix();
	glutSwapBuffers();
}

void renderScene() {
	initScene();
	drawScene();
	finishScene();
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
void setupRC() {
	// Light values and coordinates
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

	// Hidden surface removal
	glEnable(GL_DEPTH_TEST);
	// Counter clock-wise polygons face out
	glFrontFace(GL_CCW);
	// Do not calculate inside
	glEnable(GL_CULL_FACE);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Main background color
	Color backgroundColor = Color(0x555555);
	// Off-white background
	glClearColor(backgroundColor.getRed(), backgroundColor.getGreen(), backgroundColor.getBlue(), 1.0f);
}

// Respond to arrow keys (rotate snowman)
void specialKeyPressed(int key, UNUSED int x, UNUSED int y) {
	float rotationSpeed = camera.getSpeed() * 100;
	switch (key) {
		case GLUT_KEY_DOWN:
			camera.setRotation(Position(camera.getRotation().getX(), camera.getRotation().getY() - rotationSpeed, camera.getRotation().getZ()));
			break;

		case GLUT_KEY_UP:
			camera.setRotation(Position(camera.getRotation().getX(), camera.getRotation().getY() + rotationSpeed, camera.getRotation().getZ()));
			break;

		case GLUT_KEY_LEFT:
			camera.setRotation(Position(camera.getRotation().getX() + rotationSpeed, camera.getRotation().getY(), camera.getRotation().getZ()));
			break;

		case GLUT_KEY_RIGHT:
			camera.setRotation(Position(camera.getRotation().getX() - rotationSpeed, camera.getRotation().getY(), camera.getRotation().getZ()));
			break;

		case GLUT_KEY_F11:
			toggleFullScreen();
			break;
	}

	camera.setRotation(Position((int) camera.getRotation().getX() % 360, (int) camera.getRotation().getY() % 360, camera.getRotation().getZ()));

	// Refresh the Window
	glutPostRedisplay();
}

void toggleFullScreen() {
	if (isFullScreen) {
		glutReshapeWindow(width, height);
		glutPositionWindow(xPos, yPos);
	} else {
		width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);
		xPos = glutGet(GLUT_WINDOW_X);
		yPos = glutGet(GLUT_WINDOW_Y);

		glutFullScreen();
	}
	isFullScreen = !isFullScreen;
}
