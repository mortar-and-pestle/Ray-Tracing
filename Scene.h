#ifndef SCENE_H
#define SCENE_H

#include "Shape.h"
#include "Image.h"
#include <vector>
#include <limits>

namespace Raytracer148
{
	class Scene
	{
	public:
		Scene()
		{
			lightPos[0] = lightPos[1] = 3;
			lightPos[2] = 0;
		}

		virtual ~Scene()
		{
			for (unsigned int i = 0; i < shapes.size(); i++)
				delete shapes[i];
			shapes.resize(0);
		}

		void addShape(Shape* s) { shapes.push_back(s); }
		HitRecord closestHit(const Ray& ray); //hitrecord is struct containing normal,position, and double
		Eigen::Vector3d trace(const Ray& ray); //ray is a struct in shape with 3dvector origin and direction
		void render(Image& image);

	private:
		std::vector<Shape*> shapes;
		Eigen::Vector3d lightPos;
	};
}

#endif
