#include <headers/Vector2D.hpp>

Vector2D::Vector2D() {
    x = y = 0.f;
}

Vector2D::Vector2D(const float& x, const float& y) {
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::operator = (const Vector2D& v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector2D operator + (const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator - (const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator * (const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x * v2.x, v1.y * v2.y);
}

Vector2D operator / (const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x / v2.x, v1.y / v2.y);
}

Vector2D& Vector2D::operator += (const Vector2D& v) {
    this->x += v.x;
    this->y += v.y;

    return *this;
}

Vector2D& Vector2D::operator -= (const Vector2D& v) {
    this->x -= v.x;
    this->y -= v.y;

    return *this;
}

Vector2D& Vector2D::operator *= (const Vector2D& v) {
    this->x *= v.x;
    this->y *= v.y;

    return *this;
}

Vector2D& Vector2D::operator /= (const Vector2D& v) {
    this->x /= v.x;
    this->y /= v.y;

    return *this;
}

std::ostream& operator << (std::ostream& stream, const Vector2D& v) {
    stream  << "(" << v.x << ", " << v.y << ")";
    return stream;
}

Vector2D Vector2D::unitVector() {
    float l = sqrt(x * x + y * y);
    return Vector2D(x / l, y / l);
}






