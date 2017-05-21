/*
 *  Catmull-Rom.cpp
 *
 *  Created on: Apr 15, 2017
 *      Author: rsilva
 */

#include "Catmull-Rom.h"



void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3,
		float *pos) {

	// catmull-rom matrix
	float m[4][4] = {
			{ -0.5f, 1.5f, -1.5f, 0.5f },
			{ 1.0f, -2.5f, 2.0f, -0.5f },
			{ -0.5f, 0.0f, 0.5f,  0.0f },
			{ 0.0f,  1.0f, 0.0f,  0.0f } };

	float px[4] = { p0[0], p1[0], p2[0], p3[0] };
	float py[4] = { p0[1], p1[1], p2[1], p3[1] };
	float pz[4] = { p0[2], p1[2], p2[2], p3[2] };

	float tee[4] = { powf(t, 3), powf(t, 2), t, 1 };


	// Compute A = M * P
	float ax[4];
	float ay[4];
	float az[4];

	multMatrixVector((float *)m, px, ax);
	multMatrixVector((float *)m, py, ay);
	multMatrixVector((float *)m, pz, az);

	// Compute pos = T * A

	pos[0] = tee[0]*ax[0] + tee[1]*ax[1] + tee[2]*ax[2] + tee[3]*ax[3];
	pos[1] = tee[0]*ay[0] + tee[1]*ay[1] + tee[2]*ay[2]+ tee[3]*ay[3];
	pos[2] = tee[0]*az[0] + tee[1]*az[1] + tee[2]*az[2]+ tee[3]*az[3];



}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, std::vector<Point3d> points) {

	float t = gt * points.size(); // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + points.size()- 1) % points.size();
	indices[1] = (indices[0] + 1) % points.size();
	indices[2] = (indices[1] + 1) % points.size();
	indices[3] = (indices[2] + 1) % points.size();


	float p[points.size()][3];

	for (int i = 0; i < points.size(); ++i) {
		p[i][0] = points[i].getXCoord();
		p[i][1] = points[i].getYCoord();
		p[i][2] = points[i].getZCoord();
	}


	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]],
			p[indices[3]], pos);
}

void renderCatmullRomCurve(std::vector<Point3d> points) {

	float pos[3];
	float deriv[3];

	float color[4] = {0.4,0.4,0.4,1};
	float color_default[4] = {0,0,0,1};

	glMaterialfv(GL_FRONT, GL_EMISSION, color);

	glBegin(GL_LINE_LOOP);

	for (int i = 1; i < 100; ++i) {
		getGlobalCatmullRomPoint(i / 100.0, pos, points);

		glVertex3fv(pos);

	}

	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, color_default);

}


