#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
    delete[] filepath;
}

void Mesh::readSTLFile()
{
    std::ifstream asciiInputFile;

    asciiInputFile.open(filepath, std::ifstream::in);

    if(asciiInputFile.fail())
    {
        std::cout << "ERROR: Input STL file could not be opened!" << std::endl;
        return;
    }

    int triangle_number = 0;

    triangle tri;

    std::string junk;
    std::string string1,string2;

    getline(asciiInputFile,junk);

    int id = -1;

    while(true)
    {
        asciiInputFile >> string1 >> string2 >> tri.normal.x >> tri.normal.y >> tri.normal.z;
        getline(asciiInputFile,junk);

        getline(asciiInputFile,junk);

        asciiInputFile >> string1 >> tri.point[0].x >> tri.point[0].y >> tri.point[0].z;
        __int64 index;
        auto it = std::find(points.begin(), points.end(), tri.point[0]);
        if (it != points.end())
        {
            index = it - points.begin();
            tri.point[0].id = points[index].id;
        }
        else
        {
            id++;
            tri.point[0].id = id;
            points.push_back(tri.point[0]);
        }
        getline(asciiInputFile,junk);

        asciiInputFile >> string1 >> tri.point[1].x >> tri.point[1].y >> tri.point[1].z;
        it = std::find(points.begin(), points.end(), tri.point[1]);
        if (it != points.end())
        {
            index = it - points.begin();
            tri.point[1].id = points[index].id;
        }
        else
        {
            id++;
            tri.point[1].id = id;
            points.push_back(tri.point[1]);
        }
        getline(asciiInputFile,junk);

        asciiInputFile >> string1 >> tri.point[2].x >> tri.point[2].y >> tri.point[2].z;
        it = std::find(points.begin(), points.end(), tri.point[2]);
        if (it != points.end())
        {
            index = it - points.begin();
            tri.point[2].id = points[index].id;
        }
        else
        {
            id++;
            tri.point[2].id = id;
            points.push_back(tri.point[2]);
        }
        getline(asciiInputFile,junk);

        getline(asciiInputFile,junk);
        getline(asciiInputFile,junk);

        if (asciiInputFile.eof()) break;

        triangle_number++;

        facet.push_back(tri);
    }

    asciiInputFile.close();

    return;
}

void Mesh::createEdgesArray()
{
    int triId = 0;
    std::vector<edge>::iterator it;
    __int64 index;

    for(auto & tri : cleanedFacet)
    {
        tri.edges[0].v1 = tri.point[0].id;
        tri.edges[0].v2 = tri.point[1].id;
        tri.edges[0].fIds.push_back(triId);

        it = std::find(edges.begin(), edges.end(), tri.edges[0]);

        if(it != edges.end())
        {
            index = it - edges.begin();
            tri.edges[0].fIds.push_back(edges[index].fIds[0]);
            edges[index].fIds.push_back(triId);
        }
        else
        {
            edges.push_back(tri.edges[0]);
        }

        tri.edges[1].v1 = tri.point[1].id;
        tri.edges[1].v2 = tri.point[2].id;
        tri.edges[1].fIds.push_back(triId);

        it = std::find(edges.begin(), edges.end(), tri.edges[1]);

        if(it != edges.end())
        {
            index = it - edges.begin();
            tri.edges[1].fIds.push_back(edges[index].fIds[0]);
            edges[index].fIds.push_back(triId);
        }
        else
        {
            edges.push_back(tri.edges[1]);
        }

        tri.edges[2].v1 = tri.point[2].id;
        tri.edges[2].v2 = tri.point[0].id;
        tri.edges[2].fIds.push_back(triId);

        it = std::find(edges.begin(), edges.end(), tri.edges[2]);

        if(it != edges.end())
        {
            index = it - edges.begin();
            tri.edges[2].fIds.push_back(edges[index].fIds[0]);
            edges[index].fIds.push_back(triId);
        }
        else
        {
            edges.push_back(tri.edges[2]);
        }

        triId++;
    }
}

bool Mesh::findDuplicateTriangles()
{
    std::vector<SortedTriple> fvec;

    for(auto & tri : facet)
    {
        fvec.push_back(SortedTriple(    tri.point[0].id,
                                        tri.point[1].id,
                                        tri.point[2].id,
                                        &tri));
    }
    std::sort(fvec.begin(),fvec.end());
    int total=0;
    for(int i=0; i< fvec.size()-1; ++i)
    {
        if(fvec[i]==fvec[i+1])
        {
            total++;
        }
        else
        {
            cleanedFacet.push_back(*fvec[i].fp);
        }
    }

    if (total == 0)
    {
        cleanedFacet.push_back(*fvec[fvec.size()-1].fp);
    }

    if (total > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Mesh::findNonManifoldEdges()
{
    Mesh::createEdgesArray();

    int total=0;
    for(auto &e : edges)
    {
        if (e.fIds.size() != 2)
        {
            total++;
        }
    }

    if (total > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Mesh::findFlippedTriangles()
{
    int total = 0;
    double dotProduct = -1.0;

    for(auto & e : edges)
    {
        if (e.fIds.size() == 2)
        {
            vec3d normal1 = cleanedFacet[e.fIds[0]].normal;
            vec3d normal2 = cleanedFacet[e.fIds[1]].normal;

            dotProduct = normal1 * normal2;

            if (dotProduct >= 0 )
            {
                continue;
            }
            else
            {
                total++;
                cleanedFacet[e.fIds[1]].normal = -normal2;
            }
        }
    }

    if (total > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
