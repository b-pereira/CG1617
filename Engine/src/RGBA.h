/*
 * RGBA.h
 *
 *  Created on: 14/05/2017
 *      Author: bpereira
 */

#ifndef SRC_RGBA_H_
#define SRC_RGBA_H_
#include <vector>

class RGBA {
public:
	RGBA(float red, float green, float blue, float alpha);

    std::vector<float> getRGBA() const;

	~RGBA();



private:

    float r;
    float g;
    float b;
    float a;

};

#endif /* SRC_RGBA_H_ */
