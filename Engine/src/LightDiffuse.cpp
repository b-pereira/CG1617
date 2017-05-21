/*
 * LightDiffuse.cpp
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#include "LightDiffuse.h"
#include <GL/glut.h>

LightDiffuse::LightDiffuse ( GLenum numLight ) :
    light ( numLight ), diffuse ( 0.0f, 0.0f, 0.0f, 1.0f )
{
}

LightDiffuse::LightDiffuse ( GLenum numLight, float red, float green, float blue ) :
    light ( numLight ),diffuse ( red, green, blue, 1.0f )
{
}

LightDiffuse::LightDiffuse ( GLenum numLight, float red, float green, float blue, float alpha ) :
    light ( numLight ),diffuse ( red, green, blue, alpha )
{
}

void LightDiffuse::applyProperties() const
{   glLightfv ( light, GL_DIFFUSE, &diffuse.getRGBA() [0] );
}

LightDiffuse::~LightDiffuse()
{
}

