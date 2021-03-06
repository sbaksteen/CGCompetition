#ifndef SCENE_H_
#define SCENE_H_

#include "light.h"
#include "object.h"
#include "triple.h"
#include "spacePartitioning/objtree.h"
#include "camera.h"

#include <vector>

// Forward declerations
class Ray;
class Image;

class Scene
{
    std::vector<ObjectPtr> objects;
    std::vector<LightPtr> lights;   // no ptr needed, but kept for consistency
    Camera* camera;
    ObjTree* tree;
	bool shadows = false;
    int cel = 0;
	int maxDepth = 0;
	int sampleFactor = 1;

    public:

        // trace a ray into the scene and return the color
        Color trace(Ray const &ray, int depth);
		Color trace(Ray const &ray);

        // render the scene to the given image
        void render(Image &img);


        void addObject(ObjectPtr obj);
        void addLight(Light const &light);
        void setCamera(Camera* camera);
		void setShadows(bool s);
        void setCel(int c) {
            cel = c;
        }
		void setMaxDepth(int m);
		void setSampleFactor(int s);

        unsigned getNumObject();
        unsigned getNumLights();
};

#endif
