#pragma once

#include <iostream>
#include "array2d.h"
#include "imageio.h"
#include "vec3.h"

namespace image {
	class Image : public image::ImageIO, public math::Array2D<math::Vec3<float>> {
	public:
		virtual bool load(const std::string & filename, const std::string & format);

		virtual bool save(const std::string & filename, const std::string & format);
	};
}