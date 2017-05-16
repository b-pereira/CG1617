/*
 * LightProperties.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_LIGHTPROPERTY_H_
#define SRC_LIGHTPROPERTY_H_

class LightProperty {
public:
	virtual void applyProperties() const = 0;
	virtual ~LightProperty();
};

#endif /* SRC_LIGHTPROPERTY_H_ */
