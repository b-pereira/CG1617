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
		point(0, 0, 0) {

}

Translation::Translation(float x, float y, float z) :
		point(x, y, z) {

}

const Point2d&Translation::getPoint() const {
	return point;
}

void Translation::applyTransformation() const {
	/*std::cout << "translate"
			  << " X =" << point.getXCoord()
			  << " Y =" << point.getYCoord()
			  << " Z =" << point.getZCoord()
			  << std::endl;*/
			glTranslatef(point.getXCoord(), point.getYCoord(),
					point.getZCoord());
}

Translation::~Translation() {

}

