/*
 * Spotlight.h
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#ifndef SRC_SPOTLIGHT_H_
#define SRC_SPOTLIGHT_H_

#include "Light.h"
#include "LightProperty.h"
#include "Point4d.h"
#include <GL/glut.h>

class Spotlight: public virtual Light {
public:
	Spotlight();
	Spotlight(GLenum light_n, float x_pos, float y_pos, float z_pos, float x_dir, float y_dir,
			float z_dir, float cutangle, float k_fact, float lin_fact,
			float quad_fact, float exponent);

	float getCutOffAngle() const;
	float getLinearAtenuationFactor() const;
	float getConstantAtenuationFactor() const;
	float getQuadraticAtenuationFactor() const;
	float getConcentrationExponent() const;
	void addProperty(LightProperty *);
	void applyProperties() const;
	~Spotlight();

private:
    GLenum light;
	Point4d position;
	Point3d direction;
	float cutoff_angle;
	float concentration_exponent;
	float const_atenuation_factor;
	float linear_atenuation_factor;
	float quadratic_atenuation_factor;
	std::vector<LightProperty*> colorProperties;

};

#endif /* SRC_SPOTLIGHT_H_ */
