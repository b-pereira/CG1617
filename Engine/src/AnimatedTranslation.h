/*
 * AnimatedTranslation.h
 *
 *  Created on: 20/04/2017
 *      Author: rsilva
 */

#ifndef SRC_ANIMATEDTRANSLATION_H_
#define SRC_ANIMATEDTRANSLATION_H_

#include "Transformation.h"
#include <vector>
#include "Point3d.h"
using namespace std;

class AnimatedTranslation: public Transformation {
public:
	AnimatedTranslation();
	AnimatedTranslation(double t,vector<Point3d> pts);
	const vector<Point3d>&getVector() const;
	void applyTransformation() const;
	~AnimatedTranslation();

private:

	//Point3d point;
	vector<Point3d> points;
	double time;

};

#endif /* SRC_ANIMATEDTRANSLATION_H_ */
