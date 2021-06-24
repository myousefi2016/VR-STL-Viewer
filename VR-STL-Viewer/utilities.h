#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>
#include <tuple>


#define assertm(exp, msg) assert(((void)msg, exp))

struct hashTable 
{
    static const size_t HASH_TABLE_SIZE = 1000000;
    static const size_t p1 = 73856093;
    static const size_t p2 = 19349663;
    static const size_t p3 = 83492791;
};

struct vec3d
{
    float x;

    float y;

    float z;

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

     float operator * (const vec3d &s) const
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

     vec3d operator / (const float ratio) const
     {
         vec3d r;
         r.x = x / ratio;
         r.y = y / ratio;
         r.z = z / ratio;
         return r;
     }

     void operator << (const vec3d& s) const
     {
         std::cout << s.x << "," << s.y << "," << s.z << std::endl;
     }

     float magnitude() const
     {
         float m = std::sqrt(x * x + y * y + z * z);
         return m;
     }

     size_t operator ()(const vec3d &k) const 
     {
         size_t h1 = std::hash<float>()(k.x);
         size_t h2 = std::hash<float>()(k.y);
         size_t h3 = std::hash<float>()(k.z);
         return ((h1 * hashTable::p1) ^ (h2 * hashTable::p2) ^ (h2 * hashTable::p3)) % hashTable::HASH_TABLE_SIZE;
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
}

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
        assert(*this == e);

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

    bool operator < (const edge& e) const
    {
        if (!(*this == e))
        {
            std::tuple<int, int> lhs = std::make_tuple(v1.id, v2.id);
            std::tuple<int, int> rhs = std::make_tuple(e.v1.id, e.v2.id);

            return lhs < rhs;
        }
        else
        {
            return false;
        }
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
        size_t h1 = std::hash<vec3d>()(e.v1);
        size_t h2 = std::hash<vec3d>()(e.v2);
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
        size_t h1 = std::hash<vec3d>()(t.points[0]);
        size_t h2 = std::hash<vec3d>()(t.points[1]);
        size_t h3 = std::hash<vec3d>()(t.points[2]);
        return h1 ^ h2 ^ h3;
    }
};

namespace std {
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
