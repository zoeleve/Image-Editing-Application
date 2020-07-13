#include "FilterLinear.h"


image::FilterLinear::FilterLinear(float ax, float ay, float az, float cx, float cy, float cz) : ax(ax), ay(ay), az(az), cx(cx), cy(cy), cz(cz) {
}

image::FilterLinear::~FilterLinear(void)
{
}

image::Image image::FilterLinear::operator << (const image::Image & image) {
	image::Image final = image;

	math::Vec3<float> * rawdata = final.getRawDataPtr();

	unsigned int length = final.getWidth()*final.getHeight();

	for (unsigned int i=0;i<length;i++) {
		rawdata[i].r = rawdata[i].r * ax + cx;
		rawdata[i].g = rawdata[i].g * ay + cy;
		rawdata[i].b = rawdata[i].b * az + cz;

		rawdata[i].clampToLowerBound(0);
		rawdata[i].clampToUpperBound(1);
	}

	return final;
}