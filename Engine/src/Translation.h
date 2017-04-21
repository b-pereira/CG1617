/*
 * Translation.h
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#ifndef SRC_TRANSLATION_H_
#define SRC_TRANSLATION_H_

#include "Transformation.h"
#include <vector>
#include "Point3d.h"
using namespace std;

class Translation: public Transformation {
public:
	Translation();
	Translation(double t,vector<Point3d> pts);
	const vector<Point3d>&getVector() const;
	void applyTransformation() const;
	~Translation();

private:

	//Point3d point;
	vector<Point3d> points = new vector<Point3d>;
	double time;

};

#endif /* SRC_TRANSLATION_H_ */
