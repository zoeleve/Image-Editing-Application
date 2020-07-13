#pragma once

#include "Filter.h"


namespace image {
	class FilterGamma : public Filter {
		float gamma_value;
	public:
		FilterGamma(float gamma_value);
		~FilterGamma(void);

		virtual image::Image operator << (const image::Image & image);
	};
}

