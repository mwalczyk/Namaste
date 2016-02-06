#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include <assert.h>

namespace namaste {

	namespace geom {

		// Forward declarations for explicit constructors
		class Point;
		class Normal;

		class Vector
		{
		public:
			Vector();
			Vector(float aX, float aY, float aZ);
			Vector(const Vector &rhs);
			explicit Vector(const Point &rhs);
			explicit Vector(const Normal &rhs);
			explicit Vector(float aXYZ);
			~Vector();

			Vector operator+(const Vector &rhs) const;
			Vector& operator+=(const Vector &rhs);

			Vector operator-(const Vector &rhs) const;
			Vector& operator-=(const Vector &rhs);

			Vector operator*(float scalar) const;
			Vector& operator*=(float scalar);

			Vector operator/(float scalar) const;
			Vector& operator/=(float scalar);

			Vector operator-() const;

			float operator[](int i) const;
			float& operator[](int i);

			bool operator==(const Vector &rhs) const;
			bool operator!=(const Vector &rhs) const;

			friend std::ostream& operator<<(std::ostream &os, const Vector &v)
			{
				os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
				return os;
			}

			float lengthSquared() const;
			float length() const;

			float x, y, z;
		private:
			bool hasNaNs() const;
		};

		class Point
		{
		public:
			Point();
			Point(float aX, float aY, float aZ);
			Point(const Point &rhs);
			~Point();

			Point operator+(const Vector &rhs) const;
			Point& operator+=(const Vector &rhs);

			Point operator+(const Point &rhs) const;
			Point& operator+=(const Point &rhs);

			Vector operator-(const Point &rhs) const;
			Point operator-(const Vector &rhs) const;
			Point& operator-=(const Vector &rhs);

			Point operator*(float scalar) const;
			Point& operator*=(float scalar);

			Point operator/(float scalar) const;
			Point& operator/=(float scalar);

			float operator[](int i) const;
			float& operator[](int i);

			bool operator==(const Point &rhs) const;
			bool operator!=(const Point &rhs) const;

			friend std::ostream& operator<<(std::ostream &os, const Point &p)
			{
				os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
				return os;
			}

			float x, y, z;
		private:
			bool hasNaNs() const;
		};

		class Normal
		{
		public:
			Normal();
			Normal(float aX, float aY, float aZ);
			Normal(const Normal &rhs);
			explicit Normal(const Vector &rhs);
			~Normal();

			Normal operator+(const Normal &rhs) const;
			Normal& operator+=(const Normal &rhs);

			Normal operator-(const Normal &rhs) const;
			Normal& operator-=(const Normal &rhs);

			Normal operator*(float scalar) const;
			Normal& operator*=(float scalar);

			Normal operator/(float scalar) const;
			Normal& operator/=(float scalar);

			Normal operator-() const;

			float operator[](int i) const;
			float& operator[](int i);

			bool operator==(const Normal &rhs) const;
			bool operator!=(const Normal &rhs) const;

			friend std::ostream& operator<<(std::ostream &os, const Normal &n)
			{
				os << "[" << n.x << ", " << n.y << ", " << n.z << "]";
				return os;
			}

			float lengthSquared() const;
			float length() const;

			float x, y, z;
		private:
			bool hasNaNs() const;
		};

		class Ray
		{
		public:
			Ray();
			Ray(const Point &aOrigin, const Vector &aDirection, float aMinT, float aMaxT, float aTime, int aDepth);
			Ray(const Point &aOrigin, const Vector &aDirection, const Ray &aParent, float aMinT, float aMaxT);
			~Ray();

			Point operator()(float t) const;

			// The parametric equation for a ray is: r(t) = o + t*d
			// minT and maxT are mutable, meaning they can be modified even if
			// the Ray object containing them is const: in functions taking a 
			// const Ray&, we don't want the caller to be able to change the ray's
			// origin or direction, but minT and maxT should and can be altered 
			Point o;
			Vector d;
			mutable float minT;
			mutable float maxT;
			float time;
			int depth;
		private:
		};

		class RayDifferential : public Ray
		{
		public:
			RayDifferential();
			RayDifferential(const Point &aOrigin, const Vector &aDirection, float aMinT, float aMaxT, float aTime, int aDepth);
			RayDifferential(const Point &aOrigin, const Vector &aDirection, const Ray &aParent, float aMinT, float aMaxT);
			explicit RayDifferential(const Ray &aRay);
			~RayDifferential();

			void scaleDifferentials(float scale);

			bool hasDifferentials;
			Point rxOrigin;
			Point ryOrigin;
			Vector rxDirection;
			Vector ryDirection;
		private:
		};

		class BBox
		{
		public:
			BBox();
			BBox(const Point &aPoint);
			BBox(const Point &aPoint1, const Point &aPoint2);
			~BBox();

			const Point& operator[](int i) const;
			Point& operator[](int i);

