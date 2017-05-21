/*
 * FixedLight.h
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#ifndef SRC_FIXEDLIGHT_H_
#define SRC_FIXEDLIGHT_H_
#include "Light.h"
#include "Point4d.h"
#include <GL/glut.h>
#include <vector>
#include "LightProperty.h"

class FixedLight: public virtual Light {
public:
	FixedLight();
	FixedLight(GLenum light_n, float x_pos, float y_pos, float z_pos, float const_at, float lin_at, float quad_at);
	float getLinearAtenuationFactor() const;
	float getConstantAtenuationFactor() const;
	float getQuadraticAtenuationFactor() const;
	void addProperty(LightProperty *);
	void applyProperties() const;
	~FixedLight();

private:

	GLenum light;
	Point4d position;
	std::vector<LightProperty*> colorProperties;

	float const_atenuation_factor;
	float linear_atenuation_factor;
	float quadratic_atenuation_factor;
};

#endif /* SRC_FIXEDLIGHT_H_ */
