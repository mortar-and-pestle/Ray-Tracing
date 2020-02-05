#include "Scene.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray& ray) //struct/Eigen::Vector3d position, normal;double t;
{
	HitRecord result;
	result.t = -1;
	bool foundSomething = false;

	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		HitRecord r = shapes[i]->intersect(ray);
		if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
			result = r;
			foundSomething = true;
		}
	}

	return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray& ray)
{
	// Add phong shading. Including diffuse, ambient and specular
	HitRecord r = closestHit(ray);

	Vector3d result;
	result[0] = result[1] = result[2] = 0;

	if (r.t < numeric_limits<double>::epsilon()) return result; //return black 0,0,0 of t is negative

	//ambient
	float ambientStr = 0.2f;
	Vector3d objectcolor;
	objectcolor[0] = 100;
	objectcolor[1] = 70;
	objectcolor[2] = 80;

	Vector3d ambient = ambientStr * objectcolor;

	//difuse
	Vector3d lightDir = (lightPos - r.position).normalized();
	double diffuse = lightDir.dot(r.normal); 
	if (diffuse < 0) diffuse = 0;
	Vector3d diff = diffuse * objectcolor;

	// Specular
	float specularStrength = 0.75f;
	Vector3d viewPos = ray.origin;
	Vector3d viewDir =(viewPos - r.position).normalized();
	Vector3d reflectDir = -lightDir - 2.0 * r.normal.dot(-lightDir) * r.normal; 

	float max{};
	//max function
	if (viewDir.dot(reflectDir) > 0)
		max = viewDir.dot(reflectDir);
	else
		max = 0.0;

	 
	float spec = pow(max, 32);

	Vector3d specular = specularStrength * spec * objectcolor;

	result = (ambient + diff + specular) * objectcolor;
	
	return result;
}

void Scene::render(Image& image)
{
	// We make the assumption that the camera is located at (0,0,0)
	// and that the image plane happens in the square from (-1,-1,1)
	// to (1,1,1).

	assert(image.getWidth() == image.getHeight());

	int size = image.getWidth();
	double pixelSize = 2. / size;
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
		{
			Ray curRay; //from shape(struct of vector3d origin and direction
			curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0; //set origin 3d vector to the origin. Ray cast from origin(camera)

			curRay.direction[0] = (x + 0.5) * pixelSize - 1;
			curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
			curRay.direction[2] = 1;

			Vector3d color = trace(curRay);
			image.setColor(x, y, color[0], color[1], color[2]);
		}
}
