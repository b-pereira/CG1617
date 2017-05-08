/*
 * AnimatedTranslation.h
 *
 *  Created on: 20/04/2017
 *      Author: rsilva
 */

#ifndef SRC_ANIMATEDTRANSLATION_H_
#define SRC_ANIMATEDTRANSLATION_H_

#include <vector>

#include "Point3d.h"
#include "Transformation.h"

using namespace std;

class AnimatedTranslation: public Transformation {
public:
	AnimatedTranslation();
	AnimatedTranslation(float tim);

	const vector<Point2d>&getVector() const;
	const float getTime() const;
	void applyTransformation() const;
	void addPointCoords(float x, float y, float z);
	~AnimatedTranslation();

private:

	//Point3d point;
	vector<Point2d> points;
	float time;

};

#endif /* SRC_ANIMATEDTRANSLATION_H_ */
