#include "objloader.h"

// Pro C++ Tip: here you can specify other includes you may need
// such as <iostream>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>



using namespace std;

// ===================================================================
// -- Constructors and destructor ------------------------------------
// ===================================================================

// --- Public --------------------------------------------------------

OBJLoader::OBJLoader(string const &filename)
:
    d_hasTexCoords(false)
{
    parseFile(filename);
}

// ===================================================================
// -- Member functions -----------------------------------------------
// ===================================================================

// --- Public --------------------------------------------------------

vector<Vertex> OBJLoader::vertex_data() const
{
    vector<Vertex> data;

    // For all vertices in the model, interleave the data
    for (Vertex_idx const &vertex : d_vertices)
    {
        // Add coordinate data
        Vertex vert;

        vec3 const coord = d_coordinates.at(vertex.d_coord);
        vert.x = coord.x;
        vert.y = coord.y;
        vert.z = coord.z;

        // Add normal data
        vec3 const norm = d_normals.at(vertex.d_norm);
        vert.nx = norm.x;
        vert.ny = norm.y;
        vert.nz = norm.z;

        // Add texture data (if available)
        if (d_hasTexCoords)
        {
            vec2 const tex = d_texCoords.at(vertex.d_tex);
            vert.u = tex.u;      // u coordinate
            vert.v = tex.v;      // v coordinate
        } else {
            vert.u = 0;
            vert.v = 0;
        }
        data.push_back(vert);
    }
    return data;    // copy elision
}

unsigned OBJLoader::numTriangles() const
{
    return d_vertices.size() / 3U;
}

bool OBJLoader::hasTexCoords() const
{
    return d_hasTexCoords;
}

vector<Vertex> OBJLoader::unitize(vector<Vertex> verts)
{
	vector<Vertex> data;
    float max;
    for (unsigned i = 0; i < verts.size(); i++) {
        if (fabs(verts[i].x) > max) {
            max = fabs(verts[i].x);
        }
        if (fabs(verts[i].y) > max) {
            max = fabs(verts[i].y);
        }
        if (fabs(verts[i].z) > max) {
            max = fabs(verts[i].z);
        }
    }
    for (unsigned i = 0; i < verts.size(); i++) {
		Vertex vert;
		
        vert.x = verts[i].x / max;
        vert.y = verts[i].y / max;
        vert.z = verts[i].z / max;
        
        vert.nx = verts[i].nx;
        vert.ny = verts[i].ny;
        vert.nz = verts[i].nz;
        
        vert.u = verts[i].u;      
        vert.v = verts[i].v; 
        
        data.push_back(vert);  
    }
    return data;
}

vector<Vertex> OBJLoader::scale(double factor, std::vector<Vertex> verts)
{
	vector<Vertex> data;
	for (unsigned i = 0; i < verts.size(); i++) {
		Vertex vert;
		
        vert.x = verts[i].x * factor;
        vert.y = verts[i].y * factor;
        vert.z = verts[i].z * factor;
        
        vert.nx = verts[i].nx;
        vert.ny = verts[i].ny;
        vert.nz = verts[i].nz;
        
        vert.u = verts[i].u;      
        vert.v = verts[i].v; 
        
        data.push_back(vert);
    }
    return data;
}

vector<Vertex> OBJLoader::translate(Vector translation, std::vector<Vertex> verts)
{
	vector<Vertex> data;
	for (unsigned i = 0; i < verts.size(); i++) {
		Vertex vert;
		
        vert.x = verts[i].x + translation.x;
        vert.y = verts[i].y + translation.y;
        vert.z = verts[i].z + translation.z;
        
        vert.nx = verts[i].nx;
        vert.ny = verts[i].ny;
        vert.nz = verts[i].nz;
        
        vert.u = verts[i].u;      
        vert.v = verts[i].v; 
        
        data.push_back(vert);
    }
    return data;
}

// --- Private -------------------------------------------------------

void OBJLoader::parseFile(string const &filename)
{
    ifstream file(filename);
    if (file)
    {
        string line;
        while(getline(file, line))
            parseLine(line);

    } else {
        cerr << "Could not open: " << filename << " for reading!\n";
    }
}

void OBJLoader::parseLine(string const &line)
{
    if (line[0] == '#')
        return;                     // ignore comments

    StringList tokens = split(line, ' ', false);

    if (tokens[0] == "v")
        parseVertex(tokens);
    else if (tokens[0] == "vn")
        parseNormal(tokens);
    else if (tokens[0] == "vt")
        parseTexCoord(tokens);
    else if (tokens[0] == "f")
        parseFace(tokens);

    // Other data is also ignored
}

void OBJLoader::parseVertex(StringList const &tokens)
{
    float x, y, z;
    x = stof(tokens.at(1));         // 0 is the "v" token
    y = stof(tokens.at(2));
    z = stof(tokens.at(3));
    d_coordinates.push_back(vec3{x, y, z});
}

void OBJLoader::parseNormal(StringList const &tokens)
{
    float x, y, z;
    x = stof(tokens.at(1));         // 0 is the "vn" token
    y = stof(tokens.at(2));
    z = stof(tokens.at(3));
    d_normals.push_back(vec3{x, y, z});
}

void OBJLoader::parseTexCoord(StringList const &tokens)
{
    d_hasTexCoords = true;          // Texture data will be read

    float u, v;
    u = stof(tokens.at(1));         // 0 is the "vt" token
    v = stof(tokens.at(2));
    d_texCoords.push_back(vec2{u, v});
}

void OBJLoader::parseFace(StringList const &tokens)
{
    // skip the first token ("f")
    for (size_t idx = 1; idx < tokens.size(); ++idx)
    {
        // format is:
        // <vertex idx + 1>/<texture idx +1>/<normal idx + 1>
        // Wavefront .obj files start counting from 1 (yuck)

        StringList elements = split(tokens.at(idx), '/');
        Vertex_idx vertex {}; // initialize to zeros on all fields

        vertex.d_coord = stoul(elements.at(0)) - 1U;

        if (d_hasTexCoords)
            vertex.d_tex = stoul(elements.at(1)) - 1U;
        else
            vertex.d_tex = 0U;       // ignored

        vertex.d_norm = stoul(elements.at(2)) - 1U;

        d_vertices.push_back(vertex);
    }
}

OBJLoader::StringList OBJLoader::split(string const &line,
                            char splitChar,
                            bool keepEmpty)
{
    StringList tokens;
    istringstream iss(line);
    string token;
    while (getline(iss, token, splitChar))
        if (token.size() > 0 || (token.size() == 0 && keepEmpty))
            tokens.push_back(token);

    return tokens;
}
