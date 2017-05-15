/*
 * Materials.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_MATERIALS_H_
#define SRC_MATERIALS_H_

class Materials {
public:
	virtual void applyProperties() const = 0;
	virtual ~Materials();
};

#endif /* SRC_MATERIALS_H_ */
