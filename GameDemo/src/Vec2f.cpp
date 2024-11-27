#include "Vec2f.h"

#include "math.h"

Vec2f::Vec2f(const float _x, const float _y)
{
    x = _x;
    y = _y;
}

Vec2f::~Vec2f()
{
    //dtor
}

Vec2f Vec2f::operator+(const Vec2f &a)
{
    Vec2f result;

    result.x = x + a.x;
    result.y = y + a.y;

    return result;
}

Vec2f Vec2f::operator+=(const Vec2f &a)
{
    Vec2f result;

    x += a.x;
    y += a.y;

    return *this;
}

Vec2f Vec2f::operator-()
{
    Vec2f result;

    result.x = -x;
    result.y = -y;

    return result;
}

Vec2f Vec2f::operator-(const Vec2f& a)
{
    Vec2f   result;

    result.x = x - a.x;
    result.y = y - a.y;

    return result;
}

//Vec2f &Vec2f::operator-=(const Vec2f& a)
//{
//    x -= a.x;
//    y -= a.y;
//    return *this;
//}

float Vec2f::squaredMag()
{
    return x * x + y * y;
}

float Vec2f::mag()
{
    return sqrt(squaredMag());
}

float Vec2f::arg()
{
    return atan2(y, x);
}
