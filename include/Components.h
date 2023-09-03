#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CTransform
{
public:
    Vec2 velocity = {0.0f, 0.0f};
    Vec2 pos= {0.0f, 0.0f};
    float angle = 0.0f;

    // Note: I'm passing in references here
    CTransform(Vec2 & p, Vec2 & v, float a)
        :pos(p), velocity(v), angle(a)
    {}

};

class CShape
{
public:
    sf::CircleShape circle;

    CShape(int radius, int points, const sf::Color & fill,
            const sf::Color & outline, float thickness)
        :circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOrigin(radius, radius);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
    }
};

class CCollision
{
public:
    float radius;
    CCollision(float r)
        :radius(r)
    {}
};

class CScore
{
public:
    int score;
    CScore(int s)
        :score(s)
    {}
};

class CLifespan
{
public:
    int remaining = 0;
    int total = 0;

    CLifespan(int t)
        :remaining(t), total(t)
    {}
};

class CInput
{
public:
    bool up    = false;
    bool down  = false;
    bool left  = false;
    bool right = false;

    CInput() {}
};
