/*
 * Light.cpp
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#include "DirectionalLight.h"
#include <GL/glut.h>

void DirectionalLight::addProperty ( LightProperty *property )
{   colorProperties.push_back ( property );
}
void DirectionalLight::applyProperties() const
{   glLightfv ( light, GL_POSITION, &direction.getVector() [0] );

    for ( LightProperty *colo_props: colorProperties )
    {   colo_props->applyProperties();
    }

    glEnable ( light );
}

DirectionalLight::~DirectionalLight()
{   for ( std::vector<LightProperty *>::iterator it = colorProperties.begin();
            it != colorProperties.end(); ++it )
    {   delete ( *it );
    }

    colorProperties.clear();
}

DirectionalLight::DirectionalLight() :
    light ( GL_LIGHT0 ), direction ( 0.0f, 0.0f, 1.0f, 1.0f )
{
}

DirectionalLight::DirectionalLight ( GLenum light_n, float x_pos, float y_pos,
                                     float z_pos ) :
    light ( light_n ), direction ( x_pos, y_pos, z_pos, 0.0f )
{
}
