/*
 * Rotation.cpp
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#include "Rotation.h"
#include "GL/glut.h"
#include <iostream>

Rotation::Rotation(double tim, double x, double y, double z) :
		point(x, y, z), time(tim) {

}
Rotation::Rotation() :
		point(0, 0, 0), time(0) {

}

double Rotation::getTime() const {
	return time;
}

const Point3d& Rotation::getPoint() const {
	return point;
}

void Rotation::applyTransformation() const {

	std::cout << "rotation"
			  << " time =" << time
			  << " axisX =" << point.getXCoord()
			  << " axisY =" << point.getYCoord()
			  << " axisZ =" << point.getZCoord()
			  << std::endl;
	glRotatef(time, point.getXCoord(),
			point.getYCoord(), point.getZCoord());
}

Rotation::~Rotation() {

}

