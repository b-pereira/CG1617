/*
 * Triangle.h
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Point3d.h"

class Triangle {
public:

	Triangle();

	Triangle(float xA, float yA, float zA, float xB, float yB, float zB,
			float xC, float yC, float zC);

	const Point2d& getA() const;
	void setA(const Point2d& a);
	const Point2d& getB() const;
	void setB(const Point2d& b);
	const Point2d& getC() const;
	void setC(const Point2d& c);
	~Triangle();

private:
	Point2d a;
	Point2d b;
	Point2d c;
};

#endif /* TRIANGLE_H_ */
