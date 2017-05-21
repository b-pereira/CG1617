/*
 * Point3d.cpp
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#include "Point4d.h"

Point4d::Point4d() :
    point3d ( 0, 0, 0 ), w_coord ( 0 )
{
}

Point4d::Point4d ( float x, float y, float z, float w ) :
    point3d ( x, y, z ), w_coord ( w )
{
}

float Point4d::getXCoord() const
{   return point3d.getXCoord();
}

void Point4d::setXCoord ( float coord )
{   point3d.setXCoord ( coord );
}

float Point4d::getYCoord() const
{   return point3d.getYCoord();
}

void Point4d::setYCoord ( float coord )
{   point3d.setYCoord ( coord );
}

float Point4d::getZCoord() const
{   return point3d.getZCoord();
}

void Point4d::setZCoord ( float coord )
{   point3d.setZCoord ( coord );
}

float Point4d::getWCoord() const
{   return w_coord;
}

void Point4d::setWCoord ( float coord )
{   w_coord = coord;
}

void Point4d::setCoord ( float x, float y, float z, float w )
{   this->setXCoord ( x );
    this->setYCoord ( y );
    this->setZCoord ( z );
    this->setWCoord ( w );
}

std::vector<float> Point4d::getVector() const
{   std::vector<float> tmp ( 4 );
    tmp[0] = this->getXCoord();
    tmp[1] = this->getYCoord();
    tmp[2] = this->getZCoord();
    tmp[3] = this->getWCoord();
    return tmp;
}

Point4d::~Point4d()
{
}

