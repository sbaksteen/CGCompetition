#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"
#include "matrix.h"
#include "vertex.h"
#include "objloader.h"

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/sphere.h"
#include "shapes/triangle.h"
#include "shapes/plane.h"
#include "shapes/quad.h"
#include "shapes/mesh.h"
#include "shapes/torus.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "shapes/transformedObject.h"

// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>

using namespace std;        // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node)
{
    ObjectPtr obj = nullptr;

// =============================================================================
// -- Determine type and parse object parametrers ------------------------------
// =============================================================================

    if (node["type"] == "sphere")
    {
        double radius = node["radius"];
        obj = ObjectPtr(new Sphere(radius));
    } 
	else if (node["type"] == "cylinder") {
		double radius = node["radius"];
		double height = node["height"];
		obj = ObjectPtr(new Cylinder(radius, height));
	} 
	else if (node["type"] == "cone") {
		double height = node["height"];
		obj = ObjectPtr(new Cone(height));
	}
	else if (node["type"] == "torus") {
		double major = node["major"];
		double minor = node["minor"];
		obj = ObjectPtr(new Torus(major, minor));
	}
    else if (node["type"] == "triangle")
    {	
		Vertex a = {node["verts"][0][0], node["verts"][0][1], node["verts"][0][2]};
		Vertex b = {node["verts"][1][0], node["verts"][1][1], node["verts"][1][2]};
		Vertex c = {node["verts"][2][0], node["verts"][2][1], node["verts"][2][2]};
		obj = ObjectPtr(new Triangle(a, b, c));
	}
	else if (node["type"] == "quad")
    {	
		Vertex a = {node["verts"][0][0], node["verts"][0][1], node["verts"][0][2]};
		Vertex b = {node["verts"][1][0], node["verts"][1][1], node["verts"][1][2]};
		Vertex c = {node["verts"][2][0], node["verts"][2][1], node["verts"][2][2]};
		Vertex d = {node["verts"][3][0], node["verts"][3][1], node["verts"][3][2]};
		
		// Verts must be specified in a correct order (along the edge of the
		// Quad) So that two triangles are drawn correctly. Furthermore, 
		// all points must be on the same plane, otherwise a "broken" 
		// quad will be drawn
		obj = ObjectPtr(new Quad(a, b, c, d));
	}  
	else if (node["type"] == "plane")
	{
		Vector N(node["normal"]);
		obj = ObjectPtr(new Plane(N));
	}
	else if (node["type"] == "mesh")
	{
		string const fp =  node["filepath"];
		OBJLoader* mesh = new OBJLoader(fp);
		vector<Vertex> verts = mesh->vertex_data();
		vector<Vertex> unitizedVerts = mesh->unitize(verts);
		vector<Vertex> scaledVerts = mesh->scale(200, unitizedVerts);
		obj = ObjectPtr(new Mesh(scaledVerts));
	}
	else 
    {
        cerr << "Unknown object type: " << node["type"] << ".\n";
    }
	
    if (!obj)
		return false;

    // Parse material
    obj->material = parseMaterialNode(node["material"]);
	
	
	// Matrix transformation: scale, rotation, and translation.
	bool transform = false;
	Matrix44 transformMat = Matrix44();

	if (node.count("position")) {
		transform = true;
		Vector translate(node["position"]);
		transformMat.translate(translate);
	}
	if (node.count("rotationAxis")) {
		if (!node.count("angle")) {
			cerr << "Angle not present for rotation.\n";
		} else {
			transform = true;
			Vector axis(node["rotationAxis"]);
			double angle = node["angle"];
			angle *= M_PI/180;
			transformMat.rotate(axis, angle);
		}
	}
	if (node.count("uniformScale")) {
		transform = true;
		double scaleFactor = node["uniformScale"];
		Vector scale = Vector(scaleFactor, scaleFactor, scaleFactor);
		transformMat.scale(scale);
	}
	if (node.count("scale")) {
		transform = true;
		Vector scale(node["scale"]);
		transformMat.scale(scale);
	}
	
	if (transform) {
		obj = ObjectPtr(new TransformedObject(obj, transformMat));
	}

// =============================================================================
// -- End of object reading ----------------------------------------------------
// =============================================================================

	// add object to the scene
    scene.addObject(obj);
    return true;
}

Light Raytracer::parseLightNode(json const &node) const
{
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const
{
    double ka = node["ka"];
    double kd = node["kd"];
    double ks = node["ks"];
    double n  = node["n"];
	if (node.count("color")) {
		Color color(node["color"]);
		return Material(color, ka, kd, ks, n);
	} else {
		string filename = path;
		filename += node["texture"];
		Image* image = new Image(filename);
		return Material(image, ka, kd, ks, n);
	}
}

bool Raytracer::readScene(string const &ifname)
try
{
    // Read and parse input json file
    ifstream infile(ifname);
    if (!infile) throw runtime_error("Could not open input file for reading.");
    json jsonscene;
    infile >> jsonscene;
	path = ifname;
	path.erase(path.begin() + path.find_last_of('/')+1, path.end());

// =============================================================================
// -- Read your scene data in this section -------------------------------------
// =============================================================================

    Point eye(jsonscene["Eye"]);
    scene.setEye(eye);

    // TODO: add your other configuration settings here
	
	if (!jsonscene["Shadows"].is_null()) {
		bool shadows(jsonscene["Shadows"]);
		scene.setShadows(shadows);
	}
	
	if (!jsonscene["MaxRecursionDepth"].is_null()) {
		int maxDepth(jsonscene["MaxRecursionDepth"]);
		scene.setMaxDepth(maxDepth);
	}
	
	if (!jsonscene["SuperSamplingFactor"].is_null()) {
		int sampleFactor(jsonscene["SuperSamplingFactor"]);
		scene.setSampleFactor(sampleFactor);
	}

    for (auto const &lightNode : jsonscene["Lights"])
        scene.addLight(parseLightNode(lightNode));

    unsigned objCount = 0;
    for (auto const &objectNode : jsonscene["Objects"])
        if (parseObjectNode(objectNode))
            ++objCount;

    cout << "Parsed " << objCount << " objects.\n";

// =============================================================================
// -- End of scene data reading ------------------------------------------------
// =============================================================================

    return true;
}
catch (exception const &ex)
{
    cerr << ex.what() << '\n';
    return false;
}

void Raytracer::renderToFile(string const &ofname)
{
    // TODO: the size may be a settings in your file
    Image img(400, 400);
    cout << "Tracing...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}
