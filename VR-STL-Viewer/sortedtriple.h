#ifndef SORTEDTRIPLE_H
#define SORTEDTRIPLE_H

#include <algorithm>
#include "utilities.h"

class SortedTriple
{
public:
    SortedTriple() {}
    SortedTriple(unsigned int v0, unsigned int v1, unsigned int v2,triangle* _fp)
    {
        v[0]=v0;v[1]=v1;v[2]=v2;
        fp=_fp;
        std::sort(v,v+3);
    }
    bool operator < (const SortedTriple &p) const
    {
        return (v[2]!=p.v[2])?(v[2]<p.v[2]):
            (v[1]!=p.v[1])?(v[1]<p.v[1]):
                (v[0]<p.v[0]);				}

        bool operator == (const SortedTriple &s) const
        {
        if( (v[0]==s.v[0]) && (v[1]==s.v[1]) && (v[2]==s.v[2]) ) return true;
        return false;
    }

    unsigned int v[3];
    triangle* fp;
};

#endif // SORTEDTRIPLE_H
