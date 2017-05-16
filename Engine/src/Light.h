/*
 * Light.h
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_
#include "LightProperty.h"

class Light {
public:
	virtual void addProperty(LightProperty *) = 0;
	virtual void applyProperties() const = 0;
	virtual ~Light();
};

#endif /* SRC_LIGHT_H_ */
