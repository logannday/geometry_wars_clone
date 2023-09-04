#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
    float x = 0;
    float y = 0;

    // Default Constructer intialized x and y to 0
    Vec2();
    
    // Constructer which allows specification
    Vec2(float xin, float yin);

    Vec2 operator + (const Vec2& rhs) const;

    void operator += (const Vec2& rhs);

    // add in place
    Vec2& add(const Vec2& rhs);

    bool operator == (const Vec2& rhs) const;

    bool operator != (const Vec2& rhs) const;

    Vec2 operator - (const Vec2& rhs) const;

    //scalar multiplication
    Vec2 operator * (float scalar) const;

    float length() const;

    void normalize();

    float distance(Vec2 & vec);
    
};

#endif
