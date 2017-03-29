/*
 * Translation.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include "Translation.h"

Translation::Translation() :
		point(0, 0, 0) {

}

Translation::Translation(double x, double y, double z) :
		point(x, y, z) {

}


Point3d Translation::getPoint3d() const {

	return point;

}

Translation::~Translation() {

}




