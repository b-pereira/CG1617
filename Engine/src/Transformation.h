/*
 * Transformation.h
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#ifndef SRC_TRANSFORMATION_H_
#define SRC_TRANSFORMATION_H_



class Transformation {
public:
	virtual void applyTransformation() const = 0;
	virtual ~Transformation();
};



#endif /* SRC_TRANSFORMATION_H_ */
