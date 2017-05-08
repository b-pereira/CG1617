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
	AnimatedRotation(float time, float x, float y, float z);



	void applyTransformation() const;
	~AnimatedRotation();

	float getTime() const;
	const Point2d& getPoint() const;



private:
	float time;
	Point2d point;

};



#endif /* SRC_ANIMATEDROTATION_H_ */
