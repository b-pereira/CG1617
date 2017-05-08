/*
 * Point3d.h
 *
 *  Created on: 6/5/2017
 *      Author: bpereira
 */

#ifndef POINT2D_H_
#define POINT2D_H_


class Point2d {
public:

	Point2d();

	Point2d(float x, float y);

	float getXCoord() const;
	void setXCoord(float coord);
	float getYCoord() const;
	void setYCoord(float coord);
	~Point2d();

private:

	float x_coord;
	float y_coord;

};

#endif /* POINT2D_H_ */
