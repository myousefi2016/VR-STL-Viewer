#ifndef UTILITIES_H
#define UTILITIES_H

#include<vector>
#include <algorithm>
#include <cmath>
#include <iostream>

struct vec3d
{
    long double x;

    long double y;

    long double z;

    mutable int id;

     bool operator == (const vec3d &s) const
     {
        if((x == s.x) && (y == s.y) && (z == s.z)) return true;
        return false;
     }

     vec3d& operator = (const vec3d& s)
     {
         x = s.x;
         y = s.y;
         z = s.z;
         id = s.id;
         return *this;
     }

     double operator * (const vec3d &s) const
     {
         return (x*s.x+y*s.y+z*s.z);
     }

     vec3d operator ^ (const vec3d &s) const
     {
         vec3d cp;
         cp.x = y * s.z - z * s.y;
         cp.y = z * s.x - x * s.z;
         cp.z = x * s.y - y * s.x;

         return cp;
     }

     vec3d operator - () const
     {
         vec3d n;
         n.x = -x;
         n.y = -y;
         n.z = -z;

         return n;
     }

     vec3d operator - (const vec3d& s) const
     {
         vec3d r;
         r.x = x - s.x;
         r.y = y - s.y;
         r.z = z - s.z;
         
         return r;
     }

     vec3d operator + (const vec3d& s) const
     {
         vec3d r;
         r.x = x + s.x;
         r.y = y + s.y;
         r.z = z + s.z;

         return r;
     }

     vec3d operator / (const long double ratio) const
     {
         vec3d r;
         r.x = x / ratio;
         r.y = y / ratio;
         r.z = z / ratio;
         return r;
     }

     double magnitude() const
     {
         double m = std::sqrt(x * x + y * y + z * z);
         return m;
     }

     size_t operator ()(const vec3d &k) const 
     {
         size_t h1 = std::hash<long double>()(k.x);
         size_t h2 = std::hash<long double>()(k.y);
         size_t h3 = std::hash<long double>()(k.z);
         return (h1 ^ (h2 << 1)) ^ h3;
     }
};

class triangle;

class edge
{
public:
    vec3d v1;

    vec3d v2;

    mutable std::vector<triangle> fIds;

    edge operator - () const
    {
        edge r;
        r.v1 = v2;
        r.v2 = v1;
        r.fIds = fIds;
        return r;
    }

    bool operator ^ (const edge& e) const
    {
        if ((v1 == e.v1) && (v2 == e.v2))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool operator == (const edge& e) const
    {
        if (((v1 == e.v1) && (v2 == e.v2)) || ((v1 == e.v2) && (v2 == e.v1))) return true;
        return false;
    }

    edge& operator = (const edge& e)
    {
        v1 = e.v1;
        v2 = e.v2;
        fIds = e.fIds;
        return *this;
    }

    size_t operator ()(const edge& e) const
    {
        size_t h1 = std::hash<int>()(e.v1.id);
        size_t h2 = std::hash<int>()(e.v2.id);
        return h1 ^ h2;
    }
};

class triangle
{
public:
    mutable vec3d normal;

    vec3d points[3];

    mutable edge edges[3];

    mutable bool normalVectorCalculated;

    bool operator == (const triangle& t) const
    {
        if (   ((points[0] == t.points[0]) && (points[1] == t.points[1]) && (points[2] == t.points[2]))
            || ((points[0] == t.points[0]) && (points[1] == t.points[2]) && (points[2] == t.points[1]))
            || ((points[0] == t.points[1]) && (points[1] == t.points[2]) && (points[2] == t.points[0]))
            || ((points[0] == t.points[1]) && (points[1] == t.points[0]) && (points[2] == t.points[2]))
            || ((points[0] == t.points[2]) && (points[1] == t.points[0]) && (points[2] == t.points[1]))
            || ((points[0] == t.points[2]) && (points[1] == t.points[1]) && (points[2] == t.points[0])))return true;
            return false;
    }

    triangle& operator = (const triangle& t)
    {
        normal = t.normal;
        points[0] = t.points[0];
        points[1] = t.points[1];
        points[2] = t.points[2];
        edges[0] = t.edges[0];
        edges[1] = t.edges[1];
        edges[2] = t.edges[2];
        return *this;
    }

    size_t operator ()(const triangle& t) const
    {
        size_t h1 = std::hash<long double>()(t.points[0].x);
        size_t h2 = std::hash<long double>()(t.points[0].y);
        size_t h3 = std::hash<long double>()(t.points[0].z);
        size_t h4 = std::hash<long double>()(t.points[1].x);
        size_t h5 = std::hash<long double>()(t.points[1].y);
        size_t h6 = std::hash<long double>()(t.points[1].z);
        size_t h7 = std::hash<long double>()(t.points[2].x);
        size_t h8 = std::hash<long double>()(t.points[2].y);
        size_t h9 = std::hash<long double>()(t.points[2].z);
        return ((h1 ^ (h2 << 1)) ^ h3) ^ ((h4 ^ (h5 << 1)) ^ h6) ^ ((h7 ^ (h8 << 1)) ^ h9);
    }
};

namespace std {
    template<> struct hash<vec3d>
    {
        std::size_t operator()(const vec3d& p) const
        {
            return p(p);
        }
    };

    template<> struct hash<edge>
    {
        std::size_t operator()(const edge& e) const
        {
            return e(e);
        }
    };

    template<> struct hash<triangle>
    {
        std::size_t operator()(const triangle& t) const
        {
            return t(t);
        }
    };
}

#endif // UTILITIES_H
