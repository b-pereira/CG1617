/*
 * AnimatedRotation.cpp
 *
 *  Created on: 20/04/2017
 *      Author: rsilva
 */

#include "AnimatedRotation.h"

#include "GL/glut.h"
#include <iostream>

AnimatedRotation::AnimatedRotation(double tim, double x, double y, double z) :
		point(x, y, z), time(tim) {

}
AnimatedRotation::AnimatedRotation() :
		point(0, 0, 0), time(0) {

}

double AnimatedRotation::getTime() const {
	return time;
}

const Point3d& AnimatedRotation::getPoint() const {
	return point;
}

void AnimatedRotation::applyTransformation() const {

	std::cout << "rotation"
			  << " time =" << time
			  << " axisX =" << point.getXCoord()
			  << " axisY =" << point.getYCoord()
			  << " axisZ =" << point.getZCoord()
			  << std::endl;
	glRotatef(time, point.getXCoord(),
			point.getYCoord(), point.getZCoord());
}

AnimatedRotation::~AnimatedRotation() {

}

