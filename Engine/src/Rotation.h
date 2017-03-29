/*
 * Rotation.h
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#ifndef SRC_ROTATION_H_
#define SRC_ROTATION_H_

#include "Transformation.h"

#include "Point3d.h"

class Rotation: public Transformation {
public:

	Rotation();
	Rotation(double angle, double x, double y, double z);
	Point3d getPoint3d() const;
	double getAngle() const;

	~Rotation();

private:
	double angle;
	Point3d point;

};



#endif /* SRC_ROTATION_H_ */
