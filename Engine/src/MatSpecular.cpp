/*
 * MatSpecular.cpp
 *
 *  Created on: 15/05/2017
 *      Author: bpereira
 */

#include "MatSpecular.h"
#include <GL/glut.h>
#include <iostream>

MatSpecular::MatSpecular() :
		specular(0, 0, 0, 1), shin(0) {

}

MatSpecular::MatSpecular(float red, float green, float blue, float alpha,
		float shininess) :
		specular(red, green, blue, alpha), shin(shininess) {

}

void MatSpecular::applyProperties() const {

	glMaterialfv(GL_FRONT, GL_DIFFUSE, &specular.getRGBA()[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shin);

}

MatSpecular::~MatSpecular() {
}

