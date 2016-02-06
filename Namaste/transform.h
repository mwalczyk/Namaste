#pragma once

#include <array>

#include "geometry.h"

namespace namaste {

	namespace geom {

		using Matrix4x4Data = std::array<std::array<float, 4>, 4>;

		class Matrix4x4
		{
		public:
			Matrix4x4();
			~Matrix4x4();

			friend std::ostream& operator<<(std::ostream &os, const Matrix4x4 &m);

			Matrix4x4Data data;
		private:
		};

		class Transform
		{
		public:
			Transform();
			~Transform();
		private:
		};

	} // namespace geom

} // namespace namaste