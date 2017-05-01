/*
 * Catmull-Rom.h
 *
 *  Created on: Apr 15, 2017
 *      Author: rsilva
 */
#ifndef SRC_CATMULL_ROM_H_
#define SRC_CATMULL_ROM_H_


#include <vector>
#include "Point3d.h"
#include <cmath>
#include <GL/glut.h>



void multMatrixVector(float *m, float *v, float *res);

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3,
		float *pos);

void getGlobalCatmullRomPoint(float gt, float *pos,
		std::vector<Point3d> points);

void renderCatmullRomCurve(std::vector<Point3d> points);

#endif /* SRC_CATMULL_ROM_H_ */

