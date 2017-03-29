/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include "Group.h"
#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>

void applyTransformation(Grupo * g, Transformation * tr) {

	Rotation* r = 0;
	Translation* t = 0;
	Scale* s = 0;

	//printf("EVAL %p\n", typeid(tr));

//	if (typeid(tr) == typeid(r))
//		r = static_cast<Rotation*>(tr);
//	if (typeid(tr) == typeid(t))
//		t = static_cast<Translation*>(tr);
//	if (typeid(tr) == typeid(s))
//		s = static_cast<Scale*>(tr);

//cout << "EVAL" << endl;
	if (dynamic_cast<Rotation*>(tr) != 0) {

		r = dynamic_cast<Rotation*>(tr);

		//if (r != 0)
		std::cout << "rotation " << "angle =" << r->getAngle() << "axisX ="
				<< r->getPoint3d().getXCoord() << "axisY ="
				<< r->getPoint3d().getYCoord() << "axisZ ="
				<< r->getPoint3d().getZCoord() << std::endl;
		glRotatef(r->getAngle(), r->getPoint3d().getXCoord(),
				r->getPoint3d().getYCoord(), r->getPoint3d().getZCoord());

		//if (t != 0)
	}
	if (dynamic_cast<Translation*>(tr) != 0) {
		t = dynamic_cast<Translation*>(tr);
		std::cout << "translate" << "X =" << t->getPoint3d().getXCoord()
				<< "Y =" << t->getPoint3d().getYCoord() << "Z ="
				<< t->getPoint3d().getZCoord() << std::endl;
		glTranslatef(t->getPoint3d().getXCoord(), t->getPoint3d().getYCoord(),
				t->getPoint3d().getZCoord());
	}
	if (dynamic_cast<Scale*>(tr) != 0) {
		//if (s != 0)
		s = dynamic_cast<Scale*>(tr);
		std::cout << "scale " << "X =" << s->getPoint3d().getXCoord() << "Y ="
				<< s->getPoint3d().getYCoord() << "Z ="
				<< s->getPoint3d().getZCoord() << std::endl;
		glTranslatef(s->getPoint3d().getXCoord(), s->getPoint3d().getYCoord(),
				s->getPoint3d().getZCoord());

	}

}

