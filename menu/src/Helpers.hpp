#ifndef _HELPERS_HPP_
#define _HELPERS_HPP_

#include <GL/gl.h>
#include "Color.hpp"
#include "Shapes.hpp"
#include "Utils.hpp"
#include <cmath>
#include "Coordinate.hpp"
#include <vector>

#define M_PHI 3.88322207745093300000
#define NUM_OF_POINTS 300

extern std::vector<Coordinate> fibonacciPoints;

double generateAnotherCoordinateOnSurface(double r, double y0, double c1, double c2, int xyz);
GLfloat generateCoordinateInsideSphere(GLfloat r, double y0, GLfloat c1, GLfloat c2);
float calculateYAxisOfIntersection(float r0, float r1, float y0, float y1);
float calculateXAxisOfIntersection(float r, float y, float y0);

std::vector<Coordinate> fibonacciSphere(int numOfPoints);

int randomNum(int min, int max);
float randomFloat(float min, float max);
float coordsDistance(Coordinate coordA, Coordinate coordB);

#endif
