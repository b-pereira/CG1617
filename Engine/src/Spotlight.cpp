/*
 * Spotlight.cpp
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#include "Spotlight.h"
#include <GL/glut.h>

void Spotlight::applyProperties() const
{   glLightfv ( light, GL_POSITION, &position.getVector() [0] );
    glLightf ( light, GL_CONSTANT_ATTENUATION, const_atenuation_factor );
    glLightf ( light, GL_LINEAR_ATTENUATION, linear_atenuation_factor );
    glLightf ( light, GL_QUADRATIC_ATTENUATION, quadratic_atenuation_factor );
    glEnable ( light );
}

Spotlight::Spotlight() :
    light ( GL_LIGHT0 ), position ( 0.0f, 0.0f, 1.0f, 1.0f ), direction ( 0.0f,
            0.0f, -1.0f ), cutoff_angle ( 180 ), const_atenuation_factor ( 1.0f ), linear_atenuation_factor (
                0.0f ), quadratic_atenuation_factor ( 0.0f ), concentration_exponent (
                    0.0f )
{
}

Spotlight::Spotlight ( GLenum light_n, float x_pos, float y_pos, float z_pos,
                       float x_dir, float y_dir, float z_dir, float cutangle, float k_fact,
                       float lin_fact, float quad_fact, float exponent ) :
    light ( light_n ), position ( x_pos, x_pos, x_pos, 1.0f ), direction ( x_dir,
            y_dir, z_dir ), cutoff_angle ( cutangle ), const_atenuation_factor (
                k_fact ), linear_atenuation_factor ( lin_fact ), quadratic_atenuation_factor (
                    quad_fact ), concentration_exponent ( exponent )
{
}

float Spotlight::getCutOffAngle() const
{   return cutoff_angle;
}

float Spotlight::getLinearAtenuationFactor() const
{   return linear_atenuation_factor;
}

float Spotlight::getConstantAtenuationFactor() const
{   return const_atenuation_factor;
}

float Spotlight::getQuadraticAtenuationFactor() const
{   return quadratic_atenuation_factor;
}

float Spotlight::getConcentrationExponent() const
{   return concentration_exponent;
}

void Spotlight::addProperty ( LightProperty *property )
{   colorProperties.push_back ( property );
}

Spotlight::~Spotlight()
{   for ( std::vector<LightProperty *>::iterator it = colorProperties.begin();
            it != colorProperties.end(); ++it )
    {   delete ( *it );
    }

    colorProperties.clear();
}

