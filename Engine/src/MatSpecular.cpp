/*
 * MatSpecular.cpp
 *
 *  Created on: 15/05/2017
 *      Author: bpereira
 */

#include "MatSpecular.h"
#include <GL/glut.h>

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
