/*
 * LightAmbient.cpp
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#include "LightAmbient.h"
#include <GL/glut.h>

LightAmbient::LightAmbient ( GLenum numLight ) :
    light ( numLight ), ambient ( 0.0f, 0.0f, 0.0f, 1.0f )
{
}

LightAmbient::LightAmbient ( GLenum numLight, float red, float green, float blue ) :
    light ( numLight ), ambient ( red, green, blue, 1.0f )
{
}

LightAmbient::LightAmbient ( GLenum numLight, float red, float green, float blue,
                             float alpha ) :
    light ( numLight ), ambient ( red, green, blue, alpha )
{
}

void LightAmbient::applyProperties() const
{   glLightfv ( light, GL_AMBIENT, &ambient.getRGBA() [0] );
}

LightAmbient::~LightAmbient()
{
}

