#include "Vec3.h"


Vec3::Vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(const Vec3& vec3) {
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
}

Vec3::~Vec3() {

}