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

	Point3d(double x, double y, double z);

	double getXCoord() const;
	void setXCoord(double coord);
	double getYCoord() const;
	void setYCoord(double coord);
	double getZCoord() const;
	void setZCoord(double coord);
	~Point3d();

private:

	double x_coord;
	double y_coord;
	double z_coord;

};

#endif /* POINT3D_H_ */
