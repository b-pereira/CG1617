/*
 * LightAmbient.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_LIGHTAMBIENT_H_
#define SRC_LIGHTAMBIENT_H_

#include "LightProperty.h"
#include "RGBA.h"
#include <GL/glut.h>

class LightAmbient: public virtual LightProperty {
public:
	LightAmbient(GLenum numLight);
	LightAmbient(GLenum numLight, float red, float green, float blue);
	LightAmbient(GLenum numLight, float red, float green, float blue, float alpha);
	void applyProperties() const;
	~LightAmbient();
private:
	RGBA ambient;
	GLenum light;

};

#endif /* SRC_LIGHTAMBIENT_H_ */
