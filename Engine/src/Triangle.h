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

	const Point3d& getA() const;
	void setA(const Point3d& a);
	const Point3d& getB() const;
	void setB(const Point3d& b);
	const Point3d& getC() const;
	void setC(const Point3d& c);
	~Triangle();

private:
	Point3d a;
	Point3d b;
	Point3d c;
};

#endif /* TRIANGLE_H_ */
