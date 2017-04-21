/*
 * Translation.h
 *
 *  Created on: 28/03/2017
 *      Author: bpereira
 */

#ifndef SRC_TRANSLATION_H_
#define SRC_TRANSLATION_H_

#include "Transformation.h"
#include "Point3d.h"


class Translation: public Transformation {
public:
	Translation();
	Translation(double x, double y, double z);
	const Point3d& getPoint() const;
	void applyTransformation() const;
	~Translation();

private:

	Point3d point;

};

#endif /* SRC_TRANSLATION_H_ */
