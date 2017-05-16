/*
 * LightSpecular.h
 *
 *  Created on: 15/05/2017
 *      Author: bpereira
 */

#ifndef SRC_LIGHTSPECULAR_H_
#define SRC_LIGHTSPECULAR_H_

#include "LightProperty.h"
#include "RGBA.h"
#include <GL/glut.h>

class LightSpecular: public virtual LightProperty {
public:
	LightSpecular(GLenum numLight);
	LightSpecular(GLenum numLight,float red, float green, float blue);
	LightSpecular(GLenum numLight,float red, float green, float blue, float alpha);
	void applyProperties() const;
	~LightSpecular();

private:
	RGBA specular;
	GLenum light;


};

#endif /* SRC_LIGHTSPECULAR_H_ */
