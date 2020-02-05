#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "plane.h"

using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;

    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, 2));

	Vector3d position;// (-1,-1,-1) (result.position - c).normalized()
	position[0] = 0;
	position[1] = 0;
	position[2] = 4;

	Vector3d normalPoint;//
	normalPoint[0] = -8;
	normalPoint[1] = -4;
	normalPoint[2] = .5;
	
	scene.addShape(new Plane(position, normalPoint)); //add plane shape

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
