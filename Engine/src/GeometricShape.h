/*
 * GeometricShape.h
 *
 *  Created on: 28/02/2017
 *      Author: bpereira
 */

#ifndef SRC_GEOMETRICSHAPE_H_
#define SRC_GEOMETRICSHAPE_H_

class GeometricShape {
public:
	//virtual Point3d center() const =0;
	//virtual void move(Point3d to) =0;
	// pure virtual
	virtual void draw() const = 0;
	//virtual void rotate(int angle) = 0; // draw on current "Canvas"
	virtual ~GeometricShape();



};

#endif /* SRC_GEOMETRICSHAPE_H_ */
