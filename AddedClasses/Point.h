#pragma once
#include <cmath>
#include "Constants.h"

class Point
{
public:
    using value_type = double;
    
    Point ()
        : _x(0)
        , _y(0)
        , _z(0) 
    {}
    
    Point (value_type x, value_type y, value_type z)
        : _x(x)
        , _y(y)
        , _z(z) 
    {}
    
    value_type x () const { return _x; }
    value_type y () const { return _y; }
    value_type z () const { return _z; }
    
private:
    value_type _x;
    value_type _y;
    value_type _z;
};

inline typename Point::value_type distance (Point const & a, Point const & b)
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x())
            + (a.y() - b.y()) * (a.y() - b.y())
            + (a.z() - b.z()) * (a.z() - b.z())); 
}

inline bool operator == (Point const & a, Point const & b)
{
    return distance(a, b) < EPSILON; 
} 
