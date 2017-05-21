/*
 * Light.cpp
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#include "FixedLight.h"
#include <GL/glut.h>

FixedLight::FixedLight() :
    light ( GL_LIGHT0 ), position ( 0.0f, 0.0f, 1.0f, 1.0f ), const_atenuation_factor (
        1.0f ), linear_atenuation_factor ( 0.0f ), quadratic_atenuation_factor (
            0.0f )
{
}

FixedLight::FixedLight ( GLenum light_n, float x_pos, float y_pos, float z_pos, float const_at, float lin_at, float quad_at ) :
    light ( light_n ), position ( x_pos, y_pos, z_pos, 1.0f ), const_atenuation_factor (
        const_at ), linear_atenuation_factor ( lin_at ), quadratic_atenuation_factor (
            quad_at )
{
}

void FixedLight::addProperty ( LightProperty *property )
{   colorProperties.push_back ( property );
}
void FixedLight::applyProperties() const
{   glLightfv ( light, GL_POSITION, &position.getVector() [0] );
    glLightf ( light, GL_CONSTANT_ATTENUATION, const_atenuation_factor );
    glLightf ( light, GL_LINEAR_ATTENUATION, linear_atenuation_factor );
    glLightf ( light, GL_QUADRATIC_ATTENUATION, quadratic_atenuation_factor );

    for ( LightProperty *colo_props : colorProperties )
    {   colo_props->applyProperties();
    }

    glEnable ( light );
}

float FixedLight::getLinearAtenuationFactor() const
{   return linear_atenuation_factor;
}

float FixedLight::getConstantAtenuationFactor() const
{   return const_atenuation_factor;
}

float FixedLight::getQuadraticAtenuationFactor() const
{   return quadratic_atenuation_factor;
}

FixedLight::~FixedLight()
{   for ( std::vector<LightProperty *>::iterator it = colorProperties.begin();
            it != colorProperties.end(); ++it )
    {   delete ( *it );
    }

    colorProperties.clear();
}

