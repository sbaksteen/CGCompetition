#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "scene.h"
#include "object.h"
#include "shapes/closedObject.h"

#include <string>

// Forward declerations
class Light;
class Material;

#include "json/json_fwd.h"

class Raytracer
{
    Scene scene;
    unsigned w = 400, h = 400;

    public:

        bool readScene(std::string const &ifname);
        void renderToFile(std::string const &ofname);

    private:

        ClosedPtr parseClosedObject(nlohmann::json const &node);
        bool parseObjectNode(nlohmann::json const &node);

        Light parseLightNode(nlohmann::json const &node) const;
        Material parseMaterialNode(nlohmann::json const &node) const;
        Camera* parseCameraNode(nlohmann::json const &node) const;
		
		std::string path;
};

#endif
