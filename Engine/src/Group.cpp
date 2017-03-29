/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include "Group.h"
#include <typeinfo>
#include <iostream>

void applyTransformation(Grupo * g, Transformation * tr) {


	Rotation* r = 0;
	Translation* t = 0;
	Scale* s = 0;

	if (typeid(t) == typeid(r))
		r = static_cast<Rotation*>(tr);
	if (typeid(tr) == typeid(t))
		t = static_cast<Translation*>(tr);
	if (typeid(t) == typeid(s))
		s = static_cast<Scale*>(s);
	if (r != 0)
		std::cout << "rotation" << "angle" << r->getAngle() << "axisX"
				<< r->getPoint3d().getXCoord() << "axisY" << r->getPoint3d().getYCoord()
				<< "axisZ" << r->getPoint3d().getZCoord() << std::endl;
	if (t != 0)
		std::cout << "translate" << "X" << t->getPoint3d().getXCoord() << "Y"
				<< t->getPoint3d().getYCoord() << "Z" << t->getPoint3d().getZCoord()
				<< std::endl;
	if (s != 0)
		std::cout << "scale" << "X" << s->getPoint3d().getXCoord() << "Y"
				<< s->getPoint3d().getYCoord() << "Z" << s->getPoint3d().getZCoord()
				<< std::endl;

}

