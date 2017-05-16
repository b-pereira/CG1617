/*
 * Scale.h
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#ifndef SRC_SCALE_H_
#define SRC_SCALE_H_

#include "Transformation.h"

#include "Point3d.h"


class Scale: public Transformation {
public:
	Scale();
	Scale(float x, float y, float z);
	const Point3d& getPoint() const;
	void applyTransformation() const;
	~Scale();

private:

	Point3d point;

};



#endif /* SRC_SCALE_H_ */
