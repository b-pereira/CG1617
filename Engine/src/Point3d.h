/*
 * Point3d.h
 *
 *  Created on: 26/02/2017
 *      Author: bpereira
 */

#ifndef POINT3D_H_
#define POINT3D_H_


class Point2d
{
public:

    Point2d();

    Point2d(float x, float y, float z);

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
    Point2d addTo(Point2d point);;
    Point2d multiplyBy(float k);
    Point2d & operator= (const Point2d & other);
    Point2d crossProduct(Point2d& u, Point2d &v);
    ~Point2d();

private:

    float x_coord;
    float y_coord;
    float z_coord;

};

#endif /* POINT3D_H_ */
