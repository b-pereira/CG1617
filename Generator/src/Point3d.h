/*
 * Point3d.h
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#ifndef POINT3D_H_
#define POINT3D_H_


class Point3d {
public:

	Point3d();

	Point3d(float x, float y, float z);

	float getXCoord() const;
	void setXCoord(float coord);
	float getYCoord() const;
	void setYCoord(float coord);
	float getZCoord() const;
	void setZCoord(float coord);
	~Point3d();

private:

	float x_coord;
	float y_coord;
	float z_coord;

};

#endif /* POINT3D_H_ */
