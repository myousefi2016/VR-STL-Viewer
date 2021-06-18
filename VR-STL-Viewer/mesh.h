#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include "utilities.h"

class Mesh
{
public:

    Mesh();
    ~Mesh();

    const char* GetFilePath()
    {
        return filepath;
    }

    void SetFilePath(const char* fp)
    {
        filepath = fp;
    }

    void readASCIISTLFile();
    void readBinarySTLFile();
    void readSTLFile();
    void createEdgesArray();
    bool findNonManifoldEdges();
    bool findFlippedTriangles();
private:
    const char* filepath;
    std::string STL_filetype;
    std::unordered_set<triangle> facets;
    std::unordered_set<vec3d> points;
    std::unordered_set<edge> edges;
};

#endif // MESH_H
