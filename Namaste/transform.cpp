#include "stdafx.h"
#include "transform.h"

namespace namaste {

	namespace geom {

		// ---------------------------------------------------------------
		// Matrix class
		// ---------------------------------------------------------------
		Matrix4x4::Matrix4x4() 
		{
			// Construct the identity matrix
			for (size_t i = 0; i < data.size(); ++i)
			{
				for (size_t j = 0; j < data[0].size(); ++j)
				{
					data[i][j] = (i == j) ? 1.0f : 0.0f;
				}
			}
		}

		Matrix4x4::~Matrix4x4() 
		{
		}

		std::ostream& operator<<(std::ostream &os, const Matrix4x4 &m)
		{
			for (size_t i = 0; i < m.data.size(); ++i)
			{
				os << "[";
				for (size_t j = 0; j < m.data[0].size(); ++j)
				{
					os << m.data[i][j];
					if (j < m.data[0].size() - 1)
					{
						os << ", ";
					}
				}
				os << "]\n";
			}
			return os;
		}


		// ---------------------------------------------------------------
		// Transform class
		// ---------------------------------------------------------------
		Transform::Transform()
		{
		}

		Transform::~Transform()
		{
		}

	} // namespace geom

} // namespace namaste
