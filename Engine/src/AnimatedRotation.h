/*
 * AnimatedRotation.h
 *
 *  Created on: 20/04/2017
 *     Author: rsilva
 */

#ifndef SRC_ANIMATEDROTATION_H_
#define SRC_ANIMATEDROTATION_H_

#include "Transformation.h"

#include "Point3d.h"

class AnimatedRotation: public Transformation {
public:

	AnimatedRotation();
	AnimatedRotation(double time, double x, double y, double z);



	void applyTransformation() const;
	~AnimatedRotation();

	double getTime() const;
	const Point3d& getPoint() const;



private:
	double time;
	Point3d point;

};



#endif /* SRC_ANIMATEDROTATION_H_ */
