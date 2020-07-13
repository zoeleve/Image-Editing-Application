#include <cmath>

#include "FilterGamma.h"
#include "vec3.h"

using namespace std;

image::FilterGamma::FilterGamma(float gamma_value) : gamma_value(gamma_value)
{
}


image::FilterGamma::~FilterGamma(void)
{
}

image::Image image::FilterGamma::operator << (const image::Image & image) {
	image::Image final = image;

	math::Vec3<float> * rawdata = final.getRawDataPtr();

	unsigned int length = final.getWidth()*final.getHeight();

	for (unsigned int i=0;i<length;i++) {
		rawdata[i].r = (float) pow(rawdata[i].r, gamma_value);
		rawdata[i].g = (float) pow(rawdata[i].g, gamma_value);
		rawdata[i].b = (float) pow(rawdata[i].b, gamma_value);
	}

	return final;
}
