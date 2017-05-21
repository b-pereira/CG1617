/*
 * MatEmissive.cpp
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#include "MatEmissive.h"
#include <GL/glut.h>

MatEmissive::MatEmissive() :
    emissive ( 0, 0, 0, 1 )
{
}

MatEmissive::MatEmissive ( float red, float green, float blue, float alpha ) :
    emissive ( red, green, blue, alpha )
{
}

void MatEmissive::applyProperties() const
{   glMaterialfv ( GL_FRONT, GL_EMISSION, &emissive.getRGBA() [0] );
}

MatEmissive::~MatEmissive()
{
}

