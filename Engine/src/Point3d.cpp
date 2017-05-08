/*
 * Point3d.cpp
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#include "Point3d.h"

Point2d::Point2d() :
        x_coord(0), y_coord(0), z_coord(0)
{}

Point2d::Point2d(float x, float y, float z) :
        x_coord(x), y_coord (y), z_coord (z)
{}

float Point2d::getXCoord() const
{
    return x_coord;
}

void Point2d::setXCoord(float coord)
{
    x_coord = coord;
}

float Point2d::getYCoord() const
{
    return y_coord;
}

void Point2d::setYCoord(float coord)
{
    y_coord = coord;
}

float Point2d::getZCoord() const
{
    return z_coord;
}

void Point2d::setZCoord(float coord)
{
    z_coord = coord;
}

void Point2d::setCoord(float x, float y,float z)
{

    this->setXCoord(x);
    this->setYCoord(y);
    this->setZCoord(z);

}

Point2d Point2d::addTo(Point2d point)
{
    float tmp_x, tmp_y, tmp_z;
    tmp_x = x_coord + point.getXCoord();
    tmp_y = y_coord + point.getYCoord();
    tmp_z = z_coord + point.getZCoord();
    Point2d p(tmp_x, tmp_y, tmp_z);

    return p;



}

Point2d Point2d::multiplyBy(float k)
{

    float tmp_x, tmp_y, tmp_z;
    tmp_x = x_coord * k;
    tmp_y = y_coord * k;
    tmp_z = z_coord * k;



    Point2d p(tmp_x, tmp_y, tmp_z);

    return p;

}

Point2d & Point2d::operator= (const Point2d & other)
{
    if (this != &other) // protect against invalid self-assignment
    {
        x_coord = other.getXCoord();
        y_coord = other.getYCoord();
        z_coord = other.getZCoord();
    }

    return *this;
}


Point2d Point2d::crossProduct(Point2d& u, Point2d &v)
{
    float x = (u.getYCoord()*v.getZCoord()) - (u.getZCoord()*v.getZCoord());
    float y = (u.getXCoord()*v.getZCoord()) - (u.getZCoord()*v.getXCoord());
    float z = (u.getXCoord()*v.getYCoord()) - (u.getYCoord()*v.getXCoord());
    Point2d p(x, y, z);

    return p;
}


void Point2d::incrementXCoordBy(float value)
{
    x_coord+=value;
}
void Point2d::incrementYCoordBy(float value)
{
    y_coord+=value;
}
void Point2d::incrementZCoordBy(float value)
{
    z_coord+=value;
}
void Point2d::decrementXCoordBy(float value)
{
    x_coord-=value;
}
void Point2d::decrementYCoordBy(float value)
{
    y_coord-=value;
}
void Point2d::decrementZCoordBy(float value)
{
    z_coord-=value;
}




Point2d::~Point2d()
{
    // TODO Auto-generated destructor stub
}

