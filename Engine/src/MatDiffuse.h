/*
 * MatDiffuse.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_MATDIFFUSE_H_
#define SRC_MATDIFFUSE_H_

#include "Materials.h"
#include "RGBA.h"

class MatDiffuse: public virtual Materials {
public:
	MatDiffuse(float red, float green, float blue, float alpha);
	void applyProperties() const;
	~MatDiffuse();
private:
	RGBA diffuse;

};

#endif /* SRC_MATDIFFUSE_H_ */
