#include "Rect.h"
namespace Framework {
namespace Math {

Rect::Rect()
    :x(0.0f), y(0.0f), width(1.0f), height(1.0f) {}

Rect::Rect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

Rect::Rect(const Vector2& center, const Vector2& size)
    : x(center.x - size.x * 0.5f), y(center.y - size.y * 0.5f), width(size.x), height(size.y) {}

Rect::~Rect() {}

float Rect::getX() const {
    return x;
}

void Rect::setX(float x) {
    this->x = x;
}

float Rect::getY() const {
    return y;
}
void Rect::setY(float y) {
    this->y = y;
}

Vector2 Rect::getPosition() const {
    return Vector2(x, y);
}

void Rect::setPosition(const Vector2& position) {
    x = position.x;
    y = position.y;
}

void Rect::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

float Rect::getWidth() const {
    return width;
}

void Rect::setWidth(float width) {
    this->width = width;
}

float Rect::getHeight() const {
    return height;
}
void Rect::setHeight(float height) {
    this->height = height;
}

Vector2 Rect::getSize() const {
    return Vector2(width, height);
}

void Rect::setSize(const Vector2& size) {
    width = size.x;
    height = size.y;
}

void Rect::setSize(float width, float height) {
    this->width = width;
    this->height = height;
}

float Rect::getXMin() const {
    return x;
}
void Rect::setXMin(float xmin) {
    width += x - xmin;
    x = xmin;
}

float Rect::getXMax() const {
    return x + width;
}

void Rect::setXMax(float xmax) {
    width = xmax - x;
}

float Rect::getYMin() const {
    return y;
}
void Rect::setYMin(float ymin) {
    height += y - ymin;
    y = ymin;
}

float Rect::getYMax() const {
    return y + height;
}

void Rect::setYMax(float ymax) {
    height = ymax - y;
}

Vector2 Rect::getMin() const {
    return Vector2(getXMin(), getYMin());
}

void Rect::setMin(const Vector2& min) {
    setXMin(min.x);
    setYMin(min.y);
}

void Rect::setMin(float xmin, float ymin) {
    setXMin(xmin);
    setYMin(ymin);
}
Vector2 Rect::getMax() const {
    return Vector2(getXMax(), getYMax());
}

void Rect::setMax(const Vector2& max) {
    setXMax(max.x);
    setYMax(max.y);
}

void Rect::setMax(float xmax, float ymax) {
    setXMax(xmax);
    setYMax(ymax);
}

Vector2 Rect::getCenter() const {
    return Vector2(x + width * 0.5f, y + height * 0.5f);
}

bool Rect::contains(const Vector2& point) const {
    if (point.x < x) return false;
    if (point.y < y)return false;
    if (point.x > getXMax())return false;
    if (point.y > getYMax()) return false;
    return true;
}

bool Rect::intersects(const Rect& rect) const {
    if (getXMin() < rect.getXMax() && getXMax() > rect.getXMin()) {
        if (getYMin() < rect.getYMax() && getYMax() > rect.getYMax()) {
            return true;
        }
    }
    return false;
}

} //Math 
} //Framework 
