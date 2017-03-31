/*
 * Point3d.cpp
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#include "Point3d.h"

Point3d::Point3d() :
        x_coord(0), y_coord(0), z_coord(0)
{}

Point3d::Point3d(double x, double y, double z) :
        x_coord(x), y_coord (y), z_coord (z)
{}

double Point3d::getXCoord() const
{
    return x_coord;
}

void Point3d::setXCoord(double coord)
{
    x_coord = coord;
}

double Point3d::getYCoord() const
{
    return y_coord;
}

void Point3d::setYCoord(double coord)
{
    y_coord = coord;
}

double Point3d::getZCoord() const
{
    return z_coord;
}

void Point3d::setZCoord(double coord)
{
    z_coord = coord;
}

void Point3d::setCoord(double x, double y,double z)
{

    this->setXCoord(x);
    this->setYCoord(y);
    this->setZCoord(z);

}

Point3d & Point3d::addTo(Point3d &point)
{

    x_coord+=point.getXCoord();
    y_coord+=point.getYCoord();
    z_coord+=point.getZCoord();

    return *this;

}

Point3d & Point3d::multiplyBy(double k)
{

    x_coord*=k;
    y_coord*=k;
    z_coord*=k;

    return *this;
}

Point3d & Point3d::operator= (const Point3d & other)
{
    if (this != &other) // protect against invalid self-assignment
    {
        x_coord = other.getXCoord();
        y_coord = other.getYCoord();
        z_coord = other.getZCoord();
    }

    return *this;
}


Point3d Point3d::crossProduct(Point3d& u, Point3d &v){
	double x = (u.getYCoord()*v.getZCoord()) - (u.getZCoord()*v.getZCoord());
	double y = (u.getXCoord()*v.getZCoord()) - (u.getZCoord()*v.getXCoord());
	double z = (u.getXCoord()*v.getYCoord()) - (u.getYCoord()*v.getXCoord());
	Point3d p(x, y, z);

	return p;
}


void Point3d::incrementXCoordBy(double value){x_coord+=value;}
void Point3d::incrementYCoordBy(double value){y_coord+=value;}
void Point3d::incrementZCoordBy(double value){z_coord+=value;}
void Point3d::decrementXCoordBy(double value){x_coord-=value;}
void Point3d::decrementYCoordBy(double value){y_coord-=value;}
void Point3d::decrementZCoordBy(double value){z_coord-=value;}




Point3d::~Point3d()
{
    // TODO Auto-generated destructor stub
}

