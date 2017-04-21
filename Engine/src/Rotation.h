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
	Rotation(double time, double x, double y, double z);



	void applyTransformation() const;
	~Rotation();

	double getTime() const;
	const Point3d& getPoint() const;



private:
	double time;
	Point3d point;

};



#endif /* SRC_ROTATION_H_ */
