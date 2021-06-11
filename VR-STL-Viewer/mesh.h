#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include "utilities.h"
#include "sortedtriple.h"

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

    void readSTLFile();
    void createEdgesArray();
    bool findDuplicateTriangles();
    bool findNonManifoldEdges();
    bool findFlippedTriangles();
private:
    const char* filepath;
    std::vector<triangle> facet;
    std::vector<triangle> cleanedFacet;
    std::vector<vec3d> points;
    std::vector<edge> edges;
};

#endif // MESH_H
