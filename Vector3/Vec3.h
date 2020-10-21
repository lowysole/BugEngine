#pragma once
class Vec3
{

public:

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec3& vec);
	~Vec3();

	Vec3 Normalize();


	float x;
	float y;
	float z;

};

