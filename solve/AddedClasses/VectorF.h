#pragma once
#include <cmath>
#include "Constants.h"
#include "../model/Action.h"

class VectorF;
inline VectorF operator / (const VectorF & a, double v);
inline VectorF operator - (const VectorF & a, const VectorF & b);
inline VectorF operator * (const VectorF & a, double v);

class VectorF
{
public:
    using value_type = double;
    
    VectorF ()
        : _x(0)
        , _y(0)
        , _z(0) 
    {}
    
    VectorF (value_type x, value_type y, value_type z)
        : _x(x)
        , _y(y)
        , _z(z) 
    {}
    
    VectorF (const Point & p)
        : _x(p.x())
        , _y(p.y())
        , _z(p.z()) 
    {}

        
    VectorF (const Point & a, const Point & b)
    {
        *this = VectorF(b) - VectorF(a);
    }

    
    double Length() const
    {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }
    
    VectorF Normalize () const
    {
        if (this->Length() >= EPSILON)
            return *this / this->Length();
        else
            return *this;
    }
    
    VectorF ToLength (double len) const
    {        
        return this->Normalize() * len;
    }
    
    void SetX(double x)
    {
        _x = x;
    }

    void SetY(double y)
    {
        _y = y;
    }
    
    void SetZ(double z)
    {
        _z = z;
    }
    
    value_type x () const { return _x; }
    value_type y () const { return _y; }
    value_type z () const { return _z; }
    
private:
    value_type _x;
    value_type _y;
    value_type _z;
};

inline bool Collinearity(const VectorF & a, const VectorF & b)
{
    return abs(a.x() * b.z() - a.z() * b.x()) < EPSILON;
}

inline VectorF operator * (const VectorF & a, double v)
{
    return VectorF(a.x() * v, a.y() * v, a.z() * v);
}

inline VectorF operator * (double v, const VectorF & a)
{
    return VectorF(a.x() * v, a.y() * v, a.z() * v);
}

inline VectorF operator / (const VectorF & a, double v)
{
    return VectorF(a.x() / v, a.y() / v, a.z() / v);
}

inline VectorF operator + (const VectorF & a, const VectorF & b)
{
    return VectorF(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

inline VectorF operator - (const VectorF & a, const VectorF & b)
{
    return VectorF(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

inline VectorF VectorFToLength(const VectorF & a, double v)
{
    return VectorF(a.x(), a.y(), a.z()).Normalize() * v;
}

inline double DotProduct (const VectorF & a, const VectorF & b)
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

inline VectorF CrossProduct (const VectorF & a, const VectorF & b)
{
    return VectorF(a.y() * b.z() - a.z() * b.y(), a.z() * b.x() - a.x() * b.z(), a.x() * b.y() - a.y() * b.x());
}

inline double TripleProduct (const VectorF & a, const VectorF & b, const VectorF & c)
{
    return DotProduct(CrossProduct(a, b), c);
}

inline Point operator + (Point const & a, VectorF const & b)
{
    return Point(a.x() + b.x(), a.y() + b.y(), a.z() + b.z()); 
}

inline Point operator + (VectorF const & a, Point const & b)
{
    return b + a;
} 

inline Point operator - (Point const & a, VectorF const & b)
{
    return Point(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); 
}

void AddVectorToAction (model::Action & act, VectorF d)
{
    act.target_velocity_x += d.x();
    act.target_velocity_y += d.y();
    act.target_velocity_z += d.z();
}
