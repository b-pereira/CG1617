/*
 * Rotation.cpp
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#include "Rotation.h"

Rotation::Rotation(double ang, double x, double y, double z) :
		point(x, y, z), angle(ang) {

}
Rotation::Rotation() :
		point(0, 0, 0), angle(0) {

}

Point3d Rotation::getPoint3d() const {

	return point;

}
double Rotation::getAngle() const {

	return angle;
}

Rotation::~Rotation() {

}

