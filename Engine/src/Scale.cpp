/*
 * Scale.cpp
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#include "Scale.h"
#include "GL/glut.h"
#include <iostream>

Scale::Scale() :
		point(0, 0, 0) {

}

Scale::Scale(float x, float y, float z) :
		point(x, y, z) {

}

const Point2d&Scale::getPoint() const {
	return point;
}
void Scale::applyTransformation() const {

	/*std::cout << "scale"
			  << " X =" << point.getXCoord()
			  << " Y =" << point.getYCoord()
			  << " Z =" << point.getZCoord()
			  << std::endl;*/
			glScalef(point.getXCoord(), point.getYCoord(),
					point.getZCoord());

}

Scale::~Scale() {

}

