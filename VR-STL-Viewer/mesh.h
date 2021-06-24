#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <cmath>
#include "utilities.h"
#include "vtkByteSwap.h"

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

    const char* GetFilePathCleaned()
    {
        return filepathcleaned;
    }

    std::unordered_set<triangle> GetFacets()
    {
        return facets;
    }

    std::unordered_set<vec3d> GetPoints()
    {
        return points;
    }

    std::unordered_set<edge> GetEdges()
    {
        return uniqEdges;
    }

    void readSTLFile();
    void writeSTLFile();
    bool findNonManifoldEdges();
    bool findFlippedTriangles();
private:
    void readASCIISTLFile();
    void readBinarySTLFile();
    void writeASCIISTLFile();
    void writeBinarySTLFile();
    void createEdgesArray();
    const char* filepath;
    const char* filepathcleaned;
    std::string STL_filetype;
    std::unordered_set<triangle> facets;
    std::unordered_set<vec3d> points;
    std::set<edge> edges;
    std::unordered_set<edge> uniqEdges;
    const char STLWriterDefaultHeader[81] = "3D mesh cleaner and VR STL viewer generated SLA File (Mehrdad Yousefi,June 2021)";
    static const int STLWriterBinaryHeaderSize = 80;
};

#endif // MESH_H
