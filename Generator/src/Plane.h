/*
 * Plane.h
 *
 *  Created on: 28/02/2017
 *      Author: bpereira
 */

#ifndef SRC_PLANE_H_
#define SRC_PLANE_H_

#include "GeometricShape.h"
#include "Triangle.h"
#include <vector>

class Plane: public GeometricShape {
public:
	Plane();
	void draw();
	~Plane();


private:

	std::vector<Triangle> triangles;
};

#endif /* SRC_PLANE_H_ */
