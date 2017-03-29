/*
 * Scale.cpp
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#include "Scale.h"

Scale::Scale() :
		point(0, 0, 0) {

}

Scale::Scale(double x, double y, double z) :
		point(x, y, z) {

}


Point3d Scale::getPoint3d() const {

	return point;

}

Scale::~Scale() {

}

