/*
 * Point3d.h
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#ifndef POINT3D_H_
#define POINT3D_H_


class Point3d
{
public:

    Point3d();

    Point3d(float x, float y, float z);

    float getXCoord() const;
    void setXCoord(float coord);
    float getYCoord() const;
    void setYCoord(float coord);
    float getZCoord() const;
    void setZCoord(float coord);
    void setCoord(float x, float y,float z);
    void incrementXCoordBy(float value);
    void incrementYCoordBy(float value);
    void incrementZCoordBy(float value);
    void decrementXCoordBy(float value);
    void decrementYCoordBy(float value);
    void decrementZCoordBy(float value);
    Point3d addTo(Point3d point);;
    Point3d multiplyBy(float k);
    Point3d & operator= (const Point3d & other);
    Point3d crossProduct(Point3d& u, Point3d &v);
    ~Point3d();

private:

    float x_coord;
    float y_coord;
    float z_coord;

};

#endif /* POINT3D_H_ */
