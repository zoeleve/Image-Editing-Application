#pragma once

#include <iostream>
#include "Image.h"

using namespace std;

namespace image {
	class Filter {
	public:
		virtual image::Image operator << (const image::Image & image) = 0;
	};
}