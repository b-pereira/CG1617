/*
 * Triangle.cpp
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#include "Triangle.h"

#include "Point3d.h"

Triangle::Triangle() :
		a(), b(), c() {
}

Triangle::Triangle(float xA, float yA, float zA, float xB, float yB,
		float zB, float xC, float yC, float zC) :
		a (xA, yA, zA), b(xB, yB, zB), c(xC, yC, zC) {
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

const Point2d& Triangle::getA() const {
	return a;
}

void Triangle::setA(const Point2d& a) {
	this->a = a;
}

const Point2d& Triangle::getB() const {
	return b;
}

void Triangle::setB(const Point2d& b) {
	this->b = b;
}

const Point2d& Triangle::getC() const {
	return c;
}

void Triangle::setC(const Point2d& c) {
	this->c = c;
}

