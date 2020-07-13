#pragma once

#include "Filter.h"

namespace image {
	class FilterLinear : public Filter {
		float ax,ay,az;
		float cx,cy,cz;
	public:
		FilterLinear(float ax, float ay, float az, float cx, float cy, float cz);
		~FilterLinear(void);

		virtual image::Image operator << (const image::Image & image);
	};
}

