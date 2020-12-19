#include "../include/Vector2D.hpp"


Vector2D::Vector2D() {
    this->x=0;
    this->y=0;
}

Vector2D::Vector2D(float x, float y) {
    this->x=x;
    this->y=y;
}

Vector2D Vector2D::copy() {
    Vector2D r(x,y);
    return r;
}

    
Vector2D& Vector2D::add(const Vector2D& v1) {
    this->x+=v1.x;
    this->y+=v1.y;

    return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& v1) {
    this->x-=v1.x;
    this->y-=v1.y;

    return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& v1) {
    this->x*=v1.x;
    this->y*=v1.y;

    return *this;
}

Vector2D& Vector2D::divide(const Vector2D& v1) {
    this->x/=v1.x;
    this->y/=v1.y;

    return *this;
}
Vector2D& operator+(Vector2D& v1,const Vector2D& v2) {
    return v1.add(v2);
}

Vector2D& operator-(Vector2D& v1,const Vector2D& v2) {
    return v1.subtract(v2);
}

Vector2D& operator*(Vector2D& v1,const Vector2D& v2) {
    return v1.multiply(v2);
}

Vector2D& operator/(Vector2D& v1,const Vector2D& v2) {
    return v1.divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& v1) {
    return this->add(v1);
}

Vector2D& Vector2D::operator-=(const Vector2D& v1) {
    return this->subtract(v1);
}

Vector2D& Vector2D::operator*=(const Vector2D& v1) {
    return this->multiply(v1);
}

Vector2D& Vector2D::operator/=(const Vector2D& v1) {
    return this->divide(v1);
}

Vector2D& Vector2D::operator*(const float& r) {
    this->x*=r;
    this->y*=r;

    return *this;
}

Vector2D& Vector2D::operator/(const float& r) {
    this->x/=r;
    this->y/=r;

    return *this;
}

Vector2D& Vector2D::zero() {
    this->x=0;
    this->y=0;
    return *this;
}

std::string Vector2D::toString() {
    std::string r = "("+std::to_string(x)+","+std::to_string(y)+")";
    return r;
}