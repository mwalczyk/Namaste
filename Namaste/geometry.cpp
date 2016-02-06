#include "stdafx.h"
#include "geometry.h"

namespace namaste {

	namespace geom {

		// ---------------------------------------------------------------
		// Vector class
		// ---------------------------------------------------------------
		Vector::Vector() :
			x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vector::Vector(float aX, float aY, float aZ) :
			x(aX), y(aY), z(aZ)
		{
			assert(!hasNaNs());
		}

		Vector::Vector(const Vector &rhs) :
			x(rhs.x), y(rhs.y), z(rhs.z)
		{
		}

		Vector::Vector(const Point &rhs) :
			x(rhs.x), y(rhs.y), z(rhs.z)
		{
			// Explicit
		}

		Vector::Vector(const Normal &rhs) :
			x(rhs.x), y(rhs.y), z(rhs.z)
		{
			// Explicit
		}

		Vector::Vector(float aXYZ) :
			x(aXYZ), y(aXYZ), z(aXYZ)
		{
			// Explicit
		}

		Vector::~Vector()
		{
		}

		Vector Vector::operator+(const Vector &rhs) const
		{
			return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector& Vector::operator+=(const Vector &rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		Vector Vector::operator-(const Vector &rhs) const
		{
			return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector& Vector::operator-=(const Vector &rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		Vector Vector::operator*(float scalar) const
		{
			return Vector(x * scalar, y * scalar, z * scalar);
		}

		Vector& Vector::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector Vector::operator/(float scalar) const
		{
			// Compute the scalar's reciprocal and perform three component-wise
			// multiplications to avoid costly division operations
			assert(scalar != 0.0f);
			float inv = 1.0f / scalar;
			return Vector(x * inv, y * inv, z * inv);
		}

		Vector& Vector::operator/=(float scalar)
		{
			assert(scalar != 0.0f);
			float inv = 1.0f / scalar;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		Vector Vector::operator-() const
		{
			return Vector(-x, -y, -z);
		}

		float Vector::operator[](int i) const
		{
			assert(i >= 0 && i <= 2);
			return (&x)[i];
		}

		float& Vector::operator[](int i)
		{
			assert(i >= 0 && i <= 2);
			return (&x)[i];
		}

		bool Vector::operator==(const Vector &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool Vector::operator!=(const Vector &rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		float Vector::lengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		float Vector::length() const
		{
			return sqrtf(lengthSquared());
		}

		bool Vector::hasNaNs() const
		{
			return isnan(x) || isnan(y) || isnan(z);
		}

		// ---------------------------------------------------------------
		// Point class
		// ---------------------------------------------------------------
		Point::Point() :
			x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Point::Point(float aX, float aY, float aZ) :
			x(aX), y(aY), z(aZ)
		{
			assert(!hasNaNs());
		}

		Point::Point(const Point &rhs) :
			x(rhs.x), y(rhs.y), z(rhs.z)
		{
		}

		Point::~Point()
		{
		}

		Point Point::operator+(const Vector &rhs) const
		{
			return Point(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Point& Point::operator+=(const Vector &rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		Point Point::operator+(const Point &rhs) const
		{
			// Although it doesn't make sense mathematically to add two points 
			// together, we still allow these operations in order to be able to
			// compute weighted sums of points
			return Point(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Point& Point::operator+=(const Point &rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		Vector Point::operator-(const Point &rhs) const
		{
			return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Point Point::operator-(const Vector &rhs) const
		{
			return Point(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Point& Point::operator-=(const Vector &rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		Point Point::operator*(float scalar) const
		{
			// Although it doesn't make sense mathematically to weight points 
			// by a scalar, we still allow these operations for convenience
			return Point(x * scalar, y * scalar, z * scalar);
		}

		Point& Point::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Point Point::operator/(float scalar) const
		{
			assert(scalar != 0.0f);
			float inv = 1.0f / scalar;
			return Point(x * inv, y * inv, z * inv);
		}

		Point& Point::operator/=(float scalar)
		{
			assert(scalar != 0.0f);
			float inv = 1.0f / scalar;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		float Point::operator[](int i) const
		{
			assert(i >= 0 && i <= 2);
			return (&x)[i];
		}

		float& Point::operator[](int i)
		{
			assert(i >= 0 && i <= 2);
			return (&x)[i];
		}

		bool Point::operator==(const Point &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool Point::operator!=(const Point &rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		bool Point::hasNaNs() const
		{
			return isnan(x) || isnan(y) || isnan(z);
		}

		// ---------------------------------------------------------------
		// Normal class
		// ---------------------------------------------------------------
		Normal::Normal() :
			x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Normal::Normal(float aX, float aY, float aZ) :
			x(aX), y(aY), z(aZ)
		{
			assert(!hasNaNs());
		}

		Normal::Normal(const Normal &rhs) :
			x(rhs.x), y(rhs.y), z(rhs.z)
		{
		}

		Normal::Normal(const Vector &rhs) :
			x(rhs.x), y(rhs.y), z(rhs.z)
		{
			// Explicit
			// This means we can't accidently do things like: Normal n = v
			// Instead, we'd have to explicitly write: Normal n = Normal(v)
		}

		Normal::~Normal()
		{
		}

		Normal Normal::operator+(const Normal &rhs) const
		{
			return Normal(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Normal& Normal::operator+=(const Normal &rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		Normal Normal::operator-(const Normal &rhs) const
		{
			return Normal(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Normal& Normal::operator-=(const Normal &rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		Normal Normal::operator*(float scalar) const
		{
			return Normal(x * scalar, y * scalar, z * scalar);
		}

		Normal& Normal::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Normal Normal::operator/(float scalar) const
		{
			assert(scalar != 0.0f);
			float inv = 1.0f / scalar;
			return Normal(x * inv, y * inv, z * inv);
		}

		Normal& Normal::operator/=(float scalar)
		{
			assert(scalar != 0.0f);
			float inv = 1.0f / scalar;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		Normal Normal::operator-() const
		{
			return Normal(-x, -y, -z);
		}

		float Normal::operator[](int i) const
		{
			assert(i >= 0 && i <= 2);
			return (&x)[i];
		}

		float& Normal::operator[](int i)
		{
			assert(i >= 0 && i <= 2);
			return (&x)[i];
		}

		bool Normal::operator==(const Normal &rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool Normal::operator!=(const Normal &rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		float Normal::lengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		float Normal::length() const
		{
			return sqrtf(lengthSquared());
		}

		bool Normal::hasNaNs() const
		{
			return isnan(x) || isnan(y) || isnan(z);
		}

		// ---------------------------------------------------------------
		// Ray class
		// ---------------------------------------------------------------
		Ray::Ray() : minT(0.0f), maxT(INFINITY), time(0.0f), depth(0)
		{
		}

		Ray::Ray(const Point &aOrigin, const Vector &aDirection, float aMinT, float aMaxT = INFINITY, float aTime = 0.0f, int aDepth = 0) :
			o(aOrigin), d(aDirection), minT(aMinT), maxT(aMaxT), time(aTime), depth(aDepth)
		{
		}

		Ray::Ray(const Point &aOrigin, const Vector &aDirection, const Ray &aParent, float aMinT, float aMaxT = INFINITY) :
			o(aOrigin), d(aDirection), minT(aMinT), maxT(aMaxT), time(aParent.time), depth(aParent.depth + 1)
		{
			// When we spawn additional rays at a point of intersection, it's useful to be able to copy the time value and 
			// set the depth value for the new ray based on the corresponding values from the previous ray
		}

		Ray::~Ray()
		{
		}

		Point Ray::operator()(float t) const
		{
			// Overload the function call operator to return a point at position t along the ray
			return o + d * t;
		}

		// ---------------------------------------------------------------
		// Ray differential class
		// ---------------------------------------------------------------
		RayDifferential::RayDifferential()
		{
			// Calls Ray() by default
		}

		RayDifferential::RayDifferential(const Point &aOrigin, const Vector &aDirection, float aMinT, float aMaxT = INFINITY, float aTime = 0.0f, int aDepth = 0) :
			Ray(aOrigin, aDirection, aMinT, aMaxT, aTime, aDepth)
		{
			// Calls equivalent base class constructor
			hasDifferentials = false;
		}

		RayDifferential::RayDifferential(const Point &aOrigin, const Vector &aDirection, const Ray &aParent, float aMinT, float aMaxT = INFINITY) :
			Ray(aOrigin, aDirection, aMinT, aMaxT, aParent.time, aParent.depth + 1)
		{
			// Calls equivalent base class constructor
			hasDifferentials = false;
		}

		RayDifferential::RayDifferential(const Ray &aRay) :
			Ray(aRay)
		{
			// Explicit
			hasDifferentials = false;
		}

		RayDifferential::~RayDifferential()
		{
		}

		void RayDifferential::scaleDifferentials(float scale)
		{
			rxOrigin = o + (rxOrigin - o) * scale;
			ryOrigin = o + (ryOrigin - o) * scale;
			rxDirection = d + (rxDirection - d) * scale;
			ryDirection = d + (ryDirection - d) * scale;
		}

		// ---------------------------------------------------------------
		// Bounding box class
		// ---------------------------------------------------------------
		BBox::BBox() :
			pMin(INFINITY, INFINITY, INFINITY), pMax(-INFINITY, -INFINITY, -INFINITY)
		{
			// Set the extent of the bounding box to be degenerate: by violating the 
			// invariant that pMin.xyz <= pMax.xyz, we ensure that an operations done
			// with the 'zero' bounding box will have the correct result
		}

		BBox::BBox(const Point &aPoint) :
			pMin(aPoint), pMax(aPoint)
		{
			// Construct a bounding box that 'encloses' a single point
		}

		BBox::BBox(const Point &aPoint1, const Point &aPoint2)
		{
			// aPoint1 and aPoint2 won't necessarily be chosen to fit the constraint
			// that pMin.xyz <= pMax.xyz, so we calculate two new points here
			pMin = Point(std::min(aPoint1.x, aPoint2.x), std::min(aPoint1.y, aPoint2.y), std::min(aPoint1.z, aPoint2.z));
			pMax = Point(std::max(aPoint1.x, aPoint2.x), std::max(aPoint1.y, aPoint2.y), std::max(aPoint1.z, aPoint2.z));
		}

		BBox::~BBox()
		{
		}

		const Point& BBox::operator[](int i) const
		{
			assert(i == 0 || i == 1);
			return (&pMin)[i];
		}

		Point& BBox::operator[](int i)
		{
			assert(i == 0 || i == 1);
			return (&pMin)[i];
		}

		bool BBox::operator==(const BBox &rhs) const
		{
			return pMin == rhs.pMin && pMax == rhs.pMax;
		}

		bool BBox::operator!=(const BBox &rhs) const
		{
			return pMin != rhs.pMin || pMax != rhs.pMax;
		}

		bool BBox::overlaps(const BBox &aBBox) const
		{
			bool xOverlaps = (pMax.x >= aBBox.pMin.x) && (pMin.x <= aBBox.pMax.x);
			bool yOverlaps = (pMax.y >= aBBox.pMin.y) && (pMin.y <= aBBox.pMax.y);
			bool zOverlaps = (pMax.z >= aBBox.pMin.z) && (pMin.z <= aBBox.pMax.z);
			return xOverlaps && yOverlaps && zOverlaps;
		}

		bool BBox::inside(const Point &aPoint) const
		{
			return (aPoint.x >= pMin.x && aPoint.x <= pMax.x &&
				aPoint.y >= pMin.y && aPoint.y <= pMax.y &&
				aPoint.z >= pMin.z && aPoint.z <= pMax.z);
		}

		void BBox::expand(float delta)
		{
			pMin -= Vector(delta);
			pMax += Vector(delta);
		}

		float BBox::surfaceArea() const
		{
			Vector d = pMax - pMax;
			return 2.0f * (d.x * d.y +		// Front + back faces
				d.x * d.z +		// Bottom + top faces
				d.y * d.z);		// Left + right faces
		}

		float BBox::volume() const
		{
			Vector d = pMax - pMin;
			return d.x * d.y * d.z;
		}

		int BBox::maximumExtent() const
		{
			// Determines which axis of the bounding box is longest:
			// 1 -> x-axis
			// 2 -> y-axis
			// 3 -> z-axis
			Vector diagonal = pMax - pMin;
			if (diagonal.x > diagonal.y && diagonal.x > diagonal.z)
			{
				return 0;
			}
			else if (diagonal.y > diagonal.z)
			{
				return 1;
			}
			return 2;
		}

		Point BBox::lerp(float aTx, float aTy, float aTz) const
		{
			return Point(::lerp(aTx, pMin.x, pMax.x),
				::lerp(aTy, pMin.y, pMax.y),
				::lerp(aTz, pMin.z, pMax.z));
		}

		Vector BBox::offset(const Point &aPoint) const
		{	
			// Return the position of a point relative to the corners of
			// the box, where a point at the minimum corner has offset (0,0,0),
			// and a point at the maximum corner has offset (1,1,1)
			return Vector((aPoint.x - pMin.x) / (pMax.x - pMin.x),
						  (aPoint.y - pMin.y) / (pMax.y - pMin.y),
				          (aPoint.z - pMin.z) / (pMax.z - pMin.z));
		}

		void BBox::boundingSphere(Point *center, float *radius) const
		{
			*center = 0.5f * (pMin + pMax);
			*radius = inside(*center) ? distance(*center, pMax) : 0.0f;
		}

		BBox calcUnion(const BBox &aBBox, const Point &aPoint)
		{
			// Given a bounding box and a point, compute and return a new bounding
			// box that encompasses that point as well as the space that the original
			// bounding box encompassed
			BBox ret;

			ret.pMin.x = std::min(aBBox.pMin.x, aPoint.x);
			ret.pMin.y = std::min(aBBox.pMin.y, aPoint.y);
			ret.pMin.z = std::min(aBBox.pMin.z, aPoint.z);

			ret.pMax.x = std::max(aBBox.pMax.x, aPoint.x);
			ret.pMax.y = std::max(aBBox.pMax.y, aPoint.y);
			ret.pMax.z = std::max(aBBox.pMax.z, aPoint.z);

			return ret;
		}

		BBox calcUnion(const BBox &aBBox1, const BBox &aBBox2)
		{
			BBox ret;

			ret.pMin.x = std::min(aBBox1.pMin.x, aBBox2.pMin.x);
			ret.pMin.y = std::min(aBBox1.pMin.y, aBBox2.pMin.y);
			ret.pMin.z = std::min(aBBox1.pMin.z, aBBox2.pMin.z);

			ret.pMax.x = std::max(aBBox1.pMax.x, aBBox2.pMax.x);
			ret.pMax.y = std::max(aBBox1.pMax.y, aBBox2.pMax.y);
			ret.pMax.z = std::max(aBBox1.pMax.z, aBBox2.pMax.z);

			return ret;
		}

	} // namespace geom

} // namespace namaste