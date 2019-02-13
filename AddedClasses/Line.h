#pragma once
#include <cmath>
#include "Constants.h"
#include "Point.h"
#include "VectorF.h"

class Line
{
public:
    using value_type = double;
    
    Line ()
        : _ax(1)
        , _ay(1)
        , _az(1)
        , _bx(0)
        , _by(0)
        , _bz(0)
        
    {}
    
    Line (const Point & a, const VectorF & d)
        : _ax(d.x())
        , _ay(d.y())
        , _az(d.z())
        , _bx(a.x())
        , _by(a.y())
        , _bz(a.z())
    {}
    
    Line (const Point & a, const Point & b)
    {
        VectorF dir = VectorF(a, b).Normalize();
        *this = Line(a, dir);
    }
    
    VectorF directionVector() const
    {
        return VectorF(_ax, _ay, _az).Normalize();
    }
    
    Point GetPoint(double t) const
    {
        return Point(_ax * t + _bx, _ay * t + _by, _az * t + _bz);
    }
    
    value_type ax () const { return _ax; }
    value_type ay () const { return _ay; }
    value_type az () const { return _az; }
    value_type bx () const { return _bx; }
    value_type by () const { return _by; }
    value_type bz () const { return _bz; }
private:
    value_type _ax;
    value_type _ay;
    value_type _az;
    value_type _bx;
    value_type _by;
    value_type _bz;
};

std::pair<double, double> GetAtBt(double a1x, double b1x, double a2x, double b2x)
{
    double at = a2x / a1x;
    double bt = (b2x - b1x) / a1x;
    return std::make_pair(at, bt);
}

bool LineIntersection(const Line & l1, const Line & l2, Point & result)
{
    VectorF v1 = l1.directionVector();
    VectorF v2 = l2.directionVector();
    if (Collinearity(v1, v2))
        return false;
    double at, bt, t;
    if (abs(l1.ax()) >= EPSILON)
    {
        std::pair<double, double> temp = GetAtBt(l1.ax(), l1.bx(), l2.ax(), l2.bx());
        at = temp.first;
        bt = temp.second;
    } 
    else if (abs(l1.ay()) >= EPSILON)
    {
        std::pair<double, double> temp = GetAtBt(l1.ay(), l1.by(), l2.ay(), l2.by());
        at = temp.first;
        bt = temp.second;
    } 
    else 
    {
        std::pair<double, double> temp = GetAtBt(l1.az(), l1.bz(), l2.az(), l2.bz());
        at = temp.first;
        bt = temp.second;
    }
    if (abs(l1.ax() * at - l2.ax()) >= EPSILON)
        t = (l2.bx() - bt * l1.ax() - l1.bx()) / (l1.ax() * at - l2.ax());
    else if (abs(l1.ay() * at - l2.ay()) >= EPSILON)
        t = (l2.by() - bt * l1.ay() - l1.by()) / (l1.ay() * at - l2.ay());
    else
        t = (l2.bz() - bt * l1.az() - l1.bz()) / (l1.az() * at - l2.az());
    result = l2.GetPoint(t);
    return true;
}

bool InSegment(const Point & p1, const Point & p2, const Line & l, const Point & p)
{
    double d1 = distance(p1, p);
    double d2 = distance(p2, p);
    double d12 = distance(p1, p2);
    return abs(d1 + d2 - d12) <= EPSILON;
}
