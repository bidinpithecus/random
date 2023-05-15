#include "Helpers.hpp"
#include <math.h>

double generateAnotherCoordinateOnSurface(double r, double y0, double c1, double c2, int xyz) {
	if (xyz == X) {
		return sqrt(pow(r, 2) - pow(c1, 2) + (2 * c1 * y0) - pow(y0, 2) - pow(c2, 2));
	} else if (xyz == Y) {
		return sqrt(pow(r, 2) - pow(c1, 2) - pow(c2, 2)) + y0;
		// return y0 - sqrt(pow(r, 2) - pow(c1, 2) - pow(c2, 2));
	} else if (xyz == Z) {
		return sqrt(pow(r, 2) - pow(c1, 2) - pow(c2 - y0, 2));
	} else {
		return 0;
	}
}

GLfloat generateCoordinateInsideSphere(GLfloat r, double y0, GLfloat c1, GLfloat c2) {
	float max = generateAnotherCoordinateOnSurface(r, c1, c2, y0, Y);

	return randomFloat(-max, max);
}

/*
	r stands for radius and x the sphere,
	y stands for the y position
*/
float calculateYAxisOfIntersection(float r0, float r1, float y0, float y1) {
	return ((y0 + y1) / 2.0) + ((pow(r0, 2) - pow(r1, 2)) / (2 * (y1 - y0)));
}

float calculateXAxisOfIntersection(float r, float y, float y0) {
	return sqrt(pow(r, 2) - pow(y - y0, 2));
}

int randomNum(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
    // Generate a random float between 0 and 1
    double randomDouble = (double)rand() / RAND_MAX;

    // Scale the random double to the desired range between min and max
    return min + randomDouble * (max - min);
}
