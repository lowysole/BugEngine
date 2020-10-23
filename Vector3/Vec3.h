#ifndef VEC3_H
#define VEC3_H

#include <cmath>

template<class T> 
class Vec3
{

public:

	Vec3() : x(0), y(0), z(0) {};
	Vec3(const T& vx, const T& vy, const T& vz) : x(vx), y(vy), z(vz) {};
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {};

	Vec3<T> operator+(const Vec3<T>& v) const {
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}

	void Normalize() {
		T length = getMagnitude();
		x = x / length;
		y = y / length;
		z = z / length;
	}

	T getMagnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	T distance_to(const Vec3<T>& vec) const {
		T x_dist = x - vec.x;
		T y_dist = y - vec.y;
		T z_dist = z - vec.z;
		return sqrt(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist);
	}

	T dot_product(const Vec3<T>& vec) const {
		return (x * vec.x + y * vec.y + z * vec.z); 
	}

	Vec3<T> cross_product(const Vec3<T>& vec) const {
		return Vec3(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
			);
	}

	T angle_between(const Vec3<T>& vec) const {
		return acos(this->dot_product(vec) / (this->getMagnitude() * vec.getMagnitude()));
	}

	T x, y, z;
};

#endif 