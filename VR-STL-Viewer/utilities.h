#ifndef UTILITIES_H
#define UTILITIES_H

#include<vector>

struct vec3d
{
    double x;

    double y;

    double z;

    int id;

     bool operator == (const vec3d &s) const
     {
        if((x==s.x) && (y==s.y) && (z==s.z)) return true;
        return false;
     }

     double operator * (const vec3d &s) const
     {
         return (x*s.x+y*s.y+z*s.z);
     }

     vec3d operator - () const
     {
         vec3d n;
         n.x = -x;
         n.y = -y;
         n.z = -z;

         return n;
     }
};

struct edge
{
    int v1;

    int v2;

    int id;

    std::vector<int> fIds;

    bool operator == (const edge &e) const
    {
       if(((v1==e.v1) && (v2==e.v2)) || ((v1==e.v2) && (v2==e.v1))) return true;
       return false;
    }
};

class triangle
{
public:

    vec3d normal;

    vec3d point[3];

    edge edges[3];
};

#endif // UTILITIES_H
