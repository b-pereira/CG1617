/*
 * LightDiffuse.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_LIGHTDIFFUSE_H_
#define SRC_LIGHTDIFFUSE_H_

#include "LightProperty.h"
#include "RGBA.h"
#include <GL/glut.h>

class LightDiffuse: public virtual LightProperty {
public:
	LightDiffuse(GLenum numLight);
	LightDiffuse(GLenum numLight, float red, float green, float blue);
	LightDiffuse(GLenum numLight, float red, float green, float blue, float alpha);
	void applyProperties() const;
	~LightDiffuse();
private:
	RGBA diffuse;
	GLenum light;

};

#endif /* SRC_LIGHTDIFFUSE_H_ */
