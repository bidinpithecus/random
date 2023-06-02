#include "Helpers.hpp"

using namespace std;

vector<Coordinate> fibonacciPoints = fibonacciSphere(NUM_OF_POINTS);

int randomNum(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
    // Generate a random float between 0 and 1
    double randomDouble = (double)rand() / RAND_MAX;

    // Scale the random double to the desired range between min and max
    return min + randomDouble * (max - min);
}

vector<Coordinate> fibonacciSphere(int numOfPoints) {
	vector<Coordinate> points;
	float theta;
	float radius;
	float x, y, z;
	Coordinate coord;
	for (int i = 0; i < numOfPoints; i++) {
		theta = M_PHI * i;
		if (theta / (numOfPoints * 0.01) >= 300) {
			z = 1 - (i / (float) (numOfPoints - 1)) * 2;
			radius = sqrt(1 - z * z);
			y = cos(theta) * radius;
			x = sin(theta) * radius;

			points.push_back(Coordinate(x, y, z));
		}
	}
	return points;
}

float coordsDistance(Coordinate coordA, Coordinate coordB) {
	return sqrt(
		pow(coordA.getX() - coordB.getX(), 2) +
		pow(coordA.getY() - coordB.getX(), 2) +
		pow(coordA.getZ() - coordB.getX(), 2));
}
