#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"
#include "matrix.h"

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
    IResult r = tree->minhit(ray);
    Hit min_hit = r.hit;
    ObjectPtr obj = r.obj;

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material material = obj->material;          //the hit objects material
    if (min_hit.mat) {
        material = *min_hit.mat;
    }
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = ray.D;                             //the view vector

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
	
	Point texCoord = min_hit.texPt;
    if (material.hasNorm()) {
        Vector M = material.normalAt(texCoord.x, texCoord.y).normalized();
        Vector t = N.cross(Vector(0, 1, 0));
        if (t.length() == 0) {
            t = N.cross(Vector(0, 0, 1));
        }
        Vector b = N.cross(t);
        Matrix44 tbn;
        for (int i = 0; i < 3; i++) {
            tbn[i][0] = t.data[i];
            tbn[i][1] = b.data[i];
            tbn[i][2] = N.data[i];
        }
        N = tbn * M;
    }
    bool out = false;
    if (N.dot(V) > 0) {
        N = -N;
        out = true;
    }
	Color matC = material.colorAt(texCoord.x, texCoord.y);
    
    for (unsigned i = 0; i < getNumLights(); i++){
		LightPtr light = lights[i];
		Vector L = (light->position - hit).normalized();
		Vector R = 2*(N.dot(L)*N) - L;
		if (shadows) {
			Ray shadowRay = Ray(hit + EPSILON * L, L);
			double len = (light->position - hit).length();
            IResult r = tree->minhit(shadowRay);
            Hit min_hit = r.hit;
            ObjectPtr obj = r.obj;
            if (min_hit.t < len) {
                continue;
            }
		}
        double diff = fmax(0, L.dot(N));
        if (cel) {
            diff = ceil(diff*cel)/cel;
        }
		color += diff * matC * light->color * material.kd; //Diffuse
		color += pow(fmax(0, R.dot(-V)), material.n) * light->color * material.ks; //Specular
	}

	
	if (material.ks > 0) {
        double kr = 1;
        // Refraction
        if (material.transparent) {
            double eta1 = 1;
            double eta2 = material.eta;
            double eta = eta1/eta2;
            if (out) {
                double temp = eta1;
                eta1 = eta2;
                eta2 = temp;
                eta = 1/eta;
            }
            double cosv = -(V.dot(N));
            double sin2v = 1 - cosv*cosv;
            
            double sin2t = eta*eta*sin2v;
            if (sin2t <= 1) {
                double cost = sqrt(1 - sin2t);

                Vector T = eta*V + (eta*cosv - cost)*N;

                // compute Schlick approx. for Fresnel
                double r0 = ((eta2 - 1)/(eta2 + 1));
                r0 *= r0;
                kr = r0 + (1 - r0) * pow(1 - (eta > 1 ? cosv : cost), 5);

                Ray transmissionRay = Ray(hit + EPSILON * T, T);
                color += trace(transmissionRay, depth + 1) * material.ks * (1 - kr);
            }

        }
	    // Reflection
		Vector R = V - 2*(V.dot(N)*N);
		Ray reflectionRay = Ray(hit + EPSILON * R, R);
		color += trace(reflectionRay, depth + 1) * material.ks * kr;
	}

    color += matC * material.ka;

    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    camera->setDimensions(w, h);

    vector<BBox> boxes;
    for (unsigned i = 0; i < objects.size(); i++) {
        boxes.push_back(objects[i]->boundingBox());
    }

    tree = new ObjTree(objects, boxes, 15);
    
    #pragma omp parallel for
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
			Color col = Color(0,0,0);
			for (int sy = 0; sy*sy < sampleFactor; sy++) {
				for (int sx = 0; sx*sx < sampleFactor; sx++) {
				    Ray ray = camera->rayAt(x + (sx+1)/(sqrt(sampleFactor)+1), y + (sy+1)/(sqrt(sampleFactor)+1));
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

void Scene::setCamera(Camera *camera) {
    this->camera = camera;
}
