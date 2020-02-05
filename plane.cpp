#include "plane.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Plane::intersect(const Ray& ray)
{
	HitRecord result;
	result.t = -1;

	float dotProN = ray.direction.dot(n); //Find dot product of ray and plane normal

	if (dotProN == .0f) //if result is turns out to be 0, then no intersection
		return result;

	float t = (p - ray.origin).dot(n)/dotProN; //get t

	result.t = t;
	result.position = ray.origin + result.t * ray.direction;
	result.normal = (result.position - p).normalized(); 



	return result;
}
