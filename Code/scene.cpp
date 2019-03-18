#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>

#include <iostream>

#define EPSILON 0.001 
// a small number such that shadow rays will not intersect their origin.

using namespace std;

Color Scene::trace(Ray const &ray) {
	return trace(ray, 0);
}

Color Scene::trace(Ray const &ray, int depth)
{
	if (depth > maxDepth) {
		return Color(0, 0, 0);
	}
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material material = obj->material;          //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector + Vector    vector sum
    *        Vector - Vector    vector difference
    *        Point - Point      yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double * Color     scales each color component (r,g,b)
    *        Color * Color      dito
    *        pow(a,b)           a to the power of b
    ****************************************************/
    
    Color color = Color(0.0, 0.0, 0.0);
	
	Point texCoord = obj->textureCoordAt(hit);
	Color matC = material.colorAt(texCoord.x, texCoord.y);
    
    for (unsigned i = 0; i < getNumLights(); i++){
		LightPtr light = lights[i];
		Vector L = (light->position - hit).normalized();
		Vector R = 2*(N.dot(L)*N) - L;
		if (shadows) {
			Ray shadowRay = Ray(hit + EPSILON * L, L);
			double len = (light->position - hit).length();
			bool h = false;
			for (unsigned idx = 0; idx != objects.size(); ++idx) {
				Hit hit(objects[idx]->intersect(shadowRay));
				if (hit.t < len) {
					h = true;
				}
			}
			if (h) {
				continue;
			}
		}
		color += fmax(0,L.dot(N)) * matC * light->color * material.kd; //Diffuse
		color += pow(fmax(0, R.dot(V)), material.n) * light->color * material.ks; //Specular
	}
	
	// Reflection
	if (material.ks > 0) {
		Vector R = 2*(N.dot(V)*N) - V;
		Ray reflectionRay = Ray(hit + EPSILON * R, R);
		color += trace(reflectionRay, depth + 1) * material.ks;
	}

    color += matC * material.ka;

    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    
    #pragma omp parallel for
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
			Color col = Color(0,0,0);
			for (int sy = 0; sy*sy < sampleFactor; sy++) {
				for (int sx = 0; sx*sx < sampleFactor; sx++) {
					Point pixel(x + (sx+1)/(sqrt(sampleFactor)+1), h - 1 - y + (sy+1)/(sqrt(sampleFactor)+1), 0);
					Ray ray(eye, (pixel - eye).normalized());
					col += trace(ray);
				}
			}
			col /= sampleFactor;
			col.clamp();
			img(x, y) = col;
        }
    }
}

// --- Misc functions ----------------------------------------------------------

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

void Scene::setShadows(bool s) {
	shadows = s;
}

void Scene::setMaxDepth(int m) {
	maxDepth = m;
}

void Scene::setSampleFactor(int s) {
	sampleFactor = s;
}

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}
