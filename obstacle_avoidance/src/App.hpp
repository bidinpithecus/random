#ifndef _APP_H_
#define _APP_H_

#include "Utils.hpp"
#include "Camera.hpp"

class App {
	public:
		App();
		void setup();

	private:
		Camera camera;
};

extern int height;
extern int width;
extern int xPos;
extern int yPos;
extern bool isFullScreen;

extern Camera camera;

void drawScene();
void initScene();
void finishScene();
void normalKeyPressed(unsigned char key, int x, int y);
void renderScene(void);
void setupRC();
void specialKeyPressed(int key, int x, int y);
void toggleFullScreen();
void resize(int x, int y);

#endif
