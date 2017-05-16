/*
 * Point3d.h
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#ifndef POINT4D_H_
#define POINT4D_H_
#include <vector>
#include "Point3d.h"


class Point4d
{
public:

    Point4d();

    Point4d(float x, float y, float z, float w);

    float getXCoord() const;
    void setXCoord(float coord);
    float getYCoord() const;
    void setYCoord(float coord);
    float getZCoord() const;
    void setZCoord(float coord);
    float getWCoord() const;
    void setWCoord(float coord);
    void setCoord(float x, float y,float z, float w);
    std::vector <float> getVector() const;
    ~Point4d();

private:

    Point3d point3d;
    float w_coord;

};

#endif /* POINT4D_H_ */
