/*
 * MatSpecular.h
 *
 *  Created on: 15/05/2017
 *      Author: bpereira
 */

#ifndef SRC_MATSPECULAR_H_
#define SRC_MATSPECULAR_H_

#include "Materials.h"
#include "RGBA.h"

class MatSpecular: public virtual Materials {
public:
	MatSpecular(float red, float green, float blue, float alpha, float shininess);
	void applyProperties() const;
	~MatSpecular();

private:
	RGBA specular;
	float shin;


};

#endif /* SRC_MATSPECULAR_H_ */
