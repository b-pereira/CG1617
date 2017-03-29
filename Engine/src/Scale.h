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
	Scale(double x, double y, double z);
	Point3d getPoint3d() const;
	~Scale();

private:

	Point3d point;

};



#endif /* SRC_SCALE_H_ */
