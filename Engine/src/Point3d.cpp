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

Point3d::Point3d(double x, double y, double z) :
		x_coord(x), y_coord (y), z_coord (z) {
}

double Point3d::getXCoord() const {
	return x_coord;
}

void Point3d::setXCoord(double coord) {
	x_coord = coord;
}

double Point3d::getYCoord() const {
	return y_coord;
}

void Point3d::setYCoord(double coord) {
	y_coord = coord;
}

double Point3d::getZCoord() const {
	return z_coord;
}

void Point3d::setZCoord(double coord) {
	z_coord = coord;
}



//Point3d Point3d::getLookAt(Point3d pt)

//	x_coord-=pt.getXCoord();
//	y_coord-=pt.getYCoord();
//	z_coord-=pt.getZCoord();

//	return this;
//}



Point3d::~Point3d() {
	// TODO Auto-generated destructor stub
}

