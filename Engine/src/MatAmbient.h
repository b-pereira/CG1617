/*
 * MatAmbient.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_MATAMBIENT_H_
#define SRC_MATAMBIENT_H_

#include "Materials.h"
#include "RGBA.h"

class MatAmbient: public virtual Materials {
public:
	MatAmbient(float red, float green, float blue, float alpha);
	void applyProperties() const;
	~MatAmbient();
private:
	RGBA ambient;

};

#endif /* SRC_MATAMBIENT_H_ */
