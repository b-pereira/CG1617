/*
 * AnimatedTranslation.cpp
 *
 *  Created on: 20/04/2017
 *     Author: rsilva
 */

#include "AnimatedTranslation.h"

#include "GL/glut.h"
#include <iostream>
#include "Point3d.h"

AnimatedTranslation::AnimatedTranslation() :
	time(0) {

}

AnimatedTranslation::AnimatedTranslation(double tim, vector<Point3d> pts) :
		time(tim), points(pts) {
}


const vector<Point3d>&AnimatedTranslation::getVector() const {
	return points;
}

void AnimatedTranslation::applyTransformation() const { //como é que crio um subgrupo para os pontos??
//	std::cout << "translate"
//			  << " time =" << time
//			  << " X =" << point.getXCoord()
//			  << " Y =" << point.getYCoord()
//			  << " Z =" << point.getZCoord()
//			  << std::endl;
//			glTranslatef(point.getXCoord(), point.getYCoord(),
//					point.getZCoord());
}

AnimatedTranslation::~AnimatedTranslation() {

}

