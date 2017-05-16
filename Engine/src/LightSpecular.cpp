/*
 * LightSpecular.cpp
 *
 *  Created on: 15/05/2017
 *      Author: bpereira
 */

#include "LightSpecular.h"
#include <GL/glut.h>

LightSpecular::LightSpecular(GLenum numLight) :
		light(numLight), specular(0.0f, 0.0f, 0.0f, 1.0f) {

}

LightSpecular::LightSpecular(GLenum numLight, float red, float green,
		float blue) :
		light(numLight), specular(red, green, blue, 1.0f) {

}

LightSpecular::LightSpecular(GLenum numLight, float red, float green,
		float blue, float alpha) :
		light(numLight), specular(red, green, blue, alpha) {

}

void LightSpecular::applyProperties() const {

	glLightfv(light, GL_DIFFUSE, &specular.getRGBA()[0]);

}

LightSpecular::~LightSpecular() {
}