			bool operator==(const BBox &rhs) const;
			bool operator!=(const BBox &rhs) const;

			bool overlaps(const BBox &aBBox) const;
			bool inside(const Point &aPoint) const;
			void expand(float delta);
			float surfaceArea() const;
			float volume() const;
			int maximumExtent() const;
			Point lerp(float aTx, float aTy, float aTz) const;
			Vector offset(const Point &aPoint) const;
			void boundingSphere(Point *center, float *radius) const;

			friend BBox calcUnion(const BBox &aBBox, const Point &aPoint);
			friend BBox calcUnion(const BBox &aBBox1, const BBox &aBBox2);

			// An axis-aligned bounding box implementation that
			// stores two opposite vertices of the box
			Point pMin;
			Point pMax;
		private:
		};

		// Geometry inline functions
		inline Vector operator*(float scalar, const Vector &v) { return v * scalar; }
		inline Point operator*(float scalar, const Point &p) { return p * scalar; }
		inline Normal operator*(float scalar, const Normal &n) { return n * scalar; }

		inline float dot(const Vector &lhs, const Vector &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; } // V V
		inline float dot(const Vector &lhs, const Normal &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; } // V N
		inline float dot(const Normal &lhs, const Vector &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; } // N V
		inline float dot(const Normal &lhs, const Normal &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; } // N N

		inline float absDot(const Vector &lhs, const Vector &rhs) { return fabsf(dot(lhs, rhs)); } // V V
		inline float absDot(const Vector &lhs, const Normal &rhs) { return fabsf(dot(lhs, rhs)); } // V N
		inline float absDot(const Normal &lhs, const Vector &rhs) { return fabsf(dot(lhs, rhs)); } // N V
		inline float absDot(const Normal &lhs, const Normal &rhs) { return fabsf(dot(lhs, rhs)); } // N N

		inline Vector cross(const Vector &lhs, const Vector &rhs)	// V V
		{
			return Vector((lhs.y * rhs.z) - (lhs.z * rhs.y),
				(lhs.z * rhs.x) - (lhs.x * rhs.z),
				(lhs.x * rhs.y) - (lhs.y * rhs.x));
		}

		inline Vector cross(const Vector &lhs, const Normal &rhs)	// V N
		{
			return Vector((lhs.y * rhs.z) - (lhs.z * rhs.y),
				(lhs.z * rhs.x) - (lhs.x * rhs.z),
				(lhs.x * rhs.y) - (lhs.y * rhs.x));
		}

		inline Vector cross(const Normal &lhs, const Vector &rhs)	// N V
		{
			return Vector((lhs.y * rhs.z) - (lhs.z * rhs.y),
				(lhs.z * rhs.x) - (lhs.x * rhs.z),
				(lhs.x * rhs.y) - (lhs.y * rhs.x));
		}

		inline Vector normalize(const Vector &v) { return v / v.length(); }
		inline Normal normalize(const Normal &n) { return n / n.length(); }

		inline void coordinateSystem(const Vector &v1, Vector *v2, Vector *v3)
		{
			// Construct a local coordinate system given a single, normalized vector v1
			// Find the first perpendicular vector by zeroing out a component of v1 and
			// swapping the remaining two components
			if (fabsf(v1.x) > fabsf(v1.y))
			{
				float invLen = 1.0f / sqrtf(v1.x * v1.x + v1.z * v1.z);
				*v2 = Vector(-v1.z * invLen, 0.0f, v1.x * invLen);
			}
			else
			{
				float invLen = 1.0f / sqrtf(v1.y * v1.y + v1.z * v1.z);
				*v2 = Vector(0.0f, v1.z * invLen, -v1.y * invLen);
				;
			}
			*v3 = cross(v1, *v2);
		}

		inline float distanceSquared(const Point &rhs, const Point &lhs)
		{
			return (rhs - lhs).lengthSquared();
		}

		inline float distance(const Point &rhs, const Point &lhs)
		{
			// Compute the length of the vector between the two points
			return (rhs - lhs).length();
		}

		inline Normal faceForward(const Normal &n, const Vector &v)		// N V
		{
			// Flip the surface normal so that it lies in the same
			// hemisphere as v
			return (dot(n, v) < 0.0f) ? -n : n;
		}

		inline Vector faceForward(const Vector &v, const Normal &n)		// V N
		{
			return (dot(v, n) < 0.0f) ? -v : v;
		}

		inline Normal faceForward(const Normal &n1, const Normal &n2)	// N N
		{
			return (dot(n1, n2) < 0.0f) ? -n1 : n1;
		}

		inline Vector faceForward(const Vector &v1, const Vector &v2)	// V V
		{
			return (dot(v1, v2) < 0.0f) ? -v1 : v1;
		}

	}
} // namespace namaste

inline float lerp(float t, float v1, float v2) {
	return (1.0f - t) * v1 + t * v2;
}