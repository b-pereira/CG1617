/*
 * MatDiffuse.cpp
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#include "MatDiffuse.h"
#include <GL/glut.h>

MatDiffuse::MatDiffuse(float red, float green, float blue, float alpha) :
		diffuse(red, green, blue, alpha) {
}

void MatDiffuse::applyProperties() const {

	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.getRGBA()[0]);

}

MatDiffuse::~MatDiffuse() {
}

