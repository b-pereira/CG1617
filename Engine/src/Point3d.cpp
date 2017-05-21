/*
 * Point3d.cpp
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#include "Point3d.h"

Point3d::Point3d() :
    x_coord ( 0 ), y_coord ( 0 ), z_coord ( 0 )
{}

Point3d::Point3d ( float x, float y, float z ) :
    x_coord ( x ), y_coord ( y ), z_coord ( z )
{}

float Point3d::getXCoord() const
{   return x_coord;
}

void Point3d::setXCoord ( float coord )
{   x_coord = coord;
}

float Point3d::getYCoord() const
{   return y_coord;
}

void Point3d::setYCoord ( float coord )
{   y_coord = coord;
}

float Point3d::getZCoord() const
{   return z_coord;
}

void Point3d::setZCoord ( float coord )
{   z_coord = coord;
}

void Point3d::setCoord ( float x, float y,float z )
{   this->setXCoord ( x );
    this->setYCoord ( y );
    this->setZCoord ( z );
}

Point3d Point3d::addTo ( Point3d point )
{   float tmp_x, tmp_y, tmp_z;
    tmp_x = x_coord + point.getXCoord();
    tmp_y = y_coord + point.getYCoord();
    tmp_z = z_coord + point.getZCoord();
    Point3d p ( tmp_x, tmp_y, tmp_z );
    return p;
}

Point3d Point3d::multiplyBy ( float k )
{   float tmp_x, tmp_y, tmp_z;
    tmp_x = x_coord * k;
    tmp_y = y_coord * k;
    tmp_z = z_coord * k;
    Point3d p ( tmp_x, tmp_y, tmp_z );
    return p;
}

Point3d &Point3d::operator= ( const Point3d &other )
{   if ( this != &other ) // protect against invalid self-assignment
    {   x_coord = other.getXCoord();
        y_coord = other.getYCoord();
        z_coord = other.getZCoord();
    }

    return *this;
}


Point3d Point3d::crossProduct ( Point3d &u, Point3d &v )
{   float x = ( u.getYCoord() *v.getZCoord() ) - ( u.getZCoord() *v.getZCoord() );
    float y = ( u.getXCoord() *v.getZCoord() ) - ( u.getZCoord() *v.getXCoord() );
    float z = ( u.getXCoord() *v.getYCoord() ) - ( u.getYCoord() *v.getXCoord() );
    Point3d p ( x, y, z );
    return p;
}


void Point3d::incrementXCoordBy ( float value )
{   x_coord+=value;
}
void Point3d::incrementYCoordBy ( float value )
{   y_coord+=value;
}
void Point3d::incrementZCoordBy ( float value )
{   z_coord+=value;
}
void Point3d::decrementXCoordBy ( float value )
{   x_coord-=value;
}
void Point3d::decrementYCoordBy ( float value )
{   y_coord-=value;
}
void Point3d::decrementZCoordBy ( float value )
{   z_coord-=value;
}




Point3d::~Point3d()
{
}

