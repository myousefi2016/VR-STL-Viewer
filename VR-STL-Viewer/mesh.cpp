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
    FILE* fp = fopen(filepath, "rb");

    unsigned long length = 256;

    unsigned char* buffer = new unsigned char[length];

    size_t read_length = fread(buffer, 1, length, fp);

    fclose(fp);

    size_t text_count = 0;

    const unsigned char* ptr = buffer;
    const unsigned char* buffer_end = buffer + read_length;

    while (ptr != buffer_end)
    {
        if ((*ptr >= 0x20 && *ptr <= 0x7F) || *ptr == '\n' || *ptr == '\r' || *ptr == '\t')
        {
            text_count++;
        }
        ptr++;
    }

    delete[] buffer;

    long double current_percent_bin = (static_cast<long double> (read_length - text_count) / static_cast<long double> (read_length));

    long double percent_bin = 0.05;

    if (current_percent_bin >= percent_bin)
    {
        STL_filetype = "binary";
    }
    else
    {
        STL_filetype = "ascii";
    }

    if (STL_filetype == "ascii")
    {
        readASCIISTLFile();
    }

    if (STL_filetype == "binary")
    {
        readBinarySTLFile();
    }

    if (STL_filetype != "ascii" && STL_filetype != "binary")
    {
        std::cout << "ERROR: Unable to find out whether the STL file is ascii or binary" << std::endl;
    }

    std::cout << "The number of triangles in the STL file = " << facets.size() << std::endl;

    this->createEdgesArray();
}

void Mesh::readBinarySTLFile()
{
    std::ifstream binaryInputFile;

    binaryInputFile.open(filepath, std::ifstream::in | std::ifstream::binary);

    if (binaryInputFile.fail())
    {
        std::cout << "ERROR: Input STL file could not be opened!" << std::endl;
    }

    binaryInputFile.seekg(80);

    int numberOfTriangles;
    binaryInputFile.read((char*)&numberOfTriangles, sizeof(int));

    triangle tri;

    vec3d foundPoint;

    char unused_bytes[2];

    long double temp_float_var;

    int id = -1;

    for (int count = 0; count < numberOfTriangles; count++)
    {
        binaryInputFile.read((char*)&temp_float_var, 4); tri.normal.x = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.normal.y = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.normal.z = (long double)temp_float_var;

        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[0].x = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[0].y = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[0].z = (long double)temp_float_var;

        auto it = points.find(tri.points[0]);
        if (it != points.end())
        {
            foundPoint = *it;
            tri.points[0].id = foundPoint.id;
        }
        else
        {
            id++;
            tri.points[0].id = id;
            points.insert(tri.points[0]);
        }

        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[1].x = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[1].y = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[1].z = (long double)temp_float_var;

        it = points.find(tri.points[1]);
        if (it != points.end())
        {
            foundPoint = *it;
            tri.points[1].id = foundPoint.id;
        }
        else
        {
            id++;
            tri.points[1].id = id;
            points.insert(tri.points[1]);
        }

        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[2].x = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[2].y = (long double)temp_float_var;
        binaryInputFile.read((char*)&temp_float_var, 4); tri.points[2].z = (long double)temp_float_var;

        if (it != points.end())
        {
            foundPoint = *it;
            tri.points[2].id = foundPoint.id;
        }
        else
        {
            id++;
            tri.points[2].id = id;
            points.insert(tri.points[2]);
        }

        tri.normalVectorCalculated = false;

        facets.insert(tri);

        binaryInputFile.read(unused_bytes, 2);
    }

    binaryInputFile.close();
}

