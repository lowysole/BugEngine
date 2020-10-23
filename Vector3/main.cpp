#include "Vec3.h"
#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char* argv[])
{

	Vec3<float> a();
	Vec3<float> b(1, 2, 3);
	Vec3<float> c(4,5,6);
	Vec3<float> d = b + c;

	d.Normalize();

	float distance = d.distance_to(b);
	float dot_product = d.dot_product(b);
	Vec3<float> cross_product = d.cross_product(b);
	float angle = d.angle_between(b);

	//cout << "Distance d-b: " << distance << endl;
	//cout << "Dot product d-b: " << dot_product << endl;
	//cout << "Cross product d-b: (" << cross_product.x << ", " << cross_product.y << ", " << cross_product.z << ")" << endl;
	//cout << "Angle between d-b: " << angle << endl;
}

