#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "Utils.hpp"
#include <vector>
#include <GL/gl.h>

class Camera {
	public:
		Camera();
		Camera(Position Direction, Position position, Position up, Position rotation, GLfloat speed, GLfloat zoom);

		void setDirection(Position direction);
		void setPosition(Position position);
		void setUp(Position up);
		void setRotation(Position rotation);
		void setSpeed(GLfloat speed);
		void setZoom(GLfloat zoom);

		Position getDirection();
		Position getPosition();
		Position getUp();
		Position getRotation();
		GLfloat getSpeed();
		GLfloat getZoom();

	private:
		Position direction;
		Position position;
		Position up;
		Position rotation;
		GLfloat speed;
		GLfloat zoom;
};

#endif
