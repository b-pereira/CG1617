/*
 * Translation.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include "Translation.h"
#include "GL/glut.h"
#include <iostream>

Translation::Translation() :
	time(0) {

}

Translation::Translation(double tim, vector<Point3d> pts) :
		time(tim), points(pts) {
}


const vector&Translation::getVector() const {
	return points;
}

void Translation::applyTransformation() const { //como é que crio um subgrupo para os pontos??
	std::cout << "translate"
			  << " time =" << time
			  << " X =" << point.getXCoord()
			  << " Y =" << point.getYCoord()
			  << " Z =" << point.getZCoord()
			  << std::endl;
			glTranslatef(point.getXCoord(), point.getYCoord(),
					point.getZCoord());
}

Translation::~Translation() {

}

