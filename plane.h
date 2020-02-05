#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

namespace Raytracer148
{
	class Plane : public Shape
	{
	public:
		Plane(Eigen::Vector3d& postition, Eigen::Vector3d& normal) : p(postition), n(normal) {}

		virtual HitRecord intersect(const Ray& ray);

	private:
		Eigen::Vector3d p;
		Eigen::Vector3d n;
	};
}

#endif
