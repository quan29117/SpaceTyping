#pragma once

#include <iostream>
#include <cmath>

struct Vector2D {
    float x, y;

    Vector2D();
    Vector2D(const float& x, const float& y);

    Vector2D& operator = (const Vector2D& v);

    friend Vector2D operator + (const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator - (const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator * (const Vector2D& v1, const Vector2D& v2);
    friend Vector2D operator / (const Vector2D& v1, const Vector2D& v2);

    Vector2D& operator += (const Vector2D& v);
    Vector2D& operator -= (const Vector2D& v);
    Vector2D& operator *= (const Vector2D& v);
    Vector2D& operator /= (const Vector2D& v);

    friend std::ostream& operator << (std::ostream& stream, const Vector2D& v);

    Vector2D unitVector();
};