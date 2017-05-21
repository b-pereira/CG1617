/*
 * MatAmbient.cpp
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#include "MatAmbient.h"
#include <GL/glut.h>

MatAmbient::MatAmbient() :
		ambient(0.2, 0.2, 0.2, 1.0) {
}

MatAmbient::MatAmbient(float red, float green, float blue, float alpha) :
		ambient(red, green, blue, alpha) {
}

void MatAmbient::applyProperties() const {

	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.getRGBA()[0]);

}

MatAmbient::~MatAmbient() {
}

