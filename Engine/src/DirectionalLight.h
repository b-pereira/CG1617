/*
 * Light.h
 *
 *  Created on: 16/05/2017
 *      Author: bpereira
 */

#ifndef SRC_DIRECTIONALLIGHT_H_
#define SRC_DIRECTIONALLIGHT_H_
#include "Light.h"
#include "LightProperty.h"
#include "Point4d.h"
#include <GL/glut.h>


class DirectionalLight : public virtual Light {
public:
	DirectionalLight ();
    DirectionalLight (GLenum light_n, float x_pos, float y_pos, float z_pos);
	void addProperty(LightProperty *);
	void applyProperties() const;
	~DirectionalLight ();

private:
	GLenum light;
    Point4d direction;
    std::vector<LightProperty*> colorProperties;

};

#endif /* SRC_DIRECTIONALLIGHT_H_ */
