/*
 * Point2d.cpp
 *
 *  Created on: 6/5/2017
 *      Author: bpereira
 */

#include "Point2d.h"

Point2d::Point2d() :
		x_coord(0), y_coord(0) {
}

Point2d::Point2d(float x, float y) :
		x_coord(x), y_coord (y) {
}

float Point2d::getXCoord() const {
	return x_coord;
}

void Point2d::setXCoord(float coord) {
	x_coord = coord;
}

float Point2d::getYCoord() const {
	return y_coord;
}

void Point2d::setYCoord(float coord) {
	y_coord = coord;
}



Point2d::~Point2d() {
	// TODO Auto-generated destructor stub
}

