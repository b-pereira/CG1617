/*
 * RGBA.cpp
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#include "RGBA.h"

RGBA::RGBA(float red, float green, float blue, float alpha) :
		r(red), g(green), b(blue), a(alpha) {
}

std::vector<float> RGBA::getRGBA() const {

	std::vector<float> res(4);

	res[0] = r;
	res[1] = g;
	res[2] = b;
	res[3] = a;

	return res;

}

RGBA::~RGBA() {
}

