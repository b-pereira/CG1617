/*
 * Rotation.cpp
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#include "Rotation.h"
#include "GL/glut.h"
#include <iostream>

Rotation::Rotation(float ang, float x, float y, float z) :
		point(x, y, z), angle(ang) {

}
Rotation::Rotation() :
		point(0, 0, 0), angle(0) {

}

float Rotation::getAngle() const {
	return angle;
}

const Point2d& Rotation::getPoint() const {
	return point;
}

void Rotation::applyTransformation() const {

	/*std::cout << "rotation"
			  << " angle =" << angle
			  << " axisX =" << point.getXCoord()
			  << " axisY =" << point.getYCoord()
			  << " axisZ =" << point.getZCoord()
			  << std::endl;*/
	glRotatef(angle, point.getXCoord(),
			point.getYCoord(), point.getZCoord());
}

Rotation::~Rotation() {

}

