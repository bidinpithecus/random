#include "Color.hpp"
#include <GL/gl.h>

// Default constructor
Color::Color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

// Constructor receives a hex integer and set the color converting it to rgb standards
Color::Color(int hexColor) {
	this->r = ((hexColor >> 16) & 0xFF) / 255.0;
	this->g = ((hexColor >> 8) & 0xFF) / 255.0;
	this->b = ((hexColor) & 0xFF) / 255.0;
	this->a = 1.0;
}

// Constructor receives all colors in float [0, 1]
Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0;
}

// Constructor receives all colors in float [0, 1]
Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

// Constructor receives all colors in unsigned char [0, 255]
Color::Color(unsigned char r, unsigned char g, unsigned char b) {
	this->r = r / 255.0;
	this->g = g / 255.0;
	this->b = b / 255.0;
	this->a = 1.0;
}

// Constructor receives all colors in unsigned char [0, 255]
Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	this->r = r / 255.0;
	this->g = g / 255.0;
	this->b = b / 255.0;
	this->a = a / 255.0;
}

float Color::getRed() {
	return this->r;
}

float Color::getGreen() {
	return this->g;
}

float Color::getBlue() {
	return this->b;
}

float Color::getSaturation() {
	return this->a;
}

void Color::setRed(float r) {
	this->r = r;
}

void Color::setGreen(float g) {
	this->g = g;
}

void Color::setBlue(float b) {
	this->b = b;
}

void Color::setSaturation(float a) {
	this->a = a;
}

void Color::paint() {
	glColor3f(this->getRed(), this->getGreen(), this->getBlue());
}