void Mesh::readASCIISTLFile()
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

    vec3d foundPoint;

    int id = -1;

    getline(asciiInputFile, junk);

    while(true)
    {
        asciiInputFile >> string1 >> string2 >> tri.normal.x >> tri.normal.y >> tri.normal.z;
        getline(asciiInputFile,junk);

        getline(asciiInputFile,junk);

        asciiInputFile >> string1 >> tri.points[0].x >> tri.points[0].y >> tri.points[0].z;
        auto it = points.find(tri.points[0]);
        if (it != points.end())
        {
            foundPoint = *it;
            tri.points[0].id = foundPoint.id;
        }
        else
        {
            id++;
            tri.points[0].id = id;
            points.insert(tri.points[0]);
        }
        getline(asciiInputFile,junk);

        asciiInputFile >> string1 >> tri.points[1].x >> tri.points[1].y >> tri.points[1].z;
        it = points.find(tri.points[1]);
        if (it != points.end())
        {
            foundPoint = *it;
            tri.points[1].id = foundPoint.id;
        }
        else
        {
            id++;
            tri.points[1].id = id;
            points.insert(tri.points[1]);
        }
        getline(asciiInputFile,junk);

        asciiInputFile >> string1 >> tri.points[2].x >> tri.points[2].y >> tri.points[2].z;
        it = points.find(tri.points[2]);
        if (it != points.end())
        {
            foundPoint = *it;
            tri.points[2].id = foundPoint.id;
        }
        else
        {
            id++;
            tri.points[2].id = id;
            points.insert(tri.points[2]);
        }

        if (asciiInputFile.eof()) break;

        tri.normalVectorCalculated = false;

        facets.insert(tri);

        triangle_number++;

        getline(asciiInputFile,junk);

        getline(asciiInputFile,junk);

        getline(asciiInputFile,junk);
    }

    asciiInputFile.close();
}

void Mesh::createEdgesArray()
{
    std::unordered_set<edge>::iterator edgeIt;

    for (auto& tri : facets)
    {
        tri.edges[0].v1 = tri.points[0];
        tri.edges[0].v2 = tri.points[1];
        tri.edges[0].fIds.push_back(tri);

        edgeIt = edges.find(tri.edges[0]);

        if (edgeIt != edges.end())
        {
            const edge& foundEdge = *edgeIt;
            tri.edges[0].fIds.push_back(foundEdge.fIds[0]);
            foundEdge.fIds.push_back(tri);
        }
        else
        {
            edges.insert(tri.edges[0]);
        }

        tri.edges[1].v1 = tri.points[1];
        tri.edges[1].v2 = tri.points[2];
        tri.edges[1].fIds.push_back(tri);

        edgeIt = edges.find(tri.edges[1]);

        if (edgeIt != edges.end())
        {
            const edge& foundEdge = *edgeIt;
            tri.edges[1].fIds.push_back(foundEdge.fIds[0]);
            foundEdge.fIds.push_back(tri);
        }
        else
        {
            edges.insert(tri.edges[1]);
        }

        tri.edges[2].v1 = tri.points[2];
        tri.edges[2].v2 = tri.points[0];
        tri.edges[2].fIds.push_back(tri);

        edgeIt = edges.find(tri.edges[2]);

        if (edgeIt != edges.end())
        {
            const edge& foundEdge = *edgeIt;
            tri.edges[2].fIds.push_back(foundEdge.fIds[0]);
            foundEdge.fIds.push_back(tri);
        }
        else
        {
            edges.insert(tri.edges[2]);
        }
    }
}

bool Mesh::findNonManifoldEdges()
{
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
    triangle triPairs[2];
    edge ePairs[2];
    std::unordered_set<triangle>::iterator iterator;

    for(auto & e : edges)
    {
        if (e.fIds.size() == 2)
        {
            for (int it = 0; it < 2; it++)
            {
                triPairs[it] = e.fIds[it];

                for (int i = 0; i < 3; i++)
                {
                    if (triPairs[it].edges[i] == e)
                    {
                        ePairs[it] = triPairs[it].edges[i];
                    }
                }
            }

            if (!(ePairs[0] ^ ePairs[1]))
            {
                total++;
                ePairs[0] = -ePairs[0];
            }
            else
            {
                continue;
            }

            for (int it = 0; it < 2; it++)
            {
                iterator = facets.find(triPairs[it]);
                const triangle& foundTri = *iterator;
                if (!foundTri.normalVectorCalculated)
                {
                    vec3d a = ePairs[it].v2 - ePairs[it].v1;
                    vec3d p1;
                    vec3d p2;
                    for (int j = 0; j < 3; j++)
                    {
                        if (triPairs[it].points[j] == ePairs[it].v2)
                        {
                            if (j < 1)
                            {
                                p1 = triPairs[it].points[j];
                                p2 = triPairs[it].points[j + 1];
                            }
                            else
                            {
                                 p1 = triPairs[it].points[j];
                                 p2 = triPairs[it].points[0];
                            }
                        }
                    }
                    vec3d b = p2 - p1;
                    vec3d axb = a ^ b;
                    foundTri.normal = axb / axb.magnitude();
                    foundTri.normalVectorCalculated = true;
                }
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
