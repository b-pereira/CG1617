/*
 * AnimatedRotation.cpp
 *
 *  Created on: 20/04/2017
 *      Author: rsilva
 */

#include "AnimatedRotation.h"

#include "GL/glut.h"
#include <iostream>

AnimatedRotation::AnimatedRotation(float tim, float x, float y, float z) :
		point(x, y, z), time(tim) {

}
AnimatedRotation::AnimatedRotation() :
		point(0, 0, 0), time(0) {

}

float AnimatedRotation::getTime() const {
	return time;
}

const Point3d& AnimatedRotation::getPoint() const {
	return point;
}

void AnimatedRotation::applyTransformation() const {


	float t = ((glutGet(GLUT_ELAPSED_TIME))%(int)(time*1000))/(time*1000);


	glRotatef(t*360, point.getXCoord(),
				point.getYCoord(), point.getZCoord());

}

AnimatedRotation::~AnimatedRotation() {

}

