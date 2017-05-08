/*
 * AnimatedTranslation.cpp
 *
 *  Created on: 20/04/2017
 *     Author: rsilva
 */

#include "AnimatedTranslation.h"

#include "GL/glut.h"
#include <iostream>
#include "Point3d.h"
#include "Catmull-Rom.h"
#include <cmath>

AnimatedTranslation::AnimatedTranslation() :
		time(0) {

}

AnimatedTranslation::AnimatedTranslation(float tim) :
		time(tim), points() {
}

void AnimatedTranslation::addPointCoords(float x, float y, float z) {

	Point2d pt(x, y, z);

	points.push_back(pt);
}

const vector<Point2d>&AnimatedTranslation::getVector() const {
	return points;
}

const float AnimatedTranslation::getTime() const {

	return time;
}

void AnimatedTranslation::applyTransformation() const {



	/**
	 * t \in [0 .. 1]
	 * cada iteração do parametro t tem que estar entre 0 e 1.
	 * Existe um contador global do tempo, que conta o tempo em milissegundos desde o início da
	 * aplicação até ao momento. Temos que, existe um tempo em segundos, que será
	 * o tempo total da distância percorrida numa curva. Relativamente ao contador global, esse tempo é relativo.
	 * Se o tempo total da curva for 10 segundos, pretende-se percorrer segundo a segundo até perfazer esse tempo
	 * vontando ao início. Se passaram 20 segundos desde o início da aplicação, a curva deve ser percorrida duas vezes.
	 * Daí a necessidade de um contador circular, através do módulo entre tempo total da aplicação e tempo total da curva.
	 * Como se pretende o que t (tempo) esteja entre 0 e 1 é necessário dividir o tempo decorrido no contador circular, pelo
	 * tempo total da curva, obtendo assim o valor pretendido.
	 */
	float t = ((glutGet(GLUT_ELAPSED_TIME))%(int)(time*1000))/(time*1000);



	float pos[3];

	renderCatmullRomCurve(points);
	getGlobalCatmullRomPoint(t, pos, points);
	glTranslatef(pos[0], pos[1], pos[2]);

//	cross(deriv, y, z);
//	cross(z, deriv, y);
//	normalize(deriv);
//	normalize(y);
//	normalize(z);
//	buildRotMatrix(deriv, y, z, m_rot);
//	glMultMatrixf(m_rot);
//	std::cout << "translate"
//			  << " time =" << time
//			  << " X =" << pos[0]
//			  << " Y =" << pos[1]
//			  << " Z =" << pos[2]
//			  << std::endl;

	//t+=(t/1000);

}

AnimatedTranslation::~AnimatedTranslation() {

}

