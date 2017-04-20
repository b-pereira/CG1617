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
	Rotation(float angle, float x, float y, float z);



	void applyTransformation() const;
	~Rotation();

	float getAngle() const;
	const Point3d& getPoint() const;



private:
	float angle;
	Point3d point;

};



#endif /* SRC_ROTATION_H_ */
