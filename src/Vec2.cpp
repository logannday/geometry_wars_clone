#include <iostream>
#include <cmath>
#include "Vec2.h"

Vec2::Vec2() 
{}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

void Vec2::operator += (const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

Vec2& Vec2::add(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

bool Vec2::operator == (const Vec2& rhs) const
{
    return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
    return (x != rhs.x || y != rhs.y);
}

Vec2 Vec2::operator * (float scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

float Vec2::length() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Vec2::normalize()
{
    float l = length();
    x = x / l;
    y = y / l;
}
