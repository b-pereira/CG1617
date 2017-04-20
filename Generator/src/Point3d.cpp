/*
 * Point3d.cpp
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#include "Point3d.h"

Point3d::Point3d() :
		x_coord(0), y_coord(0), z_coord(0) {
}

Point3d::Point3d(float x, float y, float z) :
		x_coord(x), y_coord (y), z_coord (z) {
}

float Point3d::getXCoord() const {
	return x_coord;
}

void Point3d::setXCoord(float coord) {
	x_coord = coord;
}

float Point3d::getYCoord() const {
	return y_coord;
}

void Point3d::setYCoord(float coord) {
	y_coord = coord;
}

float Point3d::getZCoord() const {
	return z_coord;
}

void Point3d::setZCoord(float coord) {
	z_coord = coord;
}

Point3d::~Point3d() {
	// TODO Auto-generated destructor stub
}

