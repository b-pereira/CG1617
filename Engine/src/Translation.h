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
	Point3d getPoint3d() const;
	~Translation();

private:

	Point3d point;

};

#endif /* SRC_TRANSLATION_H_ */
