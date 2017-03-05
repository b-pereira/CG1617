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

Triangle::Triangle(double xA, double yA, double zA, double xB, double yB,
		double zB, double xC, double yC, double zC) :
		a (xA, yA, zA), b(xB, yB, zB), c(xC, yC, zC) {
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

const Point3d& Triangle::getA() const {
	return a;
}

void Triangle::setA(const Point3d& a) {
	this->a = a;
}

const Point3d& Triangle::getB() const {
	return b;
}

void Triangle::setB(const Point3d& b) {
	this->b = b;
}

const Point3d& Triangle::getC() const {
	return c;
}

void Triangle::setC(const Point3d& c) {
	this->c = c;
}

