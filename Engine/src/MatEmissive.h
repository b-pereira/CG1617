/*
 * MatEmissive.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_MATEMISSIVE_H_
#define SRC_MATEMISSIVE_H_

#include "Materials.h"
#include "RGBA.h"

class MatEmissive: public virtual Materials {
public:
	MatEmissive();
	MatEmissive(float red, float green, float blue, float alpha);
	void applyProperties() const;
	~MatEmissive();
private:
	RGBA emissive;

};

#endif /* SRC_MATEMISSIVE_H_ */
